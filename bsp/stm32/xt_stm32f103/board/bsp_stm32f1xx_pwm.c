/**
  * @file  bsp_stm32f1xx_pwm.c
  * @brief ȫ�ֶ�ʱ��PWM��������
  * @notice ������ֻ��Ϊ��ʼ���ο����룬��ΪPWMһ��ר����ĳ��Ӧ��ģ��
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-19     o2ospring    ԭʼ�汾
  *
  * 1. ��ʱ��������������˵��:
  *    TIM1_CHx : ������PWM�����(��ע:[TIM1_CHxN]��[TIM1_CHx]�Ļ������,��������H�������������ʹ�)
  *    TIM1_CHxN: ר�õ������,��[TIM1_CHx]���������������ʹܡ����DeadtimeΪ0�������߷��ࣻ
  *               ���Deadtime��Ϊ0������TIM1_CHxN�ϲ�����Deadtime����ֹ���¹��ʹ�ͬʱ��ͨ��
  *    TIM1_BKIN: �Ǽ�ɲ���룬�����ر�TIM1�������
  *    TIM1_ETR : ���ⲿ��������ܽš�
  *
  * 2. ���ڶ�ʱ�����ù�����ӳ�䣬��鿴��STM32_RM_CH_V10_1.pdf����118ҳ��8.3.7 ��ʱ�����ù�����ӳ�䡽
  *    TIM1 -> [00]:PA8,PA9,PA10,PA11,[01]:PA8,PA9,PA10,PA11,[11]:PE9,PE11,PE13,PE14
  *    TIM2 -> [00]:PA0,PA1,PA2,PA3,[01]:PA15,PB3,PA2,PA3,[10]:PA0,PA1,PB10,PB11,[11]:PA15,PB3,PB10,PB11
  *    TIM3 -> [00]:PA6,PA7,PB0,PB1,[10]:PB4,PB5,PB0,PB1,[11]:PC6,PC7,PC8,PC9
  *    TIM4 -> [0]:PB6,PB7,PB8,PB9,[1]:PD12,PD13,PD14,PD15
  */
#define   BSP_STM32F1XX_PWM_C__
#include "bsp_stm32f1xx_pwm.h"
#ifdef    BSP_STM32F1XX_PWM_X__
#undef    BSP_STM32F1XX_PWM_H__
#include "bsp_stm32f1xx_pwm.h"
#endif

#ifndef XT_CHIP_INIT_5_TAB_EXPORT
#define XT_CHIP_INIT_5_TAB_EXPORT(func,desc)
#endif

/**
  * @brief  ��ʱ��n��PWM�������ʼ��
  * @param  void
  * @return void
  */
