/**
  * @file  bsp_stm32f1xx_tim.c
  * @brief 全局定时器定时驱动程序
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-16     o2ospring    原始版本
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
#error "错误:还没有编写[TIM5,TIM6,TIM7,TIM8]初始化函数"
#endif

/**
  * @brief  定时器1初始化
  * @notice 使用时钟总线为: APB2 !!!!!!
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
	// 系统主时钟在: board.c/SystemClock_Config()/HAL_RCC_OscConfig() 设置
	// APBx预分频在: board.c/SystemClock_Config()/HAL_RCC_ClockConfig() 设置
	//----------------------------------------------------------------
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
	
	#define BSP_TIMx                  BSP_TIM1                          /* 定时器                       */
	#define BSP_TIMx_CLK_ENABLE()     BSP_TIM1_CLK_ENABLE()             /* 定时器时钟使能               */
	#define BSP_TIMx_IRQn             BSP_TIM1_IRQn                     /* 定时器中断通道               */
	#define BSP_TIMx_PRE_INT_PRIO     BSP_TIM1_PRE_INT_PRIO             /* 定时器抢占中断优先级         */
	#define BSP_TIMx_SUB_INT_PRIO     BSP_TIM1_SUB_INT_PRIO             /* 定时器响应中断优先级         */
	#define BSP_TIMx_TICK_US          BSP_TIM1_TICK_US                  /* 定时器计数节拍(如:10->10us)  */
	#define BSP_TIMx_CCR1             BSP_TIM1_CCR1                     /* 定时器CCR1                   */
	#define BSP_TIMx_CCR2             BSP_TIM1_CCR2                     /* 定时器CCR2                   */
	#define BSP_TIMx_CCR3             BSP_TIM1_CCR3                     /* 定时器CCR3                   */
	#define BSP_TIMx_CCR4             BSP_TIM1_CCR4                     /* 定时器CCR4                   */
	
	TIM_HandleTypeDef bsp_timx_handler;     //定时器句柄（HAL库标准用法则要求为全局变量）
	TIM_OC_InitTypeDef TIM_OCInitStructure; //定时器通道句柄
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > 下面三行代码的HAL库内部实现写法为：
	// > `HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim)`
	// >> `if (htim->State == HAL_TIM_STATE_RESET)`
	// >> `HAL_TIM_Base_MspInit(htim)`      //回调用户提供的回调函数(1.使能时钟, 2.设置引脚和中断优先级)
	BSP_TIMx_CLK_ENABLE();
	HAL_NVIC_SetPriority(BSP_TIMx_IRQn, BSP_TIMx_PRE_INT_PRIO, BSP_TIMx_SUB_INT_PRIO);/* 设置中断优先级  */
	HAL_NVIC_EnableIRQ(BSP_TIMx_IRQn);                                                /* 使能中断通道    */
	
	bsp_timx_handler.State = HAL_TIM_STATE_RESET;                                    /* 初始化           */
	bsp_timx_handler.Instance = BSP_TIMx;                                            /* 定时器           */
	bsp_timx_handler.Init.Prescaler = (72000000UL / (1000000/BSP_TIMx_TICK_US)) - 1; /* 分频系数         */
	bsp_timx_handler.Init.CounterMode = TIM_COUNTERMODE_UP;                          /* 向上计数器       */
	bsp_timx_handler.Init.Period = 0xFFFF;                                           /* 计数器翻转最大值 */
	bsp_timx_handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;                    /* 时钟分频因子     */
	bsp_timx_handler.Init.RepetitionCounter = 0;  /*0->1次翻转进入溢出中断->TIM1,8*/ /* 多少次翻转才中断 */
	bsp_timx_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;         /* 自动重装载使能   */
	HAL_TIM_Base_Init(&bsp_timx_handler);                                            /* 定时器初始化     */
	//HAL_TIM_Base_Start_IT(&bsp_timx_handler);                                      /* 溢出中断使能     */
	
	TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_LOW;    
	TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_RESET;  
	TIM_OCInitStructure.OCNIdleState= TIM_OCNIDLESTATE_RESET;
	TIM_OCInitStructure.OCFastMode  = TIM_OCFAST_DISABLE;
	TIM_OCInitStructure.OCMode      = TIM_OCMODE_TIMING;                             /* 只定时,引脚不输出*/
	TIM_OCInitStructure.OCPolarity  = TIM_OCPOLARITY_HIGH;                           /* 高电平有效       */
	/* [OCMode]知识扩充（★★特别备注:4个通道可独立,只是这里没分开设置!）：
	1、[TIM_OCMODE_TOGGLE]->输出比较模式->(CCR==CNT)时，翻转输出电平。
	2、[TIM_OCMODE_PWM1/2]->PWM模式->(CNT<CCR)时输出一种电平，(CNT>CCR)时输出相反的电平。*/
	//CCR1
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR1;                                       /* 比较通道的计数值 */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_1);/* 比较通道的初始化 */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_1);                           /* 比较通道中断使能 */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_1);                              /* 比较通道工作使能 */
	//CCR2
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR2;                                       /* 比较通道的计数值 */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_2);/* 比较通道的初始化 */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_2);                           /* 比较通道中断使能 */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_2);                              /* 比较通道工作使能 */
	//CCR3
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR3;                                       /* 比较通道的计数值 */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_3);/* 比较通道的初始化 */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_3);                           /* 比较通道中断使能 */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_3);                              /* 比较通道工作使能 */
	//CCR4
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR4;                                       /* 比较通道的计数值 */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_4);/* 比较通道的初始化 */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_4);                           /* 比较通道中断使能 */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_4);                              /* 比较通道工作使能 */
	
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
  * @brief  定时器2初始化
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
	// 系统主时钟在: board.c/SystemClock_Config()/HAL_RCC_OscConfig() 设置
	// APBx预分频在: board.c/SystemClock_Config()/HAL_RCC_ClockConfig() 设置
	//----------------------------------------------------------------
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
	
	#define BSP_TIMx                  BSP_TIM2                          /* 定时器                       */
	#define BSP_TIMx_CLK_ENABLE()     BSP_TIM2_CLK_ENABLE()             /* 定时器时钟使能               */
	#define BSP_TIMx_IRQn             BSP_TIM2_IRQn                     /* 定时器中断通道               */
	#define BSP_TIMx_PRE_INT_PRIO     BSP_TIM2_PRE_INT_PRIO             /* 定时器抢占中断优先级         */
	#define BSP_TIMx_SUB_INT_PRIO     BSP_TIM2_SUB_INT_PRIO             /* 定时器响应中断优先级         */
	#define BSP_TIMx_TICK_US          BSP_TIM2_TICK_US                  /* 定时器计数节拍(如:10->10us)  */
	#define BSP_TIMx_CCR1             BSP_TIM2_CCR1                     /* 定时器CCR1                   */
	#define BSP_TIMx_CCR2             BSP_TIM2_CCR2                     /* 定时器CCR2                   */
	#define BSP_TIMx_CCR3             BSP_TIM2_CCR3                     /* 定时器CCR3                   */
	#define BSP_TIMx_CCR4             BSP_TIM2_CCR4                     /* 定时器CCR4                   */
	
	TIM_HandleTypeDef bsp_timx_handler;     //定时器句柄（HAL库标准用法则要求为全局变量）
	TIM_OC_InitTypeDef TIM_OCInitStructure; //定时器通道句柄
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > 下面三行代码的HAL库内部实现写法为：
	// > `HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim)`
	// >> `if (htim->State == HAL_TIM_STATE_RESET)`
	// >> `HAL_TIM_Base_MspInit(htim)`      //回调用户提供的回调函数(1.使能时钟, 2.设置引脚和中断优先级)
	BSP_TIMx_CLK_ENABLE();
	HAL_NVIC_SetPriority(BSP_TIMx_IRQn, BSP_TIMx_PRE_INT_PRIO, BSP_TIMx_SUB_INT_PRIO);/* 设置中断优先级  */
	HAL_NVIC_EnableIRQ(BSP_TIMx_IRQn);                                                /* 使能中断通道    */
	
	bsp_timx_handler.State = HAL_TIM_STATE_RESET;                                    /* 初始化           */
	bsp_timx_handler.Instance = BSP_TIMx;                                            /* 定时器           */
	bsp_timx_handler.Init.Prescaler = (72000000UL / (1000000/BSP_TIMx_TICK_US)) - 1; /* 分频系数         */
	bsp_timx_handler.Init.CounterMode = TIM_COUNTERMODE_UP;                          /* 向上计数器       */
	bsp_timx_handler.Init.Period = 0xFFFF;                                           /* 计数器翻转最大值 */
	bsp_timx_handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;                    /* 时钟分频因子     */
	bsp_timx_handler.Init.RepetitionCounter = 0;  /*0->1次翻转进入溢出中断->TIM1,8*/ /* 多少次翻转才中断 */
	bsp_timx_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;         /* 自动重装载使能   */
	HAL_TIM_Base_Init(&bsp_timx_handler);                                            /* 定时器初始化     */
	//HAL_TIM_Base_Start_IT(&bsp_timx_handler);                                      /* 溢出中断使能     */
	
	TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_LOW;    
	TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_RESET;  
	TIM_OCInitStructure.OCNIdleState= TIM_OCNIDLESTATE_RESET;
	TIM_OCInitStructure.OCFastMode  = TIM_OCFAST_DISABLE;
	TIM_OCInitStructure.OCMode      = TIM_OCMODE_TIMING;                             /* 只定时,引脚不输出*/
	TIM_OCInitStructure.OCPolarity  = TIM_OCPOLARITY_HIGH;                           /* 高电平有效       */
	/* [OCMode]知识扩充（★★特别备注:4个通道可独立,只是这里没分开设置!）：
	1、[TIM_OCMODE_TOGGLE]->输出比较模式->(CCR==CNT)时，翻转输出电平。
	2、[TIM_OCMODE_PWM1/2]->PWM模式->(CNT<CCR)时输出一种电平，(CNT>CCR)时输出相反的电平。*/
	//CCR1
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR1;                                       /* 比较通道的计数值 */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_1);/* 比较通道的初始化 */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_1);                           /* 比较通道中断使能 */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_1);                              /* 比较通道工作使能 */
	//CCR2
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR2;                                       /* 比较通道的计数值 */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_2);/* 比较通道的初始化 */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_2);                           /* 比较通道中断使能 */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_2);                              /* 比较通道工作使能 */
	//CCR3
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR3;                                       /* 比较通道的计数值 */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_3);/* 比较通道的初始化 */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_3);                           /* 比较通道中断使能 */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_3);                              /* 比较通道工作使能 */
	//CCR4
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR4;                                       /* 比较通道的计数值 */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_4);/* 比较通道的初始化 */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_4);                           /* 比较通道中断使能 */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_4);                              /* 比较通道工作使能 */
	
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
  * @brief  定时器3初始化
  * @param  void
  * @return void
  */
