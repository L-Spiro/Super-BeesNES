#define SBN_INDIRECT_X_R( NAME, FUNC )												{ {	&CCpu65816::FetchPointerAndIncPc_Phi2, &CCpu65816::AddXAndDAndPointerToAddressAndIncPc, &CCpu65816::SkipOnDL_Phi2, &CCpu65816::FixPointerHigh, &CCpu65816::Null_Phi2, &CCpu65816::ReadPointerToAddressLow, &CCpu65816::ReadPointerToAddressLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerToAddressHigh_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressAndBankToOperandLow_SkipIfM_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressAndBankToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, {	&CCpu65816::FetchPointerAndIncPc_Phi2, &CCpu65816::AddXAndDAndPointerToAddressAndIncPc, &CCpu65816::SkipOnDL_Phi2, &CCpu65816::FixPointerHigh, &CCpu65816::Null_Phi2, &CCpu65816::ReadPointerToAddressLow, &CCpu65816::ReadPointerToAddressLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerToAddressHigh_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressAndBankToOperandLow_SkipIfM_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressAndBankToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, }, 8, 7, SBN_AM_INDIRECT_X, 2, 2, SBN_I_ ## NAME

#define SBN_STACK_RELATIVE_R( NAME, FUNC )											{ { &CCpu65816::FetchPointerAndIncPc_Phi2, &CCpu65816::AddStackOffsetAndIncPc, &CCpu65816::Null_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadStackOffsetLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadStackOffsetHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, { &CCpu65816::FetchPointerAndIncPc_Phi2, &CCpu65816::AddStackOffsetAndIncPc, &CCpu65816::Null_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadStackOffsetLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadStackOffsetHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, }, 5, 5, SBN_AM_STACK_RELATIVE, 2, 2, SBN_I_ ## NAME

#define SBN_STACK_RELATIVE_INDIRECT_INDEXED_Y( NAME, FUNC )							{ { &CCpu65816::FetchPointerAndIncPc_Phi2, &CCpu65816::AddStackOffsetAndIncPc, &CCpu65816::Null_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerHigh_Phi2, &CCpu65816::AddYToPointerWithBankOverflowAndPageSkip, &CCpu65816::Null_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_SkipIfM_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, { &CCpu65816::FetchPointerAndIncPc_Phi2, &CCpu65816::AddStackOffsetAndIncPc, &CCpu65816::Null_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerHigh_Phi2, &CCpu65816::AddYToPointerWithBankOverflowAndPageSkip, &CCpu65816::Null_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, }, 8, 7, SBN_AM_STACK_RELATIVE_INDIRECT_INDEXED_Y, 2, 2, SBN_I_ ## NAME

#define SBN_DIRECT_PAGE_R( NAME, FUNC )												{ { &CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2, &CCpu65816::Null_Write, &CCpu65816::Null_Phi2, &CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToOperandLow_SkipIfM_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp, }, { &CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2, &CCpu65816::Null_Write, &CCpu65816::Null_Phi2, &CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToOperandLow_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp, }, }, 5, 4, SBN_AM_DIRECT_PAGE, 2, 2, SBN_I_ ## NAME
#define SBN_DIRECT_PAGE_RMW( NAME, FUNC )											{ { &CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2, &CCpu65816::Null_Write, &CCpu65816::Null_Phi2, &CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToOperandLow_SkipIfM_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::SkipIfM_Phi2, &CCpu65816::Null_Write, &CCpu65816::WriteOperandHighToAddress_Phi2, &CCpu65816::Null_Write, &CCpu65816::WriteOperandLowToAddress_Phi2, &CCpu65816::Null_Read, &CCpu65816::PrefetchNextOp, }, { &CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2, &CCpu65816::Null_Write, &CCpu65816::Null_Phi2, &CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToOperandLow_Phi2, &CCpu65816::Null_Write, &CCpu65816::WriteOperandLowToAddress_Phi2, &CCpu65816::FUNC, &CCpu65816::WriteOperandLowToAddress_Phi2, &CCpu65816::Null_Read, &CCpu65816::PrefetchNextOp, }, }, 8, 6, SBN_AM_DIRECT_PAGE, 2, 2, SBN_I_## NAME

