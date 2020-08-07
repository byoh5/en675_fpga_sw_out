#include "dev.h"

#ifdef __USE_ISP__

#if model_TgtBd == 1
	//_regs_ BF_3(UINT _rev0 : 30, UINT PIN0_OUT_AUR : 1 ,UINT PIN0_OEN_AUR : 1 ) _rege_ _GPIO_0_AUR;
	typedef	union{UINT a; struct{ UINT PIN0_OEN_AUR:1;; UINT PIN0_OUT_AUR:1;;	UINT _rev0:30; };} _GPIO_0_AUR;
	#define GPIO_PIN0_OUT_AUR _bm(_GPIO_0_AUR,0x400FE000, (0<<3),PIN0_OUT_AUR) // 1 Bit, 1'h0, RW
	#define GPIO_PIN0_OEN_AUR _bm(_GPIO_0_AUR,0x400FE000, (0<<3),PIN0_OEN_AUR) // 1 Bit, 1'h1, RW

	//_regs_ BF_3(UINT _rev0 : 30, UINT PIN1_OUT_AUR : 1 ,UINT PIN1_OEN_AUR : 1 ) _rege_ _GPIO_1_AUR;
	typedef	union{UINT a; struct{ UINT PIN1_OEN_AUR:1;; UINT PIN1_OUT_AUR:1;; UINT _rev0:30; };} _GPIO_1_AUR;
	#define GPIO_PIN1_OUT_AUR _bm(_GPIO_1_AUR,0x400FE000, (1<<3),PIN1_OUT_AUR) // 1 Bit, 1'h0, RW
	#define GPIO_PIN1_OEN_AUR _bm(_GPIO_1_AUR,0x400FE000, (1<<3),PIN1_OEN_AUR) // 1 Bit, 1'h1, RW
#endif

#if 0
void Isp_irq_init(void)
{
	//	For VLOCKO Interrupt
	Isp_PostClk_Config(ISP_CLK_74M);		//	Isp Post Module Clock
	Isp_PostSync_Config(1, 0, 2200, 1125, 0x3a, 0x2, 0x6, 0x4, 1928, 1088, 1);	// VLOCK
	Isp_VLOCKO_init();						//	Post Sync
}
#endif

void Isp_SensorRst(void)
{
#ifdef __SENSOR__ // IITP

	INIT_DELAY(2);

	//	Sensor Init
#if model_TgtBd == 1
	SYS_GPIO0_MUX = 0;
	GPIO_PIN0_OEN_AUR = 0;
	GPIO_PIN0_OUT_AUR = 1;

	SYS_GPIO1_MUX = 0;
	GPIO_PIN1_OEN_AUR = 0;
	GPIO_PIN1_OUT_AUR = 1;

	INIT_DELAY(1);
	GPIO_PIN1_OUT_AUR = 0;
	INIT_DELAY(4);
	GPIO_PIN1_OUT_AUR = 1;
#else
  #if model_Sens==SENS_OV2718
	PCKO_SELw(3);		//	18.5 MHz
	INIT_DELAY(3);
	GpioSetOut(SENSOR_RESET_GPIO_CH,0);
	INIT_DELAY(1);
  #else
	GpioSetOut(SENSOR_RESET_GPIO_CH,0);
  #endif
	INIT_DELAY(4);
	GpioSetOut(SENSOR_RESET_GPIO_CH,1);
#endif

	INIT_DELAY(1);
#endif
}

#if model_Sens_Intf == 1	// MIPI ?�정
void APB_Write(volatile unsigned long addr, unsigned int data)
{
	*((volatile unsigned int *)(addr)) = data;
}

unsigned int APB_Read(volatile unsigned long addr)
{
	return *((volatile unsigned int *)(addr));
}
#endif

void Isp_Sensor_init(void)
{
#if model_Sens_Intf == 1	// MIPI ?�정
	//SYNC_UPw(1);
	IBT_PCK_SELw((model_Sens_Intf==0) ? M_EXT : SP(MipiClk));	// MIPI ?�정?�에 가??먼�? ?�야 ??
	IBT_PCK_PDw(1);

	APCLK_SELw(0);				//	For FPGA 148.5 MHz
	APCLK_PDw(1);
	INIT_DELAY(1);	// TODO KSH x ?�요?

	APB_Write(0x46500024,0x1f);				// Enable data, Enable clock
	// ISP CH0
	#if   (model_Sens==SENS_OS08A10) || (model_Sens==SENS_OV4689)
	APB_Write(0x46500040,((0x2<<12)|(0x2B<<2)|0x0));	// config : RAW10, VC=0, 4PPI
	#elif (model_Sens==SENS_IMX415) || (model_Sens==SENS_IMX335) || (model_Sens==SENS_IMX290)
	APB_Write(0x46500040,((0x2<<12)|(0x2C<<2)|0x0));	// config : RAW12, VC=0, 4PPI
//	APB_Write(0x46500040,((0x2<<12)|(0x2B<<2)|0x0));	// config : RAW12, VC=0, 4PPI
	#elif (model_Sens==SENS_AR0234)
	APB_Write(0x46500040,((0x2<<12)|(0x2C<<2)|0x0));	// config : RAW12, VC=0, 4PPI
	#else
	APB_Write(0x46500040,((0x2<<12)|(0x2B<<2)|0x0));	// config : RAW10, VC=0, 4PPI
	#endif

	#if	(model_Sens==SENS_OS08A10) || (model_Sens==SENS_IMX415)
	APB_Write(0x46500044,0x08800f10);		// resolution : 3856x2176
	#elif (model_Sens==SENS_IMX415) || (model_Sens==SENS_IMX335)
	APB_Write(0x46500044,0x05A00A20);		// resolution : 2560x1440
	#elif (model_Sens==SENS_OV4689)
	APB_Write(0x46500044,0x05A00A20);		// resolution : 2560x1440
	#elif (model_Sens==SENS_AR0234)
	APB_Write(0x46500044,0x04380788);		// resolution : 1920x1080
	#else
	APB_Write(0x46500044,0x04380788);		// resolution : 1920x1080
	#endif
#endif
	//----------------------------------------------------------------------------------------
	Isp_SensorRst();	// TODO KSH x enx_device_init()?�서 high�??�정?��?�??�요 ?�음?

	IspSDesPowerOn();
	IspSensorPowerOn();

	IspSDesConfig();
	IspSDesDelay();

	INIT_STR_SENSOR
	InitSensRun();

#if (model_Sens==SENS_IMX291)
	#define SENSOR_BLACK_LEVEL	0xf0	// ?�화?�역 경계부�??�이�?감소
#elif (model_Sens==SENS_IMX323)
	#define SENSOR_BLACK_LEVEL	0x3c	// ?��??�역 컬러?�이�??�주?? 감소, 미적????WDR Short 채널???�주??발생
#elif (model_Sens==SENS_IMX415)
	#define SENSOR_BLACK_LEVEL	0x0//(0x32<<2)	// IMX415 12bit출력?�면 x4
#else
	#define SENSOR_BLACK_LEVEL	0x0
#endif

	#define ISP_OFFSET	(1024-((SENSOR_BLACK_LEVEL)>>2))	// ?�EN673?�?>>2 ?��? ?�음

	PRE_GROFSw(ISP_OFFSET);
	PRE_GBOFSw(ISP_OFFSET);
	PRE_ROFSw(ISP_OFFSET);
	PRE_BOFSw(ISP_OFFSET);

	INIT_STR("ISP Sync & Sensor configuration...");
}

