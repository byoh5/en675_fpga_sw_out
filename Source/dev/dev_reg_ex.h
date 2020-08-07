#ifndef __DEV_REG_EX_H__
#define __DEV_REG_EX_H__

//******************************************************************************
// x. Register
//------------------------------------------------------------------------------
#if EN675_SINGLE
#include "dev_reg_s.h"
#else
#include "dev_reg_m.h"
#define SYS_IP_31 1
#define SYS_IP_30 1
#define SYS_IP_29 1
#define SYS_IP_28 1
#define SYS_IP_27 1
#define SYS_IP_26 1
#define SYS_IP_25 1
#define SYS_IP_24 1
#define SYS_IP_23 1
#define SYS_IP_22 1
#define SYS_IP_21 1
#define SYS_IP_20 1
#define SYS_IP_19 1
#define SYS_IP_18 1
#define SYS_IP_17 1
#define SYS_IP_16 1
#define SYS_IP_15 1
#define SYS_IP_14 1
#define SYS_IP_13 1
#define SYS_IP_12 1
#define SYS_IP_11 1
#define SYS_IP_10 1
#define SYS_IP_9  1
#define SYS_IP_8  1
#define SYS_IP_7  1
#define SYS_IP_6  1
#define SYS_IP_5  1
#define SYS_IP_4  1
#define SYS_IP_3  1
#define SYS_IP_2  1
#define SYS_IP_1  1
#define SYS_IP_0  1
#endif

_regs_ BF_8(UINT GPIO_IN : 1 ,UINT GPIO_OUT : 1 ,UINT GPIO_OEN : 1 ,UINT GPIO_IRQ_DIR : 2 ,UINT GPIO_IRQ_EN : 1 ,UINT GPIO_IRQ_CLR : 1 ,UINT GPIO_IRQ : 1 , UINT _rev0 : 24 ) _rege_ _GPIO_PIN;
_regs_ BF_2(UINT _rev0 : 30, UINT GPIO_MUX : 2 ) _rege_ _GPIO_MUX;

_regs_ BF_3(UINT DSTMAC_EN : 1 ,UINT _rev0 : 15, UINT DSTMAC_ADR_47_32 : 16 ) _rege_ _ETH_DSTMAC1;
_regs_ BF_1(UINT DSTMAC_ADR_31_0 : 32 ) _rege_ _ETH_DSTMAC2;

_regs_ BF_9(UINT CMD_RXEDGE : 1 ,UINT CMD_TXEDGE : 1 ,UINT DAT_RXEDGE : 1 ,UINT DAT_TXEDGE : 1 ,UINT _rev0 : 24, UINT BITMODE : 1 ,UINT IOMODE : 1 ,UINT MODE : 1 ,UINT EN : 1 ) _rege_ _SDIO_REG0;
_regs_ BF_4(UINT _rev0 : 17, UINT CLK_EN : 1 ,UINT CLK_SELECT : 2 ,UINT CLK_DIV : 12 ) _rege_ _SDIO_REG1;
_regs_ BF_1(UINT CMD_ARG : 32 ) _rege_ _SDIO_REG2;
_regs_ BF_10(UINT _rev0 : 2, UINT CMD_IDX : 6 ,UINT _rev1 : 14, UINT CMD_RESP_TOUT : 1 ,UINT CMD_RESP_CRCERR : 1 ,UINT _rev2 : 4, UINT CMD_RESP_BUSY_EN : 1 ,UINT CMD_RESP_TYPE : 1 ,UINT CMD_RESP_EN : 1 ,UINT CMD_EN : 1 ) _rege_ _SDIO_REG3;
_regs_ BF_4(UINT _rev0 : 18, UINT CMD_RESP_IDX : 6 ,UINT _rev1 : 1, UINT CMD_RESP_CRC : 7 ) _rege_ _SDIO_REG4;
_regs_ BF_1(UINT CMD_RESP_DAT127_96 : 32 ) _rege_ _SDIO_REG5;
_regs_ BF_1(UINT CMD_RESP_DAT95_64 : 32 ) _rege_ _SDIO_REG6;
_regs_ BF_1(UINT CMD_RESP_DAT63_32 : 32 ) _rege_ _SDIO_REG7;
_regs_ BF_1(UINT CMD_RESP_DAT31_0 : 32 ) _rege_ _SDIO_REG8;
_regs_ BF_1(UINT CMD_RESP_TLMT : 32 ) _rege_ _SDIO_REG9;
_regs_ BF_1(UINT DAT_ADR : 32 ) _rege_ _SDIO_REG10;
_regs_ BF_4(UINT TRG : 1 ,UINT _rev0 : 3, UINT DAT_BLKBYTE : 12 ,UINT DAT_BLKNUM : 16 ) _rege_ _SDIO_REG11;
_regs_ BF_1(UINT DAT_BLKADR : 32 ) _rege_ _SDIO_REG12;
_regs_ BF_17(UINT DAT_CRCERR : 1 ,UINT DAT_BUSY : 1 ,UINT _rev0 : 14, UINT IO_IRQ : 1 ,UINT IO_IRQ_CLR : 1 ,UINT IO_IRQ_EN : 1 ,UINT CMD_IRQ : 1 ,UINT CMD_IRQ_CLR : 1 ,UINT CMD_IRQ_EN : 1 ,UINT DAT_IRQ : 1 ,UINT DAT_IRQ_CLR : 1 ,UINT DAT_IRQ_EN : 1 ,UINT CMD53_FN : 3 ,UINT CMD53_BM : 1 ,UINT CMD53_OP : 1 ,UINT DAT_WE : 1 ,UINT DAT_EN : 1 ) _rege_ _SDIO_REG13;
_regs_ BF_3(UINT DAT_TOUT : 8 ,UINT _rev0 : 8, UINT DAT_BLKCNT : 16 ) _rege_ _SDIO_REG14;
_regs_ BF_4(UINT _rev0 : 18, UINT DAT_STOP_CMD : 6 ,UINT _rev1 : 2, UINT DAT_IORW_CMD : 6 ) _rege_ _SDIO_REG15;
_regs_ BF_8(UINT _rev0 : 2, UINT DAT_WRCMD_S : 6 ,UINT _rev1 : 2, UINT DAT_WRCMD_M : 6 ,UINT _rev2 : 2, UINT DAT_RDCMD_S : 6 ,UINT _rev3 : 2, UINT DAT_RDCMD_M : 6 ) _rege_ _SDIO_REG16;

#if EN675_SINGLE
_regs_ BF_15(UINT CLK_DIV : 16 ,UINT _rev0 : 2, UINT TX_TYPE : 1 ,UINT STOP_BIT : 1 ,UINT PARITY_MODE : 2 ,UINT TX_IRQ : 1 ,UINT TX_IRQ_EN : 1 ,UINT TX_IRQ_CLR : 1 ,UINT TX_EMPTY : 1 ,UINT TX_FULL : 1 ,UINT RX_IRQ : 1 ,UINT RX_IRQ_EN : 1 ,UINT RX_IRQ_CLR : 1 ,UINT RX_EMPTY : 1 ,UINT RX_FULL : 1 ) _rege_ _UART_REG0;
_regs_ BF_3(UINT _rev0 : 9, UINT SYNC : 3 ,UINT RX_LMT : 20 ) _rege_ _UART_REG3;
#else
_regs_ BF_15(UINT CLK_DIV : 12 ,UINT _rev0 : 6, UINT TX_TYPE : 1 ,UINT STOP_BIT : 1 ,UINT PARITY_MODE : 2 ,UINT TX_IRQ : 1 ,UINT TX_IRQ_EN : 1 ,UINT TX_IRQ_CLR : 1 ,UINT TX_EMPTY : 1 ,UINT TX_FULL : 1 ,UINT RX_IRQ : 1 ,UINT RX_IRQ_EN : 1 ,UINT RX_IRQ_CLR : 1 ,UINT RX_EMPTY : 1 ,UINT RX_FULL : 1 ) _rege_ _UART_REG0;
_regs_ BF_2(UINT _rev0 : 12, UINT RX_LMT : 20 ) _rege_ _UART_REG3;
#endif
_regs_ BF_2(UINT _rev0 : 24, UINT RX_DAT : 8 ) _rege_ _UART_REG1;
_regs_ BF_2(UINT _rev0 : 24, UINT TX_DAT : 8 ) _rege_ _UART_REG2;

