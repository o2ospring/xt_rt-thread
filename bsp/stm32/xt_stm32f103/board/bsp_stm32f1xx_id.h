/**
  * @file  bsp_stm32f1xx_id.h
  * @brief 读出STM32F103ID驱动程序
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    原始版本
  */
#ifndef BSP_STM32F1XX_ID_H__
#define BSP_STM32F1XX_ID_H__

#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#include <string.h> //////////////////////// <- 使用的字符处理，如: strcpy(), memcpy() 等
#include "board.h"   /////////////////////// <- 工程所有硬件资源管理头文件!!!!!!!!!!!!!!!
#include "bsp_stm32f1xx_crc.h" ///////////// <- 使用到STM32的硬件CRC

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 操作函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern int bsp_stm32_id12_cmp(uint8_t *p_dat);  //注意:缓冲器没安全检测
extern void bsp_stm32_id12_get(uint8_t *p_buf); //注意:缓冲器没安全检测

#if (BSP_CRC_EN & 0x01)   //用到STM32的硬件CRC,需要事先处理硬件互斥！
extern void bsp_unique_id_generate(uint8_t *p_buf, uint8_t id_size);
#endif

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef BSP_STM32F1XX_ID_H__


