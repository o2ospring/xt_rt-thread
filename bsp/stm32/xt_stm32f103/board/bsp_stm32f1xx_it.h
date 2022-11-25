/**
  * @file  bsp_stm32f1xx_it.h
  * @brief 全局中断资源
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-16     o2ospring    原始版本
  */
#ifndef BSP_STM32F1XX_IT_H__
#define BSP_STM32F1XX_IT_H__

#ifdef BSP_STM32F1XX_IT_C__
#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#include "application.h" /////////////////// <- 工程所有软件资源管理头文件!!!!!!!!!!!!!!!
#include "board.h"   /////////////////////// <- 工程所有硬件资源管理头文件!!!!!!!!!!!!!!!
#include "stm32f1xx.h" ///////////////////// <- 依赖STM32F103单片机HAL库
#include "bsp_stm32f1xx_tim.h" ///////////// <- 使用全局定时器定时
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
