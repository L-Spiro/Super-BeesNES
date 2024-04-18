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
			SBN_AM_RELATIVE,																/**< Relative jumping = 2 extra cycles. */
			SBN_AM_ABSOLUTE,																/**< Absolute addressing = 3 extra cycles. */
			SBN_AM_ABSOLUTE_X,																/**< Absolute X addressing = 3 extra cycles + optional cycle. */
			SBN_AM_ABSOLUTE_Y,																/**< Absolute Y addressing = 3 extra cycles + optional cycle. */
			SBN_AM_INDIRECT_X,																/**< Indirect X addressing = 5 extra cycles. */
			SBN_AM_INDIRECT_Y,																/**< Indirect Y addressing = 4 extra cycles + optional cycle. */
			SBN_AM_INDIRECT,																/**< Absolute indirect addressing (JMP) = 4 extra cycles. */
		};
		/** Instructions. Numbers specified because these are used in look-up tables. */
		enum SBN_INSTRUCTIONS : uint8_t {
			SBN_I_ADC						= 0,											/**< Add with carry. */
			SBN_I_AND						= 1,											/**< AND with accumulator. */
			SBN_I_ASL						= 2,											/**< Arithmetic shift left. */
			SBN_I_BCC						= 3,											/**< Branch on carry clear. */
			SBN_I_BCS						= 4,											/**< Branch on carry set. */
			SBN_I_BEQ						= 5,											/**< Branch on equal (zero set). */
			SBN_I_BIT						= 6,											/**< Bit test. */
			SBN_I_BMI						= 7,											/**< Branch on minus (negative set). */
			SBN_I_BNE						= 8,											/**< Branch on not equal (zero clear). */
			SBN_I_BPL						= 9,											/**< Branch on plus (negative clear). */
		/**/	SBN_I_BRK						= 10,											/**< Break/interrupt. */
			SBN_I_BVC						= 11,											/**< Branch on overflow clear. */
			SBN_I_BVS						= 12,											/**< Branch on overflow set. */
			SBN_I_CLC						= 13,											/**< Clear carry. */
			SBN_I_CLD						= 14,											/**< Clear decimal. */
			SBN_I_CLI						= 15,											/**< Clear interrupt-disable. */
			SBN_I_CLV						= 16,											/**< Clear overflow. */
			SBN_I_CMP						= 17,											/**< Compare (with accumulator). */
			SBN_I_CPX						= 18,											/**< Compare with X. */
			SBN_I_CPY						= 19,											/**< Compare with Y. */
			SBN_I_DEC						= 20,											/**< Decrement. */
			SBN_I_DEX						= 21,											/**< Decrement X. */
			SBN_I_DEY						= 22,											/**< Decrement Y. */
			SBN_I_EOR						= 23,											/**< XOR with accumulator. */
			SBN_I_INC						= 24,											/**< Increment. */
			SBN_I_INX						= 25,											/**< Increment X. */
			SBN_I_INY						= 26,											/**< Increment Y. */
			SBN_I_JMP						= 27,											/**< Jump. */
			SBN_I_JSR						= 28,											/**< Jump subroutine. */
			SBN_I_LDA						= 29,											/**< Load accumulator. */
			SBN_I_LDX						= 30,											/**< Load X. */
			SBN_I_LDY						= 31,											/**< Load Y. */
			SBN_I_LSR						= 32,											/**< Logical shift right. */
			SBN_I_NOP						= 33,											/**< No operation. */
			SBN_I_ORA						= 34,											/**< OR with accumulator. */
			SBN_I_PHA						= 35,											/**< Push accumulator. */
			SBN_I_PHP						= 36,											/**< Push processor status (SR). */
			SBN_I_PLA						= 37,											/**< Pull accumulator. */
			SBN_I_PLP						= 38,											/**< Pull processor status (SR). */
			SBN_I_ROL						= 39,											/**< Rotate left. */
			SBN_I_ROR						= 40,											/**< Rotate right. */
			SBN_I_RTI						= 41,											/**< Return from interrupt. */
			SBN_I_RTS						= 42,											/**< Return from subroutine. */
			SBN_I_SBC						= 43,											/**< Subtract with carry. */
			SBN_I_SEC						= 44,											/**< Set carry. */
			SBN_I_SED						= 45,											/**< Set decimal. */
			SBN_I_SEI						= 46,											/**< Set interrupt-disable. */
			SBN_I_STA						= 47,											/**< Store accumulator. */
			SBN_I_STX						= 48,											/**< Store X. */
			SBN_I_STY						= 49,											/**< Store Y. */
			SBN_I_TAX						= 50,											/**< Transfer accumulator to X. */
			SBN_I_TAY						= 51,											/**< Transfer accumulator to Y. */
			SBN_I_TSX						= 52,											/**< Transfer stack pointer to X. */
			SBN_I_TXA						= 53,											/**< Transfer X to accumulator. */
			SBN_I_TXS						= 54,											/**< Transfer X to stack pointer. */
			SBN_I_TYA						= 55,											/**< Transfer Y to accumulator. */

			SBN_I_ALR						= 56,											/**< Illegal. Performs A & OP; LSR. */
			SBN_I_ASR						= 56,											/**< Same as SBN_I_ALR. */
			SBN_I_ANC						= 57,											/**< Illegal. Bitwise AND with carry. C flag is set using ASL rules. */
			SBN_I_ANC2						= 58,											/**< Illegal. Bitwise AND with carry. C flag is set using ROL rules. */
			SBN_I_ANE						= 59,											/**< Illegal and highly unstable. Performs A = (A | CONST) & X & OP, where CONST is effectively random. */
			SBN_I_ARR						= 60,											/**< Illegal. Performs A = A & OP; A = (A >> 1) | (C << 7). */
			SBN_I_DCP						= 61,											/**< Illegal. Performs OP--; CMP(A, OP). */
			SBN_I_ISC						= 62,											/**< Illegal. Performs INC; SBC. */
			SBN_I_ISB						= 62,											/**< Same as SBN_I_ISC. */
			SBN_I_LAS						= 63,											/**< Illegal. Performs A = X = S = (OP & S). */
			SBN_I_LAX						= 64,											/**< Illegal. Performs A = X = OP. */
			SBN_I_LXA						= 65,											/**< Illegal and highly unstable. Performs X = A = ((A | CONST) & OP), where CONST is effectively random. */
			SBN_I_RLA						= 66,											/**< Illegal. ROL OP, A &= OP. */
			SBN_I_RRA						= 67,											/**< Illegal. ROR OP, A += OP + C. */
			SBN_I_SAX						= 68,											/**< Illegal. Performs OP = A & X. */
			SBN_I_SBX						= 69,											/**< Illegal. Performs X = (A & X) - OP, setting flags as with CMP. */
			SBN_I_SHA						= 70,											/**< Illegal. Stores A & X & (high-byte of address + 1) at the address. */
			SBN_I_SHX						= 71,											/**< Illegal. Stores X & (high-byte of address + 1) at the address. */
			SBN_I_SHY						= 72,											/**< Illegal. Stores Y & (high-byte of address + 1) at the address. */
			SBN_I_SLO						= 73,											/**< Illegal. OP <<= 1, A &= OP. */
			SBN_I_SRE						= 74,											/**< Illegal. OP >>= 1, A ^= OP. */
			SBN_I_TAS						= 75,											/**< Illegal. Performs S = A & X; Stores A & X & (high-byte of address + 1) at the address. */
			SBN_I_SHS						= 75,											/**< Same as SBN_I_TAS. */
			SBN_I_USBC						= 76,											/**< Illegal. Performs SBC + NOP. */
			SBN_I_DOP						= 77,											/**< No operation. */
			SBN_I_TOP						= 78,											/**< No operation. */
			SBN_I_JAM						= 79,											/**< Illegal. Jams the machine repeatedly putting 0xFF on the bus. */

			SBN_I_NMI						= 80,											/**< Non-opcode: NMI. */
			SBN_I_IRQ						= 81,											/**< Non-opcode: IRQ. */

			SBN_I_TOTAL
		};

		/** Other parameters. */
		enum SBN_MISC {
			SBN_M_MAX_INSTR_CYCLE_COUNT		= 7,
		};


		// == Members.
		uint64_t							m_ui64CycleCount;								/**< The total CPU cycles that have ticked. */
	};

}	// namespace sbn
