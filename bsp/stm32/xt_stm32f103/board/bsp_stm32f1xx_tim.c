/**
  * @file  bsp_stm32f1xx_tim.c
  * @brief ȫ�ֶ�ʱ����ʱ��������
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-16     o2ospring    ԭʼ�汾
  */
#define   BSP_STM32F1XX_TIM_C__
#include "bsp_stm32f1xx_tim.h"
#ifdef    BSP_STM32F1XX_TIM_X__
#undef    BSP_STM32F1XX_TIM_H__
#include "bsp_stm32f1xx_tim.h"
#endif

#ifndef XT_CHIP_INIT_5_TAB_EXPORT
#define XT_CHIP_INIT_5_TAB_EXPORT(func,desc)
#endif

#if (BSP_TIM5_EN & 0x01) || (BSP_TIM6_EN & 0x01)  \
||  (BSP_TIM7_EN & 0x01) || (BSP_TIM8_CC_EN & 0x01)
#error "����:��û�б�д[TIM5,TIM6,TIM7,TIM8]��ʼ������"
#endif

/**
  * @brief  ��ʱ��1��ʼ��
  * @notice ʹ��ʱ������Ϊ: APB2 !!!!!!
  * @param  void
  * @return void
  */
#if (BSP_TIM1_CC_EN & 0x01)
void bsp_tim1cc_init(void)
{
	/* ---------------------------------------------------------------
	TIM1 Configuration: Output Compare Timing Mode:
	TIM1CLK = 72 MHz, Prescaler = 720, TIM1 counter clock = 0.1 MHz
	CC1 update rate = TIM1 counter clock / _TIM1_CCR1_ = Hz
	CC2 update rate = TIM1 counter clock / _TIM1_CCR2_ = Hz
	CC3 update rate = TIM1 counter clock / _TIM1_CCR3_ = Hz
	CC4 update rate = TIM1 counter clock / _TIM1_CCR4_ = Hz
	--------------------------------------------------------------- */
	// ϵͳ��ʱ����: board.c/SystemClock_Config()/HAL_RCC_OscConfig() ����
	// APBxԤ��Ƶ��: board.c/SystemClock_Config()/HAL_RCC_ClockConfig() ����
	//----------------------------------------------------------------
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
	
	#define BSP_TIMx                  BSP_TIM1                          /* ��ʱ��                       */
	#define BSP_TIMx_CLK_ENABLE()     BSP_TIM1_CLK_ENABLE()             /* ��ʱ��ʱ��ʹ��               */
	#define BSP_TIMx_IRQn             BSP_TIM1_IRQn                     /* ��ʱ���ж�ͨ��               */
	#define BSP_TIMx_PRE_INT_PRIO     BSP_TIM1_PRE_INT_PRIO             /* ��ʱ����ռ�ж����ȼ�         */
	#define BSP_TIMx_SUB_INT_PRIO     BSP_TIM1_SUB_INT_PRIO             /* ��ʱ����Ӧ�ж����ȼ�         */
	#define BSP_TIMx_TICK_US          BSP_TIM1_TICK_US                  /* ��ʱ����������(��:10->10us)  */
	#define BSP_TIMx_CCR1             BSP_TIM1_CCR1                     /* ��ʱ��CCR1                   */
	#define BSP_TIMx_CCR2             BSP_TIM1_CCR2                     /* ��ʱ��CCR2                   */
	#define BSP_TIMx_CCR3             BSP_TIM1_CCR3                     /* ��ʱ��CCR3                   */
	#define BSP_TIMx_CCR4             BSP_TIM1_CCR4                     /* ��ʱ��CCR4                   */
	
	TIM_HandleTypeDef bsp_timx_handler;     //��ʱ�������HAL���׼�÷���Ҫ��Ϊȫ�ֱ�����
	TIM_OC_InitTypeDef TIM_OCInitStructure; //��ʱ��ͨ�����
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > �������д����HAL���ڲ�ʵ��д��Ϊ��
	// > `HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim)`
	// >> `if (htim->State == HAL_TIM_STATE_RESET)`
	// >> `HAL_TIM_Base_MspInit(htim)`      //�ص��û��ṩ�Ļص�����(1.ʹ��ʱ��, 2.�������ź��ж����ȼ�)
	BSP_TIMx_CLK_ENABLE();
	HAL_NVIC_SetPriority(BSP_TIMx_IRQn, BSP_TIMx_PRE_INT_PRIO, BSP_TIMx_SUB_INT_PRIO);/* �����ж����ȼ�  */
	HAL_NVIC_EnableIRQ(BSP_TIMx_IRQn);                                                /* ʹ���ж�ͨ��    */
	
	bsp_timx_handler.State = HAL_TIM_STATE_RESET;                                    /* ��ʼ��           */
	bsp_timx_handler.Instance = BSP_TIMx;                                            /* ��ʱ��           */
	bsp_timx_handler.Init.Prescaler = (72000000UL / (1000000/BSP_TIMx_TICK_US)) - 1; /* ��Ƶϵ��         */
	bsp_timx_handler.Init.CounterMode = TIM_COUNTERMODE_UP;                          /* ���ϼ�����       */
	bsp_timx_handler.Init.Period = 0xFFFF;                                           /* ��������ת���ֵ */
	bsp_timx_handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;                    /* ʱ�ӷ�Ƶ����     */
	bsp_timx_handler.Init.RepetitionCounter = 0;  /*0->1�η�ת��������ж�->TIM1,8*/ /* ���ٴη�ת���ж� */
	bsp_timx_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;         /* �Զ���װ��ʹ��   */
	HAL_TIM_Base_Init(&bsp_timx_handler);                                            /* ��ʱ����ʼ��     */
	//HAL_TIM_Base_Start_IT(&bsp_timx_handler);                                      /* ����ж�ʹ��     */
	
	TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_LOW;    
	TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_RESET;  
	TIM_OCInitStructure.OCNIdleState= TIM_OCNIDLESTATE_RESET;
	TIM_OCInitStructure.OCFastMode  = TIM_OCFAST_DISABLE;
	TIM_OCInitStructure.OCMode      = TIM_OCMODE_TIMING;                             /* ֻ��ʱ,���Ų����*/
	TIM_OCInitStructure.OCPolarity  = TIM_OCPOLARITY_HIGH;                           /* �ߵ�ƽ��Ч       */
	/* [OCMode]֪ʶ���䣨����ر�ע:4��ͨ���ɶ���,ֻ������û�ֿ�����!����
	1��[TIM_OCMODE_TOGGLE]->����Ƚ�ģʽ->(CCR==CNT)ʱ����ת�����ƽ��
	2��[TIM_OCMODE_PWM1/2]->PWMģʽ->(CNT<CCR)ʱ���һ�ֵ�ƽ��(CNT>CCR)ʱ����෴�ĵ�ƽ��*/
	//CCR1
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR1;                                       /* �Ƚ�ͨ���ļ���ֵ */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_1);/* �Ƚ�ͨ���ĳ�ʼ�� */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_1);                           /* �Ƚ�ͨ���ж�ʹ�� */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_1);                              /* �Ƚ�ͨ������ʹ�� */
	//CCR2
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR2;                                       /* �Ƚ�ͨ���ļ���ֵ */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_2);/* �Ƚ�ͨ���ĳ�ʼ�� */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_2);                           /* �Ƚ�ͨ���ж�ʹ�� */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_2);                              /* �Ƚ�ͨ������ʹ�� */
	//CCR3
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR3;                                       /* �Ƚ�ͨ���ļ���ֵ */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_3);/* �Ƚ�ͨ���ĳ�ʼ�� */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_3);                           /* �Ƚ�ͨ���ж�ʹ�� */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_3);                              /* �Ƚ�ͨ������ʹ�� */
	//CCR4
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR4;                                       /* �Ƚ�ͨ���ļ���ֵ */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_4);/* �Ƚ�ͨ���ĳ�ʼ�� */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_4);                           /* �Ƚ�ͨ���ж�ʹ�� */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_4);                              /* �Ƚ�ͨ������ʹ�� */
	
	#undef BSP_TIMx
	#undef BSP_TIMx_CLK_ENABLE
	#undef BSP_TIMx_IRQn
	#undef BSP_TIMx_PRE_INT_PRIO
	#undef BSP_TIMx_SUB_INT_PRIO
	#undef BSP_TIMx_TICK_US
	#undef BSP_TIMx_CCR1
	#undef BSP_TIMx_CCR2
	#undef BSP_TIMx_CCR3
	#undef BSP_TIMx_CCR4
}
XT_CHIP_INIT_5_TAB_EXPORT(bsp_tim1cc_init, "bsp_tim1cc_init()");
#endif  //#if (BSP_TIM1_CC_EN & 0x01)

