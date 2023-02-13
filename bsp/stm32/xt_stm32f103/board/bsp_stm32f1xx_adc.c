/**
  * @file  bsp_stm32f1xx_adc.c
  * @brief ȫ��ADCģ��ת����������
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    ԭʼ�汾
  */
#define   BSP_STM32F1XX_ADC_C__
#include "bsp_stm32f1xx_adc.h"
#ifdef    BSP_STM32F1XX_ADC_X__
#undef    BSP_STM32F1XX_ADC_H__
#include "bsp_stm32f1xx_adc.h"
#endif

#ifndef XT_CHIP_INIT_2_TAB_EXPORT
#define XT_CHIP_INIT_2_TAB_EXPORT(func,desc)
#endif

#if (BSP_ADCX_EN & 0x01)

#if (BSP_ADCX_CHANNEL_TOTAL > 16) || (BSP_ADCX_CHANNEL_TOTAL == 0)
#error "[BSP_ADCX_CHANNEL_TOTAL]���ô���"
#else
#define ADCx_DMA_SIZE      (BSP_ADCX_DMA_CHANNEL_BUF_MAX * BSP_ADCX_CHANNEL_TOTAL)
#endif
uint16_t bsp_dma_adcx_value[ADCx_DMA_SIZE];

void bsp_adcx_init(void);

/**
  * @brief  ADC+DMA��ʼ��
  * @param  void
  * @return void
  */
void bsp_adc_init(void)
{
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
	
	/* ADC ʱ������ */
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
	PeriphClkInit.AdcClockSelection = BSP_ADC_DIV;
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
	
	/* ADC ��ʼ�� */
	bsp_adcx_init();
	HAL_ADCEx_Calibration_Start(&hadcx);
	HAL_ADCEx_Calibration_Start(&hadcx);
	
	/* ���������ɼ� */
	HAL_ADC_Start_DMA(&hadcx, (uint32_t *)bsp_dma_adcx_value, ADCx_DMA_SIZE); 
}
XT_CHIP_INIT_2_TAB_EXPORT(bsp_adc_init, "bsp_adc_init()");

/**
  * @brief  ADCx��ʼ��
  * @param  void
  * @return void
  */
