#ifndef __MICRON_MT25QL128__H__
#define __MICRON_MT25QL128__H__

////////////////////////////////////////////////////////////////////////////////
// RTL(200130_1405) - single(o) dual(o) quad(o)
////////////////////////////////////////////////////////////////////////////////

#define MT25QL128_SIZE					(16*1024*1024)

#define MT25QL128_IOMODE					SFLS_QUAD // SFLS_SINGLE // SFLS_DUAL // SFLS_QUAD

#if (MT25QL128_IOMODE==SFLS_SINGLE)
#define MT25QL128_RDLTC					1
#define MT25QL128_READ_GAP				8
#define MT25QL128_IOR_CMD				SFLS_SINGLE
#define MT25QL128_IOR_ADR				SFLS_SINGLE
#define MT25QL128_IOR_DAT				SFLS_SINGLE
#define MT25QL128_IOW_CMD				SFLS_SINGLE
#define MT25QL128_IOW_ADR				SFLS_SINGLE
#define MT25QL128_IOW_DAT				SFLS_SINGLE
#define MT25QL128_IOWE_CMD				SFLS_SINGLE
#define MT25QL128_IORS_CMD				SFLS_SINGLE
#define MT25QL128_IORS_DAT				SFLS_SINGLE
#define MT25QL128_CMD_WRITE				0x02
#define MT25QL128_CMD_READ				0x0B
#elif (MT25QL128_IOMODE==SFLS_DUAL)
#define MT25QL128_RDLTC					1
#define MT25QL128_READ_GAP				11
#define MT25QL128_IOR_CMD				SFLS_SINGLE
#define MT25QL128_IOR_ADR				SFLS_DUAL
#define MT25QL128_IOR_DAT				SFLS_DUAL
#define MT25QL128_IOW_CMD				SFLS_SINGLE
#define MT25QL128_IOW_ADR				SFLS_SINGLE
#define MT25QL128_IOW_DAT				SFLS_SINGLE
#define MT25QL128_IOWE_CMD				SFLS_SINGLE
#define MT25QL128_IORS_CMD				SFLS_SINGLE
#define MT25QL128_IORS_DAT				SFLS_SINGLE
#define MT25QL128_CMD_WRITE				0x02
#define MT25QL128_CMD_READ				0xBB
#elif (MT25QL128_IOMODE==SFLS_QUAD)
#define MT25QL128_RDLTC					1
#define MT25QL128_READ_GAP				11
#define MT25QL128_IOR_CMD				SFLS_SINGLE
#define MT25QL128_IOR_ADR				SFLS_QUAD
#define MT25QL128_IOR_DAT				SFLS_QUAD
#define MT25QL128_IOW_CMD				SFLS_SINGLE
#define MT25QL128_IOW_ADR				SFLS_SINGLE
#define MT25QL128_IOW_DAT				SFLS_QUAD
#define MT25QL128_IOWE_CMD				SFLS_SINGLE
#define MT25QL128_IORS_CMD				SFLS_SINGLE
#define MT25QL128_IORS_DAT				SFLS_SINGLE
#define MT25QL128_CMD_WRITE				0x32
#define MT25QL128_CMD_READ				0xEB
#endif

#define MT25QL128_CMD_FAST_READ			MT25QL128_CMD_READ
#define MT25QL128_CMD_PAGE_PROGRAM		MT25QL128_CMD_WRITE
#define MT25QL128_CMD_WRITE_ENABLE		0x06
#define MT25QL128_CMD_READ_STATUS		0x05
#define MT25QL128_CMD_WRITE_STATUS		0x01
#define MT25QL128_CMD_READ_SFDP			0x5A
#define MT25QL128_CMD_SECTOR_ERASE		0x20
#define MT25QL128_CMD_64KB_ERASE			0xD8
#define MT25QL128_CMD_CHIP_ERASE			0xC7

extern void SflsMt25ql128_Init1(void);
extern void SflsMt25ql128_Init2(void);
extern void SflsMt25ql128_WriteEnable(void);
extern void SflsMt25ql128_SecterErase(UINT addr);
extern void SflsMt25ql128_32kErase(UINT addr);
extern void SflsMt25ql128_64kErase(UINT addr);
extern void SflsMt25ql128_ChipErase(UINT addr);
extern void SflsMt25ql128_ReadSFDP(BYTE *sfdp_bin);
extern BYTE SflsMt25ql128_ReadStatus(void);
extern void SflsMt25ql128_WriteStatus(BYTE status);
extern void SflsMt25ql128_EnterProtection(void);
extern void SflsMt25ql128_ExitProtection(void);
extern UINT SflsMt25ql128_IsProtection(void);

#endif // __MICRON_MT25QL128__H__