/**
  * @brief  ��ʱ��2��ʼ��
  * @param  void
  * @return void
  */
#if (BSP_TIM2_EN & 0x01)
void bsp_tim2_init(void)
{
	/* ---------------------------------------------------------------
	TIM2 Configuration: Output Compare Timing Mode:
	TIM2CLK = 72 MHz, Prescaler = 720, TIM2 counter clock = 0.1 MHz
	CC1 update rate = TIM2 counter clock / _TIM2_CCR1_ = Hz
	CC2 update rate = TIM2 counter clock / _TIM2_CCR2_ = Hz
	CC3 update rate = TIM2 counter clock / _TIM2_CCR3_ = Hz
	CC4 update rate = TIM2 counter clock / _TIM2_CCR4_ = Hz
	--------------------------------------------------------------- */
	// ϵͳ��ʱ����: board.c/SystemClock_Config()/HAL_RCC_OscConfig() ����
	// APBxԤ��Ƶ��: board.c/SystemClock_Config()/HAL_RCC_ClockConfig() ����
	//----------------------------------------------------------------
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
	
	#define BSP_TIMx                  BSP_TIM2                          /* ��ʱ��                       */
	#define BSP_TIMx_CLK_ENABLE()     BSP_TIM2_CLK_ENABLE()             /* ��ʱ��ʱ��ʹ��               */
	#define BSP_TIMx_IRQn             BSP_TIM2_IRQn                     /* ��ʱ���ж�ͨ��               */
	#define BSP_TIMx_PRE_INT_PRIO     BSP_TIM2_PRE_INT_PRIO             /* ��ʱ����ռ�ж����ȼ�         */
	#define BSP_TIMx_SUB_INT_PRIO     BSP_TIM2_SUB_INT_PRIO             /* ��ʱ����Ӧ�ж����ȼ�         */
	#define BSP_TIMx_TICK_US          BSP_TIM2_TICK_US                  /* ��ʱ����������(��:10->10us)  */
	#define BSP_TIMx_CCR1             BSP_TIM2_CCR1                     /* ��ʱ��CCR1                   */
	#define BSP_TIMx_CCR2             BSP_TIM2_CCR2                     /* ��ʱ��CCR2                   */
	#define BSP_TIMx_CCR3             BSP_TIM2_CCR3                     /* ��ʱ��CCR3                   */
	#define BSP_TIMx_CCR4             BSP_TIM2_CCR4                     /* ��ʱ��CCR4                   */
	
	TIM_HandleTypeDef bsp_timx_handler;     //��ʱ�������HAL���׼�÷���Ҫ��Ϊȫ�ֱ�����
	TIM_OC_InitTypeDef TIM_OCInitStructure; //��ʱ��ͨ�����
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > �������д����HAL���ڲ�ʵ��д��Ϊ��
	// > `HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim)`
	// >> `if (htim->State == HAL_TIM_STATE_RESET)`
	// >> `HAL_TIM_Base_MspInit(htim)`      //�ص��û��ṩ�Ļص�����(1.ʹ��ʱ��, 2.�������ź��ж����ȼ�)
	BSP_TIMx_CLK_ENABLE();
	HAL_NVIC_SetPriority(BSP_TIMx_IRQn, BSP_TIMx_PRE_INT_PRIO, BSP_TIMx_SUB_INT_PRIO);/* �����ж����ȼ�  */
	HAL_NVIC_EnableIRQ(BSP_TIMx_IRQn);                                                /* ʹ���ж�ͨ��    */
	
	bsp_timx_handler.State = HAL_TIM_STATE_RESET;                                    /* ��ʼ��           */
	bsp_timx_handler.Instance = BSP_TIMx;                                            /* ��ʱ��           */
	bsp_timx_handler.Init.Prescaler = (72000000UL / (1000000/BSP_TIMx_TICK_US)) - 1; /* ��Ƶϵ��         */
	bsp_timx_handler.Init.CounterMode = TIM_COUNTERMODE_UP;                          /* ���ϼ�����       */
	bsp_timx_handler.Init.Period = 0xFFFF;                                           /* ��������ת���ֵ */
	bsp_timx_handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;                    /* ʱ�ӷ�Ƶ����     */
	bsp_timx_handler.Init.RepetitionCounter = 0;  /*0->1�η�ת��������ж�->TIM1,8*/ /* ���ٴη�ת���ж� */
	bsp_timx_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;         /* �Զ���װ��ʹ��   */
	HAL_TIM_Base_Init(&bsp_timx_handler);                                            /* ��ʱ����ʼ��     */
	//HAL_TIM_Base_Start_IT(&bsp_timx_handler);                                      /* ����ж�ʹ��     */
	
	TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_LOW;    
	TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_RESET;  
	TIM_OCInitStructure.OCNIdleState= TIM_OCNIDLESTATE_RESET;
	TIM_OCInitStructure.OCFastMode  = TIM_OCFAST_DISABLE;
	TIM_OCInitStructure.OCMode      = TIM_OCMODE_TIMING;                             /* ֻ��ʱ,���Ų����*/
	TIM_OCInitStructure.OCPolarity  = TIM_OCPOLARITY_HIGH;                           /* �ߵ�ƽ��Ч       */
	/* [OCMode]֪ʶ���䣨����ر�ע:4��ͨ���ɶ���,ֻ������û�ֿ�����!����
	1��[TIM_OCMODE_TOGGLE]->����Ƚ�ģʽ->(CCR==CNT)ʱ����ת�����ƽ��
	2��[TIM_OCMODE_PWM1/2]->PWMģʽ->(CNT<CCR)ʱ���һ�ֵ�ƽ��(CNT>CCR)ʱ����෴�ĵ�ƽ��*/
	//CCR1
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR1;                                       /* �Ƚ�ͨ���ļ���ֵ */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_1);/* �Ƚ�ͨ���ĳ�ʼ�� */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_1);                           /* �Ƚ�ͨ���ж�ʹ�� */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_1);                              /* �Ƚ�ͨ������ʹ�� */
	//CCR2
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR2;                                       /* �Ƚ�ͨ���ļ���ֵ */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_2);/* �Ƚ�ͨ���ĳ�ʼ�� */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_2);                           /* �Ƚ�ͨ���ж�ʹ�� */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_2);                              /* �Ƚ�ͨ������ʹ�� */
	//CCR3
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR3;                                       /* �Ƚ�ͨ���ļ���ֵ */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_3);/* �Ƚ�ͨ���ĳ�ʼ�� */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_3);                           /* �Ƚ�ͨ���ж�ʹ�� */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_3);                              /* �Ƚ�ͨ������ʹ�� */
	//CCR4
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR4;                                       /* �Ƚ�ͨ���ļ���ֵ */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_4);/* �Ƚ�ͨ���ĳ�ʼ�� */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_4);                           /* �Ƚ�ͨ���ж�ʹ�� */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_4);                              /* �Ƚ�ͨ������ʹ�� */
	
	#undef BSP_TIMx
	#undef BSP_TIMx_CLK_ENABLE
	#undef BSP_TIMx_IRQn
	#undef BSP_TIMx_PRE_INT_PRIO
	#undef BSP_TIMx_SUB_INT_PRIO
	#undef BSP_TIMx_TICK_US
	#undef BSP_TIMx_CCR1
	#undef BSP_TIMx_CCR2
	#undef BSP_TIMx_CCR3
	#undef BSP_TIMx_CCR4
}
XT_CHIP_INIT_5_TAB_EXPORT(bsp_tim2_init, "bsp_tim2_init()");
#endif  //#if (BSP_TIM2_EN & 0x01)

