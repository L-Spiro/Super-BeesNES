#ifdef SBN_USE_WINDOWS

/**
 * Copyright L. Spiro 2024
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: Utility functions relating to the OS.
 */

#include "SBNWinUtilities.h"
#include "../../Localization/SBNLocalization.h"

namespace sbn {

	/**
	 * Fills a combo box with console types (Nintendo Entertainment System(R) and Famicom(R)).
	 *
	 * \param _pwComboBox The combo box to fill.
	 * \param _lpDefaultSelect The default selection.
	 * \return Returns true if the combo box will filled.  _pwComboBox must not be nullptr, must be of type CComboBox, and the adding of each item must succeed.
	 */
	bool CWinUtilities::FillComboWithConsoleTypes( CWidget * _pwComboBox, LPARAM _lpDefaultSelect ) {
		SBN_COMBO_ENTRY ceEnries[] = {
			//pwcName													lpParm
			{ SBN_LSTR( SBN_NES ),										SBN_CT_NES,					},
			{ SBN_LSTR( SBN_FAMICOM ),									SBN_CT_FAMICOM,				},
		};
		return FillComboBox( _pwComboBox, ceEnries, SBN_ELEMENTS( ceEnries ), _lpDefaultSelect, SBN_CT_NES );
	}

	/**
	 * Fills a combo box with Famicom(R) controller types (Standard Controller only).
	 *
	 * \param _pwComboBox The combo box to fill.
	 * \return Returns true if the combo box will filled.  _pwComboBox must not be nullptr, must be of type CComboBox, and the adding of each item must succeed.
	 */
	bool CWinUtilities::FillComboWithControllerType_Famicom( CWidget * _pwComboBox ) {
		SBN_COMBO_ENTRY ceEnries[] = {
			//pwcName													lpParm
			{ SBN_LSTR( SBN_INPUT_STANDARD_CONTROLLER ),				SBN_CT_STANDARD,			},
		};
		return FillComboBox( _pwComboBox, ceEnries, SBN_ELEMENTS( ceEnries ), SBN_CT_STANDARD );
	}

	/**
	 * Fills a combo box with Nintendo Entertainment System(R) controller types.
	 *
	 * \param _pwComboBox The combo box to fill.
	 * \param _lpDefaultSelect The default selection.
	 * \param _lpSelectBackup The backup selection in case the default selection isn't in the list.
	 * \return Returns true if the combo box will filled.  _pwComboBox must not be nullptr, must be of type CComboBox, and the adding of each item must succeed.
	 */
	bool CWinUtilities::FillComboWithControllerType_NES( CWidget * _pwComboBox, LPARAM _lpDefaultSelect, LPARAM _lpSelectBackup ) {
		SBN_COMBO_ENTRY ceEnries[] = {
			//pwcName													lpParm
			{ SBN_LSTR( SBN_INPUT_NONE ),								SBN_CT_NONE,				},
			{ SBN_LSTR( SBN_INPUT_STANDARD_CONTROLLER ),				SBN_CT_STANDARD,			},
		};
		return FillComboBox( _pwComboBox, ceEnries, SBN_ELEMENTS( ceEnries ), _lpDefaultSelect, _lpSelectBackup );
	}

	/**
	 * Fills a combo box with Nintendo Entertainment System(R) Four Score expansion types.
	 *
	 * \param _pwComboBox The combo box to fill.
	 * \param _lpDefaultSelect The default selection.
	 * \param _lpSelectBackup The backup selection in case the default selection isn't in the list.
	 * \return Returns true if the combo box will filled.  _pwComboBox must not be nullptr, must be of type CComboBox, and the adding of each item must succeed.
	 */
	bool CWinUtilities::FillComboWithControllerType_FourScore( CWidget * _pwComboBox, LPARAM _lpDefaultSelect, LPARAM _lpSelectBackup ) {
		SBN_COMBO_ENTRY ceEnries[] = {
			//pwcName													lpParm
			{ SBN_LSTR( SBN_INPUT_NONE ),								SBN_CT_NONE,				},
			{ SBN_LSTR( SBN_INPUT_STANDARD_CONTROLLER ),				SBN_CT_STANDARD,			},
			/*{ SBN_LSTR( SBN_INPUT_SNES_MOUSE ),							SBN_CT_SNES_MOUSE,			},
			{ SBN_LSTR( SBN_INPUT_SUBOR_MOUSE ),						SBN_CT_SUBOR_MOUSE,			},*/
		};
		return FillComboBox( _pwComboBox, ceEnries, SBN_ELEMENTS( ceEnries ), _lpDefaultSelect, _lpSelectBackup );
	}

