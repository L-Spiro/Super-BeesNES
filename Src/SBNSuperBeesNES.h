/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A SNES emulator with the goal of being "micro-cycle–accurate." Many emulators claim to be "cycle-accurate"
 *	but are optimized to wait X cycles and then pump out all the work or otherwise do not actually divide all the work across
 *	all the cycles. In contrast, in this emulator, the work is correctly divided across the individual cycles for each
 *	instruction.
 * This means that multi-byte writes are correctly partitioned across cycles and partial data updates are possible, allowing
 *	for the more esoteric features of the system to be accurately emulated.  This means we should be able to support interrupt
 *	hijacking and any other cases that rely heavily on the cycle timing of the system.
 *
 * Additional options/features to facilitate accurate emulation:
 *	Start-Up: Start from known state or from random state.  Helps the random seed in some games.
 *	Hardware bugs will be emulated in both their buggy and fixed states (OAMADDR bugs (writing fewer than 8 ytes on the 2C02G)
 *		are examples of this).
 *	Unofficial opcodes used by games will be supported.
 *	The bus will be open and correctly maintain the last floating read.
 *	Etc.
 *
 * The CPU should be completely cycle-accurate, as every individual cycle is documented there. The same should apply to the
 *	PPU (questions surround PAL differences at the cycle level) and probably only loosely applies to the APU.  In the case of
 *	the APU, while each individual cycle may not be doing exactly the correct work, the goal is for the output to be exactly
 *	correct. This means envelope counters and sweep units etc. get updated within the correct cycles and then perhaps only
 *	minor adjustments to match the output exactly to the real thing.
 *
 * Timing will not be based off audio as is done in many emulators. We will use a real clock (with at minimum microsecond
 *	accuracy) and try to match real timings to real time units, which we can speed up and slow down as options.
 *
 * Performance should be decent enough for real-time. We are adding work to frames by adding a dereference and pointer-
 *	function call for each cycle, but the functions never leave instruction cache. If performance becomes a problem, it may
 *	warrant the creation of the approximate loops used in other emulators, leading to the scenario in which the approximate
 *	loops are used by most for gameplay and the slower original version of the emulator is used as a reference.
 *
 *
 * Other features will include:
 *	A debugger.
 *	A disassembler.
 *	An assembler.
 *	1-877-Tools-4-TAS.
 *		- Stepping and keylogging.
 *		- Movie-making.
 */


#pragma once

#include "OS/SBNOs.h"

#include <cassert>
#include <cstdint>
#include <memory>
#include <vector>


#ifndef SBN_ELEMENTS
#define SBN_ELEMENTS( x )					((sizeof( x ) / sizeof( 0[x] )) / (static_cast<size_t>(!(sizeof( x ) % sizeof( 0[x] )))))
#endif	// #ifndef SBN_ELEMENTS


namespace sbn {

	// == Enumerations.
	/** Clock speeds. */
	enum SBN_CLOCK_SPEEDS : uint64_t {
		SBN_CS_NTSC_MASTER					= 236250000ULL,						/**< The master clock speed (236.25 MHz) without the 11 divisor. */
		SBN_CS_NTSC_MASTER_DIVISOR			= 11ULL,							/**< The master clock speed divisor. 236.25 MHz / 11 = 21477272.727272727272727272727273. */

		SBN_CS_PAL_MASTER					= 21281370ULL,						/**< The master clock speed (21.281370 MHz). */
		SBN_CS_PAL_MASTER_DIVISOR			= 1ULL,								/**< The master clock speed divisor. 21.281370 MHz / 1 = 21281370. */

		SBN_CS_NTSC_CPU_DIVISOR_FAST		= 6ULL,								/**< 236.25 MHz / 11 / 6 = 3579545.4545454545454545454545455. */
		SBN_CS_PAL_CPU_DIVISOR_FAST			= 6ULL,								/**< 53.203425 MHz / 1 / 6 = 3546895. */

		SBN_CS_NTSC_CPU_DIVISOR_DMA			= 8ULL,								/**< 236.25 MHz / 11 / 8 = 2684659.0909090909090909090909091. */
		SBN_CS_PAL_CPU_DIVISOR_DMA			= 8ULL,								/**< 53.203425 MHz / 1 / 8 = 2660171.25. */

		SBN_CS_NTSC_CPU_DIVISOR_SLOW		= 12ULL,							/**< 236.25 MHz / 11 / 12 = 1789772.7272727272727272727272727. */
		SBN_CS_PAL_CPU_DIVISOR_SLOW			= 12ULL,							/**< 53.203425 MHz / 1 / 12 = 1773447.5. */

		SBN_CS_NTSC_PPU_DIVISOR				= 4ULL,								/**< 236.25 MHz / 11 / 4 = 5369318.1818181818181818181818182. */
		SBN_CS_PAL_PPU_DIVISOR				= 4ULL,								/**< 21281370 / 1 / 4 = 5320342.5. */


		SBN_CS_SPC700_MASTER				= 24576000ULL,						/**< The master clock speed (24576000 Hz) without the 11 divisor. */
		SBN_CS_SPC700_MASTER_DIVISOR		= 1ULL,								/**< The master clock speed divisor. 24576000 Hz / 1 = 24576000. */

		SBN_CS_SPC700_DSP_DIVISOR			= (24ULL*32ULL),					/**< 24576000 / (24 * 32) = 32000. */
		SBN_CS_SPC700_CPU_DIVISOR			= 24ULL,							/**< 24576000 / 24 = 1024000. */
		SBN_CS_SPC700_TIMER_0_1_DIVISOR		= (24ULL*128ULL),					/**< 24576000 / (24 * 128) = 8000. */
		SBN_CS_SPC700_TIMER_2_DIVISOR		= (24ULL*16ULL),					/**< 24576000 / (24 * 16) = 64000. */
		SBN_CS_SPC700_CIC_DIVISOR			= 8ULL,								/**< 24576000 / 8 = 3072000. */
		SBN_CS_SPC700_EXP_DIVISOR			= 3ULL,								/**< 24576000 / 3 = 8192000. */


		/*
		 * To run clocks precisely, floating-point math must be avoided.  All inputs must be accumulated in integers.
		 * The formula to determine how many cycles go into a single tick is:
		 *	ELAPSED_TIME * MASTER / (ELAPSED_TIME_RESOLUTION * MASTER_DIVISOR * HW_DIVISOR).
		 * For example, if the system time resolution is 1000000 (microseconds), and the elapsed time is 2000000 (2 seconds), then the number of NTSC CPU cycles is:
		 *	2000000 * 236250000ULL / (1000000 * 11ULL * 12ULL) = 3579545 cycles.
		 * In PAL, that would be:
		 *	2000000 * 53203425ULL / (1000000 * 2ULL * 16ULL) = 3325214 cycles.
		 * 
		 * NTSC FPS:	60.098813897440515529533511098629.
		 *				29.992002132764596107704612103439.
		 * PAL FPS:		50.006978908188585607940446650124.
		 *				24.963425305747083291300196363176.
		 * 
		 * True NTSC SMPTE TV FPS:	59.94005994005994005994005994006.
		 *							29.97002997002997002997002997003.
		 *							23.976023976023976023976023976024.
		 *							47.952047952047952047952047952048.
		 */
	};

}	// namespace sbn
