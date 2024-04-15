#ifdef SBN_USE_WINDOWS

/**
 * Copyright L. Spiro 2022
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The ROM-selecting dialog.
 */

#pragma once

#include <Layout/LSWWidgetLayout.h>
#include <Widget/LSWWidget.h>

using namespace lsw;

namespace sbn {
	
	class CSelectRomDialogLayout {
	public :
		// == Enumerations.
		// Control ID's.
		enum SBN_SELECT_FILE_IDS {
			SBN_SFI_NONE,
			SBN_SFI_DIALOG,
			SBN_SFI_GROUP,
			SBN_SFI_GROUPSHOW,
			SBN_SFI_LISTBOX,
			SBN_SFI_LABEL_SEARCH,
			SBN_SFI_EDIT_SEARCH,
			SBN_SFI_BUTTON_OK,
			SBN_SFI_BUTTON_CANCEL,
			SBN_SFI_LABEL_FOUND,
		};


		// == Functions.
		// Creates the Select ROM dialog.
		static DWORD							CreateSelectRomDialog( CWidget * _pwParent, const std::vector<std::u16string> * _pvFiles );


	protected :
		// == Members.
		// The layout for the Open Process dialog.
		static LSW_WIDGET_LAYOUT				m_wlSelectRomDialog[];

	};

}	// namespace sbn

#endif	// #ifdef SBN_USE_WINDOWS