	/**
	 * Fills a combo box with Famicom(R) expansion types.
	 *
	 * \param _pwComboBox The combo box to fill.
	 * \param _lpDefaultSelect The default selection.
	 * \param _lpSelectBackup The backup selection in case the default selection isn't in the list.
	 * \return Returns true if the combo box will filled.  _pwComboBox must not be nullptr, must be of type CComboBox, and the adding of each item must succeed.
	 */
	bool CWinUtilities::FillComboWithExpansion_Famicom( CWidget * _pwComboBox, LPARAM _lpDefaultSelect ) {
		SBN_COMBO_ENTRY ceEnries[] = {
			//pwcName													lpParm
			{ SBN_LSTR( SBN_INPUT_NONE ),								SBN_CT_NONE,								},
			{ SBN_LSTR( SBN_INPUT_ARKANOID_CONTROLLER ),				SBN_CT_ARKANOID,							},
			{ SBN_LSTR( SBN_INPUT_BANDAI_HYPER_SHOT ),					SBN_CT_BANDAI_HYPERSHOT,					},
			{ SBN_LSTR( SBN_INPUT_BARCODE_BATTLER ),					SBN_CT_BARCODE_BATTLER,						},
			{ SBN_LSTR( SBN_INPUT_BATTLE_BOX ),							SBN_CT_BATTLE_BOX,							},
			{ SBN_LSTR( SBN_INPUT_EXCITING_BOXING_PUNCHING_BAG ),		SBN_CT_EXCITING_BOXING_PUNCHING_BAG,		},
			{ SBN_LSTR( SBN_INPUT_FAMILY_BASIC_KEYBOARD ),				SBN_CT_FAMILY_BASIC_KEYBOARD,				},
			{ SBN_LSTR( SBN_INPUT_FAMILY_TRAINER ),						SBN_CT_FAMILY_TRAINER,						},
			{ SBN_LSTR( SBN_INPUT_4_PLAYER_ADAPTOR ),					SBN_CT_FOUR_PLAYER_ADAPTER,					},
			{ SBN_LSTR( SBN_INPUT_HORI_TRACK ),							SBN_CT_HORI_TRACK,							},
			{ SBN_LSTR( SBN_INPUT_JISSEN_MAHJONG_CONTROLLER ),			SBN_CT_JISSEN_MAHJONG_CONTROLLER,			},
			{ SBN_LSTR( SBN_INPUT_KONAMI_HYPER_SHOT ),					SBN_CT_KONAMI_HYPER_SHOT,					},
			{ SBN_LSTR( SBN_INPUT_OEKA_KIDS_TABLET ),					SBN_CT_OEKA_KIDS_TABLET,					},
			{ SBN_LSTR( SBN_INPUT_PACHINKO_CONTROLLER ),				SBN_CT_PACHINKO_CONTROLLER,					},
			{ SBN_LSTR( SBN_INPUT_PARTYTAP ),							SBN_CT_PARTYTAP,							},
			{ SBN_LSTR( SBN_INPUT_SUBOR_KEYBOARD ),						SBN_CT_SUBOR_KEYBOARD,						},
			{ SBN_LSTR( SBN_INPUT_TURBO_FILE ),							SBN_CT_TURBO_FILE,							},
			{ SBN_LSTR( SBN_INPUT_ZAPPER ),								SBN_CT_ZAPPER,								},
		};
		return FillComboBox( _pwComboBox, ceEnries, SBN_ELEMENTS( ceEnries ), _lpDefaultSelect, SBN_CT_NONE );
	}

	/**
	 * Fills a combo box with the given array of SBN_COMBO_ENTRY structures.
	 *
	 * \param _pwComboBox The combo box to fill.
	 * \param _pceEntries The array of combo-box entries.
	 * \param _stTotal The total number of entries to which _pceEntries points.
	 * \param _lpDefaultSelect The default selection.
	 * \param _lpSelectBackup The backup selection in case the default selection isn't in the list.
	 * \return Returns true if _pwComboBox is not nullptr, it is of type CComboBox, and all entries were added.
	 */
	bool CWinUtilities::FillComboBox( CWidget * _pwComboBox, const SBN_COMBO_ENTRY * _pceEntries, size_t _stTotal, LPARAM _lpDefaultSelect, LPARAM _lpSelectBackup ) {
		if ( nullptr == _pwComboBox ) { return false; }
		if ( !_pwComboBox->IsComboBox() ) { return false; }

		CComboBox * pcbBox = static_cast<CComboBox *>(_pwComboBox);
		pcbBox->ResetContent();
		for ( size_t I = 0; I < _stTotal; ++I ) {
			INT iIdx = pcbBox->AddString( _pceEntries[I].pwcName );
			if ( CB_ERR == iIdx ) { return false; }
			if ( CB_ERR == pcbBox->SetItemData( iIdx, _pceEntries[I].lpParm ) ) { return false; }
		}
		if ( CB_ERR == pcbBox->SetCurSelByItemData( _lpDefaultSelect ) ) {
			pcbBox->SetCurSelByItemData( _lpSelectBackup );
		}
		pcbBox->AutoSetMinListWidth();

		return true;
	}

	/**
	 * Writes a UI key to a stream.
	 * 
	 * \param _kKey The key values to write.
	 * \param _sStream The stream to which to write the key values.
	 * \return Returns true if writing of the key information to the stream succeeded.
	 **/
	bool CWinUtilities::WriteUiKey( const lsw::LSW_KEY &_kKey, lsn::CStream &_sStream ) {
		if ( !_sStream.Write( _kKey.dwScanCode ) ) { return false; }
		if ( !_sStream.WriteUi8( _kKey.bKeyCode ) ) { return false; }
		if ( !_sStream.WriteUi8( _kKey.bKeyModifier ) ) { return false; }
		return true;
	}

	/**
	 * Reads a UI key from a stream.
	 * 
	 * \param _kKey The key values to be filled by reading from the givens tream.
	 * \param _sStream The stream from which to read the key values.
	 * \return Returns true if reading of the key information from the stream succeeded.
	 **/
	bool CWinUtilities::ReadUiKey( lsw::LSW_KEY &_kKey, lsn::CStream &_sStream ) {
		if ( !_sStream.Read( _kKey.dwScanCode ) ) { return false; }
		if ( !_sStream.ReadUi8( _kKey.bKeyCode ) ) { return false; }
		if ( !_sStream.ReadUi8( _kKey.bKeyModifier ) ) { return false; }
		return true;
	}

}	// namespace sbn

#endif	// #ifdef SBN_USE_WINDOWS
