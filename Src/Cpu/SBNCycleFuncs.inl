#define SBN_INDIRECT_X_R( NAME, FUNC )												{ {	&CCpu65816::FetchPointerAndIncPc_Phi2, &CCpu65816::AddX_D_Pointer, &CCpu65816::SkipOnDL_Phi2, &CCpu65816::FixPointerHigh, &CCpu65816::Null_Phi2, &CCpu65816::ReadPointerToAddressLow, &CCpu65816::ReadPointerToAddressLow_Phi2, &CCpu65816::ReadPointerToAddressHigh, &CCpu65816::ReadPointerToAddressHigh_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressAndBankToOperandLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressAndBankToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, {	&CCpu65816::FetchPointerAndIncPc_Phi2, &CCpu65816::AddX_D_Pointer, &CCpu65816::SkipOnDL_Phi2, &CCpu65816::FixPointerHigh, &CCpu65816::Null_Phi2, &CCpu65816::ReadPointerToAddressLow, &CCpu65816::ReadPointerToAddressLow_Phi2, &CCpu65816::ReadPointerToAddressHigh, &CCpu65816::ReadPointerToAddressHigh_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressAndBankToOperandLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadAddressAndBankToOperandHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, }, 8, 7, SBN_AM_INDIRECT_X, 2, 2, SBN_I_ ## NAME

#define SBN_STACK_RELATIVE_R( NAME, FUNC )											{ { &CCpu65816::FetchPointerAndIncPc_Phi2, &CCpu65816::AddStackOffset, &CCpu65816::Null_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadStackOffsetLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadStackOffsetHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, { &CCpu65816::FetchPointerAndIncPc_Phi2, &CCpu65816::AddStackOffset, &CCpu65816::Null_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadStackOffsetLow_Phi2, &CCpu65816::Null_Read, &CCpu65816::ReadStackOffsetHigh_Phi2, &CCpu65816::FUNC, &CCpu65816::PrefetchNextOp }, }, 5, 5, SBN_AM_STACK_RELATIVE, 2, 2, SBN_I_ ## NAME

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
		8, 7, SBN_AM_IMPLIED, 2, 2, SBN_I_BRK,
	},
	{	// 03
		SBN_STACK_RELATIVE_R( ORA, Ora )
		/*{
			{
				&CCpu65816::FetchPointerAndIncPc_Phi2,
				&CCpu65816::AddStackOffset, &CCpu65816::Null_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadStackOffsetLow_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadStackOffsetHigh_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp
			},
			{
				&CCpu65816::FetchPointerAndIncPc_Phi2,
				&CCpu65816::AddStackOffset, &CCpu65816::Null_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadStackOffsetLow_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadStackOffsetHigh_Phi2,
				&CCpu65816::Ora, &CCpu65816::PrefetchNextOp
			},
		},
		5, 5, SBN_AM_STACK_RELATIVE, 2, 2, SBN_I_ORA,*/
	},
	{	// 04
		{
			{
				&CCpu65816::FetchOperandAndIncPc_Phi2,
				&CCpu65816::AddD_Operand, &CCpu65816::Null_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToOperandLow_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToOperandHigh_Phi2,
				&CCpu65816::Tsb, &CCpu65816::SkipIfM_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::WriteOperandHighToAddress_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::WriteOperandLowToAddress_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::PrefetchNextOp,
			},
			{
				&CCpu65816::FetchOperandAndIncPc_Phi2,
				&CCpu65816::AddD_Operand, &CCpu65816::Null_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToOperandLow_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::ReadAddressToOperandHigh_Phi2,
				&CCpu65816::Tsb, &CCpu65816::SkipIfM_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::WriteOperandHighToAddress_Phi2,
				&CCpu65816::Null_Write, &CCpu65816::WriteOperandLowToAddress_Phi2,
				&CCpu65816::Null_Read, &CCpu65816::PrefetchNextOp,
			},
		},
		8, 8, SBN_AM_DIRECT_PAGE, 2, 2, SBN_I_TSB,
	},
};