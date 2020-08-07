#include "dev.h"

#ifdef __AUDIO__
#ifdef __AUDIO_TLV320AIC3206__
#include "tlv320aic3206.h"

typedef struct {
	ENX_SWITCH status;
	char volume;	
} tlv320aic3206_state;

static tlv320aic3206_state tlv320aic3206_info = {
	.status = ENX_OFF,
	.volume = 0x00,	
};

const BYTE TLV320AIC3206_SetupA[][2] =
{
	//	Software Reset
	{0x00, 0x00},	//	Select Page 0
	{0x01, 0x01},	//	Software Reset
	{0xFE, 0x01},	//	Delay 1ms

	{0x00, 0x01},	//	Select Page 1
	{0x01, 0x08},	//	Disable weak AVDD to DVDD connection
	{0x02, 0x00},	//	Enable Master Analog Power Control	- Very important
	{0x7B, 0x01},	//	REF charging time = 40ms
	{0xFE, 0x28},	//	Delay 40ms
	{0x7C, 0x06},	//	8/8 CP Sizing (Setup A), Div = 6, 333kHz
	{0x01, 0x0A},	//	CP powered, source = int 8MHz OSC
	{0x0A, 0x00},	//	Full chip CM = 0.9V (Setup A)
	{0x03, 0x00},	//	PTM_P3, High Performance (Setup A)
	{0x04, 0x00},	//	PTM_P3, High Performance (Setup A)

	//	Codec PLL Setting (MCLK 24.576MHz)
#if (PCM_WCLK==PCM_WCLK_8000HZ)
#if (I2S_MASTER_MODE==0)
	//	Fs 8KHz = 24576/2×1×8/3/32/128 = 8
	{0x00, 0x00},	//	00 Select Page 0
	{0x04, 0x03},	//	04 Clock Setting - Multiplexers
	{0x05, 0xA1},	//	05 PLL P&R : P = 0x02, R = 0x01
	{0x06, 0x08},	//	06 PLL J   : J = 0x08
	{0x07, 0x00},	//	07 PLL D MSB : P MSB = 0x00
	{0x08, 0x00}, 	//	08 PLL D LSB : P LSB = 0x00
	{0xFE, 0x0A},	//	Delay 10ms

	//	DAC Setting
	{0x0B, 0x83},	//	11 NDAC = 0x03
	{0x0C, 0xA0},	//	12 MDAC = 0x20 (32d)
	{0x0D, 0x00},	//	13 DAC DOSR MSB Over-sampling: DOSR MSB = 0x00
	{0x0E, 0x80},	//	14 DAC DOST LSB Over-sampling: DOSR LSB = 0x80 (128d)
	{0xFE, 0x01},	//	Delay 1ms

	//	ADC Setting
	{0x12, 0x83},	//	18 NADC = 0x03
	{0x13, 0xA0},	//	19 MADC = 0x20 (32d)
	{0x14, 0x80},	//	20 ADC AOSR = 0x80 (128d)
	{0xFE, 0x01},	//	Delay 1ms
#else
	{0x00, 0x00},	//	00 Select Page 0
#if 0
	{0x04, 0x00},	//	04 Clock Setting - Multiplexers(MCLK pin is CODEC_CLKIN)
#else
	{0x04, 0x02},	//	04 Clock Setting - Multiplexers(GPIO pin is CODEC_CLKIN)
	{0x34, 0x04},	//  52 GPIO mode
#endif
	{0xFE, 0x0A},	//	Delay 10ms
#if 1	//	Fs 8KHz = 24576/2/12/128 = 8
	//	DAC Setting
	{0x0B, 0x82},	//	11 NDAC = 0x02
	{0x0C, 0x8C},	//	12 MDAC = 0x0C (12d)
	{0x0D, 0x00},	//	13 DAC DOSR MSB Over-sampling: DOSR MSB = 0x00
	{0x0E, 0x80},	//	14 DAC DOST LSB Over-sampling: DOSR LSB = 0x80 (128d)
	{0xFE, 0x01},	//	Delay 1ms

	//	ADC Setting
	{0x12, 0x82},	//	18 NADC = 0x02
	{0x13, 0x8C},	//	19 MADC = 0x0C (12d)
	{0x14, 0x80},	//	20 ADC AOSR = 0x00 (128d)
	{0xFE, 0x01},	//	Delay 1ms
#else	//	Fs 8KHz = 24576/1/12/256 = 8
	//	DAC Setting
	{0x0B, 0x81},	//	11 NDAC = 0x01
	{0x0C, 0x8C},	//	12 MDAC = 0x0C (12d)
	{0x0D, 0x01},	//	13 DAC DOSR MSB Over-sampling: DOSR MSB = 0x01
	{0x0E, 0x00},	//	14 DAC DOST LSB Over-sampling: DOSR LSB = 0x00 (256d)
	{0xFE, 0x01},	//	Delay 1ms

	//	ADC Setting
	{0x12, 0x81},	//	18 NADC = 0x01
	{0x13, 0x8C},	//	19 MADC = 0x0C (12d)
	{0x14, 0x00},	//	20 ADC AOSR = 0x00 (256d)
	{0xFE, 0x01},	//	Delay 1ms
#endif
#endif
#endif

#if (PCM_WCLK==PCM_WCLK_16000HZ)
#if (I2S_MASTER_MODE==0)
	//	Fs 16KHz = 24576/2×1×16/3/32/128 = 16
	{0x00, 0x00},	//	00 Select Page 0
	{0x04, 0x03},	//	04 Clock Setting - Multiplexers
	{0x05, 0xA1},	//	05 PLL P&R : P = 0x02, R = 0x01
	{0x06, 0x10},	//	06 PLL J   : J = 0x10 (16d)
	{0x07, 0x00},	//	07 PLL D MSB : P MSB = 0x00
	{0x08, 0x00}, 	//	08 PLL D LSB : P LSB = 0x00
	{0xFE, 0x0A},	//	Delay 10ms

	//	DAC Setting
	{0x0B, 0x83},	//	11 NDAC = 0x03
	{0x0C, 0xA0},	//	12 MDAC = 0x20 (32d)
	{0x0D, 0x00},	//	13 DAC DOSR MSB Over-sampling: DOSR MSB = 0x00
	{0x0E, 0x80},	//	14 DAC DOST LSB Over-sampling: DOSR LSB = 0x80 (128d)
	{0xFE, 0x01},	//	Delay 1ms

	//	ADC Setting
	{0x12, 0x83},	//	18 NADC = 0x03
	{0x13, 0xA0},	//	19 MADC = 0x20 (32d)
	{0x14, 0x80},	//	20 ADC AOSR = 0x80 (128d)
	{0xFE, 0x01},	//	Delay 1ms
#else
	{0x00, 0x00},	//	00 Select Page 0
#if 0
	{0x04, 0x00},	//	04 Clock Setting - Multiplexers(MCLK pin is CODEC_CLKIN)
#else
	{0x04, 0x02},	//	04 Clock Setting - Multiplexers(GPIO pin is CODEC_CLKIN)
	{0x34, 0x04},	//  52 GPIO mode
#endif
	{0xFE, 0x0A},	//	Delay 10ms
#if 1	//	Fs 16KHz = 24576/2/6/128 = 16
	//	DAC Setting
	{0x0B, 0x82},	//	11 NDAC = 0x02
	{0x0C, 0x86},	//	12 MDAC = 0x06
	{0x0D, 0x00},	//	13 DAC DOSR MSB Over-sampling: DOSR MSB = 0x00
	{0x0E, 0x80},	//	14 DAC DOST LSB Over-sampling: DOSR LSB = 0x80 (128d)
	{0xFE, 0x01},	//	Delay 1ms

	//	ADC Setting
	{0x12, 0x82},	//	18 NADC = 0x02
	{0x13, 0x86},	//	19 MADC = 0x06
	{0x14, 0x80},	//	20 ADC AOSR = 0x80 (128d)
	{0xFE, 0x01},	//	Delay 1ms
#else	//	Fs 16KHz = 24576/1/6/256 = 16
	//	DAC Setting
	{0x0B, 0x81},	//	11 NDAC = 0x01
	{0x0C, 0x86},	//	12 MDAC = 0x06
	{0x0D, 0x01},	//	13 DAC DOSR MSB Over-sampling: DOSR MSB = 0x01
	{0x0E, 0x00},	//	14 DAC DOST LSB Over-sampling: DOSR LSB = 0x00 (256d)
	{0xFE, 0x01},	//	Delay 1ms

	//	ADC Setting
	{0x12, 0x81},	//	18 NADC = 0x01
	{0x13, 0x86},	//	19 MADC = 0x06
	{0x14, 0x00},	//	20 ADC AOSR = 0x00 (256d)
	{0xFE, 0x01},	//	Delay 1ms
#endif
#endif
#endif

#if (PCM_WCLK==PCM_WCLK_32000HZ)
#if (I2S_MASTER_MODE==0)
	//	Fs 32KHz = 24576/2×1×16/3/16/128 = 32
	{0x00, 0x00},	//	00 Select Page 0

	{0x04, 0x03},	//	04 Clock Setting - Multiplexers
	{0x05, 0xA1},	//	05 PLL P&R : P = 0x02, R = 0x01
	{0x06, 0x10},	//	06 PLL J   : J = 0x10 (16d)
	{0x07, 0x00},	//	07 PLL D MSB : P MSB = 0x00
	{0x08, 0x00}, 	//	08 PLL D LSB : P LSB = 0x00
	{0xFE, 0x0A},	//	Delay 10ms

	//	DAC Setting
	{0x0B, 0x83},	//	11 NDAC = 0x03
	{0x0C, 0x90},	//	12 MDAC = 0x10 (16d)
	{0x0D, 0x00},	//	13 DAC DOSR MSB Over-sampling: DOSR MSB = 0x00
	{0x0E, 0x80},	//	14 DAC DOST LSB Over-sampling: DOSR LSB = 0x80 (128d)
	{0xFE, 0x01},	//	Delay 1ms

	//	ADC Setting
	{0x12, 0x83},	//	18 NADC = 0x03
	{0x13, 0x90},	//	19 MADC = 0x10 (16d)
	{0x14, 0x80},	//	20 ADC AOSR = 0x80 (128d)
	{0xFE, 0x01},	//	Delay 1ms
#else

	{0x00, 0x00},	//	00 Select Page 0
#if 0
	{0x04, 0x00},	//	04 Clock Setting - Multiplexers(MCLK pin is CODEC_CLKIN)
#else
	{0x04, 0x02},	//	04 Clock Setting - Multiplexers(GPIO pin is CODEC_CLKIN)
	{0x34, 0x04},	//  52 GPIO mode
#endif
	{0xFE, 0x0A},	//	Delay 10ms
#if 1	//	Fs 32KHz = 24576/1/6/128 = 32
	//	DAC Setting
	{0x0B, 0x81},	//	11 NDAC = 0x01
	{0x0C, 0x86},	//	12 MDAC = 0x06
	{0x0D, 0x00},	//	13 DAC DOSR MSB Over-sampling: DOSR MSB = 0x00
	{0x0E, 0x80},	//	14 DAC DOST LSB Over-sampling: DOSR LSB = 0x80 (128d)
	{0xFE, 0x01},	//	Delay 1ms

	//	ADC Setting
	{0x12, 0x81},	//	18 NADC = 0x01
	{0x13, 0x86},	//	19 MADC = 0x06
	{0x14, 0x80},	//	20 ADC AOSR = 0x80 (128d)
	{0xFE, 0x01},	//	Delay 1ms
#else	//	Fs 32KHz = 24576/1/3/256 = 32
	//	DAC Setting
	{0x0B, 0x81},	//	11 NDAC = 0x01
	{0x0C, 0x83},	//	12 MDAC = 0x03
	{0x0D, 0x01},	//	13 DAC DOSR MSB Over-sampling: DOSR MSB = 0x01
	{0x0E, 0x00},	//	14 DAC DOST LSB Over-sampling: DOSR LSB = 0x00 (256d)
	{0xFE, 0x01},	//	Delay 1ms

	//	ADC Setting
	{0x12, 0x81},	//	18 NADC = 0x01
	{0x13, 0x83},	//	19 MADC = 0x03
	{0x14, 0x00},	//	20 ADC AOSR = 0x00 (256d)
	{0xFE, 0x01},	//	Delay 1ms
#endif
#endif
#endif

#if (PCM_WCLK==PCM_WCLK_48000HZ)
#if (I2S_MASTER_MODE==0)
	//	Fs 48KHz = 24576/2×1×16/4/16/64 = 48
	{0x00, 0x00},	//	00 Select Page 0

	{0x04, 0x03},	//	04 Clock Setting - Multiplexers
	{0x05, 0xA1},	//	05 PLL P&R : P = 0x02, R = 0x01
	{0x06, 0x10},	//	06 PLL J   : J = 0x10 (16d)
	{0x07, 0x00},	//	07 PLL D MSB : P MSB = 0x00
	{0x08, 0x00}, 	//	08 PLL D LSB : P LSB = 0x00
	{0xFE, 0x0A},	//	Delay 10ms

	//	DAC Setting
	{0x0B, 0x84},	//	11 NDAC = 0x04
	{0x0C, 0x90},	//	12 MDAC = 0x10 (16d)
	{0x0D, 0x00},	//	13 DAC DOSR MSB Over-sampling: DOSR MSB = 0x00
	{0x0E, 0x40},	//	14 DAC DOST LSB Over-sampling: DOSR LSB = 0x40 (64d)
	{0xFE, 0x01},	//	Delay 1ms

	//	ADC Setting
	{0x12, 0x84},	//	18 NADC = 0x04
	{0x13, 0x90},	//	19 MADC = 0x10 (16d)
	{0x14, 0x40},	//	20 ADC AOSR = 0x40 (64d)
	{0xFE, 0x01},	//	Delay 1ms
#else
	//	Fs 48KHz = 24576/1/8/64 = 48
	{0x00, 0x00},	//	00 Select Page 0
#if 0
	{0x04, 0x00},	//	04 Clock Setting - Multiplexers(MCLK pin is CODEC_CLKIN)
#else
	{0x04, 0x02},	//	04 Clock Setting - Multiplexers(GPIO pin is CODEC_CLKIN)
	{0x34, 0x04},	//  52 GPIO mode
#endif
	{0xFE, 0x0A},	//	Delay 10ms

	//	DAC Setting
	{0x0B, 0x81},	//	11 NDAC = 0x01
	{0x0C, 0x88},	//	12 MDAC = 0x08
	{0x0D, 0x00},	//	13 DAC DOSR MSB Over-sampling: DOSR MSB = 0x00
	{0x0E, 0x40},	//	14 DAC DOST LSB Over-sampling: DOSR LSB = 0x40 (64d)
	{0xFE, 0x01},	//	Delay 1ms

	//	ADC Setting
	{0x12, 0x81},	//	18 NADC = 0x01
	{0x13, 0x88},	//	19 MADC = 0x08
	{0x14, 0x40},	//	20 ADC AOSR = 0x40 (64d)
	{0xFE, 0x01},	//	Delay 1ms
#endif
#endif

#if (PCM_WCLK==PCM_WCLK_11025HZ)
	//	Fs 11.025KHz = 24576/2×1×7.35/1/64/128 = 11.025
	{0x00, 0x00},	//	00 Select Page 0
	{0x04, 0x03},	//	04 Clock Setting - Multiplexers
	{0x05, 0xA1},	//	05 PLL P&R : P = 0x02, R = 0x01
	{0x06, 0x07},	//	06 PLL J   : J = 0x07
	{0x07, 0x0E},	//	07 PLL D MSB : P MSB = 0x0E
	{0x08, 0xAC}, 	//	08 PLL D LSB : P LSB = 0xAC (3500d)
	{0xFE, 0x0A},	//	Delay 10ms

	//	DAC Setting
	{0x0B, 0x81},	//	11 NDAC = 0x01
	{0x0C, 0xC0},	//	12 MDAC = 0xC0 (64d)
	{0x0D, 0x00},	//	13 DAC DOSR MSB Over-sampling: DOSR MSB = 0x00
	{0x0E, 0x80},	//	14 DAC DOST LSB Over-sampling: DOSR LSB = 0x80 (128d)
	{0xFE, 0x01},	//	Delay 1ms

	//	ADC Setting
	{0x12, 0x81},	//	18 NADC = 0x01
	{0x13, 0xC0},	//	19 MADC = 0xC0 (64d)
	{0x14, 0x80},	//	20 ADC AOSR = 0x80 (128d)
	{0xFE, 0x01},	//	Delay 1ms
#endif

#if (PCM_WCLK==PCM_WCLK_22050HZ)
	//	Fs 22.05KHz = 24576/2×1×7.35/1/32/128 = 22.05
	{0x00, 0x00},	//	00 Select Page 0
	{0x04, 0x03},	//	04 Clock Setting - Multiplexers
	{0x05, 0xA1},	//	05 PLL P&R : P = 0x02, R = 0x01
	{0x06, 0x07},	//	06 PLL J   : J = 0x07
	{0x07, 0x0E},	//	07 PLL D MSB : P MSB = 0x0E
	{0x08, 0xAC}, 	//	08 PLL D LSB : P LSB = 0xAC (3500d)
	{0xFE, 0x0A},	//	Delay 10ms

	//	DAC Setting
	{0x0B, 0x81},	//	11 NDAC = 0x01
	{0x0C, 0xA0},	//	12 MDAC = 0xA0 (32d)
	{0x0D, 0x00},	//	13 DAC DOSR MSB Over-sampling: DOSR MSB = 0x00
	{0x0E, 0x80},	//	14 DAC DOST LSB Over-sampling: DOSR LSB = 0x80 (128d)
	{0xFE, 0x01},	//	Delay 1ms

	//	ADC Setting
	{0x12, 0x81},	//	18 NADC = 0x01
	{0x13, 0xA0},	//	19 MADC = 0xA0 (32d)
	{0x14, 0x80},	//	20 ADC AOSR = 0x80 (128d)
	{0xFE, 0x01},	//	Delay 1ms
#endif

#if (PCM_WCLK==PCM_WCLK_44100HZ)
	//	Fs 44.1KHz = 24576/2×1×7.35/1/16/128 = 44.1
	{0x00, 0x00},	//	00 Select Page 0
	{0x04, 0x03},	//	04 Clock Setting - Multiplexers
	{0x05, 0xA1},	//	05 PLL P&R : P = 0x02, R = 0x01
	{0x06, 0x07},	//	06 PLL J   : J = 0x07
	{0x07, 0x0E},	//	07 PLL D MSB : P MSB = 0x0E
	{0x08, 0xAC}, 	//	08 PLL D LSB : P LSB = 0xAC (3500d)
	{0xFE, 0x0A},	//	Delay 10ms

	//	DAC Setting
	{0x0B, 0x81},	//	11 NDAC = 0x01
	{0x0C, 0x90},	//	12 MDAC = 0x10 (16d)
	{0x0D, 0x00},	//	13 DAC DOSR MSB Over-sampling: DOSR MSB = 0x00
	{0x0E, 0x80},	//	14 DAC DOST LSB Over-sampling: DOSR LSB = 0x80 (128d)
	{0xFE, 0x01},	//	Delay 1ms

	//	ADC Setting
	{0x12, 0x81},	//	18 NADC = 0x01
	{0x13, 0x90},	//	19 MADC = 0x10 (16d)
	{0x14, 0x80},	//	20 ADC AOSR = 0x80 (128d)
	{0xFE, 0x01},	//	Delay 1ms
#endif

	//    Codec Interface
#if (I2S_MASTER_MODE==0)
#if (PCM_BIT==PCM_BIT_16)
	{0x1B, 0x0C},    //    27 Codec Interface Control : EN675 Slave I2S + 16bit + BCLK out + WCLK out
	{0x1D, 0x05},    //    29 Codec Interface Control2 : BDIV_CLKIN = DAC_MOD_CLK
	{0x1E, 0x84},    //    30 BCLK_N_VAL : BCLK N-divider is powered up, BCLK divider N = 04h
#elif (PCM_BIT==PCM_BIT_32)
	{0x1B, 0x3C},    //    27 Codec Interface Control : EN675 Slave I2S + 32bit + BCLK out + WCLK out
	{0x1D, 0x05},    //    29 Codec Interface Control2 : BDIV_CLKIN = DAC_MOD_CLK
	{0x1E, 0x82},    //    30 BCLK_N_VAL : BCLK N-divider is powered up, BCLK divider N = 02h
#endif
#else
#if (PCM_BIT==PCM_BIT_16)
	{0x1B, 0x00},    //    27 Codec Interface Control : EN675 Master I2S + 16bit + BCLK in + WCLK in
	{0x1D, 0x05},    //    29 Codec Interface Control2 : BDIV_CLKIN = DAC_MOD_CLK
	{0x1E, 0x84},    //    30 BCLK_N_VAL : BCLK N-divider is powered up, BCLK divider N = 04h
#elif (PCM_BIT==PCM_BIT_32)
	{0x1B, 0x30},    //    27 Codec Interface Control : EN675 Master I2S + 32bit + BCLK in + WCLK in
	{0x1D, 0x05},    //    29 Codec Interface Control2 : BDIV_CLKIN = DAC_MOD_CLK
	{0x1E, 0x82},    //    30 BCLK_N_VAL : BCLK N-divider is powered up, BCLK divider N = 02h
#endif
#endif
	{0xFE, 0x20},    //    Delay 1ms

	//	Signal Processing Settings
	{0x00, 0x00},	//	Select Page 0
	{0x3C, 0x01},	//	Set the DAC Mode to PRB_P1 (Setup A)

	//	Output Channel Configuration
	{0x00, 0x01},	//	Select Page 1
	{0x0C, 0x08},	//	Route LDAC to HPL
	{0x0D, 0x08},	//	Route RDAC to HPR
	{0x0E, 0x03},	//	14
	{0x0F, 0x03},	//	15
	{0x00, 0x00},	//	Select Page 0
	{0x3F, 0xD6},	//	Power up LDAC/RDAC
	{0x00, 0x01},	//	Select Page 1
	{0x7D, 0x13},	//	GCHP Mode, OC for all, HP Sizing (Setup A)
	{0x10, 0x00},	//	Unmute HPL driver, 0dB Gain (Setup A)
	{0x11, 0x00},	//	Unmute HPR driver, 0dB Gain (Setup A)
	{0x16, 0x32},
	{0x17, 0x32},
	{0x09, 0x3C},	//	Power up HPL/HPR drivers
	{0x09, 0x30},	//	Power up HPL/HPR drivers
	{0xFE, 0x03},	//	Delay 3 millisecond   // f 30 02 xxxxx1xx # Wait for offset correction to finish
	{0x00, 0x00},	//	Select Page 0
	{0x40, 0x00},	//	Unmute LDAC/RDAC
	{0x41, 0xC0},	//	Left DAC Channel Digital Volume Control Register
	{0x42, 0xC0},	//	Right DAC Channel Digital Volume Control Register

//	MIC Setting
	{0x00, 0x00},	//	Select Page 0
	{0x3D, 0x01},	//	Select ADC PRB_R1
	{0xFE, 0x20},	//	Delay 32ms

	{0x00, 0x01},	//	Select Page 1
	{0x01, 0x08},	//	1	Disable weak connection of AVDD with DVDD
	{0x02, 0x00},	//	2	Enable Master Analog Power Control
	{0x0A, 0x00},	//	10	Set the input common mode voltage to 0.9V
	{0x3D, 0xFF},	//	61	Select ADC PTM_R1
	{0x47, 0x32},	//	71	Set MicPGA startup delay to 3.1ms
	{0x7B, 0x01},	//	123	Set the REF charging time to 40ms
	{0x33, 0x70},	//
	{0x34, 0x30},	//	52	Route IN2L to LEFT_P with 20K input impedance
	{0x36, 0x03},	//	54	Route Common Mode to LEFT_M with impedance of 20K
	{0x37, 0x30},	//	55	Route IN2R to RIGHT_P with input impedance of 20K
	{0x39, 0x03},	//	56	Route Common Mode to RIGHT_M with impedance of 20K
	{0x3B, 0x00},	//	59	Unmute Left MICPGA, Gain selection of 6dB to make channel gain 0dB
					//		Register of 6dB with input impedance of 20K => Channel Gain of 0dB
	{0x3C, 0x00},	//	60	Unmute Right MICPGA, Gain selection of 6dB to make channel gain 0dB
					//		Register of 6dB with input impedance of 20K => Channel Gain of 0dB
	{0xFE, 0x0C},	//	Delay 1ms

	{0x00, 0x00},	//	Select Page 0
	{0x51, 0xC0},	//	Power up Left and Right ADC Channels
	{0x52, 0x00},	//	Unmute Left and Right ADC Digital Volume Control
	{0xFE, 0x20},	//	Delay 20ms

};	

