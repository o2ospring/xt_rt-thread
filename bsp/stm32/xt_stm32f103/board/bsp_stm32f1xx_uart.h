/**
  * @file  bsp_stm32f1xx_uart.h
  * @brief 全局串口驱动程序
  * @notice 本驱动只作为初始化参考代码，因为串口一般专用于某个应用模块
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    原始版本
  */
#ifndef BSP_STM32F1XX_UART_H__
#define BSP_STM32F1XX_UART_H__

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

#ifdef BSP_STM32F1XX_UART_C__
#undef  BSP_EXT
#define BSP_EXT
#else
#undef  BSP_EXT
#define BSP_EXT  extern
#endif

#if (BSP_USART1_EN & 0x01) && !(defined BSP_UART1) //////////////////////
#define BSP_UART1                    USART1                             /* 使用的哪个串口               */
#define BSP_UART1_BAUD_RATE          9600                               /* 通讯波特率: 9600bps          */
#define BSP_UART1_CLK_ENABLE()     __HAL_RCC_USART1_CLK_ENABLE()        /* 串口时钟使能                 */
#define BSP_UART1_TX_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()         /* TX脚时钟使能                 */
#define BSP_UART1_RX_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()         /* RX脚时钟使能                 */
#define BSP_UART1_IRQn               USART1_IRQn                        /* 中断通道                     */
#define BSP_UART1_PRE_INT_PRIO       0                                  /* 抢占中断优先级               */
#define BSP_UART1_SUB_INT_PRIO       0                                  /* 响应中断优先级               */
#define BSP_UART1_TX_GPIO            GPIOA                              /* TX 所在端口                  */
#define BSP_UART1_TX_PIN             GPIO_PIN_9                         /* TX 所在管脚                  */
#define BSP_UART1_RX_GPIO            GPIOA                              /* RX 所在端口                  */
#define BSP_UART1_RX_PIN             GPIO_PIN_10                        /* RX 所在管脚                  */
#define BSP_UART1_RX_IN_MODE         GPIO_PULLUP                        /* RX 输入模式(上拉/悬空)       //
#define BSP_UART1_AFIO_REMAP()     __HAL_AFIO_REMAP_USART1_ENABLE()     // 串口引脚重映射(不使用则屏蔽) //
#define BSP_UART1_HANDLER            huart1                             // 串口句柄(不使用全局句柄则屏蔽//
BSP_EXT UART_HandleTypeDef           huart1;                            // 串口句柄(全局变量,不用时屏蔽)*/
#endif ///////////////////////////////

#if (BSP_USART2_EN & 0x01) && !(defined BSP_UART2) //////////////////////
#define BSP_UART2                    USART2                             /* 使用的哪个串口               */
#define BSP_UART2_BAUD_RATE          9600                               /* 通讯波特率: 9600bps          */
#define BSP_UART2_CLK_ENABLE()     __HAL_RCC_USART2_CLK_ENABLE()        /* 串口时钟使能                 */
#define BSP_UART2_TX_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()         /* TX脚时钟使能                 */
#define BSP_UART2_RX_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()         /* RX脚时钟使能                 */
#define BSP_UART2_IRQn               USART2_IRQn                        /* 中断通道                     */
#define BSP_UART2_PRE_INT_PRIO       0                                  /* 抢占中断优先级               */
#define BSP_UART2_SUB_INT_PRIO       0                                  /* 响应中断优先级               */
#define BSP_UART2_TX_GPIO            GPIOA                              /* TX 所在端口                  */
#define BSP_UART2_TX_PIN             GPIO_PIN_2                         /* TX 所在管脚                  */
#define BSP_UART2_RX_GPIO            GPIOA                              /* RX 所在端口                  */
#define BSP_UART2_RX_PIN             GPIO_PIN_3                         /* RX 所在管脚                  */
#define BSP_UART2_RX_IN_MODE         GPIO_PULLUP                        /* RX 输入模式(上拉/悬空)       //
#define BSP_UART2_AFIO_REMAP()     __HAL_AFIO_REMAP_USART2_ENABLE()     // 串口引脚重映射(不使用则屏蔽) //
#define BSP_UART2_HANDLER            huart2                             // 串口句柄(不使用全局句柄则屏蔽//
BSP_EXT UART_HandleTypeDef           huart2;                            // 串口句柄(全局变量,不用时屏蔽)*/
#endif ///////////////////////////////

