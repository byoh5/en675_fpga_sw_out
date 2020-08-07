#include "dev.h"

#if USE_I2S

ISRD static tIhnd arrI2STXIrq;
ISRD static tIhnd arrI2SRXIrq;

void I2sInit(void)
{
	I2S_PIN_INIT;

#if EN675_SINGLE
	I2S_PD = 1;
#endif
	arrI2STXIrq.irqfn = NULL;
	arrI2STXIrq.arg = NULL;

	arrI2SRXIrq.irqfn = NULL;
	arrI2SRXIrq.arg = NULL;
}

#if EN675_SINGLE_I2S_NEW
void I2sMstInit(void)
{
#if (I2S_MST_CLK==I2S_FREQ)
	I2S_BCK_DIV = (I2S_FREQ / PCM_BCLK / 2);
	I2S_MCLK_DIV = 0;
	I2S_MCLK_SEL = 1;
	I2S_BCK_SEL = 1;
	I2S_CKIN_EN = 1;
#else
	I2S_BCK_DIV = APB_FREQ / PCM_BCLK / 2;
	I2S_MCLK_DIV = 0;
	I2S_MCLK_SEL = 0;
	I2S_BCK_SEL = 0;
	I2S_CKIN_EN = 0;
#endif
	I2S_CKOUT_EN = 1;
	I2S_BYTE = PCM_BIT >> 4;
	I2S_MODE = 1;
	ENX_DEBUGF(DBG_UART_STATUS, "I2S(M) Init - MCLK(%s%uKHz%s)BCLK(%s%uHz%s)\n", TTY_COLOR_GREEN, I2sGetMstMclClk() / 1000, TTY_COLOR_RESET, TTY_COLOR_GREEN, I2sGetMstBckClk(), TTY_COLOR_RESET);
}
#else
void I2sMstInit(UINT freq, UINT byte)
{
	UINT sckcnt = 50000/freq;
	I2S_SCKCNT = sckcnt;
	I2S_BYTE = byte;
	I2S_MODE = 1;
	ENX_DEBUGF(DBG_UART_STATUS, "I2S(M) Init\n");
}
#endif

void I2sSlvInit(void)
{
	I2S_MODE = 0;
#if EN675_SINGLE_I2S_NEW
	I2S_CKIN_EN = 0;
	I2S_CKOUT_EN = 0;
#endif
	ENX_DEBUGF(DBG_UART_STATUS, "I2S(S) Init\n");
}

inline void I2sSetCtrlByte(UINT byte)
{
	I2S_BYTE = byte;
}

inline UINT I2sGetCtrlByte(void)
{
	return I2S_BYTE;
}

#if EN675_SINGLE_I2S_NEW
inline void I2sSetMstBckDiv(UINT bck_div)
{
	I2S_BCK_DIV = bck_div;
}

inline UINT I2sGetMstBckDiv(void)
{
	return I2S_BCK_DIV;
}

inline UINT I2sGetMstBckClk(void)
{
	if (I2sGetMstBckDiv() == 0) {
		return 0; // BckDiv == 0 => error
	} else {
		return (I2S_MST_CLK / (I2sGetMstBckDiv() * 2) / (8 << I2sGetCtrlByte()) / 2);
	}
}

inline void I2sSetMstMclkDiv(UINT mclk_div)
{
	I2S_MCLK_DIV = mclk_div;
}

inline UINT I2sGetMstMclkDiv(void)
{
	return I2S_MCLK_DIV;
}

inline UINT I2sGetMstMclClk(void)
{
	if (I2sGetMstMclkDiv() == 0) {
		return I2S_MST_CLK;
	} else {
		return (I2S_MST_CLK / (I2sGetMstMclkDiv() * 2));
	}
}

inline void I2sSetMstBckSel(UINT bck_sel)
{
	I2S_BCK_SEL = bck_sel;
}

inline UINT I2sGetMstBckSel(void)
{
	return I2S_BCK_SEL;
}

