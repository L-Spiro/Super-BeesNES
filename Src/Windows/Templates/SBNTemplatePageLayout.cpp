#ifdef SBN_USE_WINDOWS

/**
 * Copyright L. Spiro 2023
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A layout template for "pages" (self-contained borderless dialogs meant for embedding into other dialogs).
 */

#include "SBNTemplatePageLayout.h"
#include "../../Localization/SBNLocalization.h"
#include "../Layout/SBNLayoutMacros.h"
#include "../Layout/SBNLayoutManager.h"



namespace sbn {

#define SBN_TEMPLATE_W									(SBN_LEFT_JUST + SBN_LEFT_JUST + 200 + SBN_LEFT_JUST + SBN_LEFT_JUST)
#define SBN_TEMPLATE_H									(50 + 150 + 20)

	// == Members.
	/** The layout for the template window. */
	LSW_WIDGET_LAYOUT CTemplatePageLayout::m_wlPage[] = {
		{
			SBN_LT_INPUT_DIALOG,					// ltType
			SBN_TWI_MAINWINDOW,						// wId
			nullptr,								// lpwcClass
			TRUE,									// bEnabled
			FALSE,									// bActive
			0,										// iLeft
			0,										// iTop
			SBN_TEMPLATE_W,							// dwWidth
			SBN_TEMPLATE_H,							// dwHeight
			WS_CHILDWINDOW | WS_VISIBLE | DS_3DLOOK | DS_FIXEDSYS | DS_SETFONT | DS_CONTROL,										// dwStyle
			WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_CONTROLPARENT,												// dwStyleEx
			nullptr,								// pwcText
			0,										// sTextLen
			SBN_TWI_NONE,							// dwParentId

			SBN_PARENT_VCLEFT,						// pcLeftSizeExp
			nullptr, 0,								// pcRightSizeExp
			SBN_PARENT_VCTOP,						// pcTopSizeExp
			nullptr, 0,								// pcBottomSizeExp
			SBN_FIXED_WIDTH,						// pcWidthSizeExp
			SBN_FIXED_HEIGHT,						// pcHeightSizeExp
		},
	};

#undef SBN_TEMPLATE_H
#undef SBN_TEMPLATE_W


	// == Functions.
	/**
	 * Creates the page.
	 *
	 * \param _pwParent the parent of the page.
	 * \return Returns the created widget.
	 */
	CWidget * CTemplatePageLayout::CreatePage( CWidget * _pwParent ) {
		return CreatePage( _pwParent, m_wlPage, SBN_ELEMENTS( m_wlPage ) );
	}

	/**
	 * Creates the tab pages.
	 *
	 * \param _pwParent The parent widget.
	 * \param _pwlLayout The page layout.
	 * \param _sTotal The number of items to which _pwlLayout points.
	 * \return Returns the created page.
	 */
	CWidget * CTemplatePageLayout::CreatePage( CWidget * _pwParent, const LSW_WIDGET_LAYOUT * _pwlLayout, size_t _sTotal ) {
		lsn::CLayoutManager * plmLayout = static_cast<lsn::CLayoutManager *>(lsw::CBase::LayoutManager());
		CWidget * pwWidget = plmLayout->CreateDialogX( _pwlLayout, _sTotal, _pwParent, 0 );
		if ( pwWidget ) {
			// Success.  Do stuff.
		}
		return pwWidget;
	}

}	// namespace sbn

#endif	// #ifdef SBN_USE_WINDOWS
