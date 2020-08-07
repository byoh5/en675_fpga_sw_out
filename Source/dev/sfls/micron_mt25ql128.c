#include "dev.h"

#ifdef __SFLS_MT25QL128__
#include "micron_mt25ql128.h"

static SFLScontrol sfls_mt25ql128 = {
	.ior_cmd = MT25QL128_IOR_CMD,
	.ior_adr = MT25QL128_IOR_ADR,
	.ior_dat = MT25QL128_IOR_DAT,
	.iow_cmd = MT25QL128_IOW_CMD,
	.iow_adr = MT25QL128_IOW_ADR,
	.iow_dat = MT25QL128_IOW_DAT,
	.iowe_cmd = MT25QL128_IOWE_CMD,
	.iors_cmd = MT25QL128_IORS_CMD,
	.iors_dat = MT25QL128_IORS_DAT,

	.is_qpi = 0,

	.cmd_read = MT25QL128_CMD_FAST_READ,
	.cmd_page_program = MT25QL128_CMD_PAGE_PROGRAM,
	.cmd_write_enable = MT25QL128_CMD_WRITE_ENABLE,
	.cmd_read_status = MT25QL128_CMD_READ_STATUS,

	.gap = MT25QL128_READ_GAP,
	.rdltc = MT25QL128_RDLTC,
	.size = MT25QL128_SIZE,

	.func_init_1 = SflsMt25ql128_Init1,
	.func_init_2 = SflsMt25ql128_Init2,
	.func_write_enable = SflsMt25ql128_WriteEnable,
	.func_secter_erase = SflsMt25ql128_SecterErase,
	.func_32k_erase = SflsMt25ql128_32kErase,
	.func_64k_erase = SflsMt25ql128_64kErase,
	.func_chip_erase = SflsMt25ql128_ChipErase,
	.func_read_status = SflsMt25ql128_ReadStatus,
	.func_write_status = SflsMt25ql128_WriteStatus,
	.func_read_sfdp = SflsMt25ql128_ReadSFDP,
	.func_enter_4b = 0,
	.func_exit_4b = 0,
	.func_is_4b = 0,
	.func_enter_qpi = 0,
	.func_exit_qpi = 0,
	.func_is_qpi = 0,
	.func_enter_qe = 0,
	.func_exit_qe = 0,
	.func_is_qe = 0,
	.func_enter_protection = SflsMt25ql128_EnterProtection,
	.func_exit_protection = SflsMt25ql128_ExitProtection,
	.func_is_protection = SflsMt25ql128_IsProtection,
};

void SflsMt25ql128_Init1(void)
{

}

void SflsMt25ql128_Init2(void)
{

}

void SflsMt25ql128_WriteEnable(void)
{
	SFLS_USR_CMD_MODE	= sfls_mt25ql128.iowe_cmd;
	SFLS_USR_ADR_EN 	= 0;
//	SFLS_USR_GAP_EN 	= 0;
	SFLS_USR_RD_EN 		= 0;
	SFLS_USR_WR_EN 		= 0;
	SFLS_USR_BUSY_EN 	= 0;
	SFLS_USR_CMD 		= sfls_mt25ql128.cmd_write_enable;
	SFLS_USR_REQ 		= 1;
}

static void SflsMt25ql128_Erase(SFLS_ERASE erase_type, UINT addr)
{
	SFLS_USR_RDLTC		= 1;
	SFLS_USR_CMD_MODE 	= sfls_mt25ql128.iow_cmd;
	SFLS_USR_ADR_MODE	= sfls_mt25ql128.iow_adr;
	SFLS_USR_RDREG_CMD_MODE = sfls_mt25ql128.iors_cmd;
	SFLS_USR_RDREG_DAT_MODE	= sfls_mt25ql128.iors_dat;

	if (erase_type == SFLS_E_ALL) {
		SFLS_USR_ADR_EN	= 0;
		SFLS_USR_ADR	= 0;
	} else {
		SFLS_USR_ADR_EN	= 1;
		SFLS_USR_ADR	= addr;
	}
//	SFLS_USR_GAP_EN 	= 0;
	SFLS_USR_RD_EN 		= 0;
	SFLS_USR_WR_EN 		= 0;
	SFLS_USR_GAP 		= 0;
	SFLS_USR_ADR_EXT 	= 0;
	SFLS_USR_BUSY_EN 	= 1;
	switch (erase_type) {
	case SFLS_E_ALL:
		SFLS_USR_CMD	= MT25QL128_CMD_CHIP_ERASE;
		break;
	case SFLS_E_4K:
		SFLS_USR_CMD	= MT25QL128_CMD_SECTOR_ERASE;
		break;
	case SFLS_E_64K:
		SFLS_USR_CMD	= MT25QL128_CMD_64KB_ERASE;
		break;
	case SFLS_E_32K:
		ENX_ASSERT(0);
		break;
	}
	SFLS_USR_REQ 		= 1;
}

void SflsMt25ql128_SecterErase(UINT addr)
{
	SflsMt25ql128_Erase(SFLS_E_4K, addr);
}

void SflsMt25ql128_32kErase(UINT addr)
{
	for (int i = 0; i < 8; i++) {
		SflsMt25ql128_Erase(SFLS_E_4K, addr + (i * 4096));
		while(SFLS_USR_REQ);
	}
}

void SflsMt25ql128_64kErase(UINT addr)
{
	SflsMt25ql128_Erase(SFLS_E_64K, addr);
}

void SflsMt25ql128_ChipErase(UINT addr)
{
	SflsMt25ql128_Erase(SFLS_E_ALL, addr);
}

