/**
  * @file  bsp_stm32f1xx_exti.h
  * @brief 全局外部中断驱动程序
  * @notice 本驱动一般只作为初始化参考代码，因为外部中断常专用于某个应用模块
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-16     o2ospring    原始版本
  */
#ifndef BSP_STM32F1XX_EXTI_H__
#define BSP_STM32F1XX_EXTI_H__

#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#ifdef BSP_STM32F1XX_EXTI_C__
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
/*++++++++++++++++++++++++++++++++++++++++++++++ 引脚定义 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#ifdef BSP_STM32F1XX_EXTI_C__ ////////////////////////// <- 只有[bsp_stm32f1xx_exti.c]才会包含引脚定义!!!!

#ifndef BSP_EXTI0_CLK_ENABLE /////////
#define BSP_EXTI0_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()         /* 外部中断时钟使能             */
#define BSP_EXTI0_MODE_IT            GPIO_MODE_IT_FALLING               /* 中断触发方式                 */
#define BSP_EXTI0_IRQn               EXTI0_IRQn                         /* 中断通道                     */
#define BSP_EXTI0_PRE_INT_PRIO       0                                  /* 抢占中断优先级               */
#define BSP_EXTI0_SUB_INT_PRIO       0                                  /* 响应中断优先级               */
#define BSP_EXTI0_GPIO               GPIOB                              /* 外部中断所在端口             */
#define BSP_EXTI0_PIN                GPIO_PIN_0                         /* 外部中断所在管脚             */
#define BSP_EXTI0_IN_MODE            GPIO_PULLUP                        /* 输入模式(上拉/下拉/悬空)     */
#endif ///////////////////////////////

#ifndef BSP_EXTI1_CLK_ENABLE /////////
#define BSP_EXTI1_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()         /* 外部中断时钟使能             */
#define BSP_EXTI1_MODE_IT            GPIO_MODE_IT_FALLING               /* 中断触发方式                 */
#define BSP_EXTI1_IRQn               EXTI1_IRQn                         /* 中断通道                     */
#define BSP_EXTI1_PRE_INT_PRIO       0                                  /* 抢占中断优先级               */
#define BSP_EXTI1_SUB_INT_PRIO       0                                  /* 响应中断优先级               */
#define BSP_EXTI1_GPIO               GPIOB                              /* 外部中断所在端口             */
#define BSP_EXTI1_PIN                GPIO_PIN_1                         /* 外部中断所在管脚             */
#define BSP_EXTI1_IN_MODE            GPIO_PULLUP                        /* 输入模式(上拉/下拉/悬空)     */
#endif ///////////////////////////////

#ifndef BSP_EXTI2_CLK_ENABLE /////////
#define BSP_EXTI2_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()         /* 外部中断时钟使能             */
#define BSP_EXTI2_MODE_IT            GPIO_MODE_IT_FALLING               /* 中断触发方式                 */
#define BSP_EXTI2_IRQn               EXTI2_IRQn                         /* 中断通道                     */
#define BSP_EXTI2_PRE_INT_PRIO       0                                  /* 抢占中断优先级               */
#define BSP_EXTI2_SUB_INT_PRIO       0                                  /* 响应中断优先级               */
#define BSP_EXTI2_GPIO               GPIOB                              /* 外部中断所在端口             */
#define BSP_EXTI2_PIN                GPIO_PIN_2                         /* 外部中断所在管脚             */
#define BSP_EXTI2_IN_MODE            GPIO_PULLUP                        /* 输入模式(上拉/下拉/悬空)     */
#endif ///////////////////////////////

