/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The glue between each component of the system. The bus allows components to talk to
 *	each other and keeps track of floating values for the emulation of an open bus.
 * All memory accesses that would go across a real SNES bus go across this. This means components
 *	with internal RAM can still manage their own RAM internally however they please.
 *
 * We have to make this as fast as possible but there are a lot of quirks to accessing any given
 *	address, plus we want it to be extensible, able to handle the CPU bus and the PPU bus all in
 *	one class.  We can't afford a bunch of virtual function calls that could allow plug-&-play
 *	behavior where each component gets to customize its RAM access, and we also want to avoid too
 *	many branches, modulo operations (mirroring), and other heavy logic required to hardcode the
 *	whole system into a tangled mess.
 * We achieve per-address programmability with minimal branching and outer logic by storing an
 *	array of pointers to functions that each handle the access logic for that address.  One pointer
 *	per address.  The outer logic is branchless, simply calling the function associated with that
 *	address.  The functions themselves already know how to access the address to which they are
 *	assigned and can perform the minimal amount of processing necessary to access any specific
 *	address.  This means there will not be several if/else statements to check address ranges each
 *	time an example address is read or written plus modulo operations to handle mirroring, there
 *	will only be the minimal access code related to any specific address, whether that be mirroring
 *	or any other special-case operation for a given address.  This solves the performance issue
 *	along with the hard-to-follow logic issue.  During setup, the hardware components get to assign
 *	these accessors to addresses as they please, solving the extensibility/flexibility issues that
 *	would have been served by virtual functions.  Ultiately, memory access can be made into an
 *	entirely branchless system.
 *
 * An outward-facing design decision is to have the entire block of system RAM contiguous in memory
 *	here to make it easier to parse by external readers (IE an external debugger).
 *
 * Since the memory is contiguous and directly part of this class, allocating this on the stack
 *	may cause a stack overflow.
 */


#pragma once

#include "../SBNSuperBeesNES.h"
#include "SBNBusPageBase.h"

#ifdef SBN_CPU_VERIFY
#include <vector>
#endif	// #ifdef SBN_CPU_VERIFY

namespace sbn {

	/**
	 * Class CBusPage
	 * \brief The glue between each component of the system.
	 *
	 * Description: The glue between each component of the system. The bus allows components to talk to
	 *	each other and keeps track of floating values for the emulation of an "open" bus.
	 * All memory accesses that would go across a real SNES bus go across this. This means components
	 *	with internal RAM can still manage their own RAM internally however they please.
	 *
	 * We have to make this as fast as possible but there are a lot of quirks to accessing any given
	 *	address, plus we want it to be extensible, able to handle the CPU bus and the PPU bus all in
	 *	one class.  We can't afford a bunch of virtual function calls that could allow plug-&-play
	 *	behavior where each component gets to customize its RAM access, and we also want to avoid too
	 *	many branches, modulo operations (mirroring), and other heavy logic required to hardcode the
	 *	whole system into a tangled mess.
	 * We achieve per-address programmability with minimal branching and outer logic by storing an
	 *	array of pointers to functions that each handle the access logic for that address.  One pointer
	 *	per address.  The outer logic is branchless, simply calling the function associated with that
	 *	address.  The functions themselves already know how to access the address to which they are
	 *	assigned and can perform the minimal amount of processing necessary to access any specific
	 *	address.  This means there will not be several if/else statements to check address ranges each
	 *	time an example address is read or written plus modulo operations to handle mirroring, there
	 *	will only be the minimal access code related to any specific address, whether that be mirroring
	 *	or any other special-case operation for a given address.  This solves the performance issue
	 *	along with the hard-to-follow logic issue.  During setup, the hardware components get to assign
	 *	these accessors to addresses as they please, solving the extensibility/flexibility issues that
	 *	would have been served by virtual functions.  Ultiately, memory access can be made into an
	 *	entirely branchless system.
	 *
	 * An outward-facing design decision is to have the entire block of system RAM contiguous in memory
	 *	here to make it easier to parse by external readers (IE an external debugger).
	 *
	 * Since the memory is contiguous and directly part of this class, allocating this on the stack
	 *	may cause a stack overflow.
	 */
	class CBusPage : public sbn::CBusPageBase {
	private :
		// == Types.
		typedef sbn::CBusPageBase			Parent;
	public :
		// == Various constructors.
		CBusPage() :
			m_prfReadFuncs( nullptr ),
			m_pwfWriteFuncs( nullptr ),
			m_prfDebugReadFuncs( nullptr ),
			m_pwfDebugWriteFuncs( nullptr ),
			m_pvvReaderPtr( nullptr ),
			m_pvvWriterPtr( nullptr ) {
		}
		~CBusPage() {
			ResetToKnown();
		}


