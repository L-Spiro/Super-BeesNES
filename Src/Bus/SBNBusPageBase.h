/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The base class for a page of memory, providing the interface for the different types of pages that can be used.
 */


#pragma once

#include "../SBNSuperBeesNES.h"

namespace sbn {

	/**
	 * Class CBusPageBase
	 * \brief The base class for a page of memory.
	 *
	 * Description: The base class for a page of memory, providing the interface for the different types of pages that can be used.
	 */
	class CBusPageBase {
	public :
		// == Types.
		/** An address-reading function. */
		typedef void (SBN_FASTCALL *		PfReadFunc)( void * _pvParm0, uint16_t _ui16Parm1, uint8_t * _pui8Data, uint8_t &_ui8Ret, uint8_t &_ui8OpenMask );

		/** An address-writing function. */
		typedef void (SBN_FASTCALL *		PfWriteFunc)( void * _pvParm0, uint16_t _ui16Parm1, uint8_t * _pui8Data, uint8_t _ui8Val, uint8_t &_ui8OpenMask );

		/** A debug address-reading function. */
		typedef void (SBN_FASTCALL *		PfDebugReadFunc)( void * _pvParm0, uint16_t _ui16Parm1, uint8_t * _pui8Data, uint8_t &_ui8Ret );

		/** A debug address-writing function. */
		typedef void (SBN_FASTCALL *		PfDebugWriteFunc)( void * _pvParm0, uint16_t _ui16Parm1, uint8_t * _pui8Data, uint8_t _ui8Val );

		/** An address accessor. */
		struct SBN_ADDR_ACCESSOR {
			uint16_t						ui16ReaderParm1;				/**< The reader's second parameter. */
			uint16_t						ui16WriterParm1;				/**< The writer's second parameter. */
			uint8_t							pfReader;						/**< The function for reading the assigned address. */
			uint8_t							pvReaderParm0;					/**< The reader's first parameter. */
			uint8_t							pfWriter;						/**< The function for writing the assigned address. */
			uint8_t							pvWriterParm0;					/**< The writer's first parameter. */
			uint8_t							pfDebugReader;					/**< The reader's first parameter. */
			uint8_t							pfDebugWriter;					/**< The writer's first parameter. */
		};


		// == Functions.
		/**
		 * Resets the bus to a known state.
		 */
		virtual void						ResetToKnown() {}

		/**
		 * Performs an "analog" reset, allowing previous data to remain.
		 */
		virtual void						ResetAnalog() {}

		/**
		 * Sets a read function on a given address.
		 * 
		 * \param _ui16Address The address to assign the read function.
		 * \param _pfReadFunc The function to assign to the address.
		 * \param _pvParm0 A data value assigned to the address.
		 * \param _ui16Parm1 A 16-bit parameter assigned to the address.
		 * \param _pfDebugReadFunc The debug function to assign to the address.
		 * \return Returns true if the functions were set.  A return value of false implies a lack of memory or too many unique function pointers being set on a page at once, neither of which is a recoverable-from error.
		 **/
		virtual bool						SetReadFunc( uint16_t _ui16Address, PfReadFunc _pfReadFunc, void * _pvParm0, uint16_t _ui16Parm1, PfDebugReadFunc _pfDebugReadFunc ) { return false; }

		/**
		 * Sets the write function for a given address.
		 *
		 * \param _ui16Address The address to assign the write function.
		 * \param _pfWriteFunc The function to assign to the address.
		 * \param _pvParm0 A data value assigned to the address.
		 * \param _ui16Parm1 A 16-bit parameter assigned to the address.
		 * \param _pfDebugWriteFunc The function to assign to the address.
		 * \return Returns true if the functions were set.  A return value of false implies a lack of memory or too many unique function pointers being set on a page at once, neither of which is a recoverable-from error.
		 */
		virtual bool						SetWriteFunc( uint16_t _ui16Address, PfWriteFunc _pfWriteFunc, void * _pvParm0, uint16_t _ui16Parm1, PfDebugWriteFunc _pfDebugWriteFunc ) { return false; }

		/**
		 * Performs a read of a given address.
		 *
		 * \param _ui16Addr The address to read.
		 * \param _ui8Ret Holds the return value.
		 * \param _ui8Mask The open-bus mask.
		 */
		virtual void						Read( uint16_t _ui16Addr, uint8_t &_ui8Ret, uint8_t &_ui8Mask ) {}

		/**
		 * Performs a write of a given address.
		 *
		 * \param _ui16Addr The address to write.
		 * \param _ui8Val The value to write.
		 * \param _ui8Mask The open-bus mask.
		 */
		virtual void						Write( uint16_t _ui16Addr, uint8_t _ui8Val, uint8_t &_ui8Mask ) {}

		/**
		 * Performs a read of a given address.
		 *
		 * \param _ui16Addr The address to read.
		 * \param _pvData The data from which to read.
		 * \param _ui8Ret Holds the return value.
		 * \param _ui8Mask The open-bus mask.
		 */
		virtual void						Read( uint16_t _ui16Addr, uint8_t * _pvData, uint8_t &_ui8Ret, uint8_t &_ui8Mask ) {}

		/**
		 * Performs a write of a given address.
		 *
		 * \param _ui16Addr The address to write.
		 * \param _pvData The data from which to write.
		 * \param _ui8Val The value to write.
		 * \param _ui8Mask The open-bus mask.
		 */
		virtual void						Write( uint16_t _ui16Addr, uint8_t * _pvData, uint8_t _ui8Val, uint8_t &_ui8Mask ) {}

