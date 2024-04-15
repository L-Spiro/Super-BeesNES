#ifdef SBN_USE_WINDOWS

/**
 * Copyright L. Spiro 2022
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The main window layout.
 */

#include "SBNMainWindowLayout.h"
#include "../Layout/SBNLayoutMacros.h"
#include "../Layout/SBNLayoutManager.h"
#include "../../Localization/SBNLocalization.h"
#include "../../Utilities/SBNUtilities.h"
#include <Base/LSWWndClassEx.h>


namespace sbn {

	// == Members.
	/** The layout for the main window. */
	LSW_WIDGET_LAYOUT CMainWindowLayout::m_wlMainWindow[] = {
		{
			SBN_LT_MAIN_WINDOW,						// ltType
			SBN_MWI_MAINWINDOW,						// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			64,										// iLeft
			64,										// iTop
			SBN_MAIN_WINDOW_W,						// dwWidth
			SBN_MAIN_WINDOW_H,						// dwHeight
			WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS,							// dwStyle
			0,										// dwStyleEx
			L"BeesNES",								// pwcText
			0,										// sTextLen
			SBN_MWI_NONE,							// dwParentId
		},
		/*{
			LSW_LT_STATUSBAR,						// ltType
			SBN_MWI_STATUSBAR,						// wId
			STATUSCLASSNAMEW,						// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			0,										// iLeft
			0,										// iTop
			0,										// dwWidth
			0,										// dwHeight
			WS_VISIBLE | WS_CHILD | SBARS_SIZEGRIP,	// dwStyle
			0,										// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_MWI_MAINWINDOW,						// dwParentId

			nullptr, 0,								// pcLeftSizeExp
			nullptr, 0,								// pcRightSizeExp
			nullptr, 0,								// pcTopSizeExp
			nullptr, 0,								// pcBottomSizeExp
			nullptr, 0,								// pcWidthSizeExp
			nullptr, 0,								// pcHeightSizeExp
		},*/
		/*{
			LSW_LT_REBAR,							// ltType
			SBN_MWI_REBAR0,							// wId
			REBARCLASSNAMEW,						// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			0,										// iLeft
			0,										// iTop
			m_wlMainWindow[0].dwWidth,				// dwWidth
			150,									// dwHeight
			//WS_CHILDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | TBSTYLE_TRANSPARENT | TBSTYLE_REGISTERDROP | TBSTYLE_LIST | TBSTYLE_FLAT | CCS_NODIVIDER | CCS_NOPARENTALIGN | CCS_NORESIZE | CCS_NOMOVEY,
			WS_VISIBLE | WS_BORDER | WS_CHILD | WS_CLIPCHILDREN |
				WS_CLIPSIBLINGS | CCS_NODIVIDER | CCS_NOPARENTALIGN |
				RBS_VARHEIGHT | RBS_BANDBORDERS,	// dwStyle
			0,//WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_TOOLWINDOW,// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_MWI_MAINWINDOW,						// dwParentId

			SBN_PARENT_CLEFT,//SBN_LOCK_LEFT,			// pcLeftSizeExp
			SBN_PARENT_CRIGHT,						// pcRightSizeExp
			SBN_PARENT_CTOP,							// pcTopSizeExp
			nullptr, 0,								// pcBottomSizeExp
			nullptr, 0,								// pcWidthSizeExp
			SBN_FIXED_HEIGHT,						// pcHeightSizeExp
		},
		{
			LSW_LT_TOOLBAR,							// ltType
			SBN_MWI_TOOLBAR0,						// wId
			TOOLBARCLASSNAMEW,						// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			0,										// iLeft
			0,										// iTop
			0,										// dwWidth
			0,										// dwHeight
			WS_CHILD | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS | WS_CLIPCHILDREN |
				WS_CLIPSIBLINGS | CCS_NODIVIDER | CCS_NORESIZE | WS_VISIBLE | CCS_ADJUSTABLE,		// dwStyle
			0,										// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_MWI_MAINWINDOW,						// dwParentId
		},*/
	};