		// == Functions.
		/**
		 * Gets the size of the bus in bytes.
		 *
		 * \return Returns the size of the bus in bytes.
		 */
		inline constexpr uint32_t			Size() const { return 0x10000; }

		/**
		 * Resets the bus to a known state.
		 */
		virtual void						ResetToKnown() {
			ResetAnalog();
			std::memset( m_ui8Memory, 0, sizeof( m_ui8Memory ) );
			std::memset( m_aaAddresses, 0, sizeof( m_aaAddresses ) );
			m_vReadFuncs = std::vector<Parent::PfReadFunc>();
			m_prfReadFuncs = nullptr;
			m_vWriteFuncs = std::vector<Parent::PfWriteFunc>();
			m_pwfWriteFuncs = nullptr;
			m_vDebugReadFuncs = std::vector<Parent::PfDebugReadFunc>();
			m_prfDebugReadFuncs = nullptr;
			m_vDebugWriteFuncs = std::vector<Parent::PfDebugWriteFunc>();
			m_pwfDebugWriteFuncs = nullptr;

			m_vReaderPtr = std::vector<void *>();
			m_pvvReaderPtr = nullptr;
			m_vWriterPtr = std::vector<void *>();
			m_pvvWriterPtr = nullptr;
		}

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
		virtual bool						SetReadFunc( uint16_t _ui16Address, Parent::PfReadFunc _pfReadFunc, void * _pvParm0, uint16_t _ui16Parm1, Parent::PfDebugReadFunc _pfDebugReadFunc ) {
			m_aaAddresses[_ui16Address].ui16ReaderParm1 = _ui16Parm1;
			size_t sIdx = FindReadFunc( _pfReadFunc );
			if ( sIdx >= m_vReadFuncs.size() || sIdx >= 256 ) { return false; }
			m_aaAddresses[_ui16Address].pfReader = uint8_t( sIdx );

			sIdx = FindDebugReadFunc( _pfDebugReadFunc );
			if ( sIdx >= m_vDebugReadFuncs.size() || sIdx >= 256 ) { return false; }
			m_aaAddresses[_ui16Address].pfDebugReader = uint8_t( sIdx );

			sIdx = FindReadPtr( _pvParm0 );
			if ( sIdx >= m_vReaderPtr.size() || sIdx >= 256 ) { return false; }
			m_aaAddresses[_ui16Address].pvReaderParm0 = uint8_t( sIdx );
			
			return true;
		}

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
		virtual bool						SetWriteFunc( uint16_t _ui16Address, Parent::PfWriteFunc _pfWriteFunc, void * _pvParm0, uint16_t _ui16Parm1, Parent::PfDebugWriteFunc _pfDebugWriteFunc ) {
			m_aaAddresses[_ui16Address].ui16WriterParm1 = _ui16Parm1;
			size_t sIdx = FindWriteFunc( _pfWriteFunc );
			if ( sIdx >= m_vWriteFuncs.size() || sIdx >= 256 ) { return false; }
			m_aaAddresses[_ui16Address].pfWriter = uint8_t( sIdx );

			sIdx = FindDebugWriteFunc( _pfDebugWriteFunc );
			if ( sIdx >= m_vDebugWriteFuncs.size() || sIdx >= 256 ) { return false; }
			m_aaAddresses[_ui16Address].pfDebugWriter = uint8_t( sIdx );

			sIdx = FindWritePtr( _pvParm0 );
			if ( sIdx >= m_vWriterPtr.size() || sIdx >= 256 ) { return false; }
			m_aaAddresses[_ui16Address].pvWriterParm0 = uint8_t( sIdx );
			
			return true;
		}