void Isp_PrePost_init(void)
{
	IspPreClkConfig();
	IspPostClkConfig();
	IspPreSyncConfig();
	IspPostSyncConfig();

	// Polling 방식 VLOCKO ?�용
	// - Post Clk & Sync ?�정 ???�행?�어????(?�는 Isp_irq_init() ?�용)
	// - IBT_PCK_SELw() ?�정 ?�?�밍 조절 ???�요(?�스????
	// - IF_Funcs() ?�서 VLOCKO ???�기?�하??코드 ?�행 ???�요(?�스????
	Isp_VLOCKO_init();

#if (model_Sens==SENS_OV2718)
	ASYNC_DSYNCw(1);
#endif

#if (model_Sens==SENS_IMX291) || (model_Sens==SENS_OV2718)
	INIT_DELAY(3);
	SYNC_UPw(1);
#endif

#if model_Sens_Intf == 1	// MIPI ?�정
	//	Interrupt Mask
	APB_Write(0x46500010,0xfff5fcff);		// sync

	APB_Write(0x46500048,0x00040000);		// sync
	APB_Write(0x46500008, 0xf0);			// clock all enable
	#if	(model_Sens==SENS_IMX290)
	APB_Write(0x46500004, 0x000f4301);		// Update shadow, Deskew level[15:13], Deskew enable[12], CH0 only(no data interleave), 4 lane, CSIS enable
	#else
	APB_Write(0x46500004, 0x000f5301);		// Update shadow, Deskew level[15:13], Deskew enable[12], CH0 only(no data interleave), 4 lane, CSIS enable
	#endif

	MIPI_PAGEw(1);
	MIPI_ISP_CH0_ENw(1);

	#if (model_Sens==SENS_IMX415)
		MIPI_CH0_BMODw(1);			//	0 : 14bit, 1 : 12bit, 2 : 10bit, 3 : 8bit, 4 : YC 20bit, 5 : YC 16bit,
		MIPI_CH0_HTWOw(0x112e);
		MIPI_CH0_VTWOw(0x8c9);
	#elif (model_Sens==SENS_IMX335)
		MIPI_CH0_BMODw(1);			//	0 : 14bit, 1 : 12bit, 2 : 10bit, 3 : 8bit, 4 : YC 20bit, 5 : YC 16bit,
		MIPI_CH0_HTWOw(0xCE2);
		MIPI_CH0_VTWOw(0x5DB);
	#elif (model_Sens==SENS_OV4689)
		MIPI_CH0_BMODw(2);			//	0 : 14bit, 1 : 12bit, 2 : 10bit, 3 : 8bit, 4 : YC 20bit, 5 : YC 16bit,
		MIPI_CH0_HTWOw(0xCE2);
		MIPI_CH0_VTWOw(0x5DB);
	#elif (model_Sens==SENS_IMX290)
		MIPI_CH0_BMODw(1);			//	0 : 14bit, 1 : 12bit, 2 : 10bit, 3 : 8bit, 4 : YC 20bit, 5 : YC 16bit,
		MIPI_CH0_HTWOw(0x896);
		MIPI_CH0_VTWOw(0x464);
	#elif (model_Sens==SENS_AR0234)
		MIPI_CH0_BMODw(1);			//	0 : 14bit, 1 : 12bit, 2 : 10bit, 3 : 8bit, 4 : YC 20bit, 5 : YC 16bit,
		MIPI_CH0_HTWOw(0x896);
		MIPI_CH0_VTWOw(0x464);
	#else
		MIPI_CH0_BMODw(2);			//	0 : 14bit, 1 : 12bit, 2 : 10bit, 3 : 8bit, 4 : YC 20bit, 5 : YC 16bit,
		MIPI_CH0_HTWOw(0x896);
		MIPI_CH0_VTWOw(0x464);
	#endif

	MIPI_CH0_WMODw(0);			//	Memory Write 0 : 4PPI, 1 : 2PPI, 2 : 1PPI
	MIPI_CH0_RYCw(0);			//	Memory Read  0 : RAW, 1 : YC
	MIPI_CH0_VRPOSw(0);

	MIPI_CH0_VSYNC_ALNw(1);
	MIPI_CH0_HSYNC_ALNw(1);

	INIT_DELAY(4);

	MIPI_CH0_SYNC_UPw(1);					//	MIPI Sync Sync-up
	INIT_DELAY(2);
#endif

	INIT_STR("ISP Clk/Res configuration...");
}

void Isp_Function_init(void)
{
	//	Isp Function Configuration------------------------------------------------------------
	InitAe();
	IspAgcSet();

	//DF_DETHSPw(RP(DF_HSP));
	//DF_DETHEPw(RP(FR_HW) + RP(DF_HSP) - 1);
	//DF_DETVSPw(RP(DF_VSP));
	//DF_DETVEPw(RP(FR_VW) + RP(DF_VSP) - 1);

	InitContrast();

	InitAwb();

	InitIMD();

	BOX_HSP0w(RP(BOX_HSP));
	BOX_VSP0w(RP(BOX_VSP));
	PrivacyBox();						// Box Privacy

	InitBox();

	HlMask();							// High light mask

	Isp_Gamma_Config(1,1);				//	Y/C Gamma On
	Isp_Edge_Config(1);					//	Edge Enhancement On

	//CHLPF_ONw(1);
	//CHLPF_SELw(1);

	FontSetColor(ISP_FONT_GREEN, ISP_FONT_WHITE, ISP_FONT_GRAY, ISP_FONT_YELLOW);
	//FontSetSize(BIG_FONT,BIG_FONT_AREA,BORDER_THICK);

	//FontCharInit(gnFontChar0, ARRAY_SIZE(gnFontChar0));		//	Write Font Data
	//FontClrAll(NO_ALPHA,MN_WHITE);

	FORCE_ABT_SOFFw(1);

	Isp_Dnr3d_Config(USE_ISP_FRC, SP(PreClk), 0x80, 0x40, 0x20);

	//Isp_Dnr2d_Config(FN_ON, DNR2D_SUM_MOD, DNR2D_CNT8, 0x38, 0x30);
	Isp_Dnr2d_Config(FN_ON, (model_TgtBd == 1) ? 3 : SP(Dnr2dICSel), SP(Dnr2dOCSel));
	//Isp_Defect_Config(FN_ON, DF_SUM_6, DF_SUM_4, DF_WGT_CASEB, DF_WGT_CASEB, DF_SLOPE_NOR, DF_GTHRES, DF_RBTHRES, DF_MAX, DF_MIN, 3);

	INIT_STR("ISP Function configuration...");
}

