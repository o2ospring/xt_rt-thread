/**
  * @file  bsp_stm32f1xx_wdg.c
  * @brief ȫ�ֿ��Ź���������
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-18     o2ospring    ԭʼ�汾
  */
#define   BSP_STM32F1XX_WDG_C__
#include "bsp_stm32f1xx_wdg.h"
#ifdef    BSP_STM32F1XX_WDG_X__
#undef    BSP_STM32F1XX_WDG_H__
#include "bsp_stm32f1xx_wdg.h"
#endif

#if (BSP_WDG_EN & 0x01)	
#if (BSP_WDG_CFG == 0)
#warning "[BSP_WDG_CFG]��ֹʱ��ҪΪ������Բ���Ӱ�죬������Ʒ�����"
#endif
#if (BSP_WDG_CFG >= 2)
#error "Ŀǰ������֧��[���ڿ��Ź�]����������������[BSP_WDG_CFG]"
#endif
#endif

#ifndef XT_APP_TLOOP_1_TAB_EXPORT
#define XT_APP_TLOOP_1_TAB_EXPORT(func,ms)
#endif

#if (BSP_WDG_EN & 0x01)
#if (BSP_WDG_CFG == 1)
uint8_t iwdg_runner = 0;
#endif
/**
  * @brief  ���Ź���ʼ��
  * @param  void
  * @return void
  */
void bsp_wdg_init(void)
{
	#if (BSP_WDG_CFG == 1)
	// �������Ź���ʼ��(��Ҫ���ڼ���Ӳ������) ############################################################
	//                                  ����LSIʱ��, ����Ʈ:�ֲ�˵LSIʱ��Ƶ�ʴ�Լ32kHz(��30kHz��60kHz֮��)
	// �ر�ע��: 1. �������Ź�ʱ�����ڲ�32KHZ�ṩ�����Բ�����ʱ��Ӱ�죬��һ���������Ź��������ڵ��Թ����У�
	//              ��ͣ�������У����Ź�Ҳ������ֹͣ���ڸ�λʱ�䵽���ԻὫϵͳ��λ��
	//           2. ���ܻ�������������������Ӳ�����Ź���Ȼ���û�����س����ˣ�JTAG����������Ϊ����¼ǰһ
	//              �̳������������Ź���JTAG���/������;�ͱ�ǿ�и�λ����������ϵ�����1�����������Ź�!!
	
	IWDG_HandleTypeDef hiwdg;
	
	hiwdg.Instance = IWDG;
	hiwdg.Init.Prescaler = IWDG_PRESCALER_32; // 40Kʱ��32��Ƶ(��32��Ƶ��ÿ����ԼΪ��1ms��)
	hiwdg.Init.Reload = IWDG_TIMEOUT_SET;     // ��������ֵ   (0-0x0FFF)(��:349->����ʱ 349+1 ������)
	if (HAL_IWDG_Init(&hiwdg) != HAL_OK) {}   // ����������   (IWDG timeout = 1ms * (349+1) = 350 ms)
	#endif
}

/**
  * @brief  ���ÿ��Ź�������
  * @param  runner     �����ߣ�0:�����ʱ��ι��, 1:Ӳ����ʱ��ι����
  * @return void
  */
void wdg_runner_set(uint8_t runner)
{
	#if (BSP_WDG_CFG == 1)
	if (runner > 1) return;
	iwdg_runner = runner;
	#endif
}

/**
  * @brief  ���Ź����ã�ι����
  * @param  runner     �����ߣ�0:�����ʱ��ι��, 1:Ӳ����ʱ��ι����
  * @return void
  */
void wdg_reload_counter(uint8_t runner)
{
	#if (BSP_WDG_CFG == 1)
	// ���ڶ������Ź�ι��
	// ע��: Ӧ���������ʱ���һ��ʱ����ι��(����1/3ʱ����),���������Ʈ�������⸴λ
	struct { IWDG_TypeDef *Instance; }   hiwdg = { IWDG };
	                                     //IWDG_HandleTypeDef hiwdg;
	if (runner == iwdg_runner) {         //hiwdg.Instance = IWDG;
	__HAL_IWDG_RELOAD_COUNTER(&hiwdg); } //HAL_IWDG_Refresh(&hiwdg);  // ������������ι����
	#endif
}

//Ӧ�ã������ʱ��ι��
void wdg_reload_software(void)
{
	wdg_reload_counter(0);
}
XT_APP_TLOOP_1_TAB_EXPORT(wdg_reload_software, 100/*ms*/);

#endif  //#if (BSP_WDG_EN & 0x01)
