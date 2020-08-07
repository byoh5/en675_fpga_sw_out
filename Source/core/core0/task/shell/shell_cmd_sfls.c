//*************************************************************************************************
// User shell commands
//*************************************************************************************************

#include "dev.h"
#include "enx_freertos.h"

#include "shell_cmd_sfls.h"
#include <stdio.h> // for snprintf
#include <stdlib.h> // for srand
#include <string.h> // for strcmp, memset

#include "eon_en25qh256.h"
#include "winbond_w25q256jvq.h"
#include "winbond_w25q64jviq.h"

//#include "en675_ddr_init_bin.h"
//#include "UBOOT.h"
//#include "BBL2.h"
//#include "EXBL.h"
#include "BOOT_BIN.h"

const char *sSflsTest[]      = {"Test SFLS",                                      (char*)0};

//*************************************************************************************************
// User functions
//-------------------------------------------------------------------------------------------------
//
#define SFLSDATA_MAX_COUNT 16
#define SFLSDATA_PP_SIZE 256
#define SFLSDATA_SE_SIZE 4096

typedef ATTR_MALIGN64 struct {
	BYTE *data;
	BYTE *alloc;
} SflsTestBuffer;
static SflsTestBuffer sfls_data = {NULL, NULL};

typedef ATTR_MALIGN64 struct {
	TaskHandle_t taskHandle;

	BYTE *arrSrc;
	BYTE *arrDst;
	ULONG u64BufSize;

	UINT u32TestCount;
	UINT u32TestBlock;
	UINT u32Flag;
	BYTE u8Close;
} SflsAutoTestBuffer;

static SflsAutoTestBuffer sflsitem;

static void sfls_create_random(BYTE *data, uint64_t size)
{
	srand(rdcycle());
	for (uint64_t i = 0; i < size; i++) {
		data[i] = rand() % 255;
	}
}

#if 0
static void SflsTestTask(void *ctx)
{
	UINT u32DataBlockByte = 0;//SflsGetDataBlockByte(0);
	if (sflsitem.u64BufSize < u32DataBlockByte) {
		_Rprintf("Buffer size error, size(%u)\n", sflsitem.u64BufSize);
		goto free;
	}

	if (sflsitem.arrSrc) {
		vPortFree(sflsitem.arrSrc);
		sflsitem.arrSrc = NULL;
	}
	sflsitem.arrSrc = pvPortMalloc(sflsitem.u64BufSize);
	if (sflsitem.arrSrc == NULL) {
		_Rprintf("malloc error(arrSrc), size(%u)\n", sflsitem.u64BufSize);
		goto free;
	}

	if (sflsitem.arrDst) {
		vPortFree(sflsitem.arrDst);
		sflsitem.arrDst = NULL;
	}
	sflsitem.arrDst = pvPortMalloc(sflsitem.u64BufSize);
	if (sflsitem.arrDst == NULL) {
		_Rprintf("malloc error(arrDst), size(%u)\n", sflsitem.u64BufSize);
		goto free;
	}

	BYTE *parrSrc = (BYTE *)ENX_MEM_ALIGN(sflsitem.arrSrc);
	BYTE *parrDst = (BYTE *)ENX_MEM_ALIGN(sflsitem.arrDst);

	printf("SFLS Memory Src(0x%08lX->0x%08lX)\n", (intptr_t)sflsitem.arrSrc, (intptr_t)parrSrc);
	printf("SFLS Memory Dst(0x%08lX->0x%08lX)\n", (intptr_t)sflsitem.arrDst, (intptr_t)parrDst);

	//srand(rdcycle());
	srand(3);

	printf("SFLS Test Task(Src:0x%08lX)(Dst:0x%08lX)(Size:%lu)(Count:%u)\n", (intptr_t)parrSrc, (intptr_t)parrDst, sflsitem.u64BufSize, sflsitem.u32TestCount);
//	char strPrintSize[16] = {0};
	UINT u32MaxIdx = 0;
//	UINT u32MaxIdx = SflsCdGetSectorCnt() - 4000;
//	getSDGBSizeT(strPrintSize);
//	_Cprintf("Info:%s MaxIdx:%u\n", strPrintSize, u32MaxIdx);

	if (u32MaxIdx == 0) {
		_Rprintf("no sd-card?\n");
		vPortFree(sflsitem.arrSrc);
		vPortFree(sflsitem.arrDst);
		sflsitem.arrSrc = NULL;
		sflsitem.arrDst = NULL;
		sflsitem.taskHandle = NULL;
		vTaskDelete(NULL);
	}

	UINT u32RelTestSize = 0;
	if (sflsitem.u64BufSize > 16 * 1024 * 1024) {
		u32RelTestSize = 16 * 1024 * 1024;
	} else {
		u32RelTestSize = sflsitem.u64BufSize;
	}
	//hwflush_dcache_range((ULONG)sflsitem.arrSrc, u32RelTestSize);
	for (UINT i = 0; i < sflsitem.u64BufSize; i++) {
		sflsitem.arrSrc[i] = rand() % 255;
	}
	hwflush_dcache_range((ULONG)sflsitem.arrSrc, u32RelTestSize);

	UINT u32StartSector = u32MaxIdx - sflsitem.u32TestBlock - 1 - sflsitem.u32TestBlock;
	UINT u32EndSector = u32MaxIdx - 1 - sflsitem.u32TestBlock;
	printf("Test Sector: 0x%08X ~ 0x%08X\n", u32StartSector, u32EndSector);

	u32RelTestSize = 0;
	UINT pass = 0, fail = 0, flag = 0;
	for (UINT i = 0; i < sflsitem.u32TestCount; i++) {
		UINT testSector = rand() % ((u32EndSector - u32StartSector) + 1) + u32StartSector;
#if 1
		UINT readCount = 0;
		if ((rand() % 4) == 0) {
			readCount = 1;
		} else {
			UINT maxCount = u32EndSector - testSector;
			if (maxCount <= 2) {
				readCount = 1;
			} else {
				readCount = rand() % (maxCount - 2) + 2;
			}
		}
#else
		UINT readCount = i + 1;
		if ((testSector + readCount) >= u32EndSector) {
			testSector -= readCount;
		}
#endif

		printf("%3u%% %5u/%5u Test Sector(0x%08X ~ 0x%08X) Count(%8u) %6s-", ((i+1) * 100) / sflsitem.u32TestCount, i+1, sflsitem.u32TestCount, testSector, testSector+readCount-1, readCount, readCount == 1 ? "single" : "multi");

		//SflsCdWrite(parrSrc, testSector, readCount);
		//printf("W");

		//SflsCdRead(parrDst, testSector, readCount);
		//printf("R");

		vTaskDelay(1);

		// comp
		flag = 0;
		UINT u32Checksize = readCount * u32DataBlockByte;
		UINT k, errSet = 0;
		for (k = 0; k < u32Checksize; k++) {
			if (parrSrc[k] != parrDst[k]) {
				flag = 1;
				errSet = k / 512;
				break;
			}
		}

		if (flag == 0) {
			pass++;
			_Gprintf(" - OK\n");
		} else {
			fail++;
			_Rprintf(" - Fail\nDet(%u), Error Sector(0x%08X)\n", k, testSector + errSet);
			hexCmpDump("SD-W/R test", parrSrc + (errSet * 512), parrDst + (errSet * 512), 512);
			break;
		}
	}

	printf("\nTest End. Pass(%d) Fail(%d)\n", pass, fail);

done:
	//vPortFree(sflsitem.arrSrc);
	//vPortFree(sflsitem.arrDst);
	sflsitem.taskHandle = NULL;
	vTaskDelete(NULL);
}
#endif