void bsp_adcx_init(void)
{
	ADC_ChannelConfTypeDef ADC_ChannelConf;
	
	// ADC��������
	hadcx.Instance = BSP_ADCX;
	hadcx.Init.ScanConvMode = ADC_SCAN_ENABLE;
	hadcx.Init.ContinuousConvMode = ENABLE;
	hadcx.Init.DiscontinuousConvMode = DISABLE;
	hadcx.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadcx.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadcx.Init.NbrOfConversion = BSP_ADCX_CHANNEL_TOTAL;
	HAL_ADC_Init(&hadcx);
	
	// ���ò���ͨ��1
	#ifdef BSP_ADCX_CHANNEL1
	ADC_ChannelConf.Channel = BSP_ADCX_CHANNEL1;
	ADC_ChannelConf.Rank = BSP_ADCX_CHANNEL1_RANK;
	ADC_ChannelConf.SamplingTime = BSP_ADCX_XXCYCLES5;
	HAL_ADC_ConfigChannel(&hadcx, &ADC_ChannelConf);
	#endif
	
	// ���ò���ͨ��2
	#ifdef BSP_ADCX_CHANNEL2
	ADC_ChannelConf.Channel = BSP_ADCX_CHANNEL2;
	ADC_ChannelConf.Rank = BSP_ADCX_CHANNEL2_RANK;
	HAL_ADC_ConfigChannel(&hadcx, &ADC_ChannelConf);
	#endif
	
	// ���ò���ͨ��3
	#ifdef BSP_ADCX_CHANNEL3
	ADC_ChannelConf.Channel = BSP_ADCX_CHANNEL3;
	ADC_ChannelConf.Rank = BSP_ADCX_CHANNEL3_RANK;
	HAL_ADC_ConfigChannel(&hadcx, &ADC_ChannelConf);
	#endif
	
	// ���ò���ͨ��4
	#ifdef BSP_ADCX_CHANNEL4
	ADC_ChannelConf.Channel = BSP_ADCX_CHANNEL4;
	ADC_ChannelConf.Rank = BSP_ADCX_CHANNEL4_RANK;
	HAL_ADC_ConfigChannel(&hadcx, &ADC_ChannelConf);
	#endif
	
	// ���ò���ͨ��5
	#ifdef BSP_ADCX_CHANNEL5
	ADC_ChannelConf.Channel = BSP_ADCX_CHANNEL5;
	ADC_ChannelConf.Rank = BSP_ADCX_CHANNEL5_RANK;
	HAL_ADC_ConfigChannel(&hadcx, &ADC_ChannelConf);
	#endif
	
	// ���ò���ͨ��6
	#ifdef BSP_ADCX_CHANNEL6
	ADC_ChannelConf.Channel = BSP_ADCX_CHANNEL6;
	ADC_ChannelConf.Rank = BSP_ADCX_CHANNEL6_RANK;
	HAL_ADC_ConfigChannel(&hadcx, &ADC_ChannelConf);
	#endif
	
	// ���ò���ͨ��7
	#ifdef BSP_ADCX_CHANNEL7
	ADC_ChannelConf.Channel = BSP_ADCX_CHANNEL7;
	ADC_ChannelConf.Rank = BSP_ADCX_CHANNEL7_RANK;
	HAL_ADC_ConfigChannel(&hadcx, &ADC_ChannelConf);
	#endif
	
	// ���ò���ͨ��8
	#ifdef BSP_ADCX_CHANNEL8
	ADC_ChannelConf.Channel = BSP_ADCX_CHANNEL8;
	ADC_ChannelConf.Rank = BSP_ADCX_CHANNEL8_RANK;
	HAL_ADC_ConfigChannel(&hadcx, &ADC_ChannelConf);
	#endif
	
	// ���ò���ͨ��9
	#ifdef BSP_ADCX_CHANNEL9
	ADC_ChannelConf.Channel = BSP_ADCX_CHANNEL9;
	ADC_ChannelConf.Rank = BSP_ADCX_CHANNEL9_RANK;
	HAL_ADC_ConfigChannel(&hadcx, &ADC_ChannelConf);
	#endif
	
	// ���ò���ͨ��10
	#ifdef BSP_ADCX_CHANNEL10
	ADC_ChannelConf.Channel = BSP_ADCX_CHANNEL10;
	ADC_ChannelConf.Rank = BSP_ADCX_CHANNEL10_RANK;
	HAL_ADC_ConfigChannel(&hadcx, &ADC_ChannelConf);
	#endif
	
	// ���ò���ͨ��11
	#ifdef BSP_ADCX_CHANNEL11
	ADC_ChannelConf.Channel = BSP_ADCX_CHANNEL11;
	ADC_ChannelConf.Rank = BSP_ADCX_CHANNEL11_RANK;
	HAL_ADC_ConfigChannel(&hadcx, &ADC_ChannelConf);
	#endif
	
	// ���ò���ͨ��12
	#ifdef BSP_ADCX_CHANNEL12
	ADC_ChannelConf.Channel = BSP_ADCX_CHANNEL12;
	ADC_ChannelConf.Rank = BSP_ADCX_CHANNEL12_RANK;
	HAL_ADC_ConfigChannel(&hadcx, &ADC_ChannelConf);
	#endif
	
	// ���ò���ͨ��13
	#ifdef BSP_ADCX_CHANNEL13
	ADC_ChannelConf.Channel = BSP_ADCX_CHANNEL13;
	ADC_ChannelConf.Rank = BSP_ADCX_CHANNEL13_RANK;
	HAL_ADC_ConfigChannel(&hadcx, &ADC_ChannelConf);
	#endif
	
	// ���ò���ͨ��14
	#ifdef BSP_ADCX_CHANNEL14
	ADC_ChannelConf.Channel = BSP_ADCX_CHANNEL14;
	ADC_ChannelConf.Rank = BSP_ADCX_CHANNEL14_RANK;
	HAL_ADC_ConfigChannel(&hadcx, &ADC_ChannelConf);
	#endif
	
	// ���ò���ͨ��15
	#ifdef BSP_ADCX_CHANNEL15
	ADC_ChannelConf.Channel = BSP_ADCX_CHANNEL15;
	ADC_ChannelConf.Rank = BSP_ADCX_CHANNEL15_RANK;
	HAL_ADC_ConfigChannel(&hadcx, &ADC_ChannelConf);
	#endif
	
	// ���ò���ͨ��16
	#ifdef BSP_ADCX_CHANNEL16
	ADC_ChannelConf.Channel = BSP_ADCX_CHANNEL16;
	ADC_ChannelConf.Rank = BSP_ADCX_CHANNEL16_RANK;
	HAL_ADC_ConfigChannel(&hadcx, &ADC_ChannelConf);
	#endif
}

