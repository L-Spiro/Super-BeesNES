#ifdef SBN_USE_WINDOWS

/**
 * Copyright L. Spiro 2023
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The input-configuration window layout.
 */

#include "SBNControllerSetupWindowLayout.h"
#include "../../Localization/SBNLocalization.h"
#include "../Input/SBNControllerSetupWindow.h"
#include "../Layout/SBNLayoutMacros.h"
#include "../Layout/SBNLayoutManager.h"
#include "SBNStdControllerPageLayout.h"



namespace sbn {

#define SBN_INPUT_GROUP_W							(SBN_STD_CONT_W)
#define SBN_INPUT_W									(SBN_INPUT_GROUP_W)
#define SBN_INPUT_H									(SBN_STD_CONT_H + SBN_DEF_BUTTON_HEIGHT + SBN_TOP_JUST * 2)

	// == Members.
	/** The layout for the main window. */
	LSW_WIDGET_LAYOUT CControllerSetupWindowLayout::m_wlInputWindow[] = {
		{
			SBN_LT_CONTROLLER_SETUP_DIALOG,			// ltType
			SBN_CSW_MAINWINDOW,						// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			0,										// iLeft
			0,										// iTop
			SBN_INPUT_W,							// dwWidth
			SBN_INPUT_H,							// dwHeight
			WS_CAPTION | WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_SYSMENU | DS_3DLOOK | DS_FIXEDSYS | DS_MODALFRAME | DS_CENTER,					// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT,												// dwStyleEx
			SBN_LSTR( SBN_INPUT_DIALOG ),			// pwcText
			0,										// sTextLen
			SBN_CSW_NONE,							// dwParentId
		},

		{
			LSW_LT_TAB,								// ltType
			SBN_CSW_TAB,							// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			0,										// iLeft
			0,										// iTop
			SBN_INPUT_GROUP_W,						// dwWidth
			SBN_STD_CONT_H,							// dwHeight
			WS_CHILDWINDOW | WS_VISIBLE | WS_TABSTOP | TCS_HOTTRACK,																					// dwStyle
			0,										// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_CSW_MAINWINDOW,						// dwParentId
		},


		{
			LSW_LT_BUTTON,							// ltType
			SBN_CSW_OK,								// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			TRUE,									// bActive
			SBN_LEFT_JUST,							// iLeft
			SBN_INPUT_H - SBN_DEF_BUTTON_HEIGHT - SBN_TOP_JUST,		// iTop
			SBN_DEF_BUTTON_WIDTH,					// dwWidth
			SBN_DEF_BUTTON_HEIGHT,					// dwHeight
			SBN_DEFBUTTONSTYLE,						// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,																								// dwStyleEx
			SBN_LSTR( SBN_OK ),						// pwcText
			0,										// sTextLen
			SBN_CSW_MAINWINDOW,						// dwParentId
		},
		{
			LSW_LT_BUTTON,							// ltType
			SBN_CSW_CANCEL,							// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_INPUT_W - SBN_DEF_BUTTON_WIDTH * 1 - SBN_LEFT_JUST,	// iLeft
			SBN_INPUT_H - SBN_DEF_BUTTON_HEIGHT - SBN_TOP_JUST,		// iTop
			SBN_DEF_BUTTON_WIDTH,					// dwWidth
			SBN_DEF_BUTTON_HEIGHT,					// dwHeight
			SBN_BUTTONSTYLE,						// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,																								// dwStyleEx
			SBN_LSTR( SBN_CANCEL ),					// pwcText
			0,										// sTextLen
			SBN_CSW_MAINWINDOW,						// dwParentId
		},
	};


#undef SBN_INPUT_H
#undef SBN_INPUT_W
#undef SBN_INPUT_GROUP_W


	// == Functions.
	/**
	 * Creates the input-configuration window.
	 *
	 * \param _pwParent The parent of the dialog.
	 * \param _ioOptions A reference to the options object.
	 * \param _pmwMainWindow A pointer to the main window.
	 * \param _stPlayerIdx The player index.
	 * \return Returns TRUE if the dialog was created successfully.
	 */
	BOOL CControllerSetupWindowLayout::CreateInputDialog( CWidget * _pwParent, SBN_INPUT_OPTIONS &_ioOptions, lsn::CMainWindow * _pmwMainWindow, size_t _stPlayerIdx ) {
		lsn::CLayoutManager * plmLayout = static_cast<lsn::CLayoutManager *>(lsw::CBase::LayoutManager());
		CControllerSetupWindow::SBN_CONTROLLER_SETUP_DATA csdData = {
			.pioOptions = &_ioOptions,
			.pmwMainWindow = _pmwMainWindow,
			.stIdx = _stPlayerIdx
		};
		INT_PTR ipProc = plmLayout->DialogBoxX( m_wlInputWindow, SBN_ELEMENTS( m_wlInputWindow ), _pwParent, reinterpret_cast<uint64_t>(&csdData) );
		if ( ipProc != 0 ) {
			// Success.  Do stuff.
			return TRUE;
		}
		return FALSE;
	}

	/**
	 * Creates the tab pages.
	 *
	 * \param _pwParent The parent widget.
	 * \param _pwlLayout The page layout.
	 * \param _sTotal The number of items to which _pwlLayout points.
	 * \param _ioOptions A reference to the options object.
	 * \return Returns the created page.
	 */
	/*CWidget * CControllerSetupWindowLayout::CreatePage( CWidget * _pwParent, const LSW_WIDGET_LAYOUT * _pwlLayout, size_t _sTotal, SBN_INPUT_OPTIONS &_ioOptions ) {
		lsn::CLayoutManager * plmLayout = static_cast<lsn::CLayoutManager *>(lsw::CBase::LayoutManager());
		CWidget * pwWidget = plmLayout->CreateDialogX( _pwlLayout, _sTotal, _pwParent, reinterpret_cast<uint64_t>(&_ioOptions) );
		if ( pwWidget ) {
			// Success.  Do stuff.
		}
		return pwWidget;
	}*/

}	// namespace sbn

#endif	// #ifdef SBN_USE_WINDOWS
