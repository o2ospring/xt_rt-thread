/**
  * @file  bsp_stm32f1xx_adc.h
  * @brief ȫ��ADCģ��ת����������
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    ԭʼ�汾
  */
#ifndef BSP_STM32F1XX_ADC_H__
#define BSP_STM32F1XX_ADC_H__

#include <stdint.h> //////////////////////// <- ʹ�õ����ݶ��壬��: int8_t, uint32_t ��
#include "xt_comdef.h" ///////////////////// <- ���ú궨�弯�ϣ���: XT_BIT_SET ��
#include "board.h"   /////////////////////// <- ��������Ӳ����Դ����ͷ�ļ�!!!!!!!!!!!!!!!
#include "stm32f1xx.h" ///////////////////// <- ����STM32F103��Ƭ��HAL��
/*
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_conf.h" */

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ ���Ŷ��� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#ifdef BSP_STM32F1XX_ADC_C__
#undef  BSP_EXT
#define BSP_EXT
#else
#undef  BSP_EXT
#define BSP_EXT  extern
#endif

/*
    APB1�������Ϊ36MHz, APB2�������Ϊ72MHz, ADC�ķ�ƵΪ RCC_ADCPCLK2_DIVx, 
	����:                                                 RCC_ADCPCLK2_DIV6
    ADC1,2,3ʱ�����Ϊ: ADCCLK = APB2/6 = 72MHz/6 = 12MHz -> ���Ƶ������:14MHz
*//*
	��ʽ: ��ת��ʱ�� = (1000000 / ADCCLK) * (ADC_SAMPLETIME_xx + 12.5)
	��ת��ʱ��: TCONV = ����Ҫ���ٸ����� + 12.5������(�̶�)
	���磺
	�� ADCCLK = 12MHz �� ADC_SAMPLETIME_13CYCLES_5 -> 13.5 ���ڵĲ���ʱ��
	��ת��ʱ��: TCONV = 13.5 + 12.5 = 26 ���� => 2.166666666667��s
*/

#ifndef BSP_ADC_DIV //////////////////
// ����ADCʱ��                       (������������ADC��ͳһʱ�ӣ�ǿ�ҽ�����"board.h"����!!!!!!!!!)
#define BSP_ADC_DIV                  RCC_ADCPCLK2_DIV8                  /* ADC 8��Ƶ=9MHz(�������14MHz)*/
#endif ///////////////////////////////

#if (BSP_ADCX_EN & 0x01) && !(defined BSP_ADCX) /////////////////////////

// ����ADCģ��
#define BSP_ADCX                     ADC1                               /* ADC Ӳ��ģ��                 */
#define BSP_ADCX_XXCYCLES5           ADC_SAMPLETIME_55CYCLES_5          /* ADC ��������                 */
#define BSP_ADCX_CLK_ENABLE()      __HAL_RCC_ADC1_CLK_ENABLE()          /* ADC ʱ��ʹ��                 */
#define BSP_ADCX_CLK_DISABLE()     __HAL_RCC_ADC1_CLK_DISABLE()         /* ADC ʱ�ӽ���                 */
#define BSP_ADCX_DMA_CLK_ENABLE()  __HAL_RCC_DMA1_CLK_ENABLE()          /* DMA ʱ�ӽ���                 */
#define BSP_ADCX_DMA_CHANNEL         DMA1_Channel1                      /* DMA ͨ��  (ע:����ҪDMA�ж�) */

// ����ADC����ͨ��1
#define BSP_ADCX_CHANNEL1_CLK_EN() __HAL_RCC_GPIOB_CLK_ENABLE()         /* ADC ͨ���ܽ�ʱ��ʹ��         */
#define BSP_ADCX_CHANNEL1_GPIO       GPIOB                              /* ADC ͨ�����ڶ˿�             */
#define BSP_ADCX_CHANNEL1_PIN        GPIO_PIN_0                         /* ADC ͨ�����ڹܽ�             */
#define BSP_ADCX_CHANNEL1            ADC_CHANNEL_8                      /* ADC ͨ��                     */
#define BSP_ADCX_CHANNEL1_RANK       1                                  /* ADC ͨ��ɨ�������1 (1~16) */

// ����ADC����ͨ��2
#define BSP_ADCX_CHANNEL2_CLK_EN() __HAL_RCC_GPIOB_CLK_ENABLE()         /* ADC ͨ���ܽ�ʱ��ʹ��         */
#define BSP_ADCX_CHANNEL2_GPIO       GPIOB                              /* ADC ͨ�����ڶ˿�             */
#define BSP_ADCX_CHANNEL2_PIN        GPIO_PIN_1                         /* ADC ͨ�����ڹܽ�             */
#define BSP_ADCX_CHANNEL2            ADC_CHANNEL_9                      /* ADC ͨ��                     */
#define BSP_ADCX_CHANNEL2_RANK       2                                  /* ADC ͨ��ɨ�������2 (1~16) */

// ����ADC����ͨ��3
#define BSP_ADCX_CHANNEL3_CLK_EN() __HAL_RCC_GPIOC_CLK_ENABLE()         /* ADC ͨ���ܽ�ʱ��ʹ��         */
#define BSP_ADCX_CHANNEL3_GPIO       GPIOC                              /* ADC ͨ�����ڶ˿�             */
#define BSP_ADCX_CHANNEL3_PIN        GPIO_PIN_4                         /* ADC ͨ�����ڹܽ�             */
#define BSP_ADCX_CHANNEL3            ADC_CHANNEL_14                     /* ADC ͨ��                     */
#define BSP_ADCX_CHANNEL3_RANK       3                                  /* ADC ͨ��ɨ�������3 (1~16) */

// ����ADC����ͨ��4
#define BSP_ADCX_CHANNEL4_CLK_EN() __HAL_RCC_GPIOC_CLK_ENABLE()         /* ADC ͨ���ܽ�ʱ��ʹ��         */
#define BSP_ADCX_CHANNEL4_GPIO       GPIOC                              /* ADC ͨ�����ڶ˿�             */
#define BSP_ADCX_CHANNEL4_PIN        GPIO_PIN_5                         /* ADC ͨ�����ڹܽ�             */
#define BSP_ADCX_CHANNEL4            ADC_CHANNEL_15                     /* ADC ͨ��                     */
#define BSP_ADCX_CHANNEL4_RANK       4                                  /* ADC ͨ��ɨ�������4 (1~16) */

#define BSP_ADCX_CHANNEL_TOTAL       4 /*ɨ����������1��ʼ��Ҫ����*//* ADC ɨ��ͨ������(1~16)       */
#define BSP_ADCX_DMA_CHANNEL_BUF_MAX 10                                 /* ADC ÿ��ͨ�������С(��Ա��) */

BSP_EXT ADC_HandleTypeDef            hadcx;                             /* ADC ���(ȫ�ֱ�������)       */
BSP_EXT DMA_HandleTypeDef            hdma_adcx;                         /* DMA ���(ȫ�ֱ�������)       */

#endif ///////////////////////////////

/* ���䣺STM32F103 DMA ��Դ����
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
/*++++++++++++++++++++++++++++++++++++++++++++++ �������� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void bsp_adc_init(void);

extern uint16_t bsp_adcx_ch_data_get(uint8_t scan_ch, uint16_t *p_buf, uint16_t total);
extern uint32_t bsp_adcx_ch_average_get(uint8_t scan_ch);

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef BSP_STM32F1XX_ADC_H__
