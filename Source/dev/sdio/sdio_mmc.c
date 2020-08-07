#include "dev.h"

#if defined(__USE_SDIOEMMC__)

#include "sdio_host.h"
#include "sdio_card.h"
#include "sdio_mmc.h"
#include "enx_freertos.h"

#include <string.h> // memset

//static mmc_host mmc_host;
//static SDIO_MMC_CARD mmc_card;

#define ENX_SDIOMMC_DELAY vTaskDelay
#define DELAY_MS(ms) ENX_SDIOMMC_DELAY(ms)

#define ENX_SDIOMMC_IRQ_LOCK portENTER_CRITICAL
#define ENX_SDIOMMC_IRQ_UNLOCK portEXIT_CRITICAL

static void SdioMmcLog_hwflush_dcache_range(uint sadr, uint size)
{
	//printf("\nH/W Flush Addr  0x%08X->0x%08X, Byte %lubyte\n", sadr, sadr + size, size);
	//uint64_t s = BenchTimeStart();
	hwflush_dcache_range(sadr, size);
	//uint64_t us = BenchTimeStop(s);
	//printf("H/W Flush %luus\n", us);
}

#define ENX_SDIOMMC_FLUSH_DCACHE SdioMmcLog_hwflush_dcache_range

//-------------------------------------------------------------------------------------------------
// SDIO-MMC Card Reg

BYTE *SDIO_DATA_BASE = NULL;

static const unsigned int tran_exp[] = {
	10000,		100000,		1000000,	10000000,
	0,		0,		0,		0
};

static const unsigned char tran_mant[] = {
	0,	10,	12,	13,	15,	20,	25,	30,
	35,	40,	45,	50,	55,	60,	70,	80,
};

static const unsigned int taac_exp[] = {
	1,	10,	100,	1000,	10000,	100000,	1000000, 10000000,
};

static const unsigned int taac_mant[] = {
	0,	10,	12,	13,	15,	20,	25,	30,
	35,	40,	45,	50,	55,	60,	70,	80,
};

#define UNSTUFF_BITS(resp,start,size)					\
	({								\
		const int __size = size;				\
		const u32 __mask = (__size < 32 ? 1 << __size : 0) - 1;	\
		const int __off = 3 - ((start) / 32);			\
		const int __shft = (start) & 31;			\
		u32 __res;						\
									\
		__res = resp[__off] >> __shft;				\
		if (__size + __shft > 32)				\
			__res |= resp[__off-1] << ((32 - __shft) % 32);	\
		__res & __mask;						\
	})

#if 0
//-------------------------------------------------------------------------------------------------
// SDIO-MMC Card Reg
void SdioPrintOCR(MMC_OCR *ocr)
{
	ENX_LOG_START(DBG_SDIO_CD_CMD);

	printf("===================================================\n");
	hexDump("OCR", (BYTE *)ocr, sizeof(MMC_OCR));
	printf("===================================================\n");
	printf("ocr->busy     [   31] : 0x%08X(%u)\n", ocr->busy, ocr->busy);
	printf("ocr->ACCMODE  [30:29] : 0x%08X(%u)\n", ocr->ACCMODE, ocr->ACCMODE);
	printf("ocr->_res1    [28:24] : 0x%08X(%u)\n", ocr->_res1, ocr->_res1);
	printf("ocr->VDD27_36 [23:15] : 0x%08X(%u)\n", ocr->VDD27_36, ocr->VDD27_36);
	printf("ocr->VDD20_26 [14: 8] : 0x%08X(%u)\n", ocr->VDD20_26, ocr->VDD20_26);
	printf("ocr->VDD17_195[    7] : 0x%08X(%u)\n", ocr->VDD17_195, ocr->VDD17_195);
	printf("ocr->_res2    [ 6: 0] : 0x%08X(%u)\n", ocr->_res2, ocr->_res2);
	printf("===================================================\n");

	ENX_LOG_END(DBG_SDIO_CD_CMD);
}

void SdioPrintCID(SDIO_MMC_CARD *card)
{
	MMC_CID *cid = &card->cid;

	ENX_LOG_START(DBG_SDIO_CD_CMD);

	printf("===================================================\n");
	hexDump("CID", (BYTE *)card->raw_cid, sizeof(card->raw_cid));
	printf("===================================================\n");
#if 0
	printf("cid->manfid     [127:120] : 0x%08X(%u)\n", cid->manfid, cid->manfid);
	printf("cid->_res1      [119:104] : 0x%08X(%u)\n", cid->oemid, cid->oemid);
	printf("cid->prod_name0 [103: 96] : 0x%08X(%u) : %c\n", cid->prod_name0, cid->prod_name0, cid->prod_name0);
	printf("cid->prod_name1 [ 95: 88] : 0x%08X(%u) : %c\n", cid->prod_name1, cid->prod_name1, cid->prod_name1);
	printf("cid->prod_name2 [ 87: 80] : 0x%08X(%u) : %c\n", cid->prod_name2, cid->prod_name2, cid->prod_name2);
	printf("cid->prod_name3 [ 79: 72] : 0x%08X(%u) : %c\n", cid->prod_name3, cid->prod_name3, cid->prod_name3);
	printf("cid->prod_name4 [ 71: 64] : 0x%08X(%u) : %c\n", cid->prod_name4, cid->prod_name4, cid->prod_name4);
	printf("cid->prod_name5 [ 63: 56] : 0x%08X(%u) : %c\n", cid->prod_name5, cid->prod_name5, cid->prod_name5);
	printf("cid->prv        [ 55: 48] : 0x%08X(%u)\n", cid->prv, cid->prv);
	printf("cid->serial     [ 47: 16] : 0x%08X(%u)\n", cid->serial0 << 16 | cid->serial1, cid->serial0 << 16 | cid->serial1);
	printf("cid->month      [ 15: 12] : 0x%08X(%u)\n", cid->month, cid->month);
	printf("cid->year       [ 11:  8] : 0x%08X(%u)\n", cid->year, cid->year);
	printf("cid->crc        [  7:  1] : 0x%08X(%u)\n", cid->crc, cid->crc);
	printf("cid->_res2      [      0] : 0x%08X(%u)\n", cid->_res2, cid->_res2);
#endif
	printf("===================================================\n");

	ENX_LOG_END(DBG_SDIO_CD_CMD);
}