#if (BSP_TIMX_PWM_EN & 0x01)
void bsp_pwm_init(void)
{
	// TIM2,3,4,5,6,7
	// �����APB1Ԥ��Ƶ=1ʱ,��ʱ��x1��Ƶ���;
	// ����������Ԥ��Ƶֵʱ,��ʱ��x2��Ƶ���.
	// ��: APB1Ԥ��Ƶ=1: 72(APB1Ƶ��) * 1(��ʱ����Ƶ) = 72MHz(��ʱ��ʱ��Ƶ��) ->�Ƿ�,��APB1�������Ϊ36MHz
	//     APB1Ԥ��Ƶ=2: 36(APB1Ƶ��) * 2(��ʱ����Ƶ) = 72MHz(��ʱ��ʱ��Ƶ��) ��
	// TIM1,8
	// �����APB2Ԥ��Ƶ=1ʱ,��ʱ��x1��Ƶ���;
	// ����������Ԥ��Ƶֵʱ,��ʱ��x2��Ƶ���.
	// ��: APB2Ԥ��Ƶ=1: 72(APB2Ƶ��) * 1(��ʱ����Ƶ) = 72MHz(��ʱ��ʱ��Ƶ��) ��
	//     APB2Ԥ��Ƶ=2: 36(APB2Ƶ��) * 2(��ʱ����Ƶ) = 36MHz(��ʱ��ʱ��Ƶ��)
	
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	#if (defined XXX_PWM1_OCIDLESTATE) \
	||  (defined XXX_PWM2_OCIDLESTATE) \
	||  (defined XXX_PWM3_OCIDLESTATE) \
	||  (defined XXX_PWM4_OCIDLESTATE)
	TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};
	#endif
	#ifndef XXX_TIMX_HANDLER
	#define XXX_TIMX_HANDLER TIMx_Handler
	TIM_HandleTypeDef XXX_TIMX_HANDLER;      //��ʱ�������HAL���׼�÷���Ҫ��Ϊȫ�ֱ�����
	#endif
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	#ifdef XXX_PWM1_CLK_ENABLE
	XXX_PWM1_CLK_ENABLE();
	#endif
	#ifdef XXX_PWM2_CLK_ENABLE
	XXX_PWM2_CLK_ENABLE();
	#endif
	#ifdef XXX_PWM3_CLK_ENABLE
	XXX_PWM3_CLK_ENABLE();
	#endif
	#ifdef XXX_PWM4_CLK_ENABLE
	XXX_PWM4_CLK_ENABLE();
	#endif
	XXX_TIMX_CLK_ENABLE();
	
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	#ifdef XXX_PWM1_CLK_ENABLE
	GPIO_InitStruct.Pin = XXX_PWM1_PIN;
	HAL_GPIO_Init(XXX_PWM1_GPIO, &GPIO_InitStruct);
	#endif
	#ifdef XXX_PWM2_CLK_ENABLE
	GPIO_InitStruct.Pin = XXX_PWM2_PIN;
	HAL_GPIO_Init(XXX_PWM2_GPIO, &GPIO_InitStruct);
	#endif
	#ifdef XXX_PWM3_CLK_ENABLE
	GPIO_InitStruct.Pin = XXX_PWM3_PIN;
	HAL_GPIO_Init(XXX_PWM3_GPIO, &GPIO_InitStruct);
	#endif
	#ifdef XXX_PWM4_CLK_ENABLE
	GPIO_InitStruct.Pin = XXX_PWM4_PIN;
	HAL_GPIO_Init(XXX_PWM4_GPIO, &GPIO_InitStruct);
	#endif
	
	#ifdef XXX_TIMX_AFIO_REMAP
	XXX_TIMX_AFIO_REMAP();
	#endif
	
	#ifdef XXX_TIMX_IRQHandler
	HAL_NVIC_SetPriority(XXX_TIMX_IRQn, XXX_TIMX_PRE_INT_PRIO, XXX_TIMX_SUB_INT_PRIO); //�����ж����ȼ�
	HAL_NVIC_EnableIRQ(XXX_TIMX_IRQn);                                                 //ʹ���ж�ͨ��
	#endif
	
	XXX_TIMX_HANDLER.Instance = XXX_TIMX;                   //��ʱ��
	XXX_TIMX_HANDLER.Init.Prescaler = XXX_TIMX_DIV;         //��Ƶϵ��XXX_TIMX_DIV+1=��Ƶֵ
	XXX_TIMX_HANDLER.Init.CounterMode = TIM_COUNTERMODE_UP; //���ϼ���
	XXX_TIMX_HANDLER.Init.Period = XXX_TIMX_PWM_FREVOL;     //��������ת���ֵ��((72000000 / (XXX_TIMX_DIV+1) / XXX_TIMX_PWM_FRE) - 1)
	XXX_TIMX_HANDLER.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;             //ʱ�ӷ�Ƶ����
	XXX_TIMX_HANDLER.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; //�ر��Զ�װ��
	if (HAL_TIM_PWM_Init(&XXX_TIMX_HANDLER) != HAL_OK)
	{}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&XXX_TIMX_HANDLER, &sMasterConfig) != HAL_OK)
	{}
	#ifdef XXX_TIMX_IRQHandler
	HAL_TIM_Base_Start_IT(&XXX_TIMX_HANDLER);               //����ж�ʹ��
	#endif
	
	//PWM1 ������������-----------------------------------------------------------------------------------
	/* [OCMode]֪ʶ���䣨����ر�ע:4��ͨ���ɶ���!����
	1��[TIM_OCMODE_TOGGLE]->����Ƚ�ģʽ->(CCR==CNT)ʱ����ת�����ƽ��
	2��[TIM_OCMODE_PWM1/2]->PWMģʽ->(CNT<CCR)ʱ���һ�ֵ�ƽ��(CNT>CCR)ʱ����෴�ĵ�ƽ��*/
	#ifdef XXX_PWM1_CLK_ENABLE
