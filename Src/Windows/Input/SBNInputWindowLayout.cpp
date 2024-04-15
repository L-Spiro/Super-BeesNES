#ifdef SBN_USE_WINDOWS

/**
 * Copyright L. Spiro 2022
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: The input window layout.
 */

#include "SBNInputWindowLayout.h"
#include "../../Localization/SBNLocalization.h"
#include "../Input/SBNInputWindow.h"
#include "../Layout/SBNLayoutMacros.h"
#include "../Layout/SBNLayoutManager.h"



namespace sbn {

#define SBN_FIRST_SECTION_W							(80 * 60 / 100)
#define SBN_FIRST_SECTION_L							(SBN_LEFT_JUST + SBN_GROUP_LEFT)
#define SBN_COMBO_W									(195 * 60 / 100)
#define SBN_COMBO_L									(SBN_FIRST_SECTION_L + SBN_FIRST_SECTION_W + SBN_LEFT_JUST)
#define SBN_THIRD_SECTION_W							(82 * 60 / 100)
#define SBN_THIRD_SECTION_L							(SBN_COMBO_L + SBN_COMBO_W + SBN_LEFT_JUST)
#define SBN_GENERAL_GROUP_H							(SBN_GROUP_TOP + SBN_DEF_COMBO_HEIGHT + SBN_GROUP_BOTTOM)
#define SBN_SETTINGS_GROUP_H						(SBN_GROUP_TOP + (SBN_DEF_COMBO_HEIGHT * 5) + (SBN_TOP_JUST * 4) + SBN_GROUP_BOTTOM)

#define SBN_INPUT_GROUP_W							(SBN_GROUP_LEFT + SBN_FIRST_SECTION_W + SBN_LEFT_JUST + SBN_COMBO_W + SBN_LEFT_JUST + SBN_THIRD_SECTION_W + SBN_GROUP_RIGHT)
#define SBN_INPUT_W									(SBN_LEFT_JUST + SBN_LEFT_JUST + SBN_INPUT_GROUP_W + SBN_LEFT_JUST + SBN_LEFT_JUST)
#define SBN_INPUT_H									(SBN_GENERAL_GROUP_H + SBN_SETTINGS_GROUP_H + 20)

	// == Members.
	/** The layout for the main window. */
	LSW_WIDGET_LAYOUT CInputWindowLayout::m_wlInputWindow[] = {
		{
			SBN_LT_INPUT_DIALOG,					// ltType
			SBN_IWI_MAINWINDOW,						// wId
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
			SBN_IWI_NONE,							// dwParentId
		},

		{
			LSW_LT_TAB,								// ltType
			SBN_IWI_TAB,							// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			0,										// iLeft
			0,										// iTop
			255,									// dwWidth
			(SBN_GENERAL_GROUP_H + SBN_SETTINGS_GROUP_H) + 22,						// dwHeight
			WS_CHILDWINDOW | WS_VISIBLE | WS_TABSTOP | TCS_HOTTRACK,				// dwStyle
			WS_EX_ACCEPTFILES,														// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_IWI_MAINWINDOW,						// dwParentId

			SBN_PARENT_VCLEFT,						// pcLeftSizeExp
			SBN_PARENT_VCRIGHT,						// pcRightSizeExp
			SBN_PARENT_VCTOP,						// pcTopSizeExp
			nullptr, 0,								// pcBottomSizeExp
			nullptr, 0,								// pcWidthSizeExp
			SBN_FIXED_HEIGHT,						// pcHeightSizeExp
		},


		{
			LSW_LT_BUTTON,							// ltType
			SBN_IWI_OK,								// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			TRUE,									// bActive
			SBN_LEFT_JUST,							// iLeft
			SBN_INPUT_H - SBN_DEF_BUTTON_HEIGHT - SBN_TOP_JUST,								// iTop
			SBN_DEF_BUTTON_WIDTH,					// dwWidth
			SBN_DEF_BUTTON_HEIGHT,					// dwHeight
			SBN_DEFBUTTONSTYLE,						// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,	// dwStyleEx
			SBN_LSTR( SBN_OK ),						// pwcText
			0,										// sTextLen
			SBN_IWI_MAINWINDOW,						// dwParentId
		},
		{
			LSW_LT_BUTTON,							// ltType
			SBN_IWI_CANCEL,							// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_INPUT_W - SBN_DEF_BUTTON_WIDTH * 1 - SBN_LEFT_JUST,							// iLeft
			SBN_INPUT_H - SBN_DEF_BUTTON_HEIGHT - SBN_TOP_JUST,								// iTop
			SBN_DEF_BUTTON_WIDTH,					// dwWidth
			SBN_DEF_BUTTON_HEIGHT,					// dwHeight
			SBN_BUTTONSTYLE,						// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,	// dwStyleEx
			SBN_LSTR( SBN_CANCEL ),					// pwcText
			0,										// sTextLen
			SBN_IWI_MAINWINDOW,						// dwParentId
		},
	};

