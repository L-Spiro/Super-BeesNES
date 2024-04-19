/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: Bus A.
 */


#pragma once

#include "../SBNSuperBeesNES.h"
#include "SBNBusPage.h"
#include "SBNBusPageBase.h"
#include "SBNBusPageFuncRef.h"
#include "SBNBusPageReadOnlyFuncRef.h"
#include "SBNBusPageRef.h"

#include <memory>

namespace sbn {

	/**
	 * Class CBusA
	 * \brief Bus A.
	 *
	 * Description: Bus A.
	 */
	class CBusA {
	public :
		// == Various constructors.
		CBusA() {
		}
		~CBusA() {
			ResetToKnown();
			for ( size_t I = SBN_ELEMENTS( m_pbpbPages ); I--; ) {
				m_pbpbPages[I].reset();
			}
		}


		// == Functions.
		/**
		 * Resets the bus to a known state.
		 */
		void										ResetToKnown() {
			for ( size_t I = SBN_ELEMENTS( m_pbpbPages ); I--; ) {
				//m_pbpbPages[I].reset();
				m_pbpbPages[I]->ResetToKnown();
			}
			m_ui8LastRead = 0;
		}

		/**
		 * Performs an "analog" reset, allowing previous data to remain.
		 */
		void										ResetAnalog() {
			for ( size_t I = SBN_ELEMENTS( m_pbpbPages ); I--; ) {
				m_pbpbPages[I]->ResetAnalog();
			}
		}

		/**
		 * Performs a read.
		 * 
		 * \param _ui16Address The address to read.
		 * \param _ui8Bank The bank from which to read the given address.
		 * \param _ui8Speed Returns the master-clock divisor for the given address.
		 * \return Returns the value read.
		 **/
		inline uint8_t								Read( uint16_t _ui16Address, uint8_t _ui8Bank, uint8_t &_ui8Speed ) {
			uint16_t ui16SpdAddr = (_ui16Address >> 8) | (uint16_t( _ui8Bank ) << 8);
			uint8_t * ui8Spd = m_ui8Speeds + (ui16SpdAddr >> 1);
			SBN_PREFETCH_LINE( ui8Spd );
			uint8_t ui8Mask = 0xFF;
			uint8_t ui8Ret = m_ui8LastRead;
			m_pbpbPages[_ui8Bank]->Read( _ui16Address, ui8Ret, ui8Mask );
			m_ui8LastRead = (m_ui8LastRead & ~ui8Mask) | (ui8Ret & ui8Mask);
			_ui8Speed = ((*ui8Spd) >> ((ui16SpdAddr & 1) << 2)) & 0b1111;
#ifdef SBN_CPU_VERIFY
			m_vReadWriteLog.push_back( { .ui32Address = _ui16Address | (uint32_t( _ui8Bank ) << 16), .ui8Value = ui8Ret, .bRead = true } );
#endif	// #ifdef SBN_CPU_VERIFY
			return ui8Ret;
		}

		/**
		 * Performs a write.
		 * 
		 * \param _ui16Address The address to write.
		 * \param _ui8Bank The bank to which to write to the given address.
		 * \param _ui8Speed Returns the master-clock divisor for the given address.
		 **/
		inline void									Write( uint16_t _ui16Address, uint8_t _ui8Bank, uint8_t _ui8Val, uint8_t &_ui8Speed ) {
			uint16_t ui16SpdAddr = (_ui16Address >> 8) | (uint16_t( _ui8Bank ) << 8);
			uint8_t * ui8Spd = m_ui8Speeds + (ui16SpdAddr >> 1);
			SBN_PREFETCH_LINE( ui8Spd );
			uint8_t ui8Mask = 0xFF;
			m_pbpbPages[_ui8Bank]->Write( _ui16Address, _ui8Val, ui8Mask );
			m_ui8LastRead = (m_ui8LastRead & ~ui8Mask) | (_ui8Val & ui8Mask);
			_ui8Speed = ((*ui8Spd) >> ((ui16SpdAddr & 1) << 2)) & 0b1111;
#ifdef SBN_CPU_VERIFY
			m_vReadWriteLog.push_back( { .ui32Address = _ui16Address | (uint32_t( _ui8Bank ) << 16), .ui8Value = _ui8Val, .bRead = false } );
#endif	// #ifdef SBN_CPU_VERIFY
		}