/**
  * @brief  ADCx��ʼ������HAL��ص���
  * @param  hadc
  * @return void
  */
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	if (hadc->Instance == BSP_ADCX)
	{
		/* ����ʱ��ʹ�� */
		BSP_ADCX_CLK_ENABLE();
		
		/* ADת��ͨ�����ų�ʼ�� */
		#ifdef BSP_ADCX_CHANNEL1
		BSP_ADCX_CHANNEL1_CLK_EN();
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; 
		GPIO_InitStruct.Pin = BSP_ADCX_CHANNEL1_PIN;
		HAL_GPIO_Init(BSP_ADCX_CHANNEL1_GPIO, &GPIO_InitStruct);
		#endif
		  
		#ifdef BSP_ADCX_CHANNEL2
		BSP_ADCX_CHANNEL2_CLK_EN();
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; 
		GPIO_InitStruct.Pin = BSP_ADCX_CHANNEL2_PIN;
		HAL_GPIO_Init(BSP_ADCX_CHANNEL2_GPIO, &GPIO_InitStruct);
		#endif
		
		#ifdef BSP_ADCX_CHANNEL3
		BSP_ADCX_CHANNEL3_CLK_EN();
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; 
		GPIO_InitStruct.Pin = BSP_ADCX_CHANNEL3_PIN;
		HAL_GPIO_Init(BSP_ADCX_CHANNEL3_GPIO, &GPIO_InitStruct);
		#endif
		
		#ifdef BSP_ADCX_CHANNEL4
		BSP_ADCX_CHANNEL4_CLK_EN();
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; 
		GPIO_InitStruct.Pin = BSP_ADCX_CHANNEL4_PIN;
		HAL_GPIO_Init(BSP_ADCX_CHANNEL4_GPIO, &GPIO_InitStruct);
		#endif
		
		#ifdef BSP_ADCX_CHANNEL5
		BSP_ADCX_CHANNEL5_CLK_EN();
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; 
		GPIO_InitStruct.Pin = BSP_ADCX_CHANNEL5_PIN;
		HAL_GPIO_Init(BSP_ADCX_CHANNEL5_GPIO, &GPIO_InitStruct);
		#endif
		
		#ifdef BSP_ADCX_CHANNEL6
		BSP_ADCX_CHANNEL6_CLK_EN();
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; 
		GPIO_InitStruct.Pin = BSP_ADCX_CHANNEL6_PIN;
		HAL_GPIO_Init(BSP_ADCX_CHANNEL6_GPIO, &GPIO_InitStruct);
		#endif
		
		#ifdef BSP_ADCX_CHANNEL7
		BSP_ADCX_CHANNEL7_CLK_EN();
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; 
		GPIO_InitStruct.Pin = BSP_ADCX_CHANNEL7_PIN;
		HAL_GPIO_Init(BSP_ADCX_CHANNEL7_GPIO, &GPIO_InitStruct);
		#endif
		
		#ifdef BSP_ADCX_CHANNEL8
		BSP_ADCX_CHANNEL8_CLK_EN();
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; 
		GPIO_InitStruct.Pin = BSP_ADCX_CHANNEL8_PIN;
		HAL_GPIO_Init(BSP_ADCX_CHANNEL8_GPIO, &GPIO_InitStruct);
		#endif
		
		#ifdef BSP_ADCX_CHANNEL9
		BSP_ADCX_CHANNEL9_CLK_EN();
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; 
		GPIO_InitStruct.Pin = BSP_ADCX_CHANNEL9_PIN;
		HAL_GPIO_Init(BSP_ADCX_CHANNEL9_GPIO, &GPIO_InitStruct);
		#endif
		
		#ifdef BSP_ADCX_CHANNEL10
		BSP_ADCX_CHANNEL10_CLK_EN();
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; 
		GPIO_InitStruct.Pin = BSP_ADCX_CHANNEL10_PIN;
		HAL_GPIO_Init(BSP_ADCX_CHANNEL10_GPIO, &GPIO_InitStruct);
		#endif
		
		#ifdef BSP_ADCX_CHANNEL11
		BSP_ADCX_CHANNEL11_CLK_EN();
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; 
		GPIO_InitStruct.Pin = BSP_ADCX_CHANNEL11_PIN;
		HAL_GPIO_Init(BSP_ADCX_CHANNEL11_GPIO, &GPIO_InitStruct);
		#endif
		
		#ifdef BSP_ADCX_CHANNEL12
		BSP_ADCX_CHANNEL12_CLK_EN();
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; 
		GPIO_InitStruct.Pin = BSP_ADCX_CHANNEL12_PIN;
		HAL_GPIO_Init(BSP_ADCX_CHANNEL12_GPIO, &GPIO_InitStruct);
		#endif
		
		#ifdef BSP_ADCX_CHANNEL13
		BSP_ADCX_CHANNEL13_CLK_EN();
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; 
		GPIO_InitStruct.Pin = BSP_ADCX_CHANNEL13_PIN;
		HAL_GPIO_Init(BSP_ADCX_CHANNEL13_GPIO, &GPIO_InitStruct);
		#endif
		
		#ifdef BSP_ADCX_CHANNEL14
		BSP_ADCX_CHANNEL14_CLK_EN();
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; 
		GPIO_InitStruct.Pin = BSP_ADCX_CHANNEL14_PIN;
		HAL_GPIO_Init(BSP_ADCX_CHANNEL14_GPIO, &GPIO_InitStruct);
		#endif
		
		#ifdef BSP_ADCX_CHANNEL15
		BSP_ADCX_CHANNEL15_CLK_EN();
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; 
		GPIO_InitStruct.Pin = BSP_ADCX_CHANNEL15_PIN;
		HAL_GPIO_Init(BSP_ADCX_CHANNEL15_GPIO, &GPIO_InitStruct);
		#endif
		
		#ifdef BSP_ADCX_CHANNEL16
		BSP_ADCX_CHANNEL16_CLK_EN();
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; 
		GPIO_InitStruct.Pin = BSP_ADCX_CHANNEL16_PIN;
		HAL_GPIO_Init(BSP_ADCX_CHANNEL16_GPIO, &GPIO_InitStruct);
		#endif
		
		/* DMAʱ��ʹ�� */
		BSP_ADCX_DMA_CLK_ENABLE();
		
		/* DMA�����ʼ������ */  
		hdma_adcx.Instance = BSP_ADCX_DMA_CHANNEL;
		hdma_adcx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_adcx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_adcx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_adcx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
		hdma_adcx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
		hdma_adcx.Init.Mode = DMA_CIRCULAR;
		hdma_adcx.Init.Priority = DMA_PRIORITY_HIGH;
		HAL_DMA_Init(&hdma_adcx);
		
		/* ����DMA */
		__HAL_LINKDMA(hadc ,DMA_Handle, hdma_adcx);
		
		/* �����ж����ȼ����ú�ʹ���ж� */
		//HAL_NVIC_SetPriority(BSP_ADCX_DMA_IRQn, BSP_ADCX_DMA_PRE_INT_PRIO, BSP_ADCX_DMA_SUB_INT_PRIO);
		//HAL_NVIC_EnableIRQ(BSP_ADCX_DMA_IRQn);
	}
}