//	HAL_TIM_PWM_Stop(&XXX_TIMX_HANDLER, XXX_PWM1_TIM_CHANNEL);//�ر�PWM1���(�ϵ�Ĭ���ǹر�,ƽʱ����رղ�������)
	sConfigOC.OCMode = XXX_PWM1_OCMODE;             //�Ƿ񷴼������(�����Ա���Ϊ��ƽ��ת,ǰ��:��ֹͣ״̬)
	sConfigOC.Pulse = 0;                            //0/XXX_TIMX_PWM_FREVOL=0%ռ�ձ�
	sConfigOC.OCPolarity = XXX_PWM1_OCPOLARITY;     //����ͨ����Чռ�ձ������ƽ
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_LOW;    //����ͨ����Чռ�ձ����Ϊ�͵�ƽ(ֻ���TIM1)
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;  //����ͨ�����У�ֹͣ��ʱ�����ƽ(ֻ���TIM1)(������ʱ��Ĭ��Ϊ�͵�ƽ)
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;//����ͨ�����У�ֹͣ��ʱ�����ƽ(ֻ���TIM1)
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	#ifdef XXX_PWM1_OCIDLESTATE
	sConfigOC.OCIdleState = XXX_PWM1_OCIDLESTATE;   //���TIM1
	#endif
	if (HAL_TIM_PWM_ConfigChannel(&XXX_TIMX_HANDLER, &sConfigOC, XXX_PWM1_TIM_CHANNEL) != HAL_OK)
	{}
	HAL_TIM_PWM_Start(&XXX_TIMX_HANDLER, XXX_PWM1_TIM_CHANNEL); //����PWM1���
	#endif
	
	//PWM2 ������������-----------------------------------------------------------------------------------
	/* [OCMode]֪ʶ���䣨����ر�ע:4��ͨ���ɶ���!����
	1��[TIM_OCMODE_TOGGLE]->����Ƚ�ģʽ->(CCR==CNT)ʱ����ת�����ƽ��
	2��[TIM_OCMODE_PWM1/2]->PWMģʽ->(CNT<CCR)ʱ���һ�ֵ�ƽ��(CNT>CCR)ʱ����෴�ĵ�ƽ��*/
	#ifdef XXX_PWM2_CLK_ENABLE
//	HAL_TIM_PWM_Stop(&XXX_TIMX_HANDLER, XXX_PWM2_TIM_CHANNEL);//�ر�PWM2���(�ϵ�Ĭ���ǹر�,ƽʱ����رղ�������)
	sConfigOC.OCMode = XXX_PWM2_OCMODE;             //�Ƿ񷴼������(�����Ա���Ϊ��ƽ��ת,ǰ��:��ֹͣ״̬)
	sConfigOC.Pulse = 0;                            //0/XXX_TIMX_PWM_FREVOL=0%ռ�ձ�
	sConfigOC.OCPolarity = XXX_PWM2_OCPOLARITY;     //����ͨ����Чռ�ձ������ƽ
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_LOW;    //����ͨ����Чռ�ձ����Ϊ�͵�ƽ(ֻ���TIM1)
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;  //����ͨ�����У�ֹͣ��ʱ�����ƽ(ֻ���TIM1)(������ʱ��Ĭ��Ϊ�͵�ƽ)
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;//����ͨ�����У�ֹͣ��ʱ�����ƽ(ֻ���TIM1)
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	#ifdef XXX_PWM2_OCIDLESTATE
	sConfigOC.OCIdleState = XXX_PWM2_OCIDLESTATE;   //���TIM1
	#endif
	if (HAL_TIM_PWM_ConfigChannel(&XXX_TIMX_HANDLER, &sConfigOC, XXX_PWM2_TIM_CHANNEL) != HAL_OK)
	{}
	HAL_TIM_PWM_Start(&XXX_TIMX_HANDLER, XXX_PWM2_TIM_CHANNEL); //����PWM2���
	#endif
	
	//PWM3 ������������-----------------------------------------------------------------------------------
	/* [OCMode]֪ʶ���䣨����ر�ע:4��ͨ���ɶ���!����
	1��[TIM_OCMODE_TOGGLE]->����Ƚ�ģʽ->(CCR==CNT)ʱ����ת�����ƽ��
	2��[TIM_OCMODE_PWM1/2]->PWMģʽ->(CNT<CCR)ʱ���һ�ֵ�ƽ��(CNT>CCR)ʱ����෴�ĵ�ƽ��*/
	#ifdef XXX_PWM3_CLK_ENABLE
