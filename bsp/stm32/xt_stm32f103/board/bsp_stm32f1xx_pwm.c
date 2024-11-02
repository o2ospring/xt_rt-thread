/**
  * @file  bsp_stm32f1xx_pwm.c
  * @brief 全局定时器PWM驱动程序
  * @notice 本驱动只作为初始化参考代码，因为PWM一般专用于某个应用模块
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-19     o2ospring    原始版本
  *
  * 1. 定时器几个功能引脚说明:
  *    TIM1_CHx : 作常规PWM输出。(补注:[TIM1_CHxN]是[TIM1_CHx]的互补输出,它们驱动H桥上下两个功率管)
  *    TIM1_CHxN: 专用电机控制,与[TIM1_CHx]驱动上下两个功率管。如果Deadtime为0，则两者反相；
  *               如果Deadtime不为0，则在TIM1_CHxN上插入了Deadtime，防止上下功率管同时导通。
  *    TIM1_BKIN: 是急刹输入，用来关闭TIM1的输出。
  *    TIM1_ETR : 是外部触发输入管脚。
  *
  * 2. 关于定时器复用功能重映射，请查看《STM32_RM_CH_V10_1.pdf》的118页〖8.3.7 定时器复用功能重映射〗
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
  * @brief  定时器n【PWM输出】初始化
  * @param  void
  * @return void
  */
#if (BSP_TIMX_PWM_EN & 0x01)
void bsp_pwm_init(void)
{
	// TIM2,3,4,5,6,7
	// 如果当APB1预分频=1时,则定时器x1倍频输出;
	// 否则是其它预分频值时,则定时器x2倍频输出.
	// 例: APB1预分频=1: 72(APB1频率) * 1(定时器倍频) = 72MHz(定时器时钟频率) ->非法,因APB1最高限制为36MHz
	//     APB1预分频=2: 36(APB1频率) * 2(定时器倍频) = 72MHz(定时器时钟频率) √
	// TIM1,8
	// 如果当APB2预分频=1时,则定时器x1倍频输出;
	// 否则是其它预分频值时,则定时器x2倍频输出.
	// 例: APB2预分频=1: 72(APB2频率) * 1(定时器倍频) = 72MHz(定时器时钟频率) √
	//     APB2预分频=2: 36(APB2频率) * 2(定时器倍频) = 36MHz(定时器时钟频率)
	
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
	TIM_HandleTypeDef XXX_TIMX_HANDLER;      //定时器句柄（HAL库标准用法则要求为全局变量）
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
	HAL_NVIC_SetPriority(XXX_TIMX_IRQn, XXX_TIMX_PRE_INT_PRIO, XXX_TIMX_SUB_INT_PRIO); //设置中断优先级
	HAL_NVIC_EnableIRQ(XXX_TIMX_IRQn);                                                 //使能中断通道
	#endif
	
	XXX_TIMX_HANDLER.Instance = XXX_TIMX;                   //定时器
	XXX_TIMX_HANDLER.Init.Prescaler = XXX_TIMX_DIV;         //分频系数XXX_TIMX_DIV+1=分频值
	XXX_TIMX_HANDLER.Init.CounterMode = TIM_COUNTERMODE_UP; //向上计数
	XXX_TIMX_HANDLER.Init.Period = XXX_TIMX_PWM_FREVOL;     //计数器翻转最大值←((72000000 / (XXX_TIMX_DIV+1) / XXX_TIMX_PWM_FRE) - 1)
	XXX_TIMX_HANDLER.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;             //时钟分频因子
	XXX_TIMX_HANDLER.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; //关闭自动装载
	if (HAL_TIM_PWM_Init(&XXX_TIMX_HANDLER) != HAL_OK)
	{}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&XXX_TIMX_HANDLER, &sMasterConfig) != HAL_OK)
	{}
	#ifdef XXX_TIMX_IRQHandler
	HAL_TIM_Base_Start_IT(&XXX_TIMX_HANDLER);               //溢出中断使能
	#endif
	
	//PWM1 工作参数设置-----------------------------------------------------------------------------------
	/* [OCMode]知识扩充（★★特别备注:4个通道可独立!）：
	1、[TIM_OCMODE_TOGGLE]->输出比较模式->(CCR==CNT)时，翻转输出电平。
	2、[TIM_OCMODE_PWM1/2]->PWM模式->(CNT<CCR)时输出一种电平，(CNT>CCR)时输出相反的电平。*/
	#ifdef XXX_PWM1_CLK_ENABLE