static void SflsReadTestTask(void *ctx)
{
	if (sflsitem.arrSrc) {
		vPortFree(sflsitem.arrSrc);
		sflsitem.arrSrc = NULL;
	}
	sflsitem.arrSrc = pvPortMalloc(sflsitem.u64BufSize);
	if (sflsitem.arrSrc == NULL) {
		printf("malloc error(arrSrc), size(%lu)\n", sflsitem.u64BufSize);
		goto freedone;
	}

	if (sflsitem.arrDst) {
		vPortFree(sflsitem.arrDst);
		sflsitem.arrDst = NULL;
	}
	sflsitem.arrDst = pvPortMalloc(sflsitem.u64BufSize);
	if (sflsitem.arrDst == NULL) {
		printf("malloc error(arrDst), size(%lu)\n", sflsitem.u64BufSize);
		goto freedone;
	}

	BYTE *parrOrg = (BYTE *)ENX_MEM_ALIGN(sflsitem.arrSrc);
	BYTE *parrSdr = (BYTE *)ENX_MEM_ALIGN(sflsitem.arrDst);

	printf("SFLS Read Test Task(Org: 0x%08lX)(SDr: 0x%08lX)(Buffer Size: %lu)\n", (intptr_t)parrOrg, (intptr_t)parrSdr, sflsitem.u64BufSize);

	hwflush_dcache_range((ULONG)parrOrg, sflsitem.u64BufSize);

	BYTE *p8Base = (BYTE *)SFLS_BASE;
	UINT u32MaxPPIdx = SFLS_SIZE / SFLSDATA_PP_SIZE;

	srand(1);

	printf("Read Test: 0x%08lX ~ 0x%08lX\n", (intptr_t)p8Base, (intptr_t)(p8Base + SFLS_SIZE));
	UINT pass = 0, fail = 0;
	ULONG start_time = BenchTimeStart();
	for (UINT i = 0; i < sflsitem.u32TestCount; i++) {
		UINT *arr32Org = (UINT *)parrOrg;
//		UINT *arr32Sdr = (UINT *)parrSdr;

		UINT readCount = 0;
		if (sflsitem.u32TestBlock == 1) {
			readCount = 1;
		} else {
			if ((rand() % 4) == 0) {
				readCount = 1;
			} else {
				readCount = rand() % (sflsitem.u32TestBlock - 2) + 2;
				if (readCount > sflsitem.u32TestBlock) {
					readCount = sflsitem.u32TestBlock - 1;
				}
				if (readCount == 0) {
					readCount = 1;
				}
			}
		}

		UINT startIdx = rand() % u32MaxPPIdx;
		UINT endIdx = startIdx + readCount;
		if (endIdx >= u32MaxPPIdx) {
			endIdx = u32MaxPPIdx - 1;
			readCount = endIdx - startIdx;
			if (readCount == 0) {
				readCount = 1;
			}
		}

		UINT startAddr = SFLS_BASE + (startIdx * SFLSDATA_PP_SIZE);
		UINT endAddr = SFLS_BASE + (endIdx * SFLSDATA_PP_SIZE);

		printf("%3u%% %5u/%5u Test Addr(0x%08X ~ 0x%08X) Count(%8u) - ", ((i+1) * 100) / sflsitem.u32TestCount, i+1, sflsitem.u32TestCount, startAddr, endAddr, readCount);

		// 정답지 만들기
		for (UINT j = 0; j < readCount; j++) {
			for (UINT j2 = 0; j2 < (SFLSDATA_PP_SIZE/4); j2 += 4) {
				UINT inx = j * (SFLSDATA_PP_SIZE / 4) + j2;
				UINT addr = (startAddr + (j * SFLSDATA_PP_SIZE)) + (4 * j2);
				if (addr >= (0xC0000000 + SFLS_SIZE)) {
					flprintf("E");
					CPU_BREAK();
				}
				arr32Org[inx+0] = ENX_HTONL(addr);
				arr32Org[inx+1] = ENX_HTONL(startIdx + j);
				arr32Org[inx+2] = 0xFF0000FF;
				arr32Org[inx+3] = (j2+3) << 24 | (j2+3) << 16 | (j2+3) << 8 | (j2+3);
			}
		}

		// copy read
		printf(".");
		hwflush_dcache_range((ulong)parrSdr, SFLSDATA_PP_SIZE*readCount);
		ULONG a = BenchTimeStart();
		BDmaMemCpy_rtos(0, parrSdr, (BYTE *)(intptr_t)startAddr, SFLSDATA_PP_SIZE*readCount);
		UINT end = BenchTimeStop(a);
		printf(".");
		// direct read
		//hwflush_dcache_range((ulong)startAddr, SFLSDATA_PP_SIZE*readCount);
		//printf(".");

		// comp
		int errchk_cp = memcmp(parrOrg, parrSdr, SFLSDATA_PP_SIZE*readCount);
		//int errchk_cp = 0;
		//printf(".");
		//ULONG a = BenchTimeStart();
		//int errchk_di = memcmp(parrOrg, startAddr, SFLSDATA_PP_SIZE*readCount);
		//UINT end = BenchTimeStop(a);
		int errchk_di = 0;
		//printf(".");
		if (errchk_cp == 0 && errchk_di == 0) {
			pass++;
			char buf[64] = {0};
			snprintf(buf, 64, "%.2f", ((SFLSDATA_PP_SIZE * readCount) / 1024.0) / (end / 1000.0 / 1000.0));
			_Gprintf("OK, %sKbyte/s\n", buf);
		} else {
			fail++;
			_Rprintf("Fail(errchk:%d:%d)\n", errchk_cp, errchk_di);

			if (errchk_cp != 0) {
				hexCmpDump("SFLS-read(copy) dump", parrOrg, parrSdr, SFLSDATA_PP_SIZE*readCount);
			}
			if (errchk_di != 0) {
				hexCmpDump("SFLS-read(direct) dump", parrOrg, p8Base, SFLSDATA_PP_SIZE*readCount);
			}
			break;
		}

		if (sflsitem.u8Close == 1) {
			break;
		}
	}
	UINT end_time = BenchTimeStop(start_time);
	char buf[64] = {0};
	snprintf(buf, 64, "%.2fsec", end_time / 1000.0 / 1000.0);
	printf("\nRead Test End(%s). Pass(%d) Fail(%d)\n", buf, pass, fail);

	vTaskInfoPrint();

done:
	sflsitem.taskHandle = NULL;
	vTaskDelete(NULL);

freedone:
	if (sflsitem.arrSrc) {
		vPortFree(sflsitem.arrSrc);
		sflsitem.arrSrc = NULL;
	}
	if (sflsitem.arrDst) {
		vPortFree(sflsitem.arrDst);
		sflsitem.arrDst = NULL;
	}
	goto done;
}