#if (BSP_TIM3_EN & 0x01)
void bsp_tim3_init(void)
{
	#define BSP_TIMx                  BSP_TIM3                          /* 定时器                       */
	#define BSP_TIMx_CLK_ENABLE()     BSP_TIM3_CLK_ENABLE()             /* 定时器时钟使能               */
	#define BSP_TIMx_IRQn             BSP_TIM3_IRQn                     /* 定时器中断通道               */
	#define BSP_TIMx_PRE_INT_PRIO     BSP_TIM3_PRE_INT_PRIO             /* 定时器抢占中断优先级         */
	#define BSP_TIMx_SUB_INT_PRIO     BSP_TIM3_SUB_INT_PRIO             /* 定时器响应中断优先级         */
	#define BSP_TIMx_TICK_US          BSP_TIM3_TICK_US                  /* 定时器计数节拍(如:10->10us)  */
	#define BSP_TIMx_CCR1             BSP_TIM3_CCR1                     /* 定时器CCR1                   */
	#define BSP_TIMx_CCR2             BSP_TIM3_CCR2                     /* 定时器CCR2                   */
	#define BSP_TIMx_CCR3             BSP_TIM3_CCR3                     /* 定时器CCR3                   */
	#define BSP_TIMx_CCR4             BSP_TIM3_CCR4                     /* 定时器CCR4                   */
	
	TIM_HandleTypeDef bsp_timx_handler;     //定时器句柄（HAL库标准用法则要求为全局变量）
	TIM_OC_InitTypeDef TIM_OCInitStructure; //定时器通道句柄
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > 下面三行代码的HAL库内部实现写法为：
	// > `HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim)`
	// >> `if (htim->State == HAL_TIM_STATE_RESET)`
	// >> `HAL_TIM_Base_MspInit(htim)`      //回调用户提供的回调函数(1.使能时钟, 2.设置引脚和中断优先级)
	BSP_TIMx_CLK_ENABLE();
	HAL_NVIC_SetPriority(BSP_TIMx_IRQn, BSP_TIMx_PRE_INT_PRIO, BSP_TIMx_SUB_INT_PRIO);/* 设置中断优先级  */
	HAL_NVIC_EnableIRQ(BSP_TIMx_IRQn);                                                /* 使能中断通道    */
	
	bsp_timx_handler.State = HAL_TIM_STATE_RESET;                                    /* 初始化           */
	bsp_timx_handler.Instance = BSP_TIMx;                                            /* 定时器           */
	bsp_timx_handler.Init.Prescaler = (72000000UL / (1000000/BSP_TIMx_TICK_US)) - 1; /* 分频系数         */
	bsp_timx_handler.Init.CounterMode = TIM_COUNTERMODE_UP;                          /* 向上计数器       */
	bsp_timx_handler.Init.Period = 0xFFFF;                                           /* 计数器翻转最大值 */
	bsp_timx_handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;                    /* 时钟分频因子     */
	bsp_timx_handler.Init.RepetitionCounter = 0;  /*0->1次翻转进入溢出中断->TIM1,8*/ /* 多少次翻转才中断 */
	bsp_timx_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;         /* 自动重装载使能   */
	HAL_TIM_Base_Init(&bsp_timx_handler);                                            /* 定时器初始化     */
	//HAL_TIM_Base_Start_IT(&bsp_timx_handler);                                      /* 溢出中断使能     */
	
	TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_LOW;    
	TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_RESET;  
	TIM_OCInitStructure.OCNIdleState= TIM_OCNIDLESTATE_RESET;
	TIM_OCInitStructure.OCFastMode  = TIM_OCFAST_DISABLE;
	TIM_OCInitStructure.OCMode      = TIM_OCMODE_TIMING;                             /* 只定时,引脚不输出*/
	TIM_OCInitStructure.OCPolarity  = TIM_OCPOLARITY_HIGH;                           /* 高电平有效       */
	/* [OCMode]知识扩充（★★特别备注:4个通道可独立,只是这里没分开设置!）：
	1、[TIM_OCMODE_TOGGLE]->输出比较模式->(CCR==CNT)时，翻转输出电平。
	2、[TIM_OCMODE_PWM1/2]->PWM模式->(CNT<CCR)时输出一种电平，(CNT>CCR)时输出相反的电平。*/
	//CCR1
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR1;                                       /* 比较通道的计数值 */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_1);/* 比较通道的初始化 */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_1);                           /* 比较通道中断使能 */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_1);                              /* 比较通道工作使能 */
	//CCR2
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR2;                                       /* 比较通道的计数值 */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_2);/* 比较通道的初始化 */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_2);                           /* 比较通道中断使能 */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_2);                              /* 比较通道工作使能 */
	//CCR3
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR3;                                       /* 比较通道的计数值 */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_3);/* 比较通道的初始化 */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_3);                           /* 比较通道中断使能 */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_3);                              /* 比较通道工作使能 */
	//CCR4
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR4;                                       /* 比较通道的计数值 */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_4);/* 比较通道的初始化 */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_4);                           /* 比较通道中断使能 */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_4);                              /* 比较通道工作使能 */
	
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
  * @brief  定时器4初始化
  * @param  void
  * @return void
  */