void Isp_DDR_init(void)
{
	//	DDR Init---------------------------------------
	//Isp_Ddr_Cong();
	printf("Isp_Ddr_Cong...\r\n");

#if USE_ISP_FRC == 0
	SD_MODw(3);				// FRC OFF
	BUS_RD_RSTw(1);
	SYNC_UPw(1);
	INIT_DELAY(1);
	VLOCKI_POSw(0x23);		// for IMX415
	HLOCKI_POSw(0x10e0);	//		"
	OCSELw(2);
	printf("USE_ISP_FRC == 0...\r\n");
#else
	#if model_1M
		#define R_LTC	0x260
	#elif model_4M
		#define R_LTC	0xa40
	#elif model_8M
		#define R_LTC	0xf80
	#else// model_2M & model_2M30p
		#define R_LTC	0x500
	#endif

	// R_LTC값�? ASIC ?�서 바�????�음
	DDR_RDNR_LTCw(R_LTC);
	DDR_RWDR_LTCw(R_LTC);
	DDR_RFRC_LTCw(R_LTC);
	DDR_RYC_LTCw(R_LTC);

	//INIT_DELAY(1);
	SD_MODw(0);			// 0 -> FRC 2 Page (Adr2, Adr3, Adr4 Don't care),  3 -> FRC OFF

	BUS_RD_RSTw(1);
	INIT_DELAY(1/*4*/);
	CPU_FRC_ENw(1);		// DDR OFF,  SD_MODw(0) ?�후 1 VLOCK Delay ???�정?�야 ??!!
#endif
}

void Isp_Digital_input_init(void)
{

#if 0 // IITP
	extern void TVI_Init(void);
	TVI_Init(); // I2C 1 Initialization needed for TP2827
//	INIT_STR("TP2827 Initialization...");
	printf("TP2827 Initialization...\r\n");
	//Isp_DigIn_CH0_Config(IF_BT656_SDR, 6, IF_NEGEDGE, 2, 1920, 0, 1080, FN_ON);
	//Isp_DigIn_CH0_Config(IF_BT656_DDR, 6, IF_NEGEDGE, 2, 1920, 0, 1080, FN_ON);
	Isp_DigIn_CH0_Config(IF_BT656_DDR, 6, IF_NEGEDGE, 2, 1280, 0, 720, FN_ON); // IITP 720P

#elif 1 // BT1120_8BIT_SDR input for IITP

	//Isp_DigIn_CH0_Config(IF_BT1120_8BIT_SDR, 6, IF_NEGEDGE, 2, 1920, 0, 1080, FN_ON);
	Isp_DigIn_CH2_Config(IF_BT1120_16BIT, 6, IF_NEGEDGE, 2, 1920, 0, 1080, FN_ON);

#else // IITP
	//	External Digital Input Configuration----------------------------------------
	Isp_DS_Step_Config(0x40);														//	Down-Scale Ratio Setting
	Isp_Pip_Clk_Config(1, CLK_74M, PIP_MAIN_ISP, PIP_ISP_SYNC, PIP_NO_MMASK);		//	PIP Main Setting
	Isp_Vlc_Config(VLC_6BIT);

#ifdef	USE_DIG_CH2		//	Digital Input Channel 2 (BT1120 YCMuxed 8Bit)
	INIT_STR("Digital Channel2 Input  --------->");
	Isp_DigIn_CH2_Config(IF_BT1120_8BIT_SDR, 0, IF_NEGEDGE, 4, 1920, 0, 1080, IF_MODE_SET);							//	Digital Channel 2 Setting		(Input Mode, Input Clock Delay, Clock Latch Position, Hsp, Hw, Vsp, Vw, On/Off)
  #ifdef	USE_WRCH2_DS1_RDCH2_PIP0
	Isp_DS1_Config(DS_DIGITAL_CH2_PATH, CLK_DIG_CH2_DIV2, 0x80, 0x80, 1920, 1080, LPF_LV3, LPF_LV3, 0, 0, FN_ON);	//	Down-Scale 1 Setting
	Isp_DS1_Edge_Enhance_Config(FN_ON, 0x40, 0x10, 0xe0, DS_APT_ROI_OFF, 0, 0, 0, 0, 0, DS_ROI_OSD_OFF);			//	Down-Scale Aperture Setting
//	Isp_WrCh2_FrcAdr(0x82b4000, 0x82f4000, 0x8314000, 0x8354000, 0x8374000, 0x83b4000);								//	DDR Write Address Setting
	Isp_WrCh2_Config(WR_CH_DOWN_SCALER1, 960, WR_DIG_CH2_SYNC, WR_COLOR, NO_INTERLACE, NO_VLCBIT, CLK_DIG_CH2_DIV2, USE_ISP_FRC, 0, DDR_WR_FIRST, DDR_RDCH2, IF_MODE_SET);	//	DDR Write Channel Setting -> Down-Scale Image
//	Isp_WrCh2_Config(WR_CH_DOWN_SCALER1, 960, WR_DIG_CH2_SYNC, WR_COLOR, NO_INTERLACE, VLC_6BIT, CLK_DIG_CH2_DIV2, USE_ISP_FRC, 0, DDR_WR_FIRST, DDR_RDCH2, IF_MODE_SET);	//	DDR Write Channel Setting -> Down-Scale Image

	Isp_WrCh2_Wr(WR_WRITE_CONTINU_MODE, FN_ON, FN_ON);																		//	Start Write...
	Isp_Pip_Ch0_Config(FN_ON, PIP_DDR_RD_CH2, 0x42, 0x226, 960, 540, PIP_LINE_ON, LINE_GREEN, PIP_MIX_100, 0x600);

	Isp_RdCh2_Config(RD_CH_PIP0, 960, WR_COLOR, CLK_74M, RD_ISP_SYNC, NO_VLCBIT, USE_ISP_FRC, DDR_WR_FIRST, DDR_WRCH2, IF_MODE_SET);		//	DDR Read Channel Settingg
//	Isp_RdCh2_Config(RD_CH_PIP0, 960, WR_COLOR, CLK_74M, RD_ISP_SYNC, VLC_6BIT, USE_ISP_FRC, DDR_WR_FIRST, DDR_WRCH2, IF_MODE_SET);		//	DDR Read Channel Settingg
  #endif
#endif

#ifdef	USE_DIG_CH3		//	Digital Input Channel 3 (BT1120 YCMuxed 8Bit)
	INIT_STR("Digital Channel3 Input--------->");
	Isp_DigIn_CH3_Config(IF_BT1120_8BIT_SDR, 4, IF_POSEDGE, 4, 1920, 0, 1080, IF_MODE_SET);							//	Digital Channel 2 Setting	(Input Mode, Input Clock Delay, Clock Latch Position, Hsp, Hw, Vsp, Vw, On/Off)
  #ifdef	USE_WRCH3_DS2_RDCH3_PIP1
	Isp_DS2_Config(DS_DIGITAL_CH3_PATH, CLK_DIG_CH3_DIV2, 0x80, 0x80, 1920, 1080, LPF_LV3, LPF_LV3, 0, 0, FN_ON);	//	Down-Scale 2 Setting
	Isp_DS2_Edge_Enhance_Config(FN_ON, 0x40, 0x10, 0xe0, DS_APT_ROI_OFF, 0, 0, 0, 0, 0, DS_ROI_OSD_OFF);			//	Down-Scale Aperture Setting
//	Isp_WrCh3_FrcAdr(0x8194000, 0x81d4000, 0x81f4000, 0x8234000, 0x8254000, 0x8294000);								//	DDR Write Address Setting
	Isp_WrCh3_Config(WR_CH_DOWN_SCALER2, 960, WR_DIG_CH3_SYNC, WR_COLOR, NO_INTERLACE, NO_VLCBIT, CLK_DIG_CH3_DIV2, USE_ISP_FRC, 0, DDR_WR_FIRST, DDR_RDCH3, IF_MODE_SET);	//	DDR Write Channel Setting -> Down-Scale 2 Image
//	Isp_WrCh3_Config(WR_CH_DOWN_SCALER2, 960, WR_DIG_CH3_SYNC, WR_COLOR, NO_INTERLACE, VLC_6BIT, CLK_DIG_CH3_DIV2, USE_ISP_FRC, 0, DDR_WR_FIRST, DDR_RDCH3, IF_MODE_SET);	//	DDR Write Channel Setting -> Down-Scale 2 Image

	Isp_WrCh3_Wr(WR_WRITE_CONTINU_MODE, FN_ON, FN_ON);																		//	Start Write...
	Isp_Pip_Ch1_Config(FN_ON, PIP_DDR_RD_CH3, 0x3fe, 0x226, 960, 540, PIP_LINE_ON, LINE_BLUE, PIP_MIX_100, 0x700);

	Isp_RdCh3_Config(RD_CH_PIP1, 960, WR_COLOR, CLK_74M, RD_ISP_SYNC, NO_VLCBIT, USE_ISP_FRC, DDR_WR_FIRST, DDR_WRCH3, IF_MODE_SET);			//	DDR Read Channel Setting
//	Isp_RdCh3_Config(RD_CH_PIP1, 960, WR_COLOR, CLK_74M, RD_ISP_SYNC, VLC_6BIT, USE_ISP_FRC, DDR_WR_FIRST, DDR_WRCH3, IF_MODE_SET);			//	DDR Read Channel Setting
  #endif
#endif

	//INIT_STR("Digital Input configuration...");

#endif // IITP
}

