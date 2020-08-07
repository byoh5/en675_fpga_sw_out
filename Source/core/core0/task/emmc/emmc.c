//*************************************************************************************************
// EMMC task
//*************************************************************************************************
#include "dev.h"

#if (LOAD_FS_EMMC==1)

#include "enx_freertos.h"

#include "enx_file.h"
#include "emmc.h"
#include "muxer_videnc.h"

#define ENX_EMMCdetect_DEBUG			// printf �ּ���

#ifdef ENX_EMMCdetect_DEBUG
	#define tprintf(fmt, args...) do { printf("%04d %s : "fmt, __LINE__, __func__, ##args); } while(0);
#else
	#define tprintf(fmt, args...) do {} while(0);
#endif

static UINT bEMMCState = emmc_OFF;
static int bEMMC_Format = 0;

int EmmcGetFormatState(void)
{
	return bEMMC_Format;
}

void EmmcSetFormat(void)
{
	bEMMC_Format = ENX_ON;
}

static void EmmcFormatFail(void)
{
	bEMMC_Format = -1;
}

static void EmmcFormatDone(void)
{
	bEMMC_Format = ENX_OFF;
}

void EmmcInit(void)
{
	char sdname[8] = {0};
	char sdsize[12] = {0};
	int flag = 1;
init_start:
	vTaskDelay(10);
	FRESULT fres;
	bEMMCState = emmc_INIT;
	if (SdioEmmcInitProcess() == ENX_FAIL) {
		printf("EMMC IN(init fail)\n");
		bEMMCState = emmc_ERR;
		goto init_end;
	}

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	return;
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
#if 0
	if (flag == 2) {
		SdioCdClockDown();
	}

#if 0
	return;
#else
	fres = drive_in(DEV_SD); // driver mount
#if 0
	if (flag == 1 && fres == FR_NO_FILESYSTEM) { // FS�� ����? Read Fail?
		SdioCdClockDown();
		fres = drive_in(DEV_SD); // driver mount
		if (fres == FR_NO_FILESYSTEM) { // FS�� ���� ����.
			flag = 1;
			SdioCdClockRestore();
		} else {
			flag = 2;
		}
	}
#endif
	switch (fres) {
		case FR_OK:
		case FR_NO_FILESYSTEM:
			SdioCdGetName(sdname);
			getSDGBSizeT(sdsize);
			tprintf("SD card IN(%s, %s)\n", sdname, sdsize);
			fres = drive_init(DEV_SD);
			if (fres != FR_OK)		goto init_err;
			flag = 2;
#if 0
			if (fwupdate_filecheck(DEV_SD, "EN675.bin")) {
				FWUPDATE_INFO* fwinfo = (FWUPDATE_INFO*)pvPortCalloc(1, sizeof(FWUPDATE_INFO));
				sprintf(fwinfo->file_path, "%d:/%s", DEV_SD, "EN675.bin");	// SD�� �߿��� ������ �ö�� �ִ�. �ö�� �ּҸ� �����Ѵ�.
				fwinfo->type = eFWT_SD;				// SD�� �߿��� ������ �ö�� �ִ�.
				fwinfo->is_areachange = DEF_YES;	// fw write �� �������� ���� �����ϱ� ���� area�� ���� �� write�Ѵ�.
				fwinfo->is_bootwrite = DEF_NO;		// boot.bin�� write���� �ʴ´�.
				fwinfo->is_autoreboot = DEF_YES;	// Task ���ο��� ������� �õ��Ѵ�.
				fwinfo->is_malloc = DEF_YES;		// �� ����ü�� malloc �����Ƿ� free�� ���� ����Ǿ���.
				fwinfo->is_encodingstop = DEF_YES;	// Task ���ο��� encoding stop ����� ������.
				vTaskCreate("fwup", fwupdate_Task, fwinfo, JABBU_STACK_SIZE, LV5_TASK_PRIO);
				while (1) {
					int update_ing = fwupdate_process(); // -1:Idle, 0~99:Processing, 100:OK, -100:Fail
					printf("[%d%]", update_ing);
					if (update_ing == 100 || update_ing == -100) {
						break;
					}
					vTaskDelay(50);
				}
			}
			getSDTimeCheck();
#endif
			bEMMCState = emmc_READY;
			break;
		default:
			flag = 2;
			printf("SD card IN(mount fail:err%d)\n", fres);
			bEMMCState = emmc_ERR;
			break;
	}
#endif

init_err:
	if (flag == 1) {
		flag = 2;
		goto init_start;
	}
#endif
init_end:
	return;
}