		/**
		 * Performs a read of a given address.
		 *
		 * \param _ui16Addr The address to read.
		 * \param _ui8Ret Holds the return value.
		 * \param _ui8Mask The open-bus mask.
		 */
		virtual void						Read( uint16_t _ui16Addr, uint8_t &_ui8Ret, uint8_t &_ui8Mask ) {
			const Parent::SBN_ADDR_ACCESSOR & aaThis = m_aaAddresses[_ui16Addr];
			m_prfReadFuncs[aaThis.pfReader]( m_pvvReaderPtr[aaThis.pvReaderParm0], aaThis.ui16ReaderParm1, m_ui8Memory, _ui8Ret, _ui8Mask );
		}

		/**
		 * Performs a write of a given address.
		 *
		 * \param _ui16Addr The address to write.
		 * \param _ui8Val The value to write.
		 * \param _ui8Mask The open-bus mask.
		 */
		virtual void						Write( uint16_t _ui16Addr, uint8_t _ui8Val, uint8_t &_ui8Mask ) {
			const Parent::SBN_ADDR_ACCESSOR & aaThis = m_aaAddresses[_ui16Addr];
			m_pwfWriteFuncs[aaThis.pfWriter]( m_pvvWriterPtr[aaThis.pvWriterParm0], aaThis.ui16WriterParm1, m_ui8Memory, _ui8Val, _ui8Mask );
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
			const Parent::SBN_ADDR_ACCESSOR & aaThis = m_aaAddresses[_ui16Addr];
			m_prfReadFuncs[aaThis.pfReader]( m_pvvReaderPtr[aaThis.pvReaderParm0], aaThis.ui16ReaderParm1, _pvData, _ui8Ret, _ui8Mask );
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
			const Parent::SBN_ADDR_ACCESSOR & aaThis = m_aaAddresses[_ui16Addr];
			m_pwfWriteFuncs[aaThis.pfWriter]( m_pvvWriterPtr[aaThis.pvWriterParm0], aaThis.ui16WriterParm1, _pvData, _ui8Val, _ui8Mask );
		}


	protected :
		// == Members.
		/** The read functions. */
		std::vector<Parent::PfReadFunc>		m_vReadFuncs;
		/** Safe access to the read functions. */
		Parent::PfReadFunc *				m_prfReadFuncs;
		/** The write functions. */
		std::vector<Parent::PfWriteFunc>	m_vWriteFuncs;
		/** Safe access to the write functions. */
		Parent::PfWriteFunc *				m_pwfWriteFuncs;

		/** The debug read functions. */
		std::vector<Parent::PfDebugReadFunc>m_vDebugReadFuncs;
		/** Safe access to the debug read functions. */
		Parent::PfDebugReadFunc *			m_prfDebugReadFuncs;
		/** The debug write functions. */
		std::vector<Parent::PfDebugWriteFunc>
											m_vDebugWriteFuncs;
		/** Safe access to the debug write functions. */
		Parent::PfDebugWriteFunc *			m_pwfDebugWriteFuncs;

		/** The reader void *. */
		std::vector<void *>					m_vReaderPtr;
		/** Safe access to the read void *. */
		void **								m_pvvReaderPtr;
		/** The writer void *. */
		std::vector<void *>					m_vWriterPtr;
		/** Safe access to the writer void *. */
		void **								m_pvvWriterPtr;

		/** The accessors. */
		Parent::SBN_ADDR_ACCESSOR			m_aaAddresses[0x10000];
		/** The memory. */
		uint8_t								m_ui8Memory[0x10000];


		// == Functions.
		/**
		 * Returns the index of a given read function pointer.
		 *
		 * \param _pfReadFunc The read function to find inside or to append to the end of m_vReadFuncs.
		 * \return Returns the index of the existing function or the index where the new function was added.
		 **/
		size_t								FindReadFunc( Parent::PfReadFunc _pfReadFunc ) {
			for ( size_t I = 0; I < m_vReadFuncs.size(); ++I ) {
				if ( m_vReadFuncs[I] == _pfReadFunc ) { return I; }
			}
			try {
				m_vReadFuncs.push_back( _pfReadFunc );
				m_prfReadFuncs = m_vReadFuncs.data();
				return m_vReadFuncs.size() - 1;
			}
			catch ( ... ) {
				return m_vReadFuncs.size();
			}
		}