#if EN675_SINGLE
#if EN675_SINGLE_I2C_NEW
_regs_ BF_8(UINT CLK_DIV : 16 ,UINT _rev0 : 8, UINT SYNC : 3 ,UINT MODE : 1 ,UINT BIT_MODE : 1 ,UINT IRQ : 1 ,UINT IRQ_EN : 1 ,UINT IRQ_CLR : 1 ) _rege_ _I2C_REG0;
_regs_ BF_3(UINT RX_DAT : 8 ,UINT TX_DAT : 8 , UINT _rev0 : 16 ) _rege_ _I2C_REG1;
_regs_ BF_8(UINT _rev0 : 25, UINT ACT : 1 ,UINT MST_COL : 1 ,UINT MST_ACK : 1 ,UINT MST_REPEAT : 1 ,UINT MST_LAST : 1 ,UINT MST_RW : 1 ,UINT MST_GO : 1 ) _rege_ _I2C_REG2;
_regs_ BF_10(UINT _rev0 : 17, UINT SLV_STOP : 1 ,UINT SLV_START : 1 ,UINT I2C_SDA : 1 ,UINT I2C_SCL : 1 ,UINT SLV_ACK_IN : 1 ,UINT SLV_GO : 1 ,UINT SLV_RW : 1 ,UINT SLV_ACK_OUT : 1 ,UINT SLV_ADR : 7 ) _rege_ _I2C_REG3;
#else
_regs_ BF_11(UINT RX_DAT : 8 ,UINT TX_DAT : 8 ,UINT _rev0 : 8, UINT LAST_FLAG : 1 ,UINT START_FLAG : 1 ,UINT ACT : 1 ,UINT MODE : 1 ,UINT BIT_MODE : 1 ,UINT IRQ : 1 ,UINT IRQ_EN : 1 ,UINT IRQ_CLR : 1 ) _rege_ _I2C_REG0;
_regs_ BF_2(UINT CLK_DIV : 16 , UINT _rev0 : 16 ) _rege_ _I2C_REG1;
_regs_ BF_7(UINT _rev0 : 26, UINT MST_COL : 1 ,UINT MST_ACK : 1 ,UINT MST_REPEAT : 1 ,UINT MST_LAST : 1 ,UINT MST_RW : 1 ,UINT MST_GO : 1 ) _rege_ _I2C_REG2;
_regs_ BF_8(UINT _rev0 : 19, UINT I2C_SDA : 1 ,UINT I2C_SCL : 1 ,UINT SLV_ACK_IN : 1 ,UINT SLV_GO : 1 ,UINT SLV_RW : 1 ,UINT SLV_ACK_OUT : 1 ,UINT SLV_ADR : 7 ) _rege_ _I2C_REG3;
#endif
#else
_regs_ BF_9(UINT RX_DAT : 8 ,UINT TX_DAT : 8 ,UINT _rev0 : 10, UINT ACT : 1 ,UINT MODE : 1 ,UINT BIT_MODE : 1 ,UINT IRQ : 1 ,UINT IRQ_EN : 1 ,UINT IRQ_CLR : 1 ) _rege_ _I2C_REG0;
_regs_ BF_2(UINT CLK_DIV : 16 , UINT _rev0 : 16 ) _rege_ _I2C_REG1;
_regs_ BF_7(UINT _rev0 : 26, UINT MST_COL : 1 ,UINT MST_ACK : 1 ,UINT MST_REPEAT : 1 ,UINT MST_LAST : 1 ,UINT MST_RW : 1 ,UINT MST_GO : 1 ) _rege_ _I2C_REG2;
_regs_ BF_8(UINT _rev0 : 19, UINT I2C_SDA : 1 ,UINT I2C_SCL : 1 ,UINT SLV_ACK_IN : 1 ,UINT SLV_GO : 1 ,UINT SLV_RW : 1 ,UINT SLV_ACK_OUT : 1 ,UINT SLV_ADR : 7 ) _rege_ _I2C_REG3;
#endif

#if EN675_SINGLE
_regs_ BF_12(UINT FULL : 1 ,UINT DONE_VAL : 1 ,UINT _rev0 : 4, UINT DONE_PTR : 4 ,UINT _rev1 : 4, UINT JOB_PTR : 4 ,UINT IRQ : 1 ,UINT IRQ_EN : 1 ,UINT IRQ_CLR : 1 ,UINT VALUE : 8 ,UINT MODE : 2 ,UINT GO : 1 ) _rege_ _DMA_REG0;
#else
_regs_ BF_12(UINT _rev0 : 1, UINT DONE_VAL : 1 ,UINT _rev1 : 2, UINT DONE_PTR : 6 ,UINT _rev2 : 2, UINT JOB_PTR : 6 ,UINT IRQ : 1 ,UINT IRQ_EN : 1 ,UINT IRQ_CLR : 1 ,UINT VALUE : 8 ,UINT MODE : 2 ,UINT GO : 1 ) _rege_ _DMA_REG0;
#endif
_regs_ BF_1(UINT SRC : 32 ) _rege_ _DMA_REG1;
_regs_ BF_1(UINT DST : 32 ) _rege_ _DMA_REG2;
_regs_ BF_1(UINT LEN : 32 ) _rege_ _DMA_REG3;

_regs_ BF_10(UINT EN : 1 ,UINT PWM_EN : 1 ,UINT CK_EN : 1 ,UINT IRQ_EN : 1 ,UINT CNT_CLR : 1 ,UINT IRQ_CLR : 1 ,UINT IRQ : 1 ,UINT _rev0 : 1, UINT DIV : 8 ,UINT LMT : 16 ) _rege_ _TIMER_REG0;
_regs_ BF_2(UINT TRIG : 16 ,UINT CNT : 16 ) _rege_ _TIMER_REG1;

_regs_ BF_1(UINT RX_DAT : 32 ) _rege_ _SPI_REG0;
_regs_ BF_1(UINT TX_DAT : 32 ) _rege_ _SPI_REG1;
_regs_ BF_14(UINT EN : 1 ,UINT _rev0 : 7, UINT CLK_DIV : 8 ,UINT _rev1 : 2, UINT BIT_MODE : 1 ,UINT CS_MODE : 2 ,UINT IRQ_EN : 1 ,UINT IRQ_CLR : 1 ,UINT IRQ : 1 ,UINT ONE_BITMODE : 1 ,UINT CLK_MODE : 2 ,UINT WS : 2 ,UINT RW : 2 ,UINT GO : 1 ) _rege_ _SPI_REG2;

_regs_ BF_5(UINT EN : 1 ,UINT MAG : 1 ,UINT MUL : 3 ,UINT _rev0 : 11, UINT DAT : 16 ) _rege_ _ADC_REG;

#define SFLS_00_T _am(_SFLS_0,REG_BASE_SFLS, (0<<3))
#define SFLS_01_T _am(_SFLS_1,REG_BASE_SFLS, (1<<3))
#define SFLS_02_T _am(_SFLS_2,REG_BASE_SFLS, (2<<3))
#define SFLS_03_T _am(_SFLS_3,REG_BASE_SFLS, (3<<3))
#define SFLS_04_T _am(_SFLS_4,REG_BASE_SFLS, (4<<3))
#define SFLS_05_T _am(_SFLS_5,REG_BASE_SFLS, (5<<3))
#define SFLS_06_T _am(_SFLS_6,REG_BASE_SFLS, (6<<3))
#define SFLS_07_T _am(_SFLS_7,REG_BASE_SFLS, (7<<3))
#define SFLS_08_T _am(_SFLS_8,REG_BASE_SFLS, (8<<3))

#define SDIO0_00_T _am(_SDIO0_0,REG_BASE_SDIO0, (0<<3))
#define SDIO0_01_T _am(_SDIO0_1,REG_BASE_SDIO0, (1<<3))
#define SDIO0_02_T _am(_SDIO0_2,REG_BASE_SDIO0, (2<<3))
#define SDIO0_03_T _am(_SDIO0_3,REG_BASE_SDIO0, (3<<3))
#define SDIO0_04_T _am(_SDIO0_4,REG_BASE_SDIO0, (4<<3))
#define SDIO0_05_T _am(_SDIO0_5,REG_BASE_SDIO0, (5<<3))
#define SDIO0_06_T _am(_SDIO0_6,REG_BASE_SDIO0, (6<<3))
#define SDIO0_07_T _am(_SDIO0_7,REG_BASE_SDIO0, (7<<3))
#define SDIO0_08_T _am(_SDIO0_8,REG_BASE_SDIO0, (8<<3))
#define SDIO0_09_T _am(_SDIO0_9,REG_BASE_SDIO0, (9<<3))
#define SDIO0_10_T _am(_SDIO0_10,REG_BASE_SDIO0, (10<<3))
#define SDIO0_11_T _am(_SDIO0_11,REG_BASE_SDIO0, (11<<3))
#define SDIO0_12_T _am(_SDIO0_12,REG_BASE_SDIO0, (12<<3))
#define SDIO0_13_T _am(_SDIO0_13,REG_BASE_SDIO0, (13<<3))
#define SDIO0_14_T _am(_SDIO0_14,REG_BASE_SDIO0, (14<<3))
#define SDIO0_15_T _am(_SDIO0_15,REG_BASE_SDIO0, (15<<3))
#define SDIO0_16_T _am(_SDIO0_16,REG_BASE_SDIO0, (16<<3))

#define SDIO1_00_T _am(_SDIO1_0,REG_BASE_SDIO1, (0<<3))
#define SDIO1_01_T _am(_SDIO1_1,REG_BASE_SDIO1, (1<<3))
#define SDIO1_02_T _am(_SDIO1_2,REG_BASE_SDIO1, (2<<3))
#define SDIO1_03_T _am(_SDIO1_3,REG_BASE_SDIO1, (3<<3))
#define SDIO1_04_T _am(_SDIO1_4,REG_BASE_SDIO1, (4<<3))
#define SDIO1_05_T _am(_SDIO1_5,REG_BASE_SDIO1, (5<<3))
#define SDIO1_06_T _am(_SDIO1_6,REG_BASE_SDIO1, (6<<3))
#define SDIO1_07_T _am(_SDIO1_7,REG_BASE_SDIO1, (7<<3))
#define SDIO1_08_T _am(_SDIO1_8,REG_BASE_SDIO1, (8<<3))
#define SDIO1_09_T _am(_SDIO1_9,REG_BASE_SDIO1, (9<<3))
#define SDIO1_10_T _am(_SDIO1_10,REG_BASE_SDIO1, (10<<3))
#define SDIO1_11_T _am(_SDIO1_11,REG_BASE_SDIO1, (11<<3))
#define SDIO1_12_T _am(_SDIO1_12,REG_BASE_SDIO1, (12<<3))
#define SDIO1_13_T _am(_SDIO1_13,REG_BASE_SDIO1, (13<<3))
#define SDIO1_14_T _am(_SDIO1_14,REG_BASE_SDIO1, (14<<3))
#define SDIO1_15_T _am(_SDIO1_15,REG_BASE_SDIO1, (15<<3))
#define SDIO1_16_T _am(_SDIO1_16,REG_BASE_SDIO1, (16<<3))