//	HAL_TIM_PWM_Stop(&XXX_TIMX_HANDLER, XXX_PWM1_TIM_CHANNEL);//关闭PWM1输出(上电默认是关闭,平时必须关闭才能设置)
	sConfigOC.OCMode = XXX_PWM1_OCMODE;             //是否反极性输出(反板性表现为电平翻转,前提:非停止状态)
	sConfigOC.Pulse = 0;                            //0/XXX_TIMX_PWM_FREVOL=0%占空比
	sConfigOC.OCPolarity = XXX_PWM1_OCPOLARITY;     //正向通道有效占空比输出电平
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_LOW;    //反向通道有效占空比输出为低电平(只针对TIM1)
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;  //正向通道空闲（停止）时输出电平(只针对TIM1)(其它定时器默认为低电平)
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;//反向通道空闲（停止）时输出电平(只针对TIM1)
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	#ifdef XXX_PWM1_OCIDLESTATE
	sConfigOC.OCIdleState = XXX_PWM1_OCIDLESTATE;   //针对TIM1
	#endif
	if (HAL_TIM_PWM_ConfigChannel(&XXX_TIMX_HANDLER, &sConfigOC, XXX_PWM1_TIM_CHANNEL) != HAL_OK)
	{}
	HAL_TIM_PWM_Start(&XXX_TIMX_HANDLER, XXX_PWM1_TIM_CHANNEL); //启动PWM1输出
	#endif
	
	//PWM2 工作参数设置-----------------------------------------------------------------------------------
	/* [OCMode]知识扩充（★★特别备注:4个通道可独立!）：
	1、[TIM_OCMODE_TOGGLE]->输出比较模式->(CCR==CNT)时，翻转输出电平。
	2、[TIM_OCMODE_PWM1/2]->PWM模式->(CNT<CCR)时输出一种电平，(CNT>CCR)时输出相反的电平。*/
	#ifdef XXX_PWM2_CLK_ENABLE
//	HAL_TIM_PWM_Stop(&XXX_TIMX_HANDLER, XXX_PWM2_TIM_CHANNEL);//关闭PWM2输出(上电默认是关闭,平时必须关闭才能设置)
	sConfigOC.OCMode = XXX_PWM2_OCMODE;             //是否反极性输出(反板性表现为电平翻转,前提:非停止状态)
	sConfigOC.Pulse = 0;                            //0/XXX_TIMX_PWM_FREVOL=0%占空比
	sConfigOC.OCPolarity = XXX_PWM2_OCPOLARITY;     //正向通道有效占空比输出电平
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_LOW;    //反向通道有效占空比输出为低电平(只针对TIM1)
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;  //正向通道空闲（停止）时输出电平(只针对TIM1)(其它定时器默认为低电平)
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;//反向通道空闲（停止）时输出电平(只针对TIM1)
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	#ifdef XXX_PWM2_OCIDLESTATE
	sConfigOC.OCIdleState = XXX_PWM2_OCIDLESTATE;   //针对TIM1
	#endif
	if (HAL_TIM_PWM_ConfigChannel(&XXX_TIMX_HANDLER, &sConfigOC, XXX_PWM2_TIM_CHANNEL) != HAL_OK)
	{}
	HAL_TIM_PWM_Start(&XXX_TIMX_HANDLER, XXX_PWM2_TIM_CHANNEL); //启动PWM2输出
	#endif
	
	//PWM3 工作参数设置-----------------------------------------------------------------------------------
	/* [OCMode]知识扩充（★★特别备注:4个通道可独立!）：
	1、[TIM_OCMODE_TOGGLE]->输出比较模式->(CCR==CNT)时，翻转输出电平。
	2、[TIM_OCMODE_PWM1/2]->PWM模式->(CNT<CCR)时输出一种电平，(CNT>CCR)时输出相反的电平。*/
	#ifdef XXX_PWM3_CLK_ENABLE
//	HAL_TIM_PWM_Stop(&XXX_TIMX_HANDLER, XXX_PWM3_TIM_CHANNEL);//关闭PWM3输出(上电默认是关闭,平时必须关闭才能设置)
	sConfigOC.OCMode = XXX_PWM3_OCMODE;             //是否反极性输出(反板性表现为电平翻转,前提:非停止状态)
	sConfigOC.Pulse = 0;                            //0/XXX_TIMX_PWM_FREVOL=0%占空比
	sConfigOC.OCPolarity = XXX_PWM3_OCPOLARITY;     //正向通道有效占空比输出电平
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_LOW;    //反向通道有效占空比输出为低电平(只针对TIM1)
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;  //正向通道空闲（停止）时输出电平(只针对TIM1)(其它定时器默认为低电平)
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;//反向通道空闲（停止）时输出电平(只针对TIM1)
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	#ifdef XXX_PWM3_OCIDLESTATE
	sConfigOC.OCIdleState = XXX_PWM3_OCIDLESTATE;   //针对TIM1
	#endif
	if (HAL_TIM_PWM_ConfigChannel(&XXX_TIMX_HANDLER, &sConfigOC, XXX_PWM3_TIM_CHANNEL) != HAL_OK)
	{}
	HAL_TIM_PWM_Start(&XXX_TIMX_HANDLER, XXX_PWM3_TIM_CHANNEL); //启动PWM3输出
	#endif
	
	//PWM4 工作参数设置-----------------------------------------------------------------------------------
	/* [OCMode]知识扩充（★★特别备注:4个通道可独立!）：
	1、[TIM_OCMODE_TOGGLE]->输出比较模式->(CCR==CNT)时，翻转输出电平。
	2、[TIM_OCMODE_PWM1/2]->PWM模式->(CNT<CCR)时输出一种电平，(CNT>CCR)时输出相反的电平。*/
	#ifdef XXX_PWM4_CLK_ENABLE