//	HAL_TIM_PWM_Stop(&XXX_TIMX_HANDLER, XXX_PWM3_TIM_CHANNEL);//�ر�PWM3���(�ϵ�Ĭ���ǹر�,ƽʱ����رղ�������)
	sConfigOC.OCMode = XXX_PWM3_OCMODE;             //�Ƿ񷴼������(�����Ա���Ϊ��ƽ��ת,ǰ��:��ֹͣ״̬)
	sConfigOC.Pulse = 0;                            //0/XXX_TIMX_PWM_FREVOL=0%ռ�ձ�
	sConfigOC.OCPolarity = XXX_PWM3_OCPOLARITY;     //����ͨ����Чռ�ձ������ƽ
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_LOW;    //����ͨ����Чռ�ձ����Ϊ�͵�ƽ(ֻ���TIM1)
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;  //����ͨ�����У�ֹͣ��ʱ�����ƽ(ֻ���TIM1)(������ʱ��Ĭ��Ϊ�͵�ƽ)
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;//����ͨ�����У�ֹͣ��ʱ�����ƽ(ֻ���TIM1)
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	#ifdef XXX_PWM3_OCIDLESTATE
	sConfigOC.OCIdleState = XXX_PWM3_OCIDLESTATE;   //���TIM1
	#endif
	if (HAL_TIM_PWM_ConfigChannel(&XXX_TIMX_HANDLER, &sConfigOC, XXX_PWM3_TIM_CHANNEL) != HAL_OK)
	{}
	HAL_TIM_PWM_Start(&XXX_TIMX_HANDLER, XXX_PWM3_TIM_CHANNEL); //����PWM3���
	#endif
	
	//PWM4 ������������-----------------------------------------------------------------------------------
	/* [OCMode]֪ʶ���䣨����ر�ע:4��ͨ���ɶ���!����
	1��[TIM_OCMODE_TOGGLE]->����Ƚ�ģʽ->(CCR==CNT)ʱ����ת�����ƽ��
	2��[TIM_OCMODE_PWM1/2]->PWMģʽ->(CNT<CCR)ʱ���һ�ֵ�ƽ��(CNT>CCR)ʱ����෴�ĵ�ƽ��*/
	#ifdef XXX_PWM4_CLK_ENABLE
