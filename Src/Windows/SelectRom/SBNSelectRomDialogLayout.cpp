#ifdef SBN_USE_WINDOWS

/**
 * Copyright L. Spiro 2022
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The ROM-selecting dialog.
 */

#include "SBNSelectRomDialogLayout.h"
#include "../../Localization/SBNLocalization.h"
#include "../../Utilities/SBNUtilities.h"
#include "../Layout/SBNLayoutMacros.h"
#include "../Layout/SBNLayoutManager.h"

#define SBN_SF_W									350
#define SBN_SF_SELECT_GROUP_TOP						SBN_TOP_JUST
#define SBN_SF_VIEW_HEIGHT							50
#define SBN_SF_SEARCH_LABEL_W						22
#define SBN_SF_SELECT_GROUP_HEIGHT					(SBN_SF_VIEW_HEIGHT + (SBN_DEF_EDIT_HEIGHT + SBN_TOP_JUST) + SBN_GROUP_TOP + SBN_GROUP_BOTTOM)
#define SBN_SF_H									(SBN_SF_SELECT_GROUP_HEIGHT + SBN_TOP_JUST * 4 + SBN_DEF_BUTTON_HEIGHT)

namespace sbn {

		// == Members.
	// The layout for the Open Process dialog.
	LSW_WIDGET_LAYOUT CSelectRomDialogLayout::m_wlSelectRomDialog[] = {
		{
			SBN_LT_SELECT_ROM_DIALOG,				// ltType
			SBN_SFI_DIALOG,							// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			64,										// iLeft
			64,										// iTop
			SBN_SF_W,								// dwWidth
			SBN_SF_H,								// dwHeight
			WS_CAPTION | WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_SYSMENU | WS_THICKFRAME | DS_3DLOOK | DS_FIXEDSYS | DS_CENTER | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,					// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT,																				// dwStyleEx
			SBN_LSTR( SBN_SELECT_ROM ),				// pwcText
			0,										// sTextLen
			SBN_SFI_NONE,							// dwParentId
		},

		// Select ROM.
		{
			LSW_LT_GROUPBOX,						// ltType
			SBN_SFI_GROUP,							// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST,							// iLeft
			SBN_SF_SELECT_GROUP_TOP,				// iTop
			SBN_SF_W - (SBN_LEFT_JUST * 2),			// dwWidth
			SBN_SF_SELECT_GROUP_HEIGHT,				// dwHeight
			SBN_GROUPSTYLE,																																								// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,																								// dwStyleEx
			SBN_LSTR( SBN_FILE_LISTING ),			// pwcText
			0,										// sTextLen
			SBN_SFI_DIALOG,							// dwParentId

			SBN_LOCK_LEFT,							// pcLeftSizeExp
			SBN_LOCK_RIGHT,							// pcRightSizeExp
			SBN_LOCK_TOP,							// pcTopSizeExp
			SBN_LOCK_BOTTOM,						// pcBottomSizeExp
			nullptr, 0,								// pcWidthSizeExp
			nullptr, 0,								// pcHeightSizeExp
		},
		{
			LSW_LT_LISTBOX,							// ltType
			SBN_SFI_LISTBOX,						// wId
			WC_LISTBOXW,							// lpwcClass
			TRUE,									// bEnabled
			TRUE,									// bActive
			SBN_LEFT_JUST + SBN_GROUP_LEFT,			// iLeft
			SBN_SF_SELECT_GROUP_TOP + SBN_GROUP_TOP,	// iTop
			SBN_SF_W - (SBN_LEFT_JUST + SBN_GROUP_LEFT) * 2,																															// dwWidth
			SBN_SF_VIEW_HEIGHT,					// dwHeight
			WS_CHILDWINDOW | WS_VISIBLE | WS_TABSTOP | WS_VSCROLL | WS_HSCROLL | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT | LBS_HASSTRINGS,													// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE,																				// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_SFI_DIALOG,							// dwParentId

			SBN_LOCK_LEFT,							// pcLeftSizeExp
			SBN_LOCK_RIGHT,							// pcRightSizeExp
			SBN_LOCK_TOP,							// pcTopSizeExp
			SBN_LOCK_BOTTOM,						// pcBottomSizeExp
			nullptr, 0,								// pcWidthSizeExp
			nullptr, 0,								// pcHeightSizeExp
		},
		{
			LSW_LT_LABEL,							// ltType
			SBN_SFI_LABEL_SEARCH,					// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST + SBN_GROUP_LEFT,			// iLeft
			SBN_SF_SELECT_GROUP_TOP + SBN_GROUP_TOP + SBN_SF_VIEW_HEIGHT + SBN_TOP_JUST + ((SBN_DEF_EDIT_HEIGHT - SBN_DEF_STATIC_HEIGHT) / 2),											// iTop
			SBN_SF_SEARCH_LABEL_W,					// dwWidth
			SBN_DEF_STATIC_HEIGHT,					// dwHeight
			SBN_STATICSTYLE,						// dwStyle
			0,										// dwStyleEx
			SBN_LSTR( SBN_SEARCH_ ),				// pwcText
			0,										// sTextLen
			SBN_SFI_DIALOG,							// dwParentId

			SBN_LOCK_LEFT,							// pcLeftSizeExp
			nullptr, 0,								// pcRightSizeExp
			nullptr, 0,								// pcTopSizeExp
			SBN_LOCK_BOTTOM,						// pcBottomSizeExp
			SBN_FIXED_WIDTH,						// pcWidthSizeExp
			SBN_FIXED_HEIGHT,						// pcHeightSizeExp
		},
		{
			LSW_LT_EDIT,							// ltType
			SBN_SFI_EDIT_SEARCH,					// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST + SBN_GROUP_LEFT + SBN_SF_SEARCH_LABEL_W + SBN_LEFT_JUST,																										// iLeft
			SBN_SF_SELECT_GROUP_TOP + SBN_GROUP_TOP + SBN_SF_VIEW_HEIGHT + SBN_TOP_JUST,																								// iTop
			SBN_SF_W - (SBN_LEFT_JUST + SBN_GROUP_LEFT) * 2 - (SBN_SF_SEARCH_LABEL_W + SBN_LEFT_JUST),																					// dwWidth
			SBN_DEF_EDIT_HEIGHT,					// dwHeight
			SBN_EDITSTYLE,							// dwStyle
			WS_EX_CLIENTEDGE,						// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_SFI_DIALOG,							// dwParentId

			SBN_LOCK_LEFT,							// pcLeftSizeExp
			SBN_LOCK_RIGHT,							// pcRightSizeExp
			nullptr, 0,								// pcTopSizeExp
			SBN_LOCK_BOTTOM,						// pcBottomSizeExp
			nullptr, 0,								// pcWidthSizeExp
			SBN_FIXED_HEIGHT,						// pcHeightSizeExp
		},

		{
			LSW_LT_BUTTON,							// ltType
			SBN_SFI_BUTTON_OK,						// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			TRUE,									// bActive
			SBN_SF_W - SBN_DEF_BUTTON_WIDTH * 2 - 2 - 2,	// iLeft
			SBN_SF_H - SBN_DEF_BUTTON_HEIGHT - 2,		// iTop
			SBN_DEF_BUTTON_WIDTH,					// dwWidth
			SBN_DEF_BUTTON_HEIGHT,					// dwHeight
			SBN_DEFBUTTONSTYLE,						// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,																								// dwStyleEx
			SBN_LSTR( SBN_OK ),						// pwcText
			0,										// sTextLen
			SBN_SFI_DIALOG,							// dwParentId

			nullptr, 0,								// pcLeftSizeExp
			SBN_LOCK_RIGHT,							// pcRightSizeExp
			nullptr, 0,								// pcTopSizeExp
			SBN_LOCK_BOTTOM,						// pcBottomSizeExp
			SBN_FIXED_WIDTH,						// pcWidthSizeExp
			SBN_FIXED_HEIGHT,						// pcHeightSizeExp
		},
		{
			LSW_LT_BUTTON,							// ltType
			SBN_SFI_BUTTON_CANCEL,					// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_SF_W - SBN_DEF_BUTTON_WIDTH * 1 - 2,// iLeft
			SBN_SF_H - SBN_DEF_BUTTON_HEIGHT - 2,	// iTop
			SBN_DEF_BUTTON_WIDTH,					// dwWidth
			SBN_DEF_BUTTON_HEIGHT,					// dwHeight
			SBN_BUTTONSTYLE,						// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,																								// dwStyleEx
			SBN_LSTR( SBN_CANCEL ),					// pwcText
			0,										// sTextLen
			SBN_SFI_DIALOG,							// dwParentId

			nullptr, 0,								// pcLeftSizeExp
			SBN_LOCK_RIGHT,							// pcRightSizeExp
			nullptr, 0,								// pcTopSizeExp
			SBN_LOCK_BOTTOM,						// pcBottomSizeExp
			SBN_FIXED_WIDTH,						// pcWidthSizeExp
			SBN_FIXED_HEIGHT,						// pcHeightSizeExp
		},
	};

#undef SBN_SF_H
#undef SBN_SF_LAST_SECTION_H
#undef SBN_SF_LAST_SECTION_TOP
#undef SBN_SF_ALL_CHECK_W
#undef SBN_SF_MAIN_CHECK_W
#undef SBN_SF_SHOW_GROUP_HEIGHT
#undef SBN_SF_SHOW_GROUP_TOP
#undef SBN_SF_SELECT_GROUP_HEIGHT
#undef SBN_SF_VIEW_HEIGHT
#undef SBN_SF_SELECT_GROUP_TOP
#undef SBN_SF_W

	// == Functions.
	// Creates the Select ROM dialog.
	DWORD CSelectRomDialogLayout::CreateSelectRomDialog( CWidget * _pwParent, const std::vector<std::u16string> * _pvFiles ) {
		lsn::CLayoutManager * plmLayout = static_cast<lsn::CLayoutManager *>(lsw::CBase::LayoutManager());
		INT_PTR ipProc = plmLayout->DialogBoxX( m_wlSelectRomDialog, SBN_ELEMENTS( m_wlSelectRomDialog ), _pwParent, reinterpret_cast<uint64_t>(_pvFiles) );

		return static_cast<DWORD>(ipProc);
	}

}	// namespace sbn

#endif	// #ifdef SBN_USE_WINDOWS