#define SBN_DIRECT_PAGE_INDEXED_X_R( NAME, FUNC )									{ { &CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2, &CCpu65816::Null_Write, &CCpu65816::Null_Phi2, &CCpu65816::AddDAndOperandAndXToAddressAndIncPc, &CCpu65816::ReadAddressToOperandLow_SkipIfM_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp, }, { &CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2,&CCpu65816::Null_Write, &CCpu65816::Null_Phi2, &CCpu65816::AddDAndOperandAndXToAddressAndIncPc, &CCpu65816::ReadAddressToOperandLow_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp, }, }, 5, 4, SBN_AM_DIRECT_PAGE_INDEXED_X, 2, 2, SBN_I_ ## NAME
#define SBN_DIRECT_PAGE_INDEXED_X_RMW( NAME, FUNC )									{ { &CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2, &CCpu65816::Null_Write, &CCpu65816::Null_Phi2, &CCpu65816::Null_Write, &CCpu65816::Null_Phi2, &CCpu65816::AddDAndOperandAndXToAddressAndIncPc, &CCpu65816::ReadAddressToOperandLow_SkipIfM_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::Null_SkipIfM, &CCpu65816::Null_Write, &CCpu65816::WriteOperandHighToAddress_Phi2, &CCpu65816::Null_Write, &CCpu65816::WriteOperandLowToAddress_Phi2, &CCpu65816::Null_Write, &CCpu65816::PrefetchNextOp, }, { &CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2, &CCpu65816::Null_Write, &CCpu65816::Null_Phi2, &CCpu65816::Null_Write, &CCpu65816::Null_Phi2, &CCpu65816::AddDAndOperandAndXToAddressAndIncPc, &CCpu65816::ReadAddressToOperandLow_Phi2, &CCpu65816::FUNC, &CCpu65816::Null_Phi2, &CCpu65816::Null_Write, &CCpu65816::WriteOperandLowToAddress_Phi2, &CCpu65816::Null_Write, &CCpu65816::PrefetchNextOp, }, }, 9, 7, SBN_AM_DIRECT_PAGE_INDEXED_X, 2, 2, SBN_I_ ## NAME

#define SBN_DIRECT_PAGE_INDIRECT_R( NAME, FUNC )									{ { &CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2, &CCpu65816::Null_Read, &CCpu65816::Null_Phi2, &CCpu65816::AddDAndOperandToPointerAndIncPc, &CCpu65816::ReadPointerToAddressLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerToAddressHigh_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressAndBankToOperandLow_SkipIfM_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressAndBankToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, { &CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2, &CCpu65816::Null_Read, &CCpu65816::Null_Phi2, &CCpu65816::AddDAndOperandToPointerAndIncPc, &CCpu65816::ReadPointerToAddressLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerToAddressHigh_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressAndBankToOperandLow_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, }, 7, 6, SBN_AM_DIRECT_PAGE_INDIRECT, 2, 2, SBN_I_ ## NAME

#define SBN_DIRECT_PAGE_INDIRECT_LONG_R( NAME, FUNC )								{ { &CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2, &CCpu65816::Null_Write, &CCpu65816::Null_Phi2, &CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToPointerLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerHigh_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToBankLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_SkipIfM_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp, }, { &CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2, &CCpu65816::Null_Write, &CCpu65816::Null_Phi2, &CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToPointerLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerHigh_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToBankLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp, }, }, 8, 7, SBN_AM_DIRECT_PAGE_INDIRECT_LONG, 2, 2, SBN_I_ ## NAME

#define SBN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( NAME, FUNC )							{ { &CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2, &CCpu65816::Null_Read, &CCpu65816::Null_Phi2, &CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToPointerLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerHigh_Phi2, &CCpu65816::AddYToPointerWithBankOverflowAndPageSkip, &CCpu65816::Null_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_SkipIfM_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, { &CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2, &CCpu65816::Null_Read, &CCpu65816::Null_Phi2, &CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToPointerLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerHigh_Phi2, &CCpu65816::AddYToPointerWithBankOverflowAndPageSkip, &CCpu65816::Null_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, }, 8, 7, SBN_AM_DIRECT_PAGE_INDIRECT_INDEXED_Y, 2, 2, SBN_I_ ## NAME