void SdioPrintCSD(SDIO_MMC_CARD *card)
{
	MMC_CSD *csd = &card->csd;

	ENX_LOG_START(DBG_SDIO_CD_CMD);

	printf("===================================================\n");
	hexDump("CSD", (BYTE *)card->raw_csd, sizeof(card->raw_csd));
	printf("===================================================\n");
#if 0
	printf("csd->structure          [127:126] : 0x%08X(%u)\n", csd->structure, csd->structure);
	printf("csd->mmca_vsn           [125:122] : 0x%08X(%u)\n", csd->mmca_vsn, csd->mmca_vsn);
	printf("csd->_res1              [121:119] : 0x%08X(%u)\n", csd->_res1, csd->_res1);
	printf("csd->taac_mant          [118:115] : 0x%08X(%u)\n", csd->taac_mant, csd->taac_mant);
	printf("csd->taac_exp           [114:112] : 0x%08X(%u)\n", csd->taac_exp, csd->taac_exp);
	printf("csd->NSAC               [111:104] : 0x%08X(%u)\n", csd->NSAC, csd->NSAC);
	printf("csd->_res12             [103:103] : 0x%08X(%u)\n", csd->_res12, csd->_res12);
	printf("csd->tran_mant          [102: 99] : 0x%08X(%u)\n", csd->tran_mant, csd->tran_mant);
	printf("csd->tran_exp           [ 98: 96] : 0x%08X(%u)\n", csd->tran_exp, csd->tran_exp);
	printf("csd->CCC                [ 95: 84] : 0x%08X(%u)\n", csd->CCC, csd->CCC);
	printf("csd->READ_BL_LEN        [ 83: 80] : 0x%08X(%u)\n", csd->READ_BL_LEN, csd->READ_BL_LEN);
	printf("csd->READ_BL_PARTIAL    [ 79: 79] : 0x%08X(%u)\n", csd->READ_BL_PARTIAL, csd->READ_BL_PARTIAL);
	printf("csd->WRITE_BLK_MISALIGN [ 78: 78] : 0x%08X(%u)\n", csd->WRITE_BLK_MISALIGN, csd->WRITE_BLK_MISALIGN);
	printf("csd->READ_BLK_MISALIGN  [ 77: 77] : 0x%08X(%u)\n", csd->READ_BLK_MISALIGN, csd->READ_BLK_MISALIGN);
	printf("csd->DSR_IMP            [ 76: 76] : 0x%08X(%u)\n", csd->DSR_IMP, csd->DSR_IMP);
	printf("csd->_res2              [ 75: 74] : 0x%08X(%u)\n", csd->_res2, csd->_res2);
	printf("csd->C_SIZE             [ 73: 62] : 0x%08X(%u)\n", csd->C_SIZE0 << 2 | csd->C_SIZE1, csd->C_SIZE0 << 2 | csd->C_SIZE1);
	printf("csd->VDD_R_CURR_MIN     [ 61: 59] : 0x%08X(%u)\n", csd->VDD_R_CURR_MIN, csd->VDD_R_CURR_MIN);
	printf("csd->VDD_R_CURR_MAX     [ 58: 56] : 0x%08X(%u)\n", csd->VDD_R_CURR_MAX, csd->VDD_R_CURR_MAX);
	printf("csd->VDD_W_CURR_MIN     [ 55: 53] : 0x%08X(%u)\n", csd->VDD_W_CURR_MIN, csd->VDD_W_CURR_MIN);
	printf("csd->VDD_W_CURR_MAX     [ 52: 50] : 0x%08X(%u)\n", csd->VDD_W_CURR_MAX, csd->VDD_W_CURR_MAX);
	printf("csd->C_SIZE_MULT        [ 49: 47] : 0x%08X(%u)\n", csd->C_SIZE_MULT, csd->C_SIZE_MULT);
	printf("csd->ERASE_GRP_SIZE     [ 46: 42] : 0x%08X(%u)\n", csd->ERASE_GRP_SIZE, csd->ERASE_GRP_SIZE);
	printf("csd->ERASE_GRP_MULT     [ 41: 37] : 0x%08X(%u)\n", csd->ERASE_GRP_MULT, csd->ERASE_GRP_MULT);
	printf("csd->WP_GRP_SIZE        [ 36: 32] : 0x%08X(%u)\n", csd->WP_GRP_SIZE, csd->WP_GRP_SIZE);
	printf("csd->WP_GRP_ENABLE      [ 31: 31] : 0x%08X(%u)\n", csd->WP_GRP_ENABLE, csd->WP_GRP_ENABLE);
	printf("csd->DEFAULT_ECC        [ 30: 29] : 0x%08X(%u)\n", csd->DEFAULT_ECC, csd->DEFAULT_ECC);
	printf("csd->R2W_FACTOR         [ 28: 26] : 0x%08X(%u)\n", csd->R2W_FACTOR, csd->R2W_FACTOR);
	printf("csd->WRITE_BL_LEN       [ 25: 22] : 0x%08X(%u)\n", csd->WRITE_BL_LEN, csd->WRITE_BL_LEN);
	printf("csd->WRITE_BL_PARTIAL   [ 21: 21] : 0x%08X(%u)\n", csd->WRITE_BL_PARTIAL, csd->WRITE_BL_PARTIAL);
	printf("csd->_res3              [ 20: 17] : 0x%08X(%u)\n", csd->_res3, csd->_res3);
	printf("csd->CONTENT_PROT_APP   [ 16: 16] : 0x%08X(%u)\n", csd->CONTENT_PROT_APP, csd->CONTENT_PROT_APP);
	printf("csd->FILE_FORMAT_GRP    [ 15: 15] : 0x%08X(%u)\n", csd->FILE_FORMAT_GRP, csd->FILE_FORMAT_GRP);
	printf("csd->COPY               [ 14: 14] : 0x%08X(%u)\n", csd->COPY, csd->COPY);
	printf("csd->PERM_WRITE_PROTECT [ 13: 13] : 0x%08X(%u)\n", csd->PERM_WRITE_PROTECT, csd->PERM_WRITE_PROTECT);
	printf("csd->TMP_WRITE_PROTECT  [ 12: 12] : 0x%08X(%u)\n", csd->TMP_WRITE_PROTECT, csd->TMP_WRITE_PROTECT);
	printf("csd->FILE_FORMAT        [ 11: 10] : 0x%08X(%u)\n", csd->FILE_FORMAT, csd->FILE_FORMAT);
	printf("csd->ECC                [  9:  8] : 0x%08X(%u)\n", csd->ECC, csd->ECC);
	printf("csd->CRC                [  7:  1] : 0x%08X(%u)\n", csd->CRC, csd->CRC);
	printf("csd->_res4              [  0:  0] : 0x%08X(%u)\n", csd->_res4, csd->_res4);
	printf("===================================================\n");
	printf("csd_taac_ns                       : 0x%08X(%u)\n", card->csd_taac_ns, card->csd_taac_ns);
	printf("csd_taac_clks                     : 0x%08X(%u)\n", card->csd_taac_clks, card->csd_taac_clks);
	printf("csd_max_dtr                       : 0x%08X(%u)\n", card->csd_max_dtr, card->csd_max_dtr);
	printf("csd_capacity                      : 0x%08X(%u)\n", card->csd_capacity, card->csd_capacity);
	printf("csd_erase_size                    : 0x%08X(%u)\n", card->csd_erase_size, card->csd_erase_size);
#endif
	printf("===================================================\n");

	ENX_LOG_END(DBG_SDIO_CD_CMD);
}
#endif

//-------------------------------------------------------------------------------------------------
// SDIO-MMC Irq & Cmd
static ENX_OKFAIL SdioMmcCmd(UINT nCH, BYTE Cmd, UINT Arg, UINT *nResp, eCmdRespType cmdType)
{
	return SdioCmd(nCH, Cmd, Arg, nResp, cmdType);
}

static ENX_OKFAIL SdioMmcDataIO(UINT nCH, eSDIO_DIO_TYPE iotype, ULONG MemDst, UINT BlkAdr, UINT BlkCnt)
{
	return SdioDataIO(nCH, iotype, MemDst, BlkAdr, BlkCnt);
}

