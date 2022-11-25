/**
  * @file  bsp_stm32f1xx_it.c
  * @brief 全局中断资源
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-16     o2ospring    原始版本
  */
#define   BSP_STM32F1XX_IT_C__
#include "bsp_stm32f1xx_it.h"
#ifdef    BSP_STM32F1XX_IT_X__
#undef    BSP_STM32F1XX_IT_H__
#include "bsp_stm32f1xx_it.h"
#endif

/**
  * @brief  定时器1中断
  * @param  void
  * @return void
  */
#if (BSP_TIM1_CC_EN & 0x10)
void TIM1_CC_IRQHandler(void)
{
	uint32_t flag = 0;
	
	/* enter interrupt */
	rt_interrupt_enter();
	
	// > HAL库内部实现写法为：
	// > `void TIM1_CC_IRQHandler(void)`                     //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;`       //指出第1路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM1_CH1 toggling with frequency  */
	if (((TIM1->SR & TIM_FLAG_CC1) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC1) != RESET)
	&&  ((TIM1->DIER & TIM_IT_CC1) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC1) != RESET)
	{
		TIM1->SR = ~TIM_IT_CC1;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);
		TIM1->CCR1 = TIM1->CNT + BSP_TIM1_CCR1; //←┐
	//	TIM1->CCR1 += BSP_TIM1_CCR1; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x01;
	}
	
	// > HAL库内部实现写法为：
	// > `void TIM1_CC_IRQHandler(void)`                     //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;`       //指出第2路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM1_CH2 toggling with frequency  */
	if (((TIM1->SR & TIM_FLAG_CC2) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC2) != RESET)
	&&  ((TIM1->DIER & TIM_IT_CC2) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC2) != RESET)
	{
		TIM1->SR = ~TIM_IT_CC2;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC2);
		TIM1->CCR2 = TIM1->CNT + BSP_TIM1_CCR2; //←┐
	//	TIM1->CCR2 += BSP_TIM1_CCR2; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x02;
	}
	
	// > HAL库内部实现写法为：
	// > `void TIM1_CC_IRQHandler(void)`                     //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;`       //指出第3路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM1_CH3 toggling with frequency  */
	if (((TIM1->SR & TIM_FLAG_CC3) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC3) != RESET)
	&&  ((TIM1->DIER & TIM_IT_CC3) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC3) != RESET)
	{
		TIM1->SR = ~TIM_IT_CC3;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC3);
		TIM1->CCR3 = TIM1->CNT + BSP_TIM1_CCR3; //←┐
	//	TIM1->CCR3 += BSP_TIM1_CCR3; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x04;
	}
	
	// > HAL库内部实现写法为：
	// > `void TIM1_CC_IRQHandler(void)`                     //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;`       //指出第4路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM1_CH4 toggling with frequency  */
	if (((TIM1->SR & TIM_FLAG_CC4) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC4) != RESET)
	&&  ((TIM1->DIER & TIM_IT_CC4) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC4) != RESET)
	{
		TIM1->SR = ~TIM_IT_CC4;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC4);
		TIM1->CCR4 = TIM1->CNT + BSP_TIM1_CCR4; //←┐
	//	TIM1->CCR4 += BSP_TIM1_CCR4; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x08;
	}
	
	// 处理 ----------------------------------------------------------------------------------------------
	if (flag & 0x01) // CCR1
	{
		#if (defined BSP_MS_TICK_TIM) && (BSP_MS_TICK_TIM == 1)
		TIME_MS_TICK();
		#endif
	}
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
	if (((TIM2->SR & TIM_FLAG_CC1) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC1) != RESET)
	&&  ((TIM2->DIER & TIM_IT_CC1) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC1) != RESET)
	{
		TIM2->SR = ~TIM_IT_CC1;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);
		TIM2->CCR1 = TIM2->CNT + BSP_TIM2_CCR1; //←┐
	//	TIM2->CCR1 += BSP_TIM2_CCR1; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x01;
	}
	
	// > HAL库内部实现写法为：
	// > `void TIM2_IRQHandler(void)`                        //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;`       //指出第2路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM2_CH2 toggling with frequency  */
	if (((TIM2->SR & TIM_FLAG_CC2) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC2) != RESET)
	&&  ((TIM2->DIER & TIM_IT_CC2) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC2) != RESET)
	{
		TIM2->SR = ~TIM_IT_CC2;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC2);
		TIM2->CCR2 = TIM2->CNT + BSP_TIM2_CCR2; //←┐
	//	TIM2->CCR2 += BSP_TIM2_CCR2; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x02;
	}
	
	// > HAL库内部实现写法为：
	// > `void TIM2_IRQHandler(void)`                        //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;`       //指出第3路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM2_CH3 toggling with frequency  */
	if (((TIM2->SR & TIM_FLAG_CC3) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC3) != RESET)
	&&  ((TIM2->DIER & TIM_IT_CC3) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC3) != RESET)
	{
		TIM2->SR = ~TIM_IT_CC3;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC3);
		TIM2->CCR3 = TIM2->CNT + BSP_TIM2_CCR3; //←┐
	//	TIM2->CCR3 += BSP_TIM2_CCR3; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x04;
	}
	
	// > HAL库内部实现写法为：
	// > `void TIM2_IRQHandler(void)`                        //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;`       //指出第4路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM2_CH4 toggling with frequency  */
	if (((TIM2->SR & TIM_FLAG_CC4) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC4) != RESET)
	&&  ((TIM2->DIER & TIM_IT_CC4) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC4) != RESET)
	{
		TIM2->SR = ~TIM_IT_CC4;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC4);
		TIM2->CCR4 = TIM2->CNT + BSP_TIM2_CCR4; //←┐
	//	TIM2->CCR4 += BSP_TIM2_CCR4; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x08;
	}
	
	// 处理 ----------------------------------------------------------------------------------------------
	if (flag & 0x01) // CCR1
	{
		#if (defined BSP_MS_TICK_TIM) && (BSP_MS_TICK_TIM == 2)
		TIME_MS_TICK();
		#endif
	}
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