inline void I2sSetMstMclkSel(UINT mclk_sel)
{
	I2S_MCLK_SEL = mclk_sel;
}

inline UINT I2sGetMstMclkSel(void)
{
	return I2S_MCLK_SEL;
}

inline void I2sSetMstCkout(UINT ckout)
{
	I2S_CKOUT_EN = ckout;
}

inline UINT I2sGetMstCkout(void)
{
	return I2S_CKOUT_EN;
}

inline void I2sSetMstCkin(UINT ckin)
{
	I2S_CKIN_EN = ckin;
}

inline UINT I2sGetMstCkin(void)
{
	return I2S_CKIN_EN;
}
#else
void I2sSetCtrlSckcnt(UINT sckcnt)
{
	I2S_SCKCNT = sckcnt;
}

UINT I2sGetCtrlSckcnt(void)
{
	return I2S_SCKCNT;
}
#endif

void I2sSetCtrlMode(UINT mode)
{
	I2S_MODE = mode;
}

UINT I2sGetCtrlMode(void)
{
	return I2S_MODE;
}

void I2sSetTxEdn(UINT txedn)
{
	I2S_TXEDN = txedn;
}

UINT I2sGetTxEdn(void)
{
	return I2S_TXEDN;
}

void I2sSetRxEdn(UINT rxedn)
{
	I2S_RXEDN = rxedn;
}

UINT I2sGetRxEdn(void)
{
	return I2S_RXEDN;
}

void I2sTxCfg(UINT tx_mode, UINT tx_cd, UINT tx_dw, UINT rd_byte, UINT rd_dw, UINT rd_len, UINT tx_lr)
{
	I2S_TXMODE	=	tx_mode	;
	I2S_TXCODEC	=	tx_cd	;
	I2S_TXDW	=	tx_dw	;
	I2S_RDBYTE	=	rd_byte	;
	I2S_RDDW	=	rd_dw	;
	I2S_RDLEN	=	rd_len	;
	I2S_TXLR	=	tx_lr	;
}

void I2sSetTxMode(UINT tx_mode)
{
	I2S_TXMODE = tx_mode;
}

UINT I2sGetTxMode(void)
{
	return I2S_TXMODE;
}

void I2sSetTxCodec(UINT tx_cd)
{
	I2S_TXCODEC = tx_cd;
}

UINT I2sGetTxCodec(void)
{
	return I2S_TXCODEC;
}

void I2sSetTxDw(UINT tx_dw)
{
	I2S_TXDW = tx_dw;
}

UINT I2sGetTxDw(void)
{
	return I2S_TXDW;
}

void I2sSetRdByte(UINT rd_byte)
{
	I2S_RDBYTE = rd_byte;
}

UINT I2sGetRdByte(void)
{
	return I2S_RDBYTE;
}

void I2sSetRdDw(UINT rd_dw)
{
	I2S_RDDW = rd_dw;
}

UINT I2sGetRdDw(void)
{
	return I2S_RDDW;
}

void I2sSetRdLen(UINT rd_len)
{
	I2S_RDLEN = rd_len;
}

UINT I2sGetRdLen(void)
{
	return I2S_RDLEN;
}

void I2sSetTxLr(UINT tx_lr)
{
	I2S_TXLR = tx_lr;
}

UINT I2sGetTxLr(void)
{
	return I2S_TXLR;
}

void I2sTxBaseAddr(BYTE *addr)
{
	I2S_ADRR = (intptr_t)addr;
}

UINT I2sGetTxBaseAddr(void)
{
	return I2S_ADRR;
}

UINT I2sTxPos(void)
{
	return I2S_TX_ADDR;
}

void I2sSetTxEn(ENX_SWITCH sw)
{
	I2S_TXEN = sw;
}

ENX_SWITCH I2sGetTxEn(void)
{
	return I2S_TXEN;
}