static UINT tlv320aic3206_check(void)
{
	return I2cCheck(AUDIO_I2C_CH, TLV320AIC3206_I2C_WRITE);
}

void tlv320aic3206_delay(UINT xms)
{
	WaitXms(xms);
}

ENX_OKFAIL tlv320aic3206_write_reg(BYTE reg, BYTE data)
{
	while (I2cWrite(AUDIO_I2C_CH, TLV320AIC3206_I2C_WRITE, 0, 0));
	if (I2cWrite(AUDIO_I2C_CH, reg, 0, 0)) return ENX_FAIL;
	if (I2cWrite(AUDIO_I2C_CH, data, 1, 0)) return ENX_FAIL;
	return ENX_OK;
}

static ENX_OKFAIL tlv320aic3206_read_reg(BYTE reg, BYTE *data)
{
	while (I2cWrite(AUDIO_I2C_CH, TLV320AIC3206_I2C_WRITE, 0, 0));
	if (I2cWrite(AUDIO_I2C_CH, reg, 1, 1)) return ENX_FAIL;
	while (I2cWrite(AUDIO_I2C_CH,TLV320AIC3206_I2C_READ, 0, 0));
	*data = I2cRead(AUDIO_I2C_CH, 1, 1);
	return ENX_OK;
} 

