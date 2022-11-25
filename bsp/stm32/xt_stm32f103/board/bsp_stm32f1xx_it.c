/**
  * @file  bsp_stm32f1xx_it.c
  * @brief ȫ���ж���Դ
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-16     o2ospring    ԭʼ�汾
  */
#define   BSP_STM32F1XX_IT_C__
#include "bsp_stm32f1xx_it.h"
#ifdef    BSP_STM32F1XX_IT_X__
#undef    BSP_STM32F1XX_IT_H__
#include "bsp_stm32f1xx_it.h"
#endif

/**
  * @brief  ��ʱ��1�ж�
  * @param  void
  * @return void
  */
#if (BSP_TIM1_CC_EN & 0x10)
void TIM1_CC_IRQHandler(void)
{
	uint32_t flag = 0;
	
	/* enter interrupt */
	rt_interrupt_enter();
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM1_CC_IRQHandler(void)`                     //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;`       //ָ����1·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM1_CH1 toggling with frequency  */
	if (((TIM1->SR & TIM_FLAG_CC1) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC1) != RESET)
	&&  ((TIM1->DIER & TIM_IT_CC1) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC1) != RESET)
	{
		TIM1->SR = ~TIM_IT_CC1;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);
		TIM1->CCR1 = TIM1->CNT + BSP_TIM1_CCR1; //����
	//	TIM1->CCR1 += BSP_TIM1_CCR1; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x01;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM1_CC_IRQHandler(void)`                     //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;`       //ָ����2·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM1_CH2 toggling with frequency  */
	if (((TIM1->SR & TIM_FLAG_CC2) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC2) != RESET)
	&&  ((TIM1->DIER & TIM_IT_CC2) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC2) != RESET)
	{
		TIM1->SR = ~TIM_IT_CC2;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC2);
		TIM1->CCR2 = TIM1->CNT + BSP_TIM1_CCR2; //����
	//	TIM1->CCR2 += BSP_TIM1_CCR2; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x02;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM1_CC_IRQHandler(void)`                     //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;`       //ָ����3·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM1_CH3 toggling with frequency  */
	if (((TIM1->SR & TIM_FLAG_CC3) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC3) != RESET)
	&&  ((TIM1->DIER & TIM_IT_CC3) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC3) != RESET)
	{
		TIM1->SR = ~TIM_IT_CC3;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC3);
		TIM1->CCR3 = TIM1->CNT + BSP_TIM1_CCR3; //����
	//	TIM1->CCR3 += BSP_TIM1_CCR3; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x04;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM1_CC_IRQHandler(void)`                     //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;`       //ָ����4·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM1_CH4 toggling with frequency  */
	if (((TIM1->SR & TIM_FLAG_CC4) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC4) != RESET)
	&&  ((TIM1->DIER & TIM_IT_CC4) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC4) != RESET)
	{
		TIM1->SR = ~TIM_IT_CC4;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC4);
		TIM1->CCR4 = TIM1->CNT + BSP_TIM1_CCR4; //����
	//	TIM1->CCR4 += BSP_TIM1_CCR4; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x08;
	}
	
	// ���� ----------------------------------------------------------------------------------------------
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
	if (((TIM2->SR & TIM_FLAG_CC1) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC1) != RESET)
	&&  ((TIM2->DIER & TIM_IT_CC1) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC1) != RESET)
	{
		TIM2->SR = ~TIM_IT_CC1;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);
		TIM2->CCR1 = TIM2->CNT + BSP_TIM2_CCR1; //����
	//	TIM2->CCR1 += BSP_TIM2_CCR1; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x01;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM2_IRQHandler(void)`                        //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;`       //ָ����2·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM2_CH2 toggling with frequency  */
	if (((TIM2->SR & TIM_FLAG_CC2) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC2) != RESET)
	&&  ((TIM2->DIER & TIM_IT_CC2) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC2) != RESET)
	{
		TIM2->SR = ~TIM_IT_CC2;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC2);
		TIM2->CCR2 = TIM2->CNT + BSP_TIM2_CCR2; //����
	//	TIM2->CCR2 += BSP_TIM2_CCR2; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x02;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM2_IRQHandler(void)`                        //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;`       //ָ����3·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM2_CH3 toggling with frequency  */
	if (((TIM2->SR & TIM_FLAG_CC3) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC3) != RESET)
	&&  ((TIM2->DIER & TIM_IT_CC3) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC3) != RESET)
	{
		TIM2->SR = ~TIM_IT_CC3;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC3);
		TIM2->CCR3 = TIM2->CNT + BSP_TIM2_CCR3; //����
	//	TIM2->CCR3 += BSP_TIM2_CCR3; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x04;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM2_IRQHandler(void)`                        //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;`       //ָ����4·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM2_CH4 toggling with frequency  */
	if (((TIM2->SR & TIM_FLAG_CC4) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC4) != RESET)
	&&  ((TIM2->DIER & TIM_IT_CC4) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC4) != RESET)
	{
		TIM2->SR = ~TIM_IT_CC4;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC4);
		TIM2->CCR4 = TIM2->CNT + BSP_TIM2_CCR4; //����
	//	TIM2->CCR4 += BSP_TIM2_CCR4; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x08;
	}
	
	// ���� ----------------------------------------------------------------------------------------------
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
  * @brief  ��ʱ��3�ж�
  * @param  void
  * @return void
  */