void I2sRxCfg(UINT rx_mode, UINT rx_cd, UINT rx_dw, UINT wr_byte, UINT wr_dw, UINT wr_len)
{
	I2S_RXMODE	=	rx_mode	;
	I2S_RXCODEC	=	rx_cd	;
	I2S_RXDW	=	rx_dw	;
	I2S_WRBYTE	=	wr_byte	;
	I2S_WRDW	=	wr_dw	;
	I2S_WRLEN	=	wr_len	;
}

void I2sSetRxMode(UINT rx_mode)
{
	I2S_RXMODE = rx_mode;
}

UINT I2sGetRxMode(void)
{
	return I2S_RXMODE;
}

void I2sSetRxCodec(UINT rx_cd)
{
	I2S_RXCODEC = rx_cd;
}

UINT I2sGetRxCodec(void)
{
	return I2S_RXCODEC;
}

void I2sSetRxDw(UINT rx_dw)
{
	I2S_RXDW = rx_dw;
}

UINT I2sGetRxDw(void)
{
	return I2S_RXDW;
}
void I2sSetWrByte(UINT wr_byte)
{
	I2S_WRBYTE = wr_byte;
}

UINT I2sGetWrByte(void)
{
	return I2S_WRBYTE;
}

void I2sSetWrDw(UINT wr_dw)
{
	I2S_WRDW = wr_dw;
}

UINT I2sGetWrDw(void)
{
	return I2S_WRDW;
}

void I2sSetWrLen(UINT wr_len)
{
	I2S_WRLEN = wr_len;
}

UINT I2sGetWrLen(void)
{
	return I2S_WRLEN;
}

void I2sRxBaseAddr(BYTE *addr)
{
	I2S_ADRW = (intptr_t)addr;
}

UINT I2sGetRxBaseAddr(void)
{
	return I2S_ADRW;
}

UINT I2sRxPos(void)
{
	return I2S_RX_ADDR;
}

void I2sSetRxEn(ENX_SWITCH sw)
{
	I2S_RXEN = sw;
}

ENX_SWITCH I2sGetRxEn(void)
{
	return I2S_RXEN;
}

#if EN675_SINGLE
void I2sSetPlatTxEn(ENX_SWITCH sw)
{
	I2S_PLAT_TXEN = sw;
}

ENX_SWITCH I2sGetPlatTxEn(void)
{
	return I2S_PLAT_TXEN;
}

void I2sSetPlatMode(I2S_TX_MODE mode)
{
	I2S_PLAT_MODE = mode;
}

I2S_TX_MODE I2sGetPlatMode(void)
{
	return I2S_PLAT_MODE;
}

void I2sSetPlatLength(UINT length)
{
	I2S_PLAT_LENGTH = length;
}

UINT I2sGetPlatLength(void)
{
	return I2S_PLAT_LENGTH;
}
#endif

void I2sTxIrqCallback(irq_fn irqfn, void *arg)
{
	arrI2STXIrq.irqfn = irqfn;
	arrI2STXIrq.arg = arg;
}

void I2sRxIrqCallback(irq_fn irqfn, void *arg)
{
	arrI2SRXIrq.irqfn = irqfn;
	arrI2SRXIrq.arg = arg;
}

void I2sSetTxIrqEn(ENX_SWITCH sw)
{
	I2S_TX_IRQ_EN = sw;
}

void I2sSetRxIrqEn(ENX_SWITCH sw)
{
	I2S_RX_IRQ_EN = sw;
}

ENX_SWITCH I2sGetTxIrqEn(void)
{
	return I2S_TX_IRQ_EN;
}

ENX_SWITCH I2sGetRxIrqEn(void)
{
	return I2S_RX_IRQ_EN;
}

void I2sTxIrqClear(void)
{
	I2S_TX_IRQ_CLR = 1;
}

void I2sRxIrqClear(void)
{
	I2S_RX_IRQ_CLR = 1;
}

UINT I2sTxIsIrq(void)
{
//	printf("%s (0x%02X)\n", __func__, I2S_TX_IRQ);
	return I2S_TX_IRQ;
}