/**
  * @brief  定时器3中断
  * @param  void
  * @return void
  */
#if (BSP_TIM3_EN & 0x10)
void TIM3_IRQHandler(void)
{
	uint32_t flag = 0;
	
	/* enter interrupt */
	rt_interrupt_enter();
	
	// > HAL库内部实现写法为：
	// > `void TIM3_IRQHandler(void)`                        //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;`       //指出第1路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM3_CH1 toggling with frequency  */
	if (((TIM3->SR & TIM_FLAG_CC1) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC1) != RESET)
	&&  ((TIM3->DIER & TIM_IT_CC1) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC1) != RESET)
	{
		TIM3->SR = ~TIM_IT_CC1;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);
		TIM3->CCR1 = TIM3->CNT + BSP_TIM3_CCR1; //←┐
	//	TIM3->CCR1 += BSP_TIM3_CCR1; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x01;
	}
	
	// > HAL库内部实现写法为：
	// > `void TIM3_IRQHandler(void)`                        //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;`       //指出第2路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM3_CH2 toggling with frequency  */
	if (((TIM3->SR & TIM_FLAG_CC2) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC2) != RESET)
	&&  ((TIM3->DIER & TIM_IT_CC2) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC2) != RESET)
	{
		TIM3->SR = ~TIM_IT_CC2;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC2);
		TIM3->CCR2 = TIM3->CNT + BSP_TIM3_CCR2; //←┐
	//	TIM3->CCR2 += BSP_TIM3_CCR2; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x02;
	}
	
	// > HAL库内部实现写法为：
	// > `void TIM3_IRQHandler(void)`                        //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;`       //指出第3路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM3_CH3 toggling with frequency  */
	if (((TIM3->SR & TIM_FLAG_CC3) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC3) != RESET)
	&&  ((TIM3->DIER & TIM_IT_CC3) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC3) != RESET)
	{
		TIM3->SR = ~TIM_IT_CC3;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC3);
		TIM3->CCR3 = TIM3->CNT + BSP_TIM3_CCR3; //←┐
	//	TIM3->CCR3 += BSP_TIM3_CCR3; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x04;
	}
	
	// > HAL库内部实现写法为：
	// > `void TIM3_IRQHandler(void)`                        //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;`       //指出第4路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM3_CH4 toggling with frequency  */
	if (((TIM3->SR & TIM_FLAG_CC4) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC4) != RESET)
	&&  ((TIM3->DIER & TIM_IT_CC4) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC4) != RESET)
	{
		TIM3->SR = ~TIM_IT_CC4;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC4);
		TIM3->CCR4 = TIM3->CNT + BSP_TIM3_CCR4; //←┐
	//	TIM3->CCR4 += BSP_TIM3_CCR4; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x08;
	}
	
	// 处理 ----------------------------------------------------------------------------------------------
	if (flag & 0x01) // CCR1
	{
		#if (defined BSP_MS_TICK_TIM) && (BSP_MS_TICK_TIM == 3)
		TIME_MS_TICK();
		#endif
	}
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