void EmmcTask(void *pvParameters)
{
	FRESULT res;
//	UINT oldSdSviSave = gtUser.bSdVidSave;

	vTaskDelay(200);

	while (1) {
		UINT EmmcDet = SdioEmmcDet();
		if (EmmcDet == 0) { // Emmc IN
			switch (bEMMCState) {
			case emmc_OFF:	// Initialization... This is done by "EmmcInit"
				EmmcInit();
				break;
			case emmc_INIT:	// Do nothing until initialization is finished.
				break;
			case emmc_READY:
				drive_init(DEV_EMMC);
				bEMMCState = emmc_IDLE;
				//break;	// next Idle state  // @suppress("No break at end of case")
			case emmc_IDLE:	// emmc_IDLE state by "EmmcInit" or "emmc off"
				if (EmmcGetFormatState() == ENX_ON) {
					UINT workbuf_len = 0x8000;
					BYTE *workbuf = pvPortMalloc(workbuf_len);
					if (workbuf) {
						char strDrive[4] = {0};
						sprintf(strDrive, "%d:", DEV_EMMC);
						res = f_mkfs(strDrive, FM_FAT32, FAT_BLOCK_EMMC, workbuf, workbuf_len);
						if (res != FR_OK) {
							printf("Error1\n");
							SdioEmmcClockDown();
							res = f_mkfs(strDrive, FM_FAT32, FAT_BLOCK_EMMC, workbuf, workbuf_len);
							if (res != FR_OK) {
								printf("Error2\n");
							}
						}
#if 0
						if (res == FR_OK) {
							res = drive_init(DEV_EMMC);
							if (res != FR_OK) {
								printf("Error3\n");
							}
						}
#endif
						if (res == FR_OK) {
							printf("EMMC Format & Init OK!\n");
//							gtUser.bSdVidSave = oldSdSviSave;
							EmmcFormatDone();
						} else {
							printf("EMMC Format & Init Fail: %s\n", put_rc(res));
							EmmcFormatFail();
						}

						vPortFree(workbuf);
					} else {
						printf("SD Format & Init Fail: %s\n", "Malloc fail");
					}
				}
				break;
			case emmc_ERR:
				printf("Emmc state Error!\n");
				bEMMCState = emmc_ERR_IDLE;
				break;
			case emmc_ERR_IDLE:
				break;
			}
		} else if (EmmcDet == 1 && bEMMCState != emmc_OFF) { // EMMC OUT
			bEMMCState = emmc_OFF;
			printf("Emmc OUT\n");
		} else if (bEMMCState == emmc_ERR) {
			static int cnt = 0;
			cnt++;
			if (cnt == 10) {
				printf("Emmc Error / reload\n");
				bEMMCState = emmc_OFF;
				cnt = 0;
			}
		}
		vTaskDelay(5);
	}
	UNUSED(pvParameters);
}

int getEmmcState(void)
{
	return bEMMCState;
}

