/**
  * @file  bsp_stm32f1xx_flash_sz.c
  * @brief 读出STM32F103内部FLASH容量大小驱动程序
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    原始版本
  */
#define   BSP_STM32F1XX_FLASH_SZ_C__
#include "bsp_stm32f1xx_flash_sz.h"
#ifdef    BSP_STM32F1XX_FLASH_SZ_X__
#undef    BSP_STM32F1XX_FLASH_SZ_H__
#include "bsp_stm32f1xx_flash_sz.h"
#endif

/**
  * @brief  读出STM32F103内部FLASH容量大小【单位:KB】
  * @param  void
  * @return FLASH容量大小, 单位:KB(K字节)
  */
uint16_t bsp_flash_sz_kb_read(void)
{
	return (*((uint16_t *)(0x1FFFF7E0)));
}

/**
  * @brief  读出STM32F103内部FLASH容量大小【单位:字节】
  * @param  void
  * @return FLASH容量大小, 单位:Byte
  */
uint32_t bsp_flash_sz_nb_read(void)
{
	return ((uint32_t)(*((uint16_t *)(0x1FFFF7E0))) * 1024UL);
}