#define ETH_00_T _am(_ETH_0,REG_BASE_ETH, (0<<3))
#define ETH_01_T _am(_ETH_1,REG_BASE_ETH, (1<<3))
#define ETH_02_T _am(_ETH_2,REG_BASE_ETH, (2<<3))
#define ETH_03_T _am(_ETH_3,REG_BASE_ETH, (3<<3))
#define ETH_04_T _am(_ETH_4,REG_BASE_ETH, (4<<3))
#define ETH_05_T _am(_ETH_5,REG_BASE_ETH, (5<<3))
#define ETH_06_T _am(_ETH_6,REG_BASE_ETH, (6<<3))
#define ETH_07_T _am(_ETH_7,REG_BASE_ETH, (7<<3))
#define ETH_08_T _am(_ETH_8,REG_BASE_ETH, (8<<3))
#define ETH_09_T _am(_ETH_9,REG_BASE_ETH, (9<<3))
#define ETH_10_T _am(_ETH_10,REG_BASE_ETH, (10<<3))
#define ETH_11_T _am(_ETH_11,REG_BASE_ETH, (11<<3))
#define ETH_12_T _am(_ETH_12,REG_BASE_ETH, (12<<3))
#define ETH_13_T _am(_ETH_13,REG_BASE_ETH, (13<<3))
#define ETH_14_T _am(_ETH_14,REG_BASE_ETH, (14<<3))
#define ETH_15_T _am(_ETH_15,REG_BASE_ETH, (15<<3))
#define ETH_16_T _am(_ETH_16,REG_BASE_ETH, (16<<3))
#define ETH_17_T _am(_ETH_17,REG_BASE_ETH, (17<<3))
#define ETH_18_T _am(_ETH_18,REG_BASE_ETH, (18<<3))
#define ETH_19_T _am(_ETH_19,REG_BASE_ETH, (19<<3))
#define ETH_32_T _am(_ETH_32,REG_BASE_ETH, (32<<3))
#define ETH_33_T _am(_ETH_33,REG_BASE_ETH, (33<<3))
#define ETH_34_T _am(_ETH_34,REG_BASE_ETH, (34<<3))
#define ETH_35_T _am(_ETH_35,REG_BASE_ETH, (35<<3))
#define ETH_36_T _am(_ETH_36,REG_BASE_ETH, (36<<3))
#define ETH_37_T _am(_ETH_37,REG_BASE_ETH, (37<<3))
#define ETH_38_T _am(_ETH_38,REG_BASE_ETH, (38<<3))
#define ETH_39_T _am(_ETH_39,REG_BASE_ETH, (39<<3))
#define ETH_40_T _am(_ETH_40,REG_BASE_ETH, (40<<3))
#define ETH_41_T _am(_ETH_41,REG_BASE_ETH, (41<<3))
#define ETH_42_T _am(_ETH_42,REG_BASE_ETH, (42<<3))
#define ETH_43_T _am(_ETH_43,REG_BASE_ETH, (43<<3))
#define ETH_44_T _am(_ETH_44,REG_BASE_ETH, (44<<3))
#define ETH_45_T _am(_ETH_45,REG_BASE_ETH, (45<<3))
#define ETH_46_T _am(_ETH_46,REG_BASE_ETH, (46<<3))
#define ETH_47_T _am(_ETH_47,REG_BASE_ETH, (47<<3))
#define ETH_48_T _am(_ETH_48,REG_BASE_ETH, (48<<3))
#define ETH_49_T _am(_ETH_49,REG_BASE_ETH, (49<<3))
#define ETH_50_T _am(_ETH_50,REG_BASE_ETH, (50<<3))
#define ETH_51_T _am(_ETH_51,REG_BASE_ETH, (51<<3))
#define ETH_52_T _am(_ETH_52,REG_BASE_ETH, (52<<3))
#define ETH_53_T _am(_ETH_53,REG_BASE_ETH, (53<<3))
#define ETH_54_T _am(_ETH_54,REG_BASE_ETH, (54<<3))
#define ETH_55_T _am(_ETH_55,REG_BASE_ETH, (55<<3))
#define ETH_56_T _am(_ETH_56,REG_BASE_ETH, (56<<3))
#define ETH_57_T _am(_ETH_57,REG_BASE_ETH, (57<<3))
#define ETH_58_T _am(_ETH_58,REG_BASE_ETH, (58<<3))
#define ETH_59_T _am(_ETH_59,REG_BASE_ETH, (59<<3))
#define ETH_60_T _am(_ETH_60,REG_BASE_ETH, (60<<3))
#define ETH_61_T _am(_ETH_61,REG_BASE_ETH, (61<<3))
#define ETH_62_T _am(_ETH_62,REG_BASE_ETH, (62<<3))
#define ETH_63_T _am(_ETH_63,REG_BASE_ETH, (63<<3))
#define ETH_64_T _am(_ETH_64,REG_BASE_ETH, (64<<3))
#define ETH_65_T _am(_ETH_65,REG_BASE_ETH, (65<<3))
#define ETH_66_T _am(_ETH_66,REG_BASE_ETH, (66<<3))
#define ETH_67_T _am(_ETH_67,REG_BASE_ETH, (67<<3))
#define ETH_68_T _am(_ETH_68,REG_BASE_ETH, (68<<3))
#define ETH_69_T _am(_ETH_69,REG_BASE_ETH, (69<<3))
#define ETH_70_T _am(_ETH_70,REG_BASE_ETH, (70<<3))
#define ETH_71_T _am(_ETH_71,REG_BASE_ETH, (71<<3))
#define ETH_72_T _am(_ETH_72,REG_BASE_ETH, (72<<3))
#define ETH_73_T _am(_ETH_73,REG_BASE_ETH, (73<<3))
#define ETH_74_T _am(_ETH_74,REG_BASE_ETH, (74<<3))
#define ETH_75_T _am(_ETH_75,REG_BASE_ETH, (75<<3))
#define ETH_76_T _am(_ETH_76,REG_BASE_ETH, (76<<3))
#define ETH_77_T _am(_ETH_77,REG_BASE_ETH, (77<<3))
#define ETH_78_T _am(_ETH_78,REG_BASE_ETH, (78<<3))
#define ETH_79_T _am(_ETH_79,REG_BASE_ETH, (79<<3))
#define ETH_80_T _am(_ETH_80,REG_BASE_ETH, (80<<3))
#define ETH_81_T _am(_ETH_81,REG_BASE_ETH, (81<<3))
#define ETH_82_T _am(_ETH_82,REG_BASE_ETH, (82<<3))
#define ETH_83_T _am(_ETH_83,REG_BASE_ETH, (83<<3))
#define ETH_84_T _am(_ETH_84,REG_BASE_ETH, (84<<3))
#define ETH_85_T _am(_ETH_85,REG_BASE_ETH, (85<<3))
#define ETH_86_T _am(_ETH_86,REG_BASE_ETH, (86<<3))
#define ETH_87_T _am(_ETH_87,REG_BASE_ETH, (87<<3))
#define ETH_88_T _am(_ETH_88,REG_BASE_ETH, (88<<3))
#define ETH_89_T _am(_ETH_89,REG_BASE_ETH, (89<<3))
#define ETH_90_T _am(_ETH_90,REG_BASE_ETH, (90<<3))
#define ETH_91_T _am(_ETH_91,REG_BASE_ETH, (91<<3))
#define ETH_92_T _am(_ETH_92,REG_BASE_ETH, (92<<3))
#define ETH_93_T _am(_ETH_93,REG_BASE_ETH, (93<<3))
#define ETH_94_T _am(_ETH_94,REG_BASE_ETH, (94<<3))
#define ETH_95_T _am(_ETH_95,REG_BASE_ETH, (95<<3))
#define ETH_96_T _am(_ETH_96,REG_BASE_ETH, (96<<3))
#define ETH_97_T _am(_ETH_97,REG_BASE_ETH, (97<<3))