	/** The layout for the global-setup panel. */
	LSW_WIDGET_LAYOUT CInputWindowLayout::m_wlGlobalPanel[] = {
		{
			SBN_LT_GLOBAL_INPUT_PAGE,				// ltType
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			0, 0,									// iLeft, iTop
			SBN_LEFT_JUST + SBN_INPUT_GROUP_W + SBN_LEFT_JUST,
			(SBN_GENERAL_GROUP_H + SBN_SETTINGS_GROUP_H),
			WS_CHILDWINDOW | WS_VISIBLE | DS_3DLOOK | DS_FIXEDSYS | DS_SETFONT | DS_CONTROL,										// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_CONTROLPARENT,												// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_IWI_NONE,							// dwParentId

			SBN_PARENT_VCLEFT,						// pcLeftSizeExp
			nullptr, 0,								// pcRightSizeExp
			SBN_PARENT_VCTOP,						// pcTopSizeExp
			nullptr, 0,								// pcBottomSizeExp
			SBN_FIXED_WIDTH,						// pcWidthSizeExp
			SBN_FIXED_HEIGHT,						// pcHeightSizeExp
		},


		// General.
		{
			LSW_LT_GROUPBOX,						// ltType
			SBN_IWI_GLOBAL( GENERAL_GROUP ),		// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST,							// iLeft
			0,										// iTop
			SBN_INPUT_GROUP_W,						// dwWidth
			SBN_GENERAL_GROUP_H,					// dwHeight
			SBN_GROUPSTYLE,																											// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,											// dwStyleEx
			SBN_LSTR( SBN_INPUT_GENERAL ),			// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},
		{
			LSW_LT_LABEL,							// ltType
			SBN_IWI_GLOBAL( CONSOLE_TYPE_LABEL ),	// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_FIRST_SECTION_L,					// iLeft
			SBN_GROUP_TOP + ((SBN_DEF_COMBO_HEIGHT - SBN_DEF_STATIC_HEIGHT) >> 1),							// iTop
			SBN_FIRST_SECTION_W,					// dwWidth
			SBN_DEF_STATIC_HEIGHT,					// dwHeight
			SBN_STATICSTYLE,						// dwStyle
			0,										// dwStyleEx
			SBN_LSTR( SBN_INPUT_CONSOLE_TYPE_ ),	// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},
		{
			LSW_LT_COMBOBOX,						// ltType
			SBN_IWI_GLOBAL( CONSOLE_TYPE_COMBO ),	// wId
			WC_COMBOBOXW,							// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_COMBO_L,							// iLeft
			SBN_GROUP_TOP,							// iTop
			SBN_COMBO_W,							// dwWidth
			SBN_DEF_COMBO_HEIGHT,					// dwHeight
			SBN_COMBOSTYLE_LIST,					// dwStyle
			SBN_COMBOSTYLEEX_LIST,					// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},


		// Settings.
		{
			LSW_LT_GROUPBOX,						// ltType
			SBN_IWI_GLOBAL( SETTINGS_GROUP ),		// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST,							// iLeft
			SBN_GENERAL_GROUP_H,					// iTop
			SBN_INPUT_GROUP_W,						// dwWidth
			SBN_SETTINGS_GROUP_H,					// dwHeight
			SBN_GROUPSTYLE,																											// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,											// dwStyleEx
			SBN_LSTR( SBN_INPUT_SETTINGS ),			// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},

		{
			LSW_LT_LABEL,							// ltType
			SBN_IWI_GLOBAL( PLAYER_1_LABEL ),		// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST + SBN_GROUP_LEFT,			// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + ((SBN_DEF_COMBO_HEIGHT - SBN_DEF_STATIC_HEIGHT) >> 1),							// iTop
			SBN_FIRST_SECTION_W,					// dwWidth
			SBN_DEF_STATIC_HEIGHT,					// dwHeight
			SBN_STATICSTYLE,						// dwStyle
			0,										// dwStyleEx
			SBN_LSTR( SBN_INPUT_PLAYER_1_ ),		// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},
		{
			LSW_LT_COMBOBOX,						// ltType
			SBN_IWI_GLOBAL( PLAYER_1_COMBO ),		// wId
			WC_COMBOBOXW,							// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_COMBO_L,							// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP,	// iTop
			SBN_COMBO_W,							// dwWidth
			SBN_DEF_COMBO_HEIGHT,					// dwHeight
			SBN_COMBOSTYLE_LIST,					// dwStyle
			SBN_COMBOSTYLEEX_LIST,					// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},
		{
			LSW_LT_BUTTON,							// ltType
			SBN_IWI_GLOBAL( PLAYER_1_BUTTON ),		// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_THIRD_SECTION_L,					// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP,	// iTop
			SBN_THIRD_SECTION_W,					// dwWidth
			SBN_DEF_BUTTON_HEIGHT,					// dwHeight
			SBN_BUTTONSTYLE,						// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,																								// dwStyleEx
			SBN_LSTR( SBN_INPUT_CONFIGURE ),		// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},

		{
			LSW_LT_LABEL,							// ltType
			SBN_IWI_GLOBAL( PLAYER_2_LABEL ),		// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST + SBN_GROUP_LEFT,			// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + ((SBN_DEF_COMBO_HEIGHT - SBN_DEF_STATIC_HEIGHT) >> 1) + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 1,							// iTop
			SBN_FIRST_SECTION_W,					// dwWidth
			SBN_DEF_STATIC_HEIGHT,					// dwHeight
			SBN_STATICSTYLE,						// dwStyle
			0,										// dwStyleEx
			SBN_LSTR( SBN_INPUT_PLAYER_2_ ),		// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},
		{
			LSW_LT_COMBOBOX,						// ltType
			SBN_IWI_GLOBAL( PLAYER_2_COMBO ),		// wId
			WC_COMBOBOXW,							// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_COMBO_L,							// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 1,	// iTop
			SBN_COMBO_W,							// dwWidth
			SBN_DEF_COMBO_HEIGHT,					// dwHeight
			SBN_COMBOSTYLE_LIST,					// dwStyle
			SBN_COMBOSTYLEEX_LIST,					// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},
		{
			LSW_LT_BUTTON,							// ltType
			SBN_IWI_GLOBAL( PLAYER_2_BUTTON ),		// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_THIRD_SECTION_L,					// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 1,	// iTop
			SBN_THIRD_SECTION_W,					// dwWidth
			SBN_DEF_BUTTON_HEIGHT,					// dwHeight
			SBN_BUTTONSTYLE,						// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,																					// dwStyleEx
			SBN_LSTR( SBN_INPUT_CONFIGURE ),		// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},

		// Use Four Score.
		{
			LSW_LT_CHECK,							// ltType
			SBN_IWI_PER_GAME( USE_FOUR_SCORE_CHECK ),																														// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST + SBN_GROUP_LEFT,			// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + ((SBN_DEF_COMBO_HEIGHT - SBN_DEF_CHECK_HEIGHT) >> 1) + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 2,							// iTop
			SBN_INPUT_GROUP_W - SBN_GROUP_LEFT * 2,	// dwWidth
			SBN_DEF_CHECK_HEIGHT,					// dwHeight
			SBN_CHECKSTYLE,							// dwStyle
			0,										// dwStyleEx
			SBN_LSTR( SBN_INPUT_USE_4_SCORE ),		// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},

		// Expension Port.
		{
			LSW_LT_LABEL,							// ltType
			SBN_IWI_GLOBAL( EXPAND_LABEL ),			// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST + SBN_GROUP_LEFT,			// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + ((SBN_DEF_COMBO_HEIGHT - SBN_DEF_STATIC_HEIGHT) >> 1) + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 2,							// iTop
			SBN_FIRST_SECTION_W,					// dwWidth
			SBN_DEF_STATIC_HEIGHT,					// dwHeight
			SBN_STATICSTYLE,						// dwStyle
			0,										// dwStyleEx
			SBN_LSTR( SBN_INPUT_EXPANSION_PORT ),	// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},
		{
			LSW_LT_COMBOBOX,						// ltType
			SBN_IWI_GLOBAL( EXPAND_COMBO ),			// wId
			WC_COMBOBOXW,							// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_COMBO_L,							// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 2,	// iTop
			SBN_COMBO_W,							// dwWidth
			SBN_DEF_COMBO_HEIGHT,					// dwHeight
			SBN_COMBOSTYLE_LIST,					// dwStyle
			SBN_COMBOSTYLEEX_LIST,					// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},
		{
			LSW_LT_BUTTON,							// ltType
			SBN_IWI_GLOBAL( EXPAND_BUTTON ),		// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_THIRD_SECTION_L,					// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 2,	// iTop
			SBN_THIRD_SECTION_W,					// dwWidth
			SBN_DEF_BUTTON_HEIGHT,					// dwHeight
			SBN_BUTTONSTYLE,						// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,																								// dwStyleEx
			SBN_LSTR( SBN_INPUT_CONFIGURE ),		// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},

		// Player 3.
		{
			LSW_LT_LABEL,							// ltType
			SBN_IWI_GLOBAL( PLAYER_3_LABEL ),		// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST + SBN_GROUP_LEFT,			// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + ((SBN_DEF_COMBO_HEIGHT - SBN_DEF_STATIC_HEIGHT) >> 1) + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 3,							// iTop
			SBN_FIRST_SECTION_W,					// dwWidth
			SBN_DEF_STATIC_HEIGHT,					// dwHeight
			SBN_STATICSTYLE,						// dwStyle
			0,										// dwStyleEx
			SBN_LSTR( SBN_INPUT_PLAYER_3_ ),		// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},
		{
			LSW_LT_COMBOBOX,						// ltType
			SBN_IWI_GLOBAL( PLAYER_3_COMBO ),		// wId
			WC_COMBOBOXW,							// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_COMBO_L,							// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 3,	// iTop
			SBN_COMBO_W,							// dwWidth
			SBN_DEF_COMBO_HEIGHT,					// dwHeight
			SBN_COMBOSTYLE_LIST,					// dwStyle
			SBN_COMBOSTYLEEX_LIST,					// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},
		{
			LSW_LT_BUTTON,							// ltType
			SBN_IWI_GLOBAL( PLAYER_3_BUTTON ),		// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_THIRD_SECTION_L,					// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 3,	// iTop
			SBN_THIRD_SECTION_W,					// dwWidth
			SBN_DEF_BUTTON_HEIGHT,					// dwHeight
			SBN_BUTTONSTYLE,						// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,																								// dwStyleEx
			SBN_LSTR( SBN_INPUT_CONFIGURE ),		// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},

		// Player 4.
		{
			LSW_LT_LABEL,							// ltType
			SBN_IWI_GLOBAL( PLAYER_4_LABEL ),		// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST + SBN_GROUP_LEFT,			// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + ((SBN_DEF_COMBO_HEIGHT - SBN_DEF_STATIC_HEIGHT) >> 1) + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 4,							// iTop
			SBN_FIRST_SECTION_W,					// dwWidth
			SBN_DEF_STATIC_HEIGHT,					// dwHeight
			SBN_STATICSTYLE,						// dwStyle
			0,										// dwStyleEx
			SBN_LSTR( SBN_INPUT_PLAYER_4_ ),		// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},
		{
			LSW_LT_COMBOBOX,						// ltType
			SBN_IWI_GLOBAL( PLAYER_4_COMBO ),		// wId
			WC_COMBOBOXW,							// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_COMBO_L,							// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 4,	// iTop
			SBN_COMBO_W,							// dwWidth
			SBN_DEF_COMBO_HEIGHT,					// dwHeight
			SBN_COMBOSTYLE_LIST,					// dwStyle
			SBN_COMBOSTYLEEX_LIST,					// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},
		{
			LSW_LT_BUTTON,							// ltType
			SBN_IWI_GLOBAL( PLAYER_4_BUTTON ),		// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_THIRD_SECTION_L,					// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 4,	// iTop
			SBN_THIRD_SECTION_W,					// dwWidth
			SBN_DEF_BUTTON_HEIGHT,					// dwHeight
			SBN_BUTTONSTYLE,						// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR /*| WS_EX_NOPARENTNOTIFY*/,																								// dwStyleEx
			SBN_LSTR( SBN_INPUT_CONFIGURE ),		// pwcText
			0,										// sTextLen
			SBN_IWI_GLOBAL_SETTINGS_PANEL,			// dwParentId
		},
	};

	/** The layout for the per-game-setup panel. */
	LSW_WIDGET_LAYOUT CInputWindowLayout::m_wlPerGamePanel[] = {
		{
			SBN_LT_PER_GAME_INPUT_PAGE,				// ltType
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			0, 0,									// iLeft, iTop
			SBN_LEFT_JUST + SBN_INPUT_GROUP_W + SBN_LEFT_JUST,
			(SBN_GENERAL_GROUP_H + SBN_SETTINGS_GROUP_H),
			WS_CHILDWINDOW | WS_VISIBLE | DS_3DLOOK | DS_FIXEDSYS | DS_SETFONT | DS_CONTROL,										// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_CONTROLPARENT,												// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_IWI_NONE,							// dwParentId

			SBN_PARENT_VCLEFT,						// pcLeftSizeExp
			nullptr, 0,								// pcRightSizeExp
			SBN_PARENT_VCTOP,						// pcTopSizeExp
			nullptr, 0,								// pcBottomSizeExp
			SBN_FIXED_WIDTH,						// pcWidthSizeExp
			SBN_FIXED_HEIGHT,						// pcHeightSizeExp
		},


		// General.
		{
			LSW_LT_GROUPBOX,						// ltType
			SBN_IWI_PER_GAME( GENERAL_GROUP ),		// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST,							// iLeft
			0,										// iTop
			SBN_INPUT_GROUP_W,						// dwWidth
			SBN_GENERAL_GROUP_H,					// dwHeight
			SBN_GROUPSTYLE,																											// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,											// dwStyleEx
			SBN_LSTR( SBN_INPUT_GENERAL ),			// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},
		{
			LSW_LT_LABEL,							// ltType
			SBN_IWI_PER_GAME( CONSOLE_TYPE_LABEL ),	// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_FIRST_SECTION_L,					// iLeft
			SBN_GROUP_TOP + ((SBN_DEF_COMBO_HEIGHT - SBN_DEF_STATIC_HEIGHT) >> 1),							// iTop
			SBN_FIRST_SECTION_W,					// dwWidth
			SBN_DEF_STATIC_HEIGHT,					// dwHeight
			SBN_STATICSTYLE,						// dwStyle
			0,										// dwStyleEx
			SBN_LSTR( SBN_INPUT_CONSOLE_TYPE_ ),	// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},
		{
			LSW_LT_COMBOBOX,						// ltType
			SBN_IWI_PER_GAME( CONSOLE_TYPE_COMBO ),	// wId
			WC_COMBOBOXW,							// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_COMBO_L,							// iLeft
			SBN_GROUP_TOP,							// iTop
			SBN_COMBO_W,							// dwWidth
			SBN_DEF_COMBO_HEIGHT,					// dwHeight
			SBN_COMBOSTYLE_LIST,					// dwStyle
			SBN_COMBOSTYLEEX_LIST,					// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},
		{
			LSW_LT_CHECK,							// ltType
			SBN_IWI_PER_GAME( USE_GLOBAL_CHECK ),	// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_THIRD_SECTION_L,					// iLeft
			SBN_GROUP_TOP + ((SBN_DEF_COMBO_HEIGHT - SBN_DEF_CHECK_HEIGHT) >> 1),							// iTop
			SBN_THIRD_SECTION_W,					// dwWidth
			SBN_DEF_CHECK_HEIGHT,					// dwHeight
			SBN_CHECKSTYLE,							// dwStyle
			0,										// dwStyleEx
			SBN_LSTR( SBN_INPUT_USE_GLOBAL ),		// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},


		// Settings.
		{
			LSW_LT_GROUPBOX,						// ltType
			SBN_IWI_PER_GAME( SETTINGS_GROUP ),		// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST,							// iLeft
			SBN_GENERAL_GROUP_H,					// iTop
			SBN_INPUT_GROUP_W,						// dwWidth
			SBN_SETTINGS_GROUP_H,					// dwHeight
			SBN_GROUPSTYLE,																											// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,											// dwStyleEx
			SBN_LSTR( SBN_INPUT_SETTINGS ),			// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},

		{
			LSW_LT_LABEL,							// ltType
			SBN_IWI_PER_GAME( PLAYER_1_LABEL ),		// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST + SBN_GROUP_LEFT,			// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + ((SBN_DEF_COMBO_HEIGHT - SBN_DEF_STATIC_HEIGHT) >> 1),							// iTop
			SBN_FIRST_SECTION_W,					// dwWidth
			SBN_DEF_STATIC_HEIGHT,					// dwHeight
			SBN_STATICSTYLE,						// dwStyle
			0,										// dwStyleEx
			SBN_LSTR( SBN_INPUT_PLAYER_1_ ),		// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},
		{
			LSW_LT_COMBOBOX,						// ltType
			SBN_IWI_PER_GAME( PLAYER_1_COMBO ),		// wId
			WC_COMBOBOXW,							// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_COMBO_L,							// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP,	// iTop
			SBN_COMBO_W,							// dwWidth
			SBN_DEF_COMBO_HEIGHT,					// dwHeight
			SBN_COMBOSTYLE_LIST,					// dwStyle
			SBN_COMBOSTYLEEX_LIST,					// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},
		{
			LSW_LT_BUTTON,							// ltType
			SBN_IWI_PER_GAME( PLAYER_1_BUTTON ),		// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_THIRD_SECTION_L,					// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP,	// iTop
			SBN_THIRD_SECTION_W,					// dwWidth
			SBN_DEF_BUTTON_HEIGHT,					// dwHeight
			SBN_BUTTONSTYLE,						// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,																								// dwStyleEx
			SBN_LSTR( SBN_INPUT_CONFIGURE ),		// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},

		{
			LSW_LT_LABEL,							// ltType
			SBN_IWI_PER_GAME( PLAYER_2_LABEL ),		// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST + SBN_GROUP_LEFT,			// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + ((SBN_DEF_COMBO_HEIGHT - SBN_DEF_STATIC_HEIGHT) >> 1) + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 1,							// iTop
			SBN_FIRST_SECTION_W,					// dwWidth
			SBN_DEF_STATIC_HEIGHT,					// dwHeight
			SBN_STATICSTYLE,						// dwStyle
			0,										// dwStyleEx
			SBN_LSTR( SBN_INPUT_PLAYER_2_ ),		// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},
		{
			LSW_LT_COMBOBOX,						// ltType
			SBN_IWI_PER_GAME( PLAYER_2_COMBO ),		// wId
			WC_COMBOBOXW,							// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_COMBO_L,							// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 1,	// iTop
			SBN_COMBO_W,							// dwWidth
			SBN_DEF_COMBO_HEIGHT,					// dwHeight
			SBN_COMBOSTYLE_LIST,					// dwStyle
			SBN_COMBOSTYLEEX_LIST,					// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},
		{
			LSW_LT_BUTTON,							// ltType
			SBN_IWI_PER_GAME( PLAYER_2_BUTTON ),		// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_THIRD_SECTION_L,					// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 1,	// iTop
			SBN_THIRD_SECTION_W,					// dwWidth
			SBN_DEF_BUTTON_HEIGHT,					// dwHeight
			SBN_BUTTONSTYLE,						// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,																								// dwStyleEx
			SBN_LSTR( SBN_INPUT_CONFIGURE ),		// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},

		// Use Four Score.
		{
			LSW_LT_CHECK,							// ltType
			SBN_IWI_PER_GAME( USE_FOUR_SCORE_CHECK ),																														// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST + SBN_GROUP_LEFT,			// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + ((SBN_DEF_COMBO_HEIGHT - SBN_DEF_CHECK_HEIGHT) >> 1) + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 2,							// iTop
			SBN_INPUT_GROUP_W - SBN_GROUP_LEFT * 2,	// dwWidth
			SBN_DEF_CHECK_HEIGHT,					// dwHeight
			SBN_CHECKSTYLE,							// dwStyle
			0,										// dwStyleEx
			SBN_LSTR( SBN_INPUT_USE_4_SCORE ),		// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},

		// Expension Port.
		{
			LSW_LT_LABEL,							// ltType
			SBN_IWI_PER_GAME( EXPAND_LABEL ),		// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST + SBN_GROUP_LEFT,			// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + ((SBN_DEF_COMBO_HEIGHT - SBN_DEF_STATIC_HEIGHT) >> 1) + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 2,						// iTop
			SBN_FIRST_SECTION_W,					// dwWidth
			SBN_DEF_STATIC_HEIGHT,					// dwHeight
			SBN_STATICSTYLE,						// dwStyle
			0,										// dwStyleEx
			SBN_LSTR( SBN_INPUT_EXPANSION_PORT ),	// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},
		{
			LSW_LT_COMBOBOX,						// ltType
			SBN_IWI_PER_GAME( EXPAND_COMBO ),			// wId
			WC_COMBOBOXW,							// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_COMBO_L,							// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 2,	// iTop
			SBN_COMBO_W,							// dwWidth
			SBN_DEF_COMBO_HEIGHT,					// dwHeight
			SBN_COMBOSTYLE_LIST,					// dwStyle
			SBN_COMBOSTYLEEX_LIST,					// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},
		{
			LSW_LT_BUTTON,							// ltType
			SBN_IWI_PER_GAME( EXPAND_BUTTON ),		// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_THIRD_SECTION_L,					// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 2,	// iTop
			SBN_THIRD_SECTION_W,					// dwWidth
			SBN_DEF_BUTTON_HEIGHT,					// dwHeight
			SBN_BUTTONSTYLE,						// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,																								// dwStyleEx
			SBN_LSTR( SBN_INPUT_CONFIGURE ),		// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},

		// Player 3.
		{
			LSW_LT_LABEL,							// ltType
			SBN_IWI_PER_GAME( PLAYER_3_LABEL ),		// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST + SBN_GROUP_LEFT,			// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + ((SBN_DEF_COMBO_HEIGHT - SBN_DEF_STATIC_HEIGHT) >> 1) + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 3,							// iTop
			SBN_FIRST_SECTION_W,					// dwWidth
			SBN_DEF_STATIC_HEIGHT,					// dwHeight
			SBN_STATICSTYLE,						// dwStyle
			0,										// dwStyleEx
			SBN_LSTR( SBN_INPUT_PLAYER_3_ ),		// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},
		{
			LSW_LT_COMBOBOX,						// ltType
			SBN_IWI_PER_GAME( PLAYER_3_COMBO ),		// wId
			WC_COMBOBOXW,							// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_COMBO_L,							// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 3,	// iTop
			SBN_COMBO_W,							// dwWidth
			SBN_DEF_COMBO_HEIGHT,					// dwHeight
			SBN_COMBOSTYLE_LIST,					// dwStyle
			SBN_COMBOSTYLEEX_LIST,					// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},
		{
			LSW_LT_BUTTON,							// ltType
			SBN_IWI_PER_GAME( PLAYER_3_BUTTON ),		// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_THIRD_SECTION_L,					// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 3,	// iTop
			SBN_THIRD_SECTION_W,					// dwWidth
			SBN_DEF_BUTTON_HEIGHT,					// dwHeight
			SBN_BUTTONSTYLE,						// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY,																								// dwStyleEx
			SBN_LSTR( SBN_INPUT_CONFIGURE ),		// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},

		// Player 4.
		{
			LSW_LT_LABEL,							// ltType
			SBN_IWI_PER_GAME( PLAYER_4_LABEL ),		// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_LEFT_JUST + SBN_GROUP_LEFT,			// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + ((SBN_DEF_COMBO_HEIGHT - SBN_DEF_STATIC_HEIGHT) >> 1) + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 4,							// iTop
			SBN_FIRST_SECTION_W,					// dwWidth
			SBN_DEF_STATIC_HEIGHT,					// dwHeight
			SBN_STATICSTYLE,						// dwStyle
			0,										// dwStyleEx
			SBN_LSTR( SBN_INPUT_PLAYER_4_ ),		// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},
		{
			LSW_LT_COMBOBOX,						// ltType
			SBN_IWI_PER_GAME( PLAYER_4_COMBO ),		// wId
			WC_COMBOBOXW,							// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_COMBO_L,							// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 4,	// iTop
			SBN_COMBO_W,							// dwWidth
			SBN_DEF_COMBO_HEIGHT,					// dwHeight
			SBN_COMBOSTYLE_LIST,					// dwStyle
			SBN_COMBOSTYLEEX_LIST,					// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},
		{
			LSW_LT_BUTTON,							// ltType
			SBN_IWI_PER_GAME( PLAYER_4_BUTTON ),	// wId
			WC_BUTTONW,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			SBN_THIRD_SECTION_L,					// iLeft
			SBN_GENERAL_GROUP_H + SBN_GROUP_TOP + (SBN_DEF_COMBO_HEIGHT + SBN_TOP_JUST) * 4,	// iTop
			SBN_THIRD_SECTION_W,					// dwWidth
			SBN_DEF_BUTTON_HEIGHT,					// dwHeight
			SBN_BUTTONSTYLE,						// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR /*| WS_EX_NOPARENTNOTIFY*/,																								// dwStyleEx
			SBN_LSTR( SBN_INPUT_CONFIGURE ),		// pwcText
			0,										// sTextLen
			SBN_IWI_PER_GAME_SETTINGS_PANEL,		// dwParentId
		},
	};

#undef SBN_INPUT_H
#undef SBN_INPUT_W
#undef SBN_INPUT_GROUP_W
#undef SBN_SETTINGS_GROUP_H
#undef SBN_GENERAL_GROUP_H

#undef SBN_THIRD_SECTION_L
#undef SBN_THIRD_SECTION_W
#undef SBN_COMBO_L
#undef SBN_COMBO_W
#undef SBN_FIRST_SECTION_L
#undef SBN_FIRST_SECTION_W


	// == Functions.
	/**
	 * Creates the input-configuration window.
	 *
	 * \param _pwParent The parent of the dialog.
	 * \param _oOptions A reference to the options object.
	 * \return Returns TRUE if the dialog was created successfully.
	 */
	BOOL CInputWindowLayout::CreateInputDialog( CWidget * _pwParent, SBN_OPTIONS &_oOptions, lsn::CMainWindow * _pmwMainWindow ) {
		lsn::CLayoutManager * plmLayout = static_cast<lsn::CLayoutManager *>(lsw::CBase::LayoutManager());
		CInputWindow::SBN_CONTROLLER_SETUP_DATA csdData = {
			.poOptions = &_oOptions,
			.pmwMainWindow = _pmwMainWindow,
		};
		INT_PTR ipProc = plmLayout->DialogBoxX( m_wlInputWindow, SBN_ELEMENTS( m_wlInputWindow ), _pwParent, reinterpret_cast<uint64_t>(&csdData) );
		if ( ipProc != 0 ) {
			// Success.  Do stuff.
			return TRUE;
		}
		return FALSE;
	}

	/**
	 * Creates the global-settings page.
	 *
	 * \param _pwParent the parent of the page.
	 * \param _oOptions A reference to the options object.
	 * \return Returns the created widget.
	 */
	CWidget * CInputWindowLayout::CreateGlobalPage( CWidget * _pwParent, SBN_OPTIONS &_oOptions, lsn::CMainWindow * _pmwMainWindow ) {
		return CreatePage( _pwParent, m_wlGlobalPanel, SBN_ELEMENTS( m_wlGlobalPanel ), _oOptions, _pmwMainWindow );
	}

	/**
	 * Creates the per-game-settings page.
	 *
	 * \param _pwParent the parent of the page.
	 * \param _oOptions A reference to the options object.
	 * \return Returns the created widget.
	 */
	CWidget * CInputWindowLayout::CreatePerGamePage( CWidget * _pwParent, SBN_OPTIONS &_oOptions, lsn::CMainWindow * _pmwMainWindow ) {
		return CreatePage( _pwParent, m_wlPerGamePanel, SBN_ELEMENTS( m_wlPerGamePanel ), _oOptions, _pmwMainWindow );
	}

	/**
	 * Creates the tab pages.
	 *
	 * \param _pwParent The parent widget.
	 * \param _pwlLayout The page layout.
	 * \param _sTotal The number of items to which _pwlLayout points.
	 * \param _oOptions A reference to the options object.
	 * \return Returns the created page.
	 */
	CWidget * CInputWindowLayout::CreatePage( CWidget * _pwParent, const LSW_WIDGET_LAYOUT * _pwlLayout, size_t _sTotal, SBN_OPTIONS &_oOptions, lsn::CMainWindow * _pmwMainWindow ) {
		lsn::CLayoutManager * plmLayout = static_cast<lsn::CLayoutManager *>(lsw::CBase::LayoutManager());
		CInputPage::SBN_CONTROLLER_SETUP_DATA csdData = {
			.poOptions = &_oOptions,
			.pmwMainWindow = _pmwMainWindow,
		};
		CWidget * pwWidget = plmLayout->CreateDialogX( _pwlLayout, _sTotal, _pwParent, reinterpret_cast<uint64_t>(&csdData) );
		if ( pwWidget ) {
			// Success.  Do stuff.
		}
		return pwWidget;
	}

}	// namespace sbn

#endif	// #ifdef SBN_USE_WINDOWS
