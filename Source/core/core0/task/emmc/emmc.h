#ifndef _EMMC_H_
#define _EMMC_H_

// #include "sdio_emmc.h"

//*************************************************************************************************
// Misc
//-------------------------------------------------------------------------------------------------
// 
enum {
	emmc_OFF = 0,
	emmc_INIT = 1,
	emmc_READY = 2,
	emmc_IDLE = 3,
	emmc_SAVE = 4,
	emmc_ERR = 5,
	emmc_ERR_IDLE = 6
};

//*************************************************************************************************
// Extern
//-------------------------------------------------------------------------------------------------
// Function
extern int EmmcGetFormatState(void);
extern void EmmcSetFormat(void);
extern void EmmcTask(void *pvParameters);
extern int getEmmcState(void);
extern void getEmmcGBSizeT(char *buf);
extern void getEmmcGBSizeU(UINT *buf);
extern ENX_OKFAIL getEmmcTimeCheck(void);

//-------------------------------------------------------------------------------------------------
// Variable


#endif // _EMMC_H_