#define GPIO_00_T _am(_GPIO_0,REG_BASE_GPIO, (0<<3))
#define GPIO_01_T _am(_GPIO_1,REG_BASE_GPIO, (1<<3))
#define GPIO_02_T _am(_GPIO_2,REG_BASE_GPIO, (2<<3))
#define GPIO_03_T _am(_GPIO_3,REG_BASE_GPIO, (3<<3))
#define GPIO_04_T _am(_GPIO_4,REG_BASE_GPIO, (4<<3))
#define GPIO_05_T _am(_GPIO_5,REG_BASE_GPIO, (5<<3))
#define GPIO_06_T _am(_GPIO_6,REG_BASE_GPIO, (6<<3))
#define GPIO_07_T _am(_GPIO_7,REG_BASE_GPIO, (7<<3))
#define GPIO_08_T _am(_GPIO_8,REG_BASE_GPIO, (8<<3))
#define GPIO_09_T _am(_GPIO_9,REG_BASE_GPIO, (9<<3))
#define GPIO_10_T _am(_GPIO_10,REG_BASE_GPIO, (10<<3))
#define GPIO_11_T _am(_GPIO_11,REG_BASE_GPIO, (11<<3))
#define GPIO_12_T _am(_GPIO_12,REG_BASE_GPIO, (12<<3))
#define GPIO_13_T _am(_GPIO_13,REG_BASE_GPIO, (13<<3))
#define GPIO_14_T _am(_GPIO_14,REG_BASE_GPIO, (14<<3))
#define GPIO_15_T _am(_GPIO_15,REG_BASE_GPIO, (15<<3))
#define GPIO_16_T _am(_GPIO_16,REG_BASE_GPIO, (16<<3))
#define GPIO_17_T _am(_GPIO_17,REG_BASE_GPIO, (17<<3))
#define GPIO_18_T _am(_GPIO_18,REG_BASE_GPIO, (18<<3))
#define GPIO_19_T _am(_GPIO_19,REG_BASE_GPIO, (19<<3))
#define GPIO_20_T _am(_GPIO_20,REG_BASE_GPIO, (20<<3))
#define GPIO_21_T _am(_GPIO_21,REG_BASE_GPIO, (21<<3))
#define GPIO_22_T _am(_GPIO_22,REG_BASE_GPIO, (22<<3))
#define GPIO_23_T _am(_GPIO_23,REG_BASE_GPIO, (23<<3))
#define GPIO_24_T _am(_GPIO_24,REG_BASE_GPIO, (24<<3))
#define GPIO_25_T _am(_GPIO_25,REG_BASE_GPIO, (25<<3))
#define GPIO_26_T _am(_GPIO_26,REG_BASE_GPIO, (26<<3))
#define GPIO_27_T _am(_GPIO_27,REG_BASE_GPIO, (27<<3))
#define GPIO_28_T _am(_GPIO_28,REG_BASE_GPIO, (28<<3))
#define GPIO_29_T _am(_GPIO_29,REG_BASE_GPIO, (29<<3))
#define GPIO_30_T _am(_GPIO_30,REG_BASE_GPIO, (30<<3))
#define GPIO_31_T _am(_GPIO_31,REG_BASE_GPIO, (31<<3))
#define GPIO_32_T _am(_GPIO_32,REG_BASE_GPIO, (32<<3))
#define GPIO_33_T _am(_GPIO_33,REG_BASE_GPIO, (33<<3))
#define GPIO_34_T _am(_GPIO_34,REG_BASE_GPIO, (34<<3))
#define GPIO_35_T _am(_GPIO_35,REG_BASE_GPIO, (35<<3))
#define GPIO_36_T _am(_GPIO_36,REG_BASE_GPIO, (36<<3))
#define GPIO_37_T _am(_GPIO_37,REG_BASE_GPIO, (37<<3))
#define GPIO_38_T _am(_GPIO_38,REG_BASE_GPIO, (38<<3))
#define GPIO_39_T _am(_GPIO_39,REG_BASE_GPIO, (39<<3))
#define GPIO_40_T _am(_GPIO_40,REG_BASE_GPIO, (40<<3))
#define GPIO_41_T _am(_GPIO_41,REG_BASE_GPIO, (41<<3))
#define GPIO_42_T _am(_GPIO_42,REG_BASE_GPIO, (42<<3))
#define GPIO_43_T _am(_GPIO_43,REG_BASE_GPIO, (43<<3))
#define GPIO_44_T _am(_GPIO_44,REG_BASE_GPIO, (44<<3))
#define GPIO_45_T _am(_GPIO_45,REG_BASE_GPIO, (45<<3))
#define GPIO_46_T _am(_GPIO_46,REG_BASE_GPIO, (46<<3))
#define GPIO_47_T _am(_GPIO_47,REG_BASE_GPIO, (47<<3))
#define GPIO_48_T _am(_GPIO_48,REG_BASE_GPIO, (48<<3))
#define GPIO_49_T _am(_GPIO_49,REG_BASE_GPIO, (49<<3))
#define GPIO_50_T _am(_GPIO_50,REG_BASE_GPIO, (50<<3))
#define GPIO_51_T _am(_GPIO_51,REG_BASE_GPIO, (51<<3))
#define GPIO_52_T _am(_GPIO_52,REG_BASE_GPIO, (52<<3))
#define GPIO_53_T _am(_GPIO_53,REG_BASE_GPIO, (53<<3))
#define GPIO_54_T _am(_GPIO_54,REG_BASE_GPIO, (54<<3))
#define GPIO_55_T _am(_GPIO_55,REG_BASE_GPIO, (55<<3))
#define GPIO_56_T _am(_GPIO_56,REG_BASE_GPIO, (56<<3))
#define GPIO_57_T _am(_GPIO_57,REG_BASE_GPIO, (57<<3))
#define GPIO_58_T _am(_GPIO_58,REG_BASE_GPIO, (58<<3))
#define GPIO_59_T _am(_GPIO_59,REG_BASE_GPIO, (59<<3))
#define GPIO_60_T _am(_GPIO_60,REG_BASE_GPIO, (60<<3))
#define GPIO_61_T _am(_GPIO_61,REG_BASE_GPIO, (61<<3))
#define GPIO_62_T _am(_GPIO_62,REG_BASE_GPIO, (62<<3))
#define GPIO_63_T _am(_GPIO_63,REG_BASE_GPIO, (63<<3))
#define GPIO_64_T _am(_GPIO_64,REG_BASE_GPIO, (64<<3))
#define GPIO_65_T _am(_GPIO_65,REG_BASE_GPIO, (65<<3))
#define GPIO_66_T _am(_GPIO_66,REG_BASE_GPIO, (66<<3))
#define GPIO_67_T _am(_GPIO_67,REG_BASE_GPIO, (67<<3))
#define GPIO_68_T _am(_GPIO_68,REG_BASE_GPIO, (68<<3))
#define GPIO_69_T _am(_GPIO_69,REG_BASE_GPIO, (69<<3))
#define GPIO_70_T _am(_GPIO_70,REG_BASE_GPIO, (70<<3))
#define GPIO_71_T _am(_GPIO_71,REG_BASE_GPIO, (71<<3))
#define GPIO_72_T _am(_GPIO_72,REG_BASE_GPIO, (72<<3))
#define GPIO_73_T _am(_GPIO_73,REG_BASE_GPIO, (73<<3))
#define GPIO_74_T _am(_GPIO_74,REG_BASE_GPIO, (74<<3))
#define GPIO_75_T _am(_GPIO_75,REG_BASE_GPIO, (75<<3))
#define GPIO_76_T _am(_GPIO_76,REG_BASE_GPIO, (76<<3))
#define GPIO_77_T _am(_GPIO_77,REG_BASE_GPIO, (77<<3))
#define GPIO_78_T _am(_GPIO_78,REG_BASE_GPIO, (78<<3))
#define GPIO_79_T _am(_GPIO_79,REG_BASE_GPIO, (79<<3))
#define GPIO_80_T _am(_GPIO_80,REG_BASE_GPIO, (80<<3))
#define GPIO_81_T _am(_GPIO_81,REG_BASE_GPIO, (81<<3))
#define GPIO_82_T _am(_GPIO_82,REG_BASE_GPIO, (82<<3))
#define GPIO_83_T _am(_GPIO_83,REG_BASE_GPIO, (83<<3))
#define GPIO_84_T _am(_GPIO_84,REG_BASE_GPIO, (84<<3))
#define GPIO_85_T _am(_GPIO_85,REG_BASE_GPIO, (85<<3))
#define GPIO_86_T _am(_GPIO_86,REG_BASE_GPIO, (86<<3))
#define GPIO_87_T _am(_GPIO_87,REG_BASE_GPIO, (87<<3))
#define GPIO_88_T _am(_GPIO_88,REG_BASE_GPIO, (88<<3))
#define GPIO_89_T _am(_GPIO_89,REG_BASE_GPIO, (89<<3))
#define GPIO_90_T _am(_GPIO_90,REG_BASE_GPIO, (90<<3))
#define GPIO_91_T _am(_GPIO_91,REG_BASE_GPIO, (91<<3))
#define GPIO_92_T _am(_GPIO_92,REG_BASE_GPIO, (92<<3))
#define GPIO_93_T _am(_GPIO_93,REG_BASE_GPIO, (93<<3))
#define GPIO_94_T _am(_GPIO_94,REG_BASE_GPIO, (94<<3))
#define GPIO_95_T _am(_GPIO_95,REG_BASE_GPIO, (95<<3))

#define SPI0_00_T _am(_SPI0_0,REG_BASE_SPI0, (0<<3))
#define SPI0_01_T _am(_SPI0_1,REG_BASE_SPI0, (1<<3))
#define SPI0_02_T _am(_SPI0_2,REG_BASE_SPI0, (2<<3))

#define SPI1_00_T _am(_SPI1_0,REG_BASE_SPI1, (0<<3))
#define SPI1_01_T _am(_SPI1_1,REG_BASE_SPI1, (1<<3))
#define SPI1_02_T _am(_SPI1_2,REG_BASE_SPI1, (2<<3))

#define SPI2_00_T _am(_SPI2_0,REG_BASE_SPI2, (0<<3))
#define SPI2_01_T _am(_SPI2_1,REG_BASE_SPI2, (1<<3))
#define SPI2_02_T _am(_SPI2_2,REG_BASE_SPI2, (2<<3))

#define SPI3_00_T _am(_SPI3_0,REG_BASE_SPI3, (0<<3))
#define SPI3_01_T _am(_SPI3_1,REG_BASE_SPI3, (1<<3))
#define SPI3_02_T _am(_SPI3_2,REG_BASE_SPI3, (2<<3))

#define SPI4_00_T _am(_SPI4_0,REG_BASE_SPI4, (0<<3))
#define SPI4_01_T _am(_SPI4_1,REG_BASE_SPI4, (1<<3))
#define SPI4_02_T _am(_SPI4_2,REG_BASE_SPI4, (2<<3))

#define SPI5_00_T _am(_SPI5_0,REG_BASE_SPI5, (0<<3))
#define SPI5_01_T _am(_SPI5_1,REG_BASE_SPI5, (1<<3))
#define SPI5_02_T _am(_SPI5_2,REG_BASE_SPI5, (2<<3))

#define SPI6_00_T _am(_SPI6_0,REG_BASE_SPI6, (0<<3))
#define SPI6_01_T _am(_SPI6_1,REG_BASE_SPI6, (1<<3))
#define SPI6_02_T _am(_SPI6_2,REG_BASE_SPI6, (2<<3))