static UINT SdioMmcRegDataRead(UINT nCH, UINT nCmd, UINT nArg, UINT *nResp, eCmdRespType cmdType, void *pSdioReg, UINT nSize)
{
	UINT nRes, nTemp;
	UINT *getData = (UINT *)SDIO_DATA_BASE;

	nTemp = SdioGetDataBlockByte(nCH);
	SdioSetDataBlockByte(nCH, nSize);		// Data Block Byte를 설정
	SdioSetDataCmd(nCH, SDIO_DIO_SINGLE_READ, nCmd);	// Data Read command를 설정

	ENX_SDIOMMC_IRQ_LOCK();
	ENX_SDIOMMC_FLUSH_DCACHE((ULONG)getData, nSize);
	nRes = SdioMmcDataIO(nCH, SDIO_DIO_SINGLE_READ, (ULONG)getData, nArg, 1);
	ENX_SDIOMMC_FLUSH_DCACHE((ULONG)getData, nSize);
	memcpy(pSdioReg, getData, nSize);
	ENX_SDIOMMC_IRQ_UNLOCK();

	SdioSetDataBlockByte(nCH, nTemp);	// Data Block Byte를 원상복귀
	SdioSetDataCmd(nCH, SDIO_DIO_SINGLE_READ, MMC_READ_SINGLE_BLOCK); // Data Read command를 17으로 설정(기본 Read 명령으로 설정)

	SdioGetResp(nCH, nResp, cmdType);
	ENX_DEBUGF(DBG_SDIO_MMC_CMD, "[%2d] res(%c) RESP0(0x%08X)\n", nCmd, nRes == ENX_OK ? 'O' : 'X', nResp[0]);
	if (cmdType == ecrtR2) {
		ENX_DEBUGF(DBG_SDIO_MMC_CMD, "[%2d] res(%c) RESP1(0x%08X)\n", nCmd, nRes == ENX_OK ? 'O' : 'X', nResp[1]);
		ENX_DEBUGF(DBG_SDIO_MMC_CMD, "[%2d] res(%c) RESP2(0x%08X)\n", nCmd, nRes == ENX_OK ? 'O' : 'X', nResp[2]);
		ENX_DEBUGF(DBG_SDIO_MMC_CMD, "[%2d] res(%c) RESP3(0x%08X)\n", nCmd, nRes == ENX_OK ? 'O' : 'X', nResp[3]);
	}

	return nRes;
}

//-------------------------------------------------------------------------------------------------
// SDIO-MMC Support
#if 0
static int Sdio_mmc_can_ext_csd(SDIO_MMC_CARD *card)
{
	return (card && card->csd.mmca_vsn > 3);
}
#endif
#if 0
static void Sdio_mmc_select_card_type(SDIO_MMC_CARD *card)
{
	SDIO_MMC_HOST *host = card->host;
	u8 card_type = card->extcsd.CARD_TYPE;
	u32 caps = host->caps, caps2 = host->caps2;
	unsigned int hs_max_dtr = 0, hs200_max_dtr = 0;
	unsigned int avail_type = 0;

	if (caps & MMC_CAP_MMC_HIGHSPEED &&
	    card_type & EXT_CSD_CARD_TYPE_HS_26) {
		hs_max_dtr = MMC_HIGH_26_MAX_DTR;
		avail_type |= EXT_CSD_CARD_TYPE_HS_26;
	}

	if (caps & MMC_CAP_MMC_HIGHSPEED &&
	    card_type & EXT_CSD_CARD_TYPE_HS_52) {
		hs_max_dtr = MMC_HIGH_52_MAX_DTR;
		avail_type |= EXT_CSD_CARD_TYPE_HS_52;
	}

	if (caps & (MMC_CAP_1_8V_DDR | MMC_CAP_3_3V_DDR) &&
	    card_type & EXT_CSD_CARD_TYPE_DDR_1_8V) {
		hs_max_dtr = MMC_HIGH_DDR_MAX_DTR;
		avail_type |= EXT_CSD_CARD_TYPE_DDR_1_8V;
	}

	if (caps & MMC_CAP_1_2V_DDR &&
	    card_type & EXT_CSD_CARD_TYPE_DDR_1_2V) {
		hs_max_dtr = MMC_HIGH_DDR_MAX_DTR;
		avail_type |= EXT_CSD_CARD_TYPE_DDR_1_2V;
	}

	if (caps2 & MMC_CAP2_HS200_1_8V_SDR &&
	    card_type & EXT_CSD_CARD_TYPE_HS200_1_8V) {
		hs200_max_dtr = MMC_HS200_MAX_DTR;
		avail_type |= EXT_CSD_CARD_TYPE_HS200_1_8V;
	}

	if (caps2 & MMC_CAP2_HS200_1_2V_SDR &&
	    card_type & EXT_CSD_CARD_TYPE_HS200_1_2V) {
		hs200_max_dtr = MMC_HS200_MAX_DTR;
		avail_type |= EXT_CSD_CARD_TYPE_HS200_1_2V;
	}

	if (caps2 & MMC_CAP2_HS400_1_8V &&
	    card_type & EXT_CSD_CARD_TYPE_HS400_1_8V) {
		hs200_max_dtr = MMC_HS200_MAX_DTR;
		avail_type |= EXT_CSD_CARD_TYPE_HS400_1_8V;
	}

	if (caps2 & MMC_CAP2_HS400_1_2V &&
	    card_type & EXT_CSD_CARD_TYPE_HS400_1_2V) {
		hs200_max_dtr = MMC_HS200_MAX_DTR;
		avail_type |= EXT_CSD_CARD_TYPE_HS400_1_2V;
	}

	if ((caps2 & MMC_CAP2_HS400_ES) &&
	    card->ext_csd.strobe_support &&
	    (avail_type & EXT_CSD_CARD_TYPE_HS400))
		avail_type |= EXT_CSD_CARD_TYPE_HS400ES;

	card->ext_csd.hs_max_dtr = hs_max_dtr;
	card->ext_csd.hs200_max_dtr = hs200_max_dtr;
	card->mmc_avail_type = avail_type;
}
#endif
#if 0
static inline int Sdio_mmc_boot_partition_access(SDIO_MMC_HOST *host)
{
	return !(host->caps2 & MMC_CAP2_BOOTPART_NOACC);
}
#endif
//-------------------------------------------------------------------------------------------------
// SDIO-MMC Command
#if 0
static ENX_OKFAIL Sdio_mmc_go_idle(SDIO_MMC_CARD *card)
{
	ENX_LOG_START(DBG_SDIO_CD_CMD);

	SdioMmcCmd(card->host->nCH, MMC_GO_IDLE_STATE, 0x0, NULL, ecrtR1);
	DELAY_MS(1);

	ENX_LOG_END(DBG_SDIO_CD_CMD);
	return ENX_OK;
}

