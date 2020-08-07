/* **************************************************************************
 File Name	: 	isp_etc.c
 Description:	EN675 - ETC. Functions
 Designer	:	Kim, Sunghoon
 Modified by:	Lee, Wanhee
 Date		:	14. 8. 4 / 15. 4. 24
 Copyright ??Eyenix Co., Ltd. All Rights Reserved.
*************************************************************************** */

#include "dev.h"

//*************************************************************************************************
// Functions
//-------------------------------------------------------------------------------------------------
int ISRT udiv4x(const UINT anNumer, const UINT anDenom, const UINT anZeroDenom)	// AE 8BIT, AWB 8BIT
{
#if 0
	return (int)( (anDenom) ? (anNumer>0x1FFFFFFF) ? (anDenom>>2) ? anNumer / (anDenom>>2) : (anNumer / anDenom)<<2 : (anNumer<<2) / anDenom : anZeroDenom );	// TestCur10bit()??Ï£ºÏÑù ! ?êÏÑú ?§Ï∞® Î∞úÏÉù
#else
	/*const*/ uint64 ulDiv = (anDenom) ? (((uint64)anNumer)<<2) / ((uint64)anDenom) : anZeroDenom;
	//return MIN(ulDiv,0x7FFFFFFF);							// unsign?ïÏùÑ x4 ???ÑÏóê ?òÎàÑ?¥ÏÑú sign?ºÎ°ú Ï∂úÎ†•?òÎ?Î°?ÏµúÏÉÅ??bit??0?¥Ïñ¥????
	if(ulDiv > (int)0x7FFFFFFF) ulDiv = (int)0x7FFFFFFF;	// MIN() Î≥¥Îã§ ÏΩîÎìú Í∞êÏÜå
	return ulDiv;
#endif
}


//-------------------------------------------------------------------------------------------------
int giIspAgc[3]={0,0,0};
BYTE gbIspAgcSta=0;
BYTE gbIspAgcEnd=0;

void IspAgcSet(void)
{
	extern int AGC_POS_MAX;
	ADNR_AGC_MIN = (UP(ShpAgcLow)  * AGC_POS_MAX) / 100;
	ADNR_AGC_MID = (UP(ShpAgcMid)  * AGC_POS_MAX) / 100;
	ADNR_AGC_MAX = (UP(ShpAgcHigh) * AGC_POS_MAX) / 100;
	if(ADNR_AGC_MID < ADNR_AGC_MIN) ADNR_AGC_MID = ADNR_AGC_MIN;
	if(ADNR_AGC_MAX < ADNR_AGC_MID) ADNR_AGC_MAX = ADNR_AGC_MID;

	//printf("ADNR_AGC: %d, %d, %d\r\n", ADNR_AGC_MIN, ADNR_AGC_MID, ADNR_AGC_MAX);
}

void ISRT IspAgcCurSet(void)
{
	const BYTE iAgcPos = (giCurAgc<=ADNR_AGC_MIN) ? 0 : (giCurAgc<=ADNR_AGC_MID) ? 1 : (giCurAgc<=ADNR_AGC_MAX) ? 2 : 3;

	gbIspAgcSta = (ADNR_AGC_MID==ADNR_AGC_MIN) || (ADNR_AGC_MID==ADNR_AGC_MAX) || (iAgcPos==0) ? 0 : (iAgcPos-1);

	gbIspAgcEnd = (ADNR_AGC_MAX<=ADNR_AGC_MIN) ? 0 : (ADNR_AGC_MID==ADNR_AGC_MIN) || (ADNR_AGC_MID==ADNR_AGC_MAX) || (iAgcPos==3) ? 2 : iAgcPos;
}


//-------------------------------------------------------------------------------------------------
const UINT Adnr2D_Q_Tbl[] = {
		0x0f000f, 0x120017, 0x1b0020, 0x240029,
		0x0f0012, 0x17001b, 0x200024, 0x29002d,
		0x120017, 0x1b0020, 0x240029, 0x2d0032,
		0x17001b, 0x200024, 0x29002d, 0x320036,
		0x1b0020, 0x240029, 0x2d0032, 0x36003b,
		0x200024, 0x29002d, 0x320036, 0x3b003f,
		0x240029, 0x2d0032, 0x36003b, 0x3f0044,
		0x29002d, 0x320036, 0x3b003f, 0x440048
};

#if 0 // Q-Table Test
	#if 0 // 1024 Scale
	const UINT Adnr2D_Tbl_Q1[] = {
		0x0120006, 0x0080008, 0x0080008, 0x009000A,
		0x0060007, 0x0080008, 0x0080009, 0x009000A,
		0x0080008, 0x0080008, 0x0080008, 0x009000A,
		0x0080008, 0x0080008, 0x0080008, 0x009000A,
		0x0080008, 0x0080008, 0x0080008, 0x0080009,
		0x0080009, 0x0080008, 0x0080008, 0x0090009,
		0x0090009, 0x0090009, 0x0080009, 0x009000A,
		0x00A000A, 0x00A000A, 0x0090009, 0x00A000B
	};

	const UINT Adnr2D_Tbl_Q5[] = {
		0x053002F, 0x0330034, 0x0340035, 0x037003B,
		0x02F0032, 0x0320033, 0x0340035, 0x037003B,
		0x0330032, 0x0320033, 0x0330034, 0x037003B,
		0x0340033, 0x0330033, 0x0330034, 0x037003B,
		0x0340034, 0x0330033, 0x0340035, 0x038003C,
		0x0350035, 0x0340034, 0x0350036, 0x039003C,
		0x0370037, 0x0370037, 0x0380039, 0x03B003E,
		0x03B003B, 0x03B003B, 0x03C003C, 0x03E0040
	};

	const UINT Adnr2D_Tbl_Q10[] = {
		0x0B00063, 0x06A006D, 0x06E0070, 0x074007A,
		0x0630066, 0x068006B, 0x06E0071, 0x075007B,
		0x06A0068, 0x069006C, 0x06E0071, 0x076007B,
		0x06D006B, 0x06C006E, 0x0700072, 0x077007B,
		0x06E006E, 0x06E0070, 0x0720074, 0x078007C,
		0x0700071, 0x0710072, 0x0740076, 0x079007C,
		0x0740075, 0x0760077, 0x0780079, 0x07B007D,
		0x07A007B, 0x07B007B, 0x07C007C, 0x07D0080
	};

	const UINT Adnr2D_Tbl_Q20[] = {
		0x15700CA, 0x0D900E1, 0x0E600EB, 0x0F100F6,
		0x0CA00D2, 0x0DB00E3, 0x0E900EE, 0x0F300F7,
		0x0D900DB, 0x0E000E6, 0x0EB00EF, 0x0F300F6,
		0x0E100E3, 0x0E600EA, 0x0ED00F0, 0x0F400F7,
		0x0E600E9, 0x0EB00ED, 0x0F000F2, 0x0F500F7,
		0x0EB00EE, 0x0EF00F0, 0x0F200F4, 0x0F500F7,
		0x0F100F3, 0x0F300F4, 0x0F500F5, 0x0F600F7,
		0x0F600F7, 0x0F600F7, 0x0F700F7, 0x0F700F8
	};

	#else // 4096 Scale
	const UINT Adnr2D_Tbl_Q1[] = {
		0x0490018, 0x0200020, 0x0200020, 0x0240028,
		0x018001C, 0x0200020, 0x0200024, 0x0240028,
		0x0200020, 0x0200020, 0x0200020, 0x0240028,
		0x0200020, 0x0200020, 0x0200020, 0x0240028,
		0x0200020, 0x0200020, 0x0200020, 0x0200024,
		0x0200024, 0x0200020, 0x0200020, 0x0240024,
		0x0240024, 0x0240024, 0x0200024, 0x0240028,
		0x0280028, 0x0280028, 0x0240024, 0x028002D
	};

	const UINT Adnr2D_Tbl_Q5[] = {
		0x14F00BC, 0x0CC00D0, 0x0D000D4, 0x0DD00ED,
		0x0BC00C8, 0x0C800CC, 0x0D000D4, 0x0DD00ED,
		0x0CC00C8, 0x0C800CC, 0x0CC00D0, 0x0DD00ED,
		0x0D000CC, 0x0CC00CC, 0x0CC00D0, 0x0DD00ED,
		0x0D000D0, 0x0CC00CC, 0x0D000D4, 0x0E100F1,
		0x0D400D4, 0x0D000D0, 0x0D400D9, 0x0E500F1,
		0x0DD00DD, 0x0DD00DD, 0x0E100E5, 0x0ED00F9,
		0x0ED00ED, 0x0ED00ED, 0x0F100F1, 0x0F90102
	};

	const UINT Adnr2D_Tbl_Q10[] = {
		0x2C0018D, 0x1A901B6, 0x1BA01C2, 0x1D201EB,
		0x18D0199, 0x1A101AE, 0x1BA01C6, 0x1D701EF,
		0x1A901A1, 0x1A501B2, 0x1BA01C6, 0x1DB01EF,
		0x1B601AE, 0x1B201BA, 0x1C201CA, 0x1DF01EF,
		0x1BA01BA, 0x1BA01C2, 0x1CA01D2, 0x1E301F3,
		0x1C201C6, 0x1C601CA, 0x1D201DB, 0x1E701F3,
		0x1D201D7, 0x1DB01DF, 0x1E301E7, 0x1EF01F7,
		0x1EB01EF, 0x1EF01EF, 0x1F301F3, 0x1F70200
	};

	const UINT Adnr2D_Tbl_Q20[] = {
		0x55C032B, 0x3640385, 0x39903AE, 0x3C603DB,
		0x32B034B, 0x36C038D, 0x3A503BA, 0x3CE03DF,
		0x364036C, 0x3810399, 0x3AE03BE, 0x3CE03DB,
		0x385038D, 0x39903A9, 0x3B603C2, 0x3D203DF,
		0x39903A5, 0x3AE03B6, 0x3C203CA, 0x3D703DF,
		0x3AE03BA, 0x3BE03C2, 0x3CA03D2, 0x3D703DF,
		0x3C603CE, 0x3CE03D2, 0x3D703D7, 0x3DB03DF,
		0x3DB03DF, 0x3DB03DF, 0x3DF03DF, 0x3DF03E3
	};
	#endif

