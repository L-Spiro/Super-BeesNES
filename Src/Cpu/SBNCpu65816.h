/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A 65816 processor.
 */


#pragma once

#include "../SBNSuperBeesNES.h"
#include "SBNCpuBase.h"

#ifdef SBN_CPU_VERIFY
#include "LSONJson.h"
#endif	// #ifdef SBN_CPU_VERIFY

#define SBN_INSTR_START_PHI1( ISREAD )									/*m_bIsReadCycle = (ISREAD)*/
#define SBN_INSTR_END_PHI1
#define SBN_INSTR_START_PHI2_READ_BUSA( ADDR, BANK, RESULT, SPEED )		RESULT = m_bBusA.Read( uint16_t( ADDR ), uint8_t( BANK ), SPEED )
#define SBN_INSTR_START_PHI2_WRITE_BUSA( ADDR, BANK, VAL, SPEED )		m_bBusA.Write( uint16_t( ADDR ), uint8_t( BANK ), uint8_t( VAL ), SPEED )
#define SBN_INSTR_START_PHI2_READ0_BUSA( ADDR, RESULT, SPEED )			RESULT = m_bBusA.ReadBank0( uint16_t( ADDR ), SPEED )
#define SBN_INSTR_START_PHI2_WRITE0_BUSA( ADDR, VAL, SPEED )			m_bBusA.WriteBank0( uint16_t( ADDR ), uint8_t( VAL ), SPEED )
#define SBN_INSTR_END_PHI2

#define SBN_NEXT_FUNCTION_BY( AMT )										m_ui8FuncIndex += AMT
#define SBN_NEXT_FUNCTION												SBN_NEXT_FUNCTION_BY( 1 )
#define SBN_FINISH_INST( CHECK_INTERRUPTS )								/*if constexpr ( CHECK_INTERRUPTS ) { SBN_CHECK_INTERRUPTS; }*/ m_pfTickFunc = m_pfTickFuncCopy = &CCpu65816::Tick_NextInstructionStd

#define SBN_PUSH( VAL, SPEED )											SBN_INSTR_START_PHI2_WRITE0_BUSA( m_bEmulationMode ? (0x100 | m_rRegs.ui8S[0]) : m_rRegs.ui16S, (VAL), (SPEED) ); m_ui16SModify = -1
#define SBN_POP( RESULT, SPEED )										SBN_INSTR_START_PHI2_READ0_BUSA( m_bEmulationMode ? (0x100 | uint8_t( m_rRegs.ui8S[0] + 1 )) : (m_rRegs.ui16S + 1), (RESULT), (SPEED) ); m_ui16SModify = 1

#define SBN_UPDATE_PC													if ( m_bAllowWritingToPc ) { m_rRegs.ui16Pc += m_ui16PcModify; } m_ui16PcModify = 0
#define SBN_UPDATE_S													m_rRegs.ui16S += m_ui16SModify; m_ui16SModify = 0

namespace sbn {

	/**
	 * Class CCpu65816
	 * \brief A 65816 processor.
	 *
	 * Description: A 65816 processor.
	 */
	class CCpu65816 : public CCpuBase {
		typedef CCpuBase									Parent;
	public :
		// == Various constructors.
		CCpu65816( CBusA &_bBusA );
		~CCpu65816();


		// == Enumeration.
		/** Status flags. */
		static constexpr uint8_t							C() { return (1 << 0); }														/**< Carry         (0=No Carry, 1=Carry). */
		static constexpr uint8_t							Z() { return (1 << 1); }														/**< Zero          (0=Nonzero, 1=Zero). */
		static constexpr uint8_t							I() { return (1 << 2); }														/**< IRQ Disable   (0=IRQ Enable, 1=IRQ Disable). */
		static constexpr uint8_t							D() { return (1 << 3); }														/**< Decimal Mode  (0=Normal, 1=BCD Mode for ADC/SBC opcodes). */
		static constexpr uint8_t							X() { return (1 << 4); }														/**< Break Flag    (0=IRQ/NMI, 1=BRK/PHP opcode)  (0=16bit, 1=8bit). */
		static constexpr uint8_t							M() { return (1 << 5); }														/**< Unused        (Always 1)                     (0=16bit, 1=8bit). */
		static constexpr uint8_t							V() { return (1 << 6); }														/**< Overflow      (0=No Overflow, 1=Overflow). */
		static constexpr uint8_t							N() { return (1 << 7); }														/**< Negative/Sign (0=Positive, 1=Negative). */

		/** Special addresses. */
		enum SBN_VECTORS : uint16_t {
			SBN_V_RESERVED2_E								= 0xFFF0,																		/**< Reserved. */
			SBN_V_RESERVED1_E								= 0xFFF2,																		/**< Reserved. */
			SBN_V_COP_E										= 0xFFF4,																		/**< The address of execution during a COP Software interrupt. */
			SBN_V_RESERVED0_E								= 0xFFF6,																		/**< Reserved. */
			SBN_V_ABORT_E									= 0xFFF8,																		/**< The address of execution during an abort interrupt. */
			SBN_V_NMI_E										= 0xFFFA,																		/**< The address of execution during an NMI interrupt. */
			SBN_V_RESET_E									= 0xFFFC,																		/**< The address of execution during a reset. */
			SBN_V_IRQ_BRK_E									= 0xFFFE,																		/**< The address of execution during an IRQ or BRK interrupt. */

			SBN_V_IRQ										= 0xFFEE,																		/**< The address of execution during an IRQ interrupt. */
			SBN_V_RESERVED0									= 0xFFEC,																		/**< Reserved. */
			SBN_V_NMI										= 0xFFEA,																		/**< The address of execution during an NMI interrupt. */
			SBN_V_ABORT										= 0xFFE8,																		/**< The address of execution during an abort interrupt. */
			SBN_V_BRK										= 0xFFE6,																		/**< The address of execution during an BRK interrupt. */
			SBN_V_COP										= 0xFFE4,																		/**< The address of execution during a COP Software interrupt. */
			SBN_V_RESERVED1									= 0xFFE2,																		/**< Reserved. */
			SBN_V_RESERVED2									= 0xFFE0,																		/**< Reserved. */
		};


		// == Types.
		/** The processor registers. */
		struct SBN_REGISTERS {
			union {
				uint8_t										ui8A[2];																		/**< A     Accumulator. */
				uint16_t									ui16A;																			/**< A     Accumulator. */
			};
			union {
				uint8_t										ui8X[2];																		/**< X     Index Register X. */
				uint16_t									ui16X;																			/**< X     Index Register X. */
			};
			union {
				uint8_t										ui8Y[2];																		/**< Y     Index Register Y. */
				uint16_t									ui16Y;																			/**< Y     Index Register Y. */
			};
			union {
				uint8_t										ui8Pc[2];																		/**< PC    Program Counter. */
				uint16_t									ui16Pc;																			/**< PC    Program Counter. */
			};
			union {
				uint8_t										ui8S[2];																		/**< S     Stack Pointer. */
				uint16_t									ui16S;																			/**< S     Stack Pointer. */
			};
			uint8_t											ui8Status = 0;																	/**< The processor status register. */
			union {
				uint8_t										ui8D[2];																		/**< D     Zeropage Offset      ;expands 8bit  [nn]   to 16bit [00:nn+D]. */
				uint16_t									ui16D;																			/**< D     Zeropage Offset      ;expands 8bit  [nn]   to 16bit [00:nn+D]. */
			};
			uint8_t											ui8Db = 0;																		/**< DB    Data Bank            ;expands 16bit [nnnn] to 24bit [DB:nnnn]. */
			uint8_t											ui8Pb = 0;																		/**< PB    Program Counter Bank ;expands 16bit PC     to 24bit PB:PC. */
		};

		typedef void (CCpu65816:: *							PfCycle)();																		/**< A function pointer for the functions that handle each cycle. */
		typedef void (CCpu65816:: *							PfTicks)();																		/**< A function pointer for the tick handlers. */

