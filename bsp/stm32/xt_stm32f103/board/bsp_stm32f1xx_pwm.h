/**
  * @file  bsp_stm32f1xx_pwm.h
  * @brief 全局定时器PWM驱动程序
  * @notice 本驱动只作为初始化参考代码，因为PWM一般专用于某个应用模块
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-19     o2ospring    原始版本
  */
#ifndef BSP_STM32F1XX_PWM_H__
#define BSP_STM32F1XX_PWM_H__

#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#include "xt_comdef.h" ///////////////////// <- 常用宏定义集合，如: XT_BIT_SET 等
#include "board.h"   /////////////////////// <- 工程所有硬件资源管理头文件!!!!!!!!!!!!!!!
#include "stm32f1xx.h" ///////////////////// <- 依赖STM32F103单片机HAL库
/*
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_conf.h" */

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 引脚定义 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#ifdef BSP_STM32F1XX_PWM_C__
#undef  BSP_EXT
#define BSP_EXT
#else
#undef  BSP_EXT
#define BSP_EXT  extern
#endif

#if (BSP_TIMX_PWM_EN & 0x01) && !(defined XXX_TIMX) /////////////////////

// 配置PWM频率等
#define XXX_TIMX_DIV         2                                                      //定时器的时钟分频
#define XXX_TIMX_PWM_FRE     1000                                                   //PWM 输出频率
#define XXX_TIMX_PWM_FREVOL  ((72000000 / (XXX_TIMX_DIV+1) / XXX_TIMX_PWM_FRE) - 1) //PWM 100%数值(≤0xFFFF)

// 配置PWM定时器
#define XXX_TIMX                     TIM2                               /* 定时器                       */
#define XXX_TIMX_CLK_ENABLE()      __HAL_RCC_TIM2_CLK_ENABLE()          /* 定时器时钟使能               //
#define XXX_TIMX_AFIO_REMAP()      __HAL_AFIO_REMAP_TIM2_PARTIAL_1()    // 定时器引脚重映射(不用则屏蔽) // //只有 TIM1~5 才有映射 (分:重映射[TIM4~5]、部分和完全重映射TIM1~3)
#define XXX_TIMX_HANDLER             htim2                              // 定时器句柄(不用全局句柄则屏蔽//
BSP_EXT TIM_HandleTypeDef            htim2;                             // 定时器句柄(全局变量,按需屏蔽)*/

// 配置PWM1
#define XXX_PWM1_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()         /* PWM1 管脚时钟使能(不用则屏蔽)*/
#define XXX_PWM1_GPIO                GPIOA                              /* PWM1 所在端口                */
#define XXX_PWM1_PIN                 GPIO_PIN_0                         /* PWM1 所在管脚                */
#define XXX_PWM1_OCMODE              TIM_OCMODE_PWM1                    /* PWM1 输出极性模式(2则反极性) */ //使用在:非0%,非停止
#define XXX_PWM1_OCPOLARITY          TIM_OCPOLARITY_HIGH                /* PWM1 有效占空比输出的电平    // //正向通道
#define XXX_PWM1_OCIDLESTATE         TIM_OCIDLESTATE_RESET              // PWM1 空闲时电平(不用则屏蔽)  */ //只针对TIM1,其它定时器默认为低电平
#define XXX_PWM1_CCRx                CCR1                               /* PWM1 XXX_TIMX->XXX_PWM1_CCRx */ //占空比

// 配置PWM2
#define XXX_PWM2_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()         /* PWM2 管脚时钟使能(不用则屏蔽)*/
#define XXX_PWM2_GPIO                GPIOA                              /* PWM2 所在端口                */
#define XXX_PWM2_PIN                 GPIO_PIN_1                         /* PWM2 所在管脚                */
#define XXX_PWM2_OCMODE              TIM_OCMODE_PWM1                    /* PWM2 输出极性模式(2则反极性) */ //使用在:非0%,非停止
#define XXX_PWM2_OCPOLARITY          TIM_OCPOLARITY_HIGH                /* PWM2 有效占空比输出的电平    // //正向通道
#define XXX_PWM2_OCIDLESTATE         TIM_OCIDLESTATE_RESET              // PWM2 空闲时电平(不用则屏蔽)  */ //只针对TIM1,其它定时器默认为低电平
#define XXX_PWM2_CCRx                CCR2                               /* PWM2 XXX_TIMX->XXX_PWM2_CCRx */ //占空比

// 配置PWM3
#define XXX_PWM3_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()         /* PWM3 管脚时钟使能(不用则屏蔽)*/
#define XXX_PWM3_GPIO                GPIOA                              /* PWM3 所在端口                */
#define XXX_PWM3_PIN                 GPIO_PIN_2                         /* PWM3 所在管脚                */
#define XXX_PWM3_OCMODE              TIM_OCMODE_PWM1                    /* PWM3 输出极性模式(2则反极性) */ //使用在:非0%,非停止
#define XXX_PWM3_OCPOLARITY          TIM_OCPOLARITY_HIGH                /* PWM3 有效占空比输出的电平    // //正向通道
#define XXX_PWM3_OCIDLESTATE         TIM_OCIDLESTATE_RESET              // PWM3 空闲时电平(不用则屏蔽)  */ //只针对TIM1,其它定时器默认为低电平
#define XXX_PWM3_CCRx                CCR3                               /* PWM3 XXX_TIMX->XXX_PWM3_CCRx */ //占空比

// 配置PWM4
#define XXX_PWM4_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()         /* PWM4 管脚时钟使能(不用则屏蔽)*/
#define XXX_PWM4_GPIO                GPIOA                              /* PWM4 所在端口                */
#define XXX_PWM4_PIN                 GPIO_PIN_3                         /* PWM4 所在管脚                */
#define XXX_PWM4_OCMODE              TIM_OCMODE_PWM1                    /* PWM4 输出极性模式(2则反极性) */ //使用在:非0%,非停止
#define XXX_PWM4_OCPOLARITY          TIM_OCPOLARITY_HIGH                /* PWM4 有效占空比输出的电平    // //正向通道
#define XXX_PWM4_OCIDLESTATE         TIM_OCIDLESTATE_RESET              // PWM4 空闲时电平(不用则屏蔽)  */ //只针对TIM1,其它定时器默认为低电平
#define XXX_PWM4_CCRx                CCR4                               /* PWM4 XXX_TIMX->XXX_PWM4_CCRx */ //占空比

#endif ///////////////////////////////

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 初始函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void bsp_pwm_init(void);

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef BSP_STM32F1XX_PWM_H__