static void SflsWriteTestTask(void *ctx)
{
	BYTE *alloc = pvPortMalloc(sflsitem.u64BufSize);
	if (alloc == NULL) {
		printf("malloc error(arrSrc), size(%lu)\n", sflsitem.u64BufSize);
		sflsitem.taskHandle = NULL;
		vTaskDelete(NULL);
	}

	sflsitem.arrSrc = (BYTE *)ENX_MEM_ALIGN(alloc);

	printf("SFLS Write Test Task(Base: 0x%08lX)\n", (intptr_t)sflsitem.arrSrc);

	hwflush_dcache_range((ULONG)sflsitem.arrSrc, SFLSDATA_PP_SIZE);

	// TEST code
	BYTE *p8Base = (BYTE *)SFLS_BASE;
	BYTE *p8Pos = p8Base;
	// Test code

	if (sflsitem.u32Flag == 0) {
		cmd_test_sfls(3, (char *[]){NULL, "e", "all"});
	}

	printf("Write Test: 0x%08lX ~ 0x%08lX\n", (intptr_t)p8Base, (intptr_t)(p8Base + (sflsitem.u32TestCount * SFLSDATA_PP_SIZE) - 1));
	ULONG total_time = 0, total_size = 0, time1000 = 0, size1000 = 0;
	char buf[64] = {0};
	ULONG start_time = BenchTimeStart();
	for (UINT i = 0; i < sflsitem.u32TestCount; i++) {
		if (i != 0 && i % 1000 == 0) {
			snprintf(buf, 64, "%.2f", (size1000 / 1024.0) / (time1000 / 1000.0 / 1000.0));
			printf("%7u/%7u ing... %3u%%, ", i, sflsitem.u32TestCount, (i * 100) / sflsitem.u32TestCount);
			_Gprintf("%sKbyte/s\n", buf);
			size1000 = time1000 = 0;
		}

		UINT *arr32Src = (UINT *)sflsitem.arrSrc;
		for (UINT j = 0; j < (SFLSDATA_PP_SIZE/4); j += 4) {
			UINT addr = ((intptr_t)p8Pos) + (4 * j);
			arr32Src[j+0] = ENX_HTONL(addr);
			arr32Src[j+1] = ENX_HTONL(i);
			arr32Src[j+2] = 0xFF0000FF;
			arr32Src[j+3] = (j+3) << 24 | (j+3) << 16 | (j+3) << 8 | (j+3);
		}
		hwflush_dcache_range((ULONG)sflsitem.arrSrc, SFLSDATA_PP_SIZE);
#if 0
		if (((ULONG)p8Pos) % 4096 == 0 && sflsitem.u32Flag == 0) {
			SflsSectErase(p8Pos - (BYTE *)SFLS_BASE, ENX_YES);
		}
#endif
		ULONG a = BenchTimeStart();
		BDmaMemCpy_rtos(0, p8Pos, sflsitem.arrSrc, SFLSDATA_PP_SIZE);
		total_time += BenchTimeStop(a);
		time1000 += BenchTimeStop(a);
		total_size += SFLSDATA_PP_SIZE;
		size1000 += SFLSDATA_PP_SIZE;

		p8Pos += SFLSDATA_PP_SIZE;
	}
	UINT end_time = BenchTimeStop(start_time);
	snprintf(buf, 64, "Write Done(%.2fsec): total avg ", end_time / 1000.0 / 1000.0);
	printf(buf);
	snprintf(buf, 64, "%.2fKbyte/s", (total_size / 1024.0) / (total_time / 1000.0 / 1000.0));
	_Gprintf("%s\n", buf);

	vPortFree(alloc);
	sflsitem.arrSrc = NULL;
	sflsitem.taskHandle = NULL;
	vTaskDelete(NULL);
}

