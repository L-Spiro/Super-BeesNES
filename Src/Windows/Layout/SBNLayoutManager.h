#ifdef SBN_USE_WINDOWS

/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The layout manager provides the classes for the windows defined in this project.
 */

#pragma once

#include <Layout/LSWLayoutManager.h>

using namespace lsw;

namespace sbn {

	enum SBN_LAYOUT_TYPES : DWORD {
		SBN_LT_MAIN_WINDOW					= LSW_LT_CUSTOM,
		SBN_LT_SELECT_ROM_DIALOG,
		SBN_LT_INPUT_DIALOG,
		SBN_LT_GLOBAL_INPUT_PAGE,
		SBN_LT_PER_GAME_INPUT_PAGE,
		SBN_LT_CONTROLLER_SETUP_DIALOG,
		SBN_LT_STD_CONTROLLER_PAGE,
	};

	class CLayoutManager : public lsw::CLayoutManager {
	public :
		// == Functions.
		// Creates a class based on its type.
		virtual CWidget *					CreateWidget( const LSW_WIDGET_LAYOUT &_wlLayout, CWidget * _pwParent, bool _bCreateWidget, HMENU _hMenu, uint64_t _ui64Data );
	};

}	// namespace sbn

#endif	// #ifdef SBN_USE_WINDOWS
