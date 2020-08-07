//*************************************************************************************************
// Sdcard task
//*************************************************************************************************
#include "dev.h"

#if (LOAD_FS_SDCARD==1)

#include "enx_freertos.h"

#include "enx_file.h"
#include "sdcard.h"
#include "muxer_videnc.h"

#define ENX_SDdetect_DEBUG			// printf �ּ���

#ifdef ENX_SDdetect_DEBUG
	#define tprintf(fmt, args...) do { printf("%04d %s : "fmt, __LINE__, __func__, ##args); } while(0);
#else
	#define tprintf(fmt, args...) do {} while(0);
#endif

static UINT bSDState = sd_OFF;
static int bSD_Format = 0;

int SDcardGetFormatState(void)
{
	return bSD_Format;
}

void SDcardSetFormat(void)
{
	bSD_Format = ENX_ON;
}

static void SDcardFormatFail(void)
{
	bSD_Format = -1;
}

static void SDcardFormatDone(void)
{
	bSD_Format = ENX_OFF;
}

void SdcardInit(void)
{
	char sdname[8] = {0};
	char sdsize[12] = {0};
	int flag = 1;
init_start:
	vTaskDelay(10);
	FRESULT fres;
	bSDState = sd_INIT;
	if (SdioCdInitProcess() == ENX_FAIL) {
		printf("SD card IN(init fail)\n");
		bSDState = sd_ERR;
		goto init_end;
	}

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	return;
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

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
			bSDState = sd_READY;
			break;
		default:
			flag = 2;
			printf("SD card IN(mount fail:err%d)\n", fres);
			bSDState = sd_ERR;
			break;
	}
#endif

init_err:
	if (flag == 1) {
		flag = 2;
		goto init_start;
	}

init_end:
	return;
}

void SdcardTask(void *pvParameters)
{
	FRESULT res;
	UINT oldSdSviSave = gtUser.bSdVidSave;

	vTaskDelay(200); // Log ��ġ�� ������

	while (1) {
		UINT SDDet = SdioCdDet();
		if (SDDet == 0) { // SD card IN
			switch (bSDState) {
			case sd_OFF:	// Initialization... This is done by "SDcardInit"
				SdcardInit();
				break;
			case sd_INIT:	// Do nothing until initialization is finished.
				break;
			case sd_READY:
				drive_init(DEV_SD);
				muxer_videnc_init();
				bSDState = sd_IDLE;
				//break;	// next Idle state  // @suppress("No break at end of case")
			case sd_IDLE:	// sd_IDLE state by "SDcardInit" or "sdsave off"
				if (SDcardGetFormatState() == ENX_ON) {
					UINT workbuf_len = 0x8000;
					BYTE *workbuf = pvPortMalloc(workbuf_len);
					if (workbuf) {
						char strDrive[4] = {0};
						sprintf(strDrive, "%d:", DEV_SD);
						res = f_mkfs(strDrive, FM_FAT32, FAT_BLOCK_SD, workbuf, workbuf_len);
						if (res != FR_OK) {
							printf("Error1\n");
							SdioCdClockDown();
							res = f_mkfs(strDrive, FM_FAT32, FAT_BLOCK_SD, workbuf, workbuf_len);
							if (res != FR_OK) {
								printf("Error2\n");
							}
						}

						if (res == FR_OK) {
							res = drive_init(DEV_SD);
							if (res != FR_OK) {
								printf("Error3\n");
							}
						}

						if (res == FR_OK) {
							printf("SD Format & Init OK!\n");
							gtUser.bSdVidSave = oldSdSviSave;
							SDcardFormatDone();
						} else {
							printf("SD Format & Init Fail: %s\n", put_rc(res));
							SDcardFormatFail();
						}

						vPortFree(workbuf);
					} else {
						printf("SD Format & Init Fail: %s\n", "Malloc fail");
					}
				}

				if (gtUser.bSdVidSave == ENX_ON) { // user command(sdsave on)
					bSDState = sd_SAVE;
					printf("SD save Start!\n");
					drive_init(DEV_SD);
					muxer_videnc_init();
					muxer_videnc_go(eRecNormal);
				}
				break;
			case sd_SAVE:	// sd_SAVE state by "SDcardInitTask" or "sdsave on"
				if (SDcardGetFormatState() == ENX_ON) {
					oldSdSviSave = gtUser.bSdVidSave;
					if (gtUser.bSdVidSave == ENX_ON) {
						gtUser.bSdVidSave = ENX_OFF;
					}
				}

				if (gtUser.bSdVidSave == ENX_OFF) { // user command(sdsave off)
					bSDState = sd_IDLE;
#ifdef GPIO_RECORDING_LED
					GpioSetLo(GPIO_RECORDING_LED);
#endif
					printf("SD save Stop\n");
					gVidenc[eRecNormal].state = VIDENC_EXIT;
#if (FAT_SDSAVE_EVENT==1)
					gVidenc[eRecEvent].state = VIDENC_EXIT;
#endif
				}
				break;
			case sd_ERR:
				printf("SD state Error!\n");
				bSDState = sd_ERR_IDLE;
				break;
			case sd_ERR_IDLE:
				break;
			}
		} else if (SDDet == 1 && bSDState != sd_OFF) { // SD card OUT
			bSDState = sd_OFF;
			printf("SD card OUT\n");
		} else if (bSDState == sd_ERR) {
			static int cnt = 0;
			cnt++;
			if (cnt == 10) {
				printf("SDcard Error / reload\n");
				bSDState = sd_OFF;
				cnt = 0;
			}
		}
		vTaskDelay(5);
	}
	UNUSED(pvParameters);
}

int getSDState(void)
{
	return bSDState;
}

void getSDGBSizeT(char *buf)
{
	int i = 0;
	UINT rem[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	UINT nSDSize = SdioCdGetSize();
	UINT nSDINTpart = nSDSize / 1024;
	UINT nSDFRACpart = nSDSize % 1024;
	for (i = 1; i <= 10; i++) {
		if (nSDFRACpart < rem[i]*1024/10) {
			nSDFRACpart = rem[i-1];
			break;
		}
	}
	sprintf(buf, "%d.%dGB", nSDINTpart, nSDFRACpart);
}

void getSDGBSizeU(UINT *buf)
{
	UINT nSDSize = SdioCdGetSize();
	nSDSize = nSDSize / 1024;
	if (nSDSize <= 8) {
		*buf = 8;	// 8GB
	} else if (nSDSize <= 16) {
		*buf = 16;	// 16GB
	} else if (nSDSize <= 32) {
		*buf = 32;	// 32GB
	} else if (nSDSize <= 64) {
		*buf = 64;	// 64GB
	} else if (nSDSize <= 128) {
		*buf = 128;// 128GB
	} else if (nSDSize <= 256) {
		*buf = 256;// 256GB
	} else if (nSDSize <= 512) {
		*buf = 512;// 512GB
	} else if (nSDSize <= 1024) {
		*buf = 1024;// 1024GB
	} else {
		*buf = 0;
		printf("Size Check Error(%dGB?)\n", nSDSize);
	}
}

ENX_OKFAIL getSDTimeCheck(void)
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