		/**
		 * Returns the index of a given write function pointer.
		 *
		 * \param _pfWriteFunc The write function to find inside or to append to the end of m_vWriteFuncs.
		 * \return Returns the index of the existing function or the index where the new function was added.
		 **/
		size_t								FindWriteFunc( Parent::PfWriteFunc _pfWriteFunc ) {
			for ( size_t I = 0; I < m_vWriteFuncs.size(); ++I ) {
				if ( m_vWriteFuncs[I] == _pfWriteFunc ) { return I; }
			}
			try {
				m_vWriteFuncs.push_back( _pfWriteFunc );
				m_pwfWriteFuncs = m_vWriteFuncs.data();
				return m_vWriteFuncs.size() - 1;
			}
			catch ( ... ) {
				return m_vWriteFuncs.size();
			}
		}

		/**
		 * Returns the index of a given debug read function pointer.
		 *
		 * \param _pfReadFunc The debug read function to find inside or to append to the end of m_vDebugReadFuncs.
		 * \return Returns the index of the existing function or the index where the new function was added.
		 **/
		size_t								FindDebugReadFunc( Parent::PfDebugReadFunc _pfReadFunc ) {
			for ( size_t I = 0; I < m_vDebugReadFuncs.size(); ++I ) {
				if ( m_vDebugReadFuncs[I] == _pfReadFunc ) { return I; }
			}
			try {
				m_vDebugReadFuncs.push_back( _pfReadFunc );
				m_prfDebugReadFuncs = m_vDebugReadFuncs.data();
				return m_vDebugReadFuncs.size() - 1;
			}
			catch ( ... ) {
				return m_vDebugReadFuncs.size();
			}
		}

		/**
		 * Returns the index of a given debug write function pointer.
		 *
		 * \param _pfWriteFunc The debug write function to find inside or to append to the end of m_vDebugWriteFuncs.
		 * \return Returns the index of the existing function or the index where the new function was added.
		 **/
		size_t								FindDebugWriteFunc( Parent::PfDebugWriteFunc _pfWriteFunc ) {
			for ( size_t I = 0; I < m_vDebugWriteFuncs.size(); ++I ) {
				if ( m_vDebugWriteFuncs[I] == _pfWriteFunc ) { return I; }
			}
			try {
				m_vDebugWriteFuncs.push_back( _pfWriteFunc );
				m_pwfDebugWriteFuncs = m_vDebugWriteFuncs.data();
				return m_vDebugWriteFuncs.size() - 1;
			}
			catch ( ... ) {
				return m_vDebugWriteFuncs.size();
			}
		}

		/**
		 * Returns the index of a given read pointer.
		 *
		 * \param _pfReadFunc The read pointer to find inside or to append to the end of m_vReaderPtr.
		 * \return Returns the index of the existing pointer or the index where the new pointer was added.
		 **/
		size_t								FindReadPtr( void * _pvParm0 ) {
			for ( size_t I = 0; I < m_vReaderPtr.size(); ++I ) {
				if ( m_vReaderPtr[I] == _pvParm0 ) { return I; }
			}
			try {
				m_vReaderPtr.push_back( _pvParm0 );
				m_pvvReaderPtr = m_vReaderPtr.data();
				return m_vReaderPtr.size() - 1;
			}
			catch ( ... ) {
				return m_vReaderPtr.size();
			}
		}

		/**
		 * Returns the index of a given write pointer.
		 *
		 * \param _pfWriteFunc The write pointer to find inside or to append to the end of m_vWriterPtr.
		 * \return Returns the index of the existing pointer or the index where the new pointer was added.
		 **/
		size_t								FindWritePtr( void * _pvParm0 ) {
			for ( size_t I = 0; I < m_vWriterPtr.size(); ++I ) {
				if ( m_vWriterPtr[I] == _pvParm0 ) { return I; }
			}
			try {
				m_vWriterPtr.push_back( _pvParm0 );
				m_pvvWriterPtr = m_vWriterPtr.data();
				return m_vWriterPtr.size() - 1;
			}
			catch ( ... ) {
				return m_vWriterPtr.size();
			}
		}


	
	};

}	// namespace sbn