/**
  * @brief  ��ʱ��3��ʼ��
  * @param  void
  * @return void
  */
#if (BSP_TIM3_EN & 0x01)
void bsp_tim3_init(void)
{
	#define BSP_TIMx                  BSP_TIM3                          /* ��ʱ��                       */
	#define BSP_TIMx_CLK_ENABLE()     BSP_TIM3_CLK_ENABLE()             /* ��ʱ��ʱ��ʹ��               */
	#define BSP_TIMx_IRQn             BSP_TIM3_IRQn                     /* ��ʱ���ж�ͨ��               */
	#define BSP_TIMx_PRE_INT_PRIO     BSP_TIM3_PRE_INT_PRIO             /* ��ʱ����ռ�ж����ȼ�         */
	#define BSP_TIMx_SUB_INT_PRIO     BSP_TIM3_SUB_INT_PRIO             /* ��ʱ����Ӧ�ж����ȼ�         */
	#define BSP_TIMx_TICK_US          BSP_TIM3_TICK_US                  /* ��ʱ����������(��:10->10us)  */
	#define BSP_TIMx_CCR1             BSP_TIM3_CCR1                     /* ��ʱ��CCR1                   */
	#define BSP_TIMx_CCR2             BSP_TIM3_CCR2                     /* ��ʱ��CCR2                   */
	#define BSP_TIMx_CCR3             BSP_TIM3_CCR3                     /* ��ʱ��CCR3                   */
	#define BSP_TIMx_CCR4             BSP_TIM3_CCR4                     /* ��ʱ��CCR4                   */
	
	TIM_HandleTypeDef bsp_timx_handler;     //��ʱ�������HAL���׼�÷���Ҫ��Ϊȫ�ֱ�����
	TIM_OC_InitTypeDef TIM_OCInitStructure; //��ʱ��ͨ�����
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > �������д����HAL���ڲ�ʵ��д��Ϊ��
	// > `HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim)`
	// >> `if (htim->State == HAL_TIM_STATE_RESET)`
	// >> `HAL_TIM_Base_MspInit(htim)`      //�ص��û��ṩ�Ļص�����(1.ʹ��ʱ��, 2.�������ź��ж����ȼ�)
	BSP_TIMx_CLK_ENABLE();
	HAL_NVIC_SetPriority(BSP_TIMx_IRQn, BSP_TIMx_PRE_INT_PRIO, BSP_TIMx_SUB_INT_PRIO);/* �����ж����ȼ�  */
	HAL_NVIC_EnableIRQ(BSP_TIMx_IRQn);                                                /* ʹ���ж�ͨ��    */
	
	bsp_timx_handler.State = HAL_TIM_STATE_RESET;                                    /* ��ʼ��           */
	bsp_timx_handler.Instance = BSP_TIMx;                                            /* ��ʱ��           */
	bsp_timx_handler.Init.Prescaler = (72000000UL / (1000000/BSP_TIMx_TICK_US)) - 1; /* ��Ƶϵ��         */
	bsp_timx_handler.Init.CounterMode = TIM_COUNTERMODE_UP;                          /* ���ϼ�����       */
	bsp_timx_handler.Init.Period = 0xFFFF;                                           /* ��������ת���ֵ */
	bsp_timx_handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;                    /* ʱ�ӷ�Ƶ����     */
	bsp_timx_handler.Init.RepetitionCounter = 0;  /*0->1�η�ת��������ж�->TIM1,8*/ /* ���ٴη�ת���ж� */
	bsp_timx_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;         /* �Զ���װ��ʹ��   */
	HAL_TIM_Base_Init(&bsp_timx_handler);                                            /* ��ʱ����ʼ��     */
	//HAL_TIM_Base_Start_IT(&bsp_timx_handler);                                      /* ����ж�ʹ��     */
	
	TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_LOW;    
	TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_RESET;  
	TIM_OCInitStructure.OCNIdleState= TIM_OCNIDLESTATE_RESET;
	TIM_OCInitStructure.OCFastMode  = TIM_OCFAST_DISABLE;
	TIM_OCInitStructure.OCMode      = TIM_OCMODE_TIMING;                             /* ֻ��ʱ,���Ų����*/
	TIM_OCInitStructure.OCPolarity  = TIM_OCPOLARITY_HIGH;                           /* �ߵ�ƽ��Ч       */
	/* [OCMode]֪ʶ���䣨����ر�ע:4��ͨ���ɶ���,ֻ������û�ֿ�����!����
	1��[TIM_OCMODE_TOGGLE]->����Ƚ�ģʽ->(CCR==CNT)ʱ����ת�����ƽ��
	2��[TIM_OCMODE_PWM1/2]->PWMģʽ->(CNT<CCR)ʱ���һ�ֵ�ƽ��(CNT>CCR)ʱ����෴�ĵ�ƽ��*/
	//CCR1
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR1;                                       /* �Ƚ�ͨ���ļ���ֵ */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_1);/* �Ƚ�ͨ���ĳ�ʼ�� */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_1);                           /* �Ƚ�ͨ���ж�ʹ�� */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_1);                              /* �Ƚ�ͨ������ʹ�� */
	//CCR2
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR2;                                       /* �Ƚ�ͨ���ļ���ֵ */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_2);/* �Ƚ�ͨ���ĳ�ʼ�� */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_2);                           /* �Ƚ�ͨ���ж�ʹ�� */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_2);                              /* �Ƚ�ͨ������ʹ�� */
	//CCR3
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR3;                                       /* �Ƚ�ͨ���ļ���ֵ */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_3);/* �Ƚ�ͨ���ĳ�ʼ�� */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_3);                           /* �Ƚ�ͨ���ж�ʹ�� */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_3);                              /* �Ƚ�ͨ������ʹ�� */
	//CCR4
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR4;                                       /* �Ƚ�ͨ���ļ���ֵ */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_4);/* �Ƚ�ͨ���ĳ�ʼ�� */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_4);                           /* �Ƚ�ͨ���ж�ʹ�� */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_4);                              /* �Ƚ�ͨ������ʹ�� */
	
	#undef BSP_TIMx
	#undef BSP_TIMx_CLK_ENABLE
	#undef BSP_TIMx_IRQn
	#undef BSP_TIMx_PRE_INT_PRIO
	#undef BSP_TIMx_SUB_INT_PRIO
	#undef BSP_TIMx_TICK_US
	#undef BSP_TIMx_CCR1
	#undef BSP_TIMx_CCR2
	#undef BSP_TIMx_CCR3
	#undef BSP_TIMx_CCR4
}
XT_CHIP_INIT_5_TAB_EXPORT(bsp_tim3_init, "bsp_tim3_init()");
#endif  //#if (BSP_TIM3_EN & 0x01)

