#ifdef SBN_USE_WINDOWS

/**
 * Copyright L. Spiro 2023
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A dialog shaped like a standard controller.
 */

#include "SBNStdControllerPageLayout.h"
#include "../../Localization/SBNLocalization.h"
#include "../Input/SBNStdControllerPage.h"
#include "../Layout/SBNLayoutMacros.h"
#include "../Layout/SBNLayoutManager.h"



namespace sbn {

	// == Members.
	/** The layout for the template window. */
	LSW_WIDGET_LAYOUT CStdControllerPageLayout::m_wlPage[] = {
		{
			SBN_LT_STD_CONTROLLER_PAGE,				// ltType
			SBN_SCPI_MAINWINDOW,					// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			0,										// iLeft
			0,										// iTop
			SBN_STD_CONT_W,							// dwWidth
			SBN_STD_CONT_H,							// dwHeight
			WS_CHILDWINDOW | WS_VISIBLE | DS_3DLOOK | DS_FIXEDSYS | DS_SETFONT | DS_CONTROL,										// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_CONTROLPARENT,												// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_SCPI_NONE,							// dwParentId

			/*SBN_PARENT_VCLEFT,						// pcLeftSizeExp
			nullptr, 0,								// pcRightSizeExp
			SBN_PARENT_VCTOP,						// pcTopSizeExp
			nullptr, 0,								// pcBottomSizeExp
			SBN_FIXED_WIDTH,						// pcWidthSizeExp
			SBN_FIXED_HEIGHT,*/						// pcHeightSizeExp
		},
#define SBN_QUICK_CONTR( TYPE_, ID_, TEXT_, X_, Y_, W_, H_, STYLE_, STYLEEX_ )																		\
	{																																				\
		TYPE_,																																		\
		ID_,																																		\
		nullptr,																																	\
		TRUE,																																		\
		FALSE,																																		\
		X_,																																			\
		Y_,																																			\
		W_,																																			\
		H_,																																			\
		STYLE_,																																		\
		STYLEEX_,																																	\
		TEXT_,																																		\
		0,																																			\
		SBN_SCPI_MAINWINDOW,																														\
	},


#define SBN_QUICK_BUTTON( BUTTON_, TEXT_, X_, Y_ )																																				\
	SBN_QUICK_CONTR( LSW_LT_GROUPBOX, BUTTON_ + SBN_SCPI_GROUP, TEXT_, (X_), (Y_),																												\
		SBN_STD_CONT_BUTTON_GROUP_W, SBN_STD_CONT_BUTTON_GROUP_H, SBN_GROUPSTYLE, WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY )									\
	SBN_QUICK_CONTR( LSW_LT_LABEL, BUTTON_ + SBN_SCPI_LABEL, SBN_LSTR( SBN_BUTTON_ ), (X_) + SBN_GROUP_LEFT, (Y_) + SBN_GROUP_TOP + (SBN_DEF_BUTTON_HEIGHT - SBN_DEF_STATIC_HEIGHT) / 2,		\
		SBN_STD_CONT_BUTTON_LABEL_W, SBN_DEF_STATIC_HEIGHT, SBN_STATICSTYLE, 0 )																												\
	SBN_QUICK_CONTR( LSW_LT_BUTTON, BUTTON_ + SBN_SCPI_BUTTON, nullptr,																															\
		(X_) + SBN_GROUP_LEFT + SBN_STD_CONT_BUTTON_LABEL_W, (Y_) + SBN_GROUP_TOP,																												\
		SBN_STD_CONT_BUTTON_BUTTON_W, SBN_DEF_BUTTON_HEIGHT, SBN_BUTTONSTYLE, WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY )										\
	SBN_QUICK_CONTR( LSW_LT_LABEL, BUTTON_ + SBN_SCPI_TURBO_LABEL, SBN_LSTR( SBN_TURBO_ ),																										\
		(X_) + SBN_GROUP_LEFT, (Y_) + SBN_GROUP_TOP + (SBN_DEF_BUTTON_HEIGHT - SBN_DEF_STATIC_HEIGHT) / 2 + SBN_DEF_BUTTON_HEIGHT + 1,															\
		SBN_STD_CONT_BUTTON_LABEL_W, SBN_DEF_STATIC_HEIGHT, SBN_STATICSTYLE, 0 )																												\
	SBN_QUICK_CONTR( LSW_LT_BUTTON, BUTTON_ + SBN_SCPI_TURBO_BUTTON, nullptr,																													\
		(X_) + SBN_GROUP_LEFT + SBN_STD_CONT_BUTTON_LABEL_W, (Y_) + SBN_GROUP_TOP + SBN_DEF_BUTTON_HEIGHT + 1,																					\
		SBN_STD_CONT_BUTTON_BUTTON_W, SBN_DEF_BUTTON_HEIGHT, SBN_BUTTONSTYLE, WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY )										\
	SBN_QUICK_CONTR( LSW_LT_COMBOBOX, BUTTON_ + SBN_SCPI_TURBO_COMBO, nullptr,																													\
		(X_) + SBN_GROUP_LEFT, (Y_) + SBN_GROUP_TOP + SBN_DEF_BUTTON_HEIGHT * 2 + 2,																											\
		SBN_STD_CONT_BUTTON_FULL_W, SBN_DEF_COMBO_HEIGHT, SBN_COMBOSTYLE_LIST, SBN_COMBOSTYLEEX_LIST )																							\
	SBN_QUICK_CONTR( LSW_LT_LABEL, BUTTON_ + SBN_SCPI_TURBO_DEADZONE_LABEL, SBN_LSTR( SBN_DEAD_ ),																								\
		(X_) + SBN_GROUP_LEFT, (Y_) + SBN_GROUP_TOP + (SBN_DEF_TRACKBAR_HEIGHT - SBN_DEF_STATIC_HEIGHT) / 2 + SBN_DEF_BUTTON_HEIGHT * 2 + SBN_DEF_COMBO_HEIGHT + 3,								\
		SBN_STD_CONT_BUTTON_LABEL_W, SBN_DEF_STATIC_HEIGHT, SBN_STATICSTYLE, 0 )																												\
	SBN_QUICK_CONTR( LSW_LT_TRACKBAR, BUTTON_ + SBN_SCPI_TURBO_DEADZONE_TRACKBAR, nullptr,																										\
		(X_) + SBN_GROUP_LEFT + SBN_STD_CONT_BUTTON_LABEL_W, (Y_) + SBN_GROUP_TOP + SBN_DEF_BUTTON_HEIGHT * 2 + SBN_DEF_COMBO_HEIGHT + 3,														\
		SBN_STD_CONT_BUTTON_BUTTON_W, SBN_DEF_TRACKBAR_HEIGHT, SBN_TRACKBAR_STYLE, 0 )

		// Buttons.
		SBN_QUICK_CONTR( LSW_LT_GROUPBOX, SBN_SCPI_DPAD_GROUP, SBN_LSTR( SBN_DIRECTIONAL_PAD ), SBN_STD_CONT_DPAD_LEFT, SBN_STD_CONT_DPAD_TOP,
			SBN_STD_CONT_DPAD_GROUP_W, SBN_STD_CONT_DPAD_GROUP_H, SBN_GROUPSTYLE, WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY )
		SBN_QUICK_BUTTON( SBN_SCPI_BUTTON_UP_START, SBN_LSTR( SBN_BUTTON_UP ), SBN_STD_CONT_DPAD_LEFT + SBN_STD_CONT_DPAD_H_MIDDLE - SBN_STD_CONT_BUTTON_GROUP_W / 2 + SBN_GROUP_LEFT,
			SBN_STD_CONT_DPAD_TOP + SBN_GROUP_TOP )
		SBN_QUICK_BUTTON( SBN_SCPI_BUTTON_LEFT_START, SBN_LSTR( SBN_BUTTON_LEFT ), SBN_STD_CONT_DPAD_LEFT + SBN_GROUP_LEFT,
			SBN_STD_CONT_DPAD_TOP + SBN_STD_CONT_DPAD_V_MIDDLE - SBN_STD_CONT_BUTTON_GROUP_H / 2 + SBN_GROUP_TOP )
		SBN_QUICK_BUTTON( SBN_SCPI_BUTTON_RIGHT_START, SBN_LSTR( SBN_BUTTON_RIGHT ), SBN_STD_CONT_DPAD_LEFT + SBN_STD_CONT_DPAD_W - SBN_STD_CONT_BUTTON_GROUP_W + SBN_GROUP_LEFT,
			SBN_STD_CONT_DPAD_TOP + SBN_STD_CONT_DPAD_V_MIDDLE - SBN_STD_CONT_BUTTON_GROUP_H / 2 + SBN_GROUP_TOP )
		SBN_QUICK_BUTTON( SBN_SCPI_BUTTON_DOWN_START, SBN_LSTR( SBN_BUTTON_DOWN ), SBN_STD_CONT_DPAD_LEFT + SBN_STD_CONT_DPAD_H_MIDDLE - SBN_STD_CONT_BUTTON_GROUP_W / 2 + SBN_GROUP_LEFT,
			SBN_STD_CONT_DPAD_TOP + SBN_STD_CONT_DPAD_H - SBN_STD_CONT_BUTTON_GROUP_H + SBN_GROUP_TOP )

		SBN_QUICK_CONTR( LSW_LT_GROUPBOX, SBN_SCPI_SS_GROUP, SBN_LSTR( SBN_SELECT_START ), SBN_STD_CONT_SS_LEFT, SBN_STD_CONT_SS_TOP,
			SBN_STD_CONT_SS_GROUP_W, SBN_STD_CONT_SS_GROUP_H, SBN_GROUPSTYLE, WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY )
		SBN_QUICK_BUTTON( SBN_SCPI_BUTTON_SELECT_START, SBN_LSTR( SBN_BUTTON_SELECT ), SBN_STD_CONT_SS_LEFT + SBN_GROUP_LEFT,
			SBN_STD_CONT_SS_TOP + SBN_GROUP_TOP )
		SBN_QUICK_BUTTON( SBN_SCPI_BUTTON_START_START, SBN_LSTR( SBN_BUTTON_START ), SBN_STD_CONT_SS_LEFT + SBN_GROUP_LEFT + SBN_STD_CONT_SS_START_LEFT,
			SBN_STD_CONT_SS_TOP + SBN_GROUP_TOP )

		SBN_QUICK_CONTR( LSW_LT_GROUPBOX, SBN_SCPI_BUTTON_GROUP, SBN_LSTR( SBN_BUTTONS ), SBN_STD_CONT_BUT_LEFT, SBN_STD_CONT_BUT_TOP,
			SBN_STD_CONT_BUT_GROUP_W, SBN_STD_CONT_BUT_GROUP_H, SBN_GROUPSTYLE, WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_NOPARENTNOTIFY )
		SBN_QUICK_BUTTON( SBN_SCPI_BUTTON_B_START, SBN_LSTR( SBN_BUTTON_B ), SBN_STD_CONT_BUT_LEFT + SBN_GROUP_LEFT,
			SBN_STD_CONT_BUT_TOP + SBN_GROUP_TOP )
		SBN_QUICK_BUTTON( SBN_SCPI_BUTTON_A_START, SBN_LSTR( SBN_BUTTON_A ), SBN_STD_CONT_BUT_LEFT + SBN_GROUP_LEFT + SBN_STD_CONT_BUT_A_LEFT,
			SBN_STD_CONT_BUT_TOP + SBN_GROUP_TOP )


#undef SBN_QUICK_BUTTON
#undef SBN_QUICK_CONTR
	};

#undef SBN_STD_CONT_H
#undef SBN_STD_CONT_W


