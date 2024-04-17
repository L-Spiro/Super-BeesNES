/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A 65816 processor.
 */


#pragma once

#include "../SBNSuperBeesNES.h"
#include "../Bus/SBNBusA.h"

#ifdef SBN_CPU_VERIFY
#include "LSONJson.h"
#endif	// #ifdef SBN_CPU_VERIFY

namespace sbn {

	/**
	 * Class CCpu65816
	 * \brief A 65816 processor.
	 *
	 * Description: A 65816 processor.
	 */
	class CCpu65816 {
	public :
		// == Various constructors.
		CCpu65816( CBusA &_bBusA );
		~CCpu65816();


		// == Enumeration.
		/** Status flags. */
		constexpr uint8_t									C() { return (1 << 0); }	/**< Carry         (0=No Carry, 1=Carry). */
		constexpr uint8_t									Z() { return (1 << 1); }	/**< Zero          (0=Nonzero, 1=Zero). */
		constexpr uint8_t									I() { return (1 << 2); }	/**< IRQ Disable   (0=IRQ Enable, 1=IRQ Disable). */
		constexpr uint8_t									D() { return (1 << 3); }	/**< Decimal Mode  (0=Normal, 1=BCD Mode for ADC/SBC opcodes). */
		constexpr uint8_t									X() { return (1 << 4); }	/**< Break Flag    (0=IRQ/NMI, 1=BRK/PHP opcode)  (0=16bit, 1=8bit). */
		constexpr uint8_t									M() { return (1 << 5); }	/**< Unused        (Always 1)                     (0=16bit, 1=8bit). */
		constexpr uint8_t									V() { return (1 << 6); }	/**< Overflow      (0=No Overflow, 1=Overflow). */
		constexpr uint8_t									N() { return (1 << 7); }	/**< Negative/Sign (0=Positive, 1=Negative). */

		/** Special addresses. */
		enum class LSN_VECTORS : uint16_t {
			LSN_V_RESERVED2_E								= 0xFFF0,					/**< Reserved. */
			LSN_V_RESERVED1_E								= 0xFFF2,					/**< Reserved. */
			LSN_V_COP_E										= 0xFFF4,					/**< The address of execution during a COP Software interrupt. */
			LSN_V_RESERVED0_E								= 0xFFF6,					/**< Reserved. */
			LSN_V_ABORT_E									= 0xFFF8,					/**< The address of execution during an abort interrupt. */
			LSN_V_NMI_E										= 0xFFFA,					/**< The address of execution during an NMI interrupt. */
			LSN_V_RESET_E									= 0xFFFC,					/**< The address of execution during a reset. */
			LSN_V_IRQ_BRK_E									= 0xFFFE,					/**< The address of execution during an IRQ or BRK interrupt. */

			LSN_V_IRQ										= 0xFFEE,					/**< The address of execution during an IRQ interrupt. */
			LSN_V_RESERVED0									= 0xFFEC,					/**< Reserved. */
			LSN_V_NMI										= 0xFFEA,					/**< The address of execution during an NMI interrupt. */
			LSN_V_ABORT										= 0xFFE8,					/**< The address of execution during an abort interrupt. */
			LSN_V_BRK										= 0xFFE6,					/**< The address of execution during an BRK interrupt. */
			LSN_V_COP										= 0xFFE4,					/**< The address of execution during a COP Software interrupt. */
			LSN_V_RESERVED1									= 0xFFE2,					/**< Reserved. */
			LSN_V_RESERVED2									= 0xFFE0,					/**< Reserved. */
		};