#if (BSP_USART3_EN & 0x01) && !(defined BSP_UART3) //////////////////////
#define BSP_UART3                    USART3                             /* 使用的哪个串口               */
#define BSP_UART3_BAUD_RATE          9600                               /* 通讯波特率: 9600bps          */
#define BSP_UART3_CLK_ENABLE()     __HAL_RCC_USART3_CLK_ENABLE()        /* 串口时钟使能                 */
#define BSP_UART3_TX_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()         /* TX脚时钟使能                 */
#define BSP_UART3_RX_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()         /* RX脚时钟使能                 */
#define BSP_UART3_IRQn               USART3_IRQn                        /* 中断通道                     */
#define BSP_UART3_PRE_INT_PRIO       0                                  /* 抢占中断优先级               */
#define BSP_UART3_SUB_INT_PRIO       0                                  /* 响应中断优先级               */
#define BSP_UART3_TX_GPIO            GPIOB                              /* TX 所在端口                  */
#define BSP_UART3_TX_PIN             GPIO_PIN_10                        /* TX 所在管脚                  */
#define BSP_UART3_RX_GPIO            GPIOB                              /* RX 所在端口                  */
#define BSP_UART3_RX_PIN             GPIO_PIN_11                        /* RX 所在管脚                  */
#define BSP_UART3_RX_IN_MODE         GPIO_PULLUP                        /* RX 输入模式(上拉/悬空)       //
#define BSP_UART3_AFIO_REMAP()     __HAL_AFIO_REMAP_USART3_ENABLE()     // 串口引脚重映射(不使用则屏蔽) //
#define BSP_UART3_HANDLER            huart3                             // 串口句柄(不使用全局句柄则屏蔽//
BSP_EXT UART_HandleTypeDef           huart3;                            // 串口句柄(全局变量,不用时屏蔽)*/
#endif ///////////////////////////////

#if (BSP_UART4_EN & 0x01) && !(defined BSP_UART4) ///////////////////////
#define BSP_UART4                    UART4                              /* 使用的哪个串口               */
#define BSP_UART4_BAUD_RATE          9600                               /* 通讯波特率: 9600bps          */
#define BSP_UART4_CLK_ENABLE()     __HAL_RCC_UART4_CLK_ENABLE()         /* 串口时钟使能                 */
#define BSP_UART4_TX_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()         /* TX脚时钟使能                 */
#define BSP_UART4_RX_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()         /* RX脚时钟使能                 */
#define BSP_UART4_IRQn               UART4_IRQn                         /* 中断通道                     */
#define BSP_UART4_PRE_INT_PRIO       0                                  /* 抢占中断优先级               */
#define BSP_UART4_SUB_INT_PRIO       0                                  /* 响应中断优先级               */
#define BSP_UART4_TX_GPIO            GPIOC                              /* TX 所在端口                  */
#define BSP_UART4_TX_PIN             GPIO_PIN_10                        /* TX 所在管脚                  */
#define BSP_UART4_RX_GPIO            GPIOC                              /* RX 所在端口                  */
#define BSP_UART4_RX_PIN             GPIO_PIN_11                        /* RX 所在管脚                  */
#define BSP_UART4_RX_IN_MODE         GPIO_PULLUP                        /* RX 输入模式(上拉/悬空)       //
#define BSP_UART4_AFIO_REMAP()     __HAL_AFIO_REMAP_USART1_ENABLE()     // 串口引脚重映射(不使用则屏蔽) //
#define BSP_UART4_HANDLER            huart4                             // 串口句柄(不使用全局句柄则屏蔽//
BSP_EXT UART_HandleTypeDef           huart4;                            // 串口句柄(全局变量,不用时屏蔽)*/
#endif ///////////////////////////////

#if (BSP_UART5_EN & 0x01) && !(defined BSP_UART5) ///////////////////////
#define BSP_UART5                    UART5                              /* 使用的哪个串口               */
#define BSP_UART5_BAUD_RATE          9600                               /* 通讯波特率: 9600bps          */
#define BSP_UART5_CLK_ENABLE()     __HAL_RCC_UART5_CLK_ENABLE()         /* 串口时钟使能                 */
#define BSP_UART5_TX_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()         /* TX脚时钟使能                 */
#define BSP_UART5_RX_CLK_ENABLE()  __HAL_RCC_GPIOD_CLK_ENABLE()         /* RX脚时钟使能                 */
#define BSP_UART5_IRQn               UART5_IRQn                         /* 中断通道                     */
#define BSP_UART5_PRE_INT_PRIO       0                                  /* 抢占中断优先级               */
#define BSP_UART5_SUB_INT_PRIO       0                                  /* 响应中断优先级               */
#define BSP_UART5_TX_GPIO            GPIOC                              /* TX 所在端口                  */
#define BSP_UART5_TX_PIN             GPIO_PIN_12                        /* TX 所在管脚                  */
#define BSP_UART5_RX_GPIO            GPIOD                              /* RX 所在端口                  */
#define BSP_UART5_RX_PIN             GPIO_PIN_2                         /* RX 所在管脚                  */
#define BSP_UART5_RX_IN_MODE         GPIO_PULLUP                        /* RX 输入模式(上拉/悬空)       //
#define BSP_UART5_AFIO_REMAP()     __HAL_AFIO_REMAP_USART1_ENABLE()     // 串口引脚重映射(不使用则屏蔽) //
#define BSP_UART5_HANDLER            huart5                             // 串口句柄(不使用全局句柄则屏蔽//
BSP_EXT UART_HandleTypeDef           huart5;                            // 串口句柄(全局变量,不用时屏蔽)*/
#endif ///////////////////////////////

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 初始函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void bsp_usart1_init(void);
extern void bsp_usart2_init(void);
extern void bsp_usart3_init(void);
extern void bsp_uart4_init(void);
extern void bsp_uart5_init(void);

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef BSP_STM32F1XX_UART_H__
