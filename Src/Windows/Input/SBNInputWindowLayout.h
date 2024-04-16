#ifdef SBN_USE_WINDOWS

/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The input window layout.
 */

#pragma once

#include "../../SBNSuperBeesNES.h"
#include "../../Options/SBNOptions.h"
#include <Layout/LSWMenuLayout.h>
#include <Layout/LSWWidgetLayout.h>
#include <Widget/LSWWidget.h>

using namespace lsw;

namespace sbn {

	class										CMainWindow;
	
	/**
	 * Class CInputWindowLayout
	 * \brief The input window layout.
	 *
	 * Description: The input window layout.
	 */
	class CInputWindowLayout {
	public :
		// == Enumerations.
		// Control ID's.
		enum SBN_INPUT_WINDOW_IDS : WORD {
			SBN_IWI_NONE,
			SBN_IWI_MAINWINDOW,
			SBN_IWI_TAB,
			SBN_IWI_OK,
			SBN_IWI_CANCEL,

			SBN_IWI_GENERAL_GROUP,
			SBN_IWI_GENERAL_CONSOLE_TYPE_LABEL,
			SBN_IWI_GENERAL_CONSOLE_TYPE_COMBO,
			SBN_IWI_GENERAL_USE_GLOBAL_CHECK,


#define SBN_IWI_PER_GAME( NAME )				SBN_IWI_SETTINGS_ ## NAME
#define SBN_IWI_GLOBAL( NAME )					SBN_IWI_SETTINGS_ ## NAME
#define SBN_BOTH( NAME )						SBN_IWI_GLOBAL( NAME )
/*#define SBN_IWI_PER_GAME( NAME )				SBN_IWI_PER_GAME_SETTINGS_ ## NAME
#define SBN_IWI_GLOBAL( NAME )					SBN_IWI_GLOBAL_SETTINGS_ ## NAME
#define SBN_BOTH( NAME )						SBN_IWI_PER_GAME( NAME ), SBN_IWI_GLOBAL( NAME )*/
			SBN_IWI_PER_GAME_SETTINGS_PANEL,
			SBN_IWI_GLOBAL_SETTINGS_PANEL,
			//SBN_BOTH( PANEL ),
			SBN_BOTH( GENERAL_GROUP ),
			SBN_BOTH( CONSOLE_TYPE_LABEL ),
			SBN_BOTH( CONSOLE_TYPE_COMBO ),
			SBN_BOTH( USE_GLOBAL_CHECK ),
			SBN_BOTH( SETTINGS_GROUP ),
			SBN_BOTH( PLAYER_1_LABEL ),
			SBN_BOTH( PLAYER_1_COMBO ),
			SBN_BOTH( PLAYER_1_BUTTON ),
			SBN_BOTH( PLAYER_2_LABEL ),
			SBN_BOTH( PLAYER_2_COMBO ),
			SBN_BOTH( PLAYER_2_BUTTON ),

			SBN_BOTH( USE_FOUR_SCORE_CHECK ),
			SBN_BOTH( EXPAND_LABEL ),
			SBN_BOTH( EXPAND_COMBO ),
			SBN_BOTH( EXPAND_BUTTON ),

			SBN_BOTH( PLAYER_3_LABEL ),
			SBN_BOTH( PLAYER_3_COMBO ),
			SBN_BOTH( PLAYER_3_BUTTON ),

			SBN_BOTH( PLAYER_4_LABEL ),
			SBN_BOTH( PLAYER_4_COMBO ),
			SBN_BOTH( PLAYER_4_BUTTON ),
#undef SBN_BOTH
		};


		// == Functions.
		/**
		 * Creates the input-configuration window.
		 *
		 * \param _pwParent The parent of the dialog.
		 * \param _oOptions A reference to the options object.
		 * \param _pmwMainWindow A pointer to the main window to allow access to USB controllers.
		 * \return Returns TRUE if the dialog was created successfully.
		 */
		static BOOL								CreateInputDialog( CWidget * _pwParent, SBN_OPTIONS &_oOptions, lsn::CMainWindow * _pmwMainWindow );

		/**
		 * Creates the global-settings page.
		 *
		 * \param _pwParent the parent of the page.
		 * \param _oOptions A reference to the options object.
		 * \param _pmwMainWindow A pointer to the main window to allow access to USB controllers.
		 * \return Returns the created widget.
		 */
		static CWidget *						CreateGlobalPage( CWidget * _pwParent, SBN_OPTIONS &_oOptions, lsn::CMainWindow * _pmwMainWindow );

		/**
		 * Creates the per-game-settings page.
		 *
		 * \param _pwParent the parent of the page.
		 * \param _oOptions A reference to the options object.
		 * \param _pmwMainWindow A pointer to the main window to allow access to USB controllers.
		 * \return Returns the created widget.
		 */
		static CWidget *						CreatePerGamePage( CWidget * _pwParent, SBN_OPTIONS &_oOptions, lsn::CMainWindow * _pmwMainWindow );


	protected :
		// == Members.
		/** The layout for the main window. */
		static LSW_WIDGET_LAYOUT				m_wlInputWindow[];
		/** The layout for the global-setup panel. */
		static LSW_WIDGET_LAYOUT				m_wlGlobalPanel[];
		/** The layout for the per-game-setup panel. */
		static LSW_WIDGET_LAYOUT				m_wlPerGamePanel[];


		// == Functions.
		/**
		 * Creates the tab pages.
		 *
		 * \param _pwParent The parent widget.
		 * \param _pwlLayout The page layout.
		 * \param _sTotal The number of items to which _pwlLayout points.
		 * \param _oOptions A reference to the options object.
		 * \param _pmwMainWindow A pointer to the main window to allow access to USB controllers.
		 * \return Returns the created page.
		 */
		static CWidget *						CreatePage( CWidget * _pwParent, const LSW_WIDGET_LAYOUT * _pwlLayout, size_t _sTotal, SBN_OPTIONS &_oOptions, lsn::CMainWindow * _pmwMainWindow );
 		
	};

}	// namespace sbn

#endif	// #ifdef SBN_USE_WINDOWS