		/**
		 * Performs a read from bank 0.
		 * 
		 * \param _ui16Address The address to read.
		 * \param _ui8Bank The bank from which to read the given address.
		 * \param _ui8Speed Returns the master-clock divisor for the given address.
		 * \return Returns the value read.
		 **/
		inline uint8_t								ReadBank0( uint16_t _ui16Address, uint8_t &_ui8Speed ) {
			uint16_t ui16SpdAddr = (_ui16Address >> 8);
			uint8_t * ui8Spd = m_ui8Speeds + (ui16SpdAddr >> 1);
			SBN_PREFETCH_LINE( ui8Spd );
			uint8_t ui8Mask = 0xFF;
			uint8_t ui8Ret = m_ui8LastRead;
			m_pbpbPages[0]->Read( _ui16Address, ui8Ret, ui8Mask );
			m_ui8LastRead = (m_ui8LastRead & ~ui8Mask) | (ui8Ret & ui8Mask);
			_ui8Speed = ((*ui8Spd) >> ((ui16SpdAddr & 1) << 2)) & 0b1111;
#ifdef SBN_CPU_VERIFY
			m_vReadWriteLog.push_back( { .ui32Address = _ui16Address, .ui8Value = ui8Ret, .bRead = true } );
#endif	// #ifdef SBN_CPU_VERIFY
			return ui8Ret;
		}

		/**
		 * Performs a write to bank 0.
		 * 
		 * \param _ui16Address The address to write.
		 * \param _ui8Bank The bank to which to write to the given address.
		 * \param _ui8Speed Returns the master-clock divisor for the given address.
		 **/
		inline void									WriteBank0( uint16_t _ui16Address, uint8_t _ui8Val, uint8_t &_ui8Speed ) {
			uint16_t ui16SpdAddr = (_ui16Address >> 8);
			uint8_t * ui8Spd = m_ui8Speeds + (ui16SpdAddr >> 1);
			SBN_PREFETCH_LINE( ui8Spd );
			uint8_t ui8Mask = 0xFF;
			m_pbpbPages[0]->Write( _ui16Address, _ui8Val, ui8Mask );
			m_ui8LastRead = (m_ui8LastRead & ~ui8Mask) | (_ui8Val & ui8Mask);
			_ui8Speed = ((*ui8Spd) >> ((ui16SpdAddr & 1) << 2)) & 0b1111;
#ifdef SBN_CPU_VERIFY
			m_vReadWriteLog.push_back( { .ui32Address = _ui16Address, .ui8Value = _ui8Val, .bRead = false } );
#endif	// #ifdef SBN_CPU_VERIFY
		}

		/**
		 * Applies a basic memory map where everything is read/write.
		 * 
		 * \return Returns true if the memory map was allocated successfully.
		 **/
		bool										ApplyBasicMap() {
#ifdef SBN_CPU_VERIFY
			m_vReadWriteLog.clear();
#endif	// #ifdef SBN_CPU_VERIFY
			try {
				if ( m_pbpbPages[0].get() ) {
					m_pbpbPages[0].reset();
				}
				m_pbpbPages[0] = std::make_unique<sbn::CBusPage>();
				for ( size_t I = 0; I < 0x10000; ++I ) {
					m_pbpbPages[0]->SetReadFunc( uint16_t( I ), sbn::CBusPageBase::StdRead, nullptr, uint16_t( I ), sbn::CBusPageBase::StdDebugRead );
					m_pbpbPages[0]->SetWriteFunc( uint16_t( I ), sbn::CBusPageBase::StdWrite, nullptr, uint16_t( I ), sbn::CBusPageBase::StdDebugWrite );
				}

				for ( size_t I = 1; I < 256; ++I ) {
					if ( m_pbpbPages[I].get() ) {
						m_pbpbPages[I].reset();
					}
					m_pbpbPages[I] = std::make_unique<sbn::CBusPageFuncRef>( m_pbpbPages[0].get() );
				}
			}
			catch ( ... ) { return false; }
			return true;
		}

#ifdef SBN_CPU_VERIFY
		// == Types.
		struct LSN_READ_WRITE_LOG {
			uint32_t								ui32Address;
			uint8_t									ui8Value;
			bool									bRead;
		};

		/**
		 * Gets the read/write log.
		 *
		 * \return Returns a constant reference to the read/write log.
		 */
		 std::vector<LSN_READ_WRITE_LOG> &			ReadWriteLog() { return m_vReadWriteLog; }
#endif	// #ifdef SBN_CPU_VERIFY

	protected :
		// == Members.
		uint8_t										m_ui8Speeds[0x8000];			/**< The speed table. */
		std::unique_ptr<CBusPageBase>				m_pbpbPages[256];				/**< The pages. */
		uint8_t										m_ui8LastRead = 0;				/**< The open-bus value. */

#ifdef SBN_CPU_VERIFY
		std::vector<LSN_READ_WRITE_LOG>				m_vReadWriteLog;
#endif	// #ifdef SBN_CPU_VERIFY

	};

}	// namespace sbn
