/**
  * @file  board.h
  * @brief 所有硬件资源管理
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-15     o2ospring    原始版本
  */
#ifndef BOARD_H__
#define BOARD_H__

#include <stdint.h> //////////////////////// <-使用的数据定义，如: int8_t, uint32_t 等
#include <string.h> //////////////////////// <-使用的字符处理，如: strcpy(), memcpy() 等
#include "stm32f1xx.h" ///////////////////// <-处理器总头文件
#include "drv_common.h" //////////////////// <-操作系统模块
#include "drv_gpio.h" ////////////////////// <-操作系统模块
#include "application.h" /////////////////// <-软件资源管理
/*
#include "stm32f1xx_hal_conf.h"
#include "system_stm32f10x.h"
#include "stm32f1xx_hal.h" */

#ifdef __cplusplus
extern "C" {
#endif

#define STM32_FLASH_START_ADRESS     ((uint32_t)0x08000000)
#define STM32_FLASH_SIZE             (128 * 1024)
#define STM32_FLASH_END_ADDRESS      ((uint32_t)(STM32_FLASH_START_ADRESS + STM32_FLASH_SIZE))

/* Internal SRAM memory size[Kbytes] <8-64>, Default: 64*/
#define STM32_SRAM_SIZE      20
#define STM32_SRAM_END       (0x20000000 + STM32_SRAM_SIZE * 1024)

#if defined(__ARMCC_VERSION)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      (__segment_end("CSTACK"))
#else
extern int __bss_end;
#define HEAP_BEGIN      ((void *)&__bss_end)
#endif

#define HEAP_END        STM32_SRAM_END

//````````````````````````````````````````````````````````````````````````````````````````````````````````
#ifdef BOARD_C__
#define BSP_EXT
#else
#define BSP_EXT  extern
#endif

//````````````````````````````````````````````````````````````````````````````````````````````````````````
#define BSP_DEV_INIT_DELAY()         bsp_delay10us(150000)              /* 所有器件上电初始化前的延时   */ //建议延时0.5秒以上
#define BSP_NVIC_PRIORITY            NVIC_PRIORITYGROUP_2               /* 系统优先级模式(一般不要改)   */

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 资源分配 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

// JTAG/SW                          (bit0->是否使用统一的[初始化代码], bit4->是否使用统一的[中断代码])
#define BSP_JTAG_DI_SW_EN            0x01                               /* JTAG-DP禁用 + SW-DP 使能配置 */
// WDG 
#define BSP_WDG_EN                   0x00                               /* WDG                 使能配置 */
// CRC
#define BSP_CRC_EN                   0x00                               /* CRC                 使能配置 */
// UART
#define BSP_USART1_EN                0x00                               /* USART1              使能配置 */ //[0]:PA9,PA10,[1]:PB6,PB7
#define BSP_USART2_EN                0x00                               /* USART2              使能配置 */ //[0]:PA2,PA3,[1]:PD5,PD6
#define BSP_USART3_EN                0x00                  /*调试串口*/ /* USART3              使能配置 */ //[00]:PB10,PB11,[01]:PC10,PC11,[11]:PD8,PD9
#define BSP_UART4_EN                 0x00                               /* UART4               使能配置 */
#define BSP_UART5_EN                 0x00                               /* UART5               使能配置 */
// EXTI
#define BSP_EXTI0_EN                 0x00                               /* EXTI0               使能配置 */
#define BSP_EXTI1_EN                 0x00                               /* EXTI1               使能配置 */
#define BSP_EXTI2_EN                 0x00                               /* EXTI2               使能配置 */
#define BSP_EXTI3_EN                 0x00                               /* EXTI3               使能配置 */
#define BSP_EXTI4_EN                 0x00                               /* EXTI4               使能配置 */
#define BSP_EXTI9_5_EN               0x00                               /* EXTI9_5             使能配置 */
#define BSP_EXTI15_10_EN             0x00                               /* EXTI15_10           使能配置 */
// TIM
#define BSP_TIM1_CC_EN               0x00                               /* TIM1                使能配置 */ //[00]:PA8,PA9,PA10,PA11,[01]:PA8,PA9,PA10,PA11,[11]:PE9,PE11,PE13,PE14
#define BSP_TIM2_EN                  0x00                               /* TIM2                使能配置 */ //[00]:PA0,PA1,PA2,PA3,[01]:PA15,PB3,PA2,PA3,[10]:PA0,PA1,PB10,PB11,[11]:PA15,PB3,PB10,PB11
#define BSP_TIM3_EN                  0x00                               /* TIM3                使能配置 */ //[00]:PA6,PA7,PB0,PB1,[10]:PB4,PB5,PB0,PB1,[11]:PC6,PC7,PC8,PC9
#define BSP_TIM4_EN                  0x11                /*公共定时器*/ /* TIM4                使能配置 */ //[0]:PB6,PB7,PB8,PB9,[1]:PD12,PD13,PD14,PD15
#define BSP_TIM5_EN                  0x00                               /* TIM5                使能配置 */
#define BSP_TIM6_EN                  0x00                               /* TIM6                使能配置 */
#define BSP_TIM7_EN                  0x00                               /* TIM7                使能配置 */
#define BSP_TIM8_CC_EN               0x00                               /* TIM8                使能配置 */
#define BSP_TIMX_PWM_EN              0x00                               /* TIMx PWM            使能配置 */
// SPI
#define BSP_SPI1_EN                  0x00                               /* SPI1                使能配置 */ //[0]:PA4,PA5,PA6,PA7,[1]:PA15,PB3,PB4,PB5
#define BSP_SPI2_EN                  0x00                               /* SPI2                使能配置 */
#define BSP_SPI3_EN                  0x00                               /* SPI3                使能配置 */ //[0]:PA15,PB3,PB4,PB5,[1]:PA4,PC10,PC11,PC12
// DMA
#define BSP_DMA1_CHANNEL1            0x00                               /* DMA1_Channel1       使用配置 */ //ADC1,TIM2_CH3,TIM4_CH1
#define BSP_DMA1_CHANNEL2            0x00                               /* DMA1_Channel2       使用配置 */ //SPI1_RX,USART3_TX,TIM1_CH1,TIM2_UP,TIM3_CH3
#define BSP_DMA1_CHANNEL3            0x00                               /* DMA1_Channel3       使用配置 */ //SPI1_TX,USART3_RX,TIM1_CH2,TIM3_CH4/TIM3_UP
#define BSP_DMA1_CHANNEL4            0x00                               /* DMA1_Channel4       使用配置 */ //SPI/I2S2_RX,USART1_TX,I2C2_TX,TIM1_TX4/TIM1_TRIG/TIM1_COM,TIM4_CH2
#define BSP_DMA1_CHANNEL5            0x00                               /* DMA1_Channel5       使用配置 */ //SPI/I2S2_TX,USART1_RX,I2C2_RX,TIM1_UP,TIM2_CH1,TIM4_CH3
#define BSP_DMA1_CHANNEL6            0x00                               /* DMA1_Channel6       使用配置 */ //USART2_RX,I2C1_TX,TIM1_CH3,TIM3_CH1/TIM3_TRIG
#define BSP_DMA1_CHANNEL7            0x00                               /* DMA1_Channel7       使用配置 */ //USART2_TX,I2C1_RX,TIM2_CH2/TIM2_CH4,TIM4_UP
#define BSP_DMA2_CHANNEL1            0x00                               /* DMA2_Channel1       使用配置 */ //SPI/I2S3_RX,TIM5_CH4/TIM5_TRIG,TIM8_CH3/TIM8_UP
#define BSP_DMA2_CHANNEL2            0x00                               /* DMA2_Channel2       使用配置 */ //SPI/I2S3_TX,TIM5_CH3/TIM5_UP,TIM8_CH4/TIM8_TRIG,TIM8_COM
#define BSP_DMA2_CHANNEL3            0x00                               /* DMA2_Channel3       使用配置 */ //UART4_RX,TIM6_UP/DAC_CH1,TIM8_CH1
#define BSP_DMA2_CHANNEL4            0x00                               /* DMA2_Channel4       使用配置 */ //SDIO,TIM5_CH2,TIM7_UP/DAC_CH2
#define BSP_DMA2_CHANNEL5            0x00                               /* DMA2_Channel5       使用配置 */ //ADC3,UART4_TX,TIM5_CH1,TIM8_CH2
// ADC
#define BSP_ADCX_EN                  0x00                               /* ADCX                使能配置 */

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 硬件分配 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

// 操作系统调试串口+++++++++++++++++++
// 例如 串口-3: <rtconfig.h> -> #define RT_CONSOLE_DEVICE_NAME "uart3", #define BSP_USING_UART3。
// 涉及 #define .*CONSOLE.*, #define .*MSH.*, #define .*FINSH.*, #define .*SERIAL.*, #define .*UART.* （使用正则表达式查找）
#define RTT_COM3_UART_CLK_ENABLE() __HAL_RCC_USART3_CLK_ENABLE()        /* 串口时钟使能                 */
#define RTT_COM3_TX_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()         /* TX脚时钟使能                 */
#define RTT_COM3_RX_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()         /* RX脚时钟使能                 */
#define RTT_COM3_TX_GPIO             GPIOB                              /* TX 所在端口                  */
#define RTT_COM3_TX_PIN              GPIO_PIN_10                        /* TX 所在管脚                  */
#define RTT_COM3_RX_GPIO             GPIOB                              /* RX 所在端口                  */
#define RTT_COM3_RX_PIN              GPIO_PIN_11                        /* RX 所在管脚                  */
#define RTT_COM3_RX_IN_MODE          GPIO_PULLUP                        /* RX 输入模式(上拉/悬空)       //
#define RTT_COM3_AFIO_REMAP_UART() __HAL_AFIO_REMAP_USART3_ENABLE()     // 串口引脚重映射(不使用则屏蔽) */ //只有 UART1~3 才有映射

// 公共定时器+++++++++++++++++++++++++
#define BSP_MS_TICK_TIM              4 /*TIME_MS_TICK()为硬件计数器*/   /* 定时器CCR4 用于硬件计数器    */
#if (BSP_TIM4_EN & 0x11)
#define BSP_TIM4                     TIM4                               /* 定时器                       */
#define BSP_TIM4_CLK_ENABLE()      __HAL_RCC_TIM4_CLK_ENABLE()          /* 定时器时钟使能               */
#define BSP_TIM4_IRQn                TIM4_IRQn                          /* 定时器中断通道               */
#define BSP_TIM4_PRE_INT_PRIO        0                                  /* 定时器抢占中断优先级         */
#define BSP_TIM4_SUB_INT_PRIO        0                                  /* 定时器响应中断优先级         */
#define BSP_TIM4_TICK_US             10/*整除:72000000/(1000000/10)*/   /* 定时器计数节拍(如:10->10us)  */
#define BSP_TIM4_CCR1                100    /*1ms 的通用定时器*/        /* 定时器CCR1                   */
#define BSP_TIM4_CCR2                0xFFF0 /*保留其它应用使用*/        /* 定时器CCR2                   */
#define BSP_TIM4_CCR3                0xFFF0 /*保留其它应用使用*/        /* 定时器CCR3                   */
#define BSP_TIM4_CCR4                0xFFF0 /*保留其它应用使用*/        /* 定时器CCR4                   */
#endif

// 红外发送服务+++++++++++++++++++++++
// 配置PWM的频率
#define XT_IRSEND_TIM_DIV            1                                      /* 定时器的时钟分频         */
#define XT_IRSEND_TIM_PWM_HZ(hz)   ((72000000/(XT_IRSEND_TIM_DIV+1)/(hz))-1)/* PWM 100%数值(≤0xFFFF)   */

// 配置PWM的定时器
#define XT_IRSEND_TIM                TIM3                               /* 定时器                       */
#define XT_IRSEND_TIM_CLK_DI()     __HAL_RCC_TIM3_CLK_DISABLE()         /* 定时器时钟禁能               */
#define XT_IRSEND_TIM_CLK_EN()     __HAL_RCC_TIM3_CLK_ENABLE()          /* 定时器时钟使能               //
#define XT_IRSEND_TIM_AFIO_REMAP() __HAL_AFIO_REMAP_TIM3_PARTIAL()      // 定时器引脚重映射(不用则屏蔽) */ //只有 TIM1~5 才有映射 (分为:重映射[TIM4~5]、部分和完全重映射TIM1~3)

// 配置PWM的通道（只使用1路）
#define XT_IRSEND_PWM_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()         /* PWM 管脚时钟使能             */
#define XT_IRSEND_PWM_GPIO           GPIOB                              /* PWM 所在端口                 */
#define XT_IRSEND_PWM_PIN            GPIO_PIN_1                         /* PWM 所在管脚                 */
#define XT_IRSEND_PWM_OCMODE         TIM_OCMODE_PWM1 /*不能改*/         /* PWM 输出极性模式(2则反极性)  */ //使用在:非0%,非停止
#define XT_IRSEND_PWM_OCPOLARITY     TIM_OCPOLARITY_HIGH                /* PWM 有效占空比输出的电平     // //正向通道
#define XT_IRSEND_PWM_OCIDLESTATE    TIM_OCIDLESTATE_RESET              // PWM 空闲时电平(不用则屏蔽)   */ //只针对TIM1,其它定时器默认为低电平
#define XT_IRSEND_PWM_CCR            CCR4                               /* PWM 占空比寄存器(TIM3->CCR4) */
#define XT_IRSEND_PWM_TIM_CHANNEL    TIM_CHANNEL_4                      /* PWM 所在定时器通道           */
#define XT_IRSEND_TIM_DMA_ID_CC      TIM_DMA_ID_CC4                     /* 定时器DMA更新请求通道(如:CC4)*/
#define XT_IRSEND_TIM_DMA_CC         TIM_DMA_CC4                        /* 定时器DMA更新事件通道(如:CC4)*/

// 配置PWM的DMA
#define XT_IRSEND_DMA_CLK_ENABLE() __HAL_RCC_DMA1_CLK_ENABLE()          /* DMA 时钟使能                 */
#define XT_IRSEND_DMA_CHANNEL        DMA1_Channel3                      /* DMA 通道                     */
#define XT_IRSEND_DMA_IRQn           DMA1_Channel3_IRQn                 /* DMA 中断通道                 */
#define XT_IRSEND_DMA_PRE_INT_PRIO   0                                  /* DMA 通道抢占中断优先级       */
#define XT_IRSEND_DMA_SUB_INT_PRIO   0                                  /* DMA 通道响应中断优先级       */
#define XT_IRSEND_DMA_PRIORITY       DMA_PRIORITY_MEDIUM                /* DMA 通道优先级（中等）       */
#define XT_IRSEND_DMA_IRQHandler     DMA1_Channel3_IRQHandler           /* DMA 中断向量函数             */
#define XT_IRSEND_RAM_SUM            65 /*以空间换取执行效率*/          /* DMA 转传数据源大小(数据个数) */

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 操作函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void bsp_delay10us(uint32_t at10us);
extern void bsp_delay0us5(uint32_t at0us5);
extern void bsp_delay0us125(uint32_t at0us125);

//````````````````````````````````````````````````````````````````````````````````````````````````````````
void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif

#endif //#ifndef BOARD_H__