/**
  * @brief  ADCx����ʼ������HAL��ص���
  * @param  hadc
  * @return void
  */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
	if (hadc->Instance == BSP_ADCX)
	{
		/* ����ADC����ʱ�� */
		BSP_ADCX_CLK_DISABLE();
		
		/* ADת��ͨ�����ŷ���ʼ�� */
		#ifdef BSP_ADCX_CHANNEL1
		HAL_GPIO_DeInit(BSP_ADCX_CHANNEL1_GPIO, BSP_ADCX_CHANNEL1_PIN);
		#endif
		#ifdef BSP_ADCX_CHANNEL2
		HAL_GPIO_DeInit(BSP_ADCX_CHANNEL2_GPIO, BSP_ADCX_CHANNEL2_PIN);
		#endif
		#ifdef BSP_ADCX_CHANNEL3
		HAL_GPIO_DeInit(BSP_ADCX_CHANNEL3_GPIO, BSP_ADCX_CHANNEL3_PIN);
		#endif
		#ifdef BSP_ADCX_CHANNEL4
		HAL_GPIO_DeInit(BSP_ADCX_CHANNEL4_GPIO, BSP_ADCX_CHANNEL4_PIN);
		#endif
		#ifdef BSP_ADCX_CHANNEL5
		HAL_GPIO_DeInit(BSP_ADCX_CHANNEL5_GPIO, BSP_ADCX_CHANNEL5_PIN);
		#endif
		#ifdef BSP_ADCX_CHANNEL6
		HAL_GPIO_DeInit(BSP_ADCX_CHANNEL6_GPIO, BSP_ADCX_CHANNEL6_PIN);
		#endif
		#ifdef BSP_ADCX_CHANNEL7
		HAL_GPIO_DeInit(BSP_ADCX_CHANNEL7_GPIO, BSP_ADCX_CHANNEL7_PIN);
		#endif
		#ifdef BSP_ADCX_CHANNEL8
		HAL_GPIO_DeInit(BSP_ADCX_CHANNEL8_GPIO, BSP_ADCX_CHANNEL8_PIN);
		#endif
		#ifdef BSP_ADCX_CHANNEL9
		HAL_GPIO_DeInit(BSP_ADCX_CHANNEL9_GPIO, BSP_ADCX_CHANNEL9_PIN);
		#endif
		#ifdef BSP_ADCX_CHANNEL10
		HAL_GPIO_DeInit(BSP_ADCX_CHANNEL10_GPIO, BSP_ADCX_CHANNEL10_PIN);
		#endif
		#ifdef BSP_ADCX_CHANNEL11
		HAL_GPIO_DeInit(BSP_ADCX_CHANNEL11_GPIO, BSP_ADCX_CHANNEL11_PIN);
		#endif
		#ifdef BSP_ADCX_CHANNEL12
		HAL_GPIO_DeInit(BSP_ADCX_CHANNEL12_GPIO, BSP_ADCX_CHANNEL12_PIN);
		#endif
		#ifdef BSP_ADCX_CHANNEL13
		HAL_GPIO_DeInit(BSP_ADCX_CHANNEL13_GPIO, BSP_ADCX_CHANNEL13_PIN);
		#endif
		#ifdef BSP_ADCX_CHANNEL14
		HAL_GPIO_DeInit(BSP_ADCX_CHANNEL14_GPIO, BSP_ADCX_CHANNEL14_PIN);
		#endif
		#ifdef BSP_ADCX_CHANNEL15
		HAL_GPIO_DeInit(BSP_ADCX_CHANNEL15_GPIO, BSP_ADCX_CHANNEL15_PIN);
		#endif
		#ifdef BSP_ADCX_CHANNEL16
		HAL_GPIO_DeInit(BSP_ADCX_CHANNEL16_GPIO, BSP_ADCX_CHANNEL16_PIN);
		#endif
		
		/* DMA���跴��ʼ��*/
		HAL_DMA_DeInit(hadc->DMA_Handle);
	}
}