		/**
		 * Performs a debug read of a given address.
		 *
		 * \param _ui16Addr The address to read.
		 * \param _ui8Ret Holds the return value.
		 */
		virtual void						DebugRead( uint16_t _ui16Addr, uint8_t &_ui8Ret ) {}

		/**
		 * Performs a debug write of a given address.
		 *
		 * \param _ui16Addr The address to write.
		 * \param _ui8Val The value to write.
		 */
		virtual void						DebugWrite( uint16_t _ui16Addr, uint8_t _ui8Val ) {}

		/**
		 * Performs a debug read of a given address.
		 *
		 * \param _ui16Addr The address to read.
		 * \param _pvData The data from which to read.
		 * \param _ui8Ret Holds the return value.
		 */
		virtual void						DebugRead( uint16_t _ui16Addr, uint8_t * _pvData, uint8_t &_ui8Ret ) {}

		/**
		 * Performs a debug write of a given address.
		 *
		 * \param _ui16Addr The address to write.
		 * \param _pvData The data from which to write.
		 * \param _ui8Val The value to write.
		 */
		virtual void						DebugWrite( uint16_t _ui16Addr, uint8_t * _pvData, uint8_t _ui8Val ) {}

		/**
		 * A standard read function.
		 *
		 * \param _pvParm0 A data value assigned to this address.
		 * \param _ui16Parm1 A 16-bit parameter assigned to this address.  Typically this will be the address to read from _pui8Data.  It is not constant because sometimes reads do modify status registers etc.
		 * \param _pui8Data The buffer from which to read.
		 * \param _ui8Ret The read value.
		 */
		static void SBN_FASTCALL			StdRead( void * /*_pvParm0*/, uint16_t _ui16Parm1, uint8_t * _pui8Data, uint8_t &_ui8Ret, uint8_t &/*_ui8OpenMask*/ ) {
			_ui8Ret = _pui8Data[_ui16Parm1];
		}

		/**
		 * A standard write function.
		 *
		 * \param _pvParm0 A data value assigned to this address.
		 * \param _ui16Parm1 A 16-bit parameter assigned to this address.  Typically this will be the address to write to _pui8Data.
		 * \param _pui8Data The buffer to which to write.
		 * \param _ui8Val The value to write.
		 */
		static void SBN_FASTCALL			StdWrite( void * /*_pvParm0*/, uint16_t _ui16Parm1, uint8_t * _pui8Data, uint8_t _ui8Val, uint8_t &/*_ui8OpenMask*/ ) {
			_pui8Data[_ui16Parm1] = _ui8Val;
		}

		/**
		 * A function usable for addresses that can't be read.
		 *
		 * \param _pvParm0 A data value assigned to this address.
		 * \param _ui16Parm1 A 16-bit parameter assigned to this address.  Typically this will be the address to read from _pui8Data.  It is not constant because sometimes reads do modify status registers etc.
		 * \param _pui8Data The buffer from which to read.
		 * \param _ui8Ret The read value.
		 */
		static void SBN_FASTCALL			NoRead( void * /*_pvParm0*/, uint16_t /*_ui16Parm1*/, uint8_t * /*_pui8Data*/, uint8_t &/*_ui8Ret*/, uint8_t &/*_ui8OpenMask*/ ) {
		}

		/**
		 * A function usable for addresses that can't be written.
		 *
		 * \param _pvParm0 A data value assigned to this address.
		 * \param _ui16Parm1 A 16-bit parameter assigned to this address.  Typically this will be the address to write to _pui8Data.
		 * \param _pui8Data The buffer to which to write.
		 * \param _ui8Val The value to write.
		 */
		static void SBN_FASTCALL			NoWrite( void * /*_pvParm0*/, uint16_t /*_ui16Parm1*/, uint8_t * /*_pui8Data*/, uint8_t /*_ui8Val*/, uint8_t &/*_ui8OpenMask*/ ) {
		}

		/**
		 * A standard debug read function.
		 *
		 * \param _pvParm0 A data value assigned to this address.
		 * \param _ui16Parm1 A 16-bit parameter assigned to this address.  Typically this will be the address to read from _pui8Data.  It is not constant because sometimes reads do modify status registers etc.
		 * \param _pui8Data The buffer from which to read.
		 * \param _ui8Ret The read value.
		 */
		static void SBN_FASTCALL			StdDebugRead( void * /*_pvParm0*/, uint16_t _ui16Parm1, uint8_t * _pui8Data, uint8_t &_ui8Ret ) {
			_ui8Ret = _pui8Data[_ui16Parm1];
		}

		/**
		 * A standard debug write function.
		 *
		 * \param _pvParm0 A data value assigned to this address.
		 * \param _ui16Parm1 A 16-bit parameter assigned to this address.  Typically this will be the address to write to _pui8Data.
		 * \param _pui8Data The buffer to which to write.
		 * \param _ui8Val The value to write.
		 */
		static void SBN_FASTCALL			StdDebugWrite( void * /*_pvParm0*/, uint16_t _ui16Parm1, uint8_t * _pui8Data, uint8_t _ui8Val ) {
			_pui8Data[_ui16Parm1] = _ui8Val;
		}
	};

}	// namespace sbn