void OutMode(void)
{
#if 0
	static BYTE bOutFps = 0xee;
	static BYTE bSysFreq = 0xee;

	if(bOutFps!=UP(OutFps) || bSysFreq!=UP(SysFreq)) {
#endif
		extern UINT gnVDI_CHG;
		gnVDI_CHG = 2;

		FreqAdjust();				// FPS_VDO & FPS_VDI �?gnAeVtw & gnAeHtw ?�정

		Isp_PrePost_init();			// ISP Pre & Post??Clk�?Res ?�정

		IspDout0SyncConfig();

#if model_TgtBd == 2	// Test HD-SDI Output by Down-Scale
		//Isp_Dout1_Sync_Config(2200, 0x1b, 0x440, 0, 0x2a, 1920, 1080);							//	For HD-SDI Output (Scaling Image)
		//Isp_Frc_Adr_Config(0x80a0000, 0x8140000, 0x0000000, 0x0000000, 0x0000000);			//	4 K
		//YCW_DCK2_PDw(0); YCW_DCK2_SELw(CLK_74M); YCW_DCK2_PDw(1);
#else
		IspDout1SyncConfig();
#endif
		//Isp_Output_init();			// Output ?�정

#if 0
		bOutFps = UP(OutFps);
		bSysFreq = UP(SysFreq);
	}
#endif
}