void tlv320aic3206_print_name(void)
{
	_Gprintf("  >>TLV320AIC3206 Connected...\n");
	_Gprintf("  >>TLV320AIC3206 is set to %ubit %uHz.\n", PCM_BIT, PCM_WCLK);
}

void tlv320aic3206_init(void)
{
	if (tlv320aic3206_check() == ENX_FAIL) {
		_Rprintf("  >>TLV320AIC3206 Not Connected...\n");
	} else {
		tlv320aic3206_info.status = ENX_ON;
		tlv320aic3206_print_name();

		int size = sizeof(TLV320AIC3206_SetupA) / sizeof(TLV320AIC3206_SetupA[0]);
		for (int i = 0; i < size; i++) {
			if (TLV320AIC3206_SetupA[i][0] == 0xFE) {
				tlv320aic3206_delay((UINT)TLV320AIC3206_SetupA[i][1]);
			} else {
				tlv320aic3206_write_reg(TLV320AIC3206_SetupA[i][0],TLV320AIC3206_SetupA[i][1]);
#if 0
				BYTE u8Read;
				tlv320aic3206_read_reg(TLV320AIC3206_SetupA[i][0], &u8Read);
				if (u8Read != TLV320AIC3206_SetupA[i][1]) {
					printf("  >>TLV320AIC3206 Setting Error. Addr(0x%02X) Data(0x%02X/0x%02X)\n", TLV320AIC3206_SetupA[i][0], TLV320AIC3206_SetupA[i][1], u8Read);

					for (int j = 0; j < 5; j++) {
						tlv320aic3206_write_reg(TLV320AIC3206_SetupA[i][0],TLV320AIC3206_SetupA[i][1]);
						tlv320aic3206_read_reg(TLV320AIC3206_SetupA[i][0], &u8Read);
						if (u8Read != TLV320AIC3206_SetupA[i][1]) {
							printf("  >>TLV320AIC3206 Setting Retry(%u) Error. Addr(0x%02X) Data(0x%02X/0x%02X)\n", j, TLV320AIC3206_SetupA[i][0], TLV320AIC3206_SetupA[i][1], u8Read);
						} else {
							printf("  >>TLV320AIC3206 Setting Retry OK\n");
							break;
						}
					}
				} else {
//					printf("  >>TLV320AIC3206 Setting OK\n");
				}
#endif
//				printf("Read Adr = %08x  Reg = %08x\n", TLV320AIC3206_SetupA[i][0], u8Read);
			}
		}
	}
}
#endif
#endif
