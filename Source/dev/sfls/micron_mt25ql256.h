#ifndef __MICRON_MT25QL256__H__
#define __MICRON_MT25QL256__H__

////////////////////////////////////////////////////////////////////////////////
// RTL(200703_1234) - single(-) dual(-) quad(-) quad-qpi(-)
////////////////////////////////////////////////////////////////////////////////

#define MT25QL256_SIZE					(32*1024*1024)

#define MT25QL256_IOMODE				SFLS_SINGLE // SFLS_SINGLE // SFLS_DUAL // SFLS_QUAD
#define MT25QL256_ENABLE_QPI			0
#define MT25QL256_ENABLE_4B				1

#if (MT25QL256_IOMODE==SFLS_SINGLE)
#define MT25QL256_RDLTC					1
#define MT25QL256_READ_GAP				8
#define MT25QL256_READ_MODE_EN			0
#define MT25QL256_READ_MODE_VALUE		0x00
#define MT25QL256_IOR_CMD				SFLS_SINGLE
#define MT25QL256_IOR_ADR				SFLS_SINGLE
#define MT25QL256_IOR_DAT				SFLS_SINGLE
#define MT25QL256_IOW_CMD				SFLS_SINGLE
#define MT25QL256_IOW_ADR				SFLS_SINGLE
#define MT25QL256_IOW_DAT				SFLS_SINGLE
#define MT25QL256_IOWE_CMD				SFLS_SINGLE
#define MT25QL256_IORS_CMD				SFLS_SINGLE
#define MT25QL256_IORS_DAT				SFLS_SINGLE
#define MT25QL256_CMD_WRITE				0x02
#define MT25QL256_CMD_READ				0x0B
#elif (MT25QL256_IOMODE==SFLS_DUAL)
#define MT25QL256_RDLTC					1
#define MT25QL256_READ_MODE_EN			0
#define MT25QL256_READ_MODE_VALUE		0x00
#define MT25QL256_READ_GAP				8
#define MT25QL256_IOR_CMD				SFLS_SINGLE
#define MT25QL256_IOR_ADR				SFLS_DUAL
#define MT25QL256_IOR_DAT				SFLS_DUAL
#define MT25QL256_IOW_CMD				SFLS_SINGLE
#define MT25QL256_IOW_ADR				SFLS_DUAL
#define MT25QL256_IOW_DAT				SFLS_DUAL
#define MT25QL256_IOWE_CMD				SFLS_SINGLE
#define MT25QL256_IORS_CMD				SFLS_SINGLE
#define MT25QL256_IORS_DAT				SFLS_SINGLE
#define MT25QL256_CMD_WRITE				0xD2
#define MT25QL256_CMD_READ				0xBB
#elif (MT25QL256_IOMODE==SFLS_QUAD)
#if (MT25QL256_ENABLE_QPI==0)
#define MT25QL256_RDLTC					1
#define MT25QL256_READ_MODE_EN			0
#define MT25QL256_READ_MODE_VALUE		0x00
#define MT25QL256_READ_GAP				10
#define MT25QL256_IOR_CMD				SFLS_SINGLE
#define MT25QL256_IOR_ADR				SFLS_QUAD
#define MT25QL256_IOR_DAT				SFLS_QUAD
#define MT25QL256_IOW_CMD				SFLS_SINGLE
#define MT25QL256_IOW_ADR				SFLS_QUAD
#define MT25QL256_IOW_DAT				SFLS_QUAD
#define MT25QL256_IOWE_CMD				SFLS_SINGLE
#define MT25QL256_IORS_CMD				SFLS_SINGLE
#define MT25QL256_IORS_DAT				SFLS_SINGLE
#define MT25QL256_CMD_WRITE				0x38
#define MT25QL256_CMD_READ				0xEB
#else
#define MT25QL256_RDLTC					1
#define MT25QL256_READ_MODE_EN			0
#define MT25QL256_READ_MODE_VALUE		0x00
#define MT25QL256_READ_GAP				10
#define MT25QL256_IOR_CMD				SFLS_QUAD
#define MT25QL256_IOR_ADR				SFLS_QUAD
#define MT25QL256_IOR_DAT				SFLS_QUAD
#define MT25QL256_IOW_CMD				SFLS_QUAD
#define MT25QL256_IOW_ADR				SFLS_QUAD
#define MT25QL256_IOW_DAT				SFLS_QUAD
#define MT25QL256_IOWE_CMD				SFLS_QUAD
#define MT25QL256_IORS_CMD				SFLS_QUAD
#define MT25QL256_IORS_DAT				SFLS_QUAD
#define MT25QL256_CMD_WRITE				0x32
#define MT25QL256_CMD_READ				0xEB
#endif
#endif

#define MT25QL256_CMD_FAST_READ			MT25QL256_CMD_READ
#define MT25QL256_CMD_PAGE_PROGRAM		MT25QL256_CMD_WRITE
#define MT25QL256_CMD_WRITE_ENABLE		0x06
#define MT25QL256_CMD_WRITE_DISABLE		0x04
#define MT25QL256_CMD_READ_STATUS1		0x05
#define MT25QL256_CMD_READ_STATUS2		0x70
#define MT25QL256_CMD_WRITE_STATUS1		0x01
#define MT25QL256_CMD_READ_SFDP			0x5A
#define MT25QL256_CMD_ENTER_QPI			0x35
#define MT25QL256_CMD_EXIT_QPI			0xF5
#define MT25QL256_CMD_EN4B				0xB7
#define MT25QL256_CMD_EX4B				0xE9
#define MT25QL256_CMD_SECTOR_ERASE		0x20
#define MT25QL256_CMD_32KB_ERASE		0x52
#define MT25QL256_CMD_64KB_ERASE		0xD8
#define MT25QL256_CMD_CHIP_ERASE		0x60

#define MT25QL256_PROTECTION_MASK		0x7C

extern void SflsMt25ql256_Init1(void);
extern void SflsMt25ql256_Init2(void);
extern void SflsMt25ql256_ReadStatus1View(BYTE status);
extern BYTE SflsMt25ql256_ReadStatus2(void);
extern void SflsMt25ql256_ReadStatus2View(BYTE status);
extern UINT SflsMt25ql256_Is4B(void);
extern void SflsMt25ql256_EnterProtection(void);
extern void SflsMt25ql256_ExitProtection(void);
extern UINT SflsMt25ql256_IsProtection(void);

#if (MT25QL256_ENABLE_QPI==1)
#if (MT25QL256_IOMODE!=SFLS_QUAD)
#error "QPI mode failed to activate. Set the serial flash memory to QUAD mode."
#endif
#endif

#endif // __MICRON_MT25QL256__H__