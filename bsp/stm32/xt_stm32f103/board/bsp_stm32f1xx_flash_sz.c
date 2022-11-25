/**
  * @file  bsp_stm32f1xx_flash_sz.c
  * @brief ����STM32F103�ڲ�FLASH������С��������
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    ԭʼ�汾
  */
#define   BSP_STM32F1XX_FLASH_SZ_C__
#include "bsp_stm32f1xx_flash_sz.h"
#ifdef    BSP_STM32F1XX_FLASH_SZ_X__
#undef    BSP_STM32F1XX_FLASH_SZ_H__
#include "bsp_stm32f1xx_flash_sz.h"
#endif

/**
  * @brief  ����STM32F103�ڲ�FLASH������С����λ:KB��
  * @param  void
  * @return FLASH������С, ��λ:KB(K�ֽ�)
  */
uint16_t bsp_flash_sz_kb_read(void)
{
	return (*((uint16_t *)(0x1FFFF7E0)));
}

/**
  * @brief  ����STM32F103�ڲ�FLASH������С����λ:�ֽڡ�
  * @param  void
  * @return FLASH������С, ��λ:Byte
  */
uint32_t bsp_flash_sz_nb_read(void)
{
	return ((uint32_t)(*((uint16_t *)(0x1FFFF7E0))) * 1024UL);
}