//	HAL_TIM_PWM_Stop(&XXX_TIMX_HANDLER, XXX_PWM4_TIM_CHANNEL);//关闭PWM4输出(上电默认是关闭,平时必须关闭才能设置)
	sConfigOC.OCMode = XXX_PWM4_OCMODE;             //是否反极性输出(反板性表现为电平翻转,前提:非停止状态)
	sConfigOC.Pulse = 0;                            //0/XXX_TIMX_PWM_FREVOL=0%占空比
	sConfigOC.OCPolarity = XXX_PWM4_OCPOLARITY;     //正向通道有效占空比输出电平
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_LOW;    //反向通道有效占空比输出为低电平(只针对TIM1)
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;  //正向通道空闲（停止）时输出电平(只针对TIM1)(其它定时器默认为低电平)
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;//反向通道空闲（停止）时输出电平(只针对TIM1)
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	#ifdef XXX_PWM4_OCIDLESTATE
	sConfigOC.OCIdleState = XXX_PWM4_OCIDLESTATE;   //针对TIM1
	#endif
	if (HAL_TIM_PWM_ConfigChannel(&XXX_TIMX_HANDLER, &sConfigOC, XXX_PWM4_TIM_CHANNEL) != HAL_OK)
	{}
	HAL_TIM_PWM_Start(&XXX_TIMX_HANDLER, XXX_PWM4_TIM_CHANNEL); //启动PWM4输出
	#endif
	
	#if (defined XXX_PWM1_OCIDLESTATE) \
	||  (defined XXX_PWM2_OCIDLESTATE) \
	||  (defined XXX_PWM3_OCIDLESTATE) \
	||  (defined XXX_PWM4_OCIDLESTATE) //针对TIM1/TIM8
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
	
	// 临时修改[50%占空比方波输出]例子!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// XXX_TIMX->XXX_PWM1_CCR = XXX_TIMX_PWM_FREVOL/2; -> 50%占空比方波输出
	// XXX_TIMX->XXX_PWM2_CCR = XXX_TIMX_PWM_FREVOL/2; -> 50%占空比方波输出
	// XXX_TIMX->XXX_PWM3_CCR = XXX_TIMX_PWM_FREVOL/2; -> 50%占空比方波输出
	// XXX_TIMX->XXX_PWM4_CCR = XXX_TIMX_PWM_FREVOL/2; -> 50%占空比方波输出
	
	// 临时关闭[PWM1输出]例子!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// XXX_TIMX->CCER &=  ~(TIM_CCER_CC1E << (XXX_PWM1_TIM_CHANNEL & 0x1FU)); /* Reset the CCxE Bit */
	// XXX_TIMX->CCER |= (TIM_CCx_DISABLE << (XXX_PWM1_TIM_CHANNEL & 0x1FU)); /* Set or reset the CCxE Bit */
	// 临时启动[PWM1输出]例子!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// XXX_TIMX->CCER &=  ~(TIM_CCER_CC1E << (XXX_PWM1_TIM_CHANNEL & 0x1FU)); /* Reset the CCxE Bit */
	// XXX_TIMX->CCER |=  (TIM_CCx_ENABLE << (XXX_PWM1_TIM_CHANNEL & 0x1FU)); /* Set or reset the CCxE Bit */
	
	// 补充说明：
	// 由于 PWM模式->(CNT<CCR)时输出一种电平，(CNT>CCR)时输出相反的电平，
	// 所以 XXX_TIMX->XXX_PWM1_CCR 修改占空比操作不会引起定时器错过比较值而造成计数反转的现象。
}
XT_CHIP_INIT_5_TAB_EXPORT(bsp_pwm_init, "bsp_pwm_init()");

/**
  * @brief  定时器中断
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
		//溢出中断，如果PWM输出频率1KHz，则1ms中断一次
	}
	
	/* leave interrupt */
	rt_interrupt_leave();
}
#endif
#endif  //#if (BSP_TIMX_PWM_EN & 0x01)
