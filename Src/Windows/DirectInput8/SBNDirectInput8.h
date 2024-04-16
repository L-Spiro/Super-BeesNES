#ifdef SBN_USE_WINDOWS

/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A wrapper around DirectInput8.
 */

#pragma once

//#include <dinput.h>

namespace sbn {

	/**
	 * Class CDirectInput8
	 * \brief A wrapper around DirectInput8.
	 *
	 * Description: A wrapper around DirectInput8.
	 */
	class CDirectInput8 {
	public :
		CDirectInput8();
		~CDirectInput8();

	};

}	// namespace sbn

#endif	// #ifdef SBN_USE_WINDOWS