//	HAL_TIM_PWM_Stop(&XXX_TIMX_HANDLER, XXX_PWM4_TIM_CHANNEL);//�ر�PWM4���(�ϵ�Ĭ���ǹر�,ƽʱ����رղ�������)
	sConfigOC.OCMode = XXX_PWM4_OCMODE;             //�Ƿ񷴼������(�����Ա���Ϊ��ƽ��ת,ǰ��:��ֹͣ״̬)
	sConfigOC.Pulse = 0;                            //0/XXX_TIMX_PWM_FREVOL=0%ռ�ձ�
	sConfigOC.OCPolarity = XXX_PWM4_OCPOLARITY;     //����ͨ����Чռ�ձ������ƽ
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_LOW;    //����ͨ����Чռ�ձ����Ϊ�͵�ƽ(ֻ���TIM1)
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;  //����ͨ�����У�ֹͣ��ʱ�����ƽ(ֻ���TIM1)(������ʱ��Ĭ��Ϊ�͵�ƽ)
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;//����ͨ�����У�ֹͣ��ʱ�����ƽ(ֻ���TIM1)
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	#ifdef XXX_PWM4_OCIDLESTATE
	sConfigOC.OCIdleState = XXX_PWM4_OCIDLESTATE;   //���TIM1
	#endif
	if (HAL_TIM_PWM_ConfigChannel(&XXX_TIMX_HANDLER, &sConfigOC, XXX_PWM4_TIM_CHANNEL) != HAL_OK)
	{}
	HAL_TIM_PWM_Start(&XXX_TIMX_HANDLER, XXX_PWM4_TIM_CHANNEL); //����PWM4���
	#endif
	
	#if (defined XXX_PWM1_OCIDLESTATE) \
	||  (defined XXX_PWM2_OCIDLESTATE) \
	||  (defined XXX_PWM3_OCIDLESTATE) \
	||  (defined XXX_PWM4_OCIDLESTATE) //���TIM1/TIM8
	sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	sBreakDeadTimeConfig.DeadTime = 0;
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	if (HAL_TIMEx_ConfigBreakDeadTime(&XXX_TIMX_HANDLER, &sBreakDeadTimeConfig) != HAL_OK)
	{}
	#endif
	
	// ��ʱ�޸�[50%ռ�ձȷ������]����!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// XXX_TIMX->XXX_PWM1_CCR = XXX_TIMX_PWM_FREVOL/2; -> 50%ռ�ձȷ������
	// XXX_TIMX->XXX_PWM2_CCR = XXX_TIMX_PWM_FREVOL/2; -> 50%ռ�ձȷ������
	// XXX_TIMX->XXX_PWM3_CCR = XXX_TIMX_PWM_FREVOL/2; -> 50%ռ�ձȷ������
	// XXX_TIMX->XXX_PWM4_CCR = XXX_TIMX_PWM_FREVOL/2; -> 50%ռ�ձȷ������
	
	// ��ʱ�ر�[PWM1���]����!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// XXX_TIMX->CCER &=  ~(TIM_CCER_CC1E << (XXX_PWM1_TIM_CHANNEL & 0x1FU)); /* Reset the CCxE Bit */
	// XXX_TIMX->CCER |= (TIM_CCx_DISABLE << (XXX_PWM1_TIM_CHANNEL & 0x1FU)); /* Set or reset the CCxE Bit */
	// ��ʱ����[PWM1���]����!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// XXX_TIMX->CCER &=  ~(TIM_CCER_CC1E << (XXX_PWM1_TIM_CHANNEL & 0x1FU)); /* Reset the CCxE Bit */
	// XXX_TIMX->CCER |=  (TIM_CCx_ENABLE << (XXX_PWM1_TIM_CHANNEL & 0x1FU)); /* Set or reset the CCxE Bit */
	
	// ����˵����
	// ���� PWMģʽ->(CNT<CCR)ʱ���һ�ֵ�ƽ��(CNT>CCR)ʱ����෴�ĵ�ƽ��
	// ���� XXX_TIMX->XXX_PWM1_CCR �޸�ռ�ձȲ�����������ʱ������Ƚ�ֵ����ɼ�����ת������
}
XT_CHIP_INIT_5_TAB_EXPORT(bsp_pwm_init, "bsp_pwm_init()");

/**
  * @brief  ��ʱ���ж�
  * @param  void
  * @return void
  */
#ifdef XXX_TIMX_IRQHandler
void XXX_TIMX_IRQHandler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();
	
	if (((XXX_TIMX->SR & TIM_FLAG_UPDATE) != RESET)  //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_UPDATE) != RESET)
	&&  ((XXX_TIMX->DIER & TIM_IT_UPDATE) != RESET)) //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_UPDATE) != RESET)
	{
		XXX_TIMX->SR = ~TIM_IT_UPDATE;               //__HAL_TIM_CLEAR_IT(htim, TIM_IT_UPDATE);
		//����жϣ����PWM���Ƶ��1KHz����1ms�ж�һ��
	}
	
	/* leave interrupt */
	rt_interrupt_leave();
}
#endif
#endif  //#if (BSP_TIMX_PWM_EN & 0x01)
