#include "dev.h"

#ifdef __ETHERNET__
#include "ethphy.h"

#ifdef __ETHPHY_KSZ8081MNX__
#include "ksz8081mnx.h"
#endif
#ifdef __ETHPHY_KSZ8081RNB__
#include "ksz8081rnb.h"
#endif
#ifdef __ETHPHY_KSZ9031RNX__
#include "ksz9031rnx.h"
#endif

EthphyInfo ethphy_info;

ENX_OKFAIL EthphyReset(void)
{
	WORD wBuf, nLoop = 0, nCk;

#if ETHPHY_MDIO_TEST
	UINT nCnt, nGetAddr = -1;
	WaitXms(100);
	_printf("Ethernet PHY MDIO Address Test.. Idle 10sec\n");
	for (UINT i = 0; i < 20; i++) {
		_printf(".");
		WaitXms(50);
	}
	printf("Test Start!\r\n");
	for (UINT i = 0; i < 32; i++) {
		nCnt = 0;
		ethphy_info.addr = i;

		MdioWrite(ethphy_info.addr, ETHPHY_BCR_ADR, ETHPHY_BCR_RESET);		// PHY reset
		do {
			WaitXms(10);
			MdioRead(ethphy_info.addr, ETHPHY_BCR_ADR, &wBuf);
		} while (wBuf & ETHPHY_BCR_RESET && ++nCnt <= 100);
		_printf("Phy address(%02d), wData(0x%04X), nCnt(%d) ", ethphy_info.addr, wBuf, nCnt);

		if (!(wBuf & ETHPHY_BCR_RESET)) {
			printf(" - ok\n");
			nGetAddr = i;
		} else {
			printf(" - fail\n");
		}

		WaitXms(1);
	}
	if (nGetAddr != -1) {
		ethphy_info.addr = nGetAddr;
		printf("Ethernet PHY MDIO Address(%d)\n", ethphy_info.addr);
	} else {
		printf("Ethernet PHY MDIO Error! Not Ready!\n");
		return ENX_FAIL;
	}
#endif

	MdioWrite(ethphy_info.addr, ETHPHY_BCR_ADR, ETHPHY_BCR_RESET);		// PHY reset
	for (nLoop = 0, nCk = 0; nLoop < 100; nLoop++) {
		MdioRead(ethphy_info.addr, ETHPHY_BCR_ADR, &wBuf);
		if (!(wBuf & ETHPHY_BCR_RESET)) {
			EthphyRegView(ETHPHY_BCR_ADR, wBuf);
			nCk = 1;
			break;
		}
		WaitXms(100);
	}

	if (nCk == 1) {
		return ENX_OK;
	} else {
		printf("Ethernet PHY RESET Fail?\n");
	}

	return ENX_FAIL;
}

ENX_SWITCH EthphyLinkState(void)
{
	WORD wBuf;
	for (UINT i = 0; i < 100; i++) {
		MdioRead(ethphy_info.addr, ETHPHY_BSR_ADR, &wBuf);
		EthphyRegView(ETHPHY_BSR_ADR, wBuf);
		if (wBuf & ETHPHY_BSR_LINK_STATUS) {
			return ENX_ON;
		}
		WaitXms(10);
	}
	EthphyReset();	//	fail? sw reset
	return ENX_OFF;
}

void EthphyInit(BYTE phy_addr, irq_fn irqfn)
{
	if (irqfn != NULL) {
		GpioSetDir(ETHPHY_GPIO_IRQ, GPIO_DIR_IN);
		GpioIrqCallback(ETHPHY_GPIO_IRQ, irqfn, NULL);
		GpioSetIrqEn(ETHPHY_GPIO_IRQ, ENX_ON);
	}

	GpioSetDir(ETHPHY_GPIO_RST, GPIO_DIR_OUT);
	GpioSetOut(ETHPHY_GPIO_RST, GPIO_OUT_LOW);
	WaitXms(10);
	GpioSetOut(ETHPHY_GPIO_RST, GPIO_OUT_HI);

	ethphy_info.addr = phy_addr & 0x1F;
	ethphy_info.type = ETHPHY_TYPE_UNKNOWN;
	ethphy_info.speed = ETHPHY_SPD_0;
	ethphy_info.duplex = ETHPHY_DUPLEX_UNKNOWN;
}

UINT EthphyGetPHYID(void)
{
#define ETHPHY_PHY_ID_MASK 0x00fffff0
	UINT outData;
	WORD getData2, getData1;
	MdioRead(ethphy_info.addr, ETHPHY_PI1R_ADR, &getData1); // Read the PHY Identifier I Register.
	MdioRead(ethphy_info.addr, ETHPHY_PI2R_ADR, &getData2); // Read the PHY Identifier II Register.
	outData = ((getData1 << 16) | getData2);
	return outData;
}

void EthphyPrintPHYName(void)
{
	UINT outData = EthphyGetPHYID();
	if ((outData & ETHPHY_PHY_ID_MASK) == 0x00221560) {
#if defined(__ETHPHY_KSZ8081MNX__) || defined(__ETHPHY_KSZ8081RNB__)
		WORD getData;
		MdioRead(ethphy_info.addr, 0x17, &getData);
		if (getData & 0x1) {
#if defined(__ETHPHY_KSZ8081MNX__)
			_Gprintf("  >>KSZ8081MNX Connected...\n");
#else
			_Rprintf("  >>KSZ8081MNX Connected... Error setting & compile\n");
#endif
		} else if (getData & 0x2) {
#if defined(__ETHPHY_KSZ8081RNB__)
			_Gprintf("  >>KSZ8081RNB Connected...\n");
#else
			_Rprintf("  >>KSZ8081RNB Connected... Error setting & compile\n");
#endif
		}
#else
		_Rprintf("  >>KSZ8081 Connected... Error setting & compile\n");
#endif
	} else if ((outData & ETHPHY_PHY_ID_MASK) == 0x00221620) {
#if defined(__ETHPHY_KSZ9031RNX__)
		_Gprintf("  >>KSZ9031 Connected...\n");
#else
		_Rprintf("  >>KSZ9031 Connected... Error setting & compile\n");
#endif
	} else {
		_Rprintf("  >>Unknown Ethernet PHY[0x%08X] Connected...\n", outData);
	}
}

#endif // __ETHERNET__
