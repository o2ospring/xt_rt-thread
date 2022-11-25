/**
  * @file  bsp_stm32f1xx_crc.h
  * @brief ȫ��CRC32������������
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    ԭʼ�汾
  */
#ifndef  BSP_STM32F1XX_CRC_H__
#define  BSP_STM32F1XX_CRC_H__

#include <stdint.h> //////////////////////// <- ʹ�õ����ݶ��壬��: int8_t, uint32_t ��
#ifdef BSP_STM32F1XX_CRC_C__
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
/*++++++++++++++++++++++++++++++++++++++++++++++ �������� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void bsp_crc_init(void);

// �����CRC32У��ֵ (ע��: ���ñ�����ʱ�����Ƚ��Ӳ����������)
extern uint32_t bsp_stm32_crc32(const uint8_t *p_dat, uint16_t dat_len);

#ifdef __cplusplus
	}
#endif

#endif // BSP_STM32F1XX_CRC_H__