SFLScontrol *SflsMt25ql128_GetControl(void)
{
	return &sfls_mt25ql128;
}

void SflsMt25ql128_ReadSFDP(BYTE *sfdp_bin)
{
	UINT *data = (UINT *)sfdp_bin;

	SFLS_USR_RDLTC		= 1;
	SFLS_USR_CMD_MODE	= 0;
	SFLS_USR_ADR_MODE	= 0;
	SFLS_USR_DAT_MODE	= 0;
	SFLS_USR_ADR_EN		= 1;
//	SFLS_USR_GAP_EN		= 1;
	SFLS_USR_GAP		= 7;
	SFLS_USR_RD_EN		= 1;
	SFLS_USR_WR_EN		= 0;
	SFLS_USR_LEN		= 3;
	SFLS_USR_ADR_EXT	= 0;
	SFLS_USR_BUSY_EN	= 0;
	SFLS_USR_CMD		= MT25QL128_CMD_READ_SFDP;
	SFLS_USR_WRDAT		= 0;

	for (UINT i = 0; i < (256 / 4); i++) {
		SFLS_USR_ADR	= i * 4;
		SFLS_USR_REQ	= 1;
		while (SFLS_USR_REQ);
		data[i] = ENX_HTONL(SFLS_USR_RDDAT);
	}
}

BYTE SflsMt25ql128_ReadStatus(void)
{
	SFLS_USR_RDLTC		= sfls_mt25ql128.rdltc;
	SFLS_USR_CMD_MODE	= sfls_mt25ql128.iors_cmd;
	SFLS_USR_DAT_MODE	= sfls_mt25ql128.iors_dat;
	SFLS_USR_ADR_EN		= 0;
//	SFLS_USR_GAP_EN		= 0;
	SFLS_USR_GAP 		= 0;
	SFLS_USR_RD_EN		= 1;
	SFLS_USR_WR_EN		= 0;
	SFLS_USR_LEN		= 0;
	SFLS_USR_BUSY_EN	= 0;
	SFLS_USR_CMD		= MT25QL128_CMD_READ_STATUS;
	SFLS_USR_REQ		= 1;
	while (SFLS_USR_REQ);
//	printf("CMD%02X: SFLS-RD:0x%08X(0x%02X), MODE(%d,%d)\n", SFLS_USR_CMD, SFLS_USR_RDDAT, SFLS_USR_RDDAT >> 24, SFLS_USR_CMD_MODE, SFLS_USR_DAT_MODE);
	BYTE status = SFLS_USR_RDDAT >> 24;
#if (DBG_SFLS_STATUS==ENX_DBG_ON)
	if (status & 0x1)	printf("- Write In Progress (WIP)\n");
	if (status & 0x2)	printf("- Write Enable Latch (WEL)\n");
	if (status & 0x4)	printf("- Block Protect Bits (BP0) \n");
	if (status & 0x8)	printf("- Block Protect Bits (BP1) \n");
	if (status & 0x10)	printf("- Block Protect Bits (BP2) \n");
	if (status & 0x20)	printf("- Block Protect Bits (BP3) \n");
	if (status & 0x40)	printf("- Top/Bottom Protect Bits\n");
	if (status & 0x80)	printf("- Status Register Write Disable (SRWD)\n");
#endif
	return status;
}

void SflsMt25ql128_WriteStatus(BYTE status)
{
	SflsMt25ql128_WriteEnable();
	while (SFLS_USR_REQ);

	SFLS_USR_RDLTC		= sfls_mt25ql128.rdltc;
	SFLS_USR_CMD_MODE	= sfls_mt25ql128.iors_cmd;
	SFLS_USR_DAT_MODE	= sfls_mt25ql128.iors_dat;
	SFLS_USR_ADR_EN		= 0;
//	SFLS_USR_GAP_EN		= 0;
	SFLS_USR_GAP 		= 0;
	SFLS_USR_RD_EN		= 0;
	SFLS_USR_WR_EN		= 1;
	SFLS_USR_LEN		= 0;
	SFLS_USR_BUSY_EN	= 1;
	SFLS_USR_CMD		= MT25QL128_CMD_WRITE_STATUS;
	SFLS_USR_WRDAT		= status << 24;
	SFLS_USR_REQ		= 1;
	while (SFLS_USR_REQ);
//	printf("CMD%02X: SFLS-WD:0x%08X(0x%02X), MODE(%d,%d)\n", SFLS_USR_CMD, SFLS_USR_WRDAT, dat, SFLS_USR_CMD_MODE, SFLS_USR_DAT_MODE);
}

void SflsMt25ql128_EnterProtection(void)
{
	BYTE status = SflsMt25ql128_ReadStatus();
	if (!((status & 0x7C) == 0x7C)) {
		status |= 0x7C;
		SflsMt25ql128_WriteStatus(status);
	} else {
		ENX_DEBUGF(DBG_SFLS_WARNING, "already enter protection\n");
	}
}

void SflsMt25ql128_ExitProtection(void)
{
	BYTE status = SflsMt25ql128_ReadStatus();
	if (status & 0x7C) {
		status &= ~0x7C;
		SflsMt25ql128_WriteStatus(status);
	} else {
		ENX_DEBUGF(DBG_SFLS_WARNING, "already exit protection\n");
	}
}

UINT SflsMt25ql128_IsProtection(void)
{
	BYTE status = SflsMt25ql128_ReadStatus();
	if (status & 0x7C) {
		return 1;
	} else {
		return 0;
	}
}
#endif