#if (BSP_TIM3_EN & 0x10)
void TIM3_IRQHandler(void)
{
	uint32_t flag = 0;
	
	/* enter interrupt */
	rt_interrupt_enter();
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM3_IRQHandler(void)`                        //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;`       //ָ����1·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM3_CH1 toggling with frequency  */
	if (((TIM3->SR & TIM_FLAG_CC1) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC1) != RESET)
	&&  ((TIM3->DIER & TIM_IT_CC1) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC1) != RESET)
	{
		TIM3->SR = ~TIM_IT_CC1;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);
		TIM3->CCR1 = TIM3->CNT + BSP_TIM3_CCR1; //����
	//	TIM3->CCR1 += BSP_TIM3_CCR1; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x01;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM3_IRQHandler(void)`                        //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;`       //ָ����2·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM3_CH2 toggling with frequency  */
	if (((TIM3->SR & TIM_FLAG_CC2) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC2) != RESET)
	&&  ((TIM3->DIER & TIM_IT_CC2) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC2) != RESET)
	{
		TIM3->SR = ~TIM_IT_CC2;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC2);
		TIM3->CCR2 = TIM3->CNT + BSP_TIM3_CCR2; //����
	//	TIM3->CCR2 += BSP_TIM3_CCR2; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x02;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM3_IRQHandler(void)`                        //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;`       //ָ����3·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM3_CH3 toggling with frequency  */
	if (((TIM3->SR & TIM_FLAG_CC3) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC3) != RESET)
	&&  ((TIM3->DIER & TIM_IT_CC3) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC3) != RESET)
	{
		TIM3->SR = ~TIM_IT_CC3;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC3);
		TIM3->CCR3 = TIM3->CNT + BSP_TIM3_CCR3; //����
	//	TIM3->CCR3 += BSP_TIM3_CCR3; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x04;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM3_IRQHandler(void)`                        //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;`       //ָ����4·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM3_CH4 toggling with frequency  */
	if (((TIM3->SR & TIM_FLAG_CC4) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC4) != RESET)
	&&  ((TIM3->DIER & TIM_IT_CC4) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC4) != RESET)
	{
		TIM3->SR = ~TIM_IT_CC4;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC4);
		TIM3->CCR4 = TIM3->CNT + BSP_TIM3_CCR4; //����
	//	TIM3->CCR4 += BSP_TIM3_CCR4; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x08;
	}
	
	// ���� ----------------------------------------------------------------------------------------------
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
  * @brief  ��ʱ��4�ж�
  * @param  void
  * @return void
  */