static ENX_OKFAIL Sdio_mmc_send_op_cond(SDIO_MMC_CARD *card, u32 ocr)
{
	ENX_OKFAIL nRes = ENX_FAIL;
	int i;
	UINT *pResp;

	ENX_LOG_START(DBG_SDIO_CD_CMD);

	pResp = (UINT *)&card->ocr;

	for (i = 100; i; i--) {
		nRes = SdioMmcCmd(card->host->nCH, MMC_SEND_OP_COND, ocr, pResp, ecrtR3);
		if (nRes == ENX_FAIL) {
			break;
		}

		if (ocr == 0) {
			break;
		}

		if (*pResp & MMC_CARD_BUSY) {
			break;
		}

		nRes = ENX_FAIL;

		DELAY_MS(10);
	}

	ENX_LOG_END(DBG_SDIO_CD_CMD);
	return nRes;
}

static ENX_OKFAIL Sdio_mmc_decode_cid(SDIO_MMC_CARD *card)
{
	u32 *resp = card->raw_cid;

	/*
	 * The selection of the format here is based upon published
	 * specs from sandisk and from what people have reported.
	 */
	switch (card->csd.mmca_vsn) {
	case 0: /* MMC v1.0 - v1.2 */
	case 1: /* MMC v1.4 */
		card->cid.manfid	= UNSTUFF_BITS(resp, 104, 24);
		card->cid.prod_name[0]	= UNSTUFF_BITS(resp, 96, 8);
		card->cid.prod_name[1]	= UNSTUFF_BITS(resp, 88, 8);
		card->cid.prod_name[2]	= UNSTUFF_BITS(resp, 80, 8);
		card->cid.prod_name[3]	= UNSTUFF_BITS(resp, 72, 8);
		card->cid.prod_name[4]	= UNSTUFF_BITS(resp, 64, 8);
		card->cid.prod_name[5]	= UNSTUFF_BITS(resp, 56, 8);
		card->cid.prod_name[6]	= UNSTUFF_BITS(resp, 48, 8);
		card->cid.hwrev		= UNSTUFF_BITS(resp, 44, 4);
		card->cid.fwrev		= UNSTUFF_BITS(resp, 40, 4);
		card->cid.serial	= UNSTUFF_BITS(resp, 16, 24);
		card->cid.month		= UNSTUFF_BITS(resp, 12, 4);
		card->cid.year		= UNSTUFF_BITS(resp, 8, 4) + 1997;
		break;

	case 2: /* MMC v2.0 - v2.2 */
	case 3: /* MMC v3.1 - v3.3 */
	case 4: /* MMC v4 */
		card->cid.manfid	= UNSTUFF_BITS(resp, 120, 8);
		card->cid.oemid		= UNSTUFF_BITS(resp, 104, 16);
		card->cid.prod_name[0]	= UNSTUFF_BITS(resp, 96, 8);
		card->cid.prod_name[1]	= UNSTUFF_BITS(resp, 88, 8);
		card->cid.prod_name[2]	= UNSTUFF_BITS(resp, 80, 8);
		card->cid.prod_name[3]	= UNSTUFF_BITS(resp, 72, 8);
		card->cid.prod_name[4]	= UNSTUFF_BITS(resp, 64, 8);
		card->cid.prod_name[5]	= UNSTUFF_BITS(resp, 56, 8);
		card->cid.prv		= UNSTUFF_BITS(resp, 48, 8);
		card->cid.serial	= UNSTUFF_BITS(resp, 16, 32);
		card->cid.month		= UNSTUFF_BITS(resp, 12, 4);
		card->cid.year		= UNSTUFF_BITS(resp, 8, 4) + 1997;
		break;

	default:
		ENX_DEBUGF(DBG_SDIO_MMC_ERR, "card has unknown MMCA version %d\n", card->csd.mmca_vsn);
		return ENX_FAIL;
	}

	return ENX_OK;
}

static ENX_OKFAIL Sdio_mmc_send_cid(SDIO_MMC_CARD *card)
{
	ENX_OKFAIL nRes = ENX_FAIL;
	UINT *pResp = card->raw_cid;

	ENX_LOG_START(DBG_SDIO_CD_CMD);

	nRes = SdioMmcCmd(card->host->nCH, MMC_ALL_SEND_CID, 0, pResp, ecrtR2);

	ENX_LOG_END(DBG_SDIO_CD_CMD);
	return nRes;
}

static ENX_OKFAIL Sdio_mmc_set_relative_addr(SDIO_MMC_CARD *card)
{
	ENX_OKFAIL nRes = ENX_FAIL;
	UINT nResp;

	ENX_LOG_START(DBG_SDIO_CD_CMD);

	nRes = SdioMmcCmd(card->host->nCH, MMC_SET_RELATIVE_ADDR, card->rca << 16, &nResp, ecrtR1);

	ENX_LOG_END(DBG_SDIO_CD_CMD);
	return nRes;
}

static ENX_OKFAIL Sdio_mmc_decode_csd(SDIO_MMC_CARD *card)
{
	ENX_OKFAIL nRes = ENX_FAIL;
	MMC_CSD *csd = &card->csd;
	unsigned int e, m, a, b;
	u32 *resp = card->raw_csd;

	/*
	 * We only understand CSD structure v1.1 and v1.2.
	 * v1.2 has extra information in bits 15, 11 and 10.
	 * We also support eMMC v4.4 & v4.41.
	 */
	csd->structure = UNSTUFF_BITS(resp, 126, 2);
	if (csd->structure == 0) {
		ENX_DEBUGF(DBG_SDIO_MMC_ERR, "unrecognised CSD structure version %d\n", csd->structure);
		nRes = ENX_FAIL;
		goto done;
	}

	csd->mmca_vsn	 = UNSTUFF_BITS(resp, 122, 4);
	m = UNSTUFF_BITS(resp, 115, 4);
	e = UNSTUFF_BITS(resp, 112, 3);
	csd->taac_ns	 = (taac_exp[e] * taac_mant[m] + 9) / 10;
	csd->taac_clks	 = UNSTUFF_BITS(resp, 104, 8) * 100;

	m = UNSTUFF_BITS(resp, 99, 4);
	e = UNSTUFF_BITS(resp, 96, 3);
	csd->max_dtr	  = tran_exp[e] * tran_mant[m];
	csd->cmdclass	  = UNSTUFF_BITS(resp, 84, 12);

	e = UNSTUFF_BITS(resp, 47, 3);
	m = UNSTUFF_BITS(resp, 62, 12);
	csd->capacity	  = (1 + m) << (e + 2);

	csd->read_blkbits = UNSTUFF_BITS(resp, 80, 4);
	csd->read_partial = UNSTUFF_BITS(resp, 79, 1);
	csd->write_misalign = UNSTUFF_BITS(resp, 78, 1);
	csd->read_misalign = UNSTUFF_BITS(resp, 77, 1);
	csd->dsr_imp = UNSTUFF_BITS(resp, 76, 1);
	csd->r2w_factor = UNSTUFF_BITS(resp, 26, 3);
	csd->write_blkbits = UNSTUFF_BITS(resp, 22, 4);
	csd->write_partial = UNSTUFF_BITS(resp, 21, 1);

	if (csd->write_blkbits >= 9) {
		a = UNSTUFF_BITS(resp, 42, 5);
		b = UNSTUFF_BITS(resp, 37, 5);
		csd->erase_size = (a + 1) * (b + 1);
		csd->erase_size <<= csd->write_blkbits - 9;
	}

done:
	ENX_LOG_END(DBG_SDIO_CD_CMD);
	return nRes;
}