#define SPI7_00_T _am(_SPI7_0,REG_BASE_SPI7, (0<<3))
#define SPI7_01_T _am(_SPI7_1,REG_BASE_SPI7, (1<<3))
#define SPI7_02_T _am(_SPI7_2,REG_BASE_SPI7, (2<<3))

#define SPI8_00_T _am(_SPI8_0,REG_BASE_SPI8, (0<<3))
#define SPI8_01_T _am(_SPI8_1,REG_BASE_SPI8, (1<<3))
#define SPI8_02_T _am(_SPI8_2,REG_BASE_SPI8, (2<<3))

#define I2C0_00_T _am(_I2C0_0,REG_BASE_I2C0, (0<<3))
#define I2C0_01_T _am(_I2C0_1,REG_BASE_I2C0, (1<<3))
#define I2C0_02_T _am(_I2C0_2,REG_BASE_I2C0, (2<<3))
#define I2C0_03_T _am(_I2C0_3,REG_BASE_I2C0, (3<<3))

#define I2C1_00_T _am(_I2C1_0,REG_BASE_I2C1, (0<<3))
#define I2C1_01_T _am(_I2C1_1,REG_BASE_I2C1, (1<<3))
#define I2C1_02_T _am(_I2C1_2,REG_BASE_I2C1, (2<<3))
#define I2C1_03_T _am(_I2C1_3,REG_BASE_I2C1, (3<<3))

#define I2C2_00_T _am(_I2C2_0,REG_BASE_I2C2, (0<<3))
#define I2C2_01_T _am(_I2C2_1,REG_BASE_I2C2, (1<<3))
#define I2C2_02_T _am(_I2C2_2,REG_BASE_I2C2, (2<<3))
#define I2C2_03_T _am(_I2C2_3,REG_BASE_I2C2, (3<<3))

#define I2C3_00_T _am(_I2C3_0,REG_BASE_I2C3, (0<<3))
#define I2C3_01_T _am(_I2C3_1,REG_BASE_I2C3, (1<<3))
#define I2C3_02_T _am(_I2C3_2,REG_BASE_I2C3, (2<<3))
#define I2C3_03_T _am(_I2C3_3,REG_BASE_I2C3, (3<<3))

#define I2C4_00_T _am(_I2C4_0,REG_BASE_I2C4, (0<<3))
#define I2C4_01_T _am(_I2C4_1,REG_BASE_I2C4, (1<<3))
#define I2C4_02_T _am(_I2C4_2,REG_BASE_I2C4, (2<<3))
#define I2C4_03_T _am(_I2C4_3,REG_BASE_I2C4, (3<<3))

#define I2C5_00_T _am(_I2C5_0,REG_BASE_I2C5, (0<<3))
#define I2C5_01_T _am(_I2C5_1,REG_BASE_I2C5, (1<<3))
#define I2C5_02_T _am(_I2C5_2,REG_BASE_I2C5, (2<<3))
#define I2C5_03_T _am(_I2C5_3,REG_BASE_I2C5, (3<<3))

#define I2C6_00_T _am(_I2C6_0,REG_BASE_I2C6, (0<<3))
#define I2C6_01_T _am(_I2C6_1,REG_BASE_I2C6, (1<<3))
#define I2C6_02_T _am(_I2C6_2,REG_BASE_I2C6, (2<<3))
#define I2C6_03_T _am(_I2C6_3,REG_BASE_I2C6, (3<<3))

#define I2C7_00_T _am(_I2C7_0,REG_BASE_I2C7, (0<<3))
#define I2C7_01_T _am(_I2C7_1,REG_BASE_I2C7, (1<<3))
#define I2C7_02_T _am(_I2C7_2,REG_BASE_I2C7, (2<<3))
#define I2C7_03_T _am(_I2C7_3,REG_BASE_I2C7, (3<<3))

#define I2C8_00_T _am(_I2C8_0,REG_BASE_I2C8, (0<<3))
#define I2C8_01_T _am(_I2C8_1,REG_BASE_I2C8, (1<<3))
#define I2C8_02_T _am(_I2C8_2,REG_BASE_I2C8, (2<<3))
#define I2C8_03_T _am(_I2C8_3,REG_BASE_I2C8, (3<<3))

#define TIMER0_00_T _am(_TIMER0_0,REG_BASE_TIMER0, (0<<3))
#define TIMER0_01_T _am(_TIMER0_1,REG_BASE_TIMER0, (1<<3))

#define TIMER1_00_T _am(_TIMER1_0,REG_BASE_TIMER1, (0<<3))
#define TIMER1_01_T _am(_TIMER1_1,REG_BASE_TIMER1, (1<<3))

#define TIMER2_00_T _am(_TIMER2_0,REG_BASE_TIMER2, (0<<3))
#define TIMER2_01_T _am(_TIMER2_1,REG_BASE_TIMER2, (1<<3))

#define TIMER3_00_T _am(_TIMER3_0,REG_BASE_TIMER3, (0<<3))
#define TIMER3_01_T _am(_TIMER3_1,REG_BASE_TIMER3, (1<<3))

#define TIMER4_00_T _am(_TIMER4_0,REG_BASE_TIMER4, (0<<3))
#define TIMER4_01_T _am(_TIMER4_1,REG_BASE_TIMER4, (1<<3))

#define TIMER5_00_T _am(_TIMER5_0,REG_BASE_TIMER5, (0<<3))
#define TIMER5_01_T _am(_TIMER5_1,REG_BASE_TIMER5, (1<<3))

#define TIMER6_00_T _am(_TIMER6_0,REG_BASE_TIMER6, (0<<3))
#define TIMER6_01_T _am(_TIMER6_1,REG_BASE_TIMER6, (1<<3))

#define TIMER7_00_T _am(_TIMER7_0,REG_BASE_TIMER7, (0<<3))
#define TIMER7_01_T _am(_TIMER7_1,REG_BASE_TIMER7, (1<<3))

#define TIMER8_00_T _am(_TIMER8_0,REG_BASE_TIMER8, (0<<3))
#define TIMER8_01_T _am(_TIMER8_1,REG_BASE_TIMER8, (1<<3))

#define TIMER9_00_T _am(_TIMER9_0,REG_BASE_TIMER9, (0<<3))
#define TIMER9_01_T _am(_TIMER9_1,REG_BASE_TIMER9, (1<<3))

#define TIMER10_00_T _am(_TIMER10_0,REG_BASE_TIMER10, (0<<3))
#define TIMER10_01_T _am(_TIMER10_1,REG_BASE_TIMER10, (1<<3))

#define TIMER11_00_T _am(_TIMER11_0,REG_BASE_TIMER11, (0<<3))
#define TIMER11_01_T _am(_TIMER11_1,REG_BASE_TIMER11, (1<<3))

#define TIMER12_00_T _am(_TIMER12_0,REG_BASE_TIMER12, (0<<3))
#define TIMER12_01_T _am(_TIMER12_1,REG_BASE_TIMER12, (1<<3))

#define TIMER13_00_T _am(_TIMER13_0,REG_BASE_TIMER13, (0<<3))
#define TIMER13_01_T _am(_TIMER13_1,REG_BASE_TIMER13, (1<<3))

#define TIMER14_00_T _am(_TIMER14_0,REG_BASE_TIMER14, (0<<3))
#define TIMER14_01_T _am(_TIMER14_1,REG_BASE_TIMER14, (1<<3))

#define TIMER15_00_T _am(_TIMER15_0,REG_BASE_TIMER15, (0<<3))
#define TIMER15_01_T _am(_TIMER15_1,REG_BASE_TIMER15, (1<<3))

#define TIMER16_00_T _am(_TIMER16_0,REG_BASE_TIMER16, (0<<3))
#define TIMER16_01_T _am(_TIMER16_1,REG_BASE_TIMER16, (1<<3))

#define TIMER17_00_T _am(_TIMER17_0,REG_BASE_TIMER17, (0<<3))
#define TIMER17_01_T _am(_TIMER17_1,REG_BASE_TIMER17, (1<<3))

#define TIMER18_00_T _am(_TIMER18_0,REG_BASE_TIMER18, (0<<3))
#define TIMER18_01_T _am(_TIMER18_1,REG_BASE_TIMER18, (1<<3))

#define TIMER19_00_T _am(_TIMER19_0,REG_BASE_TIMER19, (0<<3))
#define TIMER19_01_T _am(_TIMER19_1,REG_BASE_TIMER19, (1<<3))

#define TIMER20_00_T _am(_TIMER20_0,REG_BASE_TIMER20, (0<<3))
#define TIMER20_01_T _am(_TIMER20_1,REG_BASE_TIMER20, (1<<3))

#define TIMER21_00_T _am(_TIMER21_0,REG_BASE_TIMER21, (0<<3))
#define TIMER21_01_T _am(_TIMER21_1,REG_BASE_TIMER21, (1<<3))

#define TIMER22_00_T _am(_TIMER22_0,REG_BASE_TIMER22, (0<<3))
#define TIMER22_01_T _am(_TIMER22_1,REG_BASE_TIMER22, (1<<3))

#define TIMER23_00_T _am(_TIMER23_0,REG_BASE_TIMER23, (0<<3))
#define TIMER23_01_T _am(_TIMER23_1,REG_BASE_TIMER23, (1<<3))

#define TIMER24_00_T _am(_TIMER24_0,REG_BASE_TIMER24, (0<<3))
#define TIMER24_01_T _am(_TIMER24_1,REG_BASE_TIMER24, (1<<3))

#define TIMER25_00_T _am(_TIMER25_0,REG_BASE_TIMER25, (0<<3))
#define TIMER25_01_T _am(_TIMER25_1,REG_BASE_TIMER25, (1<<3))

#define TIMER26_00_T _am(_TIMER26_0,REG_BASE_TIMER26, (0<<3))
#define TIMER26_01_T _am(_TIMER26_1,REG_BASE_TIMER26, (1<<3))