#if (BSP_TIM4_EN & 0x10)
void TIM4_IRQHandler(void)
{
	uint32_t flag = 0;
	
	/* enter interrupt */
	rt_interrupt_enter();
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM4_IRQHandler(void)`                        //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;`       //ָ����1·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM4_CH1 toggling with frequency  */
	if (((TIM4->SR & TIM_FLAG_CC1) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC1) != RESET)
	&&  ((TIM4->DIER & TIM_IT_CC1) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC1) != RESET)
	{
		TIM4->SR = ~TIM_IT_CC1;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);
		TIM4->CCR1 = TIM4->CNT + BSP_TIM4_CCR1; //����
	//	TIM4->CCR1 += BSP_TIM4_CCR1; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x01;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM4_IRQHandler(void)`                        //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;`       //ָ����2·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM4_CH2 toggling with frequency  */
	if (((TIM4->SR & TIM_FLAG_CC2) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC2) != RESET)
	&&  ((TIM4->DIER & TIM_IT_CC2) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC2) != RESET)
	{
		TIM4->SR = ~TIM_IT_CC2;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC2);
		TIM4->CCR2 = TIM4->CNT + BSP_TIM4_CCR2; //����
	//	TIM4->CCR2 += BSP_TIM4_CCR2; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x02;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM4_IRQHandler(void)`                        //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;`       //ָ����3·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM4_CH3 toggling with frequency  */
	if (((TIM4->SR & TIM_FLAG_CC3) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC3) != RESET)
	&&  ((TIM4->DIER & TIM_IT_CC3) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC3) != RESET)
	{
		TIM4->SR = ~TIM_IT_CC3;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC3);
		TIM4->CCR3 = TIM4->CNT + BSP_TIM4_CCR3; //����
	//	TIM4->CCR3 += BSP_TIM4_CCR3; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x04;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void TIM4_IRQHandler(void)`                        //�ж���������
	// >> `void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)` //�ж��¼�������
	// >>> `htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;`       //ָ����4·ͨ���ж�
	// >>> `HAL_TIM_OC_DelayElapsedCallback(htim);`          //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	/* TIM4_CH4 toggling with frequency  */
	if (((TIM4->SR & TIM_FLAG_CC4) != RESET)    //(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC4) != RESET)
	&&  ((TIM4->DIER & TIM_IT_CC4) != RESET))   //(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC4) != RESET)
	{
		TIM4->SR = ~TIM_IT_CC4;                 //__HAL_TIM_CLEAR_IT(htim, TIM_IT_CC4);
		TIM4->CCR4 = TIM4->CNT + BSP_TIM4_CCR4; //����
	//	TIM4->CCR4 += BSP_TIM4_CCR4; -> �ŵ�:��׼��ʱ; ȱ��:����ж��ж���ʱ���ܴ���Ժ�ȫ���ж�ֱ����������ת
		flag |= 0x08;
	}
	
	// ���� ----------------------------------------------------------------------------------------------
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
  * @brief  �ⲿ�ж�9-5�ж�
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
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void EXTI9_5_IRQHandler(void)`                     //�ж���������
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //�ж��¼�������
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //�ж���·�ⲿ�ж�
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //�����·�ⲿ�жϱ�־
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_5) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
		flag |= _EXTI_5;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void EXTI9_5_IRQHandler(void)`                     //�ж���������
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //�ж��¼�������
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //�ж���·�ⲿ�ж�
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //�����·�ⲿ�жϱ�־
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_6) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);
		flag |= _EXTI_6;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void EXTI9_5_IRQHandler(void)`                     //�ж���������
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //�ж��¼�������
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //�ж���·�ⲿ�ж�
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //�����·�ⲿ�жϱ�־
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_7) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_7);
		flag |= _EXTI_7;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void EXTI9_5_IRQHandler(void)`                     //�ж���������
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //�ж��¼�������
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //�ж���·�ⲿ�ж�
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //�����·�ⲿ�жϱ�־
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_8) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8);
		flag |= _EXTI_8;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void EXTI9_5_IRQHandler(void)`                     //�ж���������
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //�ж��¼�������
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //�ж���·�ⲿ�ж�
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //�����·�ⲿ�жϱ�־
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_9) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);
		flag |= _EXTI_9;
	}
	
	// ���� ----------------------------------------------------------------------------------------------
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
  * @brief  �ⲿ�ж�15-10�ж�
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
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void EXTI15_10_IRQHandler(void)`                   //�ж���������
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //�ж��¼�������
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //�ж���·�ⲿ�ж�
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //�����·�ⲿ�жϱ�־
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_10) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);
		flag |= _EXTI_10;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void EXTI15_10_IRQHandler(void)`                   //�ж���������
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //�ж��¼�������
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //�ж���·�ⲿ�ж�
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //�����·�ⲿ�жϱ�־
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_11) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);
		flag |= _EXTI_11;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void EXTI15_10_IRQHandler(void)`                   //�ж���������
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //�ж��¼�������
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //�ж���·�ⲿ�ж�
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //�����·�ⲿ�жϱ�־
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12);
		flag |= _EXTI_12;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void EXTI15_10_IRQHandler(void)`                   //�ж���������
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //�ж��¼�������
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //�ж���·�ⲿ�ж�
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //�����·�ⲿ�жϱ�־
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
		flag |= _EXTI_13;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void EXTI15_10_IRQHandler(void)`                   //�ж���������
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //�ж��¼�������
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //�ж���·�ⲿ�ж�
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //�����·�ⲿ�жϱ�־
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_14) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_14);
		flag |= _EXTI_14;
	}
	
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void EXTI15_10_IRQHandler(void)`                   //�ж���������
	// >> `void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)` //�ж��¼�������
	// >>> `if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)`  //�ж���·�ⲿ�ж�
	// >>> `__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);`             //�����·�ⲿ�жϱ�־
	// >>> `HAL_GPIO_EXTI_Callback(GPIO_Pin);`               //�ص��û��ṩ�Ļص�����(ע:�жϱ�־�ѱ����)
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_15) != 0x00u)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_15);
		flag |= _EXTI_15;
	}
	
	// ���� ----------------------------------------------------------------------------------------------
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
