/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A 65816 processor.
 */

#include "SBNCpu65816.h"

#ifdef SBN_CPU_VERIFY
#include "EEExpEval.h"
#endif	// #ifdef SBN_CPU_VERIFY

namespace sbn {

	// == Members.
#include "SBNCycleFuncs.inl"

	// == Various constructors.
	CCpu65816::CCpu65816( CBusA &_bBusA ) :
		Parent(),
		m_bBusA( _bBusA ) {

		m_pfTickFunc = m_pfTickFuncCopy = &CCpu65816::Tick_NextInstructionStd;
	}
	CCpu65816::~CCpu65816() {
	}

	// == Functions.
	/**
	 * Performs a single PHI1 update.
	 */
	void CCpu65816::TickPhi1() {
		(this->*m_pfTickFunc)();
	}

	/**
	 * Performs a single PHI2 update.
	 **/
	void CCpu65816::TickPhi2() {
		(this->*m_pfTickFunc)();
	}

#ifdef SBN_CPU_VERIFY
	/**
	 * Runs a test given a JSON's value representing the test to run.
	 *
	 * \param _jJson The JSON file.
	 * \param _jvTest The test to run.
	 * \return Returns true if te test succeeds, false otherwise.
	 */
	bool CCpu65816::RunJsonTest( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvTest ) {
		SBN_CPU_VERIFY_OBJ cvoVerifyMe;
		if ( !GetTest( _jJson, _jvTest, cvoVerifyMe ) ) { return false; }

		// Create the initial state.
		ResetToKnown();
		m_bBusA.ApplyBasicMap();				// Set default read/write functions.
		m_ui64CycleCount = 0;
		
		m_rRegs.ui16A = cvoVerifyMe.cvsStart.cvrRegisters.ui16A;
		m_rRegs.ui16S = cvoVerifyMe.cvsStart.cvrRegisters.ui16S;
		m_rRegs.ui16X = cvoVerifyMe.cvsStart.cvrRegisters.ui16X;
		m_rRegs.ui16Y = cvoVerifyMe.cvsStart.cvrRegisters.ui16Y;

		m_rRegs.ui16D = cvoVerifyMe.cvsStart.cvrRegisters.ui16D;
		m_rRegs.ui8Db = cvoVerifyMe.cvsStart.cvrRegisters.ui8Db;
		m_rRegs.ui8Pb = cvoVerifyMe.cvsStart.cvrRegisters.ui8Pb;
		
		m_rRegs.ui8Status = cvoVerifyMe.cvsStart.cvrRegisters.ui8Status;
		m_rRegs.ui16Pc = cvoVerifyMe.cvsStart.cvrRegisters.ui16Pc;
		m_bEmulationMode = cvoVerifyMe.cvsStart.bEmulationMode;

		uint8_t ui8Speed;
		{
			for ( auto I = cvoVerifyMe.cvsStart.vRam.size(); I--; ) {
				m_bBusA.Write( uint16_t( cvoVerifyMe.cvsStart.vRam[I].ui32Addr ), uint8_t( cvoVerifyMe.cvsStart.vRam[I].ui32Addr >> 16 ), cvoVerifyMe.cvsStart.vRam[I].ui8Value, ui8Speed );
			}
			m_bBusA.ReadWriteLog().clear();
		}

		/*if ( "6b fa 28" == cvoVerifyMe.sName ) {
			volatile int ghg = 0;
		}*/
		// Tick once for each cycle.
		m_ui16Operand = m_bBusA.Read( m_rRegs.ui16Pc, m_rRegs.ui8Pb, ui8Speed );
		m_ui16PcModify = 1;
		for ( auto I = cvoVerifyMe.vCycles.size(); I--; ) {
			TickPhi1();
			TickPhi2();
		}
		m_bBusA.ReadWriteLog().pop_back();
		if ( m_bEmulationMode ) {
			m_rRegs.ui8S[1] = 1;
		}

		// Verify.
#define SBN_VURIFFY( REG )																																											\
	if ( m_rRegs. ## REG != cvoVerifyMe.cvsEnd.cvrRegisters. ## REG ) {																																\
		::OutputDebugStringA( cvoVerifyMe.sName.c_str() );																																			\
		::OutputDebugStringA( "\r\nCPU Failure: " # REG "\r\n" );																																	\
		::OutputDebugStringA( (std::string( "Expected: ") + std::to_string( cvoVerifyMe.cvsEnd.cvrRegisters. ## REG ) + std::string( " Got: " ) + std::to_string( m_rRegs. ## REG ) ).c_str() );	\
		::OutputDebugStringA( "\r\n\r\n" );																																							\
	}

		SBN_VURIFFY( ui16A );
		SBN_VURIFFY( ui16X );
		SBN_VURIFFY( ui16Y );
		SBN_VURIFFY( ui16S );

		SBN_VURIFFY( ui16D );
		SBN_VURIFFY( ui8Db );
		SBN_VURIFFY( ui8Pb );

		SBN_VURIFFY( ui8Status );
		SBN_VURIFFY( ui16Pc );
#undef SBN_VURIFFY


		if ( m_bBusA.ReadWriteLog().size() > cvoVerifyMe.vCycles.size() ) {
			::OutputDebugStringA( cvoVerifyMe.sName.c_str() );
			::OutputDebugStringA( "\r\nInternal Error\r\n" );
			::OutputDebugStringA( "\r\n\r\n" );
		}
		else {
			size_t J = 0;
			for ( size_t I = 0; I < m_bBusA.ReadWriteLog().size(); ++I ) {
				if ( m_bBusA.ReadWriteLog()[J].ui32Address != cvoVerifyMe.vCycles[I].ui32Addr ) {
					::OutputDebugStringA( cvoVerifyMe.sName.c_str() );
					::OutputDebugStringA( "\r\nCPU Failure: Cycle Address Wrong\r\n" );
					::OutputDebugStringA( (std::string( "Expected: ") + std::to_string( cvoVerifyMe.vCycles[I].ui32Addr ) + std::string( " Got: " ) + std::to_string( m_bBusA.ReadWriteLog()[J].ui32Address ) ).c_str() );
					::OutputDebugStringA( "\r\n\r\n" );
				}
				if ( m_bBusA.ReadWriteLog()[J].ui8Value != cvoVerifyMe.vCycles[I].ui8Value ) {
					::OutputDebugStringA( cvoVerifyMe.sName.c_str() );
					::OutputDebugStringA( "\r\nCPU Failure: Cycle Value Wrong\r\n" );
					::OutputDebugStringA( (std::string( "Expected: ") + std::to_string( cvoVerifyMe.vCycles[I].ui8Value ) + std::string( " Got: " ) + std::to_string( m_bBusA.ReadWriteLog()[J].ui8Value ) ).c_str() );
					::OutputDebugStringA( "\r\n\r\n" );
				}
				if ( cvoVerifyMe.vCycles[I].bNoReadOrWrite == false ) {
					if ( m_bBusA.ReadWriteLog()[I].bRead != (cvoVerifyMe.vCycles[I].sStatus[3] == 'r') ) {
						::OutputDebugStringA( cvoVerifyMe.sName.c_str() );
						::OutputDebugStringA( "\r\nCPU Failure: Cycle Read/Write Wrong\r\n" );
						::OutputDebugStringA( (std::string( "Expected: ") + std::to_string( cvoVerifyMe.vCycles[I].sStatus[3] ) + std::string( " Got: " ) + std::to_string( m_bBusA.ReadWriteLog()[J].bRead ) ).c_str() );
						::OutputDebugStringA( "\r\n\r\n" );
					}
					++J;
				}
			}
		}
		return true;
	}
#endif	// #ifdef SBN_CPU_VERIFY


#ifdef SBN_CPU_VERIFY
	/**
	 * Given a JSON object and the value for the test to run, this loads the test and fills a SBN_CPU_VERIFY structure.
	 *
	 * \param _jJson The JSON file.
	 * \param _jvTest The test to run.
	 * \param _cvoTest The test structure to fill out.
	 * \return Returns true if the JSON data was successfully extracted and the test created.
	 */
	bool CCpu65816::GetTest( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvTest, SBN_CPU_VERIFY_OBJ &_cvoTest ) {
		const lson::CJsonContainer::LSON_JSON_VALUE * pjvVal;
		// The name.
		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvTest, "name" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_STRING ) {
			_cvoTest.sName = _jJson.GetContainer()->GetString( pjvVal->u.stString );
		}
		else { return false; }

		// The initial state.
		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvTest, "initial" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_OBJECT ) {
			if ( !LoadState( _jJson, (*pjvVal), _cvoTest.cvsStart ) ) { return false; }
		}
		else { return false; }

		// The final state.
		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvTest, "final" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_OBJECT ) {
			if ( !LoadState( _jJson, (*pjvVal), _cvoTest.cvsEnd ) ) { return false; }
		}
		else { return false; }

		// The cycles.
		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvTest, "cycles" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_ARRAY ) {
			for ( size_t I = 0; I < pjvVal->vArray.size(); ++I ) {
				const lson::CJsonContainer::LSON_JSON_VALUE & jvThis = _jJson.GetContainer()->GetValue( pjvVal->vArray[I] );
				if ( jvThis.vtType == lson::CJsonContainer::LSON_VT_ARRAY && jvThis.vArray.size() == 3 ) {
					auto aReadWrite = _jJson.GetContainer()->GetValue( jvThis.vArray[1] );
					SBN_CPU_VERIFY_CYCLE cvcCycle = {
						.ui32Addr = uint32_t( _jJson.GetContainer()->GetValue( jvThis.vArray[0] ).u.dDecimal ),
						.ui8Value = uint8_t( aReadWrite.u.dDecimal ),
						.sStatus = _jJson.GetContainer()->GetString( _jJson.GetContainer()->GetValue( jvThis.vArray[2] ).u.stString ),
						.bNoReadOrWrite = aReadWrite.vtType == lson::CJsonContainer::LSON_VT_NULL,
					};
					_cvoTest.vCycles.push_back( cvcCycle );
				}
				else { return false; }
			}
		}
		else { return false; }
		return true;
	}