void getEmmcGBSizeT(char *buf)
{
	int i = 0;
	UINT rem[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	UINT nEmmcSize = SdioEmmcGetSize();
	UINT nEmmcINTpart = nEmmcSize / 1024;
	UINT nEmmcFRACpart = nEmmcSize % 1024;
	for (i = 1; i <= 10; i++) {
		if (nEmmcFRACpart < rem[i]*1024/10) {
			nEmmcFRACpart = rem[i-1];
			break;
		}
	}
	sprintf(buf, "%d.%dGB", nEmmcINTpart, nEmmcFRACpart);
}

void getEmmcGBSizeU(UINT *buf)
{
	UINT nEmmcSize = SdioEmmcGetSize();
	nEmmcSize = nEmmcSize / 1024;
	if (nEmmcSize <= 8) {
		*buf = 8;	// 8GB
	} else if (nEmmcSize <= 16) {
		*buf = 16;	// 16GB
	} else if (nEmmcSize <= 32) {
		*buf = 32;	// 32GB
	} else if (nEmmcSize <= 64) {
		*buf = 64;	// 64GB
	} else if (nEmmcSize <= 128) {
		*buf = 128;// 128GB
	} else if (nEmmcSize <= 256) {
		*buf = 256;// 256GB
	} else if (nEmmcSize <= 512) {
		*buf = 512;// 512GB
	} else if (nEmmcSize <= 1024) {
		*buf = 1024;// 1024GB
	} else {
		*buf = 0;
		printf("Size Check Error(%dGB?)\n", nEmmcSize);
	}
}

ENX_OKFAIL getEmmcTimeCheck(void)
{
#if 0
	char strCmpPath[FF_MAX_LFN + 1] = {0};
	char strPath[128] = {0};
	FRESULT fres;
	FILINFO finfo;
	DIR dir;
	int nYear_Old, nMonth_Old, nDay_Old, nHour_Old, nMin_Old, nSec_Old;
	int nYear_New, nMonth_New, nDay_New, nHour_New, nMin_New, nSec_New;
	int nGetRes = 0, nNewDay = 0;
	nYear_New = nMonth_New = nDay_New = nHour_New = nMin_New = nSec_New = 0;

	// ����ð��� �����´�. �� �ð��� RTC�� ����.
	struct tm tmout;
	enx_get_tmtime(gptMsgShare.TIME, &tmout, DEF_YES);
	sprintf(strCmpPath, SAVE_NOR_NAME_FORMAT, tmout.tm_year+1900-2000, tmout.tm_mon+1, tmout.tm_mday, tmout.tm_hour, tmout.tm_min, tmout.tm_sec);

	sprintf(strPath, "%d:/%s", DEV_SD, SD_DIR_NOR);
	fres = f_findfirst(&dir, &finfo, strPath, SAVE_NOR_NAME_PATTERN);
	while (fres == FR_OK && finfo.fname[0]) {
		if (!(finfo.fattrib & AM_DIR)) {
			if (strlen(finfo.fname) == SAVE_FILENAME_LENS) {
				nGetRes = sscanf(finfo.fname, SAVE_NOR_NAME_FORMAT, &nYear_Old, &nMonth_Old, &nDay_Old, &nHour_Old, &nMin_Old, &nSec_Old);
				if (nGetRes == 6) {
					if (strcmp(strCmpPath, finfo.fname) < 0) {
						strcpy(strCmpPath, finfo.fname);
						nYear_New = nYear_Old;
						nMonth_New = nMonth_Old;
						nDay_New = nDay_Old;
						nHour_New = nHour_Old;
						nMin_New = nMin_Old;
						nSec_New = nSec_Old;
						nNewDay = 1;
					}
				}
			}
		}
		fres = f_findnext(&dir, &finfo);
	}
	f_closedir(&dir);

	// ����, ���� �ð��� ���� ������ �������Ϻ��� ���Ŷ��,
	// ���� ������ ���������� +1���� ���� �ð����� �����Ѵ�. -> 60�� �� over�� ���ɼ��� ����, �ʸ� ������ 59�ʷ� �Ѵ�.
	if (nNewDay) {
		if (set_devicetime(TimeZone_LOC, nYear_New+2000, nMonth_New, nDay_New, nHour_New, nMin_New, 59) == ENX_FAIL) {
			printf("time set fail\n");
			return ENX_FAIL;
		}
		return ENX_OK;
	}
	return ENX_FAIL;
#else
	ENX_ASSERT(0);
#endif
}
#endif