#define TIMER27_00_T _am(_TIMER27_0,REG_BASE_TIMER27, (0<<3))
#define TIMER27_01_T _am(_TIMER27_1,REG_BASE_TIMER27, (1<<3))

#define TIMER28_00_T _am(_TIMER28_0,REG_BASE_TIMER28, (0<<3))
#define TIMER28_01_T _am(_TIMER28_1,REG_BASE_TIMER28, (1<<3))

#define TIMER29_00_T _am(_TIMER29_0,REG_BASE_TIMER29, (0<<3))
#define TIMER29_01_T _am(_TIMER29_1,REG_BASE_TIMER29, (1<<3))

#define TIMER30_00_T _am(_TIMER30_0,REG_BASE_TIMER30, (0<<3))
#define TIMER30_01_T _am(_TIMER30_1,REG_BASE_TIMER30, (1<<3))

#define TIMER31_00_T _am(_TIMER31_0,REG_BASE_TIMER31, (0<<3))
#define TIMER31_01_T _am(_TIMER31_1,REG_BASE_TIMER31, (1<<3))

#define TIMER32_00_T _am(_TIMER32_0,REG_BASE_TIMER32, (0<<3))
#define TIMER32_01_T _am(_TIMER32_1,REG_BASE_TIMER32, (1<<3))

#define TIMER33_00_T _am(_TIMER33_0,REG_BASE_TIMER33, (0<<3))
#define TIMER33_01_T _am(_TIMER33_1,REG_BASE_TIMER33, (1<<3))

#define TIMER34_00_T _am(_TIMER34_0,REG_BASE_TIMER34, (0<<3))
#define TIMER34_01_T _am(_TIMER34_1,REG_BASE_TIMER34, (1<<3))

#define TIMER35_00_T _am(_TIMER35_0,REG_BASE_TIMER35, (0<<3))
#define TIMER35_01_T _am(_TIMER35_1,REG_BASE_TIMER35, (1<<3))

#define TIMER36_00_T _am(_TIMER36_0,REG_BASE_TIMER36, (0<<3))
#define TIMER36_01_T _am(_TIMER36_1,REG_BASE_TIMER36, (1<<3))

#define TIMER37_00_T _am(_TIMER37_0,REG_BASE_TIMER37, (0<<3))
#define TIMER37_01_T _am(_TIMER37_1,REG_BASE_TIMER37, (1<<3))

#define TIMER38_00_T _am(_TIMER38_0,REG_BASE_TIMER38, (0<<3))
#define TIMER38_01_T _am(_TIMER38_1,REG_BASE_TIMER38, (1<<3))

#define UART0_00_T _am(_UART0_0,REG_BASE_UART0, (0<<3))
#define UART0_01_T _am(_UART0_1,REG_BASE_UART0, (1<<3))
#define UART0_02_T _am(_UART0_2,REG_BASE_UART0, (2<<3))
#define UART0_03_T _am(_UART0_3,REG_BASE_UART0, (3<<3))

#define UART1_00_T _am(_UART1_0,REG_BASE_UART1, (0<<3))
#define UART1_01_T _am(_UART1_1,REG_BASE_UART1, (1<<3))
#define UART1_02_T _am(_UART1_2,REG_BASE_UART1, (2<<3))
#define UART1_03_T _am(_UART1_3,REG_BASE_UART1, (3<<3))

#define UART2_00_T _am(_UART2_0,REG_BASE_UART2, (0<<3))
#define UART2_01_T _am(_UART2_1,REG_BASE_UART2, (1<<3))
#define UART2_02_T _am(_UART2_2,REG_BASE_UART2, (2<<3))
#define UART2_03_T _am(_UART2_3,REG_BASE_UART2, (3<<3))

#define UART3_00_T _am(_UART3_0,REG_BASE_UART3, (0<<3))
#define UART3_01_T _am(_UART3_1,REG_BASE_UART3, (1<<3))
#define UART3_02_T _am(_UART3_2,REG_BASE_UART3, (2<<3))
#define UART3_03_T _am(_UART3_3,REG_BASE_UART3, (3<<3))

#define UART4_00_T _am(_UART4_0,REG_BASE_UART4, (0<<3))
#define UART4_01_T _am(_UART4_1,REG_BASE_UART4, (1<<3))
#define UART4_02_T _am(_UART4_2,REG_BASE_UART4, (2<<3))
#define UART4_03_T _am(_UART4_3,REG_BASE_UART4, (3<<3))

#define UART5_00_T _am(_UART5_0,REG_BASE_UART5, (0<<3))
#define UART5_01_T _am(_UART5_1,REG_BASE_UART5, (1<<3))
#define UART5_02_T _am(_UART5_2,REG_BASE_UART5, (2<<3))
#define UART5_03_T _am(_UART5_3,REG_BASE_UART5, (3<<3))

#define UART6_00_T _am(_UART6_0,REG_BASE_UART6, (0<<3))
#define UART6_01_T _am(_UART6_1,REG_BASE_UART6, (1<<3))
#define UART6_02_T _am(_UART6_2,REG_BASE_UART6, (2<<3))
#define UART6_03_T _am(_UART6_3,REG_BASE_UART6, (3<<3))

#define UART7_00_T _am(_UART7_0,REG_BASE_UART7, (0<<3))
#define UART7_01_T _am(_UART7_1,REG_BASE_UART7, (1<<3))
#define UART7_02_T _am(_UART7_2,REG_BASE_UART7, (2<<3))
#define UART7_03_T _am(_UART7_3,REG_BASE_UART7, (3<<3))

#define UART8_00_T _am(_UART8_0,REG_BASE_UART8, (0<<3))
#define UART8_01_T _am(_UART8_1,REG_BASE_UART8, (1<<3))
#define UART8_02_T _am(_UART8_2,REG_BASE_UART8, (2<<3))
#define UART8_03_T _am(_UART8_3,REG_BASE_UART8, (3<<3))

#define AES_00_T _am(_AES_0,REG_BASE_AES, (0<<3))
#define AES_01_T _am(_AES_1,REG_BASE_AES, (1<<3))
#define AES_02_T _am(_AES_2,REG_BASE_AES, (2<<3))
#define AES_03_T _am(_AES_3,REG_BASE_AES, (3<<3))
#define AES_04_T _am(_AES_4,REG_BASE_AES, (4<<3))
#define AES_05_T _am(_AES_5,REG_BASE_AES, (5<<3))
#define AES_06_T _am(_AES_6,REG_BASE_AES, (6<<3))
#define AES_07_T _am(_AES_7,REG_BASE_AES, (7<<3))
#define AES_08_T _am(_AES_8,REG_BASE_AES, (8<<3))
#define AES_09_T _am(_AES_9,REG_BASE_AES, (9<<3))
#define AES_10_T _am(_AES_10,REG_BASE_AES, (10<<3))
#define AES_11_T _am(_AES_11,REG_BASE_AES, (11<<3))
#define AES_12_T _am(_AES_12,REG_BASE_AES, (12<<3))
#define AES_13_T _am(_AES_13,REG_BASE_AES, (13<<3))
#define AES_14_T _am(_AES_14,REG_BASE_AES, (14<<3))
#define AES_15_T _am(_AES_15,REG_BASE_AES, (15<<3))

#define SHA_00_T _am(_SHA_0,REG_BASE_SHA, (0<<3))
#define SHA_01_T _am(_SHA_0,REG_BASE_SHA, (1<<3))
#define SHA_02_T _am(_SHA_2,REG_BASE_SHA, (2<<3))
#define SHA_03_T _am(_SHA_3,REG_BASE_SHA, (3<<3))
#define SHA_04_T _am(_SHA_4,REG_BASE_SHA, (4<<3))
#define SHA_05_T _am(_SHA_5,REG_BASE_SHA, (5<<3))
#define SHA_06_T _am(_SHA_6,REG_BASE_SHA, (6<<3))
#define SHA_07_T _am(_SHA_7,REG_BASE_SHA, (7<<3))
#define SHA_08_T _am(_SHA_8,REG_BASE_SHA, (8<<3))
#define SHA_09_T _am(_SHA_9,REG_BASE_SHA, (9<<3))
#define SHA_10_T _am(_SHA_10,REG_BASE_SHA, (10<<3))
#define SHA_11_T _am(_SHA_11,REG_BASE_SHA, (11<<3))

#define CHKSUM_00_T _am(_CHKSUM_0,REG_BASE_CHKSUM, (0<<3))
#define CHKSUM_01_T _am(_CHKSUM_1,REG_BASE_CHKSUM, (1<<3))
#define CHKSUM_02_T _am(_CHKSUM_2,REG_BASE_CHKSUM, (2<<3))
#define CHKSUM_03_T _am(_CHKSUM_3,REG_BASE_CHKSUM, (3<<3))