		/** An instruction. The micro-functions (pfHandler) that make up each cycle of each instruction are programmed to know what to do and can correctly pass the cycles without
		 *	using ui8TotalCycles or amAddrMode. This means pcName, ui8TotalCycles, and amAddrMode are only used for debugging, verification, printing things, etc.
		 * Since we are adding work by increasing the number of functions calls per instruction, we get that time back by not checking for addressing modes or referencing any other
		 *	tables or data.  For the sake of performance, each micro-function just knows what to do and does so in the most efficient manner possible, free from any unnecessary
		 *	branching etc.
		 * pfHandler points to an array of functions that can handle all possible cycles for a given instruction, and we use a subtractive process for eliminating optional cycles
		 *	rather than using the additive approach most commonly found in emulators.
		 */
		struct SBN_INSTR {
			PfCycle											pfHandler[2][SBN_M_MAX_INSTR_CYCLE_COUNT*2];									/**< Indexed by SBN_CPU_CONTEXT::ui8FuncIdx, these functions handle each cycle of the instruction. */
			uint8_t											ui8TotalCyclesN;																/**< Total non-optional non-overlapping cycles in the instruction. Used only for debugging, disassembling, etc. */
			uint8_t											ui8TotalCyclesE;																/**< Total non-optional non-overlapping cycles in the instruction. Used only for debugging, disassembling, etc. */
			SBN_ADDRESSING_MODES							amAddrMode;																		/**< Addressing mode. Used only for debugging, disassembling, etc. */
			uint8_t											ui8SizeN;																		/**< Size in bytes of the instruction (native). Used only for debugging, disassembling, etc. */
			uint8_t											ui8SizeE;																		/**< Size in bytes of the instruction (emulation mode). Used only for debugging, disassembling, etc. */
			SBN_INSTRUCTIONS								iInstruction;																	/**< The instruction. */
		};


		// == Functions.
		/**
		 * Performs a single PHI1 update.
		 */
		virtual void										TickPhi1();

		/**
		 * Performs a single PHI2 update.
		 **/
		virtual void										TickPhi2();

