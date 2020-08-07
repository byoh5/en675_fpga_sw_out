#include "dev.h"

#ifdef __SFLS_MT25QL256__
#include "micron_mt25ql256.h"

static SFLScontrol sfls_mt25ql256 = {
	.ior_cmd = MT25QL256_IOR_CMD,
	.ior_adr = MT25QL256_IOR_ADR,
	.ior_dat = MT25QL256_IOR_DAT,
	.iow_cmd = MT25QL256_IOW_CMD,
	.iow_adr = MT25QL256_IOW_ADR,
	.iow_dat = MT25QL256_IOW_DAT,
	.iowe_cmd = MT25QL256_IOWE_CMD,
	.iors_cmd = MT25QL256_IORS_CMD,
	.iors_dat = MT25QL256_IORS_DAT,

	.use_qe = 0,
	.use_qpi = MT25QL256_ENABLE_QPI,
	.use_4b = MT25QL256_ENABLE_4B,
	.is_qe = 0,
	.is_qpi = 0,
	.is_4b = 0,

	.cmd_read = MT25QL256_CMD_FAST_READ,
	.cmd_page_program = MT25QL256_CMD_PAGE_PROGRAM,
	.cmd_write_enable = MT25QL256_CMD_WRITE_ENABLE,
	.cmd_read_status = MT25QL256_CMD_READ_STATUS1,

	.cmd_write_disable = MT25QL256_CMD_WRITE_DISABLE,
	.cmd_write_status = MT25QL256_CMD_WRITE_STATUS1,
	.cmd_erase_secter = MT25QL256_CMD_SECTOR_ERASE,
	.cmd_erase_32kbyte = MT25QL256_CMD_32KB_ERASE,
	.cmd_erase_64kbyte = MT25QL256_CMD_64KB_ERASE,
	.cmd_erase_all = MT25QL256_CMD_CHIP_ERASE,
	.cmd_read_sfdp = MT25QL256_CMD_READ_SFDP,
	.cmd_enter_4b = MT25QL256_CMD_EN4B,
	.cmd_exit_4b = MT25QL256_CMD_EX4B,
	.cmd_enter_qpi = MT25QL256_CMD_ENTER_QPI,
	.cmd_exit_qpi = MT25QL256_CMD_EXIT_QPI,

	.mode_en = MT25QL256_READ_MODE_EN,
	.mode_val = MT25QL256_READ_MODE_VALUE,
	.gap = MT25QL256_READ_GAP,
	.rdltc = MT25QL256_RDLTC,
	.size = MT25QL256_SIZE,
	.qe_mask = 0,
	.protection_mask = MT25QL256_PROTECTION_MASK,

	.func_init_1 = SflsMt25ql256_Init1,
	.func_init_2 = SflsMt25ql256_Init2,
	.func_write_enable = 0,
	.func_secter_erase = 0,
	.func_32k_erase = 0,
	.func_64k_erase = 0,
	.func_chip_erase = 0,
	.func_read_status = 0,
	.func_read_status_view = SflsMt25ql256_ReadStatus1View,
	.func_write_status = 0,
	.func_read_sfdp = 0,
	.func_enter_4b = 0,
	.func_exit_4b = 0,
#if (MT25QL256_ENABLE_4B==1)
	.func_is_4b = SflsMt25ql256_Is4B,
#else
	.func_is_4b = 0,
#endif
	.func_enter_qpi = 0,
	.func_exit_qpi = 0,
	.func_is_qpi = 0,
	.func_enter_qe = 0,
	.func_exit_qe = 0,
	.func_is_qe = 0,
	.func_enter_protection = 0,
	.func_exit_protection = 0,
	.func_is_protection = 0,
};

void SflsMt25ql256_Init1(void)
{

}

void SflsMt25ql256_Init2(void)
{

}

SFLScontrol *SflsMt25ql256_GetControl(void)
{
	return &sfls_mt25ql256;
}

void SflsMt25ql256_ReadStatus1View(BYTE status)
{
#if (DBG_SFLS_STATUS==ENX_DBG_ON)
	if (status & 0x1)	printf("- Write In Progress (WIP)\n");
	if (status & 0x2)	printf("- Write Enable Latch (WEL)\n");
	if (status & 0x4)	printf("- Block Protect Bits (BP0) \n");
	if (status & 0x8)	printf("- Block Protect Bits (BP1) \n");
	if (status & 0x10)	printf("- Block Protect Bits (BP2) \n");
	if (status & 0x20)	printf("- Top/Bottom Protect Bits\n");
	if (status & 0x40)	printf("- Block Protect Bits (BP3) \n");
	if (status & 0x80)	printf("- Status Register Write Disable (SRWD)\n");
#endif
}

BYTE SflsMt25ql256_ReadStatus2(void)
{
	return SflsReadStatusCmd(MT25QL256_CMD_READ_STATUS2);
}

void SflsMt25ql256_ReadStatus2View(BYTE status)
{
#if (DBG_SFLS_STATUS==ENX_DBG_ON)
	printf("- Addressing (%s)\n", (status & 0x1) ? "4-byte addressing" : "3-byte addressing");
	printf("- Protection (%s)\n", (status & 0x2) ? "Failure or protection error" : "Clear");
	printf("- Program suspend (%s)\n", (status & 0x4) ? "Suspend" : "Clear");
	if (status & 0x8)	printf("- Reserved\n");
	printf("- Program (%s)\n", (status & 0x10) ? "Failure or protection error" : "Clear");
	printf("- Erase (%s)\n", (status & 0x20) ? "Failure or protection error" : "Clear");
	printf("- Erase suspend (%s)\n", (status & 0x40) ? "Suspend" : "Clear");
	printf("- Program or erase controller (%s)\n", (status & 0x80) ? "Ready" : "Busy");
#endif
}

#if (MT25QL256_ENABLE_4B==1)
inline UINT SflsMt25ql256_Is4B(void)
{
	BYTE status = SflsMt25ql256_ReadStatus2();
	if (status & 0x01) {
		sfls_mt25ql256.is_4b = ENX_YES;
	} else {
		sfls_mt25ql256.is_4b = ENX_NO;
	}
	return sfls_mt25ql256.is_4b;
}
#endif
#endif