void Digital_OutputSet(void)
{

#if 1 // BT1120_8BIT_SDR input for IITP

	//	Digital Output Configuration
	Isp_DigOut_Config(IFO_OPIN_0TO15,  IFO_BT1120_16BIT, IFO_RD_SYNC1, (SP(PostClk)==C_148M) ? IFO_1080_60P : IFO_1080_30P, IFO_DIG_RDCH3_FONT_PATH, 0, 0);
	//Isp_DigOut_Config(IFO_OPIN_0TO15,  IFO_BT1120_16BIT, IFO_RD_SYNC1, IFO_720_30P, IFO_DIG_CH0_DIRT_PATH, 0, 0); // IITP 720P
	Isp_Dout_Clock0_Config(FN_ON, CLK_74M, 6, CLK_INVERSE);														//	DCKO0 Pin Clock Out	->	FPGA HDMI,  DCKO0_DLYw 0 -> 6 for VU Bd.

    //YCW_CK1_SELw(SP(PostClk));	// Write Channel Clock ?�정 (ISP Clock 74.25MHz)
	//YCW_CK1_PDw(1);				// Clock Enable
	//IM_HWI1w(RP(FR_HW));		// Write???�상 ?�평 ?�기 ?�정 -> HWOw?�??�일???�기, ?�제 DDR ?�용 ?�기?�??�일
	//IM_CGO1w(1);				// Write Enable

	#if 1 // mjs - 200805 // RYC_VTWO1[11:0] / W/R DDR buffering for HDMI Output

	HSPI1w(4); VSPI1w(0);
	VLOCKO_IT_POS0w(0x43e);
	HLOCKO_IT_POS0w(0x1d);

	// Write ?�정
	YCW_CK3_PDw(0);
	//YCW_CK1_SELw(7);
	YCW_CK3_SELw(5);
	YCW_CK3_PDw(1);
	//IM_IVSEL1w(1);
	//IM_ISEL1w(4);
	IM_IVSEL3w(3);
	IM_ISEL3w(6);
	IM_HWI3w(0x780);
	IM_VWI3w(0x438);
	IM_WFRC3_ONw(1);
	// Read ?�정
	RYCCK1_PDw(0);  RYCCK1_SELw(2); RYCCK1_PDw(1);
	RYC_VWI1w(0x438);
	RYC_HWI1w(0x780);
	RYC_HTWO1w(0x896);
	RYC_VTWO1w(0x464);

	IM_RFRC3_ONw(1);
	IM_RVSEL3w(5);
	IM_RISEL3w(5);
	IM_RHWI3w(0x780);
	YCR_CK3_PDw(0);
	YCRCK3_SELw(2);
	YCR_CK3_PDw(1);

	BUS_RD_RSTw(1);
	BUS_WR_RSTw(0xfffff);

	IM_CGO3w(1);    // Write

	OSD_IVSEL0w(5);
	OSD_ISEL0w(8);
	POST_OSEL0w(0);
	ITU_SSEL0w(5);
	ITU_ASEL0w(0x11);

	WaitXms(70); // ??70ms ?�상 Delay ??
	IM_RON3w(1);    // read Enable
	// Output Clock Setting
	PR_CK0_SELw(2);
	FN_CK0_SELw(2);
	ITCK0_PDw(0);    ITCK0_SELw(2);    ITCK0_PDw(1);
	DITCK0_PDw(0);   DITCK0_SELw(2);  DITCK0_PDw(1);
	OTCK0_PDw(0);   OTCK0_SELw(2);  OTCK0_PDw(1);
	DO0_CK_PDw(0);  DO0_CK_SELw(2); DO0_CK_PDw(1);
	DO1_CK_PDw(0);  DO1_CK_SELw(2); DO1_CK_PDw(1);
	#endif

#else
	//	Digital Output Configuration----------------------------------------------------------
	//IspDout0SyncConfig();
	//IspDout1SyncConfig();

	//	Digital Output Configuration
	Isp_DigOut_Config(IFO_OPIN_0TO15,  IFO_BT1120_16BIT, IFO_ISP_SYNC, (SP(PostClk)==C_148M) ? IFO_1080_60P : IFO_1080_30P, IFO_ISP_PATH, 0, 0);		//	For HDMI (PinList, Dout Mode, Read Sync, Resolution, Output Source Path, Vsp, Hsp)

	Isp_DigOut_Config(IFO_OPIN_16TO31, IFO_BT1120_16BIT, IFO_ISP_SYNC, (SP(PostClk)==C_148M) ? IFO_1080_60P : IFO_1080_30P, IFO_ISP_PATH, 0, 0);		//	For HD-SDI (PinList, Dout Mode, Read Sync, Resolution, Output Source Path, Vsp, Hsp)
//	Isp_DigOut_Config(IFO_OPIN_24TO31, IFO_BT1120_8BIT_SDR, IFO_ISP_SYNC, IFO_1080_30P, IFO_ISP_PATH, 0, 0);		//	For HD-SDI (PinList, Dout Mode, Read Sync, Resolution, Output Source Path, Vsp, Hsp)


	Isp_Dout_Clock1_Config(FN_ON, SP(PostClk), 6, CLK_INVERSE);														//	DCKO1 Pin Clock Out	->	FPGA HDSDI	(Clken, ClkFrq, ClkDelay, ClkInv),  DCKO1_DLYw 0 -> 6 for VU Bd.
//	Isp_Dout_Clock1_Config(FN_ON, CLK_148M, 0, CLK_INVERSE);													//	DCKO1 Pin Clock Out	->	FPGA HDSDI	(Clken, ClkFrq, ClkDelay, ClkInv)
	Isp_Dout_Clock0_Config(FN_ON, SP(PostClk), 6, CLK_INVERSE);														//	DCKO0 Pin Clock Out	->	FPGA HDMI,  DCKO0_DLYw 0 -> 6 for VU Bd.


#if 1 // For image write dump
    YCW_CK1_SELw(SP(PostClk));	// Write Channel Clock ?�정 (ISP Clock 74.25MHz)
	YCW_CK1_PDw(1);				// Clock Enable
	IM_HWI1w(RP(FR_HW));		// Write???�상 ?�평 ?�기 ?�정 -> HWOw?�??�일???�기, ?�제 DDR ?�용 ?�기?�??�일
	IM_IVSEL1w(0);				// DDR Write Channel1 ??sync ?�정 (ISP Sync)
	IM_ISEL1w(0xC);				// DDR Write Channel1 ??Image ?�력 Path ?�정 (ISP Image, No Font)
	IM_WFRC1_ONw(1);			// DDR R/W Channel 1??FRC  ?�용 ?�정. ???�인 경우 Disable
	IM_CADR1_P0w(IM_YADR1_P0r + ((RP(FR_HW)*RP(FR_VW))>>4));
	//INIT_DELAY(1);			// Delay need ?
	IM_CGO1w(1);				// Write Enable
#else
	//Dzoom_init();
	Init_LCD_Control();
#endif
#if 0
	//extern void TVI_Init(void);
	//TVI_Init(); // I2C 1 Initialization needed for TP2827
	INIT_STR("TP2827 Initialization...");

	//void MCP2515_Init(void);
	//MCP2515_Init(); // SPI 2,3 Initialization needed for CAN Deviece
	INIT_STR("MCP2515 Initialization...");
#endif
#endif

	//INIT_STR("Output configuration...");
}

void Analog_OutputSet(void)
{
	Isp_Cvbs_Config(UP(Cvbs), NTSC, FREQ_27M, ISP_148M/*ISP_74M*/, DS_ISP_FONT_PATH, NO_VLCBIT, 0x7a, 0xe);
}

void Isp_init(void)
{	// The execution order of the functions is important !!!
	InitDataSet();				// Data setting for initialization
	AppLoadPar();				// load parameter from memory
	InitMenu();					// If hold down a specific key, reset the user parameters.

#if 0 // IITP
	InMode();

	Isp_Sensor_init();			// ISP Sync ?�정 �?Sensor Initial

	FONT_INIT();				// SetFontChg() 보다 먼�? ?�행?�어????
	InitUsrParChgAll();			// SensFlip(), SensMirror() ?�행???�해 Isp_Sensor_init()??먼�? ?�정?�어????
	ChangeMenuSize();

	OutMode();

	Isp_Function_init();		// OSD Font �?ISP 기능 ?�정
#endif
}

void Digital_InputSet(void)
{
	Isp_Digital_input_init();	// Digital Input configuration
}

void make_box_set(void)
{
	FontInit(0x3a, RP(FONT_OFY), 1, RP(FR_HW));
	UsrParReset();
	InitUsrParChgAll();
	ChangeMenuSize();
	FontSetColor(ISP_FONT_GREEN, ISP_FONT_WHITE, ISP_FONT_GRAY, ISP_FONT_YELLOW);

	InitIMD();
	BOX_HSP0w(0x10/*RP(BOX_HSP)*/);
	BOX_VSP0w(RP(BOX_VSP));
	PrivacyBox();						// Box Privacy

	InitBox();
}

void DownScaleSet(void)
{
#if 1 // IITP
	Isp_DS2_Config(DS_DIGITAL_CH2_PATH, CLK_74M, 0x194, 0xe6, 1920, 1080, LPF_LV3, LPF_LV3, 0, 0, FN_ON);
	//Isp_DS0_Config(DS_DIGITAL_CH0_FONT_PATH, CLK_74M, 0x10D, 0x99, 1280, 720, LPF_LV3, LPF_LV3, 0, 0, FN_ON); // IITP 720P

	CDS2_HWw(304); CDS2_VWw(300); // DS H,V Width

	YUVCK1_SELw(5);
	YUVCK1_PDw(1);
	YUV1_WSELw(2);
	YUV1_DDR_ENw(1);
	YUV1_HWIw(304);
	YUV1_WADRw(0x9400000);
	YUV1_CGOw(1);
	//YUV_GOw

	YUV1_ORDw(0); // 00 : CbYCr, 1 : YCbCr

#endif
}