		/**
		 * Resets the bus to a known state.
		 */
		void												ResetToKnown() {
			ResetAnalog();
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
			m_pfTickFunc = m_pfTickFuncCopy = &CCpu65816::Tick_NextInstructionStd;
			m_bBoundaryCrossed = false;
			m_ui16PcModify = 0;
			m_ui16SModify = 0;
			m_bAllowWritingToPc = true;
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
		PfTicks												m_pfTickFunc;																		/**< The current tick function (called by Tick()). */
		PfTicks												m_pfTickFuncCopy;																	/**< A copy of the current tick, used to restore the intended original tick when control flow is changed by DMA transfers. */
		SBN_REGISTERS										m_rRegs;																			/**< Registers. */
		CBusA &												m_bBusA;																			/**< Bus A. */

		SBN_VECTORS											m_vBrkVector = SBN_V_BRK;															/**< The vector to use inside BRK and whether to push B with status. */
		union {
			uint8_t											m_ui8Operand[2];																	/**< The operand. */
			uint16_t										m_ui16Operand;																		/**< The operand. */
		};
		union {
			uint8_t											m_ui8Address[2];																	/**< An address loaded into memory before transfer to a register such as PC. */
			uint16_t										m_ui16Address;																		/**< An address loaded into memory before transfer to a register such as PC. */
		};
		union {
			uint8_t											m_ui8Pointer[2];																	/**< An address loaded into memory for indirect access. */
			uint16_t										m_ui16Pointer;																		/**< An address loaded into memory for indirect access. */
		};
		uint16_t											m_ui16OpCode = 0;																	/**< The current opcode. */
		uint16_t											m_ui16PcModify = 0;																	/**< The amount by which to modify PC during the next Phi1. */
		uint16_t											m_ui16SModify = 0;																	/**< The amount by which to modify S during the next Phi1. */
		uint8_t												m_ui8FuncIndex = 0;																	/**< The function index. */
		uint8_t												m_ui8Bank = 0;																		/**< Holds the bank for long reads/writes. */
		
		bool												m_bIsReadCycle = true;																/**< Is the current cycle a read? */
		bool												m_bBoundaryCrossed = false;															/**< Did we cross a page boundary? */
		bool												m_bPushB = false;																	/**< Push the B flag with the status byte? */
		bool												m_bAllowWritingToPc = true;															/**< Allow writing to PC? */
		bool												m_bTakeJump;																		/**< Determines if a branch is taken. */
		
		bool												m_bEmulationMode = true;															/**< Emulation Mode flag. */
		static SBN_INSTR									m_iInstructionSet[256];																/**< The instruction set. */


#ifdef SBN_CPU_VERIFY
		// == Types.
		struct SBN_CPU_VERIFY_RAM {
			uint32_t										ui32Addr;
			uint8_t											ui8Value;
		};

		struct SBN_CPU_VERIFY_STATE {
			SBN_REGISTERS									cvrRegisters;
			std::vector<SBN_CPU_VERIFY_RAM>					vRam;
			bool											bEmulationMode;
		};

		struct SBN_CPU_VERIFY_CYCLE {
			uint32_t										ui32Addr;
			uint8_t											ui8Value;
			std::string										sStatus;
			bool											bNoReadOrWrite;
		};

		struct SBN_CPU_VERIFY_OBJ {
			std::string										sName;
			SBN_CPU_VERIFY_STATE							cvsStart;
			SBN_CPU_VERIFY_STATE							cvsEnd;
			std::vector<SBN_CPU_VERIFY_CYCLE>				vCycles;
		};


		// == Functions.
		/**
		 * Given a JSON object and the value for the test to run, this loads the test and fills a SBN_CPU_VERIFY structure.
		 *
		 * \param _jJson The JSON file.
		 * \param _jvTest The test to run.
		 * \param _cvoTest The test structure to fill out.
		 * \return Returns true if the JSON data was successfully extracted and the test created.
		 */
		bool												GetTest( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvTest, SBN_CPU_VERIFY_OBJ &_cvoTest );

		/**
		 * Fills out a SBN_CPU_VERIFY_STATE structure given a JSON "initial" or "final" member.
		 *
		 * \param _jJson The JSON file.
		 * \param _jvState The bject member representing the state to load.
		 * \param _cvsState The state structure to fill.
		 * \return Returns true if the state was loaded.
		 */
		bool												LoadState( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvState, SBN_CPU_VERIFY_STATE &_cvsState );
#endif	// #ifdef SBN_CPU_VERIFY


		// == Functions.
		/** Fetches the next opcode and begins the next instruction. */
		inline void											Tick_NextInstructionStd();

		/** Performs a cycle inside an instruction. */
		inline void											Tick_InstructionCycleStd();


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		// CYCLES
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		/** Adds D and m_ui8Operand[0] and X, stores in m_ui16Address. */
		inline void											AddDAndOperandAndXToAddressAndIncPc();

		/** Adds D and m_ui8Operand[0], stores in m_ui16Address. */
		inline void											AddDAndOperandToAddressAndIncPc();

		/** Adds D and m_ui8Operand[0], stores in m_ui16Pointer. */
		inline void											AddDAndOperandToPointerAndIncPc();

		/** Adds S to m_ui16Pointer, stores in m_ui16Address. */
		inline void											AddStackOffsetAndIncPc();

		/** Adds X to m_ui16Pointer and D, stores to m_ui16Address. */
		inline void											AddXAndDAndPointerToAddressAndIncPc();

		/** Adds Y to m_ui16Address. */
		inline void											AddYToAddress();

		/** Adds Y to m_ui16Address. */
		//inline void											AddYToAddress_WithPageSkip_AndIncPc();

		/** Adds Y to m_ui16Pointer. */
		inline void											AddYToPointer();

		/** Adds Y to m_ui16Pointer, copies m_rRegs.ui8Db to m_ui8Bank. */
		inline void											AddYToPointerAndSetBank();

		/** Adds Y to m_ui16Pointer, sets m_ui8Bank. */
		inline void											AddYToPointerWithBankOverflow();

		/** Adds Y to m_ui16Pointer, sets m_ui8Bank. */
		inline void											AddYToPointerWithBankOverflowAndPageSkip();

		/** Performs M <<= 1.  Sets C, N, and V. */
		inline void											Asl();

		/** Performs M <<= 1.  Sets C, N, and V, increases PC. */
		inline void											AslAndIncPc();

		/** Performs A <<= 1.  Sets C, N, and V. */
		inline void											AslOnA();

		/** 2nd cycle of branch instructions. Fetches opcode of next instruction and performs the check to decide which cycle comes next (or to end the instruction). */
		template <unsigned _uBit, unsigned _uVal>
		inline void											Branch_Cycle2();

		/** 2nd cycle of branch instructions. Fetches opcode of next instruction and performs the check to decide which cycle comes next (or to end the instruction). */
		inline void											Branch_Cycle2_Phi2();

		/** 3rd cycle of branch instructions. Branch was taken and might have crossed a page boundary. */
		inline void											Branch_Cycle3();

		/** 3rd cycle of branch instructions. Branch was taken and might have crossed a page boundary. */
		inline void											Branch_Cycle3_Phi2();

		/** 3rd cycle of branch instructions. Branch was taken and might have crossed a page boundary. */
		inline void											Branch_Cycle3_Native();

		/** 4th cycle of branch instructions. Page boundary was crossed. */
		inline void											Branch_Cycle4();

		/** Copies the vector address into PC. */
		inline void											Brk();

		/** Clears the carry bit. */
		inline void											Clc();

		/** Clears the IRQ flag. */
		inline void											Cli();

		/** Fetches the low byte of the NMI/IRQ/BRK/reset vector into the low byte of PC. */
		inline void											CopyVectorPcl();

		/** Fetches the low byte of the NMI/IRQ/BRK/reset vector into the low byte of PC. */
		inline void											CopyVectorPcl_Phi2();

		/** Fetches the high byte of the NMI/IRQ/BRK/reset vector into the high byte of PC and sets the I flag. */
		inline void											CopyVectorPch();

		/** Fetches the high byte of the NMI/IRQ/BRK/reset vector into the high byte of PC and sets the I flag. */
		inline void											CopyVectorPch_Phi2();

		/** Fetches the address and increments PC. */
		inline void											FetchAddressAndIncPc_Phi2();

		/** Fetches into m_ui8Address[1] and increments PC .*/
		inline void											FetchAddressHighAndIncPc_Phi2();

		/** Fetches to m_ui8Bank and increments PC .*/
		inline void											FetchBankhAndIncPc_Phi2();

		/** Fetches the next operand and increments the PC. */
		inline void											FetchOpcodeAndIncPc();

		/** Fetches the next opcode and does not the program counter. */
		inline void											FetchOperand_Phi2();

		/** Fetches the operand. */
		inline void											FetchOperandAndDiscard_Phi2();

		/** Fetches the next operand and increments the PC. */
		inline void											FetchOperandAndIncPc_Phi2();

		/** Fetches the next operand and increments the PC. */
		inline void											FetchOperandHighAndIncPc_Phi2();

		/** Fetches the next operand and increments the PC. */
		inline void											FetchOperandLowAndIncPc_SkipIfM_Phi2();

		/** Fetches the next operand and increments the PC, performs the D.l skip. */
		inline void											FetchOperandAndIncPc_WithDlSkip_Phi2();

		/** Fetches to m_ui16Pointer and increments PC .*/
		inline void											FetchPointerHighAndIncPc_Phi2();

		/** Fetches to m_ui16Pointer and increments PC .*/
		inline void											FetchPointerAndIncPc_Phi2();

		/** Fixes the high bit of m_ui16Address. */
		inline void											FixPointerHigh();

		/** Performs A++.  Sets N and Z. */
		inline void											IncOnA();

		/** Increments PC. */
		inline void											NullIncPc_Read();

		/** Increments PC. */
		inline void											NullIncPc_Write();

		/** Does nothing. */
		inline void											Null_Read();

		/** Does nothing. */
		inline void											Null_Write();

		/** A no-op Phi2. */
		inline void											Null_Phi2();

		/** Adjusts S after stack operation. */
		inline void											NullAdjustS_Read();

		/** Adjusts S after stack operation. */
		inline void											NullAdjustS_Write();

		/** Skips the next cycle if M() is set. */
		inline void											Null_SkipIfM();

		/** Performs ORA with m_ui8Operand[0]. */
		inline void											Ora();

		/** Performs ORA with m_ui8Operand[0]. */
		inline void											OraAndIncPc();

		/** Sets m_ui8Operand to the status byte with Break and Reserved set. */
		inline void											Php();

		/** Copies the vector address into PC. */
		inline void											PrefetchNextOp();

		/** Pushes m_ui8Operand[0]. */
		inline void											PushOperandLow_Phi2();

		/** Pushes D.h. */
		inline void											PushDh_Phi2();

		/** Pushes D.l. */
		inline void											PushDl_Phi2();

		/** Pushes PB. */
		inline void											PushPb();

		/** Pushes PB. */
		inline void											PushPb_Phi2();

		/** Pushes PCH. */
		inline void											PushPch();

		/** Pushes PCH. */
		inline void											PushPch_Phi2();

		/** Pushes PCL. */
		inline void											PushPcl();

		/** Pushes PCL. */
		inline void											PushPcl_Phi2();

		/** Pushes the status byte with B conditionally set. */
		inline void											PushStatus();

		/** Pushes the status byte with B conditionally set. */
		inline void											PushStatus_Phi2();

		/** Pushes the status byte without B. */
		inline void											PushStatusCop();

		/** Pushes the status byte without B. */
		inline void											PushStatusCop_Phi2();

		/** Reads from m_ui16Address and Bank and stores the result in m_ui8Operand[1]. */
		inline void											ReadAddressAndBankToOperandHigh_Phi2();

		/** Reads from m_ui16Address and Bank and stores the result in m_ui8Operand[0]. */
		inline void											ReadAddressAndBankToOperandLow_Phi2();

		/** Reads from m_ui16Address and Bank and stores the result in m_ui8Operand[0]. */
		inline void											ReadAddressAndBankToOperandLow_SkipIfM_Phi2();

		/** Reads from m_ui16Address and stores the result in m_ui8Bank. */
		inline void											ReadAddressToBankLow_Phi2();

		/** Reads from m_ui16Address and stores the result in m_ui8Bank. */
		inline void											ReadAddressToBankLow_WithLowByteWrap_Phi2();

		/** Reads from m_ui16Address and stores the result in m_ui8Operand[1]. */
		inline void											ReadAddressToOperandHigh_Phi2();

		/** Reads from m_ui16Address and stores the result in m_ui8Operand[0]. */
		inline void											ReadAddressToOperandLow_Phi2();

		/** Reads from m_ui16Address and stores the result in m_ui8Operand[0]. */
		inline void											ReadAddressToOperandLow_SkipIfM_Phi2();

		/** Reads from m_ui16Address and stores the result in m_ui8Pointer[1]. */
		inline void											ReadAddressToPointerHigh_Phi2();

		/** Reads from m_ui16Address and stores the result in m_ui8Pointer[1]. */
		inline void											ReadAddressToPointerHigh_WithLowByteWrap_Phi2();

		/** Reads from m_ui16Address and stores the result in m_ui8Pointer[0]. */
		inline void											ReadAddressToPointerLow_Phi2();

		/** Reads from m_ui16Pointer and the bank in m_ui8Bank, stores result in m_ui8Operand[1]. */
		inline void											ReadPointerAndBankToOperandHigh_Phi2();

		/** Reads from m_ui16Pointer and the bank in m_ui8Bank, stores result in m_ui8Operand[0]. */
		inline void											ReadPointerAndBankToOperandLow_SkipIfM_Phi2();

		/** Reads from m_ui16Pointer and the bank in m_ui8Bank, stores result in m_ui8Operand[0]. */
		inline void											ReadPointerAndBankToOperandLow_Phi2();

		/** Reads from m_ui16Pointer and stores the low byte in m_ui8Address[1]. */
		inline void											ReadPointerToAddressHigh_Phi2();

		/** Reads from m_ui16Pointer and stores the low byte in m_ui8Address[0]. */
		inline void											ReadPointerToAddressLow();

		/** Reads from m_ui16Pointer and stores the low byte in m_ui8Address[0]. */
		inline void											ReadPointerToAddressLow_Phi2();

		/** Reads from the stack offset address stored in m_ui16Address. */
		inline void											ReadStackOffsetHigh_Phi2();

		/** Reads from the stack offset address stored in m_ui16Address. */
		inline void											ReadStackOffsetLow_Phi2();

		/** Skips the next instruction if the M status flag is set. */
		inline void											SkipIfM_Phi2();

		/** Skips the next instruction if the low byte of D is 0. */
		inline void											SkipOnDL_Phi2();

		/** Transfer 16 bit A to S.  Sets N and Z. */
		inline void											Tcs();

		/** Performs m_ui16Operand &= ~A.  Sets Z. */
		inline void											Trb();

		/** Performs m_ui16Operand |= A.  Sets Z. */
		inline void											Tsb();

		/** Writes m_ui8Operand[1] to m_ui16Address. */
		inline void											WriteOperandHighToAddress_Phi2();

		/** Writes m_ui8Operand[1] to m_ui16Address with bank. */
		inline void											WriteOperandHighToAddressAndBank_Phi2();

		/** Writes m_ui8Operand[0] to m_ui16Address. */
		inline void											WriteOperandLowToAddress_Phi2();

		/** Writes m_ui8Operand[0] to m_ui16Address with bank. */
		inline void											WriteOperandLowToAddressAndBank_Phi2();

		/** Writes m_ui8Operand[0] to m_ui16Address. */
		inline void											WriteOperandLowToAddress_SkipIfM_Phi2();

		/** Writes m_ui8Operand[0] to m_ui16Address with bank. */
		inline void											WriteOperandLowToAddressAndBank_SkipIfM_Phi2();

		/**
		 * Prepares to enter a new instruction.
		 */
		inline void											BeginInst();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// DEFINITIONS
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	// == Fuctions.
	/** Fetches the next opcode and begins the next instruction. */
	inline void CCpu65816::Tick_NextInstructionStd() {
		// Expects the opcode to be in m_ui16Operand.
		FetchOpcodeAndIncPc();
	}

	/** Performs a cycle inside an instruction. */
	inline void CCpu65816::Tick_InstructionCycleStd() {
		(this->*m_iInstructionSet[m_ui16OpCode].pfHandler[m_bEmulationMode][m_ui8FuncIndex])();
	}

	/** Adds D and m_ui8Operand[0] and X, stores in m_ui16Address. */
	inline void CCpu65816::AddDAndOperandAndXToAddressAndIncPc() {
		SBN_INSTR_START_PHI1( true );

		SBN_UPDATE_PC;

		if ( m_bEmulationMode && m_rRegs.ui8D[0] == 0x00 ) {
			m_ui8Address[0] = uint8_t( m_ui16Operand + m_rRegs.ui16X + m_rRegs.ui16D );
			m_ui8Address[1] = m_rRegs.ui8D[1];
		}
		else {
			m_ui16Address = m_ui16Operand + m_rRegs.ui16X + m_rRegs.ui16D;
		}

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Adds D and m_ui8Operand[0], stores in m_ui16Address. */
	inline void CCpu65816::AddDAndOperandToAddressAndIncPc() {
		SBN_INSTR_START_PHI1( true );

		SBN_UPDATE_PC;

		/*if ( m_bEmulationMode ) {
			m_ui16Address = m_ui16Pointer + m_rRegs.ui16D;
		}
		else {*/
			m_ui16Address = m_ui16Operand + m_rRegs.ui16D;
		//}

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Adds D and m_ui8Operand[0], stores in m_ui16Pointer. */
	inline void CCpu65816::AddDAndOperandToPointerAndIncPc() {
		SBN_INSTR_START_PHI1( true );

		SBN_UPDATE_PC;

		/*if ( m_bEmulationMode ) {
			m_ui16Address = m_ui16Pointer + m_rRegs.ui16D;
		}
		else {*/
			m_ui16Pointer = m_ui16Operand + m_rRegs.ui16D;
		//}

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Adds S to m_ui16Pointer, stores in m_ui16Address. */
	inline void CCpu65816::AddStackOffsetAndIncPc() {
		SBN_INSTR_START_PHI1( false );

		SBN_UPDATE_PC;

		if ( m_bEmulationMode ) {
			m_ui16Address = m_ui16Pointer + (m_rRegs.ui8S[0] | 0x100);
		}
		else {
			m_ui16Address = m_ui16Pointer + m_rRegs.ui16S;
		}

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Adds X to m_ui16Pointer and D, stores to m_ui16Address. */
	inline void CCpu65816::AddXAndDAndPointerToAddressAndIncPc() {
		SBN_INSTR_START_PHI1( false );

		SBN_UPDATE_PC;

		if ( m_bEmulationMode ) {
			m_ui8Address[0] = uint8_t( m_ui16Pointer + m_rRegs.ui16X + m_rRegs.ui16D );
			m_ui8Address[1] = uint8_t( m_rRegs.ui16D >> 8 );
		}
		else {
			m_ui16Address = m_ui16Pointer + m_rRegs.ui16X + m_rRegs.ui16D;
		}

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Adds Y to m_ui16Address. */
	inline void CCpu65816::AddYToAddress() {
		SBN_INSTR_START_PHI1( false );

		SBN_UPDATE_PC;

		m_ui16Address += m_rRegs.ui16Y;

		/*if ( m_bEmulationMode ) {
			m_ui8Address[0] = uint8_t( m_ui16Pointer + m_rRegs.ui16X + m_rRegs.ui16D );
			m_ui8Address[1] = uint8_t( m_rRegs.ui16D >> 8 );
		}
		else {
			m_ui16Address = m_ui16Pointer + m_rRegs.ui16X + m_rRegs.ui16D;
		}*/

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Adds Y to m_ui16Address. */
	/*inline void CCpu65816::AddYToAddress_WithPageSkip_AndIncPc() {
		SBN_INSTR_START_PHI1( false );

		SBN_UPDATE_PC;

		uint32_t ui32Orig = m_ui16Address;
		uint32_t ui32Tmp = m_ui16Address + m_rRegs.ui16Y;
		m_ui16Address = uint16_t( ui32Tmp );

		if ( uint8_t( ui32Orig >> 8 ) == m_ui8Address[1] ) {
			SBN_NEXT_FUNCTION_BY( 2 );
		}

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}*/

	/** Adds Y to m_ui16Pointer. */
	inline void CCpu65816::AddYToPointer() {
		SBN_INSTR_START_PHI1( true );

		SBN_UPDATE_PC;

		m_ui16Pointer += m_rRegs.ui16Y;

		/*if ( m_bEmulationMode ) {
			m_ui8Address[0] = uint8_t( m_ui16Pointer + m_rRegs.ui16X + m_rRegs.ui16D );
			m_ui8Address[1] = uint8_t( m_rRegs.ui16D >> 8 );
		}
		else {
			m_ui16Address = m_ui16Pointer + m_rRegs.ui16X + m_rRegs.ui16D;
		}*/

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Adds Y to m_ui16Pointer, copies m_rRegs.ui8Db to m_ui8Bank. */
	inline void CCpu65816::AddYToPointerAndSetBank() {
		SBN_INSTR_START_PHI1( false );

		SBN_UPDATE_PC;

		m_ui16Pointer += m_rRegs.ui16Y;
		m_ui8Bank = m_rRegs.ui8Db;

		/*if ( m_bEmulationMode ) {
			m_ui8Address[0] = uint8_t( m_ui16Pointer + m_rRegs.ui16X + m_rRegs.ui16D );
			m_ui8Address[1] = uint8_t( m_rRegs.ui16D >> 8 );
		}
		else {
			m_ui16Address = m_ui16Pointer + m_rRegs.ui16X + m_rRegs.ui16D;
		}*/

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Adds Y to m_ui16Pointer, sets m_ui8Bank. */
	inline void CCpu65816::AddYToPointerWithBankOverflow() {
		SBN_INSTR_START_PHI1( false );

		SBN_UPDATE_PC;

		uint32_t ui32Orig = m_ui16Pointer;
		uint32_t ui32Tmp = m_ui16Pointer + m_rRegs.ui16Y;
		m_ui16Pointer = uint16_t( ui32Tmp );
		m_ui8Bank += (ui32Tmp >> 16);

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Adds Y to m_ui16Pointer, sets m_ui8Bank. */
	inline void CCpu65816::AddYToPointerWithBankOverflowAndPageSkip() {
		SBN_INSTR_START_PHI1( false );

		SBN_UPDATE_PC;

		uint32_t ui32Orig = m_ui16Pointer;
		uint32_t ui32Tmp = m_ui16Pointer + m_rRegs.ui16Y;
		m_ui16Pointer = uint16_t( ui32Tmp );
		m_ui8Bank = m_rRegs.ui8Db + (ui32Tmp >> 16);

		if ( uint8_t( ui32Orig >> 8 ) == m_ui8Pointer[1] ) {
			SBN_NEXT_FUNCTION_BY( 2 );
		}
		/*if ( m_bEmulationMode ) {
			m_ui8Address[0] = uint8_t( m_ui16Pointer + m_rRegs.ui16X + m_rRegs.ui16D );
			m_ui8Address[1] = uint8_t( m_rRegs.ui16D >> 8 );
		}
		else {
			m_ui16Address = m_ui16Pointer + m_rRegs.ui16X + m_rRegs.ui16D;
		}*/

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Performs M <<= 1.  Sets C, N, and V. */
	inline void CCpu65816::Asl() {
		SBN_INSTR_START_PHI1( true );

		if ( (m_rRegs.ui8Status & M()) ) {
			SetBit<C()>( m_rRegs.ui8Status, (m_ui8Operand[0] & 0x80) != 0 );

			m_ui16Operand <<= 1;

			SetBit<N()>( m_rRegs.ui8Status, (m_ui8Operand[0] & 0x80) != 0 );
			SetBit<Z()>( m_rRegs.ui8Status, !m_ui8Operand[0] );
		}
		else {
			SetBit<C()>( m_rRegs.ui8Status, (m_ui8Operand[1] & 0x80) != 0 );

			m_ui16Operand <<= 1;

			SetBit<N()>( m_rRegs.ui8Status, (m_ui8Operand[1] & 0x80) != 0 );
			SetBit<Z()>( m_rRegs.ui8Status, !m_ui16Operand );
		}
		

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Performs M <<= 1.  Sets C, N, and V, increases PC. */
	inline void CCpu65816::AslAndIncPc() {
		SBN_INSTR_START_PHI1( true );

		SBN_UPDATE_PC;

		if ( (m_rRegs.ui8Status & M()) ) {
			SetBit<C()>( m_rRegs.ui8Status, (m_ui8Operand[0] & 0x80) != 0 );

			m_ui16Operand <<= 1;

			SetBit<N()>( m_rRegs.ui8Status, (m_ui8Operand[0] & 0x80) != 0 );
			SetBit<Z()>( m_rRegs.ui8Status, !m_ui8Operand[0] );
		}
		else {
			SetBit<C()>( m_rRegs.ui8Status, (m_ui8Operand[1] & 0x80) != 0 );

			m_ui16Operand <<= 1;

			SetBit<N()>( m_rRegs.ui8Status, (m_ui8Operand[1] & 0x80) != 0 );
			SetBit<Z()>( m_rRegs.ui8Status, !m_ui16Operand );
		}
		

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Performs A <<= 1.  Sets C, N, and V. */
	inline void CCpu65816::AslOnA() {
		SBN_INSTR_START_PHI1( true );

		if ( (m_rRegs.ui8Status & M()) ) {
			SetBit<C()>( m_rRegs.ui8Status, (m_rRegs.ui8A[0] & 0x80) != 0 );

			m_rRegs.ui8A[0] <<= 1;

			SetBit<N()>( m_rRegs.ui8Status, (m_rRegs.ui8A[0] & 0x80) != 0 );
			SetBit<Z()>( m_rRegs.ui8Status, !m_rRegs.ui8A[0] );
		}
		else {
			SetBit<C()>( m_rRegs.ui8Status, (m_rRegs.ui8A[1] & 0x80) != 0 );

			m_rRegs.ui16A <<= 1;

			SetBit<N()>( m_rRegs.ui8Status, (m_rRegs.ui8A[1] & 0x80) != 0 );
			SetBit<Z()>( m_rRegs.ui8Status, !m_rRegs.ui16A );
		}
		

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** 2nd cycle of branch instructions. Fetches opcode of next instruction and performs the check to decide which cycle comes next (or to end the instruction). */
	template <unsigned _uBit, unsigned _uVal>
	inline void CCpu65816::Branch_Cycle2() {
		SBN_INSTR_START_PHI1( true );

		m_bTakeJump = (m_rRegs.ui8Status & _uBit) == (_uVal * _uBit);
		SBN_UPDATE_PC;

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** 2nd cycle of branch instructions. Fetches opcode of next instruction and performs the check to decide which cycle comes next (or to end the instruction). */
	inline void CCpu65816::Branch_Cycle2_Phi2() {
		if ( !m_bTakeJump ) {
			SBN_FINISH_INST( true );
		}
		else {
			SBN_NEXT_FUNCTION;

			m_ui16Address = static_cast<int16_t>(static_cast<int8_t>(m_ui8Operand[0])) + m_rRegs.ui16Pc;

			m_bBoundaryCrossed = m_ui8Address[1] != m_rRegs.ui8Pc[1];
			if ( !m_bBoundaryCrossed ) {
				//SBN_CHECK_INTERRUPTS;
			}
		}

		SBN_INSTR_END_PHI2;
	}

	/** 3rd cycle of branch instructions. Branch was taken and might have crossed a page boundary. */
	inline void CCpu65816::Branch_Cycle3() {
		SBN_INSTR_START_PHI1( true );

		m_rRegs.ui8Pc[0] = m_ui8Address[0];

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** 3rd cycle of branch instructions. Branch was taken and might have crossed a page boundary. */
	inline void CCpu65816::Branch_Cycle3_Phi2() {
		if ( m_bBoundaryCrossed ) {
			SBN_NEXT_FUNCTION;
		}
		else {
			SBN_FINISH_INST( false );
		}

		SBN_INSTR_END_PHI2;
	}

	/** 3rd cycle of branch instructions. Branch was taken and might have crossed a page boundary. */
	inline void CCpu65816::Branch_Cycle3_Native() {
		SBN_INSTR_START_PHI1( true );

		m_rRegs.ui16Pc = m_ui16Address;

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** 4th cycle of branch instructions. Page boundary was crossed. */
	inline void CCpu65816::Branch_Cycle4() {
		SBN_INSTR_START_PHI1( true );

		m_rRegs.ui8Pc[1] = m_ui8Address[1];

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Copies the vector address into PC. */
	inline void CCpu65816::Brk() {
		SBN_INSTR_START_PHI1( true );

		m_bAllowWritingToPc = true;
		m_rRegs.ui16Pc = m_ui16Address;
		m_rRegs.ui8Pb = 0;

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Clears the carry bit. */
	inline void CCpu65816::Clc() {
		SBN_INSTR_START_PHI1( true );
		
		SetBit<C(), false>( m_rRegs.ui8Status );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Clears the IRQ flag. */
	inline void CCpu65816::Cli() {
		SBN_INSTR_START_PHI1( true );

		SetBit<I(), false>( m_rRegs.ui8Status );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Fetches the low byte of the NMI/IRQ/BRK/reset vector into the low byte of PC. */
	inline void CCpu65816::CopyVectorPcl() {
		SBN_INSTR_START_PHI1( true );

		SBN_UPDATE_S;

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Fetches the low byte of the NMI/IRQ/BRK/reset vector into the low byte of PC. */
	inline void CCpu65816::CopyVectorPcl_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ0_BUSA( m_vBrkVector, m_ui8Address[0], ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Fetches the high byte of the NMI/IRQ/BRK/reset vector into the high byte of PC and sets the I flag. */
	inline void CCpu65816::CopyVectorPch() {
		SBN_INSTR_START_PHI1( true );

		SetBit<I(), true>( m_rRegs.ui8Status );
		SetBit<D(), false>( m_rRegs.ui8Status );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Fetches the high byte of the NMI/IRQ/BRK/reset vector into the high byte of PC and sets the I flag. */
	inline void CCpu65816::CopyVectorPch_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ0_BUSA( m_vBrkVector + 1, m_ui8Address[1], ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Fetches the address and increments PC. */
	inline void CCpu65816::FetchAddressAndIncPc_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ_BUSA( m_rRegs.ui16Pc, m_rRegs.ui8Pb, m_ui16Address, ui8Speed );
		m_ui16PcModify = 1;
		
		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Fetches into m_ui8Address[1] and increments PC .*/
	inline void CCpu65816::FetchAddressHighAndIncPc_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ_BUSA( m_rRegs.ui16Pc, m_rRegs.ui8Pb, m_ui8Address[1], ui8Speed );
		m_ui16PcModify = 1;
		
		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Fetches to m_ui8Bank and increments PC .*/
	inline void CCpu65816::FetchBankhAndIncPc_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ_BUSA( m_rRegs.ui16Pc, m_rRegs.ui8Pb, m_ui8Bank, ui8Speed );
		m_ui16PcModify = 1;
		
		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Fetches the next operand and increments the PC. */
	inline void CCpu65816::FetchOpcodeAndIncPc() {
		SBN_INSTR_START_PHI1( true );
		m_ui16OpCode = m_ui16Operand;
		
		SBN_UPDATE_PC;

		SBN_NEXT_FUNCTION;

		BeginInst();
		SBN_INSTR_END_PHI1;
	}

	/** Fetches the next opcode and does not the program counter. */
	inline void CCpu65816::FetchOperand_Phi2() {
		uint8_t ui8Speed;
		uint8_t ui8Op;
		SBN_INSTR_START_PHI2_READ_BUSA( m_rRegs.ui16Pc, m_rRegs.ui8Pb, ui8Op, ui8Speed );
		m_ui16Operand = ui8Op;
		
		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Fetches the operand. */
	inline void CCpu65816::FetchOperandAndDiscard_Phi2() {
		uint8_t ui8Speed;
		uint8_t ui8Op;
		SBN_INSTR_START_PHI2_READ_BUSA( m_rRegs.ui16Pc, m_rRegs.ui8Pb, ui8Op, ui8Speed );
		
		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Fetches the next operand and increments the PC. */
	inline void CCpu65816::FetchOperandAndIncPc_Phi2() {
		uint8_t ui8Speed;
		uint8_t ui8Op;
		SBN_INSTR_START_PHI2_READ_BUSA( m_rRegs.ui16Pc, m_rRegs.ui8Pb, ui8Op, ui8Speed );
		m_ui16Operand = ui8Op;
		m_ui16PcModify = 1;
		
		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Fetches the next operand and increments the PC. */
	inline void CCpu65816::FetchOperandHighAndIncPc_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ_BUSA( m_rRegs.ui16Pc, m_rRegs.ui8Pb, m_ui8Operand[1], ui8Speed );
		m_ui16PcModify = 1;
		
		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Fetches the next operand and increments the PC. */
	inline void CCpu65816::FetchOperandLowAndIncPc_SkipIfM_Phi2() {
		uint8_t ui8Speed;
		uint8_t ui8Op;
		SBN_INSTR_START_PHI2_READ_BUSA( m_rRegs.ui16Pc, m_rRegs.ui8Pb, ui8Op, ui8Speed );
		m_ui16Operand = ui8Op;
		m_ui16PcModify = 1;
		
		SBN_NEXT_FUNCTION;

		if ( (m_rRegs.ui8Status & M()) ) {
			SBN_NEXT_FUNCTION_BY( 2 );
		}

		SBN_INSTR_END_PHI2;
	}

	/** Fetches the next operand and increments the PC, performs the D.l skip. */
	inline void CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2() {
		uint8_t ui8Speed;
		uint8_t ui8Op;
		SBN_INSTR_START_PHI2_READ_BUSA( m_rRegs.ui16Pc, m_rRegs.ui8Pb, ui8Op, ui8Speed );
		m_ui16Operand = ui8Op;
		m_ui16PcModify = 1;
		
		SBN_NEXT_FUNCTION;

		if ( !(m_rRegs.ui16D & 0xFF) ) {
			SBN_NEXT_FUNCTION_BY( 2 );
		}

		SBN_INSTR_END_PHI2;
	}

	/** Fetches to m_ui16Pointer and increments PC .*/
	inline void CCpu65816::FetchPointerHighAndIncPc_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ_BUSA( m_rRegs.ui16Pc, m_rRegs.ui8Pb, m_ui8Pointer[1], ui8Speed );
		m_ui16PcModify = 1;
		
		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Fetches to m_ui16Pointer and increments PC .*/
	inline void CCpu65816::FetchPointerAndIncPc_Phi2() {
		uint8_t ui8Speed;
		uint8_t ui8Op;
		SBN_INSTR_START_PHI2_READ_BUSA( m_rRegs.ui16Pc, m_rRegs.ui8Pb, ui8Op, ui8Speed );
		m_ui16Pointer = ui8Op;
		m_ui16PcModify = 1;
		
		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Fixes the high bit of m_ui16Address. */
	inline void CCpu65816::FixPointerHigh() {
		SBN_INSTR_START_PHI1( false );

		m_ui8Address[1] = uint8_t( (m_ui16Pointer + m_rRegs.ui16X + m_rRegs.ui16D) >> 8 );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Performs A++.  Sets N and Z. */
	inline void CCpu65816::IncOnA() {
		SBN_INSTR_START_PHI1( true );

		if ( (m_rRegs.ui8Status & M()) ) {
			++m_rRegs.ui8A[0];
			SetBit<N()>( m_rRegs.ui8Status, m_rRegs.ui8A[0] & 0x80 );
			SetBit<Z()>( m_rRegs.ui8Status, !m_rRegs.ui8A[0] );
		}
		else {
			++m_rRegs.ui16A;
			SetBit<N()>( m_rRegs.ui8Status, m_rRegs.ui8A[1] & 0x80 );
			SetBit<Z()>( m_rRegs.ui8Status, !m_rRegs.ui16A );
		}

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Increments PC. */
	inline void CCpu65816::NullIncPc_Read() {
		SBN_INSTR_START_PHI1( true );

		SBN_UPDATE_PC;

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Increments PC. */
	inline void CCpu65816::NullIncPc_Write() {
		SBN_INSTR_START_PHI1( false );

		SBN_UPDATE_PC;

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Does nothing. */
	inline void CCpu65816::Null_Read() {
		SBN_INSTR_START_PHI1( true );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Does nothing. */
	inline void CCpu65816::Null_Write() {
		SBN_INSTR_START_PHI1( false );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** A no-op Phi2. */
	inline void CCpu65816::Null_Phi2() {
		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Adjusts S after stack operation. */
	inline void CCpu65816::NullAdjustS_Read() {
		SBN_INSTR_START_PHI1( true );

		SBN_UPDATE_S;

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Adjusts S after stack operation. */
	inline void CCpu65816::NullAdjustS_Write() {
		SBN_INSTR_START_PHI1( false );

		SBN_UPDATE_S;

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Skips the next cycle if M() is set. */
	inline void CCpu65816::Null_SkipIfM() {
		SBN_INSTR_START_PHI1( false );

		SBN_NEXT_FUNCTION;

		if ( (m_rRegs.ui8Status & M()) ) {
			SBN_NEXT_FUNCTION_BY( 2 );
		}

		SBN_INSTR_END_PHI1;
	}

	/** Performs ORA with m_ui8Operand[0]. */
	inline void CCpu65816::Ora() {
		SBN_INSTR_START_PHI1( true );

		m_rRegs.ui16A |= m_ui16Operand;

		if ( (m_rRegs.ui8Status & M()) ) {
			SetBit<N()>( m_rRegs.ui8Status, m_rRegs.ui8A[0] & 0x80 );
			SetBit<Z()>( m_rRegs.ui8Status, !m_rRegs.ui8A[0] );
		}
		else {
			SetBit<N()>( m_rRegs.ui8Status, m_rRegs.ui8A[1] & 0x80 );
			SetBit<Z()>( m_rRegs.ui8Status, !m_rRegs.ui16A );
		}
		

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Performs ORA with m_ui8Operand[0]. */
	inline void CCpu65816::OraAndIncPc() {
		SBN_INSTR_START_PHI1( true );

		SBN_UPDATE_PC;

		m_rRegs.ui16A |= m_ui16Operand;

		if ( (m_rRegs.ui8Status & M()) ) {
			SetBit<N()>( m_rRegs.ui8Status, m_rRegs.ui8A[0] & 0x80 );
			SetBit<Z()>( m_rRegs.ui8Status, !m_rRegs.ui8A[0] );
		}
		else {
			SetBit<N()>( m_rRegs.ui8Status, m_rRegs.ui8A[1] & 0x80 );
			SetBit<Z()>( m_rRegs.ui8Status, !m_rRegs.ui16A );
		}
		

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Sets m_ui8Operand to the status byte with Break and Reserved set. */
	inline void CCpu65816::Php() {
		SBN_INSTR_START_PHI1( true );

		m_ui8Operand[0] = m_rRegs.ui8Status;
		SetBit<X() | M(), true>( m_ui8Operand[0] );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Copies the vector address into PC. */
	inline void CCpu65816::PrefetchNextOp() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ_BUSA( m_rRegs.ui16Pc, m_rRegs.ui8Pb, m_ui16Operand, ui8Speed );

		SBN_FINISH_INST( true );

		SBN_INSTR_END_PHI2;
	}

	/** Pushes m_ui8Operand[0]. */
	inline void CCpu65816::PushOperandLow_Phi2() {
		uint8_t ui8Speed;
		SBN_PUSH( m_ui8Operand[0], ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Pushes D.h. */
	inline void CCpu65816::PushDh_Phi2() {
		uint8_t ui8Speed;
		SBN_PUSH( m_rRegs.ui8D[1], ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Pushes D.l. */
	inline void CCpu65816::PushDl_Phi2() {
		uint8_t ui8Speed;
		SBN_PUSH( m_rRegs.ui8D[0], ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Pushes PB. */
	inline void CCpu65816::PushPb() {
		SBN_INSTR_START_PHI1( false );

		SBN_UPDATE_PC;

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Pushes PB. */
	inline void CCpu65816::PushPb_Phi2() {
		uint8_t ui8Speed;
		SBN_PUSH( m_rRegs.ui8Pb, ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Pushes PCH. */
	inline void CCpu65816::PushPch() {
		SBN_INSTR_START_PHI1( true );

		SBN_UPDATE_PC;
		SBN_UPDATE_S;

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Pushes PCH. */
	inline void CCpu65816::PushPch_Phi2() {
		uint8_t ui8Speed;
		SBN_PUSH( m_rRegs.ui8Pc[1], ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Pushes PCL. */
	inline void CCpu65816::PushPcl() {
		SBN_INSTR_START_PHI1( true );

		SBN_UPDATE_S;

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Pushes PCL. */
	inline void CCpu65816::PushPcl_Phi2() {
		uint8_t ui8Speed;
		SBN_PUSH( m_rRegs.ui8Pc[0], ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Pushes the status byte with B conditionally set. */
	inline void CCpu65816::PushStatus() {
		SBN_INSTR_START_PHI1( false );

		SBN_UPDATE_S;

		// Select vector to use.
		if ( m_bEmulationMode ) {
			m_vBrkVector = SBN_V_IRQ_BRK_E;
			m_bPushB = true;
		}
		else {
			m_vBrkVector = SBN_V_BRK;
			m_bPushB = false;
		}

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Pushes the status byte with B conditionally set. */
	inline void CCpu65816::PushStatus_Phi2() {
		uint8_t ui8Speed;
		if ( m_bPushB ) {
			SBN_PUSH( m_rRegs.ui8Status | X(), ui8Speed );
		}
		else {
			SBN_PUSH( m_rRegs.ui8Status, ui8Speed );
		}

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Pushes the status byte without B. */
	inline void CCpu65816::PushStatusCop() {
		SBN_INSTR_START_PHI1( true );

		SBN_UPDATE_S;

		// Select vector to use.
		if ( m_bEmulationMode ) {
			m_vBrkVector = SBN_V_COP_E;
		}
		else {
			m_vBrkVector = SBN_V_COP;
		}

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Pushes the status byte without B. */
	inline void CCpu65816::PushStatusCop_Phi2() {
		uint8_t ui8Speed;
		SBN_PUSH( m_rRegs.ui8Status, ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Reads from m_ui16Address and Bank and stores the result in m_ui8Operand[1]. */
	inline void CCpu65816::ReadAddressAndBankToOperandHigh_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ_BUSA( m_ui16Address + 1, m_rRegs.ui8Db, m_ui8Operand[1], ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Reads from m_ui16Address and Bank and stores the result in m_ui8Operand[0]. */
	inline void CCpu65816::ReadAddressAndBankToOperandLow_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ_BUSA( m_ui16Address, m_rRegs.ui8Db, m_ui16Operand, ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Reads from m_ui16Address and Bank and stores the result in m_ui8Operand[0]. */
	inline void CCpu65816::ReadAddressAndBankToOperandLow_SkipIfM_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ_BUSA( m_ui16Address, m_rRegs.ui8Db, m_ui16Operand, ui8Speed );

		SBN_NEXT_FUNCTION;

		if ( (m_rRegs.ui8Status & M()) ) {
			SBN_NEXT_FUNCTION_BY( 2 );
		}

		SBN_INSTR_END_PHI2;
	}

	/** Reads from m_ui16Address and stores the result in m_ui8Bank. */
	inline void CCpu65816::ReadAddressToBankLow_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ0_BUSA( m_ui16Address + 2, m_ui8Bank, ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Reads from m_ui16Address and stores the result in m_ui8Bank. */
	inline void CCpu65816::ReadAddressToBankLow_WithLowByteWrap_Phi2() {
		uint8_t ui8Speed;
		if ( !(m_rRegs.ui16D & 0xFF) ) {
			SBN_INSTR_START_PHI2_READ0_BUSA( uint8_t( m_ui8Address[0] + 2 ) | (m_ui8Address[1] << 8), m_ui8Bank, ui8Speed );
		}
		else {
			SBN_INSTR_START_PHI2_READ0_BUSA( m_ui16Address + 2, m_ui8Bank, ui8Speed );
		}

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Reads from m_ui16Address and stores the result in m_ui8Operand[1]. */
	inline void CCpu65816::ReadAddressToOperandHigh_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ0_BUSA( m_ui16Address + 1, m_ui8Operand[1], ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Reads from m_ui16Address and stores the result in m_ui8Operand[0]. */
	inline void CCpu65816::ReadAddressToOperandLow_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ0_BUSA( m_ui16Address, m_ui16Operand, ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Reads from m_ui16Address and stores the result in m_ui8Operand[0]. */
	inline void CCpu65816::ReadAddressToOperandLow_SkipIfM_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ0_BUSA( m_ui16Address, m_ui16Operand, ui8Speed );

		SBN_NEXT_FUNCTION;

		if ( (m_rRegs.ui8Status & M()) ) {
			SBN_NEXT_FUNCTION_BY( 2 );
		}

		SBN_INSTR_END_PHI2;
	}

	/** Reads from m_ui16Address and stores the result in m_ui8Pointer[1]. */
	inline void CCpu65816::ReadAddressToPointerHigh_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ0_BUSA( m_ui16Address + 1, m_ui8Pointer[1], ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Reads from m_ui16Address and stores the result in m_ui8Pointer[1]. */
	inline void CCpu65816::ReadAddressToPointerHigh_WithLowByteWrap_Phi2() {
		uint8_t ui8Speed;
		if ( !(m_rRegs.ui16D & 0xFF) ) {
			SBN_INSTR_START_PHI2_READ0_BUSA( uint8_t( m_ui8Address[0] + 1 ) | (m_ui8Address[1] << 8), m_ui8Pointer[1], ui8Speed );
		}
		else {
			SBN_INSTR_START_PHI2_READ0_BUSA( m_ui16Address + 1, m_ui8Pointer[1], ui8Speed );
		}

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Reads from m_ui16Address and stores the result in m_ui8Pointer[0]. */
	inline void CCpu65816::ReadAddressToPointerLow_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ0_BUSA( m_ui16Address, m_ui16Pointer, ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Reads from m_ui16Pointer and the bank in m_ui8Bank, stores result in m_ui8Operand[1]. */
	inline void CCpu65816::ReadPointerAndBankToOperandHigh_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ_BUSA( m_ui16Pointer + 1, m_ui8Bank, m_ui8Operand[1], ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Reads from m_ui16Pointer and the bank in m_ui8Bank, stores result in m_ui8Operand[0]. */
	inline void CCpu65816::ReadPointerAndBankToOperandLow_SkipIfM_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ_BUSA( m_ui16Pointer, m_ui8Bank, m_ui16Operand, ui8Speed );

		SBN_NEXT_FUNCTION;

		if ( (m_rRegs.ui8Status & M()) ) {
			SBN_NEXT_FUNCTION_BY( 2 );
		}

		SBN_INSTR_END_PHI2;
	}

	/** Reads from m_ui16Pointer and the bank in m_ui8Bank, stores result in m_ui8Operand[0]. */
	inline void CCpu65816::ReadPointerAndBankToOperandLow_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ_BUSA( m_ui16Pointer, m_ui8Bank, m_ui16Operand, ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Reads from m_ui16Pointer and stores the low byte in m_ui8Address[1]. */
	inline void CCpu65816::ReadPointerToAddressHigh_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ0_BUSA( m_ui16Pointer + 1, m_ui8Address[1], ui8Speed );
		
		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Reads from m_ui16Pointer and stores the low byte in m_ui8Address[0]. */
	inline void CCpu65816::ReadPointerToAddressLow() {
		SBN_INSTR_START_PHI1( true );

		m_ui16Pointer = m_ui16Address;

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Reads from m_ui16Pointer and stores the low byte in m_ui8Address[0]. */
	inline void CCpu65816::ReadPointerToAddressLow_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ0_BUSA( m_ui16Pointer, m_ui8Address[0], ui8Speed );
		
		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Reads from the stack offset address stored in m_ui16Address. */
	inline void CCpu65816::ReadStackOffsetHigh_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ0_BUSA( m_ui16Address + 1, m_ui8Operand[1], ui8Speed );

		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Reads from the stack offset address stored in m_ui16Address. */
	inline void CCpu65816::ReadStackOffsetLow_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_READ0_BUSA( m_ui16Address, m_ui16Operand, ui8Speed );
		
		SBN_NEXT_FUNCTION;

		if ( (m_rRegs.ui8Status & M()) ) {
			SBN_NEXT_FUNCTION_BY( 2 );
		}

		SBN_INSTR_END_PHI2;
	}

	/** Skips the next instruction if the M status flag is set. */
	inline void CCpu65816::SkipIfM_Phi2() {
		SBN_NEXT_FUNCTION;

		if ( (m_rRegs.ui8Status & M()) ) {
			SBN_NEXT_FUNCTION_BY( 2 );
		}

		SBN_INSTR_END_PHI2;
	}

	/** Skips the next instruction if the low byte of D is 0. */
	inline void CCpu65816::SkipOnDL_Phi2() {
		SBN_NEXT_FUNCTION;

		if ( !(m_rRegs.ui16D & 0xFF) ) {
			SBN_NEXT_FUNCTION_BY( 2 );
		}

		SBN_INSTR_END_PHI2;
	}

	/** Transfer 16 bit A to S.  Sets N and Z. */
	inline void CCpu65816::Tcs() {
		SBN_INSTR_START_PHI1( false );

		if ( m_bEmulationMode ) {
			m_rRegs.ui16S = m_rRegs.ui8A[0];
		}
		else {
			m_rRegs.ui16S = m_rRegs.ui16A;
		}
		/*if ( (m_rRegs.ui8Status & M()) ) {
			SetBit<N()>( m_rRegs.ui8Status, m_rRegs.ui8S[0] & 0x80 );
			SetBit<Z()>( m_rRegs.ui8Status, !m_rRegs.ui8S[0] );
		}
		else {
			SetBit<N()>( m_rRegs.ui8Status, m_rRegs.ui8S[1] & 0x80 );
			SetBit<Z()>( m_rRegs.ui8Status, !m_rRegs.ui16S );
		}*/


		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Performs m_ui16Operand &= ~A.  Sets Z. */
	inline void CCpu65816::Trb() {
		SBN_INSTR_START_PHI1( false );

		if ( (m_rRegs.ui8Status & M()) ) {
			SetBit<Z()>( m_rRegs.ui8Status, (m_rRegs.ui8A[0] & m_ui8Operand[0]) == 0 );
		}
		else {
			SetBit<Z()>( m_rRegs.ui8Status, (m_rRegs.ui16A & m_ui16Operand) == 0 );
		}
		
		m_ui16Operand &= ~m_rRegs.ui16A;


		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Performs m_ui16Operand |= A.  Sets Z. */
	inline void CCpu65816::Tsb() {
		SBN_INSTR_START_PHI1( false );

		if ( (m_rRegs.ui8Status & M()) ) {
			SetBit<Z()>( m_rRegs.ui8Status, (m_rRegs.ui8A[0] & m_ui8Operand[0]) == 0 );
		}
		else {
			SetBit<Z()>( m_rRegs.ui8Status, (m_rRegs.ui16A & m_ui16Operand) == 0 );
		}
		
		m_ui16Operand |= m_rRegs.ui16A;


		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI1;
	}

	/** Writes m_ui8Operand[1] to m_ui16Address. */
	inline void CCpu65816::WriteOperandHighToAddress_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_WRITE0_BUSA( m_ui16Address + 1, m_ui8Operand[1], ui8Speed );
		
		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Writes m_ui8Operand[1] to m_ui16Address with bank. */
	inline void CCpu65816::WriteOperandHighToAddressAndBank_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_WRITE_BUSA( m_ui16Address + 1, m_rRegs.ui8Db, m_ui8Operand[1], ui8Speed );
		
		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Writes m_ui8Operand[0] to m_ui16Address. */
	inline void CCpu65816::WriteOperandLowToAddress_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_WRITE0_BUSA( m_ui16Address, m_ui8Operand[0], ui8Speed );
		
		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Writes m_ui8Operand[0] to m_ui16Address with bank. */
	inline void CCpu65816::WriteOperandLowToAddressAndBank_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_WRITE_BUSA( m_ui16Address, m_rRegs.ui8Db, m_ui8Operand[0], ui8Speed );
		
		SBN_NEXT_FUNCTION;

		SBN_INSTR_END_PHI2;
	}

	/** Writes m_ui8Operand[0] to m_ui16Address. */
	inline void CCpu65816::WriteOperandLowToAddress_SkipIfM_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_WRITE0_BUSA( m_ui16Address, m_ui8Operand[0], ui8Speed );
		
		SBN_NEXT_FUNCTION;

		if ( (m_rRegs.ui8Status & M()) ) {
			SBN_NEXT_FUNCTION_BY( 2 );
		}

		SBN_INSTR_END_PHI2;
	}

	/** Writes m_ui8Operand[0] to m_ui16Address with bank. */
	inline void CCpu65816::WriteOperandLowToAddressAndBank_SkipIfM_Phi2() {
		uint8_t ui8Speed;
		SBN_INSTR_START_PHI2_WRITE_BUSA( m_ui16Address, m_rRegs.ui8Db, m_ui8Operand[0], ui8Speed );
		
		SBN_NEXT_FUNCTION;

		if ( (m_rRegs.ui8Status & M()) ) {
			SBN_NEXT_FUNCTION_BY( 2 );
		}

		SBN_INSTR_END_PHI2;
	}

	/**
	 * Prepares to enter a new instruction.
	 *
	 * \param _ui16Op The instruction to begin executing.
	 */
	inline void CCpu65816::BeginInst() {
		// Enter normal instruction context.
		m_ui8FuncIndex = 0;
		m_pfTickFunc = m_pfTickFuncCopy = &CCpu65816::Tick_InstructionCycleStd;
		m_bBoundaryCrossed = false;
		if ( m_bEmulationMode ) {
			m_rRegs.ui8S[1] = 1;
		}
	}

}	// namespace sbn