#define SYS_00_T _am(_SYS_0,REG_BASE_SYS, (0<<3))
#define SYS_01_T _am(_SYS_1,REG_BASE_SYS, (1<<3))
#define SYS_02_T _am(_SYS_2,REG_BASE_SYS, (2<<3))
#define SYS_03_T _am(_SYS_3,REG_BASE_SYS, (3<<3))
#define SYS_04_T _am(_SYS_4,REG_BASE_SYS, (4<<3))
#define SYS_05_T _am(_SYS_5,REG_BASE_SYS, (5<<3))
#define SYS_06_T _am(_SYS_6,REG_BASE_SYS, (6<<3))
#define SYS_07_T _am(_SYS_7,REG_BASE_SYS, (7<<3))
#define SYS_16_T _am(_SYS_16,REG_BASE_SYS, (16<<3))
#define SYS_17_T _am(_SYS_17,REG_BASE_SYS, (17<<3))
#define SYS_18_T _am(_SYS_18,REG_BASE_SYS, (18<<3))
#define SYS_19_T _am(_SYS_19,REG_BASE_SYS, (19<<3))
#define SYS_20_T _am(_SYS_20,REG_BASE_SYS, (20<<3))
#define SYS_21_T _am(_SYS_21,REG_BASE_SYS, (21<<3))
#define SYS_22_T _am(_SYS_22,REG_BASE_SYS, (22<<3))
#define SYS_23_T _am(_SYS_23,REG_BASE_SYS, (23<<3))
#define SYS_24_T _am(_SYS_24,REG_BASE_SYS, (24<<3))
#define SYS_25_T _am(_SYS_25,REG_BASE_SYS, (25<<3))
#define SYS_32_T _am(_SYS_32,REG_BASE_SYS, (32<<3))
#define SYS_33_T _am(_SYS_33,REG_BASE_SYS, (33<<3))
#define SYS_34_T _am(_SYS_34,REG_BASE_SYS, (34<<3))
#define SYS_35_T _am(_SYS_35,REG_BASE_SYS, (35<<3))
#define SYS_36_T _am(_SYS_36,REG_BASE_SYS, (36<<3))
#define SYS_37_T _am(_SYS_37,REG_BASE_SYS, (37<<3))
#define SYS_38_T _am(_SYS_38,REG_BASE_SYS, (38<<3))
#define SYS_39_T _am(_SYS_39,REG_BASE_SYS, (39<<3))
#define SYS_40_T _am(_SYS_40,REG_BASE_SYS, (40<<3))
#define SYS_41_T _am(_SYS_41,REG_BASE_SYS, (41<<3))
#define SYS_42_T _am(_SYS_42,REG_BASE_SYS, (42<<3))
#define SYS_43_T _am(_SYS_43,REG_BASE_SYS, (43<<3))
#define SYS_44_T _am(_SYS_44,REG_BASE_SYS, (44<<3))
#define SYS_45_T _am(_SYS_45,REG_BASE_SYS, (45<<3))
#define SYS_46_T _am(_SYS_46,REG_BASE_SYS, (46<<3))
#define SYS_47_T _am(_SYS_47,REG_BASE_SYS, (47<<3))
#define SYS_48_T _am(_SYS_48,REG_BASE_SYS, (48<<3))
#define SYS_49_T _am(_SYS_49,REG_BASE_SYS, (49<<3))
#define SYS_50_T _am(_SYS_50,REG_BASE_SYS, (50<<3))
#define SYS_51_T _am(_SYS_51,REG_BASE_SYS, (51<<3))
#define SYS_52_T _am(_SYS_52,REG_BASE_SYS, (52<<3))
#define SYS_53_T _am(_SYS_53,REG_BASE_SYS, (53<<3))
#define SYS_54_T _am(_SYS_54,REG_BASE_SYS, (54<<3))
#define SYS_55_T _am(_SYS_55,REG_BASE_SYS, (55<<3))
#define SYS_56_T _am(_SYS_56,REG_BASE_SYS, (56<<3))
#define SYS_57_T _am(_SYS_57,REG_BASE_SYS, (57<<3))
#define SYS_64_T _am(_SYS_64,REG_BASE_SYS, (64<<3))
#define SYS_65_T _am(_SYS_65,REG_BASE_SYS, (65<<3))
#define SYS_256_T _am(_SYS_256,REG_BASE_SYS, (256<<3))
#define SYS_257_T _am(_SYS_257,REG_BASE_SYS, (257<<3))
#define SYS_258_T _am(_SYS_258,REG_BASE_SYS, (258<<3))
#define SYS_259_T _am(_SYS_259,REG_BASE_SYS, (259<<3))
#define SYS_260_T _am(_SYS_260,REG_BASE_SYS, (260<<3))
#define SYS_261_T _am(_SYS_261,REG_BASE_SYS, (261<<3))
#define SYS_262_T _am(_SYS_262,REG_BASE_SYS, (262<<3))
#define SYS_263_T _am(_SYS_263,REG_BASE_SYS, (263<<3))
#define SYS_264_T _am(_SYS_264,REG_BASE_SYS, (264<<3))
#define SYS_265_T _am(_SYS_265,REG_BASE_SYS, (265<<3))
#define SYS_266_T _am(_SYS_266,REG_BASE_SYS, (266<<3))
#define SYS_267_T _am(_SYS_267,REG_BASE_SYS, (267<<3))
#define SYS_268_T _am(_SYS_268,REG_BASE_SYS, (268<<3))
#define SYS_269_T _am(_SYS_269,REG_BASE_SYS, (269<<3))
#define SYS_270_T _am(_SYS_270,REG_BASE_SYS, (270<<3))
#define SYS_271_T _am(_SYS_271,REG_BASE_SYS, (271<<3))
#define SYS_272_T _am(_SYS_272,REG_BASE_SYS, (272<<3))
#define SYS_273_T _am(_SYS_273,REG_BASE_SYS, (273<<3))
#define SYS_274_T _am(_SYS_274,REG_BASE_SYS, (274<<3))
#define SYS_275_T _am(_SYS_275,REG_BASE_SYS, (275<<3))
#define SYS_276_T _am(_SYS_276,REG_BASE_SYS, (276<<3))
#define SYS_277_T _am(_SYS_277,REG_BASE_SYS, (277<<3))
#define SYS_278_T _am(_SYS_278,REG_BASE_SYS, (278<<3))
#define SYS_279_T _am(_SYS_279,REG_BASE_SYS, (279<<3))
#define SYS_280_T _am(_SYS_280,REG_BASE_SYS, (280<<3))
#define SYS_281_T _am(_SYS_281,REG_BASE_SYS, (281<<3))
#define SYS_282_T _am(_SYS_282,REG_BASE_SYS, (282<<3))
#define SYS_283_T _am(_SYS_283,REG_BASE_SYS, (283<<3))
#define SYS_284_T _am(_SYS_284,REG_BASE_SYS, (284<<3))
#define SYS_285_T _am(_SYS_285,REG_BASE_SYS, (285<<3))
#define SYS_286_T _am(_SYS_286,REG_BASE_SYS, (286<<3))
#define SYS_287_T _am(_SYS_287,REG_BASE_SYS, (287<<3))
#define SYS_288_T _am(_SYS_288,REG_BASE_SYS, (288<<3))
#define SYS_289_T _am(_SYS_289,REG_BASE_SYS, (289<<3))
#define SYS_290_T _am(_SYS_290,REG_BASE_SYS, (290<<3))
#define SYS_291_T _am(_SYS_291,REG_BASE_SYS, (291<<3))
#define SYS_292_T _am(_SYS_292,REG_BASE_SYS, (292<<3))
#define SYS_293_T _am(_SYS_293,REG_BASE_SYS, (293<<3))
#define SYS_294_T _am(_SYS_294,REG_BASE_SYS, (294<<3))
#define SYS_295_T _am(_SYS_295,REG_BASE_SYS, (295<<3))
#define SYS_296_T _am(_SYS_296,REG_BASE_SYS, (296<<3))
#define SYS_297_T _am(_SYS_297,REG_BASE_SYS, (297<<3))
#define SYS_298_T _am(_SYS_298,REG_BASE_SYS, (298<<3))
#define SYS_299_T _am(_SYS_299,REG_BASE_SYS, (299<<3))
#define SYS_300_T _am(_SYS_300,REG_BASE_SYS, (300<<3))
#define SYS_301_T _am(_SYS_301,REG_BASE_SYS, (301<<3))
#define SYS_302_T _am(_SYS_302,REG_BASE_SYS, (302<<3))
#define SYS_303_T _am(_SYS_303,REG_BASE_SYS, (303<<3))
#define SYS_304_T _am(_SYS_304,REG_BASE_SYS, (304<<3))
#define SYS_305_T _am(_SYS_305,REG_BASE_SYS, (305<<3))
#define SYS_306_T _am(_SYS_306,REG_BASE_SYS, (306<<3))
#define SYS_307_T _am(_SYS_307,REG_BASE_SYS, (307<<3))
#define SYS_308_T _am(_SYS_308,REG_BASE_SYS, (308<<3))
#define SYS_309_T _am(_SYS_309,REG_BASE_SYS, (309<<3))
#define SYS_310_T _am(_SYS_310,REG_BASE_SYS, (310<<3))
#define SYS_311_T _am(_SYS_311,REG_BASE_SYS, (311<<3))
#define SYS_312_T _am(_SYS_312,REG_BASE_SYS, (312<<3))
#define SYS_313_T _am(_SYS_313,REG_BASE_SYS, (313<<3))
#define SYS_314_T _am(_SYS_314,REG_BASE_SYS, (314<<3))
#define SYS_315_T _am(_SYS_315,REG_BASE_SYS, (315<<3))
#define SYS_316_T _am(_SYS_316,REG_BASE_SYS, (316<<3))
#define SYS_317_T _am(_SYS_317,REG_BASE_SYS, (317<<3))
#define SYS_318_T _am(_SYS_318,REG_BASE_SYS, (318<<3))
#define SYS_319_T _am(_SYS_319,REG_BASE_SYS, (319<<3))
#define SYS_320_T _am(_SYS_320,REG_BASE_SYS, (320<<3))
#define SYS_321_T _am(_SYS_321,REG_BASE_SYS, (321<<3))
#define SYS_322_T _am(_SYS_322,REG_BASE_SYS, (322<<3))
#define SYS_323_T _am(_SYS_323,REG_BASE_SYS, (323<<3))
#define SYS_324_T _am(_SYS_324,REG_BASE_SYS, (324<<3))
#define SYS_325_T _am(_SYS_325,REG_BASE_SYS, (325<<3))
#define SYS_326_T _am(_SYS_326,REG_BASE_SYS, (326<<3))
#define SYS_327_T _am(_SYS_327,REG_BASE_SYS, (327<<3))

