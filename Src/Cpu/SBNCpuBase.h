/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The base class for all CPU's.
 */


#pragma once


#include "../SBNSuperBeesNES.h"
#include "../Bus/SBNBusA.h"

namespace sbn {

	/**
	 * Class CCpuBase
	 * \brief The base class for all CPU's.
	 *
	 * Description: The base class for all CPU's.
	 */
	class CCpuBase {
	public :
		CCpuBase() :
			m_ui64CycleCount( 0 ) {
		}


		// == Functions.
		/**
		 * Gets the current CPU cycle count.
		 *
		 * \return Returns the current CPU cycle count.
		 */
		inline uint64_t						GetCycleCount() const { return m_ui64CycleCount; }

		/**
		 * Signals an IRQ to be handled before the next instruction.
		 */
		virtual void						Irq() {}

	protected :
		// == Enumerations.
		/** Addressing modes. */
		enum SBN_ADDRESSING_MODES : uint8_t {
			SBN_AM_IMPLIED,																	/**< Implied addressing = 1 extra cycle. */
			SBN_AM_ACCUMULATOR,																/**< Accumulator = 1 extra cycle. */
			SBN_AM_IMMEDIATE,																/**< Immediate = 1 extra cycle. */
			SBN_AM_ZERO_PAGE,																/**< Zero-page = 2 extra cycles. */
			SBN_AM_ZERO_PAGE_X,																/**< Zero-page-X = 3 extra cycles. */
			SBN_AM_ZERO_PAGE_Y,																/**< Zero-page-Y = 3 extra cycles. */
			SBN_AM_DIRECT_PAGE,																/**< Direct page, up to 2 extra cycles. */
			SBN_AM_DIRECT_PAGE_INDIRECT_LONG,												/**< Direct page, up to 2 extra cycles. */
			SBN_AM_RELATIVE,																/**< Relative jumping = 2 extra cycles. */
			SBN_AM_STACK_RELATIVE,															/**< Relative jumping on stackr. */
			SBN_AM_ABSOLUTE,																/**< Absolute addressing = 3 extra cycles. */
			SBN_AM_ABSOLUTE_X,																/**< Absolute X addressing = 3 extra cycles + optional cycle. */
			SBN_AM_ABSOLUTE_Y,																/**< Absolute Y addressing = 3 extra cycles + optional cycle. */
			SBN_AM_INDIRECT_X,																/**< Indirect X addressing = 5 extra cycles. */
			SBN_AM_INDIRECT_Y,																/**< Indirect Y addressing = 4 extra cycles + optional cycle. */
			SBN_AM_INDIRECT,																/**< Absolute indirect addressing (JMP) = 4 extra cycles. */
		};

		/** Instructions. Numbers specified because these are used in look-up tables. */
		enum SBN_INSTRUCTIONS : uint8_t {
			SBN_I_ADC,											/**< Add with carry. */
			SBN_I_AND,											/**< AND with accumulator. */
		/**/	SBN_I_ASL,											/**< Arithmetic shift left. */
			SBN_I_BCC,											/**< Branch on carry clear. */
			SBN_I_BCS,											/**< Branch on carry set. */
			SBN_I_BEQ,											/**< Branch on equal (zero set). */
			SBN_I_BIT,											/**< Bit test. */
			SBN_I_BMI,											/**< Branch on minus (negative set). */
			SBN_I_BNE,											/**< Branch on not equal (zero clear). */
			SBN_I_BPL,											/**< Branch on plus (negative clear). */
		/**/	SBN_I_BRK,											/**< Break/interrupt. */
			SBN_I_BVC,											/**< Branch on overflow clear. */
			SBN_I_BVS,											/**< Branch on overflow set. */
			SBN_I_CLC,											/**< Clear carry. */
			SBN_I_CLD,											/**< Clear decimal. */
			SBN_I_CLI,											/**< Clear interrupt-disable. */
			SBN_I_CLV,											/**< Clear overflow. */
			SBN_I_CMP,											/**< Compare (with accumulator). */

		/**/	SBN_I_COP,											/**< Coprocessor routine. */