/**
  * @brief  ��ʱ��4��ʼ��
  * @param  void
  * @return void
  */
#if (BSP_TIM4_EN & 0x01)
void bsp_tim4_init(void)
{
	#define BSP_TIMx                  BSP_TIM4                          /* ��ʱ��                       */
	#define BSP_TIMx_CLK_ENABLE()     BSP_TIM4_CLK_ENABLE()             /* ��ʱ��ʱ��ʹ��               */
	#define BSP_TIMx_IRQn             BSP_TIM4_IRQn                     /* ��ʱ���ж�ͨ��               */
	#define BSP_TIMx_PRE_INT_PRIO     BSP_TIM4_PRE_INT_PRIO             /* ��ʱ����ռ�ж����ȼ�         */
	#define BSP_TIMx_SUB_INT_PRIO     BSP_TIM4_SUB_INT_PRIO             /* ��ʱ����Ӧ�ж����ȼ�         */
	#define BSP_TIMx_TICK_US          BSP_TIM4_TICK_US                  /* ��ʱ����������(��:10->10us)  */
	#define BSP_TIMx_CCR1             BSP_TIM4_CCR1                     /* ��ʱ��CCR1                   */
	#define BSP_TIMx_CCR2             BSP_TIM4_CCR2                     /* ��ʱ��CCR2                   */
	#define BSP_TIMx_CCR3             BSP_TIM4_CCR3                     /* ��ʱ��CCR3                   */
	#define BSP_TIMx_CCR4             BSP_TIM4_CCR4                     /* ��ʱ��CCR4                   */
	
	TIM_HandleTypeDef bsp_timx_handler;     //��ʱ�������HAL���׼�÷���Ҫ��Ϊȫ�ֱ�����
	TIM_OC_InitTypeDef TIM_OCInitStructure; //��ʱ��ͨ�����
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > �������д����HAL���ڲ�ʵ��д��Ϊ��
	// > `HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim)`
	// >> `if (htim->State == HAL_TIM_STATE_RESET)`
	// >> `HAL_TIM_Base_MspInit(htim)`      //�ص��û��ṩ�Ļص�����(1.ʹ��ʱ��, 2.�������ź��ж����ȼ�)
	BSP_TIMx_CLK_ENABLE();
	HAL_NVIC_SetPriority(BSP_TIMx_IRQn, BSP_TIMx_PRE_INT_PRIO, BSP_TIMx_SUB_INT_PRIO);/* �����ж����ȼ�  */
	HAL_NVIC_EnableIRQ(BSP_TIMx_IRQn);                                                /* ʹ���ж�ͨ��    */
	
	bsp_timx_handler.State = HAL_TIM_STATE_RESET;                                    /* ��ʼ��           */
	bsp_timx_handler.Instance = BSP_TIMx;                                            /* ��ʱ��           */
	bsp_timx_handler.Init.Prescaler = (72000000UL / (1000000/BSP_TIMx_TICK_US)) - 1; /* ��Ƶϵ��         */
	bsp_timx_handler.Init.CounterMode = TIM_COUNTERMODE_UP;                          /* ���ϼ�����       */
	bsp_timx_handler.Init.Period = 0xFFFF;                                           /* ��������ת���ֵ */
	bsp_timx_handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;                    /* ʱ�ӷ�Ƶ����     */
	bsp_timx_handler.Init.RepetitionCounter = 0;  /*0->1�η�ת��������ж�->TIM1,8*/ /* ���ٴη�ת���ж� */
	bsp_timx_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;         /* �Զ���װ��ʹ��   */
	HAL_TIM_Base_Init(&bsp_timx_handler);                                            /* ��ʱ����ʼ��     */
	//HAL_TIM_Base_Start_IT(&bsp_timx_handler);                                      /* ����ж�ʹ��     */
	
	TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_LOW;    
	TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_RESET;  
	TIM_OCInitStructure.OCNIdleState= TIM_OCNIDLESTATE_RESET;
	TIM_OCInitStructure.OCFastMode  = TIM_OCFAST_DISABLE;
	TIM_OCInitStructure.OCMode      = TIM_OCMODE_TIMING;                             /* ֻ��ʱ,���Ų����*/
	TIM_OCInitStructure.OCPolarity  = TIM_OCPOLARITY_HIGH;                           /* �ߵ�ƽ��Ч       */
	/* [OCMode]֪ʶ���䣨����ر�ע:4��ͨ���ɶ���,ֻ������û�ֿ�����!����
	1��[TIM_OCMODE_TOGGLE]->����Ƚ�ģʽ->(CCR==CNT)ʱ����ת�����ƽ��
	2��[TIM_OCMODE_PWM1/2]->PWMģʽ->(CNT<CCR)ʱ���һ�ֵ�ƽ��(CNT>CCR)ʱ����෴�ĵ�ƽ��*/
	//CCR1
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR1;                                       /* �Ƚ�ͨ���ļ���ֵ */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_1);/* �Ƚ�ͨ���ĳ�ʼ�� */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_1);                           /* �Ƚ�ͨ���ж�ʹ�� */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_1);                              /* �Ƚ�ͨ������ʹ�� */
	//CCR2
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR2;                                       /* �Ƚ�ͨ���ļ���ֵ */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_2);/* �Ƚ�ͨ���ĳ�ʼ�� */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_2);                           /* �Ƚ�ͨ���ж�ʹ�� */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_2);                              /* �Ƚ�ͨ������ʹ�� */
	//CCR3
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR3;                                       /* �Ƚ�ͨ���ļ���ֵ */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_3);/* �Ƚ�ͨ���ĳ�ʼ�� */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_3);                           /* �Ƚ�ͨ���ж�ʹ�� */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_3);                              /* �Ƚ�ͨ������ʹ�� */
	//CCR4
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR4;                                       /* �Ƚ�ͨ���ļ���ֵ */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_4);/* �Ƚ�ͨ���ĳ�ʼ�� */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_4);                           /* �Ƚ�ͨ���ж�ʹ�� */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_4);                              /* �Ƚ�ͨ������ʹ�� */
	
	#undef BSP_TIMx
	#undef BSP_TIMx_CLK_ENABLE
	#undef BSP_TIMx_IRQn
	#undef BSP_TIMx_PRE_INT_PRIO
	#undef BSP_TIMx_SUB_INT_PRIO
	#undef BSP_TIMx_TICK_US
	#undef BSP_TIMx_CCR1
	#undef BSP_TIMx_CCR2
	#undef BSP_TIMx_CCR3
	#undef BSP_TIMx_CCR4
}
XT_CHIP_INIT_5_TAB_EXPORT(bsp_tim4_init, "bsp_tim4_init()");
#endif  //#if (BSP_TIM4_EN & 0x01)

