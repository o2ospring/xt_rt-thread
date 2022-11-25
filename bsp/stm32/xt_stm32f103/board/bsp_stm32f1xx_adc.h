/**
  * @file  bsp_stm32f1xx_adc.h
  * @brief 全局ADC模数转换驱动程序
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    原始版本
  */
#ifndef BSP_STM32F1XX_ADC_H__
#define BSP_STM32F1XX_ADC_H__

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

#ifdef BSP_STM32F1XX_ADC_C__
#undef  BSP_EXT
#define BSP_EXT
#else
#undef  BSP_EXT
#define BSP_EXT  extern
#endif

/*
    APB1最高限制为36MHz, APB2最高限制为72MHz, ADC的分频为 RCC_ADCPCLK2_DIVx, 
	例如:                                                 RCC_ADCPCLK2_DIV6
    ADC1,2,3时钟最高为: ADCCLK = APB2/6 = 72MHz/6 = 12MHz -> 最高频率限制:14MHz
*//*
	公式: 总转换时间 = (1000000 / ADCCLK) * (ADC_SAMPLETIME_xx + 12.5)
	总转换时间: TCONV = 采样要多少个周期 + 12.5个周期(固定)
	例如：
	当 ADCCLK = 12MHz 和 ADC_SAMPLETIME_13CYCLES_5 -> 13.5 周期的采样时间
	总转换时间: TCONV = 13.5 + 12.5 = 26 周期 => 2.166666666667μs
*/

#ifndef BSP_ADC_DIV //////////////////
// 配置ADC时钟                       (★★★★★★★所有ADC的统一时钟，强烈建议是"board.h"定义!!!!!!!!!)
#define BSP_ADC_DIV                  RCC_ADCPCLK2_DIV8                  /* ADC 8分频=9MHz(最高限制14MHz)*/
#endif ///////////////////////////////

#if (BSP_ADCX_EN & 0x01) && !(defined BSP_ADCX) /////////////////////////

// 配置ADC模块
#define BSP_ADCX                     ADC1                               /* ADC 硬件模块                 */
#define BSP_ADCX_XXCYCLES5           ADC_SAMPLETIME_55CYCLES_5          /* ADC 采样周期                 */
#define BSP_ADCX_CLK_ENABLE()      __HAL_RCC_ADC1_CLK_ENABLE()          /* ADC 时钟使能                 */
#define BSP_ADCX_CLK_DISABLE()     __HAL_RCC_ADC1_CLK_DISABLE()         /* ADC 时钟禁能                 */
#define BSP_ADCX_DMA_CLK_ENABLE()  __HAL_RCC_DMA1_CLK_ENABLE()          /* DMA 时钟禁能                 */
#define BSP_ADCX_DMA_CHANNEL         DMA1_Channel1                      /* DMA 通道  (注:不需要DMA中断) */

// 配置ADC采样通道1
#define BSP_ADCX_CHANNEL1_CLK_EN() __HAL_RCC_GPIOB_CLK_ENABLE()         /* ADC 通道管脚时钟使能         */
#define BSP_ADCX_CHANNEL1_GPIO       GPIOB                              /* ADC 通道所在端口             */
#define BSP_ADCX_CHANNEL1_PIN        GPIO_PIN_0                         /* ADC 通道所在管脚             */
#define BSP_ADCX_CHANNEL1            ADC_CHANNEL_8                      /* ADC 通道                     */
#define BSP_ADCX_CHANNEL1_RANK       1                                  /* ADC 通道扫描次序编号1 (1~16) */

// 配置ADC采样通道2
#define BSP_ADCX_CHANNEL2_CLK_EN() __HAL_RCC_GPIOB_CLK_ENABLE()         /* ADC 通道管脚时钟使能         */
#define BSP_ADCX_CHANNEL2_GPIO       GPIOB                              /* ADC 通道所在端口             */
#define BSP_ADCX_CHANNEL2_PIN        GPIO_PIN_1                         /* ADC 通道所在管脚             */
#define BSP_ADCX_CHANNEL2            ADC_CHANNEL_9                      /* ADC 通道                     */
#define BSP_ADCX_CHANNEL2_RANK       2                                  /* ADC 通道扫描次序编号2 (1~16) */

