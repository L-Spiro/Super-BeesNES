#ifdef SBN_USE_WINDOWS

/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The main window layout.
 */

#pragma once

#include <Layout/LSWMenuLayout.h>
#include <Layout/LSWWidgetLayout.h>
#include <Widget/LSWWidget.h>

using namespace lsw;

namespace sbn {
	
	/**
	 * Class CMainWindowLayout
	 * \brief The main window layout.
	 *
	 * Description: The main window layout.
	 */
	class CMainWindowLayout {
	public :
		// == Enumerations.
		// Control ID's.
		enum SBN_MAIN_WINDOW_IDS {
			SBN_MWI_NONE,
			SBN_MWI_MAINWINDOW,
			SBN_MWI_REBAR0,
			SBN_MWI_TOOLBAR0,
			SBN_MWI_STATUSBAR,

		};

		// Menu items
		enum SBN_MAINWINDOW_MENU_IDS {
			SBN_MWMI_MENU_BAR					= 300,
			SBN_MWMI_MENU_FILE,
			SBN_MWMI_MENU_OPTIONS,
			SBN_MWMI_MENU_TOOLS,
			SBN_MWMI_MENU_WINDOW,
			SBN_MWMI_MENU_HELP,

			SBN_MWMI_FILE						= 100,
			SBN_MWMI_SEARCH,
			SBN_MWMI_OPTIONS,
			SBN_MWMI_TOOLS,
			SBN_MWMI_WINDOW,
			SBN_MWMI_HELP,

			SBN_MWMI_OPENROM,
			SBN_MWMI_OPENRECENT,
			SBN_MWMI_OPENRECENT_MENU,
			SBN_MWMI_OPENFORDEBUG,
			SBN_MWMI_ADDENTRY,
			SBN_MWMI_OPENSAVEFILE,
			SBN_MWMI_SAVE,
			SBN_MWMI_SAVEAS,
			SBN_MWMI_DELETE,
			SBN_MWMI_DELETEALL,
			SBN_MWMI_LOCK,
			SBN_MWMI_UNLOCK,
			SBN_MWMI_EDIT,

			SBN_MWMI_VIDEO_SIZE,
			SBN_MWMI_VIDEO_FILTER,
			SBN_MWMI_INPUT,
			SBN_MWMI_VIDEO,

			SBN_MWMI_VIDEO_SIZES,
			SBN_MWMI_VIDEO_SIZE_1X,
			SBN_MWMI_VIDEO_SIZE_2X,
			SBN_MWMI_VIDEO_SIZE_3X,
			SBN_MWMI_VIDEO_SIZE_4X,
			SBN_MWMI_VIDEO_SIZE_5X,
			SBN_MWMI_VIDEO_SIZE_6X,

			SBN_MWMI_VIDEO_FILTERS,
			SBN_MWMI_VIDEO_FILTER_NONE,
			SBN_MWMI_VIDEO_FILTER_NTSC_BLARGG,
			SBN_MWMI_VIDEO_FILTER_PAL_BLARGG,
			SBN_MWMI_VIDEO_FILTER_NTSC_LSPIRO,
			SBN_MWMI_VIDEO_FILTER_PAL_LSPIRO,
			SBN_MWMI_VIDEO_FILTER_DENDY_LSPIRO,
			SBN_MWMI_VIDEO_FILTER_PALM_LSPIRO,
			SBN_MWMI_VIDEO_FILTER_PALN_LSPIRO,
			SBN_MWMI_VIDEO_FILTER_AUTO_BLARGG,
			SBN_MWMI_VIDEO_FILTER_NTSC_CRT,
			SBN_MWMI_VIDEO_FILTER_NTSC_CRT_FULL,
			SBN_MWMI_VIDEO_FILTER_PAL_CRT_FULL,
			SBN_MWMI_VIDEO_FILTER_AUTO_CRT,
			SBN_MWMI_VIDEO_FILTER_AUTO_CRT_FULL,
			SBN_MWMI_VIDEO_FILTER_AUTO_LSPIRO,

			SBN_MWMI_SHOWFOUNDADDR,
			SBN_MWMI_SHOW_EXPEVAL,
			SBN_MWMI_SHOW_CONVERTER,
			SBN_MWMI_SHOW_ALL,

			SBN_MWMI_SHOW_RECENT_BASE			= 600,
		};


		// == Functions.
		/**
		 * Creates the main window.  Makes an in-memory copy of the LSW_WIDGET_LAYOUT's so it can decode strings etc., and registers the main window class.
		 *
		 * \param _pabIsAlive An atomic that tells the main loop that the window has closed and its pointer is no longer valid.
		 * \return Returns the main window widget.
		 */
		static CWidget *						CreateMainWindow( std::atomic_bool * _pabIsAlive );

		/**
		 * Creates the main menu and adds it to the window.
		 *
		 * \param _pwMainWindow The main window, used for parenting the menu.
		 * \return Returns TRUE if the menu was created.
		 */
		static BOOL								CreateMenu( CWidget * _pwMainWindow );

		/**
		 * Gets the main window widget.
		 *
		 * \return Returns the main window widget.
		 */
		static CWidget *						MainWindow() { return m_pwMainWindow; }


	protected :
		// == Members.
		/** The layout for the main window. */
		static LSW_WIDGET_LAYOUT				m_wlMainWindow[];

		/** Menu bar items for the main window. */
		static LSW_MENU_ITEM					m_miMenuBar[];

		/** File menu. */
		static LSW_MENU_ITEM					m_miFileMenu[];

		/** Options menu. */
		static LSW_MENU_ITEM					m_miOptionsMenu[];

		/** Tools menu. */
		static LSW_MENU_ITEM					m_miToolsMenu[];

		/** Windows menu. */
		static LSW_MENU_ITEM					m_miWindowsMenu[];

		/** Video-size sub-menu. */
		static LSW_MENU_ITEM					m_miVideoSizeMenu[];

		/** Video-filter sub-menu. */
		static LSW_MENU_ITEM					m_miVideoFilterMenu[];

		/** Menus. */
		static LSW_MENU_LAYOUT					m_miMenus[];

		/** The class for the main window. */
		static ATOM								m_aMainClass;

		/** The main window. */
		static CWidget *						m_pwMainWindow;


	};

}	// namespace sbn

#endif	// #ifdef SBN_USE_WINDOWS