#if 0
/**
  * @brief  ��ʱ��2�ж�
  * @param  void
  * @return void
  */
#if (BSP_TIM2_EN & 0x10)
void TIM2_IRQHandler(void)
{
	uint32_t flag = 0;
	
	/* enter interrupt */
	rt_interrupt_enter();
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM2_IRQHandler(void)`                        //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;`       //ָ����1·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM2_CH1 toggling with frequency  */
	if (((TIM2->SR & TIM_FLAG_CC1) != RESET)  //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC1) != RESET)
	&&  ((TIM2->DIER & TIM_IT_CC1) != RESET)) //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC1) != RESET)
	{
		TIM2->SR = ~TIM_IT_CC1;               //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);
		TIM2->CCR1 = TIM2->CNT + _TIM2_CCR1_; //����
	//	TIM2->CCR1 += _TIM2_CCR1_; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x01;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM2_IRQHandler(void)`                        //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;`       //ָ����2·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM2_CH2 toggling with frequency  */
	if (((TIM2->SR & TIM_FLAG_CC2) != RESET)  //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC2) != RESET)
	&&  ((TIM2->DIER & TIM_IT_CC2) != RESET)) //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC2) != RESET)
	{
		TIM2->SR = ~TIM_IT_CC2;               //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC2);
		TIM2->CCR2 = TIM2->CNT + _TIM2_CCR2_; //����
	//	TIM2->CCR2 += _TIM2_CCR2_; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x02;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM2_IRQHandler(void)`                        //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;`       //ָ����3·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM2_CH3 toggling with frequency  */
	if (((TIM2->SR & TIM_FLAG_CC3) != RESET)  //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC3) != RESET)
	&&  ((TIM2->DIER & TIM_IT_CC3) != RESET)) //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC3) != RESET)
	{
		TIM2->SR = ~TIM_IT_CC3;               //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC3);
		TIM2->CCR3 = TIM2->CNT + _TIM2_CCR3_; //����
	//	TIM2->CCR3 += _TIM2_CCR3_; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x04;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM2_IRQHandler(void)`                        //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;`       //ָ����4·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM2_CH4 toggling with frequency  */
	if (((TIM2->SR & TIM_FLAG_CC4) != RESET)  //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC4) != RESET)
	&&  ((TIM2->DIER & TIM_IT_CC4) != RESET)) //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC4) != RESET)
	{
		TIM2->SR = ~TIM_IT_CC4;               //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC4);
		TIM2->CCR4 = TIM2->CNT + _TIM2_CCR4_; //����
	//	TIM2->CCR4 += _TIM2_CCR4_; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x08;
	}
	
	// ���� ----------------------------------------------------------------------------------------------
	// if (flag & 0x01) // CCR1
	// {
	// }
	// if (flag & 0x02) // CCR2
	// {
	// }
	// if (flag & 0x04) // CCR3
	// {
	// }
	// if (flag & 0x08) // CCR4
	// {
	// }
	//----------------------------------------------------------------------------------------------------
	
	/* leave interrupt */
	rt_interrupt_leave();
}
#endif

#endif  //#if 0
