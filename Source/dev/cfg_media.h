//******************************************************************************
//	Copyright(c) Eyenix Co.,Ltd. 2003-
//
//	File Name:     cfg_media.h
//	Description:   EN675 Network configure
//	Author:        Team 2
//
//	Note:          Here you will check the settings.
//
//	Ver   Date   Author  Changes
//	---  ------  ------  -------
//	0.1  190530  hjlee   support EN675
//------------------------------------------------------------------------------
#ifndef __CFG_MEDIA_H__
#define __CFG_MEDIA_H__

////////////////////////////////////////////////////////////////////////////////
// ISP
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ISP Default Image Size & Default Video Setting
#define SENSOR_SIZE_W					1920
#define SENSOR_SIZE_H					1080

////////////////////////////////////////////////////////////////////////////////
// DownScaler Switch(0:Stream1 1:Stream2 2:Stream3 3:Stream4)
#define HW_DS0							0
#define HW_DS1							1
#define HW_DS2							2
#define HW_DS3							3

////////////////////////////////////////////////////////////////////////////////
// Video
////////////////////////////////////////////////////////////////////////////////
#define VIDEO_CODEC_JPEG
#define VIDEO_CODEC_H264
#define VIDEO_CODEC_H265

////////////////////////////////////////////////////////////////////////////////
// H.265
#define H265_Quantize_MAX				(51)
#define H265_Quantize_MIN				(10)		// (0)

#define H265_Idrframe_MAX				(150)
#define H265_Idrframe_MIN				(1)

#define H265_Resolution_1st_MAX			e_res1920x1080
#define H265_Resolution_1st_MIN			e_res320x240

#define H265_Resolution_2nd_MAX			e_res640x360
#define H265_Resolution_2nd_MIN			e_res320x240

////////////////////////////////////////////////////////////////////////////////
// H.264
#define H264_Quantize_MAX				(51)
#define H264_Quantize_MIN				(10)		// (0)

#define H264_Idrframe_MAX				(150)
#define H264_Idrframe_MIN				(1)

#define H264_Resolution_1st_MAX			e_res1920x1080
#define H264_Resolution_1st_MIN			e_res320x240

#define H264_Resolution_2nd_MAX			e_res640x360
#define H264_Resolution_2nd_MIN			e_res320x240

////////////////////////////////////////////////////////////////////////////////
// JPEG
#define JPEG_Quantize_MAX				(99)
#define JPEG_Quantize_MIN				(0)

#define JPEG_Resolution_MAX				e_res1920x1080
#define JPEG_Resolution_MIN				e_res320x240

#define JPEG_STREAM						1
#define JPEG_SNAPSHOT					1
#define JPEG_WEBVIEW					1

////////////////////////////////////////////////////////////////////////////////
// Audio
////////////////////////////////////////////////////////////////////////////////
#ifdef __AUDIO__
#define AUDIO_CODEC_RAW					0
#define AUDIO_CODEC_G711A				1
#define AUDIO_CODEC_G711U				2
#define AUDIO_CODEC						AUDIO_CODEC_RAW

////////////////////////////////////////////////////////////////////////////////
// PCM/Codec
#define I2S_MASTER_MODE					0			// 0:Slave 1:Master

#define I2S_FREQ						24576000
#define I2S_MST_CLK						I2S_FREQ	// I2S_FREQ or APB_FREQ

#define PCM_BIT_8						(8)
#define PCM_BIT_16						(16)
#define PCM_BIT_24						(24)
#define PCM_BIT_32						(32)
#define PCM_BIT							PCM_BIT_16

#define PCM_WCLK_8000HZ					(8000)
#define PCM_WCLK_16000HZ				(16000)
#define PCM_WCLK_32000HZ				(32000)
#define PCM_WCLK_48000HZ				(48000)
#define PCM_WCLK_11025HZ				(11025)
#define PCM_WCLK_22050HZ				(22050)
#define PCM_WCLK_44100HZ				(44100)
#define PCM_WCLK						PCM_WCLK_32000HZ

#define PCM_MONO						(1)
#define PCM_STEREO						(2)
#define PCM_SOUNDMODE					PCM_STEREO

#define PCM_BCLK						(PCM_WCLK*PCM_BIT*2)
#define PCM_BYTE						(PCM_BCLK/8)

#if (PCM_WCLK==PCM_WCLK_8000HZ)
#define AUD_STM_SIZE					(320)
#define PCM_RecordingHz					(50)
#elif (PCM_WCLK==PCM_WCLK_16000HZ)
#define AUD_STM_SIZE					(640)
#define PCM_RecordingHz					(50)
#elif (PCM_WCLK==PCM_WCLK_32000HZ)
#define AUD_STM_SIZE					(1280)
#define PCM_RecordingHz					(50)
#elif (PCM_WCLK==PCM_WCLK_48000HZ)
#define AUD_STM_SIZE					(1280)
#define PCM_RecordingHz					(75)
#elif (PCM_WCLK==PCM_WCLK_11025HZ)
#define AUD_STM_SIZE					(630)
#define PCM_RecordingHz					(35)
#elif (PCM_WCLK==PCM_WCLK_22050HZ)
#define AUD_STM_SIZE					(1260)
#define PCM_RecordingHz					(35)
#elif (PCM_WCLK==PCM_WCLK_44100HZ)
#define AUD_STM_SIZE					(1260)
#define PCM_RecordingHz					(70)
#endif

////////////////////////////////////////////////////////////////////////////////
// G.711
#define G711_KBitrate_MAX				(64)
#define G711_KBitrate_MIN				(64)
#define G711_KHzSampleRate_MAX			(8)
#define G711_KHzSampleRate_MIN			(8)
#define G711_RecordingHz				(10)

////////////////////////////////////////////////////////////////////////////////
//#if (AUDIO_CODEC==AUDIO_CODEC_RAW)
//#define AUD_SAMPLING_BIT  				16
//#else
//#define AUD_SAMPLING_BIT  				8
//#endif
//#define AUD_SAMPLING_RATE 				(PCM_FREQUENCY / (AUD_SAMPLING_BIT / 8))

#endif

#endif //__CFG_MEDIA_H__