#ifndef BSP_EXTI3_CLK_ENABLE /////////
#define BSP_EXTI3_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()         /* 外部中断时钟使能             */
#define BSP_EXTI3_MODE_IT            GPIO_MODE_IT_FALLING               /* 中断触发方式                 */
#define BSP_EXTI3_IRQn               EXTI3_IRQn                         /* 中断通道                     */
#define BSP_EXTI3_PRE_INT_PRIO       0                                  /* 抢占中断优先级               */
#define BSP_EXTI3_SUB_INT_PRIO       0                                  /* 响应中断优先级               */
#define BSP_EXTI3_GPIO               GPIOB                              /* 外部中断所在端口             */
#define BSP_EXTI3_PIN                GPIO_PIN_3                         /* 外部中断所在管脚             */
#define BSP_EXTI3_IN_MODE            GPIO_PULLUP                        /* 输入模式(上拉/下拉/悬空)     */
#endif ///////////////////////////////

#ifndef BSP_EXTI4_CLK_ENABLE /////////
#define BSP_EXTI4_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()         /* 外部中断时钟使能             */
#define BSP_EXTI4_MODE_IT            GPIO_MODE_IT_FALLING               /* 中断触发方式                 */
#define BSP_EXTI4_IRQn               EXTI4_IRQn                         /* 中断通道                     */
#define BSP_EXTI4_PRE_INT_PRIO       0                                  /* 抢占中断优先级               */
#define BSP_EXTI4_SUB_INT_PRIO       0                                  /* 响应中断优先级               */
#define BSP_EXTI4_GPIO               GPIOB                              /* 外部中断所在端口             */
#define BSP_EXTI4_PIN                GPIO_PIN_4                         /* 外部中断所在管脚             */
#define BSP_EXTI4_IN_MODE            GPIO_PULLUP                        /* 输入模式(上拉/下拉/悬空)     */
#endif ///////////////////////////////

#ifndef BSP_EXTI9_5_CLK_ENABLE /////////
#define BSP_EXTI9_5_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()         /* 外部中断时钟使能             */
#define BSP_EXTI9_5_MODE_IT          GPIO_MODE_IT_FALLING               /* 中断触发方式                 */
#define BSP_EXTI9_5_IRQn             EXTI9_5_IRQn                       /* 中断通道                     */
#define BSP_EXTI9_5_PRE_INT_PRIO     0                                  /* 抢占中断优先级               */
#define BSP_EXTI9_5_SUB_INT_PRIO     0                                  /* 响应中断优先级               */
#define BSP_EXTI9_5_GPIO             GPIOB                              /* 外部中断所在端口             */
#define BSP_EXTI9_5_PIN              GPIO_PIN_8                         /* 外部中断所在管脚             */
#define BSP_EXTI9_5_IN_MODE          GPIO_PULLUP                        /* 输入模式(上拉/下拉/悬空)     */
#endif ///////////////////////////////

#ifndef BSP_EXTI15_10_CLK_ENABLE /////////
#define BSP_EXTI15_10_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()         /* 外部中断时钟使能             */
#define BSP_EXTI15_10_MODE_IT        GPIO_MODE_IT_FALLING               /* 中断触发方式                 */
#define BSP_EXTI15_10_IRQn           EXTI15_10_IRQn                     /* 中断通道                     */
#define BSP_EXTI15_10_PRE_INT_PRIO   0                                  /* 抢占中断优先级               */
#define BSP_EXTI15_10_SUB_INT_PRIO   0                                  /* 响应中断优先级               */
#define BSP_EXTI15_10_GPIO           GPIOB                              /* 外部中断所在端口             */
#define BSP_EXTI15_10_PIN            GPIO_PIN_14                        /* 外部中断所在管脚             */
#define BSP_EXTI15_10_IN_MODE        GPIO_PULLUP                        /* 输入模式(上拉/下拉/悬空)     */
#endif ///////////////////////////////

#endif ///////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 初始函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void bsp_exti0_init(void);
extern void bsp_exti1_init(void);
extern void bsp_exti2_init(void);
extern void bsp_exti3_init(void);
extern void bsp_exti4_init(void);
extern void bsp_exti9_5_init(void);
extern void bsp_exti15_10_init(void);

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef BSP_STM32F1XX_EXTI_H__
