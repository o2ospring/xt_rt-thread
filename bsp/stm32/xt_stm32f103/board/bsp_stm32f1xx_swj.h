/**
  * @file  bsp_stm32f1xx_swj.h
  * @brief ����SWJ���Կ���������
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    ԭʼ�汾
  */
#ifndef  BSP_STM32F1XX_SWJ_H__
#define  BSP_STM32F1XX_SWJ_H__

#include <stdint.h> //////////////////////// <- ʹ�õ����ݶ��壬��: int8_t, uint32_t ��
#ifdef BSP_STM32F1XX_SWJ_C__
#include "xt_comdef.h" ///////////////////// <- ���ú궨�弯�ϣ���: XT_BIT_SET ��
#include "board.h"   /////////////////////// <- ��������Ӳ����Դ����ͷ�ļ�!!!!!!!!!!!!!!!
#include "stm32f1xx.h" ///////////////////// <- ����STM32F103��Ƭ��HAL��
/*
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_conf.h" */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ ��ʼ���� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void bsp_swj_init(void);

#ifdef __cplusplus
	}
#endif

#endif // BSP_STM32F1XX_SWJ_H__