#if (BSP_TIM4_EN & 0x01)
void bsp_tim4_init(void)
{
	#define BSP_TIMx                  BSP_TIM4                          /* 定时器                       */
	#define BSP_TIMx_CLK_ENABLE()     BSP_TIM4_CLK_ENABLE()             /* 定时器时钟使能               */
	#define BSP_TIMx_IRQn             BSP_TIM4_IRQn                     /* 定时器中断通道               */
	#define BSP_TIMx_PRE_INT_PRIO     BSP_TIM4_PRE_INT_PRIO             /* 定时器抢占中断优先级         */
	#define BSP_TIMx_SUB_INT_PRIO     BSP_TIM4_SUB_INT_PRIO             /* 定时器响应中断优先级         */
	#define BSP_TIMx_TICK_US          BSP_TIM4_TICK_US                  /* 定时器计数节拍(如:10->10us)  */
	#define BSP_TIMx_CCR1             BSP_TIM4_CCR1                     /* 定时器CCR1                   */
	#define BSP_TIMx_CCR2             BSP_TIM4_CCR2                     /* 定时器CCR2                   */
	#define BSP_TIMx_CCR3             BSP_TIM4_CCR3                     /* 定时器CCR3                   */
	#define BSP_TIMx_CCR4             BSP_TIM4_CCR4                     /* 定时器CCR4                   */
	
	TIM_HandleTypeDef bsp_timx_handler;     //定时器句柄（HAL库标准用法则要求为全局变量）
	TIM_OC_InitTypeDef TIM_OCInitStructure; //定时器通道句柄
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > 下面三行代码的HAL库内部实现写法为：
	// > `HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim)`
	// >> `if (htim->State == HAL_TIM_STATE_RESET)`
	// >> `HAL_TIM_Base_MspInit(htim)`      //回调用户提供的回调函数(1.使能时钟, 2.设置引脚和中断优先级)
	BSP_TIMx_CLK_ENABLE();
	HAL_NVIC_SetPriority(BSP_TIMx_IRQn, BSP_TIMx_PRE_INT_PRIO, BSP_TIMx_SUB_INT_PRIO);/* 设置中断优先级  */
	HAL_NVIC_EnableIRQ(BSP_TIMx_IRQn);                                                /* 使能中断通道    */
	
	bsp_timx_handler.State = HAL_TIM_STATE_RESET;                                    /* 初始化           */
	bsp_timx_handler.Instance = BSP_TIMx;                                            /* 定时器           */
	bsp_timx_handler.Init.Prescaler = (72000000UL / (1000000/BSP_TIMx_TICK_US)) - 1; /* 分频系数         */
	bsp_timx_handler.Init.CounterMode = TIM_COUNTERMODE_UP;                          /* 向上计数器       */
	bsp_timx_handler.Init.Period = 0xFFFF;                                           /* 计数器翻转最大值 */
	bsp_timx_handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;                    /* 时钟分频因子     */
	bsp_timx_handler.Init.RepetitionCounter = 0;  /*0->1次翻转进入溢出中断->TIM1,8*/ /* 多少次翻转才中断 */
	bsp_timx_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;         /* 自动重装载使能   */
	HAL_TIM_Base_Init(&bsp_timx_handler);                                            /* 定时器初始化     */
	//HAL_TIM_Base_Start_IT(&bsp_timx_handler);                                      /* 溢出中断使能     */
	
	TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_LOW;    
	TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_RESET;  
	TIM_OCInitStructure.OCNIdleState= TIM_OCNIDLESTATE_RESET;
	TIM_OCInitStructure.OCFastMode  = TIM_OCFAST_DISABLE;
	TIM_OCInitStructure.OCMode      = TIM_OCMODE_TIMING;                             /* 只定时,引脚不输出*/
	TIM_OCInitStructure.OCPolarity  = TIM_OCPOLARITY_HIGH;                           /* 高电平有效       */
	/* [OCMode]知识扩充（★★特别备注:4个通道可独立,只是这里没分开设置!）：
	1、[TIM_OCMODE_TOGGLE]->输出比较模式->(CCR==CNT)时，翻转输出电平。
	2、[TIM_OCMODE_PWM1/2]->PWM模式->(CNT<CCR)时输出一种电平，(CNT>CCR)时输出相反的电平。*/
	//CCR1
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR1;                                       /* 比较通道的计数值 */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_1);/* 比较通道的初始化 */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_1);                           /* 比较通道中断使能 */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_1);                              /* 比较通道工作使能 */
	//CCR2
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR2;                                       /* 比较通道的计数值 */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_2);/* 比较通道的初始化 */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_2);                           /* 比较通道中断使能 */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_2);                              /* 比较通道工作使能 */
	//CCR3
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR3;                                       /* 比较通道的计数值 */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_3);/* 比较通道的初始化 */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_3);                           /* 比较通道中断使能 */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_3);                              /* 比较通道工作使能 */
	//CCR4
	TIM_OCInitStructure.Pulse = BSP_TIMx_CCR4;                                       /* 比较通道的计数值 */
	HAL_TIM_OC_ConfigChannel(&bsp_timx_handler, &TIM_OCInitStructure, TIM_CHANNEL_4);/* 比较通道的初始化 */
	HAL_TIM_OC_Start_IT(&bsp_timx_handler, TIM_CHANNEL_4);                           /* 比较通道中断使能 */
	HAL_TIM_OC_Start(&bsp_timx_handler, TIM_CHANNEL_4);                              /* 比较通道工作使能 */
	
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
  * @brief  定时器2中断
  * @param  void
  * @return void
  */