// 配置ADC采样通道3
#define BSP_ADCX_CHANNEL3_CLK_EN() __HAL_RCC_GPIOC_CLK_ENABLE()         /* ADC 通道管脚时钟使能         */
#define BSP_ADCX_CHANNEL3_GPIO       GPIOC                              /* ADC 通道所在端口             */
#define BSP_ADCX_CHANNEL3_PIN        GPIO_PIN_4                         /* ADC 通道所在管脚             */
#define BSP_ADCX_CHANNEL3            ADC_CHANNEL_14                     /* ADC 通道                     */
#define BSP_ADCX_CHANNEL3_RANK       3                                  /* ADC 通道扫描次序编号3 (1~16) */

// 配置ADC采样通道4
#define BSP_ADCX_CHANNEL4_CLK_EN() __HAL_RCC_GPIOC_CLK_ENABLE()         /* ADC 通道管脚时钟使能         */
#define BSP_ADCX_CHANNEL4_GPIO       GPIOC                              /* ADC 通道所在端口             */
#define BSP_ADCX_CHANNEL4_PIN        GPIO_PIN_5                         /* ADC 通道所在管脚             */
#define BSP_ADCX_CHANNEL4            ADC_CHANNEL_15                     /* ADC 通道                     */
#define BSP_ADCX_CHANNEL4_RANK       4                                  /* ADC 通道扫描次序编号4 (1~16) */

#define BSP_ADCX_CHANNEL_TOTAL       4 /*扫描次序编号须从1开始且要连续*//* ADC 扫描通道总数(1~16)       */
#define BSP_ADCX_DMA_CHANNEL_BUF_MAX 10                                 /* ADC 每组通道数组大小(组员数) */

BSP_EXT ADC_HandleTypeDef            hadcx;                             /* ADC 句柄(全局变量声明)       */
BSP_EXT DMA_HandleTypeDef            hdma_adcx;                         /* DMA 句柄(全局变量声明)       */

#endif ///////////////////////////////

/* 补充：STM32F103 DMA 资源介绍
DMA1_Channel1: ADC1,TIM2_CH3,TIM4_CH1
DMA1_Channel2: SPI1_RX,USART3_TX,TIM1_CH1,TIM2_UP,TIM3_CH3
DMA1_Channel3: SPI1_TX,USART3_RX,TIM1_CH2,TIM3_CH4/TIM3_UP
DMA1_Channel4: SPI/I2S2_RX,USART1_TX,I2C2_TX,TIM1_TX4/TIM1_TRIG/TIM1_COM,TIM4_CH2
DMA1_Channel5: SPI/I2S2_TX,USART1_RX,I2C2_RX,TIM1_UP,TIM2_CH1,TIM4_CH3
DMA1_Channel6: USART2_RX,I2C1_TX,TIM1_CH3,TIM3_CH1/TIM3_TRIG
DMA1_Channel7: USART2_TX,I2C1_RX,TIM2_CH2/TIM2_CH4,TIM4_UP
DMA2_Channel1: SPI/I2S3_RX,TIM5_CH4/TIM5_TRIG,TIM8_CH3/TIM8_UP
DMA2_Channel2: SPI/I2S3_TX,TIM5_CH3/TIM5_UP,TIM8_CH4/TIM8_TRIG,TIM8_COM
DMA2_Channel3: UART4_RX,TIM6_UP/DAC_CH1,TIM8_CH1
DMA2_Channel4: SDIO,TIM5_CH2,TIM7_UP/DAC_CH2
DMA2_Channel5: ADC3,UART4_TX,TIM5_CH1,TIM8_CH2
*/

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 操作函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void bsp_adc_init(void);

extern uint16_t bsp_adcx_ch_data_get(uint8_t scan_ch, uint16_t *p_buf, uint16_t total);
extern uint32_t bsp_adcx_ch_average_get(uint8_t scan_ch);

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef BSP_STM32F1XX_ADC_H__