void Vcap_ChannelSet(void)
{
	Isp_DDR_init();				// ISP ?�서 ?�용?�는 DDR ?�정
}

void Init_Visp(void)
{
	Isp_init(); // ISP & Sensor Initial
	printf("Isp_init\r\n");

	Digital_InputSet(); // BT.XXX Input interface setting
	printf("Digital_InputSet\r\n");
}

void Init_Vcap(void)
{
	DownScaleSet();
	printf("DownScaleSet\r\n");

	make_box_set();

	//Vcap_ChannelSet();
}

void Init_Vout(void)
{
	Digital_OutputSet(); // BT.XXX Output interface setting
	printf("Digital_OutputSet\r\n");

	//Analog_OutputSet(); // CVBS, HD Analog
	//printf("Analog_OutputSet\r\n");
}

void Init_Virq(void)
{
	//extern void ParFncTest(void); ParFncTest();		// TODO KSH ??ParFncTest()

	VIRQO_ENw(1);				// VLOCKO IRQ Routine Test, enx_exirq_source1() ?�수?�서 CLI_VLOCKOw(1) ?�행??
	VIRQI_ENw(1);				// Sensor FPS 출력??

	VIRQI_EN_Tw(1);
	//CLI_VLOCKI_Tw(1);		// TODO KSH> 컴파??문제?

#if 0
	//YC_OSELw(0x11);
	PCKO_PDw(0);	// Sensor가 Master�??�작?�고 ?�는 경우 SLVw(0)?�기 ?�에 Sensor Clock Off ?�야 ??
	SLVw(0);
	SYNC_BYSw(1);
	INSELw(0x6);
#endif
}

void Hdmi_Check(void)
{
#ifdef __HDMI_SILICON__
	BYTE DetFmt0[2] = {0,0};

	Hdmi(DetFmt0);
	WriteByteTPI(0x63,0x40);
//	INIT_STR("HDMI Detect format...");
#endif
}

void isp_DispLogo(void)
{
	const BYTE bLogo[][14] = {{142,143,146,147,150,151,168,169,172,173,176,177,180,181},
							  {144,145,148,149,152,153,170,171,174,175,178,179,182,183}};

	FontStr(0,0,(const char*)bLogo[0],14);
	FontStr(1,0,(const char*)bLogo[1],14);
}

void isp_DispTime(void)
{
	static UINT VO_CNT = 0;
	VO_CNT++;

	static ULONG isp_main_first_time = 0;
	if(isp_main_first_time==0) isp_main_first_time = BenchTimeStart();
	const UINT nCur_ms = BenchTimeStop(isp_main_first_time)/1000;

	static ULONG isp_main_start_time = 0;
	const UINT isp_main_call_time = BenchTimeStop(isp_main_start_time);
	isp_main_start_time = BenchTimeStart();
	if(isp_main_start_time) FontDecEx(3, 4, NO_ALPHA, MN_YELLOW, isp_main_call_time, 6, 1);
	FontStr(3,0,"VLO",3);
	FontStr(3,10,"us",2);

	extern UINT gnVDI_4FPS;
	const UINT nFPS_Float = gnVDI_4FPS&3;
	FontStr(4,0,"VDI",3);
	FontDecEx(4, 4, NO_ALPHA, MN_YELLOW, gnVDI_4FPS>>2, 3, 1);
	FontCharEx(4,7, NO_ALPHA, MN_YELLOW, '.');
	FontStrEx(4,8, NO_ALPHA, MN_YELLOW, (nFPS_Float==0) ? "00": (nFPS_Float==1) ? "25" : (nFPS_Float==2) ? "50" : "75", 2);
	FontStr(4,10,"FPS",3);

	#define DISP_TIME_Y		17
	#define DISP_TIME_X		0

	//FontStr(DISP_TIME_Y, DISP_TIME_X, "TIME",4);

	extern UINT gnVoIrqCnt;
	FontStrEx(DISP_TIME_Y+1, DISP_TIME_X,    NO_ALPHA, MN_GREEN,  "IRQ",3);
	FontDecEx(DISP_TIME_Y+1, DISP_TIME_X+3,  NO_ALPHA, MN_YELLOW, (gnVoIrqCnt*1000)/FPS_VDO, 10, 1);
	FontStr(DISP_TIME_Y+1, DISP_TIME_X+13, "ms",2);

	FontStrEx(DISP_TIME_Y+2, DISP_TIME_X,    NO_ALPHA, MN_GREEN,  "CPU",3);
	FontDecEx(DISP_TIME_Y+2, DISP_TIME_X+3,  NO_ALPHA, MN_YELLOW, nCur_ms, 10, 1);
	FontStr(DISP_TIME_Y+2, DISP_TIME_X+13, "ms",2);

	FontStrEx(DISP_TIME_Y+3, DISP_TIME_X,    NO_ALPHA, MN_GREEN,  "VLO",3);
	FontDecEx(DISP_TIME_Y+3, DISP_TIME_X+3,  NO_ALPHA, MN_YELLOW, (VO_CNT*1000)/FPS_VDO, 10, 1);
	FontStr(DISP_TIME_Y+3, DISP_TIME_X+13, "ms",2);
}

#if 0
void isp_LedCtrl(void)
{
	static UINT LED_FLG = 0;

	//	LED Display when it operated
	if(LED_FLG<10) { GPIO_PIN55_OUT = 1; /*FontStrEx(0,gnFontXw-5,NO_ALPHA,MN_GREEN,"EN675",5);*/ } // 10 Frames On		// TODO KSH> GPIO_IR_LED ?�서 GPIO 55 ?�용
	else		   { GPIO_PIN55_OUT = 0; /*FontClr(0,gnFontXw-5,5);*/                         } // 10 Frames Off		// "

	LED_FLG = (LED_FLG<20) ? (LED_FLG+1) : 0;
}
#endif