			SBN_I_CPX,											/**< Compare with X. */
			SBN_I_CPY,											/**< Compare with Y. */
			SBN_I_DEC,											/**< Decrement. */
			SBN_I_DEX,											/**< Decrement X. */
			SBN_I_DEY,											/**< Decrement Y. */
			SBN_I_EOR,											/**< XOR with accumulator. */
			SBN_I_INC,											/**< Increment. */
			SBN_I_INX,											/**< Increment X. */
			SBN_I_INY,											/**< Increment Y. */
			SBN_I_JMP,											/**< Jump. */
			SBN_I_JSR,											/**< Jump subroutine. */
			SBN_I_LDA,											/**< Load accumulator. */
			SBN_I_LDX,											/**< Load X. */
			SBN_I_LDY,											/**< Load Y. */
			SBN_I_LSR,											/**< Logical shift right. */
			SBN_I_NOP,											/**< No operation. */
		/**/	SBN_I_ORA,											/**< OR with accumulator. */
			SBN_I_PHA,											/**< Push accumulator. */
		/**/	SBN_I_PHD,											/**< Push direct page register. */
			SBN_I_PHP,											/**< Push processor status (SR). */
			SBN_I_PLA,											/**< Pull accumulator. */
			SBN_I_PLP,											/**< Pull processor status (SR). */
			SBN_I_ROL,											/**< Rotate left. */
			SBN_I_ROR,											/**< Rotate right. */
			SBN_I_RTI,											/**< Return from interrupt. */
			SBN_I_RTS,											/**< Return from subroutine. */
			SBN_I_SBC,											/**< Subtract with carry. */
			SBN_I_SEC,											/**< Set carry. */
			SBN_I_SED,											/**< Set decimal. */
			SBN_I_SEI,											/**< Set interrupt-disable. */
			SBN_I_STA,											/**< Store accumulator. */
			SBN_I_STX,											/**< Store X. */
			SBN_I_STY,											/**< Store Y. */
			SBN_I_TAX,											/**< Transfer accumulator to X. */
			SBN_I_TAY,											/**< Transfer accumulator to Y. */
			SBN_I_TSB,											/**< Test and set memory bits against accumulator. */
			SBN_I_TSX,											/**< Transfer stack pointer to X. */
			SBN_I_TXA,											/**< Transfer X to accumulator. */
			SBN_I_TXS,											/**< Transfer X to stack pointer. */
			SBN_I_TYA,											/**< Transfer Y to accumulator. */

			SBN_I_ALR,											/**< Illegal. Performs A & OP; LSR. */
			SBN_I_ASR,											/**< Same as SBN_I_ALR. */
			SBN_I_ANC,											/**< Illegal. Bitwise AND with carry. C flag is set using ASL rules. */
			SBN_I_ANC2,											/**< Illegal. Bitwise AND with carry. C flag is set using ROL rules. */
			SBN_I_ANE,											/**< Illegal and highly unstable. Performs A = (A | CONST) & X & OP, where CONST is effectively random. */
			SBN_I_ARR,											/**< Illegal. Performs A = A & OP; A = (A >> 1) | (C << 7). */
			SBN_I_DCP,											/**< Illegal. Performs OP--; CMP(A, OP). */
			SBN_I_ISC,											/**< Illegal. Performs INC; SBC. */
			SBN_I_ISB,											/**< Same as SBN_I_ISC. */
			SBN_I_LAS,											/**< Illegal. Performs A = X = S = (OP & S). */
			SBN_I_LAX,											/**< Illegal. Performs A = X = OP. */
			SBN_I_LXA,											/**< Illegal and highly unstable. Performs X = A = ((A | CONST) & OP), where CONST is effectively random. */
			SBN_I_RLA,											/**< Illegal. ROL OP, A &= OP. */
			SBN_I_RRA,											/**< Illegal. ROR OP, A += OP + C. */
			SBN_I_SAX,											/**< Illegal. Performs OP = A & X. */
			SBN_I_SBX,											/**< Illegal. Performs X = (A & X) - OP, setting flags as with CMP. */
			SBN_I_SHA,											/**< Illegal. Stores A & X & (high-byte of address + 1) at the address. */
			SBN_I_SHX,											/**< Illegal. Stores X & (high-byte of address + 1) at the address. */
			SBN_I_SHY,											/**< Illegal. Stores Y & (high-byte of address + 1) at the address. */
			SBN_I_SLO,											/**< Illegal. OP <<= 1, A &= OP. */
			SBN_I_SRE,											/**< Illegal. OP >>= 1, A ^= OP. */
			SBN_I_TAS,											/**< Illegal. Performs S = A & X; Stores A & X & (high-byte of address + 1) at the address. */
			SBN_I_SHS,											/**< Same as SBN_I_TAS. */
			SBN_I_USBC,											/**< Illegal. Performs SBC + NOP. */
			SBN_I_DOP,											/**< No operation. */
			SBN_I_TOP,											/**< No operation. */
			SBN_I_JAM,											/**< Illegal. Jams the machine repeatedly putting 0xFF on the bus. */

			SBN_I_NMI,											/**< Non-opcode: NMI. */
			SBN_I_IRQ,											/**< Non-opcode: IRQ. */

			SBN_I_TOTAL
		};

		/** Other parameters. */
		enum SBN_MISC {
			SBN_M_MAX_INSTR_CYCLE_COUNT		= 8,
		};


		// == Members.
		uint64_t							m_ui64CycleCount;								/**< The total CPU cycles that have ticked. */
	};

}	// namespace sbn