#define BDMA0_00_T _am(_BDMA0_0,REG_BASE_BDMA0, (0<<3))
#define BDMA0_01_T _am(_BDMA0_1,REG_BASE_BDMA0, (1<<3))
#define BDMA0_02_T _am(_BDMA0_2,REG_BASE_BDMA0, (2<<3))
#define BDMA0_03_T _am(_BDMA0_3,REG_BASE_BDMA0, (3<<3))

#define BDMA1_00_T _am(_BDMA1_0,REG_BASE_BDMA1, (0<<3))
#define BDMA1_01_T _am(_BDMA1_1,REG_BASE_BDMA1, (1<<3))
#define BDMA1_02_T _am(_BDMA1_2,REG_BASE_BDMA1, (2<<3))
#define BDMA1_03_T _am(_BDMA1_3,REG_BASE_BDMA1, (3<<3))

#define BDMA2_00_T _am(_BDMA2_0,REG_BASE_BDMA2, (0<<3))
#define BDMA2_01_T _am(_BDMA2_1,REG_BASE_BDMA2, (1<<3))
#define BDMA2_02_T _am(_BDMA2_2,REG_BASE_BDMA2, (2<<3))
#define BDMA2_03_T _am(_BDMA2_3,REG_BASE_BDMA2, (3<<3))

#define BDMA3_00_T _am(_BDMA3_0,REG_BASE_BDMA3, (0<<3))
#define BDMA3_01_T _am(_BDMA3_1,REG_BASE_BDMA3, (1<<3))
#define BDMA3_02_T _am(_BDMA3_2,REG_BASE_BDMA3, (2<<3))
#define BDMA3_03_T _am(_BDMA3_3,REG_BASE_BDMA3, (3<<3))

#define CDMA0_00_T _am(_CDMA0_0,REG_BASE_CDMA0, (0<<3))
#define CDMA0_01_T _am(_CDMA0_1,REG_BASE_CDMA0, (1<<3))
#define CDMA0_02_T _am(_CDMA0_2,REG_BASE_CDMA0, (2<<3))
#define CDMA0_03_T _am(_CDMA0_3,REG_BASE_CDMA0, (3<<3))

#define CDMA1_00_T _am(_CDMA1_0,REG_BASE_CDMA1, (0<<3))
#define CDMA1_01_T _am(_CDMA1_1,REG_BASE_CDMA1, (1<<3))
#define CDMA1_02_T _am(_CDMA1_2,REG_BASE_CDMA1, (2<<3))
#define CDMA1_03_T _am(_CDMA1_3,REG_BASE_CDMA1, (3<<3))

#define CDMA2_00_T _am(_CDMA2_0,REG_BASE_CDMA2, (0<<3))
#define CDMA2_01_T _am(_CDMA2_1,REG_BASE_CDMA2, (1<<3))
#define CDMA2_02_T _am(_CDMA2_2,REG_BASE_CDMA2, (2<<3))
#define CDMA2_03_T _am(_CDMA2_3,REG_BASE_CDMA2, (3<<3))

#define CDMA3_00_T _am(_CDMA3_0,REG_BASE_CDMA3, (0<<3))
#define CDMA3_01_T _am(_CDMA3_1,REG_BASE_CDMA3, (1<<3))
#define CDMA3_02_T _am(_CDMA3_2,REG_BASE_CDMA3, (2<<3))
#define CDMA3_03_T _am(_CDMA3_3,REG_BASE_CDMA3, (3<<3))

#define I2S_00_T _am(_I2S_0,REG_BASE_I2S, (0<<3))
#define I2S_01_T _am(_I2S_1,REG_BASE_I2S, (1<<3))
#define I2S_02_T _am(_I2S_2,REG_BASE_I2S, (2<<3))
#define I2S_03_T _am(_I2S_3,REG_BASE_I2S, (3<<3))
#define I2S_04_T _am(_I2S_4,REG_BASE_I2S, (4<<3))
#define I2S_05_T _am(_I2S_5,REG_BASE_I2S, (5<<3))
#define I2S_06_T _am(_I2S_6,REG_BASE_I2S, (6<<3))
#define I2S_07_T _am(_I2S_7,REG_BASE_I2S, (7<<3))
#define I2S_08_T _am(_I2S_8,REG_BASE_I2S, (8<<3))

#define IRQ_01_T _am(_IRQ_0,REG_BASE_IRQ_0, (0<<3))
#define IRQ_02_T _am(_IRQ_1,REG_BASE_IRQ, (1<<3))
#define IRQ_03_T _am(_IRQ_2,REG_BASE_IRQ, (2<<3))
#define IRQ_04_T _am(_IRQ_3,REG_BASE_IRQ, (3<<3))
#define IRQ_05_T _am(_IRQ_4,REG_BASE_IRQ, (4<<3))
#define IRQ_06_T _am(_IRQ_5,REG_BASE_IRQ, (5<<3))
#define IRQ_07_T _am(_IRQ_6,REG_BASE_IRQ, (6<<3))
#define IRQ_08_T _am(_IRQ_7,REG_BASE_IRQ, (7<<3))
#define IRQ_09_T _am(_IRQ_8,REG_BASE_IRQ, (8<<3))
#define IRQ_10_T _am(_IRQ_9,REG_BASE_IRQ, (9<<3))
#define IRQ_11_T _am(_IRQ_10,REG_BASE_IRQ, (10<<3))
#define IRQ_12_T _am(_IRQ_11,REG_BASE_IRQ, (11<<3))
#define IRQ_13_T _am(_IRQ_12,REG_BASE_IRQ, (12<<3))
#define IRQ_14_T _am(_IRQ_13,REG_BASE_IRQ, (13<<3))
#define IRQ_15_T _am(_IRQ_14,REG_BASE_IRQ, (14<<3))
#define IRQ_16_T _am(_IRQ_15,REG_BASE_IRQ, (15<<3))
#define IRQ_17_T _am(_IRQ_16,REG_BASE_IRQ, (16<<3))
#define IRQ_18_T _am(_IRQ_17,REG_BASE_IRQ, (17<<3))
#define IRQ_19_T _am(_IRQ_18,REG_BASE_IRQ, (18<<3))
#define IRQ_20_T _am(_IRQ_19,REG_BASE_IRQ, (19<<3))
#define IRQ_21_T _am(_IRQ_20,REG_BASE_IRQ, (20<<3))
#define IRQ_22_T _am(_IRQ_21,REG_BASE_IRQ, (21<<3))
#define IRQ_23_T _am(_IRQ_22,REG_BASE_IRQ, (22<<3))
#define IRQ_24_T _am(_IRQ_23,REG_BASE_IRQ, (23<<3))
#define IRQ_25_T _am(_IRQ_24,REG_BASE_IRQ, (24<<3))
#define IRQ_26_T _am(_IRQ_25,REG_BASE_IRQ, (25<<3))
#define IRQ_27_T _am(_IRQ_26,REG_BASE_IRQ, (26<<3))
#define IRQ_28_T _am(_IRQ_27,REG_BASE_IRQ, (27<<3))
#define IRQ_29_T _am(_IRQ_28,REG_BASE_IRQ, (28<<3))
#define IRQ_30_T _am(_IRQ_29,REG_BASE_IRQ, (29<<3))
#define IRQ_31_T _am(_IRQ_30,REG_BASE_IRQ, (30<<3))
#define IRQ_32_T _am(_IRQ_31,REG_BASE_IRQ, (31<<3))
#define IRQ_33_T _am(_IRQ_32,REG_BASE_IRQ, (32<<3))
#define IRQ_34_T _am(_IRQ_33,REG_BASE_IRQ, (33<<3))
#define IRQ_35_T _am(_IRQ_34,REG_BASE_IRQ, (34<<3))
#define IRQ_36_T _am(_IRQ_35,REG_BASE_IRQ, (35<<3))
#define IRQ_37_T _am(_IRQ_36,REG_BASE_IRQ, (36<<3))
#define IRQ_38_T _am(_IRQ_37,REG_BASE_IRQ, (37<<3))
#define IRQ_39_T _am(_IRQ_38,REG_BASE_IRQ, (38<<3))
#define IRQ_40_T _am(_IRQ_39,REG_BASE_IRQ, (39<<3))
#if EN675_SINGLE
_regs_ BF_4(UINT _rev0 : 28, UINT MCK_OFF : 1 ,UINT DCK_OFF : 1, UINT _rev1 : 2 ) _rege_ _WDT_REG3;
#define WDT_KILL_T _am(_WDT_REG3,REG_BASE_WDT, (3<<3))

_regs_ BF_2(UINT PLAT_UP : 16, UINT DOWN : 16 ) _rege_ _I2S_7a;
#define I2S_PLAT_IRQ_UP _bm(_I2S_7a,REG_BASE_I2S, (7<<3),PLAT_UP) // 1 Bit, 1'h0, RW
#define I2S_PLAT_IRQ_DOWN _bm(_I2S_7a,REG_BASE_I2S, (7<<3),DOWN) // 1 Bit, 1'h0, RW

_regs_ BF_3(UINT PLAT_UP : 16, UINT DOWN1 : 8, UINT DOWN2 : 8 ) _rege_ _I2S_7b;
#define I2S_PLAT_IRQ_DOWN1 _bm(_I2S_7b,REG_BASE_I2S, (7<<3),DOWN1) // 1 Bit, 1'h0, RW
#define I2S_PLAT_IRQ_DOWN2 _bm(_I2S_7b,REG_BASE_I2S, (7<<3),DOWN2) // 1 Bit, 1'h0, RW

#define I2S_PLAT_IRQ_T _am(_I2S_7,REG_BASE_I2S, (7<<3))
#endif

#endif