UINT IspMsgFnc(UINT anMsg)
{
	UINT nErrBit = 0;
	int i;
	const WORD wAdr = anMsg>>16;
	const WORD wDat = anMsg&0xFFFF;
	BYTE *dest = (BYTE*)ISP_MSG_AREA;

	switch(anMsg) {
		case 0x40000001 :
			//UsrParCpy(dest, gbUsrParTbl);
			for(i=2; i<UPtoMSG(USR_PAR_EA); i++) *(dest+i) = gbUsrParTbl[MSGtoUP(i)];
			break;
		case 0x40000003 : {
#if 0
				__attribute__((__aligned__(4))) BYTE tmp[USR_PAR_EA];
				for(i=0; i<UPsti(ISP_BINARY_INFO); i++) tmp[i] = gbUsrParTbl[i];
				for(   ; i<USR_PAR_EA            ; i++) tmp[i] = *(dest+UPtoMSG(i));
				UsrParCpy(gbUsrParTbl, tmp);
#else
				__attribute__((__aligned__(4))) BYTE ParOri[USR_PAR_EA];
				for(i=0; i<USR_PAR_EA; i++) ParOri[i] = gbUsrParTbl[i];
				for(i=UPstinv(ISP_BINARY_INFO)+1; i<USR_PAR_EA; i++) gbUsrParTbl[i] = *(dest+UPtoMSG(i));
				menu_val_chack();

				for(i=UPstinv(ISP_BINARY_INFO)+1; i<USR_PAR_EA; i++) {
					if(gbUsrParTbl[i] != *(dest+UPtoMSG(i))) {
						gbUsrParTbl[i] = ParOri[i];
						nErrBit |= UsrParBit(i);    // ?�못??Shared Memory 변�?
						printf("[%X] : %d is wrong. Change to %d.\n", i, *(dest+UPtoMSG(i)), ParOri[i]);

						*(dest+UPtoMSG(i)) = gbUsrParTbl[i];
					}

					if(gbUsrParTbl[i] != ParOri[i]) printf("[%X] : %d to %d change completed.\n", i, ParOri[i], gbUsrParTbl[i]);
				}

				UsrParCpy(ParOri, gbUsrParTbl);
				menu_redraw(1,0);	// OSD MENU가 출력 중이�?변경사???�데?�트

				//if(nErrBit) printf("Error Bit : %.32b\n", nErrBit);
#endif
			}
			break;
		default :
			if(UPtoMSG(UPstinv(ISP_BINARY_INFO)) < wAdr && wAdr < UPtoMSG(USR_PAR_EA)) {
				//hwflush_dcache_range(dest, (UPtoMSG(USR_PAR_EA)+63)&~3);
				//SetByte(dest+wAdr, UsrParSiz(MSGtoUP(wAdr)), wDat);

				UINT nParOri = 0;
				const UINT nAdr = wAdr;//MSGtoUP(wAdr);
				const UINT nSiz = UsrParSiz(nAdr);
				SetByte((BYTE*)&nParOri, nSiz, GetByte(gbUsrParTbl+nAdr, nSiz));
				SetByte(gbUsrParTbl+nAdr, nSiz, wDat);
				menu_val_chack();
#if 1
				if(GetByte(gbUsrParTbl+nAdr, nSiz) != wDat) {
					SetByte(gbUsrParTbl+nAdr, nSiz, nParOri);
					nErrBit |= UsrParBit(nAdr);
					printf("[%X] : %d is wrong. Change to %d.\n", nAdr, wDat, nParOri);
				}

				const UINT nVal = GetByte(gbUsrParTbl+nAdr, nSiz);
				if(nVal != nParOri) printf("[%X] : %d to %d change completed.\n", nAdr, nParOri, nVal);

#else
				for(i=0; i<nSiz; i++) {
					if(gbUsrParTbl[nAdr+i] != *(((BYTE*)&wDat)+i) ) {
						gbUsrParTbl[nAdr+i] = ParOri[i];
						nErrBit |= UsrParBit(nAdr+i);
						printf("[%X] : %d is wrong. Change to %d.\n", nAdr+i, *(((BYTE*)&wDat)+i), ParOri[i]);

						//*(dest+UPtoMSG(i)) = gbUsrParTbl[nAdr+i];
					}

					if(gbUsrParTbl[nAdr+i] != ParOri[i]) printf("[%X] : %d to %d change completed.\n", nAdr+i, ParOri[i], gbUsrParTbl[nAdr+i]);
				}
#endif
				UsrParChg(nAdr);
				menu_redraw(1,0);
			}
	}

	return nErrBit;
}

void CPUtoISPcallback(void *ctx)
{
	//while (CPU_TO_ISP_MSG_MUTEX);

	SHREG_RSP = IspMsgFnc(SHREG_CMD);	// SHREG_RSP ?�시 ?�용

	printf("CPU to ISP!(%X)\n", SHREG_CMD);

	SHREG_CMD = 0;
	CPU_TO_ISP_MSG_MUTEX = 0;

	BtoAIrqCall();
}

