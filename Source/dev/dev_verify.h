//******************************************************************************
//	Copyright(c) Eyenix Co.,Ltd. 2003-
//
//	File Name:     dev_verify.h
//	Description:   EN675 Verify definition
//	Author:        Team 2
//
//	Note:          Here you will check the settings.
//
//	Ver   Date   Author  Changes
//	---  ------  ------  -------
//  0.1  190318  hjlee   support EN675
//------------------------------------------------------------------------------
#ifndef __DEV_VERIFY_H__
#define __DEV_VERIFY_H__

#if !defined(__USE_SDIOCD__)
#if (LOAD_FS_SDCARD==1)
#error "You need to activate 'USE_SD' or need to set USE_FS_SD to 0."
#endif
#else
#if (LOAD_FS_SDCARD==0)
#error "You need to activate 'USE_SD' or need to set USE_FS_SD to 0."
#endif
#endif

#if (USE_ETH==0)
#if defined(__ETHERNET__)
#error "You need to activate 'USE_ETH' or need to set USE_ETHERNET to 0."
#endif
#else
#if !defined(__ETHERNET__)
#error "You need to activate 'USE_ETH' or need to set USE_ETHERNET to 0."
#endif
#endif

#if (AUDIO_CODEC!=AUDIO_CODEC_RAW)
#if (PCM_FREQUENCY!=PCM_16BIT_8000HZ)
#error "Audio frequency error! If you selected G.711 as your codec, set PCM_FREQUENCY to PCM_16BIT_8000HZ."
#endif
#endif

#endif //__DEV_VERIFY_H__
