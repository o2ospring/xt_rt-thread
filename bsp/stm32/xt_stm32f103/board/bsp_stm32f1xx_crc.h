/**
  * @file  bsp_stm32f1xx_crc.h
  * @brief 全局CRC32运算驱动程序
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    原始版本
  */
#ifndef  BSP_STM32F1XX_CRC_H__
#define  BSP_STM32F1XX_CRC_H__

#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#ifdef BSP_STM32F1XX_CRC_C__
#include "xt_comdef.h" ///////////////////// <- 常用宏定义集合，如: XT_BIT_SET 等
#include "board.h"   /////////////////////// <- 工程所有硬件资源管理头文件!!!!!!!!!!!!!!!
#include "stm32f1xx.h" ///////////////////// <- 依赖STM32F103单片机HAL库
/*
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_conf.h" */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 操作函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void bsp_crc_init(void);

// 计算出CRC32校验值 (注意: 调用本函数时必须先解决硬件互斥问题)
extern uint32_t bsp_stm32_crc32(const uint8_t *p_dat, uint16_t dat_len);

#ifdef __cplusplus
	}
#endif

#endif // BSP_STM32F1XX_CRC_H__
