

CCpu65816::SBN_INSTR CCpu65816::m_iInstructionSet[256+2] = {							/**< The instruction set. */
	/** 00-07 */
	{	// 00
		{
			{
				&CCpu65816::FetchOpcodeAndIncPc_Phi2,
				&CCpu65816::PushPb, &CCpu65816::PushPb_Phi2,
				&CCpu65816::PushPch, &CCpu65816::PushPch_Phi2,
				&CCpu65816::PushPcl, &CCpu65816::PushPcl_Phi2,
				&CCpu65816::PushStatus, &CCpu65816::PushStatus_Phi2 },
			{
				&CCpu65816::FetchOpcodeAndIncPc_Phi2,
				&CCpu65816::PushPch, &CCpu65816::PushPch_Phi2,
				&CCpu65816::PushPcl, &CCpu65816::PushPcl_Phi2,
				&CCpu65816::PushStatus, &CCpu65816::PushStatus_Phi2 },
		},
		8, 7, SBN_AM_IMPLIED, 2, 2, SBN_I_BRK,
	},
};