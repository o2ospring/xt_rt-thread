/**
  * @file  bsp_stm32f1xx_it.h
  * @brief ȫ���ж���Դ
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-16     o2ospring    ԭʼ�汾
  */
#ifndef BSP_STM32F1XX_IT_H__
#define BSP_STM32F1XX_IT_H__

#ifdef BSP_STM32F1XX_IT_C__
#include <stdint.h> //////////////////////// <- ʹ�õ����ݶ��壬��: int8_t, uint32_t ��
#include "application.h" /////////////////// <- �������������Դ����ͷ�ļ�!!!!!!!!!!!!!!!
#include "board.h"   /////////////////////// <- ��������Ӳ����Դ����ͷ�ļ�!!!!!!!!!!!!!!!
#include "stm32f1xx.h" ///////////////////// <- ����STM32F103��Ƭ��HAL��
#include "bsp_stm32f1xx_tim.h" ///////////// <- ʹ��ȫ�ֶ�ʱ����ʱ
/*
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_conf.h" */
#endif

//#ifdef __cplusplus
//extern "C" {
//#endif
//
//#ifdef __cplusplus
//	}
//#endif

#endif  //#ifndef BSP_STM32F1XX_IT_H__