void ISRT Adnr_2D_Gain(const UINT anGain)
{
	static BYTE bPAR0A_Buf=0;

	if(bPAR0A_Buf!=PAR0A)
	{
		switch(PAR0A) {
			case 1  : {  for(int i=0; i<32; i++) { SetIsp(DNR_Q_BASE+i, Adnr2D_Tbl_Q1[i]);  } printf("Adnr2D_Tbl_Q1  d\r\n"); break; }
			case 2  : {  for(int i=0; i<32; i++) { SetIsp(DNR_Q_BASE+i, Adnr2D_Tbl_Q5[i]);  } printf("Adnr2D_Tbl_Q5  d\r\n"); break; }
			case 3  : {  for(int i=0; i<32; i++) { SetIsp(DNR_Q_BASE+i, Adnr2D_Tbl_Q10[i]); } printf("Adnr2D_Tbl_Q10 d\r\n"); break; }
			case 4  : {  for(int i=0; i<32; i++) { SetIsp(DNR_Q_BASE+i, Adnr2D_Tbl_Q20[i]); } printf("Adnr2D_Tbl_Q20 d\r\n"); break; }
			default : {  for(int i=0; i<32; i++) { SetIsp(DNR_Q_BASE+i, Adnr2D_Q_Tbl[i]);   } printf("Adnr2D_Q_Tbl   d\r\n"); break; }
		}
		bPAR0A_Buf=PAR0A;
	}
}

#else

void ISRT Adnr_2D_Gain(const UINT anGain)
{
	for(int i=0; i<ARRAY_SIZE(Adnr2D_Q_Tbl); i++)
	{
		const UINT nQHt = (Adnr2D_Q_Tbl[i]>>16)&0x1fff;
		const UINT nQLt = Adnr2D_Q_Tbl[i]&0x1fff;
	#if 0	// ?ÑÏ£º ??Gain???ÅÏö©??Í≤ΩÏö∞ ?ÑÏöî
		const UINT nQH = (nQHt*anGain)>>7;
		const UINT nQL = (nQLt*anGain)>>7;
		SetIsp(DNR_Q_BASE+i, (MIN(nQH,0x1fff)<<16) | MIN(nQL,0x1fff) );
	#else
		SetIsp(DNR_Q_BASE+i, (((nQHt*anGain)>>7)<<16) | ((nQLt*anGain)>>7) );
	#endif
	}
}
#endif


#if 0
void Adnr_CmdCheck(void) // 180320 LWH
{
	//static BYTE gbAdnr_WaitCnt=3;

	// Exception Condition
#if (model_2M30p)
	#define NOR_MODE	(UP(FrameMode) == UP_FRAMEMODE_NORMAL_25_30)
#else
	#define NOR_MODE	((UP(FrameMode) == UP_FRAMEMODE_NORMAL_25_30) || (UP(FrameMode) == UP_FRAMEMODE_NORMAL_50_60))
#endif

#if (model_Sens == SENS_OV2718)		// OV2718 Parallel 27MHz ?ôÏûë ??Sensor Ï∂úÎ†•??HLOCK???îÎì§Î¶?-> VLOCK???îÎì§Î¶?-> DNR ??Í∞ÑÌóê?ÅÏúºÎ°??ÅÏÉÅ??Íπ®Ï???Í≤ΩÏö∞ Î∞úÏÉù -> HLOCK???îÎì§Î¶¨Ï? ?äÎäî Sensor initial setting???ÑÏöî
	const BYTE bMpAdnr = UP_4sOFF;
#else
	const BYTE bMpAdnr = ((UP(BackLight) == UP_BL_WDR) || (gbWdrOn!=WDR_OFF) || (gbWdrOnBuf2!=WDR_OFF) || FPS_HI || NOR_MODE) ? UP_4sOFF : UP(Adnr3D) ;
#endif

	if(bMpAdnr == UP_4sOFF) gbAdnr_WaitCnt=3; // Priority : WDR > DNR
	else if(gbAdnr_WaitCnt) gbAdnr_WaitCnt--; // wait for stable image

	gbAdnr_Excute = (gbAdnr_WaitCnt==0);
}
#endif

	const int Adnr3DFkTbl[3][3]	= 	{//  Low Agc,	Mid Agc,	Hi Agc
										{0x90,		0xc0,		0xe0	},		// Low strength
										{0xa0, 		0xd0, 		0xe0	},		// Mid	"
										{0xb0, 		0xd8, 		0xe0	}		// Hi	"
									};

	const int Adnr3DGainTbl[3][3] =	{//  Low Agc,	Mid Agc,	Hi Agc
										{0x28,		0x10,		0x0c	},		// Low strength
										{0x20, 		0x0c, 		0x08	},		// Mid	"
										{0x18, 		0x08, 		0x04	}		// Hi	"
									};