	/** Menu bar items for the main window. */
	LSW_MENU_ITEM CMainWindowLayout::m_miMenuBar[] = {
		//bIsSeperator	dwId						bCheckable	bChecked	bEnabled	
		{ FALSE,		SBN_MWMI_FILE,				FALSE,		FALSE,		TRUE,		SBN_LSTR( SBN__FILE ) },
		{ FALSE,		SBN_MWMI_OPTIONS,			FALSE,		FALSE,		TRUE,		SBN_LSTR( SBN__OPTIONS ) },
		{ FALSE,		SBN_MWMI_TOOLS,				FALSE,		FALSE,		TRUE,		SBN_LSTR( SBN__TOOLS ) },
		{ FALSE,		SBN_MWMI_WINDOW,			FALSE,		FALSE,		TRUE,		SBN_LSTR( SBN__WINDOW ) },
		{ FALSE,		SBN_MWMI_HELP,				FALSE,		FALSE,		TRUE,		SBN_LSTR( SBN__HELP ) },
	};

	/** File menu. */
	LSW_MENU_ITEM CMainWindowLayout::m_miFileMenu[] {
		//bIsSeperator	dwId						bCheckable	bChecked	bEnabled	
		{ FALSE,		SBN_MWMI_OPENROM,			FALSE,		FALSE,		TRUE,		SBN_LSTR( SBN_OPEN__ROM ) },
		{ FALSE,		SBN_MWMI_OPENRECENT,		FALSE,		FALSE,		TRUE,		SBN_LSTR( SBN_OPEN_REC_ENT ) },
		{ TRUE,			0,							FALSE,		FALSE,		TRUE,		nullptr },
		{ FALSE,		SBN_MWMI_OPENSAVEFILE,		FALSE,		FALSE,		TRUE,		L"Dummy &0" },
		{ FALSE,		SBN_MWMI_SAVE,				FALSE,		FALSE,		TRUE,		L"Dummy &1" },
		{ FALSE,		SBN_MWMI_SAVEAS,			FALSE,		FALSE,		TRUE,		L"Dummy &2" },
	};