#define SBN_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y_R( NAME, FUNC )						{ { &CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2, &CCpu65816::Null_Write, &CCpu65816::Null_Phi2, &CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToPointerLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerHigh_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToBankLow_Phi2, &CCpu65816::AddYToPointerWithBankOverflow, &CCpu65816::ReadPointerAndBankToOperandLow_SkipIfM_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp, }, { &CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2, &CCpu65816::Null_Write, &CCpu65816::Null_Phi2, &CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToPointerLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerHigh_WithLowByteWrap_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressToBankLow_WithLowByteWrap_Phi2, &CCpu65816::AddYToPointerWithBankOverflow, &CCpu65816::ReadPointerAndBankToOperandLow_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp, }, }, 8, 7, SBN_AM_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y, 2, 2, SBN_I_ ## NAME

#define LSN_IMMEDIATE( NAME, FUNC )													{ { &CCpu65816::FetchOperandLowAndIncPc_SkipIfM_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::FetchOperandHighAndIncPc_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, { &CCpu65816::FetchOperandAndIncPc_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, }, 3, 2, SBN_AM_IMMEDIATE, 3, 2, SBN_I_ ## NAME

#define SBN_ABSOLUTE_R( NAME, FUNC )												{ { &CCpu65816::FetchAddressAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::FetchAddressHighAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::ReadAddressAndBankToOperandLow_SkipIfM_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::ReadAddressAndBankToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, { &CCpu65816::FetchAddressAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::FetchAddressHighAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::ReadAddressAndBankToOperandLow_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, }, 5, 4, SBN_AM_ABSOLUTE, 3, 3, SBN_I_ ## NAME
#define SBN_ABSOLUTE_RMW( NAME, FUNC )												{ { &CCpu65816::FetchAddressAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::FetchAddressHighAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::ReadAddressAndBankToOperandLow_SkipIfM_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::ReadAddressAndBankToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::Null_SkipIfM, &CCpu65816::Null_Write, &CCpu65816::WriteOperandHighToAddressAndBank_Phi2, &CCpu65816::Null_Write, &CCpu65816::WriteOperandLowToAddressAndBank_Phi2, &CCpu65816::Null_Read, &CCpu65816::PrefetchNextOp }, { &CCpu65816::FetchAddressAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::FetchAddressHighAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::ReadAddressAndBankToOperandLow_Phi2, &CCpu65816::Null_Write, &CCpu65816::WriteOperandLowToAddressAndBank_Phi2, &CCpu65816::FUNC, &CCpu65816::WriteOperandLowToAddressAndBank_Phi2, &CCpu65816::Null_Read, &CCpu65816::PrefetchNextOp }, }, 8, 6, SBN_AM_ABSOLUTE, 3, 3, SBN_I_ ## NAME

#define SBN_ABSOLUTE_LONG_R( NAME, FUNC )											{ { &CCpu65816::FetchPointerAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::FetchPointerHighAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::FetchBankhAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::ReadPointerAndBankToOperandLow_SkipIfM_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, { &CCpu65816::FetchPointerAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::FetchPointerHighAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::FetchBankhAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::ReadPointerAndBankToOperandLow_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, }, 6, 5, SBN_AM_ABSOLUTE_LONG, 4, 4, SBN_I_ ## NAME

#define SBN_ABSOLUTE_INDEXED_X_R( NAME, FUNC )										{ { &CCpu65816::FetchPointerAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::FetchPointerHighAndIncPc_Phi2, &CCpu65816::AddXToPointerWithBankOverflowAndPageSkipAndIncPc, &CCpu65816::Null_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_SkipIfM_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp, }, { &CCpu65816::FetchPointerAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::FetchPointerHighAndIncPc_Phi2, &CCpu65816::AddXToPointerWithBankOverflowAndPageSkipAndIncPc, &CCpu65816::Null_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp, }, }, 6, 5, SBN_AM_IMPLIED, 3, 3, SBN_I_ ## NAME

