#include "dev.h"

#if 0
UINT gnIF_Funcs_Run = 0;
void IF_Funcs_Timer_irq(void *ctx)
{
	gnIF_Funcs_Run = 1;
}
#endif

void Init_Vsys(void) // System
{
	SYS_REG0 = 0xf;
	while(SYS_REG0 == 0xf) {} // Wait for CPU0 to be ready.

	enx_externalirq_init_cpu3();

#ifdef __USE_ISP__
	AtoBIrqCallback(CPUtoISPcallback, NULL);
	AtoBSetIrqEn(ENX_ON);
#endif
}

void main_3(int cpu_id)
{
	Init_Vsys(); INIT_STR("Init_Vsys...");	// CPU3 System initial

#if 1
	printf("=====================================\r\n");
	printf("= CPU3 Start~~\r\n");
	printf("=====================================\r\n");
	printf("WDR_ADR_LEr  : 0x%08x\r\n", WDR_ADR_LEr );
	printf("FRC_ADR0r    : 0x%08x\r\n", FRC_ADR0r   );
	printf("FRC_ADR1r    : 0x%08x\r\n", FRC_ADR1r   );
	printf("FRC_ADR2r    : 0x%08x\r\n", FRC_ADR2r   );
	printf("FRC_ADR3r    : 0x%08x\r\n", FRC_ADR3r   );
	printf("FRC_ADR4r    : 0x%08x\r\n", FRC_ADR4r   );
	printf("ENC_ADR0r    : 0x%08x\r\n", ENC_ADR0r   );
	printf("ENC_ADR1r    : 0x%08x\r\n", ENC_ADR1r   );
	printf("ENC_ADR2r    : 0x%08x\r\n", ENC_ADR2r   );
	printf("ENC_ADR3r    : 0x%08x\r\n", ENC_ADR3r   );
	printf("IM_YADR0r    : 0x%08x\r\n", IM_YADR0r   );
	printf("IM_CADR0r    : 0x%08x\r\n", IM_CADR0r   );
	printf("IM_YADR1_P0r : 0x%08x\r\n", IM_YADR1_P0r);
	printf("IM_CADR1_P0r : 0x%08x\r\n", IM_CADR1_P0r);
	printf("IM_YADR1_P1r : 0x%08x\r\n", IM_YADR1_P1r);
	printf("IM_CADR1_P1r : 0x%08x\r\n", IM_CADR1_P1r);
	printf("IM_YADR1_P2r : 0x%08x\r\n", IM_YADR1_P2r);
	printf("IM_CADR1_P2r : 0x%08x\r\n", IM_CADR1_P2r);
	printf("IM_YADR2_P0r : 0x%08x\r\n", IM_YADR2_P0r);
	printf("IM_CADR2_P0r : 0x%08x\r\n", IM_CADR2_P0r);
	printf("IM_YADR2_P1r : 0x%08x\r\n", IM_YADR2_P1r);
	printf("IM_CADR2_P1r : 0x%08x\r\n", IM_CADR2_P1r);
	printf("IM_YADR2_P2r : 0x%08x\r\n", IM_YADR2_P2r);
	printf("IM_CADR2_P2r : 0x%08x\r\n", IM_CADR2_P2r);
	printf("IM_YADR3_P0r : 0x%08x\r\n", IM_YADR3_P0r);
	printf("IM_CADR3_P0r : 0x%08x\r\n", IM_CADR3_P0r);
	printf("IM_YADR3_P1r : 0x%08x\r\n", IM_YADR3_P1r);
	printf("IM_CADR3_P1r : 0x%08x\r\n", IM_CADR3_P1r);
	printf("IM_YADR3_P2r : 0x%08x\r\n", IM_YADR3_P2r);
	printf("IM_CADR3_P2r : 0x%08x\r\n", IM_CADR3_P2r);
	printf("IM_YADR4_P0r : 0x%08x\r\n", IM_YADR4_P0r);
	printf("IM_CADR4_P0r : 0x%08x\r\n", IM_CADR4_P0r);
	printf("IM_YADR4_P1r : 0x%08x\r\n", IM_YADR4_P1r);
	printf("IM_CADR4_P1r : 0x%08x\r\n", IM_CADR4_P1r);
	printf("IM_YADR4_P2r : 0x%08x\r\n", IM_YADR4_P2r);
	printf("IM_CADR4_P2r : 0x%08x\r\n", IM_CADR4_P2r);
	printf("WDR_ADR_SEr  : 0x%08x\r\n", WDR_ADR_SEr );
	printf("=====================================\r\n");
#endif

//	FORCE_ABT_SOFFw(1); // I2S-BCK pin muxer issus

#ifdef __USE_ISP__

	Init_Visp(); INIT_STR("Init_Visp...");	// ISP initial
	Init_Vcap(); INIT_STR("Init_Vcap...");	// Video path set
	Init_Vout(); INIT_STR("Init_Vout...");	// Digital/Analog Output set
	Init_Virq(); INIT_STR("Init_Virq...");	// Video interrupt enable

#if 0
	// Test pattern
	SLVw(0);
	SYNC_BYSw(1);
	INSELw(0x5);	// 0x5 고정, 0x6 움직임

	// font off
	FONT_ON0w(0);
#endif

	INIT_STR("--------- Main Loop Start ---------");

	while (1)
	{
		Visp();
		Vcap();
		//Venc();
		//Vdec();
	}

#else
	while (1) {
  #ifdef __ECM_STRING__
		Comm();
  #endif
		if (SYS_REG0 == 0xC) {
  #ifdef __USE_LED1__
			GpioSetOut(GPIO_LED1, GPIO_OUT_LOW);
  #endif
  #ifdef __USE_LED2__
			GpioSetOut(GPIO_LED2, GPIO_OUT_LOW);
  #endif
			//_printf("%d:%lu\r\n", cpu_id, *mtime);
			WaitXms(100);
			SYS_REG0 = 0xA;
		}
		WaitXms(1);
	}
#endif
}