static ENX_OKFAIL Sdio_mmc_send_csd(SDIO_MMC_CARD *card)
{
	ENX_OKFAIL nRes = ENX_FAIL;
	UINT *nResp = card->raw_csd;

	ENX_LOG_START(DBG_SDIO_CD_CMD);

	nRes = SdioMmcCmd(card->host->nCH, MMC_SEND_CSD, card->rca << 16, nResp, ecrtR2);

	ENX_LOG_END(DBG_SDIO_CD_CMD);
	return nRes;
}

static ENX_OKFAIL Sdio_mmc_select_card(SDIO_MMC_CARD *card, int cardsw)
{
	ENX_OKFAIL nRes = ENX_FAIL;
	UINT nResp;

	ENX_LOG_START(DBG_SDIO_CD_CMD);

	if (cardsw) {
		nRes = SdioMmcCmd(card->host->nCH, MMC_SELECT_CARD, card->rca << 16, &nResp, ecrtR1);
	} else {
		nRes = SdioMmcCmd(card->host->nCH, MMC_SELECT_CARD, 0, NULL, ecrtR1);
	}

	ENX_LOG_END(DBG_SDIO_CD_CMD);
	return nRes;
}

static ENX_OKFAIL Sdio_mmc_decode_ext_csd(SDIO_MMC_CARD *card)
{
	ENX_OKFAIL nRes = ENX_FAIL;
	MMC_CSD *csd = &card->csd;
	u8 *ext_csd = card->raw_ext_csd;
	ENX_TF broken_hpi = ENX_FALSE;
//	int err = 0, idx;
//	unsigned int part_size;
//	struct device_node *np;


	/* Version is coded in the CSD_STRUCTURE byte in the EXT_CSD register */
	card->ext_csd.raw_ext_csd_structure = ext_csd[EXT_CSD_STRUCTURE];
	if (card->csd.structure == 3) {
		if (card->ext_csd.raw_ext_csd_structure > 2) {
			ENX_DEBUGF(DBG_SDIO_MMC_ERR, "unrecognised EXT_CSD structure version %d\n", card->ext_csd.raw_ext_csd_structure);
			nRes = ENX_FAIL;
			goto done;
		}
	}

	card->ext_csd.rev = ext_csd[EXT_CSD_REV];

//	mmc_fixup_device(card, mmc_ext_csd_fixups);

	card->ext_csd.raw_sectors[0] = ext_csd[EXT_CSD_SEC_CNT + 0];
	card->ext_csd.raw_sectors[1] = ext_csd[EXT_CSD_SEC_CNT + 1];
	card->ext_csd.raw_sectors[2] = ext_csd[EXT_CSD_SEC_CNT + 2];
	card->ext_csd.raw_sectors[3] = ext_csd[EXT_CSD_SEC_CNT + 3];
	if (card->ext_csd.rev >= 2) {
		card->ext_csd.sectors =
			ext_csd[EXT_CSD_SEC_CNT + 0] << 0 |
			ext_csd[EXT_CSD_SEC_CNT + 1] << 8 |
			ext_csd[EXT_CSD_SEC_CNT + 2] << 16 |
			ext_csd[EXT_CSD_SEC_CNT + 3] << 24;

		/* Cards with density > 2GiB are sector addressed */
		if (card->ext_csd.sectors > (2u * 1024 * 1024 * 1024) / 512)
			mmc_card_set_blockaddr(card);
	}

	card->ext_csd.strobe_support = ext_csd[EXT_CSD_STROBE_SUPPORT];
	card->ext_csd.raw_card_type = ext_csd[EXT_CSD_CARD_TYPE];
	mmc_select_card_type(card);

	card->ext_csd.raw_s_a_timeout = ext_csd[EXT_CSD_S_A_TIMEOUT];
	card->ext_csd.raw_erase_timeout_mult =
		ext_csd[EXT_CSD_ERASE_TIMEOUT_MULT];
	card->ext_csd.raw_hc_erase_grp_size =
		ext_csd[EXT_CSD_HC_ERASE_GRP_SIZE];
	if (card->ext_csd.rev >= 3) {
		u8 sa_shift = ext_csd[EXT_CSD_S_A_TIMEOUT];
		card->ext_csd.part_config = ext_csd[EXT_CSD_PART_CONFIG];

		/* EXT_CSD value is in units of 10ms, but we store in ms */
		card->ext_csd.part_time = 10 * ext_csd[EXT_CSD_PART_SWITCH_TIME];
		/* Some eMMC set the value too low so set a minimum */
		if (card->ext_csd.part_time &&
		    card->ext_csd.part_time < MMC_MIN_PART_SWITCH_TIME)
			card->ext_csd.part_time = MMC_MIN_PART_SWITCH_TIME;

		/* Sleep / awake timeout in 100ns units */
		if (sa_shift > 0 && sa_shift <= 0x17)
			card->ext_csd.sa_timeout =
					1 << ext_csd[EXT_CSD_S_A_TIMEOUT];
		card->ext_csd.erase_group_def =
			ext_csd[EXT_CSD_ERASE_GROUP_DEF];
		card->ext_csd.hc_erase_timeout = 300 *
			ext_csd[EXT_CSD_ERASE_TIMEOUT_MULT];
		card->ext_csd.hc_erase_size =
			ext_csd[EXT_CSD_HC_ERASE_GRP_SIZE] << 10;

		card->ext_csd.rel_sectors = ext_csd[EXT_CSD_REL_WR_SEC_C];

#if 0
		/*
		 * There are two boot regions of equal size, defined in
		 * multiples of 128K.
		 */
		if (ext_csd[EXT_CSD_BOOT_MULT] && mmc_boot_partition_access(card->host)) {
			for (idx = 0; idx < MMC_NUM_BOOT_PARTITION; idx++) {
				part_size = ext_csd[EXT_CSD_BOOT_MULT] << 17;
				mmc_part_add(card, part_size,
					EXT_CSD_PART_CONFIG_ACC_BOOT0 + idx,
					"boot%d", idx, true,
					MMC_BLK_DATA_AREA_BOOT);
			}
		}
#endif
	}

	card->ext_csd.raw_hc_erase_gap_size =
		ext_csd[EXT_CSD_HC_WP_GRP_SIZE];
	card->ext_csd.raw_sec_trim_mult =
		ext_csd[EXT_CSD_SEC_TRIM_MULT];
	card->ext_csd.raw_sec_erase_mult =
		ext_csd[EXT_CSD_SEC_ERASE_MULT];
	card->ext_csd.raw_sec_feature_support =
		ext_csd[EXT_CSD_SEC_FEATURE_SUPPORT];
	card->ext_csd.raw_trim_mult =
		ext_csd[EXT_CSD_TRIM_MULT];
	card->ext_csd.raw_partition_support = ext_csd[EXT_CSD_PARTITION_SUPPORT];
	card->ext_csd.raw_driver_strength = ext_csd[EXT_CSD_DRIVER_STRENGTH];
	if (card->ext_csd.rev >= 4) {
		if (ext_csd[EXT_CSD_PARTITION_SETTING_COMPLETED] &
		    EXT_CSD_PART_SETTING_COMPLETED)
			card->ext_csd.partition_setting_completed = 1;
		else
			card->ext_csd.partition_setting_completed = 0;

		mmc_manage_enhanced_area(card, ext_csd);

		mmc_manage_gp_partitions(card, ext_csd);

		card->ext_csd.sec_trim_mult =
			ext_csd[EXT_CSD_SEC_TRIM_MULT];
		card->ext_csd.sec_erase_mult =
			ext_csd[EXT_CSD_SEC_ERASE_MULT];
		card->ext_csd.sec_feature_support =
			ext_csd[EXT_CSD_SEC_FEATURE_SUPPORT];
		card->ext_csd.trim_timeout = 300 *
			ext_csd[EXT_CSD_TRIM_MULT];

		/*
		 * Note that the call to mmc_part_add above defaults to read
		 * only. If this default assumption is changed, the call must
		 * take into account the value of boot_locked below.
		 */
		card->ext_csd.boot_ro_lock = ext_csd[EXT_CSD_BOOT_WP];
		card->ext_csd.boot_ro_lockable = ENX_TRUE;

		/* Save power class values */
		card->ext_csd.raw_pwr_cl_52_195 =
			ext_csd[EXT_CSD_PWR_CL_52_195];
		card->ext_csd.raw_pwr_cl_26_195 =
			ext_csd[EXT_CSD_PWR_CL_26_195];
		card->ext_csd.raw_pwr_cl_52_360 =
			ext_csd[EXT_CSD_PWR_CL_52_360];
		card->ext_csd.raw_pwr_cl_26_360 =
			ext_csd[EXT_CSD_PWR_CL_26_360];
		card->ext_csd.raw_pwr_cl_200_195 =
			ext_csd[EXT_CSD_PWR_CL_200_195];
		card->ext_csd.raw_pwr_cl_200_360 =
			ext_csd[EXT_CSD_PWR_CL_200_360];
		card->ext_csd.raw_pwr_cl_ddr_52_195 =
			ext_csd[EXT_CSD_PWR_CL_DDR_52_195];
		card->ext_csd.raw_pwr_cl_ddr_52_360 =
			ext_csd[EXT_CSD_PWR_CL_DDR_52_360];
		card->ext_csd.raw_pwr_cl_ddr_200_360 =
			ext_csd[EXT_CSD_PWR_CL_DDR_200_360];
	}

	if (card->ext_csd.rev >= 5) {
		/* Adjust production date as per JEDEC JESD84-B451 */
		if (card->cid.year < 2010)
			card->cid.year += 16;

		/* check whether the eMMC card supports BKOPS */
		if (ext_csd[EXT_CSD_BKOPS_SUPPORT] & 0x1) {
			card->ext_csd.bkops = 1;
			card->ext_csd.man_bkops_en =
					(ext_csd[EXT_CSD_BKOPS_EN] &
						EXT_CSD_MANUAL_BKOPS_MASK);
			card->ext_csd.raw_bkops_status =
				ext_csd[EXT_CSD_BKOPS_STATUS];
			if (card->ext_csd.man_bkops_en)
				pr_debug("%s: MAN_BKOPS_EN bit is set\n",
					mmc_hostname(card->host));
			card->ext_csd.auto_bkops_en =
					(ext_csd[EXT_CSD_BKOPS_EN] &
						EXT_CSD_AUTO_BKOPS_MASK);
			if (card->ext_csd.auto_bkops_en)
				pr_debug("%s: AUTO_BKOPS_EN bit is set\n",
					mmc_hostname(card->host));
		}

		/* check whether the eMMC card supports HPI */
		if (!mmc_card_broken_hpi(card) &&
		    !broken_hpi && (ext_csd[EXT_CSD_HPI_FEATURES] & 0x1)) {
			card->ext_csd.hpi = 1;
			if (ext_csd[EXT_CSD_HPI_FEATURES] & 0x2)
				card->ext_csd.hpi_cmd =	MMC_STOP_TRANSMISSION;
			else
				card->ext_csd.hpi_cmd = MMC_SEND_STATUS;
			/*
			 * Indicate the maximum timeout to close
			 * a command interrupted by HPI
			 */
			card->ext_csd.out_of_int_time =
				ext_csd[EXT_CSD_OUT_OF_INTERRUPT_TIME] * 10;
		}

		card->ext_csd.rel_param = ext_csd[EXT_CSD_WR_REL_PARAM];
		card->ext_csd.rst_n_function = ext_csd[EXT_CSD_RST_N_FUNCTION];

		/*
		 * RPMB regions are defined in multiples of 128K.
		 */
		card->ext_csd.raw_rpmb_size_mult = ext_csd[EXT_CSD_RPMB_MULT];
		if (ext_csd[EXT_CSD_RPMB_MULT] && mmc_host_cmd23(card->host)) {
			mmc_part_add(card, ext_csd[EXT_CSD_RPMB_MULT] << 17,
				EXT_CSD_PART_CONFIG_ACC_RPMB,
				"rpmb", 0, false,
				MMC_BLK_DATA_AREA_RPMB);
		}
	}

	card->ext_csd.raw_erased_mem_count = ext_csd[EXT_CSD_ERASED_MEM_CONT];
	if (ext_csd[EXT_CSD_ERASED_MEM_CONT])
		card->erased_byte = 0xFF;
	else
		card->erased_byte = 0x0;

	/* eMMC v4.5 or later */
	card->ext_csd.generic_cmd6_time = DEFAULT_CMD6_TIMEOUT_MS;
	if (card->ext_csd.rev >= 6) {
		card->ext_csd.feature_support |= MMC_DISCARD_FEATURE;

		card->ext_csd.generic_cmd6_time = 10 *
			ext_csd[EXT_CSD_GENERIC_CMD6_TIME];
		card->ext_csd.power_off_longtime = 10 *
			ext_csd[EXT_CSD_POWER_OFF_LONG_TIME];

		card->ext_csd.cache_size =
			ext_csd[EXT_CSD_CACHE_SIZE + 0] << 0 |
			ext_csd[EXT_CSD_CACHE_SIZE + 1] << 8 |
			ext_csd[EXT_CSD_CACHE_SIZE + 2] << 16 |
			ext_csd[EXT_CSD_CACHE_SIZE + 3] << 24;

		if (ext_csd[EXT_CSD_DATA_SECTOR_SIZE] == 1)
			card->ext_csd.data_sector_size = 4096;
		else
			card->ext_csd.data_sector_size = 512;

		if ((ext_csd[EXT_CSD_DATA_TAG_SUPPORT] & 1) &&
		    (ext_csd[EXT_CSD_TAG_UNIT_SIZE] <= 8)) {
			card->ext_csd.data_tag_unit_size =
			((unsigned int) 1 << ext_csd[EXT_CSD_TAG_UNIT_SIZE]) *
			(card->ext_csd.data_sector_size);
		} else {
			card->ext_csd.data_tag_unit_size = 0;
		}

		card->ext_csd.max_packed_writes =
			ext_csd[EXT_CSD_MAX_PACKED_WRITES];
		card->ext_csd.max_packed_reads =
			ext_csd[EXT_CSD_MAX_PACKED_READS];
	} else {
		card->ext_csd.data_sector_size = 512;
	}

	/* eMMC v5 or later */
	if (card->ext_csd.rev >= 7) {
		memcpy(card->ext_csd.fwrev, &ext_csd[EXT_CSD_FIRMWARE_VERSION],
		       MMC_FIRMWARE_LEN);
		card->ext_csd.ffu_capable =
			(ext_csd[EXT_CSD_SUPPORTED_MODE] & 0x1) &&
			!(ext_csd[EXT_CSD_FW_CONFIG] & 0x1);

		card->ext_csd.pre_eol_info = ext_csd[EXT_CSD_PRE_EOL_INFO];
		card->ext_csd.device_life_time_est_typ_a =
			ext_csd[EXT_CSD_DEVICE_LIFE_TIME_EST_TYP_A];
		card->ext_csd.device_life_time_est_typ_b =
			ext_csd[EXT_CSD_DEVICE_LIFE_TIME_EST_TYP_B];
	}

	/* eMMC v5.1 or later */
	if (card->ext_csd.rev >= 8) {
		card->ext_csd.cmdq_support = ext_csd[EXT_CSD_CMDQ_SUPPORT] &
					     EXT_CSD_CMDQ_SUPPORTED;
		card->ext_csd.cmdq_depth = (ext_csd[EXT_CSD_CMDQ_DEPTH] &
					    EXT_CSD_CMDQ_DEPTH_MASK) + 1;
		/* Exclude inefficiently small queue depths */
		if (card->ext_csd.cmdq_depth <= 2) {
			card->ext_csd.cmdq_support = false;
			card->ext_csd.cmdq_depth = 0;
		}
		if (card->ext_csd.cmdq_support) {
			pr_debug("%s: Command Queue supported depth %u\n",
				 mmc_hostname(card->host),
				 card->ext_csd.cmdq_depth);
		}
	}

done:
	ENX_LOG_END(DBG_SDIO_CD_CMD);
	return nRes;
}

