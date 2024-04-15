#ifdef SBN_USE_WINDOWS

/**
 * Copyright L. Spiro 2022
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The dialog for selecting a ROM file.
 */

#pragma once

#include <MainWindow/LSWMainWindow.h>

using namespace lsw;

namespace sbn {

	class CSelectRomDialog : public lsw::CMainWindow {
	public :
		CSelectRomDialog( const LSW_WIDGET_LAYOUT &_wlLayout, CWidget * _pwParent, bool _bCreateWidget = true, HMENU _hMenu = NULL, uint64_t _ui64Data = 0 );


		// == Functions.
		// WM_INITDIALOG.
		virtual LSW_HANDLED					InitDialog();

		// WM_COMMAND from control.
		virtual LSW_HANDLED					Command( WORD _wCtrlCode, WORD _wId, CWidget * _pwSrc );

		// WM_CLOSE.
		virtual LSW_HANDLED					Close();

		// WM_GETMINMAXINFO.
		virtual LSW_HANDLED					GetMinMaxInfo( MINMAXINFO * _pmmiInfo );


		// == Members.
	protected :
		const std::vector<std::u16string> *	m_pvFiles;
	};

}	// namespace sbn

#endif	// #ifdef SBN_USE_WINDOWS