	// == Functions.
	/**
	 * Creates the page.
	 *
	 * \param _pwParent The parent of the page.
	 * \param _ioOptions The input options to potentially modify.
	 * \param _pmwMainWindow A pointer to the main window for USB controller access.
	 * \param _stIdx The page's configuration index.
	 * \return Returns the created widget.
	 */
	CWidget * CStdControllerPageLayout::CreatePage( CWidget * _pwParent, SBN_INPUT_OPTIONS &_ioOptions, lsn::CMainWindow * _pmwMainWindow, size_t _stIdx ) {
		return CreatePage( _pwParent, _ioOptions, _pmwMainWindow, _stIdx, m_wlPage, SBN_ELEMENTS( m_wlPage ) );
	}

	/**
	 * Creates the tab pages.
	 *
	 * \param _pwParent The parent widget.
	 * \param _ioOptions The input options to potentially modify.
	 * \param _pmwMainWindow A pointer to the main window for USB controller access.
	 * \param _stIdx The page's configuration index.
	 * \param _pwlLayout The page layout.
	 * \param _sTotal The number of items to which _pwlLayout points.
	 * \return Returns the created page.
	 */
	CWidget * CStdControllerPageLayout::CreatePage( CWidget * _pwParent, SBN_INPUT_OPTIONS &_ioOptions, lsn::CMainWindow * _pmwMainWindow, size_t _stIdx, const LSW_WIDGET_LAYOUT * _pwlLayout, size_t _sTotal ) {
		lsn::CLayoutManager * plmLayout = static_cast<lsn::CLayoutManager *>(lsw::CBase::LayoutManager());
		CStdControllerPage::SBN_CONTROLLER_SETUP_DATA scdData = {
			.pioOptions = &_ioOptions,
			.pmwMainWindow = _pmwMainWindow,
			.stConfigureIdx = _stIdx
		};
		CWidget * pwWidget = plmLayout->CreateDialogX( _pwlLayout, _sTotal, _pwParent, reinterpret_cast<uint64_t>(&scdData) );
		if ( pwWidget ) {
			// Success.  Do stuff.
		}
		return pwWidget;
	}

}	// namespace sbn

#endif	// #ifdef SBN_USE_WINDOWS