static ENX_OKFAIL Sdio_mmc_read_ext_csd(SDIO_MMC_CARD *card)
{
	ENX_OKFAIL nRes = ENX_FAIL;
	UINT nResp;

	ENX_LOG_START(DBG_SDIO_CD_CMD);

	if (!Sdio_mmc_can_ext_csd(&mmc_card)) {
		nRes = ENX_OK;
		goto done;
	}

	nRes = SdioMmcRegDataRead(card->host->nCH, MMC_SEND_EXT_CSD, 0, &nResp, ecrtR1, card->raw_ext_csd, sizeof(card->raw_ext_csd));

done:
	ENX_LOG_END(DBG_SDIO_CD_CMD);
	return nRes;
}

static ENX_OKFAIL Sdio_mmc_card_set_blockaddr(SDIO_MMC_CARD *card)
{
	ENX_OKFAIL nRes = ENX_FAIL;
	UINT nResp;

	ENX_LOG_START(DBG_SDIO_CD_CMD);

	nRes = SdioMmcCmd(card->host->nCH, MMC_SELECT_CARD, card->rca << 16, &nResp, ecrtR1);

	ENX_LOG_END(DBG_SDIO_CD_CMD);
	return nRes;
}

static ENX_OKFAIL Sdio_mmc_set_erase_size(SDIO_MMC_CARD *card)
{
	ENX_OKFAIL nRes = ENX_FAIL;
	UINT nResp;

	ENX_LOG_START(DBG_SDIO_CD_CMD);

	nRes = SdioMmcCmd(card->host->nCH, MMC_SELECT_CARD, card->rca << 16, &nResp, ecrtR1);

	ENX_LOG_END(DBG_SDIO_CD_CMD);
	return nRes;
}
#endif
////////////////////////////////////////////////////////////////////////////////
// SDIO-MMC Process
static uint64_t sdio_data_address = 1;