/**
  * @brief  ��ȡDMA������ADC����
  * @param  scan_ch      ������·ͨ������(ɨ��ͨ��)(1~BSP_ADCX_CHANNEL_TOTAL)
  * @param  *p_buf       �洢��
  * @param  total        Ҫ����ADC���ݵĸ���(1~BSP_ADCX_DMA_CHANNEL_BUF_MAX)
  * @return ����ADC���ݵĸ���
  */
uint16_t bsp_adcx_ch_data_get(uint8_t scan_ch, uint16_t *p_buf, uint16_t total)
{
    uint32_t i;
    
	if ((scan_ch == 0) || (scan_ch > BSP_ADCX_CHANNEL_TOTAL) || (p_buf == 0) || (total == 0))
    {
        return (0);
    }
	scan_ch -= 1;
	
    for (i=0; i<BSP_ADCX_DMA_CHANNEL_BUF_MAX; i++,total--,p_buf++)
    {
        *p_buf = bsp_dma_adcx_value[(i * BSP_ADCX_CHANNEL_TOTAL) + scan_ch];
        if (total <= 1)
        {
            return (i + 1);
        }
    }
    return (BSP_ADCX_DMA_CHANNEL_BUF_MAX);
}

/**
  * @brief  ��ȡDMA������ADCͨ����ƽ����
  * @param  scan_ch      ������·ͨ������(ɨ��ͨ��)(1~BSP_ADCX_CHANNEL_TOTAL)
  * @return ��·ɨ��ͨ��AD��ƽ��ֵ
  */
uint32_t bsp_adcx_ch_average_get(uint8_t scan_ch)
{
	uint32_t i;
	uint32_t tmp = 0;
	
	if ((scan_ch == 0) || (scan_ch > BSP_ADCX_CHANNEL_TOTAL))
	{
		return (0);
	}
	scan_ch -= 1;
	
	for (i=0; i<BSP_ADCX_DMA_CHANNEL_BUF_MAX; i++)
	{
		tmp += bsp_dma_adcx_value[(i * BSP_ADCX_CHANNEL_TOTAL) + scan_ch];
	}
	return (tmp / BSP_ADCX_DMA_CHANNEL_BUF_MAX);
}

#endif //#if (BSP_ADCX_EN & 0x01)