/**
  * @brief  定时器4中断
  * @param  void
  * @return void
  */
#if (BSP_TIM4_EN & 0x10)
void TIM4_IRQHandler(void)
{
	uint32_t flag = 0;
	
	/* enter interrupt */
	rt_interrupt_enter();
	
	// > HAL库内部实现写法为：
	// > `void TIM4_IRQHandler(void)`                        //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;`       //指出第1路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM4_CH1 toggling with frequency  */
	if (((TIM4->SR & TIM_FLAG_CC1) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC1) != RESET)
	&&  ((TIM4->DIER & TIM_IT_CC1) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC1) != RESET)
	{
		TIM4->SR = ~TIM_IT_CC1;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);
		TIM4->CCR1 = TIM4->CNT + BSP_TIM4_CCR1; //←┐
	//	TIM4->CCR1 += BSP_TIM4_CCR1; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x01;
	}
	
	// > HAL库内部实现写法为：
	// > `void TIM4_IRQHandler(void)`                        //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;`       //指出第2路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM4_CH2 toggling with frequency  */
	if (((TIM4->SR & TIM_FLAG_CC2) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC2) != RESET)
	&&  ((TIM4->DIER & TIM_IT_CC2) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC2) != RESET)
	{
		TIM4->SR = ~TIM_IT_CC2;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC2);
		TIM4->CCR2 = TIM4->CNT + BSP_TIM4_CCR2; //←┐
	//	TIM4->CCR2 += BSP_TIM4_CCR2; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x02;
	}
	
	// > HAL库内部实现写法为：
	// > `void TIM4_IRQHandler(void)`                        //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;`       //指出第3路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM4_CH3 toggling with frequency  */
	if (((TIM4->SR & TIM_FLAG_CC3) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC3) != RESET)
	&&  ((TIM4->DIER & TIM_IT_CC3) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC3) != RESET)
	{
		TIM4->SR = ~TIM_IT_CC3;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC3);
		TIM4->CCR3 = TIM4->CNT + BSP_TIM4_CCR3; //←┐
	//	TIM4->CCR3 += BSP_TIM4_CCR3; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x04;
	}
	
	// > HAL库内部实现写法为：
	// > `void TIM4_IRQHandler(void)`                        //中断向量函数
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //中断事件服务函数
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;`       //指出第4路通道中断
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //回调用户提供的回调函数(注:中断标志已被清除)
	/* TIM4_CH4 toggling with frequency  */
	if (((TIM4->SR & TIM_FLAG_CC4) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC4) != RESET)
	&&  ((TIM4->DIER & TIM_IT_CC4) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC4) != RESET)
	{
		TIM4->SR = ~TIM_IT_CC4;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC4);
		TIM4->CCR4 = TIM4->CNT + BSP_TIM4_CCR4; //←┐
	//	TIM4->CCR4 += BSP_TIM4_CCR4; -> 优点:极准定时; 缺点:如果中断有堵塞时可能错过以后全部中断直至计数器反转
		flag |= 0x08;
	}
	
	// 处理 ----------------------------------------------------------------------------------------------
	if (flag & 0x01) // CCR1
	{
		#if (defined BSP_MS_TICK_TIM) && (BSP_MS_TICK_TIM == 4)
		TIME_MS_TICK();
		#endif
	}
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

/**
  * @brief  外部中断9-5中断
  * @param  void
  * @return void
  */
#if (BSP_EXTI9_5_EN & 0x10)
void EXTI9_5_IRQHandler(void)
{
	#define _EXTI_5       (1<<0)
	#define _EXTI_6       (1<<1)
	#define _EXTI_7       (1<<2)
	#define _EXTI_8       (1<<3)
	#define _EXTI_9       (1<<4)
	uint32_t flag = 0;
	
	/* enter interrupt */
	rt_interrupt_enter();
	
	// > HAL库内部实现写法为：
	// > `void EXTI9_5_IRQHandler(void)`                     //中断向量函数
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //中断事件服务函数
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //判断哪路外部中断
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //清除此路外部中断标志
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //回调用户提供的回调函数(注:中断标志已被清除)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_5) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
		flag |= _EXTI_5;
	}
	
	// > HAL库内部实现写法为：
	// > `void EXTI9_5_IRQHandler(void)`                     //中断向量函数
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //中断事件服务函数
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //判断哪路外部中断
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //清除此路外部中断标志
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //回调用户提供的回调函数(注:中断标志已被清除)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_6) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);
		flag |= _EXTI_6;
	}
	
	// > HAL库内部实现写法为：
	// > `void EXTI9_5_IRQHandler(void)`                     //中断向量函数
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //中断事件服务函数
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //判断哪路外部中断
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //清除此路外部中断标志
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //回调用户提供的回调函数(注:中断标志已被清除)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_7) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_7);
		flag |= _EXTI_7;
	}
	
	// > HAL库内部实现写法为：
	// > `void EXTI9_5_IRQHandler(void)`                     //中断向量函数
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //中断事件服务函数
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //判断哪路外部中断
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //清除此路外部中断标志
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //回调用户提供的回调函数(注:中断标志已被清除)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_8) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8);
		flag |= _EXTI_8;
	}
	
	// > HAL库内部实现写法为：
	// > `void EXTI9_5_IRQHandler(void)`                     //中断向量函数
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //中断事件服务函数
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //判断哪路外部中断
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //清除此路外部中断标志
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //回调用户提供的回调函数(注:中断标志已被清除)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_9) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);
		flag |= _EXTI_9;
	}
	
	// 处理 ----------------------------------------------------------------------------------------------
	// if (flag & _EXTI_5)
	// {
	// }
	// if (flag & _EXTI_6)
	// {
	// }
	// if (flag & _EXTI_7)
	// {
	// }
	// if (flag & _EXTI_8)
	// {
	// }
	// if (flag & _EXTI_9)
	// {
	// }
	//----------------------------------------------------------------------------------------------------
	
	/* leave interrupt */
	rt_interrupt_leave();
}
#endif

/**
  * @brief  外部中断15-10中断
  * @param  void
  * @return void
  */
#if (BSP_EXTI15_10_EN & 0x10)
void EXTI15_10_IRQHandler(void)
{
	#define _EXTI_10      (1<<0)
	#define _EXTI_11      (1<<1)
	#define _EXTI_12      (1<<2)
	#define _EXTI_13      (1<<3)
	#define _EXTI_14      (1<<4)
	#define _EXTI_15      (1<<5)
	uint32_t flag = 0;
	
	/* enter interrupt */
	rt_interrupt_enter();
	
	// > HAL库内部实现写法为：
	// > `void EXTI15_10_IRQHandler(void)`                   //中断向量函数
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //中断事件服务函数
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //判断哪路外部中断
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //清除此路外部中断标志
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //回调用户提供的回调函数(注:中断标志已被清除)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_10) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);
		flag |= _EXTI_10;
	}
	
	// > HAL库内部实现写法为：
	// > `void EXTI15_10_IRQHandler(void)`                   //中断向量函数
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //中断事件服务函数
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //判断哪路外部中断
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //清除此路外部中断标志
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //回调用户提供的回调函数(注:中断标志已被清除)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_11) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);
		flag |= _EXTI_11;
	}
	
	// > HAL库内部实现写法为：
	// > `void EXTI15_10_IRQHandler(void)`                   //中断向量函数
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //中断事件服务函数
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //判断哪路外部中断
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //清除此路外部中断标志
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //回调用户提供的回调函数(注:中断标志已被清除)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12);
		flag |= _EXTI_12;
	}
	
	// > HAL库内部实现写法为：
	// > `void EXTI15_10_IRQHandler(void)`                   //中断向量函数
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //中断事件服务函数
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //判断哪路外部中断
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //清除此路外部中断标志
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //回调用户提供的回调函数(注:中断标志已被清除)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
		flag |= _EXTI_13;
	}
	
	// > HAL库内部实现写法为：
	// > `void EXTI15_10_IRQHandler(void)`                   //中断向量函数
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //中断事件服务函数
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //判断哪路外部中断
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //清除此路外部中断标志
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //回调用户提供的回调函数(注:中断标志已被清除)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_14) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_14);
		flag |= _EXTI_14;
	}
	
	// > HAL库内部实现写法为：
	// > `void EXTI15_10_IRQHandler(void)`                   //中断向量函数
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //中断事件服务函数
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //判断哪路外部中断
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //清除此路外部中断标志
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //回调用户提供的回调函数(注:中断标志已被清除)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_15) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_15);
		flag |= _EXTI_15;
	}
	
	// 处理 ----------------------------------------------------------------------------------------------
	// if (flag & _EXTI_10)
	// {
	// }
	// if (flag & _EXTI_11)
	// {
	// }
	// if (flag & _EXTI_12)
	// {
	// }
	// if (flag & _EXTI_13)
	// {
	// }
	// if (flag & _EXTI_14)
	// {
	// }
	// if (flag & _EXTI_15)
	// {
	// }
	//----------------------------------------------------------------------------------------------------
	
	/* leave interrupt */
	rt_interrupt_leave();
}
#endif
