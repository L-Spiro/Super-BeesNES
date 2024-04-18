/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: Provides additional memory accessed using the same functions as another page of memory.  Performs only reads.
 */


#pragma once

#include "../SBNSuperBeesNES.h"
#include "SBNBusPageBase.h"

namespace sbn {

	/**
	 * Class CBusPageReadOnlyFuncRef
	 * \brief Provides additional memory accessed using the same functions as another page of memory.
	 *
	 * Description: Provides additional memory accessed using the same functions as another page of memory.  Performs only reads.
	 */
	class CBusPageReadOnlyFuncRef : public sbn::CBusPageBase {
	private :
		// == Types.
		typedef sbn::CBusPageBase			Parent;
	public :
		// == Various constructors.
		CBusPageReadOnlyFuncRef( CBusPageBase * _pbpbPage ) :
			m_pbpbTarget( _pbpbPage ) {
		}
		~CBusPageReadOnlyFuncRef() {
			ResetToKnown();
		}


		// == Functions.
		/**
		 * Resets the bus to a known state.
		 */
		virtual void						ResetToKnown() {
			ResetAnalog();
			std::memset( m_ui8Memory, 0, sizeof( m_ui8Memory ) );
		}

		/**
		 * Performs a read of a given address.
		 *
		 * \param _ui16Addr The address to read.
		 * \param _ui8Ret Holds the return value.
		 * \param _ui8Mask The open-bus mask.
		 */
		virtual void						Read( uint16_t _ui16Addr, uint8_t &_ui8Ret, uint8_t &_ui8Mask ) {
			m_pbpbTarget->Read( _ui16Addr, m_ui8Memory, _ui8Ret, _ui8Mask );
		}

		/**
		 * Performs a write of a given address.
		 *
		 * \param _ui16Addr The address to write.
		 * \param _ui8Val The value to write.
		 * \param _ui8Mask The open-bus mask.
		 */
		virtual void						Write( uint16_t _ui16Addr, uint8_t _ui8Val, uint8_t &_ui8Mask ) {
		}

		/**
		 * Performs a read of a given address.
		 *
		 * \param _ui16Addr The address to read.
		 * \param _pvData The data from which to read.
		 * \param _ui8Ret Holds the return value.
		 * \param _ui8Mask The open-bus mask.
		 */
		virtual void						Read( uint16_t _ui16Addr, uint8_t * _pvData, uint8_t &_ui8Ret, uint8_t &_ui8Mask ) {
			m_pbpbTarget->Read( _ui16Addr, _pvData, _ui8Ret, _ui8Mask );
		}

		/**
		 * Performs a write of a given address.
		 *
		 * \param _ui16Addr The address to write.
		 * \param _pvData The data from which to write.
		 * \param _ui8Val The value to write.
		 * \param _ui8Mask The open-bus mask.
		 */
		virtual void						Write( uint16_t _ui16Addr, uint8_t * _pvData, uint8_t _ui8Val, uint8_t &_ui8Mask ) {
		}

		/**
		 * Performs a debug read of a given address.
		 *
		 * \param _ui16Addr The address to read.
		 * \param _ui8Ret Holds the return value.
		 */
		virtual void						DebugRead( uint16_t _ui16Addr, uint8_t &_ui8Ret ) {
			m_pbpbTarget->DebugRead( _ui16Addr, m_ui8Memory, _ui8Ret );
		}

		/**
		 * Performs a debug write of a given address.
		 *
		 * \param _ui16Addr The address to write.
		 * \param _ui8Val The value to write.
		 */
		virtual void						DebugWrite( uint16_t _ui16Addr, uint8_t _ui8Val ) {
		}

		/**
		 * Performs a debug read of a given address.
		 *
		 * \param _ui16Addr The address to read.
		 * \param _pvData The data from which to read.
		 * \param _ui8Ret Holds the return value.
		 */
		virtual void						DebugRead( uint16_t _ui16Addr, uint8_t * _pvData, uint8_t &_ui8Ret ) {
			m_pbpbTarget->DebugRead( _ui16Addr, _pvData, _ui8Ret );
		}

		/**
		 * Performs a debug write of a given address.
		 *
		 * \param _ui16Addr The address to write.
		 * \param _pvData The data from which to write.
		 * \param _ui8Val The value to write.
		 */
		virtual void						DebugWrite( uint16_t _ui16Addr, uint8_t * _pvData, uint8_t _ui8Val ) {
		}

	protected :
		// == Members.
		/** The page we reference. */
		CBusPageBase *						m_pbpbTarget;
		/** The memory. */
		uint8_t								m_ui8Memory[0x10000];
	};

}	// namespace sbn