#if (BSP_TIM2_EN & 0x10)
void TIM2_IRQHandler(void)
{
	uint32_t flag = 0;
	
	/* enter interrupt */
	rt_interrupt_enter();
	
	// > HAL库内部实现写法为：
	// > `void TIM2_IRQHandler(void)`                        //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;`       //指出第1路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM2_CH1 toggling with frequency  */
	if (((TIM2->SR & TIM_FLAG_CC1) != RESET)  //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC1) != RESET)
	&&  ((TIM2->DIER & TIM_IT_CC1) != RESET)) //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC1) != RESET)
	{
		TIM2->SR = ~TIM_IT_CC1;               //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);
		TIM2->CCR1 = TIM2->CNT + _TIM2_CCR1_; //←┐
	//	TIM2->CCR1 += _TIM2_CCR1_; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x01;
	}
	
	// > HAL库内部实现写法为：
	// > `void TIM2_IRQHandler(void)`                        //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;`       //指出第2路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM2_CH2 toggling with frequency  */
	if (((TIM2->SR & TIM_FLAG_CC2) != RESET)  //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC2) != RESET)
	&&  ((TIM2->DIER & TIM_IT_CC2) != RESET)) //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC2) != RESET)
	{
		TIM2->SR = ~TIM_IT_CC2;               //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC2);
		TIM2->CCR2 = TIM2->CNT + _TIM2_CCR2_; //←┐
	//	TIM2->CCR2 += _TIM2_CCR2_; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x02;
	}
	
	// > HAL库内部实现写法为：
	// > `void TIM2_IRQHandler(void)`                        //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;`       //指出第3路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM2_CH3 toggling with frequency  */
	if (((TIM2->SR & TIM_FLAG_CC3) != RESET)  //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC3) != RESET)
	&&  ((TIM2->DIER & TIM_IT_CC3) != RESET)) //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC3) != RESET)
	{
		TIM2->SR = ~TIM_IT_CC3;               //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC3);
		TIM2->CCR3 = TIM2->CNT + _TIM2_CCR3_; //←┐
	//	TIM2->CCR3 += _TIM2_CCR3_; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x04;
	}
	
	// > HAL库内部实现写法为：
	// > `void TIM2_IRQHandler(void)`                        //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;`       //指出第4路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM2_CH4 toggling with frequency  */
	if (((TIM2->SR & TIM_FLAG_CC4) != RESET)  //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC4) != RESET)
	&&  ((TIM2->DIER & TIM_IT_CC4) != RESET)) //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC4) != RESET)
	{
		TIM2->SR = ~TIM_IT_CC4;               //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC4);
		TIM2->CCR4 = TIM2->CNT + _TIM2_CCR4_; //←┐
	//	TIM2->CCR4 += _TIM2_CCR4_; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x08;
	}
	
	// 处理 ----------------------------------------------------------------------------------------------
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