ENX_OKFAIL SdioEmmcInitProcess(void)
{
	ENX_LOG_START(DBG_SDIO_MMC_CMD);
#if 0
	UINT wgap;
	ULONG wstart = BenchTimeStart();

	UINT nCH = mmc_host.nCH;
	memset(&mmc_host, 0, sizeof(mmc_host));
	memset(&mmc_card, 0, sizeof(mmc_card));
	mmc_host.nCH = nCH;
	mmc_host.caps = MMC_CAP_4_BIT_DATA | MMC_CAP_MMC_HIGHSPEED | MMC_CAP_3_3V_DDR;
	mmc_host.caps2 = 0;
	mmc_card.host = &mmc_host;

#if 1
	if (SDIO_DATA_BASE == NULL) {
		SDIO_DATA_BASE = pvPortMalloc(1024);
		sdio_data_address = (uint64_t)SDIO_DATA_BASE;
		for (int k = 0; k < 1024; k++) {
			SDIO_DATA_BASE[k] = 0xA5;
		}
	}
//	BYTE *pSDIO_DATA_BASE = SDIO_DATA_BASE;
//	printf("SDIO_DATA_BASE: 0x%08X\n", SDIO_DATA_BASE);
#endif

	SdioSetBitMode(mmc_host.nCH, SDIO_1BIT_MODE);	// 1bit mode
	SdioSetDataBlockByte(mmc_host.nCH, 0x200);	// 512byte
	SdioSetClockDef(mmc_host.nCH);				// 400khz
	char strClockPrint[40] = {0};
#if (DBG_SDIO_MMC_CMD & ENX_DBG_STATE)
	SdioClockDivPrint(mmc_host.nCH, strClockPrint);
	printf("SDIO%u(EMMC) Init Start(%s)\n", mmc_host.nCH, strClockPrint);
#endif

	// mmc_go_idle
	if (Sdio_mmc_go_idle(&mmc_card) == ENX_FAIL) {
		mmc_host.nErrorCode = 0x00000001;
		goto done_fail;
	}

	// mmc_send_op_cond
	if (Sdio_mmc_send_op_cond(&mmc_card, 0x40FF8000) == ENX_FAIL) {
		mmc_host.nErrorCode = 0x00000002;
		goto done_fail;
	}
	SdioPrintOCR(&mmc_card.ocr);

	// mmc_send_cid
	if (Sdio_mmc_send_cid(&mmc_card) == ENX_FAIL) {
		mmc_host.nErrorCode = 0x00000003;
		goto done_fail;
	}
	SdioPrintCID(&mmc_card);

	// mmc_set_relative_addr
	mmc_card.rca = 1;
	if (Sdio_mmc_set_relative_addr(&mmc_card) == ENX_FAIL) {
		mmc_host.nErrorCode = 0x00000004;
		goto done_fail;
	}

	// mmc_send_csd
	if (Sdio_mmc_send_csd(&mmc_card) == ENX_FAIL) {
		mmc_host.nErrorCode = 0x00000005;
		goto done_fail;
	}
	if (Sdio_mmc_decode_csd(&mmc_card) == ENX_FAIL) {
		mmc_host.nErrorCode = 0x00000105;
		goto done_fail;
	}
	if (Sdio_mmc_decode_cid(&mmc_card) == ENX_FAIL) {
		mmc_host.nErrorCode = 0x00000205;
		goto done_fail;
	}
	SdioPrintCSD(&mmc_card);

	// mmc_set_dsr
	if (mmc_card.csd.dsr_imp) {
		_Rprintf("Check!\n");
	}

	// mmc_select_card
	if (Sdio_mmc_select_card(&mmc_card, 1) == ENX_FAIL) {
		mmc_host.nErrorCode = 6;
		goto done_fail;
	}

	// mmc_read_ext_csd
	if (Sdio_mmc_read_ext_csd(&mmc_card) == ENX_FAIL) {
		mmc_host.nErrorCode = 7;
		goto done_fail;
	}

	mmc_host.nErrorCode = 0xff;
	goto done_fail;










	// mmc_card_set_blockaddr
	if (mmc_card.ocr.ACCMODE & 0x2) {
		if (Sdio_mmc_card_set_blockaddr(&mmc_card) == ENX_FAIL) {
			mmc_host.nErrorCode = 8;
			goto done_fail;
		}
	}

	// mmc_set_erase_size
	if (Sdio_mmc_set_erase_size(&mmc_card) == ENX_FAIL) {
		mmc_host.nErrorCode = 9;
		goto done_fail;
	}










	mmc_host.nErrorCode = 0xff;
	goto done_fail;

	mmc_host.nActive = 1;

	SdioClockDivPrint(mmc_host.nCH, strClockPrint);
	wgap = BenchTimeStop(wstart);
	_Gprintf("SDIO%u(EMMC) Init OK(%s) %uus\n", mmc_host.nCH, strClockPrint, wgap);

	ENX_LOG_END(DBG_SDIO_MMC_CMD);
	return ENX_OK;
done_fail:
	SdioClockDivPrint(mmc_host.nCH, strClockPrint);
	wgap = BenchTimeStop(wstart);
	_Rprintf("SDIO%u(EMMC) Init Fail(err:%u)(%s) %uus\n", mmc_host.nCH, mmc_host.nErrorCode, strClockPrint, wgap);
#endif
	ENX_LOG_END(DBG_SDIO_MMC_CMD);
	return ENX_FAIL;
}

