/**
  * @file  bsp_stm32f1xx_flash_sz.h
  * @brief 读出STM32F103内部FLASH容量大小驱动程序
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    原始版本
  */
#ifndef BSP_STM32F1XX_FLASH_SZ_H__
#define BSP_STM32F1XX_FLASH_SZ_H__

#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 操作函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern uint16_t bsp_flash_sz_kb_read(void);
extern uint32_t bsp_flash_sz_nb_read(void);

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef BSP_STM32F1XX_FLASH_SZ_H__