void ISRT Adnr(void)
{	// Digital noise reduction

	if(UP(Adnr2D)) {	// UP(Adnr2D) : Sharpness=5 ?¥Î©¥ 2, Sharpness=10 ?¥Î©¥ 3 Í∂åÏû•, Sharpness=10 + Ace=HIGH ?¥Î©¥ 8 Í∂åÏû•
	#if 1
		#define ADNR_2D_MID 0x80
		#define ADNR_2D_MAX 0x100

		const int iAdnr2D_L = (UP(Adnr2D)<<4);	// UP(Adnr2D)Í∞Ä 4 ?¥Î©¥ 0x40
		const int iAdnr2D_M = MAX(iAdnr2D_L, ADNR_2D_MID);
		const int iAdnr2D_H = MAX(iAdnr2D_M, ADNR_2D_MAX);

		const int iGain2D_S = (gbIspAgcSta==0) ? iAdnr2D_L : (gbIspAgcSta==1) ? iAdnr2D_M : iAdnr2D_H;
		const int iGain2D_E = (gbIspAgcEnd==0) ? iAdnr2D_L : (gbIspAgcEnd==1) ? iAdnr2D_M : iAdnr2D_H;
		const int iGain2D   = (gbIspAgcSta < gbIspAgcEnd) ? LibUtlInterp1D(giCurAgc, ADNR_AGC_STA, ADNR_AGC_END, iGain2D_S, iGain2D_E) : iGain2D_S ;
		Adnr_2D_Gain(iGain2D);
	#else
		const int iGain2D_S = (gbIspAgcSta==0) ? UP(Adnr2D) : 0xc0;	// 0xc0 Ï¥àÍ≥º ?ÅÏö© ???¨Ìôî Í≤ΩÍ≥Ñ??Î∂ÄÎ∂ÑÏóê ?ÅÏÉÅ?úÍ≥° Î∞úÏÉù, UP(Adnr2D)Í∞íÏúºÎ°?0x30 ?êÎäî 0x60 Í∂åÏû•
		const int iGain2D_E = (gbIspAgcEnd==0) ? UP(Adnr2D) : 0xc0;
		const int iGain2D = (gbIspAgcSta < gbIspAgcEnd) ? LibUtlInterp1D(giCurAgc, ADNR_AGC_STA, ADNR_AGC_END, iGain2D_S, iGain2D_E) : iGain2D_S ;
		//DNR2D_GAINw(iGain2D);
	#endif
		DNR2D_ONw(1);
	}
	else {
		DNR2D_ONw(0);
	}

#if 0
	static BYTE bIspResetCnt = 0;
	//GrpAe(GA_ERR_NIGHT_ORI) = bIspResetCnt;
	if(bIspResetCnt) { bIspResetCnt--; return; }

	Adnr_CmdCheck();

	if(gbAdnr_Excute) {

		if(giCurDssStg > 1) return;
		else if(giCurDssStg==1) {
			giCurDssStg = 0;
			isp_reset();
			bIspResetCnt = 1/*PAR00*/;	// isp_reset ??ÏµúÏÜå 2frame ?ÑÏóê DNR3D_ONw(1) ?¥Ïïº ??
			return;
		}
#else
	if(UP(Adnr3D) != UP_4sOFF/*gbAdnr_Excute*/) {
#endif
		int iGain=0,iFk=0,iTh=0;
		const BYTE bTblSel_0 = (UP(Adnr3D) == UP_4sHI) ? UP_3sHI : (UP(Adnr3D) == UP_4sMID) ? UP_3sMID : UP_3sLOW ;

		if((gbIspAgcSta < gbIspAgcEnd) && (UP(DnrIncrease) == UP_ON)) {
			iGain = LibUtlInterp1D(giCurAgc, ADNR_AGC_STA, ADNR_AGC_END, Adnr3DGainTbl[bTblSel_0][gbIspAgcSta], Adnr3DGainTbl[bTblSel_0][gbIspAgcEnd]);
			iTh   = 0;//LibUtlInterp1D(giCurAgc, ADNR_AGC_STA, ADNR_AGC_END, Adnr3DThrsTbl[bTblSel_0][gbIspAgcSta], Adnr3DThrsTbl[bTblSel_0][gbIspAgcEnd]);
			iFk   = LibUtlInterp1D(giCurAgc, ADNR_AGC_STA, ADNR_AGC_END, Adnr3DFkTbl  [bTblSel_0][gbIspAgcSta], Adnr3DFkTbl  [bTblSel_0][gbIspAgcEnd]);
		}
		else {
			const BYTE bTblSel_1 = (UP(DnrIncrease) == UP_ON) ? gbIspAgcSta : 0 ;
			iGain = Adnr3DGainTbl[bTblSel_0][bTblSel_1];
			iTh   = 0;//Adnr3DThrsTbl[bTblSel_0][bTblSel_1];	// 0 Ï¥àÍ≥º ?ÅÏö© ???ºÎ∞ò Ï°∞ÎèÑ ?ÅÌô©?êÏÑú Í¥òÏ†Å Î∞úÏÉù
			iFk   = Adnr3DFkTbl  [bTblSel_0][bTblSel_1];
		}

		// Adding user parameter gain weight
#if 0
		const BYTE b3D_DNR_GAIN = (MP(MpAdnr) == MN_4sLOW) ? UP(3D_DNR_GAIN_LOW)    :
		                          (MP(MpAdnr) == MN_4sMID) ? UP(3D_DNR_GAIN_MIDDLE) :
								  (MP(MpAdnr) == MN_4sHI ) ? UP(3D_DNR_GAIN_HIGH)   : 0 ;

		iGain = MIN((iGain * b3D_DNR_GAIN)>>7, 0x3F);
		iTh   = MIN((iTh   * b3D_DNR_GAIN)>>7, 0xFF);
		iFk   = MIN((iFk   * b3D_DNR_GAIN)>>7, 0xFF);
#endif

		// Post Processing
		DNR3D_ONw(1);
		//DDR_RD_MODw(1); // DDR set to DNR Mode

		DNR3D_GAw((UINT)iGain);		// 0x3F
		DNR3D_THw((UINT)iTh  );		// 0xFF
		DNR3D_FKw((UINT)iFk  );		// 0xFF
	}
	else DNR3D_ONw(0);
}


//-------------------------------------------------------------------------------------------------
const int Apt55ThTbl[3]  =   //  Low Agc,	Mid Agc,	Hi Agc
								{0x10,		0xa0,		0x100	};	// 2015827 - WHL
//								{0x20,		0xa0,		0x100	};	// 2015827 - WHL

#if 0
const int Apt55GainTbl[3]=   //  Low Agc,	Mid Agc,	Hi Agc
								{0x30,		0x20,		0x10	};		// 150526 LH
//								{0x20,		0x18,		0x10	};	// 20170509 - WHL
#endif

const int Apt33ThTbl[3] =   //  Low Agc,	Mid Agc,	Hi Agc
								{0x20,		0x100,		0x100	};	// 2015827 - WHL
//								{0x40,		0x100,		0x100	};	// 20170509 - WHL

void ISRT Sharpness(void)
{	// Aperture

	//if(gbMnDebugFnc==8) return;

	int i55Th, i55Gain, i33Th, i33Gain;

	const int i55Gain_S = (gbIspAgcSta==0) ? UP(ShpBigEdge) : (gbIspAgcSta==1) ? (UP(ShpBigEdge)>>1) : 0;
	const int i55Gain_E = (gbIspAgcEnd==0) ? UP(ShpBigEdge) : (gbIspAgcEnd==1) ? (UP(ShpBigEdge)>>1) : 0;

	const int i33Gain_S = (gbIspAgcSta==0) ? UP(ShpSmallEdge) : 0;
	const int i33Gain_E = (gbIspAgcEnd==0) ? UP(ShpSmallEdge) : 0;

//	APT_ONw(1);
//	APT_GAIN_ONw(1);

	if(gbIspAgcSta < gbIspAgcEnd) {
		i55Th 	= LibUtlInterp1D(giCurAgc, ADNR_AGC_STA, ADNR_AGC_END, Apt55ThTbl[gbIspAgcSta], Apt55ThTbl[gbIspAgcEnd]);
		i55Gain = LibUtlInterp1D(giCurAgc, ADNR_AGC_STA, ADNR_AGC_END, i55Gain_S, i55Gain_E);
		i33Th 	= LibUtlInterp1D(giCurAgc, ADNR_AGC_STA, ADNR_AGC_END, Apt33ThTbl[gbIspAgcSta], Apt33ThTbl[gbIspAgcEnd]);
		i33Gain = LibUtlInterp1D(giCurAgc, ADNR_AGC_STA, ADNR_AGC_END, i33Gain_S, i33Gain_E);
	}
	else {
		i55Th  	= Apt55ThTbl[gbIspAgcSta];
		i55Gain	= i55Gain_S;
		i33Th	= Apt33ThTbl[gbIspAgcSta];
		i33Gain	= i33Gain_S;
	}

	// APT 5x5 Filter control
	i55Gain = MIN((i55Gain * UP(Sharpness) / 5/*UP(SHARPNESS_GAIN)*/), 0xff);

	APT_GAIN1_POSw(i55Gain);
	APT_GAIN2_POSw(i55Gain);
	APT_GAIN1_NEGw(i55Gain);
	APT_GAIN2_NEGw(i55Gain);
	APT_TH1w(i55Th);
//	APT_TH3w(0x80);

	// APT 3x3 Filter control
	i33Gain = MIN((i33Gain * UP(Sharpness) / 5/*UP(SHARPNESS_GAIN)*/), 0xff);

	APT_GAIN3w(i33Gain);
	APT_SLIC3w(i33Th);
//	APT_CLIP3w(0x80);

	/*GRP0 = giCurAgc;
	GRP1 = i55Th;
	GRP2 = i55Gain;
	GRP3 = i33Th;
	GRP4 = i33Gain;
	TxGrpFnc();*/
}

//-------------------------------------------------------------------------------------------------
const int DefectDifGaTbl[3]  = {0x20, 0x30, 0x40};		//  AUTO Defect gain table (Low Agc, Mid Agc, Hi Agc)
const int DefectSDifGaTbl[3] = {0x10, 0x08, 0x00};		// AUTO Defect spot gain table (Low Agc, Mid Agc, Hi Agc)

void ISRT DefectAuto(void)	// TODO KSH ??DefectAuto() - DOL ??LongÍ≥?Short???∞Î°ú ?§Ï†ï?òÎèÑÎ°??¥Ïïº ??
{	// Auto Defect correction
	int iGain, iSGain;
	if(gbIspAgcSta < gbIspAgcEnd) {
		iGain  = LibUtlInterp1D(giCurAgc, ADNR_AGC_STA, ADNR_AGC_END, DefectDifGaTbl[gbIspAgcSta], DefectDifGaTbl[gbIspAgcEnd]);
		iSGain = LibUtlInterp1D(giCurAgc, ADNR_AGC_STA, ADNR_AGC_END, DefectSDifGaTbl[gbIspAgcSta], DefectSDifGaTbl[gbIspAgcEnd]);
	}
	else {
		iGain  = DefectDifGaTbl[gbIspAgcSta];
		iSGain = DefectSDifGaTbl[gbIspAgcSta];
	}

	iGain = MIN(((iGain * UP(DEFECT_GA))>>7), 0x3F);	// 2015615 HSH
	iSGain = MIN(((iSGain * UP(DEFECT_SPOT_GA))>>7), 0x3F);	// 2015615 HSH

	DF_DIFGA_LEw(iGain);
	DF_DIFGA_SE0w(iGain);

	DFS_DIFGA_LEw(iSGain);
	DFS_DIFGA_SE0w(iSGain);
}

//-------------------------------------------------------------------------------------------------
#if(model_Sens==SENS_IMX291)||(model_Sens==SENS_IMX327)||(model_Sens==SENS_IMX307)
							//Low Agc,	Mid Agc,	Hi Agc
const int LowCSupGaTbl[3] = {0x38,		0x24,		0x10	}; // 14.2.10
#else
const int LowCSupGaTbl[3] = {0x20,		0x18,		0x10	}; // 14.2.10
#endif

void ISRT CSup(void)	// TODO KSH ??WDR - CSup()?êÏÑú Line WDR ?§Ï†ï??Frame WDRÎ°??òÎäîÍ≤???Ï¢ãÏ?ÏßÄ ?ïÏù∏ ?ÑÏöî
{
	// Low light color suppression ----------------------------
	int iGain = (gbIspAgcSta < gbIspAgcEnd) ? LibUtlInterp1D(giCurAgc, ADNR_AGC_STA, ADNR_AGC_END, LowCSupGaTbl[gbIspAgcSta], LowCSupGaTbl[gbIspAgcEnd]) : LowCSupGaTbl[gbIspAgcSta];
	iGain = MIN((iGain * UP(LSUP_GA))>>7, 0x3F);	// 15.06.13 KSH

	LSUP_ONw(UP(LSUP_ON)&&(gbWdrOn!=WDR_FRAME));
	LSUP_GAw(iGain);

	// Edge color suppression -------------------------------
	const BYTE bMpCES_ON = (gbWdrOn==WDR_FRAME) ? UP(CES_WDR) : UP(CES_NOR);
	const BYTE bMpCES_ONrv = (40 < bMpCES_ON) ? 40 : 40 - bMpCES_ON;
	const BYTE bCES_LCLIP = (bMpCES_ONrv > 20) ? bMpCES_ONrv + (((bMpCES_ONrv-19)*(bMpCES_ONrv-20))>>1) : bMpCES_ONrv;

	CES_ONw(bMpCES_ON>0);				//WHL 20180807
	CES_GAINw((gbWdrOn==WDR_FRAME) ? UP(CES_WGAIN) : UP(CES_GAIN));
	CES_LCLIPw((gbWdrOn==WDR_FRAME) ? (bCES_LCLIP>>1)/*UP(CES_WLCLP)*/ : bCES_LCLIP/*UP(CES_LCLP)*/);
}

//-------------------------------------------------------------------------------------------------
// Privacy Color Table -            Y,  Cb, Cr
const BYTE gbPrvcYCbCrTbl[8][3] = {{235,128,128/*WHT*/},{218,  8,139/*YEL*/},{185,155,  8/*CYN*/},{168, 35, 19/*GRN*/},
								   { 67,221,237/*MAG*/},{ 50,101,248/*RED*/},{ 17,248,117/*BLU*/},{  0,128,128/*BLK*/}};

void HlMask(void)
{	// High Light Mask

#if 1
	HLMASK_ONw((UP(BackLight)==UP_BL_HLC));
	HLMASK_THw(54+(UP(HlMaskThrs)*0xA/*UP(HLMASK_THRS_STEP)*/));

	if(UP(HlMaskColorSel)<8) {	// Fixed Menu Color Table

		HLMASK_YLVw((UINT)gbPrvcYCbCrTbl[UP(HlMaskColorSel)][0]);
		HLMASK_BLVw((UINT)gbPrvcYCbCrTbl[UP(HlMaskColorSel)][1]);
		HLMASK_RLVw((UINT)gbPrvcYCbCrTbl[UP(HlMaskColorSel)][2]);
	}
	else {	// CUSTOMIZE

		HLMASK_YLVw((UINT)UP(HlMaskColorCY));
		HLMASK_BLVw((UINT)UP(HlMaskColorCB));
		HLMASK_RLVw((UINT)UP(HlMaskColorCR));
	}
#endif
}

//-------------------------------------------------------------------------------------------------
void ColorSpace(void)
{ // Color space setup

	switch(UP(OutFormat)) {
		case UP_FRMT_UV :	RMYRw(0x276);RMYGw(0x20F);RMYBw(0x66);BMYRw(0x97);BMYGw(0x128);BMYBw(0x1BE); break;
		case UP_FRMT_SD :	RMYRw(0x20B);RMYGw(0x1B6);RMYBw(0x55);BMYRw(0xB0);BMYGw(0x15B);BMYBw(0x20B); break;
		case UP_FRMT_HD :	RMYRw(0x20B);RMYGw(0x1DB);RMYBw(0x30);BMYRw(0x78);BMYGw(0x193);BMYBw(0x20B); break;
	}
}

void Flip(void)
{
	if(UP(Flip) == UP_ON || UP(Flip) == UP_OFF) {
		//FLP_ONw(UP(Flip)); FLP_OFSw(0x1e);
		SensFlip(UP(Flip));
	}

	ICSELw(/*(UP(Flip)==UP_ON) ? UP(ICSelFlip) :*/ UP(ICSel));
	OCSELw(/*(UP(Flip)==UP_ON) ? UP(OCSelFlip) :*/ UP(OCSel));

	//DNR_CSELw(UP(ICSel));	// TODO KSH + ICSEL Í≥?DNR_CSEL ?åÏä§??
}

void DZoom(void)
{
	DZ_VSP_KYw((10<<12)/UP(DZoom));

	const int iDZoomPosHmin = DZ_HW*5/UP(DZoom);
	const int iDZoomPosVmin = DZ_VW*5/UP(DZoom);
	const int iDZoomPosHmax = (UP(DZoom)-5)*DZ_HW/UP(DZoom);
	const int iDZoomPosVmax = (UP(DZoom)-5)*DZ_VW/UP(DZoom);
	UP(DZoomPosH) = CLAMP(UP(DZoomPosH), iDZoomPosHmin, iDZoomPosHmax);
	UP(DZoomPosV) = CLAMP(UP(DZoomPosV), iDZoomPosVmin, iDZoomPosVmax);

	const int iDZoomPosH = (UP(DZoomPosH)<<12) - (((DZ_HW<<11)*10) / UP(DZoom));
	const int iDZoomPosV = (UP(DZoomPosV)<<12) - (((DZ_VW<<11)*10) / UP(DZoom));
	DZ_HSP_POSw((iDZoomPosH < 0) ? 0 : iDZoomPosH);
	DZ_VSP_POSw((iDZoomPosV < 0) ? 0 : iDZoomPosV);

	if(UP(DZoom) <= 10)	// Off
	{
		//HWIw(RP(PO_HW));				// DZoom??Margin???ÑÏöî?? Sensor?êÏÑú????ÎßåÌÅº Ï∂úÎ†•?òÍ≤å ?§Ï†ï.
		//HWOw(RP(PO_HW));

		OSD_ISEL0w(0);				// OSD & Fonc ?ÖÎ†• Path ?§Ï†ï (DZOOM Module Ï∂úÎ†•)

		//DZ_DZOOM_ONw(0);			// DZOOM On
		DZPCK_PDw(0);				// Clock Enable

		YCW_CK1_PDw(0);				// Clock Enable
		YCR_CK1_PDw(0);				// DDR Read Channel 1 Clock Enable
	}
	else {
		//HWIw(RP(PO_HW)+DZ_HW_MR);				// DZoom??Margin???ÑÏöî?? Sensor?êÏÑú????ÎßåÌÅº Ï∂úÎ†•?òÍ≤å ?§Ï†ï.
		//HWOw(RP(PO_HW)+DZ_HW_MR);

		YCW_CK1_PDw(1);				// Clock Enable
		YCR_CK1_PDw(1);				// DDR Read Channel 1 Clock Enable

		IM_CGO1w(1);				// Write Enable
		//INIT_DELAY(1);				// 1 VLOCKI Í∏∞Îã§Î¶???
		IM_RON1w(1);				// Read Enable

		//DZ_DZOOM_ONw(1);			// DZOOM On
		DZPCK_PDw(1);				// Clock Enable

		OSD_ISEL0w(0xb);			// OSD & Fonc ?ÖÎ†• Path ?§Ï†ï (DZOOM Module Ï∂úÎ†•)
	}
}

void Dzoom_init(void)
{
	// DZOOM ?§Ï†ï : Margin ?ÑÏöî
	//HWIw(RP(PO_HW)+DZ_HW_MR);		// DZoom??Margin???ÑÏöî?? Sensor?êÏÑú????ÎßåÌÅº Ï∂úÎ†•?òÍ≤å ?§Ï†ï.
	//HWOw(RP(PO_HW)+DZ_HW_MR);

	// DZOOM ?§Ï†ï : Write ?§Ï†ï
	IM_IVSEL1w(0);					// DDR Write Channel1 ??sync ?§Ï†ï (ISP Sync)
	IM_ISEL1w(0x11);				// DDR Write Channel1 ??Image ?ÖÎ†• Path ?§Ï†ï (ISP Image, No Font)
	IM_HWI1w(DZ_HW/*RP(PO_HW)+DZ_HW_MR*/);	// Write???ÅÏÉÅ ?òÌèâ ?¨Í∏∞ ?§Ï†ï -> HWOw?Ä ?ôÏùº???¨Í∏∞, ?§Ï†ú DDR ?¨Ïö© ?¨Í∏∞?Ä ?ôÏùº -> ?ÑÏãúÎ°?DZ_HWÎ°??§Ï†ï
	IM_WFRC1_ONw(1);				// DDR R/W Channel 1??FRC  ?¨Ïö© ?§Ï†ï. ???ùÏù∏ Í≤ΩÏö∞ Disable
	YCW_CK1_SELw(SP(PostClk));		// Write Channel Clock ?§Ï†ï (ISP Clock 74.25MHz)
	//YCW_CK1_PDw(1);				// Clock Enable

	// DZOOM ?§Ï†ï : Read ?§Ï†ï
	IM_RFRC1_ONw(1);				// DDR Read Channel 1 FRC Enable
	IM_RHWI1w(DZ_HW/*RP(PO_HW)+DZ_HW_MR*/);	// DDR Read Channel 1??Read Image ?òÌèâ ?¨Í∏∞ ?§Ï†ï -> IM_HWI1w?Ä ?ôÏùº???¨Í∏∞, ?§Ï†ú DDR ?¨Ïö© ?¨Í∏∞?Ä ?ôÏùº -> ?ÑÏãúÎ°?DZ_HWÎ°??§Ï†ï
	IM_RVSEL1w(0);					// DDR Read Channel 1??Read Sync ?§Ï†ï (ISP Sync)
	IM_RISEL1w(4);					// DDR Read Channel 1??Read Active Path ?§Ï†ï (ISP Sync ?ôÍ∏∞??Active)
	IM_RYCB_MOD1w(1);				// Y C Ï∂úÎ†• Enable
	YCRCK1_SELw(SP(PostClk));		// DDR Read Channel 1 Clock ?§Ï†ï
	//YCR_CK1_PDw(1);				// DDR Read Channel 1 Clock Enable

	// DZOOM ?§Ï†ï
	DZ_DAONw(0/*1*/);				// DZOOM Position Auto On
	DZ_DKXY_ONw(1);					// DKY ?∞Îèô Í∏∞Îä• On
	DZ_CH_SELw(1);					// DZOOM ??Source,  DDR Read Channel1 ?†ÌÉù
	DZ_ZHLOCK_SELw(0);				// DZOOM HLOCK ?§Ï†ï (ISP ?ôÍ∏∞ H)
	DZ_BUF_ASELw(0);				// DZOOM Active ?§Ï†ï (ISP ?ôÍ∏∞ Active)
	DZ_VWOw(RP(FR_VW));				// DZOOM Vertical ?¨Í∏∞ ?§Ï†ï
	DZOOM_VSPw(0x9);				// DZOOM V ?ÑÏπò Ï°∞Ï†ï    -> ?ÅÏÉÅ ?ÑÏπòÍ∞Ä ??ÎßûÏúºÎ©????òÏùÑ Ï°∞Ï†à -> sensorÎßàÎã§ ?§Î? ???àÏùå.
	DZOOM_HSPw(0x65/*0x63*/);		// DZOOM H ?ÑÏπò Ï°∞Ï†ï   -> ?ÅÏÉÅ ?ÑÏπòÍ∞Ä ??ÎßûÏúºÎ©????òÏùÑ Ï°∞Ï†à -> sensorÎßàÎã§ ?§Î? ???àÏùå.
	//DZ_VSP_KYw(0x800);			// DZOOM Î∞∞Ïú® ?§Ï†ï      -> Í≥ÑÏÜç ?úÏñ¥
	DZ_DZOOM_ONw(1);				// DZOOM On
	DZPCK_SELw(SP(PostClk));		// DZOOM Clock ?§Ï†ï
	//DZPCK_PDw(1);					// Clock Enable

	// DZOOM ?§Ï†ï : ÏµúÏ¢Ö ?§Ï†ï
	OSD_IVSEL0w(0);					// Post??Ï∂úÎ†• Sync ?§Ï†ï (ISP Sync)
	//OSD_ISEL0w(0xb);				// OSD & Fonc ?ÖÎ†• Path ?§Ï†ï (DZOOM Module Ï∂úÎ†•)

	//IM_CGO1w(1);					// Write Enable
	//INIT_DELAY(1);				// 1 VLOCKI Í∏∞Îã§Î¶???
	//IM_RON1w(1);					// Read Enable

	DZoom();
}


//-------------------------------------------------------------------------------------------------
UINT gnBoxPosPVC[PVC_EA*2];
UINT gnBoxPltPVC/*[PVC_EA]*/;
ULONG guBoxTonePVC;
UINT gnBoxFillPVC;
UINT gnBoxOnPVC;
UINT gnBoxFmtPVC;
UINT gnBBoxPltPVC;
UINT gnBoxNumPVC;

void PrivacyBox(void)
{	// Box Privacy 32ea

	const UINT nPixelStep = CLAMP(UpBOX_MV_PXL, BOX_MVPXL_MIN, BOX_MVPXL_MAX);		//141126 LGH
	const BYTE nColorStep = CLAMP(UpBOX_COLOR_STEP, 0x01, 0xFF);					//141126 LGH

	gnBoxOnPVC = 0;		// init	14.2.20
	gnBoxFmtPVC = 0;
	gnBoxNumPVC = 0;
	guBoxTonePVC = 0;
	gnBoxFillPVC = 0;

	if(UP(PvcOn)==UP_ON)
	{
		const UINT nPRVC_CY = UP(PvcYLevel)  * 255 / nColorStep;
		const UINT nPRVC_CB = UP(PvcCBLevel) * 255 / nColorStep;
		const UINT nPRVC_CR = UP(PvcCRLevel) * 255 / nColorStep;

		gnBBoxPltPVC = (nPRVC_CB<<16)|(nPRVC_CR<<8)|(nPRVC_CY);
		gnBoxPltPVC  = (nPRVC_CY<<16)|(nPRVC_CB<<8)|(nPRVC_CR);			// box attr

		for(UINT i=0; i<PVC_EA; i++)
		{
			if(gbMnPvcCfg(i)->bAction)
			{
				const int iPosX = (gbMnPvcCfg(i)->bPosX) * nPixelStep;
				const int iSizX = (gbMnPvcCfg(i)->bSizX) * nPixelStep;

				const int iPosY = (gbMnPvcCfg(i)->bPosY) * nPixelStep;
				const int iSizY = (gbMnPvcCfg(i)->bSizY) * nPixelStep;

				gnBoxPosPVC[(gnBoxNumPVC<<1)]   = (MAX((iPosY+iSizY), 0)) | (MAX(iPosY, 0)<<16);	// y pos
				gnBoxPosPVC[(gnBoxNumPVC<<1)+1] = (iPosX+iSizX) | (iPosX<<16);						// x pos

//				gnBoxPltPVC[gnBoxNumPVC] = (nPRVC_CY<<16)|(nPRVC_CB<<8)|(nPRVC_CR);			// box attr

				guBoxTonePVC |= (UP(PvcTrans)<<(gnBoxNumPVC<<1));

				gnBoxFillPVC |= (1<<gnBoxNumPVC);
				gnBoxOnPVC |= (1<<gnBoxNumPVC);

				if(UP(PvcFormat)==1) {	// 2015112 - WHL : Add Bit Box Mode
					gnBoxFmtPVC |= (1<<gnBoxNumPVC);
				}

				gnBoxNumPVC++;
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
#undef OSD_BOX_USR
#undef OSD_BOX_PVC
#undef OSD_BOX_IMD
#define OSD_BOX_USR(CH,NAME,NUM)	OSD_BOX BOX(NAME); _BOX_INFO stBoxInfo##NAME[NUM]; BYTE gbBoxLut##NAME[NUM];
#define OSD_BOX_PVC(CH)
#define OSD_BOX_IMD(CH)
OSD_BOX_SET

void BoxSet(OSD_BOX* Box)
{
	int i;
	Box->Tone = 0;
	Box->Fill = 0;

	for(i=0; i<Box->Num; i++) {
		Box->Tone |= (Box->Info[Box->Lut[i]].b.Tone<<(i<<1));
		Box->Fill |= (Box->Info[Box->Lut[i]].b.Fill<<i);
	}
}

void BoxAtt(OSD_BOX* Box, const BYTE bID, const BYTE bFILL, const BYTE bTONE,
		const BYTE bY, const BYTE bCb, const BYTE bCr)
{
	if(bID >= Box->Siz) return;

	Box->Info[bID].b.Y    = bY;
	Box->Info[bID].b.Cb   = bCb;
	Box->Info[bID].b.Cr   = bCr;
	Box->Info[bID].b.Tone = bTONE;
	Box->Info[bID].b.Fill = bFILL;
}

void BoxPos(OSD_BOX* Box, const BYTE bID,
		const WORD wXs, const WORD wYs, const WORD wXe, const WORD wYe)
{
	if(bID >= Box->Siz) return;

	int i, k;

	for(i=0; i<Box->Num; i++) {
		if(bID <= Box->Lut[i]) break;
	}

	k = i;

	if(k < Box->Num && bID < Box->Lut[k]) {
		for(i=Box->Num; i>k; i--) Box->Lut[i] = Box->Lut[i-1];
	}

	if(!(k < Box->Num && bID == Box->Lut[k])) {
		Box->On |= (1<<Box->Num);
		Box->Num++;
	}

	Box->Lut[k] = bID;

	Box->Info[bID].b.wXs  = wXs;
	Box->Info[bID].b.wXe  = wXe;
	Box->Info[bID].b.wYs  = wYs;
	Box->Info[bID].b.wYe  = wYe;

	BoxSet(Box);
}

void BoxDraw(OSD_BOX* Box, const BYTE bID, const BYTE bFILL, const BYTE bTONE,
		const BYTE bY, const BYTE bCb, const BYTE bCr,
		const WORD wXs, const WORD wYs, const WORD wXe, const WORD wYe)
{
	BoxAtt(Box, bID, bFILL, bTONE, bY, bCb, bCr);
	BoxPos(Box, bID, wXs, wYs, wXe, wYe);
}

void BoxErase(OSD_BOX* Box, const BYTE bID)
{
	if(bID >= Box->Siz || Box->Num == 0) return;

	int i;

	for(i=0; i<Box->Num; i++) {
		if(bID == Box->Lut[i]) break;
	}

	if(i < Box->Num && bID == Box->Lut[i]) {
		Box->Num--;
		Box->On &= ~(1<<Box->Num);
		for(; i<Box->Num; i++) Box->Lut[i] = Box->Lut[i+1];
	}

	BoxSet(Box);
}

void BoxEraseAll(OSD_BOX* Box)
{
	Box->Num = 0;
	Box->On = 0;
	BoxSet(Box);
}

UINT nOSD_BOX_CH_MAX = 0;

void InitBox(void)
{
	#undef OSD_BOX_USR
	#undef OSD_BOX_PVC
	#undef OSD_BOX_IMD
	#define OSD_BOX_USR(CH,NAME,NUM)	if(i==CH) nOSD_BOX_CH_MAX = MAX(OSD_BOX_##NAME##_CH, nOSD_BOX_CH_MAX);
	#define OSD_BOX_PVC(CH)				if(i==CH) nOSD_BOX_CH_MAX = MAX(OSD_BOX_##PVC##_CH, nOSD_BOX_CH_MAX);
	#define OSD_BOX_IMD(CH)				if(i==CH) nOSD_BOX_CH_MAX = MAX(OSD_BOX_##IMD##_CH, nOSD_BOX_CH_MAX);
	for(int i=0; i<100; i++) { OSD_BOX_SET }

	//printf("Box: %d, %d, %d, %d, %d\n", OSD_BOX_AeDebug_CH, OSD_BOX_AI_CH, OSD_BOX_PVC_CH, OSD_BOX_IMD_CH, nOSD_BOX_CH_MAX);

	#undef OSD_BOX_USR
	#undef OSD_BOX_PVC
	#undef OSD_BOX_IMD
	#define OSD_BOX_USR(CH,NAME,NUM)	BOX(NAME).Info = stBoxInfo##NAME; BOX(NAME).Lut = gbBoxLut##NAME; BOX(NAME).Siz = NUM; BOX(NAME).Num = 0; BOX(NAME).On = 0;
	#define OSD_BOX_PVC(CH)
	#define OSD_BOX_IMD(CH)
	OSD_BOX_SET
}

//-------------------------------------------------------------------------------------------------
//                             0x0  0x1  0x2  0x3  0x4   0x5   0x6   0x7   0x8   0x9   0xA   0xB   0xC   0xD   0xE   0xF
//const BYTE gbTwinBitLUT[] = { 0x0, 0x3, 0xC, 0xF, 0x30, 0x33, 0x3C, 0x3F, 0xC0, 0xC3, 0xCC, 0xCF, 0xF0, 0xF3, 0xFC, 0xFF };
//#define CHG_TWIN_BIT(M)	gbTwinBitLUT[(M)&0xf]

int ISRT BoxLastUsr(OSD_BOX* Box, const int aiSta)
{
	int i,j;
	const int iEnd = MIN(aiSta + Box->Num, ISP_BOX_EA);
	for(i=aiSta,j=0; i<iEnd; i++,j++) {
		SetIsp(BOXPOS_BASE+(i<<1),     Box->Info[Box->Lut[j]].n.Y&0X0FFF0FFF);
		SetIsp(BOXPOS_BASE+((i<<1)+1), Box->Info[Box->Lut[j]].n.X&0X1FFF1FFF);
		SetIsp(BOXPLT_BASE+i,          Box->Info[Box->Lut[j]].n.Att&0xFFFFFF);
	}
	return i;
}

void ISRT BoxLast(void)
{	// Last Box apply (priority, sharing control)

	//BoxSet();
	//return;

// LGH 20150410
#if 0
  #if (model_1M)
	BOX_HSP0w(0x127);
	BOX_VSP0w(0x22);

  #else				//2M
		if((UP(OutFps)==UP_2M_720p_25_30)||(UP(OutFps)==UP_2M_720p_50_60)){		//MD, Privacy Box Start Position
			BOX_HSP0w(0x4F);	// 20161111 - WHL
			BOX_VSP0w(0x1a);
		}
		else{
			#if ((IMAGE_INPUT_MODE==2)||(IMAGE_INPUT_MODE==3)) // BT656 or BT1120 Input Setting
				BOX_HSP0w(0x00);
				BOX_VSP0w(0x00);
			#else
				BOX_HSP0w(0x4F);	// 20161111 - WHL
				BOX_VSP0w(0x09);
			#endif
		}
  #endif
#endif

	//const int DefogAutoOn = (UP(Defog) == UP_ON) && (UP(DefogMode) == UP_DEFOG_AUTO);
	//const int HistoOn = (UP(PvcOn) == UP_OFF) && (UP(Itl) == UP_OFF) && (DefogAutoOn == 0) && (gbMnDebugFnc == 1);

#if 1
	const int AeMonOn = (gbMnDebugFnc == 1);
	extern int grr;
	if(AeMonOn) { grr = 1; void AeMonOn(OSD_BOX *, const int); AeMonOn(&BOX(AeDebug), 173829904); }
	else        { grr = 0; }
#endif

	//----------------------------------------------------------------------------------------
	int i,j,k;

#if 0//(model_Lens==0)
	if(MP(MpFad_On)) {
		for(i=0; i<FADJ_EA; i++) { // Focus Assist
			SetIsp(BOXPOS_BASE+(i*2)  , gnBoxPosFADJ[(i*2)]);			// box y
			SetIsp(BOXPOS_BASE+(i*2+1), gnBoxPosFADJ[(i*2)+1]);		// box x
			SetIsp(BOXPLT_BASE+i      , gnBoxPltFADJ[i]);				// box attr
		}

		SetIsp(BOXTON_BASE  , gnBoxToneFADJ[0]);						// box tone msb
		SetIsp(BOXTON_BASE+1, gnBoxToneFADJ[1]);						// box tone lsb
		SetIsp(BOXFIL_BASE  , gnBox_BFL_FADJ);							// box fill tone

		BOSD_ON0w(0x7ffff); // USE 19 Box
	}
	else {
#endif

		//OSD_MUTE0w(1);

		//UINT nPltPVCBit = 0;
		//const UINT nBOSD_ON0 = BOSD_ON0r;
		//static UINT nPltIMDBit1d = 0;
		//UINT nPltIMDBit = 0;

		//printf("BOX : %d, %d, %d, %d\n", BOX(AeDebug).Num, gnBoxNumPVC, BOX(AI).Num, gnBoxNumIMD);

		#undef OSD_BOX_USR
		#undef OSD_BOX_PVC
		#undef OSD_BOX_IMD
		#define OSD_BOX_USR(CH,NAME,NUM)	int iSta##NAME;
		#define OSD_BOX_PVC(CH)				int iSta##PVC;
		#define OSD_BOX_IMD(CH)				int iSta##IMD; int iSkp##IMD;
		OSD_BOX_SET
		#undef OSD_BOX_USR
		#undef OSD_BOX_PVC
		#undef OSD_BOX_IMD

			extern BYTE gbMnImdDetWin;
			//const int iItlDettone = (gbMnImdDetWin && (UP(ItlDettone)==3)) ? 2 : UP(ItlDettone);	// DET TONE??3????DET WINDOW Î©îÎâ¥ ?¨Ïö© ??DET TONEÎ•?2Î°??§Ï†ï
			const int iItlDettone = (gbMnImdDetWin) ? 4 : UP(ItlDettone);							// DET WINDOW Î©îÎâ¥ ?¨Ïö© ??DET TONEÎ•?4Î°??§Ï†ï

		for(i=0,k=0; k<=nOSD_BOX_CH_MAX; k++)
		{
			#define OSD_BOX_USR(CH,NAME,NUM)	if(k == CH) {\
				iSta##NAME = i;\
				i = BoxLastUsr(&BOX(NAME), iSta##NAME);}

			#define OSD_BOX_PVC(CH)				if(k == CH) {\
				iSta##PVC = i;\
				const int iEnd##PVC = MIN(i+gnBoxNumPVC, ISP_BOX_EA);\
				for(j=0; i<iEnd##PVC; i++,j++) {\
					SetIsp(BOXPOS_BASE+(i<<1),     gnBoxPosPVC[(j<<1)]);\
					SetIsp(BOXPOS_BASE+((i<<1)+1), gnBoxPosPVC[(j<<1)+1]);\
					SetIsp(BOXPLT_BASE+i,          gnBoxPltPVC);\
					/*nPltPVCBit |= (1<<i);*/\
				}}

			#define OSD_BOX_IMD(CH)				if(k == CH) {\
				iSta##IMD = i;\
				const int iEnd##IMD = MIN(i+gnBoxNumIMD, ISP_BOX_EA);\
				iSkp##IMD = (i+gnBoxNumIMD) - iEnd##IMD;\
				for(j=iSkp##IMD; i<iEnd##IMD; i++,j++) {\
					SetIsp(BOXPOS_BASE+(i<<1),     gnBoxPosIMD[(j<<1)]);\
					SetIsp(BOXPOS_BASE+((i<<1)+1), gnBoxPosIMD[(j<<1)+1]);\
					const UINT nColorIMD = (j < (gnBoxNumIMD-1-gnBoxMskNum) || iItlDettone==3) ? (0x51<<16 | 0x5a<<8 | 0xef) :	/* Motion Box */\
										   (j < (gnBoxNumIMD-1)) ? (gnBoxMskSel&&(j==(gnBoxNumIMD-1-gnBoxMskNum+(gnBoxMskSel-1)))) ? 0xd21092 : 0x903522 : /* Area Box */\
												   	   	   	   	   (235<<16 | 128<<8 | 128) ;	/* Background Box */\
					SetIsp(BOXPLT_BASE+i, nColorIMD);\
					/*nPltIMDBit |= (1<<i);*/\
				}}

			OSD_BOX_SET
		}

		/*if(gnBoxOnIMD) {
			printf("PO %.32b\n", gnBoxOnPVC<<iStaPVC);
			if((gnBoxOnPVC<<iStaPVC) != nPltPVCBit) printf("PC %.32b\n", nPltPVCBit);
			printf("IO %.32b\n", gnBoxOnIMD<<iStaIMD);
			if((gnBoxOnIMD<<iStaIMD) != nPltIMDBit) printf("IC %.32b\n", nPltIMDBit);
			printf("\n");
		}*/

		/*UINT nErrBit = 0;
		for (i=iStaIMD; i<ISP_BOX_EA; i++) {
			if(GetIsp(BOXPLT_BASE+i) != (0x51<<16 | 0x5a<<8 | 0xef)) nErrBit |= (1<<i);
		}
		if(nErrBit) printf("%.32b\n", nErrBit);*/


		//const UINT nBoxBitMask = ~(gnBoxOnIMD<<iStaIMD | gnBoxOnPVC<<iStaPVC);
		//const UINT nBoxBitMask2L = CHG_TWIN_BIT(nBoxBitMask)     | (CHG_TWIN_BIT(nBoxBitMask>>4)<<8)  | (CHG_TWIN_BIT(nBoxBitMask>>8)<<16)  | (CHG_TWIN_BIT(nBoxBitMask>>12)<<24);
		//const UINT nBoxBitMask2H = CHG_TWIN_BIT(nBoxBitMask>>16) | (CHG_TWIN_BIT(nBoxBitMask>>20)<<8) | (CHG_TWIN_BIT(nBoxBitMask>>24)<<16) | (CHG_TWIN_BIT(nBoxBitMask>>28)<<24);

		#undef OSD_BOX_USR
		#undef OSD_BOX_PVC
		#undef OSD_BOX_IMD
		#define OSD_BOX_USR(CH,NAME,NUM)	| BOX(NAME).Tone<<(iSta##NAME<<1)
		#define OSD_BOX_PVC(CH)				| guBoxTonePVC<<(iSta##PVC<<1)
		#define OSD_BOX_IMD(CH)				| ((ULONG)(gnBoxToneIMD>>(iSkp##IMD<<1)))<<(iSta##IMD<<1)
		const ULONG uBoxTone_U = 0 OSD_BOX_SET;

		//const ULONG uBoxTone_U = ((ULONG)gnBoxToneIMD)<<(iStaIMD<<1) | guBoxTonePVC<<(iStaPVC<<1);
		//const UINT nBoxTone_L = uBoxTone_U;
		//const UINT nBoxTone_H = uBoxTone_U>>32;

		//SetIsp(BOXTON_BASE  , (GetIsp(BOXTON_BASE  )&nBoxBitMask2H) | nBoxTone_H);
		//SetIsp(BOXTON_BASE+1, (GetIsp(BOXTON_BASE+1)&nBoxBitMask2L) | nBoxTone_L);
		SetIsp(BOXTON_BASE  , uBoxTone_U>>32);
		SetIsp(BOXTON_BASE+1, uBoxTone_U);

		//SetIsp(BOXFIL_BASE  , (GetIsp(BOXFIL_BASE)&nBoxBitMask) | gnBoxFillIMD<<iStaIMD | gnBoxFillPVC<<iStaPVC);
		//SetIsp(BOXFIL_BASE  , gnBoxFillIMD<<iStaIMD | gnBoxFillPVC<<iStaPVC);
		#undef OSD_BOX_USR
		#undef OSD_BOX_PVC
		#undef OSD_BOX_IMD
		#define OSD_BOX_USR(CH,NAME,NUM)	| BOX(NAME).Fill<<iSta##NAME
		#define OSD_BOX_PVC(CH)				| gnBoxFillPVC<<iSta##PVC
		#define OSD_BOX_IMD(CH)				| (gnBoxFillIMD>>iSkp##IMD)<<iSta##IMD
		SetIsp(BOXFIL_BASE  , 0 OSD_BOX_SET);

		//BOSD_ON0w(gnBoxOnIMD<<iStaIMD | gnBoxOnPVC<<iStaPVC);	// box on/off
		#undef OSD_BOX_USR
		#undef OSD_BOX_PVC
		#undef OSD_BOX_IMD
		#define OSD_BOX_USR(CH,NAME,NUM)	| BOX(NAME).On<<iSta##NAME
		#define OSD_BOX_PVC(CH)				| gnBoxOnPVC<<iSta##PVC
		#define OSD_BOX_IMD(CH)				| (gnBoxOnIMD>>iSkp##IMD)<<iSta##IMD
		BOSD_ON0w(0 OSD_BOX_SET);

		// 2015112 - WHL : Add Bit Box Mode
		SetIsp(BOXFMT_BASE , gnBoxFmtPVC<<iStaPVC);						// box format
		SetIsp(BBOXFMT_BASE, gnBBoxPltPVC);								// bit box fill format

		/*GRP0 = nBoxBitMask;
		GRP1 = nBoxBitMask2L;
		GRP2 = nBoxBitMask2H;
		GRP3 = gnBoxTonePVC_L;
		GRP4 = gnBoxTonePVC_H;
		GRP5 = iStaPVC;
		UartTxGrp();*/

		/*if(nPltIMDBit1d != nPltIMDBit) {
			nPltIMDBit1d = nPltIMDBit;
			printf("OL %.32b\n", nBOSD_ON0);
			printf("IC %.32b\n", nPltIMDBit);
			printf("NW %.32b\n", BOSD_ON0r);
			printf("\n");
		}*/

		//OSD_MUTE0w(0);

#if 0//(model_Lens==0)
	}
#endif

	/*UINT nPvcCnt = 0;
	UINT nImdCnt = 0;
	UINT nErrCnt = 0;
	const UINT nBOSD_ON0 = BOSD_ON0r;

	for (i=0; i<32; i++) {
		if((nBOSD_ON0>>i)&1) {
			const UINT nBoxPlt = GetIsp(BOXPLT_BASE+i);

			if(nBoxPlt == (0x51<<16 | 0x5a<<8 | 0xef)) nImdCnt++;
			else if(nBoxPlt == gnBoxPltPVC) nPvcCnt++;
			else nErrCnt++;
		}
	}

	if(nImdCnt || nErrCnt) {
		printf("BLUE:%3d, RED:%3d, OTHER:%3d\n", nPvcCnt, nImdCnt, nErrCnt);
	}*/
}




/* EOF */