void SdioEmmcClockDown(void)
{
#if 0
	UINT Clkdiv = SdioGetClockDiv(mmc_host.nCH);
	if (Clkdiv == 0xffff) {
		SdioSetClockDiv(mmc_host.nCH, 0);
	} else {
		SdioSetClockDiv(mmc_host.nCH, Clkdiv + 1);
	}

	char strClockPrint[40] = {0};
	SdioClockDivPrint(mmc_host.nCH, strClockPrint);
	printf("SDIO%u(EMMC) Change Clock(%s)\n", mmc_host.nCH, strClockPrint);
#endif
}

void SdioEmmcClockSet(WORD Clkdiv)
{
#if 0
	SdioSetClockDiv(mmc_host.nCH, Clkdiv);

	char strClockPrint[40] = {0};
	SdioClockDivPrint(mmc_host.nCH, strClockPrint);
	printf("SDIO%u(EMMC) Change Clock(%s)\n", mmc_host.nCH, strClockPrint);
#endif
}

void SdioEmmcClockRestore(void)
{
#if 0
	SdioSetClockDiv(mmc_host.nCH, mmc_host.nSetClock);

	char strClockPrint[40] = {0};
	SdioClockDivPrint(mmc_host.nCH, strClockPrint);
	printf("SDIO%u(EMMC) Change Clock(%s)\n", mmc_host.nCH, strClockPrint);
#endif
}


UINT SdioEmmcDet(void)
{
	return GpioGetPin(EMMC_GPIO_IRQ);
}

// 기본적인 CH, IRQ, 최초주파수, Pull-up 등을 설정한다.
void SdioEmmcInit(UINT nCH)
{
#if 0
	memset(&mmc_host, 0, sizeof(mmc_host));
	mmc_host.nCH = nCH;
	mmc_host.nErrorCode = 0;

	SdioSetIoMode(mmc_host.nCH, SDIO_CD_MODE);

#if 0										// New Peri B/d - LO:OFF HI:ON
	GpioSetOut(EMMC_GPIO_RST, GPIO_OUT_LOW);
	WaitXms(100);
	GpioSetOut(EMMC_GPIO_RST, GPIO_OUT_HI);
#else
	GpioSetOut(EMMC_GPIO_RST, GPIO_OUT_LOW);	// Old Peri B/d - LO:ON HI:OFF
#endif
	SdioSetDelayfn(mmc_host.nCH, (user_delay_fn)ENX_SDIOMMC_DELAY);

//	GpioSetDir(EMMC_GPIO_IRQ, GPIO_DIR_IN);
//	GpioRiseEdge(EMMC_GPIO_IRQ);
//	GpioIrqCallback(EMMC_GPIO_IRQ, SdioEmmcDetectIrq, NULL);
//	GpioIrqOn(EMMC_GPIO_IRQ);
#endif
}

////////////////////////////////////////////////////////////////////////////////
// SDIO-EMMC Port
UINT SdioEmmcGetActive(void)
{
//	return mmc_host.nActive;
}

UINT SdioEmmcGetErrCode(void)
{
//	return mmc_host.nErrorCode;
}

UINT SdioEmmcGetAUSize(void)
{
	ENX_LOG_START(DBG_SDIO_MMC_CMD);
	ENX_LOG_END(DBG_SDIO_MMC_CMD);
	return 0;
}

void SdioEmmcGetName(char *buf)
{
	ENX_LOG_START(DBG_SDIO_MMC_CMD);
	buf[0] = 0;
	buf[1] = 0;
	buf[2] = 0;
	buf[3] = 0;
	buf[4] = 0;
	ENX_LOG_END(DBG_SDIO_MMC_CMD);
}

UINT SdioEmmcGetSectorCnt(void)
{
	ENX_LOG_START(DBG_SDIO_MMC_CMD);
	ENX_LOG_END(DBG_SDIO_MMC_CMD);
	return 0;
}

UINT SdioEmmcGetSize(void)
{
	ENX_LOG_START(DBG_SDIO_CD_CMD);
	ENX_LOG_END(DBG_SDIO_CD_CMD);
	return 0;
}

ENX_OKFAIL SdioEmmcE(UINT start_sctor, UINT end_sctor)
{
	ENX_OKFAIL nRes = ENX_FAIL;

	ENX_LOG_START(DBG_SDIO_CD_CMD);

	ENX_LOG_END(DBG_SDIO_CD_CMD);

	return nRes;
}

ENX_OKFAIL SdioEmmcRead(const BYTE *buff, UINT sector, UINT count)
{
	ENX_OKFAIL nRes = ENX_FAIL;

	ENX_LOG_START(DBG_SDIO_CD_CMD);

	ENX_LOG_END(DBG_SDIO_CD_CMD);

	return nRes;
}

ENX_OKFAIL SdioEmmcWrite(const BYTE *buff, UINT sector, UINT count)
{
	ENX_OKFAIL nRes = ENX_FAIL;

	ENX_LOG_START(DBG_SDIO_CD_CMD);

	ENX_LOG_END(DBG_SDIO_CD_CMD);

	return nRes;
}
#endif
