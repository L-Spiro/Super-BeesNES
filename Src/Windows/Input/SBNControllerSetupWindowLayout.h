#ifdef SBN_USE_WINDOWS

/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The input-configuration window layout.
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
	 * Class CControllerSetupWindowLayout
	 * \brief The input-configuration window layout.
	 *
	 * Description: The input-configuration window layout.
	 */
	class CControllerSetupWindowLayout {
	public :
		// == Enumerations.
		// Control ID's.
		enum SBN_CONTROLLER_SETUP_WINDOW_IDS : WORD {
			SBN_CSW_NONE,
			SBN_CSW_MAINWINDOW,
			SBN_CSW_TAB,
			SBN_CSW_OK,
			SBN_CSW_CANCEL,

			SBN_CSW_MAIN_PANEL,
			SBN_CSW_RAPID_PANEL,
		};


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
		static BOOL								CreateInputDialog( CWidget * _pwParent, SBN_INPUT_OPTIONS &_ioOptions, lsn::CMainWindow * _pmwMainWindow, size_t _stPlayerIdx );


	protected :
		// == Members.
		/** The layout for the main window. */
		static LSW_WIDGET_LAYOUT				m_wlInputWindow[];


		// == Functions.
		/**
		 * Creates the tab pages.
		 *
		 * \param _pwParent The parent widget.
		 * \param _pwlLayout The page layout.
		 * \param _sTotal The number of items to which _pwlLayout points.
		 * \param _ioOptions A reference to the options object.
		 * \return Returns the created page.
		 */
		//static CWidget *						CreatePage( CWidget * _pwParent, const LSW_WIDGET_LAYOUT * _pwlLayout, size_t _sTotal, SBN_INPUT_OPTIONS &_ioOptions );
 		
	};

}	// namespace sbn

#endif	// #ifdef SBN_USE_WINDOWS