		// == Types.
		/** The processor registers. */
		struct SBN_REGISTERS {
			union {
				uint8_t										ui8A[2];					/**< A     Accumulator. */
				uint16_t									ui16A;						/**< A     Accumulator. */
			};
			union {
				uint8_t										ui8X[2];					/**< X     Index Register X. */
				uint16_t									ui16X;						/**< X     Index Register X. */
			};
			union {
				uint8_t										ui8Y[2];					/**< Y     Index Register Y. */
				uint16_t									ui16Y;						/**< Y     Index Register Y. */
			};
			uint16_t										ui16Pc = 0;					/**< PC    Program Counter. */
			union {
				uint8_t										ui8S[2];					/**< S     Stack Pointer. */
				uint16_t									ui16S;						/**< S     Stack Pointer. */
			};
			uint8_t											ui8Status = 0;				/**< The processor status register. */
			uint16_t										ui16D = 0;					/**< D     Zeropage Offset      ;expands 8bit  [nn]   to 16bit [00:nn+D]. */
			uint8_t											ui8Db = 0;					/**< DB    Data Bank            ;expands 16bit [nnnn] to 24bit [DB:nnnn]. */
			uint8_t											ui8Pb = 0;					/**< PB    Program Counter Bank ;expands 16bit PC     to 24bit PB:PC. */
		};


		// == Functions.
		/**
		 * Resets the bus to a known state.
		 */
		void												ResetToKnown() {
			std::memset( &m_rRegs, 0, sizeof( m_rRegs ) );
			uint8_t ui8Speed;
			m_rRegs.ui16Pc = m_bBusA.Read( 0xFFFC, 0x00, ui8Speed ) | (m_bBusA.Read( 0xFFFD, 0x00, ui8Speed ) << 8);
			m_rRegs.ui8S[0] = 0xFD;
			m_bEmulationMode = true;

			m_ui64CycleCount = 0ULL;
		}

		/**
		 * Performs an "analog" reset, allowing previous data to remain.
		 */
		void												ResetAnalog() {
		}

#ifdef SBN_CPU_VERIFY
		/**
		 * Runs a test given a JSON's value representing the test to run.
		 *
		 * \param _jJson The JSON file.
		 * \param _jvTest The test to run.
		 * \return Returns true if te test succeeds, false otherwise.
		 */
		bool												RunJsonTest( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvTest );
#endif	// #ifdef SBN_CPU_VERIFY

	protected :
		// == Members.
		uint64_t											m_ui64CycleCount = 0ULL;	/**< The cycle count. */
		SBN_REGISTERS										m_rRegs;					/**< Registers. */
		CBusA &												m_bBusA;					/**< Bus A. */
		bool												m_bEmulationMode = true;	/**< Emulation Mode flag. */


		// == Functions.
#ifdef SBN_CPU_VERIFY
		// == Types.
		struct LSN_CPU_VERIFY_RAM {
			uint32_t										ui32Addr;
			uint8_t											ui8Value;
		};

		struct LSN_CPU_VERIFY_STATE {
			SBN_REGISTERS									cvrRegisters;
			std::vector<LSN_CPU_VERIFY_RAM>					vRam;
		};

		struct LSN_CPU_VERIFY_CYCLE {
			uint32_t										ui32Addr;
			uint8_t											ui8Value;
			std::string										sStatus;
		};

		struct LSN_CPU_VERIFY_OBJ {
			std::string										sName;
			LSN_CPU_VERIFY_STATE							cvsStart;
			LSN_CPU_VERIFY_STATE							cvsEnd;
			std::vector<LSN_CPU_VERIFY_CYCLE>				vCycles;
		};


		// == Functions.
		/**
		 * Given a JSON object and the value for the test to run, this loads the test and fills a LSN_CPU_VERIFY structure.
		 *
		 * \param _jJson The JSON file.
		 * \param _jvTest The test to run.
		 * \param _cvoTest The test structure to fill out.
		 * \return Returns true if the JSON data was successfully extracted and the test created.
		 */
		bool												GetTest( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvTest, LSN_CPU_VERIFY_OBJ &_cvoTest );

		/**
		 * Fills out a LSN_CPU_VERIFY_STATE structure given a JSON "initial" or "final" member.
		 *
		 * \param _jJson The JSON file.
		 * \param _jvState The bject member representing the state to load.
		 * \param _cvsState The state structure to fill.
		 * \return Returns true if the state was loaded.
		 */
		bool												LoadState( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvState, LSN_CPU_VERIFY_STATE &_cvsState );
#endif	// #ifdef SBN_CPU_VERIFY

	};

}	// namespace sbn