UINT I2sRxIsIrq(void)
{
//	printf("%s (0x%02X)\n", __func__, I2S_RX_IRQ);
	return I2S_RX_IRQ;
}

void IrqI2sTx(void)
{
	if (I2sTxIsIrq()) {
		if (arrI2STXIrq.irqfn) {
			arrI2STXIrq.irqfn(arrI2STXIrq.arg);
		} else {
			printf("I2sTx IRQ Get\n");
		}
		I2sTxIrqClear();
	}
}

void IrqI2sRx(void)
{
	if (I2sRxIsIrq()) {
		if (arrI2SRXIrq.irqfn) {
			arrI2SRXIrq.irqfn(arrI2SRXIrq.arg);
		} else {
			printf("I2sRx IRQ Get\n");
		}
		I2sRxIrqClear();
	}
}

#if 0
void I2sTxIrq(void)
{
//	I2S_TX_IRQ_CLR = 1;

	I2S_ADRR = 0xa0060000;
//	I2S_ADRR = PCM_HELLO;
	printf("I2S_ADRR = %08x\n",I2S_ADRR);
	I2S_TXEN	=	1;
//	I2S_TX_IRQ_EN = 1;
#if 0
	printf("I2S_MODE__ = %08x\n",I2S_MODE);
	printf("I2S_TXEN__ = %08x\n",I2S_TXEN);
	printf("I2S_TXMODE = %08x\n",I2S_TXMODE);
	printf("I2S_TXCD__ = %08x\n",I2S_TXCODEC);
	printf("I2S_TXDW__ = %08x\n",I2S_TXDW);
	printf("I2S_RDBYTE = %08x\n",I2S_RDBYTE);
	printf("I2S_BYTE__ = %08x\n",I2S_BYTE);
	printf("I2S_TXIRQEN = %08x\n",I2S_TX_IRQ_EN);
	printf("I2S_TXIRQCLR = %08x\n",I2S_TX_IRQ_CLR);
	printf("I2S_IRQ___ = %08x\n",I2S_IRQ);
#endif
	//UINT hellosize = sizeof(PCM_HELLO) / sizeof(PCM_HELLO[0]);
	while(1)
	{
//		printf("I2S_TX_ADDR: %08X\n", I2S_TX_ADDR);
		if(I2S_TX_ADDR<0xa0097000)
		//if(I2S_TX_ADDR<0xa00A0000)
		//if(I2S_TX_ADDR<(0xa0060000+0x4000))
			I2S_TXEN = 1;
		else {
			I2S_TXEN = 0;
			break;
		}
//		printf("Wait TXEN = 0\n");
//		printf("I2S_ADRR = %08x\n",I2S_ADRR);
// 		printf("%08x - 0x%08X - 0x%08X - %u\n",I2S_TX_ADDR, PCM_HELLO+hellosize, I2S_ADRR, hellosize);
//		if(I2S_TX_ADDR<(PCM_HELLO+hellosize))
			//I2S_TXEN	=	1;
//			;
//		else {
//			I2S_TXEN	=	0;
//			printf("I2S_TX_ADDR: %08X\n", I2S_TX_ADDR);
//			I2S_ADRR = PCM_HELLO;
//			I2S_TXEN	=	1;

			//break;
//		}
	}
//	I2S_TXEN = 0;
//	printf("I2S_ADRR = %08x\n",I2S_ADRR);
//	printf("BREAK =====> I2S_TX_ADDR = %08x, size(%u)\n",I2S_TX_ADDR, hellosize);
}
#endif
#else
void IrqI2sTx(void)
{
	_Rprintf("I2S TX IRQ Get! I2S is inactive.\n");
	ENX_ASSERT(0);
}

void IrqI2sRx(void)
{
	_Rprintf("I2S RX IRQ Get! I2S is inactive.\n");
	ENX_ASSERT(0);
}
#endif
