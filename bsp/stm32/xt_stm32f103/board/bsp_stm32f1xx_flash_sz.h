/**
  * @file  bsp_stm32f1xx_flash_sz.h
  * @brief ����STM32F103�ڲ�FLASH������С��������
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    ԭʼ�汾
  */
#ifndef BSP_STM32F1XX_FLASH_SZ_H__
#define BSP_STM32F1XX_FLASH_SZ_H__

#include <stdint.h> //////////////////////// <- ʹ�õ����ݶ��壬��: int8_t, uint32_t ��

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ �������� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern uint16_t bsp_flash_sz_kb_read(void);
extern uint32_t bsp_flash_sz_nb_read(void);

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef BSP_STM32F1XX_FLASH_SZ_H__