int cmd_test_sfls(int argc, char *argv[])
{
	static UINT nBufferSize = SFLSDATA_PP_SIZE * SFLSDATA_MAX_COUNT;

	if (sfls_data.alloc == NULL) {
		sfls_data.alloc = pvPortMalloc(nBufferSize+SFLSDATA_PP_SIZE);
		printf("SFLS test memory Init (0x%08lX)\n", (intptr_t)sfls_data.alloc);
		sfls_data.data = (BYTE *)ENX_MEM_ALIGN(sfls_data.alloc);
		printf("SFLS test memory ALIGN64 address (0x%08lX)\n", (intptr_t)sfls_data.data);
	}

	if(argc == 1) {
		SflsRegShow(ENX_YES);
		cmd_test_sfls(2, (char *[]){NULL, "status"});

		BYTE sfdp_bin[256] = {0};
		SflsReadSFDP(sfdp_bin);
		SflsViewerSFDP(sfdp_bin);
	} else {
		static int gap = 0, iomode = 0;

		if (strcmp(argv[1], "init") == 0) {
			printf("call SflsInit\n");
			SflsInit();
		} else if (strcmp(argv[1], "reset") == 0) {
			SFLS_IF_RST = 1;
		} else if (strcmp(argv[1], "reset2") == 0) {
#ifdef __SFLS_EN25QH256__
			extern void SflsEn25qh256_Reset(void);
			SflsEn25qh256_Reset();
#endif
		} else if (strcmp(argv[1], "status") == 0) {
			char outbuf[32] = {0};
			BYTE status;
			shell_line_print('-', NULL);
			status = SflsReadStatus();
			es_snprintf(outbuf, sizeof(outbuf), "%08b, 0x%02X", status, status);
			printf("Read Status Register 1: %s\n", outbuf);
			SflsReadStatusView(status);
#ifdef __SFLS_MT25QL256__
#if 0
			shell_line_print('-', NULL);
			status = SflsMt25ql256_ReadStatus2();
			es_snprintf(outbuf, sizeof(outbuf), "%08b, 0x%02X", status, status);
			printf("Read Status Register 2: %s\n", outbuf);
#endif
#endif
#ifdef __SFLS_W25Q256JVQ__
			shell_line_print('-', NULL);
			status = SflsW25q256jvq_ReadStatus2();
			es_snprintf(outbuf, sizeof(outbuf), "%08b, 0x%02X", status, status);
			printf("Read Status Register 2: %s\n", outbuf);
			shell_line_print('-', NULL);
			status = SflsW25q256jvq_ReadStatus3();
			es_snprintf(outbuf, sizeof(outbuf), "%08b, 0x%02X", status, status);
			printf("Read Status Register 3: %s\n", outbuf);
#endif
#ifdef __SFLS_W25Q64JVIQ__
			shell_line_print('-', NULL);
			status = SflsW25q64jviq_ReadStatus2();
			es_snprintf(outbuf, sizeof(outbuf), "%08b, 0x%02X", status, status);
			printf("Read Status Register 2: %s\n", outbuf);
			shell_line_print('-', NULL);
			status = SflsW25q64jviq_ReadStatus3();
			es_snprintf(outbuf, sizeof(outbuf), "%08b, 0x%02X", status, status);
			printf("Read Status Register 3: %s\n", outbuf);
#endif
#ifdef __SFLS_GD25Q128C__
			shell_line_print('-', NULL);
			status = SflsGd25q128c_ReadStatus2();
			es_snprintf(outbuf, sizeof(outbuf), "%08b, 0x%02X", status, status);
			printf("Read Status Register 2: %s\n", outbuf);
			shell_line_print('-', NULL);
			status = SflsGd25q128c_ReadStatus3();
			es_snprintf(outbuf, sizeof(outbuf), "%08b, 0x%02X", status, status);
			printf("Read Status Register 3: %s\n", outbuf);
#endif
#ifdef __SFLS_EN25QH256__
			shell_line_print('-', NULL);
			status = SflsEn25qh256_ReadIFR();
			es_snprintf(outbuf, sizeof(outbuf), "%08b", status);
			printf("Read Information Register: %s\n", outbuf);
#endif
			shell_line_print('-', NULL);
		} else if (argc == 3 && strcmp(argv[1], "4b") == 0) {
			if (strcmp(argv[2], "on") == 0) {
				SflsEnter4B();
			} else {
				SflsExit4B();
			}
		} else if (argc == 3 && strcmp(argv[1], "qpi") == 0) {
			if (strcmp(argv[2], "on") == 0) {
				SflsEnterQPI();
			} else {
				SflsExitQPI();
			}
		} else if (argc == 3 && strcmp(argv[1], "qe") == 0) {
			if (strcmp(argv[2], "on") == 0) {
				SflsEnterQE();
			} else {
				SflsExitQE();
			}
			cmd_test_sfls(2, (char *[]){NULL, "status"});
		} else if (argc == 3 && strcmp(argv[1], "pro") == 0) {
			if (strcmp(argv[2], "on") == 0) {
				SflsEnterProtection();
			} else {
				SflsExitProtection();
			}
			cmd_test_sfls(2, (char *[]){NULL, "status"});
		} else if (strcmp(argv[1], "info") == 0) {
			printf("call SflsGetinfo\n");
			SflsGetinfo();
		} else if (strcmp(argv[1], "t1") == 0) {
			SFLS_USR_CMD_MODE	= 2;
			SFLS_USR_ADR_EN		= 0;
#if (EN675_SINGLE==0)
			SFLS_USR_GAP_EN		= 0;
#else
			SFLS_USR_GAP		= 0;
#endif
			SFLS_USR_RD_EN		= 0;
			SFLS_USR_WR_EN		= 0;
			SFLS_USR_BUSY_EN	= 0;
			SFLS_USR_CMD		= 0xf5;
			SFLS_USR_REQ		= 1;
			while (SFLS_USR_REQ);
		} else if (strcmp(argv[1], "t2") == 0) {
			SFLS_USR_CMD_MODE	= 2;
			SFLS_USR_ADR_EN		= 0;
#if (EN675_SINGLE==0)
			SFLS_USR_GAP_EN		= 0;
#else
			SFLS_USR_GAP		= 0;
#endif
			SFLS_USR_RD_EN		= 0;
			SFLS_USR_WR_EN		= 0;
			SFLS_USR_BUSY_EN	= 0;
			SFLS_USR_CMD		= 0xf5;
			SFLS_USR_REQ		= 1;
			while (SFLS_USR_REQ);
		} else if (strcmp(argv[1], "reggap") == 0) {
			SFLS_USR_GAP = SFLS_BUS_GAP = atoi(argv[2]);
			SFLS_BUS_REQ = 1;
			while (SFLS_BUS_REQ);
			printf("Set Gap: %u/%u\n", SFLS_USR_GAP, SFLS_BUS_GAP);
		} else if (strcmp(argv[1], "regrd") == 0) {
#if (EN675_SINGLE==0)
			SFLS_USR_RDLTC = SFLS_IO_RDLTC = atoi(argv[2]);
			SFLS_BUS_REQ = 1;
			while (SFLS_BUS_REQ);
			printf("Set RDLTC: %u/%u\n", SFLS_USR_RDLTC, SFLS_IO_RDLTC);
#else
			SFLS_USR_RDLTC = SFLS_BUS_RDLTC = atoi(argv[2]);
			SFLS_BUS_REQ = 1;
			while (SFLS_BUS_REQ);
			printf("Set RDLTC: %u/%u\n", SFLS_USR_RDLTC, SFLS_BUS_RDLTC);
#endif
#if (EN675_SINGLE==1)
		} else if (strcmp(argv[1], "srd") == 0) {
			printf("USR_RD_FULL : %u\n", SFLS_USR_RD_FULL);
			printf("USR_RD_EMPTY: %u\n", SFLS_USR_RD_EMPTY);
		} else if (strcmp(argv[1], "srd2") == 0) {
			printf("USR_RD_FULL : %u\n", SFLS_USR_RD_FULL);
			printf("USR_RD_EMPTY: %u\n", SFLS_USR_RD_EMPTY);
			printf("USR_RDDAT   : %u\n", SFLS_USR_RDDAT);
		} else if (strcmp(argv[1], "swd") == 0) {
			printf("USR_RD_FULL : %u\n", SFLS_USR_WR_FULL);
			printf("USR_RD_EMPTY: %u\n", SFLS_USR_WR_EMPTY);
			SFLS_USR_WRDAT = 0x10;
			printf("USR_RD_FULL : %u\n", SFLS_USR_WR_FULL);
			printf("USR_RD_EMPTY: %u\n", SFLS_USR_WR_EMPTY);
			SFLS_USR_WR_EN = 1;
			printf("USR_RD_FULL : %u\n", SFLS_USR_WR_FULL);
			printf("USR_RD_EMPTY: %u\n", SFLS_USR_WR_EMPTY);
			SFLS_USR_WR_EN = 0;
			printf("USR_RD_FULL : %u\n", SFLS_USR_WR_FULL);
			printf("USR_RD_EMPTY: %u\n", SFLS_USR_WR_EMPTY);
#endif
#if 1
		} else if (strcmp(argv[1], "we") == 0) {
			SflsWriteEnable();
#endif
#if 1
		} else if (strcmp(argv[1], "io") == 0) {
			BYTE old_iomode = iomode;
			iomode = atoi(argv[2]);
			if (iomode > 2) {
				printf("Error IOmode (%u)\n", iomode);
				iomode = old_iomode;
			} else {
				printf("IOmode %u -> %u\n", old_iomode, iomode);
			}
#endif
#if 1
		} else if (argc == 3 && strcmp(argv[1], "gap") == 0) {
			UINT getgap = atoi(argv[2]);
			if (getgap == 0) {
#if (EN675_SINGLE==0)
				SFLS_BUS_GAP_EN = 0;
#endif
				SFLS_BUS_GAP = 0;
			} else {
#if (EN675_SINGLE==0)
				SFLS_BUS_GAP_EN = 1;
				SFLS_BUS_GAP = getgap - 1;
#else
				SFLS_BUS_GAP = getgap;
#endif
			}
			SFLS_BUS_REQ = 1;
			while (SFLS_BUS_REQ);
#else
		} else if (strcmp(argv[1], "gap") == 0) {
			BYTE old_gap = gap;
			gap = atoi(argv[2]);
			if (gap > 0xf) {
				printf("Error GAP (%u)\n", gap);
				gap = old_gap;
			} else {
				printf("GAP %u -> %u\n", old_gap, gap);
			}
#endif
		} else if (strcmp(argv[1], "clk") == 0) {
			if (argc == 3) {
				BYTE old_clk = SFLS_IO_CLKDIV;
				SFLS_IO_CLKDIV = atoi(argv[2]);
				printf("Set SFLS_IO_CLKDIV = %u -> %u\n", old_clk, SFLS_IO_CLKDIV);
			} else {
				printf("Get SFLS_IO_CLKDIV = %u\n", SFLS_IO_CLKDIV);
			}
#if 0
		} else if (strcmp(argv[1], "t") == 0) {
			// Erase 후 즉시 Write 할 때 첫번째 PP가 안써지는 문제 테스트용...
			BYTE *p8Base = (BYTE *)SFLS_BASE;
			printf("Test address: %u\n", (UINT)(intptr_t)p8Base);

			hwflush_dcache_range((ulong)sfls_data.data, 4096);
			sfls_create_random(sfls_data.data, nBufferSize);
			hwflush_dcache_range((ulong)sfls_data.data, 4096);

			hwflush_dcache_range((ulong)p8Base, 4096);

			SflsSectErase((UINT)(intptr_t)p8Base, ENX_YES);
			BDmaMemCpy_rtos(0, p8Base, sfls_data.data, 4096);
#endif
		} else if (argc >= 3 && (strcmp(argv[1], "r") == 0 || strcmp(argv[1], "w") == 0)) {
			const char *strMode[8] = {"Read", "Write"};
			UINT nMode = strcmp(argv[1], "r") == 0 ? 0 : 1; // 0:Read 1:Write
			flprintf("Mode: %s\n", strMode[nMode]);
			UINT saddr = atoi(argv[2]);
			UINT eaddr = saddr;
			if (argc == 4) {
				eaddr = atoi(argv[3]);
			}

			if (saddr >= (SFLS_SIZE/SFLSDATA_PP_SIZE) || eaddr >= (SFLS_SIZE/SFLSDATA_PP_SIZE)) {
				_Rprintf("Error offset(%lu~%lu) (range:0~%lu)\n", saddr, eaddr, (SFLS_SIZE/SFLSDATA_PP_SIZE)-1);
				return 0;
			}

			for (UINT i = saddr; i <= eaddr; i++) {
				BYTE *p8Base = ((BYTE *)SFLS_BASE + (i * SFLSDATA_PP_SIZE));
				printf("SFLS %s Addr(0x%08lX) Dst(0x%08lX)\n", strMode[nMode], (intptr_t)p8Base, (intptr_t)sfls_data.data);
				if (nMode == 0) { // Read
					// copy read
					hwflush_dcache_range((ulong)sfls_data.data, SFLSDATA_PP_SIZE);
					BDmaMemCpy_rtos(0, sfls_data.data, (BYTE *)p8Base, SFLSDATA_PP_SIZE);

					// direct read
					hwflush_dcache_range((ulong)p8Base, SFLSDATA_PP_SIZE);

					hexCmpDump("SFLS Read(Direct/Copy)", p8Base, sfls_data.data, SFLSDATA_PP_SIZE);
				} else { // Write
					hwflush_dcache_range((ulong)sfls_data.data, SFLSDATA_PP_SIZE);
					sfls_create_random(sfls_data.data, SFLSDATA_PP_SIZE);
					hwflush_dcache_range((ulong)sfls_data.data, SFLSDATA_PP_SIZE);
					BDmaMemCpy_rtos(0, p8Base, sfls_data.data, SFLSDATA_PP_SIZE);

					hexDump("SFLS Write", sfls_data.data, SFLSDATA_PP_SIZE);
				}
			}
		} else if (strcmp(argv[1], "wdma") == 0) {
			hwflush_dcache_range((ulong)sfls_data.data, 4096);
			sfls_create_random(sfls_data.data, nBufferSize);
			hwflush_dcache_range((ulong)sfls_data.data, 4096);

			ULONG a = BenchTimeStart();
			ULONG t1 = BenchTimeStart();
			UINT tend;
			for (int i = 0; i < 4096; i++) {
				BYTE *p8Base = ((BYTE *)SFLS_BASE + (i * 4096));
				BDmaMemCpy_rtos(0, p8Base, sfls_data.data, 4096);
				if (i % 256 == 0) {
					tend = BenchTimeStop(t1);
					printf("%8u/%8u ing... %u%%, %u us\n", i, 4096, (i * 100) / 4096, tend);
					t1 = BenchTimeStart();
				}
			}
			UINT end = BenchTimeStop(a);
			int se = end / 1000 / 1000;
			char buf[64] = {0};
			snprintf(buf, 64, "%.2f", (SFLS_SIZE/1000.0) / se);
			printf("Time: %u.%us, Speed: %sKbyte/s\n", se, (end / 1000) % 1000, buf);
		} else if (strcmp(argv[1], "e") == 0) {
			if (argc == 3) {
				if (strcmp("all", argv[2]) == 0) {
					printf("SFLS all erase");
					SflsChipErase(ENX_NO);
					ULONG a = BenchTimeStart();
					while (SflsGetUsrreq() == 1) {
						vTaskDelay(100);
						printf(".");
					}
					UINT end = BenchTimeStop(a);
					_Gprintf("done!\n");
					int se = end / 1000 / 1000;
					char buf[64] = {0};
					snprintf(buf, 64, "%.2f", (SFLS_SIZE/1000.0) / se);
					printf("Time: %u.%us, Speed: %sKbyte/s\n", se, (end / 1000) % 1000, buf);
					return 0;
				}
			}

			UINT eaddr = atoi(argv[2]) * 4096;
			//SflsSectErase(eaddr, ENX_YES);

			SflsSectErase(eaddr, ENX_NO);
			ULONG a = BenchTimeStart();
			while (SflsGetUsrreq() == 1){
				SflsReadStatus();
			}
			UINT end = BenchTimeStop(a);
			printf("Time: %uus\n", end);

			//UINT eaddr = atoi(argv[2]);
			//SflsSect64KErase(eaddr, ENX_YES);
			printf("SFLS data erase(idx:%u)(addr:0x%08X~0x%08X)\n", atoi(argv[2]), SFLS_BASE + eaddr, SFLS_BASE + (eaddr + 4096) - 1);
#if 1
#if 0
		} else if (strcmp(argv[1], "start") == 0) {
			if (sflsitem.taskHandle != NULL) {
				printf("SFLS Auto Test already!\n");
				return 0;
			}

			UINT u32TestBlock = 1024;
			UINT nLoop = 100;
			if (argc == 3) {
				nLoop = atoi(argv[2]);
			}
			if (argc == 4) {
				u32TestBlock = atoi(argv[3]);
				if (u32TestBlock > 1024) {
					printf("Max Test Block => 1024 / (input:%u)\n", u32TestBlock);
					return 0;
				}
			}

			sflsitem.u8Close = 0;
			sflsitem.u64BufSize = SFLSDATA_PP_SIZE * u32TestBlock + SFLSDATA_PP_SIZE;
			sflsitem.u32TestCount = nLoop; // 반복 횟수 자체
			sflsitem.u32TestBlock = u32TestBlock; // 한번에 Write/Read할 단위 1(512B) ~ 1024(512KB)
			sflsitem.taskHandle = vTaskCreate("SflsT", SflsTestTask, NULL, LV3_STACK_SIZE, LV4_TASK_PRIO);
#endif
#if 1
		} else if (strcmp(argv[1], "ws") == 0) {
			if (sflsitem.taskHandle != NULL) {
				printf("SFLS Auto Test already!\n");
				return 0;
			}

			UINT u32Flag = 0;
			UINT u32TestBlock = SFLS_SIZE / SFLSDATA_PP_SIZE;
			if (argc == 3) {
				if (strcmp("only", argv[2]) == 0) {
					u32Flag = 1;
				} else {
					u32TestBlock = atoi(argv[2]);
					if (u32TestBlock > (SFLS_SIZE / SFLSDATA_PP_SIZE)) {
						printf("Max Test Block => %u / (input:%u)\n", SFLS_SIZE / SFLSDATA_PP_SIZE, u32TestBlock);
						return 0;
					}
				}
			}

			sflsitem.u8Close = 0;
			sflsitem.u32Flag = u32Flag;
			sflsitem.u64BufSize = SFLSDATA_PP_SIZE * 2;
			sflsitem.u32TestCount = u32TestBlock;
			sflsitem.u32TestBlock = 0;
			sflsitem.taskHandle = vTaskCreate("SflsWT", SflsWriteTestTask, NULL, LV3_STACK_SIZE, LV4_TASK_PRIO);
#endif
		} else if (strcmp(argv[1], "rs") == 0) {
			if (sflsitem.taskHandle != NULL) {
				printf("SFLS Auto Test already!\n");
				return 0;
			}

			UINT u32TestBlock = 4096;
			UINT nLoop = 100;
			if (argc == 3) {
				nLoop = atoi(argv[2]);
			}
			if (argc == 4) {
				u32TestBlock = atoi(argv[2]);
				if (u32TestBlock > 4096) {
					printf("Max Test Block => 4096 / (input:%u)\n", u32TestBlock);
					return 0;
				}
			}

			sflsitem.u8Close = 0;
			sflsitem.u64BufSize = SFLSDATA_PP_SIZE * u32TestBlock + SFLSDATA_PP_SIZE;
			sflsitem.u32TestCount = nLoop; // 반복 횟수 자체
			sflsitem.u32TestBlock = u32TestBlock; // 한번에 Read할 단위 1(512B) ~ 2048(1024KB)
			sflsitem.taskHandle = vTaskCreate("SflsRT", SflsReadTestTask, NULL, LV3_STACK_SIZE, LV4_TASK_PRIO);
		} else if (strcmp(argv[1], "stop") == 0) {
#if 1
			sflsitem.u8Close = 1;
#else
			if (sflsitem.arrSrc) {
				vPortFree(sflsitem.arrSrc);
				sflsitem.arrSrc = NULL;
			}
			if (sflsitem.arrDst) {
				vPortFree(sflsitem.arrDst);
				sflsitem.arrDst = NULL;
			}
			if (sflsitem.taskHandle) {
				vTaskDelete(sflsitem.taskHandle);
				sflsitem.taskHandle = NULL;
			}
#endif
#endif
		} else if (strcmp(argv[1], "wbin") == 0) {
			BYTE *p8WBase = (BYTE *)SFLS_BASE + 0;//0xC8000;
			BYTE *p8eBase = p8WBase;

			BYTE *binbase = (BYTE *)BOOT_BIN;
			UINT binsize = BOOT_BIN_LEN;

//			binsize = 1214464; // 256의 배수...

			printf("binary copy...: %ubyte\n", binsize);

			for (int i = 0 ; i < binsize; i += 4096) {
				SflsSectErase(((UINT)(intptr_t)p8eBase) + i, ENX_YES);
			}
			printf("Erase Done!!\n");

//			BDmaMemCpy_rtos(0, p8WBase, (BYTE *)binbase, binsize);
			for (int i = 0 ; i < binsize; i += 256) {
				BDmaMemCpy_rtos(0, p8WBase+i, (BYTE *)binbase+i, 256);
			}

			printf("Write Done!\n");
#if 0
			BYTE *p8RBase = pvPortMalloc(EN675_DDR_INIT_BIN_LEN + 64);
			if(p8RBase == NULL) {
				printf("Error!\n");
				while(1);
			}

			hwflush_dcache_range((ulong)p8RBase, EN675_DDR_INIT_BIN_LEN);

			BDmaMemCpy_rtos(0, p8RBase, (BYTE *)(intptr_t)startAddr, SFLSDATA_PP_SIZE*readCount);
#else
			hwflush_dcache_range((ulong)p8WBase, binsize);
#endif
			int errchk_cp = memcmp(binbase, p8WBase, binsize);
			printf("memcmp Done!(%d)\n", errchk_cp);

		} else {
			Shell_Unknown();
		}
	}
	return 0;
}