#define SBN_ABSOLUTE_INDEXED_Y_R( NAME, FUNC )										{ { &CCpu65816::FetchPointerAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::FetchPointerHighAndIncPc_Phi2, &CCpu65816::AddYToPointerWithBankOverflowAndPageSkip, &CCpu65816::Null_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_SkipIfM_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp, }, { &CCpu65816::FetchPointerAndIncPc_Phi2, &CCpu65816::NullIncPc_Read, &CCpu65816::FetchPointerHighAndIncPc_Phi2, &CCpu65816::AddYToPointerWithBankOverflowAndPageSkip, &CCpu65816::Null_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp, }, }, 6, 5, SBN_AM_ABSOLUTE_INDEXED_Y, 3, 3, SBN_I_ ## NAME

CCpu65816::SBN_INSTR CCpu65816::m_iInstructionSet[256] = {							/**< The instruction set. */
	/** 00-07 */
	{	// 00
		{
			{
				&CCpu65816::FetchOperandAndIncPc_Phi2,
				&CCpu65816::PushPb, &CCpu65816::PushPb_Phi2,
				&CCpu65816::PushPch, &CCpu65816::PushPch_Phi2,
				&CCpu65816::PushPcl, &CCpu65816::PushPcl_Phi2,
				&CCpu65816::PushStatus, &CCpu65816::PushStatus_Phi2,
				&CCpu65816::CopyVectorPcl, &CCpu65816::CopyVectorPcl_Phi2,
				&CCpu65816::CopyVectorPch, &CCpu65816::CopyVectorPch_Phi2,
				&CCpu65816::Brk, &CCpu65816::PrefetchNextOp },
			{
				&CCpu65816::FetchOperandAndIncPc_Phi2,
				&CCpu65816::PushPch, &CCpu65816::PushPch_Phi2,
				&CCpu65816::PushPcl, &CCpu65816::PushPcl_Phi2,
				&CCpu65816::PushStatus, &CCpu65816::PushStatus_Phi2,
				&CCpu65816::CopyVectorPcl, &CCpu65816::CopyVectorPcl_Phi2,
				&CCpu65816::CopyVectorPch, &CCpu65816::CopyVectorPch_Phi2,
				&CCpu65816::Brk, &CCpu65816::PrefetchNextOp },
		},
		8, 7, SBN_AM_IMPLIED, 2, 2, SBN_I_BRK,
	},
	{	// 01
		SBN_INDIRECT_X_R( ORA, Ora )
	},
	{	// 02
		{
			{
				&CCpu65816::FetchOperandAndIncPc_Phi2,
				&CCpu65816::PushPb, &CCpu65816::PushPb_Phi2,
				&CCpu65816::PushPch, &CCpu65816::PushPch_Phi2,
				&CCpu65816::PushPcl, &CCpu65816::PushPcl_Phi2,
				&CCpu65816::PushStatusCop, &CCpu65816::PushStatusCop_Phi2,
				&CCpu65816::CopyVectorPcl, &CCpu65816::CopyVectorPcl_Phi2,
				&CCpu65816::CopyVectorPch, &CCpu65816::CopyVectorPch_Phi2,
				&CCpu65816::Brk, &CCpu65816::PrefetchNextOp, },
			{
				&CCpu65816::FetchOperandAndIncPc_Phi2,
				&CCpu65816::PushPch, &CCpu65816::PushPch_Phi2,
				&CCpu65816::PushPcl, &CCpu65816::PushPcl_Phi2,
				&CCpu65816::PushStatusCop, &CCpu65816::PushStatusCop_Phi2,
				&CCpu65816::CopyVectorPcl, &CCpu65816::CopyVectorPcl_Phi2,
				&CCpu65816::CopyVectorPch, &CCpu65816::CopyVectorPch_Phi2,
				&CCpu65816::Brk, &CCpu65816::PrefetchNextOp },
		},
		8, 7, SBN_AM_IMPLIED, 2, 2, SBN_I_COP,
	},
	{	// 03
		SBN_STACK_RELATIVE_R( ORA, Ora )
	},
	{	// 04
		SBN_DIRECT_PAGE_RMW( TSB, Tsb )
	},
	{	// 05
		SBN_DIRECT_PAGE_R( ORA, Ora )
	},
	{	// 06
		SBN_DIRECT_PAGE_RMW( ASL, Asl )
	},
	{	// 07
		SBN_DIRECT_PAGE_INDIRECT_LONG_R( ORA, Ora )
		/*{
			{
				&CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::Null_Phi2,
				&CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToPointerLow_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerHigh_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToBankLow_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_SkipIfM_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandHigh_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp,
			},
			{
				&CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::Null_Phi2,
				&CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToPointerLow_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerHigh_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToBankLow_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp,
			},
		},
		8, 7, SBN_AM_DIRECT_PAGE_INDIRECT_LONG, 2, 2, SBN_I_ORA,*/
	},


	/** 08-0F */
	{	// 08
		{
			{
				&CCpu65816::Null_Phi2,
				&CCpu65816::Php, &CCpu65816::PushOperandLow_Phi2,
				&CCpu65816::NullAdjustS_Read, &CCpu65816::PrefetchNextOp
			},
			{
				&CCpu65816::Null_Phi2,
				&CCpu65816::Php, &CCpu65816::PushOperandLow_Phi2,
				&CCpu65816::NullAdjustS_Read, &CCpu65816::PrefetchNextOp
			},
		},
		3, 3, SBN_AM_IMPLIED, 1, 1, SBN_I_PHP,
	},
	{	// 09
		LSN_IMMEDIATE( ORA, OraAndIncPc )
		/*{
			{
				&CCpu65816::FetchOperandLowAndIncPc_SkipIfM_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::FetchOperandHighAndIncPc_Phi2,
				&CCpu65816::OraAndIncPc, &CCpu65816::PrefetchNextOp
			},
			{
				&CCpu65816::FetchOperandAndIncPc_Phi2,
				&CCpu65816::OraAndIncPc, &CCpu65816::PrefetchNextOp
			},
		},
		3, 2, SBN_AM_IMMEDIATE, 3, 2, SBN_I_ORA,*/
	},
	{	// 0A
		{
			{
				&CCpu65816::FetchOperandAndDiscard_Phi2,
				&CCpu65816::AslOnA, &CCpu65816::PrefetchNextOp
			},
			{
				&CCpu65816::FetchOperandAndDiscard_Phi2,
				&CCpu65816::AslOnA, &CCpu65816::PrefetchNextOp
			},
		},
		2, 2, SBN_AM_IMPLIED, 1, 1, SBN_I_ASL,
	},
	{	// 0B
		{
			{
				&CCpu65816::Null_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::PushDh_Phi2,
				&CCpu65816::NullAdjustS_Write, &CCpu65816::PushDl_Phi2,
				&CCpu65816::NullAdjustS_Read, &CCpu65816::PrefetchNextOp
			},
			{
				&CCpu65816::Null_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::PushDh_Phi2,
				&CCpu65816::NullAdjustS_Write, &CCpu65816::PushDl_Phi2,
				&CCpu65816::NullAdjustS_Read, &CCpu65816::PrefetchNextOp
			},
		},
		4, 4, SBN_AM_IMPLIED, 1, 1, SBN_I_PHD,
	},
	{	// 0C
		SBN_ABSOLUTE_RMW( TSB, Tsb )
		/*{
			{
				&CCpu65816::FetchAddressAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::FetchAddressHighAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::ReadAddressAndBankToOperandLow_SkipIfM_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::ReadAddressAndBankToOperandHigh_Phi2,
				&CCpu65816::Tsb, &CCpu65816::Null_SkipIfM,
				&CCpu65816::Null_Write, &CCpu65816::WriteOperandHighToAddressAndBank_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::WriteOperandLowToAddressAndBank_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::PrefetchNextOp
			},
			{
				&CCpu65816::FetchAddressAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::FetchAddressHighAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::ReadAddressAndBankToOperandLow_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::WriteOperandLowToAddressAndBank_Phi2,
				&CCpu65816::Tsb, &CCpu65816::WriteOperandLowToAddressAndBank_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::PrefetchNextOp
			},
		},
		8, 6, SBN_AM_ABSOLUTE, 3, 3, SBN_I_TSB,*/
	},
	{	// 0D
		SBN_ABSOLUTE_R( ORA, Ora )
		/*{
			{
				&CCpu65816::FetchAddressAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::FetchAddressHighAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::ReadAddressAndBankToOperandLow_SkipIfM_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::ReadAddressAndBankToOperandHigh_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp
			},
			{
				&CCpu65816::FetchAddressAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::FetchAddressHighAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::ReadAddressAndBankToOperandLow_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp
			},
		},
		5, 4, SBN_AM_ABSOLUTE, 3, 3, SBN_I_ORA*/
	},
	{	// 0E
		SBN_ABSOLUTE_RMW( ASL, Asl )
		/*{
			{
				&CCpu65816::FetchAddressAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::FetchAddressHighAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::ReadAddressAndBankToOperandLow_SkipIfM_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::ReadAddressAndBankToOperandHigh_Phi2,
				&CCpu65816::Tsb, &CCpu65816::Null_SkipIfM,
				&CCpu65816::Null_Write, &CCpu65816::WriteOperandHighToAddressAndBank_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::WriteOperandLowToAddressAndBank_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::PrefetchNextOp
			},
			{
				&CCpu65816::FetchAddressAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::FetchAddressHighAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::ReadAddressAndBankToOperandLow_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::WriteOperandLowToAddressAndBank_Phi2,
				&CCpu65816::Tsb, &CCpu65816::WriteOperandLowToAddressAndBank_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::PrefetchNextOp
			},
		},
		8, 6, SBN_AM_ABSOLUTE, 3, 3, SBN_I_TSB,*/
	},
	{	// 0F
		SBN_ABSOLUTE_LONG_R( ORA, Ora )
		/*{
			{
				&CCpu65816::FetchPointerAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::FetchPointerHighAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::FetchBankhAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::ReadPointerAndBankToOperandLow_SkipIfM_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandHigh_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp
			},
			{
				&CCpu65816::FetchPointerAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::FetchPointerHighAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::FetchBankhAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::ReadPointerAndBankToOperandLow_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp
			},
		},
		6, 5, SBN_AM_ABSOLUTE_LONG, 4, 4, SBN_I_ORA,*/
	},


	/** 10-17 */
	{	// 10
		{
			{
				&CCpu65816::FetchOperandAndIncPc_Phi2,
				&CCpu65816::Branch_Cycle2<N(), 0>, &CCpu65816::Branch_Cycle2_Phi2,
				&CCpu65816::Branch_Cycle3_Native, &CCpu65816::PrefetchNextOp
			},
			{
				&CCpu65816::FetchOperandAndIncPc_Phi2,
				&CCpu65816::Branch_Cycle2<N(), 0>, &CCpu65816::Branch_Cycle2_Phi2,
				&CCpu65816::Branch_Cycle3, &CCpu65816::Branch_Cycle3_Phi2,
				&CCpu65816::Branch_Cycle4, &CCpu65816::PrefetchNextOp
			},
		},
		3, 4, SBN_AM_RELATIVE, 2, 2, SBN_I_BPL,
	},

	{	// 11
		SBN_DIRECT_PAGE_INDIRECT_INDEXED_Y_R( ORA, Ora )
		/*{
			{
				&CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::Null_Phi2,
				&CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToPointerLow_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerHigh_Phi2,
				&CCpu65816::AddYToPointerWithBankOverflowAndPageSkip, &CCpu65816::Null_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_SkipIfM_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandHigh_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp
			},
			{
				&CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::Null_Phi2,
				&CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToPointerLow_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerHigh_Phi2,
				&CCpu65816::AddYToPointerWithBankOverflowAndPageSkip, &CCpu65816::Null_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp
			},
		},
		8, 7, SBN_AM_DIRECT_PAGE_INDIRECT_INDEXED_Y, 2, 2, SBN_I_ORA,*/
	},
	{	// 12
		SBN_DIRECT_PAGE_INDIRECT_R( ORA, Ora )
		/*{
			{
				&CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::Null_Phi2,
				&CCpu65816::AddDAndOperandToPointerAndIncPc, &CCpu65816::ReadPointerToAddressLow_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerToAddressHigh_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressAndBankToOperandLow_SkipIfM_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressAndBankToOperandHigh_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp
			},
			{
				&CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::Null_Phi2,
				&CCpu65816::AddDAndOperandToPointerAndIncPc, &CCpu65816::ReadPointerToAddressLow_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerToAddressHigh_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressAndBankToOperandLow_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp
			},
		},
		7, 6, SBN_AM_DIRECT_PAGE_INDIRECT, 2, 2, SBN_I_ORA*/
	},
	{	// 13
		SBN_STACK_RELATIVE_INDIRECT_INDEXED_Y( ORA, Ora )
		/*{
			{
				&CCpu65816::FetchPointerAndIncPc_Phi2,
				&CCpu65816::AddStackOffsetAndIncPc, &CCpu65816::Null_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerLow_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerHigh_Phi2,
				&CCpu65816::AddYToPointerWithBankOverflowAndPageSkip, &CCpu65816::Null_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_SkipIfM_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandHigh_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp
			},
			{
				&CCpu65816::FetchPointerAndIncPc_Phi2,
				&CCpu65816::AddStackOffsetAndIncPc, &CCpu65816::Null_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerLow_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerHigh_Phi2,
				&CCpu65816::AddYToPointerWithBankOverflowAndPageSkip, &CCpu65816::Null_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp
			},
		},
		8, 7, SBN_AM_STACK_RELATIVE_INDIRECT_INDEXED_Y, 2, 2, SBN_I_ORA*/
	},
	{	// 14
		SBN_DIRECT_PAGE_RMW( TRB, Trb )
		/*{
			{
				&CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::Null_Phi2,
				&CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToOperandLow_SkipIfM_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToOperandHigh_Phi2,
				&CCpu65816::Tsb, &CCpu65816::SkipIfM_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::WriteOperandHighToAddress_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::WriteOperandLowToAddress_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::PrefetchNextOp,
			},
			{
				&CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::Null_Phi2,
				&CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToOperandLow_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::WriteOperandLowToAddress_Phi2,
				&CCpu65816::Tsb, &CCpu65816::WriteOperandLowToAddress_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::PrefetchNextOp,
			},
		},
		8, 6, SBN_AM_DIRECT_PAGE, 2, 2, SBN_I_TSB,*/
	},
	{	// 15
		SBN_DIRECT_PAGE_INDEXED_X_R( ORA, Ora )
		/*{
			{
				&CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::Null_Phi2,
				&CCpu65816::AddDAndOperandAndXToAddressAndIncPc, &CCpu65816::ReadAddressToOperandLow_SkipIfM_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToOperandHigh_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp,
			},
			{
				&CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::Null_Phi2,
				&CCpu65816::AddDAndOperandAndXToAddressAndIncPc, &CCpu65816::ReadAddressToOperandLow_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp,
			},
		},
		5, 4, SBN_AM_DIRECT_PAGE_INDEXED_X, 2, 2, SBN_I_ORA*/
	},
	{	// 16
		SBN_DIRECT_PAGE_INDEXED_X_RMW( ASL, Asl )
		/*{
			{
				&CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::Null_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::Null_Phi2,
				&CCpu65816::AddDAndOperandAndXToAddressAndIncPc, &CCpu65816::ReadAddressToOperandLow_SkipIfM_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToOperandHigh_Phi2,
				&CCpu65816::Asl, &CCpu65816::Null_SkipIfM,
				&CCpu65816::Null_Write, &CCpu65816::WriteOperandHighToAddress_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::WriteOperandLowToAddress_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::PrefetchNextOp,
			},
			{
				&CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::Null_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::Null_Phi2,
				&CCpu65816::AddDAndOperandAndXToAddressAndIncPc, &CCpu65816::ReadAddressToOperandLow_Phi2,
				&CCpu65816::Asl, &CCpu65816::Null_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::WriteOperandLowToAddress_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::PrefetchNextOp,
			},
		},
		9, 7, SBN_AM_DIRECT_PAGE_INDEXED_X, 2, 2, SBN_I_ASL*/
	},
	{	// 17
		SBN_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y_R( ORA, Ora )
		/*{
			{
				&CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::Null_Phi2,
				&CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToPointerLow_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerHigh_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToBankLow_Phi2,
				&CCpu65816::AddYToPointerWithBankOverflow, &CCpu65816::ReadPointerAndBankToOperandLow_SkipIfM_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandHigh_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp,
			},
			{
				&CCpu65816::FetchOperandAndIncPc_WithDlSkip_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::Null_Phi2,
				&CCpu65816::AddDAndOperandToAddressAndIncPc, &CCpu65816::ReadAddressToPointerLow_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToPointerHigh_WithLowByteWrap_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToBankLow_WithLowByteWrap_Phi2,
				&CCpu65816::AddYToPointerWithBankOverflow, &CCpu65816::ReadPointerAndBankToOperandLow_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp,
			},
		},
		8, 7, SBN_AM_DIRECT_PAGE_INDIRECT_LONG_INDEXED_Y, 2, 2, SBN_I_ORA*/
	},


	/** 18-1F */
	{	// 18
		{
			{
				&CCpu65816::FetchOperandAndDiscard_Phi2,
				&CCpu65816::Clc, &CCpu65816::PrefetchNextOp,
			},
			{
				&CCpu65816::FetchOperandAndDiscard_Phi2,
				&CCpu65816::Clc, &CCpu65816::PrefetchNextOp,
			},
		},
		2, 2, SBN_AM_IMPLIED, 1, 1, SBN_I_CLC
	},
	{	// 19
		SBN_ABSOLUTE_INDEXED_Y_R( ORA, Ora )
		/*{
			{
				&CCpu65816::FetchPointerAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::FetchPointerHighAndIncPc_Phi2,
				&CCpu65816::AddYToPointerWithBankOverflowAndPageSkip, &CCpu65816::Null_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_SkipIfM_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandHigh_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp,
			},
			{
				&CCpu65816::FetchPointerAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::FetchPointerHighAndIncPc_Phi2,
				&CCpu65816::AddYToPointerWithBankOverflowAndPageSkip, &CCpu65816::Null_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp,
			},
		},
		6, 5, SBN_AM_ABSOLUTE_INDEXED_Y, 3, 3, SBN_I_ORA*/
	},
	{	// 1A
		{
			{
				&CCpu65816::FetchOperandAndDiscard_Phi2,
				&CCpu65816::IncOnA, &CCpu65816::PrefetchNextOp,
			},
			{
				&CCpu65816::FetchOperandAndDiscard_Phi2,
				&CCpu65816::IncOnA, &CCpu65816::PrefetchNextOp,
			},
		},
		2, 2, SBN_AM_IMPLIED, 1, 1, SBN_I_INC
	},
	{	// 1B
		{
			{
				&CCpu65816::FetchOperandAndDiscard_Phi2,
				&CCpu65816::Tcs, &CCpu65816::PrefetchNextOp,
			},
			{
				&CCpu65816::FetchOperandAndDiscard_Phi2,
				&CCpu65816::Tcs, &CCpu65816::PrefetchNextOp,
			},
		},
		2, 2, SBN_AM_IMPLIED, 1, 1, SBN_I_TCS
	},
	{	// 1C
		SBN_ABSOLUTE_RMW( TRB, Trb )
	},
	{	// 1D
		SBN_ABSOLUTE_INDEXED_X_R( ORA, Ora )
		/*{
			{
				&CCpu65816::FetchPointerAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::FetchPointerHighAndIncPc_Phi2,
				&CCpu65816::AddXToPointerWithBankOverflowAndPageSkipAndIncPc, &CCpu65816::Null_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_SkipIfM_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandHigh_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp,
			},
			{
				&CCpu65816::FetchPointerAndIncPc_Phi2,
				&CCpu65816::NullIncPc_Read, &CCpu65816::FetchPointerHighAndIncPc_Phi2,
				&CCpu65816::AddXToPointerWithBankOverflowAndPageSkipAndIncPc, &CCpu65816::Null_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadPointerAndBankToOperandLow_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp,
			},
		},
		6, 5, SBN_AM_IMPLIED, 3, 3, SBN_I_ORA*/
	},
	{	// 1D
		//SBN_ABSOLUTE_INDEXED_X_RMW( ASL, Asl )
	},

};