	/** Options menu. */
	LSW_MENU_ITEM CMainWindowLayout::m_miOptionsMenu[] = {
		//bIsSeperator	dwId						bCheckable	bChecked	bEnabled	
		{ FALSE,		SBN_MWMI_VIDEO_SIZE,		FALSE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_SIZE ) },
		{ FALSE,		SBN_MWMI_VIDEO_FILTER,		FALSE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_FILTER ) },
		{ TRUE,			0,							FALSE,		FALSE,		TRUE,		nullptr },
		{ FALSE,		SBN_MWMI_INPUT,				FALSE,		FALSE,		TRUE,		SBN_LSTR( SBN_INPUT ) },
		{ FALSE,		SBN_MWMI_VIDEO,				FALSE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO ) },
	};

	/** Tools menu. */
	LSW_MENU_ITEM CMainWindowLayout::m_miToolsMenu[] = {
		//bIsSeperator	dwId						bCheckable	bChecked	bEnabled	
		{ FALSE,		SBN_MWMI_DELETE,			FALSE,		FALSE,		TRUE,		L"Dummy &0" },
		{ FALSE,		SBN_MWMI_DELETEALL,			FALSE,		FALSE,		TRUE,		L"Dummy &1" },
		{ FALSE,		SBN_MWMI_LOCK,				FALSE,		FALSE,		TRUE,		L"Dummy &2" },
		{ FALSE,		SBN_MWMI_UNLOCK,			FALSE,		FALSE,		TRUE,		L"Dummy &3" },
	};

	/** Windows menu. */
	LSW_MENU_ITEM CMainWindowLayout::m_miWindowsMenu[] = {
		//bIsSeperator	dwId						bCheckable	bChecked	bEnabled	
		{ FALSE,		SBN_MWMI_SHOW_EXPEVAL,		TRUE,		FALSE,		TRUE,		L"Dummy &0" },
		{ FALSE,		SBN_MWMI_SHOWFOUNDADDR,		TRUE,		FALSE,		TRUE,		L"Dummy &1" },
		{ FALSE,		SBN_MWMI_SHOW_CONVERTER,	TRUE,		FALSE,		TRUE,		L"Dummy &2" },
		{ TRUE,			0,							FALSE,		FALSE,		TRUE,		nullptr },
		{ FALSE,		SBN_MWMI_SHOW_ALL,			TRUE,		FALSE,		TRUE,		L"Dummy &3" },
	};

	/** Video-size sub-menu. */
	LSW_MENU_ITEM CMainWindowLayout::m_miVideoSizeMenu[] = {
		//bIsSeperator	dwId						bCheckable	bChecked	bEnabled	
		{ FALSE,		SBN_MWMI_VIDEO_SIZE_1X,		TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_SIZE_1X ) },
		{ FALSE,		SBN_MWMI_VIDEO_SIZE_2X,		TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_SIZE_2X ) },
		{ FALSE,		SBN_MWMI_VIDEO_SIZE_3X,		TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_SIZE_3X ) },
		{ FALSE,		SBN_MWMI_VIDEO_SIZE_4X,		TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_SIZE_4X ) },
		{ FALSE,		SBN_MWMI_VIDEO_SIZE_5X,		TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_SIZE_5X ) },
		{ FALSE,		SBN_MWMI_VIDEO_SIZE_6X,		TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_SIZE_6X ) },
	};

	/** Video-filter sub-menu. */
	LSW_MENU_ITEM CMainWindowLayout::m_miVideoFilterMenu[] = {
		//bIsSeperator	dwId									bCheckable	bChecked	bEnabled	
		{ FALSE,		SBN_MWMI_VIDEO_FILTER_NONE,				TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_FILTER_NONE ) },
		{ FALSE,		SBN_MWMI_VIDEO_FILTER_NTSC_BLARGG,		TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_FILTER_NTSC_BLARGG ) },
		//{ FALSE,		SBN_MWMI_VIDEO_FILTER_PAL_BLARGG,		TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_FILTER_PAL_BLARGG ) },
		{ FALSE,		SBN_MWMI_VIDEO_FILTER_NTSC_LSPIRO,		TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_FILTER_NTSC_L_SPIRO ) },
		{ FALSE,		SBN_MWMI_VIDEO_FILTER_PAL_LSPIRO,		TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_FILTER_PAL_L_SPIRO ) },
		{ FALSE,		SBN_MWMI_VIDEO_FILTER_DENDY_LSPIRO,		TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_FILTER_DENDY_L_SPIRO ) },
		{ FALSE,		SBN_MWMI_VIDEO_FILTER_PALM_LSPIRO,		TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_FILTER_PALM_L_SPIRO ) },
		{ FALSE,		SBN_MWMI_VIDEO_FILTER_PALN_LSPIRO,		TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_FILTER_PALN_L_SPIRO ) },
		////{ FALSE,		SBN_MWMI_VIDEO_FILTER_NTSC_CRT,			TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_FILTER_NTSC_CRT ) },
		{ FALSE,		SBN_MWMI_VIDEO_FILTER_NTSC_CRT_FULL,	TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_FILTER_NTSC_CRT_FULL ) },
		{ FALSE,		SBN_MWMI_VIDEO_FILTER_PAL_CRT_FULL,		TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_FILTER_PAL_CRT_FULL ) },
		{ TRUE,			0,										FALSE,		FALSE,		TRUE,		nullptr },
		//{ FALSE,		SBN_MWMI_VIDEO_FILTER_AUTO_BLARGG,		TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_FILTER_AUTO_BLARGG ) },
		////{ FALSE,		SBN_MWMI_VIDEO_FILTER_AUTO_CRT,			TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_FILTER_AUTO_CRT ) },
		{ FALSE,		SBN_MWMI_VIDEO_FILTER_AUTO_CRT_FULL,	TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_FILTER_AUTO_CRT_FULL ) },
		{ FALSE,		SBN_MWMI_VIDEO_FILTER_AUTO_LSPIRO,		TRUE,		FALSE,		TRUE,		SBN_LSTR( SBN_VIDEO_FILTER_AUTO_LSPIRO ) },
	};

	/** Menus. */
	LSW_MENU_LAYOUT CMainWindowLayout::m_miMenus[] = {
		{
			SBN_MWMI_MENU_BAR,
			0,
			0,
			SBN_ELEMENTS( m_miMenuBar ),
			m_miMenuBar
		},
		{
			SBN_MWMI_MENU_FILE,
			SBN_MWMI_MENU_BAR,
			SBN_MWMI_FILE,
			SBN_ELEMENTS( m_miFileMenu ),
			m_miFileMenu
		},
		{
			SBN_MWMI_MENU_OPTIONS,
			SBN_MWMI_MENU_BAR,
			SBN_MWMI_OPTIONS,
			SBN_ELEMENTS( m_miOptionsMenu ),
			m_miOptionsMenu
		},
		{
			SBN_MWMI_MENU_TOOLS,
			SBN_MWMI_MENU_BAR,
			SBN_MWMI_TOOLS,
			SBN_ELEMENTS( m_miToolsMenu ),
			m_miToolsMenu
		},
		{
			SBN_MWMI_MENU_WINDOW,
			SBN_MWMI_MENU_BAR,
			SBN_MWMI_WINDOW,
			SBN_ELEMENTS( m_miWindowsMenu ),
			m_miWindowsMenu
		},

		// Video Sizes.
		{
			SBN_MWMI_VIDEO_SIZES,
			SBN_MWMI_MENU_OPTIONS,
			SBN_MWMI_VIDEO_SIZE,
			SBN_ELEMENTS( m_miVideoSizeMenu ),
			m_miVideoSizeMenu
		},
		// Video Filters.
		{
			SBN_MWMI_VIDEO_FILTERS,
			SBN_MWMI_MENU_OPTIONS,
			SBN_MWMI_VIDEO_FILTER,
			SBN_ELEMENTS( m_miVideoFilterMenu ),
			m_miVideoFilterMenu
		},
	};

	/** The class for the main window. */
	ATOM CMainWindowLayout::m_aMainClass = 0;

	/** The main window. */
	CWidget * CMainWindowLayout::m_pwMainWindow = nullptr;

	// == Functions.
	/**
	 * Creates the main window.  Makes an in-memory copy of the LSW_WIDGET_LAYOUT's so it can decode strings etc., and registers the main window class.
	 *
	 * \param _pabIsAlive An atomic that tells the main loop that the window has closed and its pointer is no longer valid.
	 * \return Returns the main window widget.
	 */
	CWidget * CMainWindowLayout::CreateMainWindow( std::atomic_bool * _pabIsAlive ) {
		if ( !m_aMainClass ) {
			// Register the window classes we need.
			lsw::CWndClassEx wceEx( lsw::CWidget::WindowProc, L"LSNMAIN" );
			wceEx.SetBackgroundBrush( reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1) );
			m_aMainClass = lsw::CBase::RegisterClassExW( wceEx.Obj() );	
		}

		//std::vector<LSW_WIDGET_LAYOUT> vLayouts;
		std::vector<LSW_MENU_LAYOUT> vMenus;
		std::vector<std::vector<LSW_MENU_ITEM> *> vMenuItems;

		LSW_WIDGET_LAYOUT * _pwMain = CHelpers::FindLayout( m_wlMainWindow, SBN_ELEMENTS( m_wlMainWindow ), SBN_MWI_MAINWINDOW );

		_pwMain->lpwcClass = reinterpret_cast<LPCWSTR>(m_aMainClass);
		m_pwMainWindow = lsw::CBase::LayoutManager()->CreateWindowX( m_wlMainWindow, SBN_ELEMENTS( m_wlMainWindow ),
			SBN_ELEMENTS( m_miMenus ) ? m_miMenus : nullptr, SBN_ELEMENTS( m_miMenus ),
			nullptr,
			reinterpret_cast<uint64_t>(_pabIsAlive) );
		_pwMain->lpwcClass = nullptr;
		return m_pwMainWindow;
	}

	/**
	 * Creates the main menu and adds it to the window.
	 *
	 * \param _pwMainWindow The main window, used for parenting the menu.
	 * \return Returns TRUE if the menu was created.
	 */
	BOOL CMainWindowLayout::CreateMenu( CWidget * _pwMainWindow ) {
		if ( !_pwMainWindow ) { return FALSE; }
		HMENU hMenu = lsw::CBase::LayoutManager()->CreateMenu( m_miMenus, SBN_ELEMENTS( m_miMenus ) );
		if ( !hMenu ) { return FALSE; }
		return ::SetMenu( _pwMainWindow->Wnd(), hMenu );
	}

}	// namespace sbn

#endif	// #ifdef SBN_USE_WINDOWS