	/**
	 * Fills out a SBN_CPU_VERIFY_STATE structure given a JSON "initial" or "final" member.
	 *
	 * \param _jJson The JSON file.
	 * \param _jvState The bject member representing the state to load.
	 * \param _cvsState The state structure to fill.
	 * \return Returns true if the state was loaded.
	 */
	bool CCpu65816::LoadState( lson::CJson &_jJson, const lson::CJsonContainer::LSON_JSON_VALUE &_jvState, SBN_CPU_VERIFY_STATE &_cvsState ) {
		const lson::CJsonContainer::LSON_JSON_VALUE * pjvVal;

		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "pc" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_DECIMAL ) {
			_cvsState.cvrRegisters.ui16Pc = uint16_t( pjvVal->u.dDecimal );
		}
		else { return false; }

		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "s" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_DECIMAL ) {
			_cvsState.cvrRegisters.ui16S = uint16_t( pjvVal->u.dDecimal );
		}
		else { return false; }

		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "a" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_DECIMAL ) {
			_cvsState.cvrRegisters.ui16A = uint16_t( pjvVal->u.dDecimal );
		}
		else { return false; }

		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "x" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_DECIMAL ) {
			_cvsState.cvrRegisters.ui16X = uint16_t( pjvVal->u.dDecimal );
		}
		else { return false; }

		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "y" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_DECIMAL ) {
			_cvsState.cvrRegisters.ui16Y = uint16_t( pjvVal->u.dDecimal );
		}
		else { return false; }

		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "p" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_DECIMAL ) {
			_cvsState.cvrRegisters.ui8Status = uint8_t( pjvVal->u.dDecimal );
		}
		else { return false; }

		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "d" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_DECIMAL ) {
			_cvsState.cvrRegisters.ui16D = uint16_t( pjvVal->u.dDecimal );
		}
		else { return false; }

		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "dbr" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_DECIMAL ) {
			_cvsState.cvrRegisters.ui8Db = uint8_t( pjvVal->u.dDecimal );
		}
		else { return false; }

		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "pbr" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_DECIMAL ) {
			_cvsState.cvrRegisters.ui8Pb = uint8_t( pjvVal->u.dDecimal );
		}
		else { return false; }

		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "e" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_DECIMAL ) {
			_cvsState.bEmulationMode = uint8_t( pjvVal->u.dDecimal ) != 0;
		}
		else { return false; }


		pjvVal = _jJson.GetContainer()->GetMemberByName( _jvState, "ram" );
		if ( pjvVal && pjvVal->vtType == lson::CJsonContainer::LSON_VT_ARRAY ) {
			for ( size_t I = 0; I < pjvVal->vArray.size(); ++I ) {
				const lson::CJsonContainer::LSON_JSON_VALUE & jvThis = _jJson.GetContainer()->GetValue( pjvVal->vArray[I] );
				if ( jvThis.vtType == lson::CJsonContainer::LSON_VT_ARRAY && jvThis.vArray.size() == 2 ) {
					SBN_CPU_VERIFY_RAM cvrRam = {
						.ui32Addr = uint32_t( _jJson.GetContainer()->GetValue( jvThis.vArray[0] ).u.dDecimal ),
						.ui8Value = uint8_t( _jJson.GetContainer()->GetValue( jvThis.vArray[1] ).u.dDecimal ),
					};
					_cvsState.vRam.push_back( cvrRam );
				}
				else { return false; }
			}
		}
		else { return false; }

		return true;
	}
#endif	// #ifdef SBN_CPU_VERIFY

}	// namespace sbn