void IF_Funcs(void)
{
	const ULONG IspIfTimeSta = rdcycle();
	static ULONG IF_Funcs_Time = 0;

	if(ISP_RIRQ_VOr) {			// VLOCKO ???�기?�하???�행
		CLI_VLOCKO_Tw(1);

		isp_DispTime();
		isp_DispLogo();
		//isp_LedCtrl();

		//DebugDisp2(1, Dec, "UPTEST0", 25, 0, gbUsrParTbl[UPi(LckDly)], 4)
		//DebugDisp2(1, Dec, "UPTEST1", 26, 0, UpList->LckDly, 4)
		//DebugDisp2(1, Dec, "UPTEST2", 27, 0, UpListEx->Sensor.LckDly, 4)
		//DebugDisp2(1, Dec, "UPTEST0", 25, 0, gbUsrParTbl[UPi(CamTitle2)], 4)
		//DebugDisp2(1, Dec, "UPTEST1", 26, 0, UpList->CamTitle2, 4)
		//DebugDisp2(1, Dec, "UPTEST2", 27, 0, UpListEx->MENU_SYSTEM.CamTitle2, 4)
		//DebugDisp2(1, Dec, "UPTEST0", 25, 0, gbUsrParTbl[UPi(Sensor_FPS)], 4)
		//DebugDisp2(1, Dec, "UPTEST1", 26, 0, UpList->Sensor_FPS, 4)
		//DebugDisp2(1, Dec, "UPTEST2", 27, 0, UpListEx->ISP_BINARY_INFO.Sensor_FPS, 4)
		//DebugDisp2(1, Dec, "UPTEST0", 25, 0, gbUsrParTbl[UP_END], 4)
		//DebugDisp2(1, Dec, "UPTEST1", 26, 0, UpList->End, 4)
		//DebugDisp2(1, Dec, "UPTEST2", 27, 0, UpListEx->End, 4)
		//DebugDisp2(1, Dec, "UPTEST0", 25, 0, gbMnPvcCfg(0)->bAction, 4)
		//DebugDisp2(1, Dec, "UPTEST1", 26, 0, UpList->PVC0.bAction, 4)
		//DebugDisp2(1, Dec, "UPTEST2", 27, 0, UpListEx->PVC0.bAction, 4)
		DebugDisp2(1, Dec, "UPTEST0", 25, 0, gbMnImdCfg(3)->bSizY, 4)
		DebugDisp2(1, Dec, "UPTEST1", 26, 0, UpList->IMD3.bSizY, 4)
		DebugDisp2(1, Dec, "UPTEST2", 27, 0, UpListEx->IMD3.bSizY, 4)

		//hwflush_dcache_range(&((UP_LIST_EX*)UPtoMSG(ISP_MSG_AREA))->IMD3.bSizY, 64);
		DebugDisp2(1, Dec, "UPTEST3", 28, 0, ((UP_LIST_EX*)UPtoMSG(ISP_MSG_AREA))->IMD3.bSizY, 4)

#if 0	// ddr write test
		const int iX = B30_HSPr;
		const int iY = B30_VSPr;
		//const UINT nAddrY = (FRC_ADR0r<<4) + ((((RP(PO_HW) * iY) + iX)*10)>>3);
		const UINT nAddrY = (IM_YADR0r<<4) + (RP(PO_HW) * iY) + iX;
		const UINT nAddrC = (IM_CADR0r<<4) + ((RP(PO_HW)>>1) * iY) + (iX>>1);

		hwflush_dcache_range(nAddrC, 64);
		hwflush_dcache_range(nAddrY, 64);

		const BYTE bDdrY = *((volatile BYTE *)(unsigned long)(nAddrY));
		const BYTE bDdrC = *((volatile BYTE *)(unsigned long)(nAddrC));

		DebugDisp2(1, Hex, "DDR YC ", 13, 0, bDdrY/*(bDdrY<<8) | bDdrC*/, 4)
		DebugDisp2(1, Hex, "ADDR Y ", 14, 0, nAddrY, 8)
		DebugDisp2(1, Dec, "B30_HSP", 15, 0, iX, 4)
		DebugDisp2(1, Dec, "B30_VSP", 16, 0, iY, 4)
#endif
	}
	else if(ABSDIFF(IF_Funcs_Time,IspIfTimeSta) < (CPU_FREQ/IF_FUNC_FPS)) return;


//	FontStr(4,0,"ADC1",4);
//	FontDec(4,5,AdcGet(1), 5, 1);

//	extern UINT gnNO_IRQ_UART_SPI_I2C;
//	FontStr(5,0,"NO IRQ",6);
//	FontDec(5,7,gnNO_IRQ_UART_SPI_I2C, 6, 1);

//	FontDecEx(4+0,0, NO_ALPHA, MN_YELLOW, AdcGet(0), 5, 1);
//	FontDecEx(4+1,0, NO_ALPHA, MN_YELLOW, AdcGet(1), 5, 1);
//	FontDecEx(4+2,0, NO_ALPHA, MN_YELLOW, AdcGet(2), 5, 1);
//	FontDecEx(4+3,0, NO_ALPHA, MN_YELLOW, AdcGet(3), 5, 1);
//	FontDecEx(4+4,0, NO_ALPHA, MN_YELLOW, AdcGet(4), 5, 1);
//	FontDecEx(4+5,0, NO_ALPHA, MN_YELLOW, AdcGet(5), 5, 1);
//	FontDecEx(4+6,0, NO_ALPHA, MN_YELLOW, AdcGet(6), 5, 1);
//	FontDecEx(4+7,0, NO_ALPHA, MN_YELLOW, AdcGet(7), 5, 1);

//	static UINT nPAR00 = 0;
//	if(nPAR00 != PAR00) {
//		nPAR00 = PAR00;
//		extern void UartClk(UINT nCH, UINT Speed_Hz, int ofs);
//		UartClk(7, UART7_SPEED, (nPAR00 > 100) ? 100 - (int)nPAR00 : (int)nPAR00);
//	}

	Comm(); 								// Communication Interface

	KeyScan();								// Key input detection

//	static int iUD = 0;
//	static int iLR = 0;
//	if(KEY_U) iUD++;
//	if(KEY_D) iUD--;
//	if(KEY_R) iLR++;
//	if(KEY_L) iLR--;
//	FontDec(6,5, NO_ALPHA, MN_WHITE, iUD, 5, 1);
//	FontDec(7,5, NO_ALPHA, MN_WHITE, iLR, 5, 1);


	Menu(); 								// Menu

	AppSavePar();
	AppLoadPar();

	if(!gbMnDebugBypass) {

//		Focus;								// Auto Focus or Focus Assist

//		TDN();								// Day & Night

		Gamma();							// Gamma control

//		BoxLast();							// Last Box control
	}

	Hdmi_Check();	// VLOCKO ???�기?�될 ?�요 ?�이 가???�번???�행?�면 ??

	IF_Funcs_Time = rdcycle();

	FontBenchTime(1/*gbMnDebugFnc==1*/, 23, 0, "ISP_I", IspIfTimeSta, 6);
}

void Vcap(void)
{
	// Downscale, Video capture setting
}


void Visp(void)
{
	extern UINT gnViIrqOn;

#if 1	// ECM Control Only
	WaitXms(100);
	Comm();

	BoxLast();							// Last Box control

	#if 1
	WaitXms(100);
	static BYTE bString_Cnt=0;
	if(bString_Cnt==10) { bString_Cnt=0; printf("i"); }
	else                  bString_Cnt++;

	#else
	extern irq_fn GetUartRxIrqCallback(UINT nCH);
	printf("%x %x %x\n", GetUartRxIrqCallback(7), gtUartQue.pbRxHead, gtUartQue.bRxQue);
	//UartRxIrqCallback(DEBUG_UART_NUM, UartDebugRxIrq, NULL);

	UartDebugRxIrq(NULL);
//	arrUARTRXIrq[nCH].irqfn = irqfn;
//	arrUARTRXIrq[nCH].arg = arg;
	#endif

	static UINT nHCNTI_Buf=0xff;

	if(nHCNTI_Buf!=HCNTI1_BT_SVr) {
		nHCNTI_Buf=HCNTI1_BT_SVr;
		printf("HCNTIr : 0x%08x\r\n", HCNTI1_BT_SVr);
		printf("VCNTIr : 0x%08x\r\n", VCNTI1_BT_SVr);
	}

#if 0
	static UINT nPAR0A_Buf=0;
	BYTE val = 0;
	extern void NXT_I2C_Write(BYTE,BYTE,BYTE);
	extern void NXT_I2C_Read(BYTE,BYTE,BYTE*);

	if(nPAR0A_Buf!=PAR0A) {

		NXT_I2C_Write(0x88, (BYTE)PAR0B, (BYTE)PAR0C);
		nPAR0A_Buf=PAR0A;

		NXT_I2C_Read(0x88, (BYTE)PAR0B, &val);
		printf("0x%02x : 0x%02x\r\n", PAR0B, val);
	}
#endif
#else

  #if 0		// Polling operation
	if(ISP_RIRQ_VIr) { CLI_VLOCKI_Tw(1);
  #else		// Interrupt operation
	if(gnViIrqOn) { gnViIrqOn = 0;
  #endif

		const ULONG IspMainTimeSta = BenchTimeStart();

		if(!gbMnDebugBypass) {

			Ae();								// Auto exposure

			Af();								// Auto exposure

			AceDefog(); 						// ACE & Defog

			Awb();								// Auto white balance

			Adnr();								// DNR 2D/3D

			Sharpness();						// Sharpness (aperture)

			CSup(); 							// Color surpression

			IMD();								// Motion detector

			DefectAuto();						// Defect correction

			BoxLast();							// Last Box control

			UartTxGrpRun();

			AeDev();
		}

		FontBenchTime(1/*gbMnDebugFnc==1*/, 22, 0, "ISP_M", IspMainTimeSta, 6);
	}
	else { IF_Funcs(); }
#endif
}

#endif

