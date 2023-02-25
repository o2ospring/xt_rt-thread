/**
  * @file  bsp_stm32f1xx_wdg.h
  * @brief 全局看门狗驱动程序
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-18     o2ospring    原始版本
  */
#ifndef BSP_STM32F1XX_WDG_H__
#define BSP_STM32F1XX_WDG_H__

#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#ifdef BSP_STM32F1XX_WDG_C__
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
/*++++++++++++++++++++++++++++++++++++++++++++++ 参数配置 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#define BSP_WDG_CFG                  1                                  /* 选择看门狗工作               */
                                                                        /* 0: 关闭看门狗(调试临时关闭)  */
                                                                        /* 1: 独立看门狗(影响仿真调试)  */ //备注：会温飘,应该小于1/3时间就必须喂狗
                                                                        /* 2: 窗口看门狗(半饿时才喂狗)  */ //备注：不建议用
#define IWDG_TIMEOUT_SET             2000UL /*100~3000mS*/              /* 独立看门狗的溢出时间设置@1mS */ //备注：不要设置300ms以下
#define WWDG_WINDOW_VALUE_SET        0x70   /*0x7E~0x41*/               /* 窗口看门狗可喂狗时段设置     */ //备注：倒计时方式

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 操作函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void bsp_wdg_init(void);
extern void wdg_runner_set(uint8_t runner);
extern void wdg_reload_counter(uint8_t runner);
extern void wdg_reload_software(void);

// 由于喂狗一般在软件定时器操作,但当一些特别操作会影响软
// 件定时器喂狗的及时性时,可以临时启动在硬件定时器中喂狗：
//【1】临时启动在硬件定时器中喂狗
// #if (BSP_WDG_EN & 0x01)
// wdg_runner_set(1);
// #endif
//【2】硬件定时器中断函数喂狗代码
// #if (BSP_WDG_EN & 0x01)
// wdg_reload_counter(1)
// #endif
//【3】关闭临时在硬件定时器中喂狗
// #if (BSP_WDG_EN & 0x01)
// wdg_runner_set(0);
// #endif

#ifdef __cplusplus
	}
#endif

#endif  //BSP_STM32F1XX_WDG_H__
