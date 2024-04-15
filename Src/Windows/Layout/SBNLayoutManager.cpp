#ifdef SBN_USE_WINDOWS

/**
 * Copyright L. Spiro 2022
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The layout manager provides the classes for the windows defined in this project.
 */

#include "SBNLayoutManager.h"
#include "../Input/SBNControllerSetupWindow.h"
#include "../Input/SBNInputConfigurePage.h"
#include "../Input/SBNInputWindow.h"
#include "../Input/SBNStdControllerPage.h"
#include "../MainWindow/SBNMainWindow.h"
#include "../SelectRom/SBNSelectRomDialog.h"


namespace sbn {

	// == Functions.
	// Creates a class based on its type.
	CWidget * CLayoutManager::CreateWidget( const LSW_WIDGET_LAYOUT &_wlLayout, CWidget * _pwParent, bool _bCreateWidget, HMENU _hMenu, uint64_t _ui64Data ) {
		switch ( _wlLayout.ltType ) {
			case SBN_LT_MAIN_WINDOW : {
				return new CMainWindow( _wlLayout, _pwParent,  _bCreateWidget, _hMenu, _ui64Data );
			}
			case SBN_LT_SELECT_ROM_DIALOG : {
				return new CSelectRomDialog( _wlLayout, _pwParent,  _bCreateWidget, _hMenu, _ui64Data );
			}
			case SBN_LT_INPUT_DIALOG : {
				return new CInputWindow( _wlLayout, _pwParent,  _bCreateWidget, _hMenu, _ui64Data );
			}
			case SBN_LT_GLOBAL_INPUT_PAGE : {
				return new CInputConfigurePage<true>( _wlLayout, _pwParent,  _bCreateWidget, _hMenu, _ui64Data );
			}
			case SBN_LT_PER_GAME_INPUT_PAGE : {
				return new CInputConfigurePage<false>( _wlLayout, _pwParent,  _bCreateWidget, _hMenu, _ui64Data );
			}
			case SBN_LT_CONTROLLER_SETUP_DIALOG : {
				return new CControllerSetupWindow( _wlLayout, _pwParent,  _bCreateWidget, _hMenu, _ui64Data );
			}
			case SBN_LT_STD_CONTROLLER_PAGE : {
				return new CStdControllerPage( _wlLayout, _pwParent,  _bCreateWidget, _hMenu, _ui64Data );
			}
		}
		return lsw::CLayoutManager::CreateWidget( _wlLayout, _pwParent, _bCreateWidget, _hMenu, _ui64Data );
	}

}	// namespace sbn

#endif	// #ifdef SBN_USE_WINDOWS
