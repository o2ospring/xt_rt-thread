/**
  * @file  bsp_stm32f1xx_exti.c
  * @brief ȫ���ⲿ�ж���������
  * @notice ������һ��ֻ��Ϊ��ʼ���ο����룬��Ϊ�ⲿ�жϳ�ר����ĳ��Ӧ��ģ��
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-16     o2ospring    ԭʼ�汾
  */
#define   BSP_STM32F1XX_EXTI_C__
#include "bsp_stm32f1xx_exti.h"
#ifdef    BSP_STM32F1XX_EXTI_X__
#undef    BSP_STM32F1XX_EXTI_H__
#include "bsp_stm32f1xx_exti.h"
#endif

#ifndef XT_CHIP_INIT_2_TAB_EXPORT
#define XT_CHIP_INIT_2_TAB_EXPORT(func,desc)
#endif

/**
  * @brief  �ⲿ�ж�0��ʼ��
  * @param  void
  * @return void
  */
#if (BSP_EXTI0_EN & 0x01)
void bsp_exti0_init(void)
{
	#define BSP_EXTIx_CLK_ENABLE()       BSP_EXTI0_CLK_ENABLE()         /* �ⲿ�ж�ʱ��ʹ��             */
	#define BSP_EXTIx_MODE_IT            BSP_EXTI0_MODE_IT              /* �жϴ�����ʽ                 */
	#define BSP_EXTIx_IRQn               BSP_EXTI0_IRQn                 /* �ж�ͨ��                     */
	#define BSP_EXTIx_PRE_INT_PRIO       BSP_EXTI0_PRE_INT_PRIO         /* ��ռ�ж����ȼ�               */
	#define BSP_EXTIx_SUB_INT_PRIO       BSP_EXTI0_SUB_INT_PRIO         /* ��Ӧ�ж����ȼ�               */
	#define BSP_EXTIx_GPIO               BSP_EXTI0_GPIO                 /* �ⲿ�ж����ڶ˿�             */
	#define BSP_EXTIx_PIN                BSP_EXTI0_PIN                  /* �ⲿ�ж����ڹܽ�             */
	#define BSP_EXTIx_IN_MODE            BSP_EXTI0_IN_MODE              /* ����ģʽ(����/����/����)     */
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	BSP_EXTIx_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = BSP_EXTIx_PIN;
	GPIO_InitStruct.Mode = BSP_EXTIx_MODE_IT;     //������ʽ
	GPIO_InitStruct.Pull = BSP_EXTIx_IN_MODE;     //����/����/����
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; //����
	HAL_GPIO_Init(BSP_EXTIx_GPIO, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(BSP_EXTIx_IRQn, BSP_EXTIx_PRE_INT_PRIO, BSP_EXTIx_SUB_INT_PRIO);
	HAL_NVIC_EnableIRQ(BSP_EXTIx_IRQn);
	
	#undef BSP_EXTIx_CLK_ENABLE
	#undef BSP_EXTIx_MODE_IT
	#undef BSP_EXTIx_IRQn
	#undef BSP_EXTIx_PRE_INT_PRIO
	#undef BSP_EXTIx_SUB_INT_PRIO
	#undef BSP_EXTIx_GPIO
	#undef BSP_EXTIx_PIN
	#undef BSP_EXTIx_IN_MODE
}
XT_CHIP_INIT_2_TAB_EXPORT(bsp_exti0_init, "bsp_exti0_init()");
#endif  //#if (BSP_EXTI0_EN & 0x01)

/**
  * @brief  �ⲿ�ж�1��ʼ��
  * @param  void
  * @return void
  */
#if (BSP_EXTI1_EN & 0x01)
void bsp_exti1_init(void)
{
	#define BSP_EXTIx_CLK_ENABLE()       BSP_EXTI1_CLK_ENABLE()         /* �ⲿ�ж�ʱ��ʹ��             */
	#define BSP_EXTIx_MODE_IT            BSP_EXTI1_MODE_IT              /* �жϴ�����ʽ                 */
	#define BSP_EXTIx_IRQn               BSP_EXTI1_IRQn                 /* �ж�ͨ��                     */
	#define BSP_EXTIx_PRE_INT_PRIO       BSP_EXTI1_PRE_INT_PRIO         /* ��ռ�ж����ȼ�               */
	#define BSP_EXTIx_SUB_INT_PRIO       BSP_EXTI1_SUB_INT_PRIO         /* ��Ӧ�ж����ȼ�               */
	#define BSP_EXTIx_GPIO               BSP_EXTI1_GPIO                 /* �ⲿ�ж����ڶ˿�             */
	#define BSP_EXTIx_PIN                BSP_EXTI1_PIN                  /* �ⲿ�ж����ڹܽ�             */
	#define BSP_EXTIx_IN_MODE            BSP_EXTI1_IN_MODE              /* ����ģʽ(����/����/����)     */
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	BSP_EXTIx_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = BSP_EXTIx_PIN;
	GPIO_InitStruct.Mode = BSP_EXTIx_MODE_IT;     //������ʽ
	GPIO_InitStruct.Pull = BSP_EXTIx_IN_MODE;     //����/����/����
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; //����
	HAL_GPIO_Init(BSP_EXTIx_GPIO, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(BSP_EXTIx_IRQn, BSP_EXTIx_PRE_INT_PRIO, BSP_EXTIx_SUB_INT_PRIO);
	HAL_NVIC_EnableIRQ(BSP_EXTIx_IRQn);
	
	#undef BSP_EXTIx_CLK_ENABLE
	#undef BSP_EXTIx_MODE_IT
	#undef BSP_EXTIx_IRQn
	#undef BSP_EXTIx_PRE_INT_PRIO
	#undef BSP_EXTIx_SUB_INT_PRIO
	#undef BSP_EXTIx_GPIO
	#undef BSP_EXTIx_PIN
	#undef BSP_EXTIx_IN_MODE
}
XT_CHIP_INIT_2_TAB_EXPORT(bsp_exti1_init, "bsp_exti1_init()");
#endif  //#if (BSP_EXTI1_EN & 0x01)

/**
  * @brief  �ⲿ�ж�2��ʼ��
  * @param  void
  * @return void
  */
#if (BSP_EXTI2_EN & 0x01)
void bsp_exti2_init(void)
{
	#define BSP_EXTIx_CLK_ENABLE()       BSP_EXTI2_CLK_ENABLE()         /* �ⲿ�ж�ʱ��ʹ��             */
	#define BSP_EXTIx_MODE_IT            BSP_EXTI2_MODE_IT              /* �жϴ�����ʽ                 */
	#define BSP_EXTIx_IRQn               BSP_EXTI2_IRQn                 /* �ж�ͨ��                     */
	#define BSP_EXTIx_PRE_INT_PRIO       BSP_EXTI2_PRE_INT_PRIO         /* ��ռ�ж����ȼ�               */
	#define BSP_EXTIx_SUB_INT_PRIO       BSP_EXTI2_SUB_INT_PRIO         /* ��Ӧ�ж����ȼ�               */
	#define BSP_EXTIx_GPIO               BSP_EXTI2_GPIO                 /* �ⲿ�ж����ڶ˿�             */
	#define BSP_EXTIx_PIN                BSP_EXTI2_PIN                  /* �ⲿ�ж����ڹܽ�             */
	#define BSP_EXTIx_IN_MODE            BSP_EXTI2_IN_MODE              /* ����ģʽ(����/����/����)     */
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	BSP_EXTIx_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = BSP_EXTIx_PIN;
	GPIO_InitStruct.Mode = BSP_EXTIx_MODE_IT;     //������ʽ
	GPIO_InitStruct.Pull = BSP_EXTIx_IN_MODE;     //����/����/����
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; //����
	HAL_GPIO_Init(BSP_EXTIx_GPIO, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(BSP_EXTIx_IRQn, BSP_EXTIx_PRE_INT_PRIO, BSP_EXTIx_SUB_INT_PRIO);
	HAL_NVIC_EnableIRQ(BSP_EXTIx_IRQn);
	
	#undef BSP_EXTIx_CLK_ENABLE
	#undef BSP_EXTIx_MODE_IT
	#undef BSP_EXTIx_IRQn
	#undef BSP_EXTIx_PRE_INT_PRIO
	#undef BSP_EXTIx_SUB_INT_PRIO
	#undef BSP_EXTIx_GPIO
	#undef BSP_EXTIx_PIN
	#undef BSP_EXTIx_IN_MODE
}
XT_CHIP_INIT_2_TAB_EXPORT(bsp_exti2_init, "bsp_exti2_init()");
#endif  //#if (BSP_EXTI2_EN & 0x01)

/**
  * @brief  �ⲿ�ж�3��ʼ��
  * @param  void
  * @return void
  */
#if (BSP_EXTI3_EN & 0x01)
void bsp_exti3_init(void)
{
	#define BSP_EXTIx_CLK_ENABLE()       BSP_EXTI3_CLK_ENABLE()         /* �ⲿ�ж�ʱ��ʹ��             */
	#define BSP_EXTIx_MODE_IT            BSP_EXTI3_MODE_IT              /* �жϴ�����ʽ                 */
	#define BSP_EXTIx_IRQn               BSP_EXTI3_IRQn                 /* �ж�ͨ��                     */
	#define BSP_EXTIx_PRE_INT_PRIO       BSP_EXTI3_PRE_INT_PRIO         /* ��ռ�ж����ȼ�               */
	#define BSP_EXTIx_SUB_INT_PRIO       BSP_EXTI3_SUB_INT_PRIO         /* ��Ӧ�ж����ȼ�               */
	#define BSP_EXTIx_GPIO               BSP_EXTI3_GPIO                 /* �ⲿ�ж����ڶ˿�             */
	#define BSP_EXTIx_PIN                BSP_EXTI3_PIN                  /* �ⲿ�ж����ڹܽ�             */
	#define BSP_EXTIx_IN_MODE            BSP_EXTI3_IN_MODE              /* ����ģʽ(����/����/����)     */
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	BSP_EXTIx_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = BSP_EXTIx_PIN;
	GPIO_InitStruct.Mode = BSP_EXTIx_MODE_IT;     //������ʽ
	GPIO_InitStruct.Pull = BSP_EXTIx_IN_MODE;     //����/����/����
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; //����
	HAL_GPIO_Init(BSP_EXTIx_GPIO, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(BSP_EXTIx_IRQn, BSP_EXTIx_PRE_INT_PRIO, BSP_EXTIx_SUB_INT_PRIO);
	HAL_NVIC_EnableIRQ(BSP_EXTIx_IRQn);
	
	#undef BSP_EXTIx_CLK_ENABLE
	#undef BSP_EXTIx_MODE_IT
	#undef BSP_EXTIx_IRQn
	#undef BSP_EXTIx_PRE_INT_PRIO
	#undef BSP_EXTIx_SUB_INT_PRIO
	#undef BSP_EXTIx_GPIO
	#undef BSP_EXTIx_PIN
	#undef BSP_EXTIx_IN_MODE
}
XT_CHIP_INIT_2_TAB_EXPORT(bsp_exti3_init, "bsp_exti3_init()");
#endif  //#if (BSP_EXTI3_EN & 0x01)

/**
  * @brief  �ⲿ�ж�4��ʼ��
  * @param  void
  * @return void
  */
#if (BSP_EXTI4_EN & 0x01)
void bsp_exti4_init(void)
{
	#define BSP_EXTIx_CLK_ENABLE()       BSP_EXTI4_CLK_ENABLE()         /* �ⲿ�ж�ʱ��ʹ��             */
	#define BSP_EXTIx_MODE_IT            BSP_EXTI4_MODE_IT              /* �жϴ�����ʽ                 */
	#define BSP_EXTIx_IRQn               BSP_EXTI4_IRQn                 /* �ж�ͨ��                     */
	#define BSP_EXTIx_PRE_INT_PRIO       BSP_EXTI4_PRE_INT_PRIO         /* ��ռ�ж����ȼ�               */
	#define BSP_EXTIx_SUB_INT_PRIO       BSP_EXTI4_SUB_INT_PRIO         /* ��Ӧ�ж����ȼ�               */
	#define BSP_EXTIx_GPIO               BSP_EXTI4_GPIO                 /* �ⲿ�ж����ڶ˿�             */
	#define BSP_EXTIx_PIN                BSP_EXTI4_PIN                  /* �ⲿ�ж����ڹܽ�             */
	#define BSP_EXTIx_IN_MODE            BSP_EXTI4_IN_MODE              /* ����ģʽ(����/����/����)     */
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	BSP_EXTIx_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = BSP_EXTIx_PIN;
	GPIO_InitStruct.Mode = BSP_EXTIx_MODE_IT;     //������ʽ
	GPIO_InitStruct.Pull = BSP_EXTIx_IN_MODE;     //����/����/����
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; //����
	HAL_GPIO_Init(BSP_EXTIx_GPIO, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(BSP_EXTIx_IRQn, BSP_EXTIx_PRE_INT_PRIO, BSP_EXTIx_SUB_INT_PRIO);
	HAL_NVIC_EnableIRQ(BSP_EXTIx_IRQn);
	
	#undef BSP_EXTIx_CLK_ENABLE
	#undef BSP_EXTIx_MODE_IT
	#undef BSP_EXTIx_IRQn
	#undef BSP_EXTIx_PRE_INT_PRIO
	#undef BSP_EXTIx_SUB_INT_PRIO
	#undef BSP_EXTIx_GPIO
	#undef BSP_EXTIx_PIN
	#undef BSP_EXTIx_IN_MODE
}
XT_CHIP_INIT_2_TAB_EXPORT(bsp_exti4_init, "bsp_exti4_init()");
#endif  //#if (BSP_EXTI4_EN & 0x01)

/**
  * @brief  �ⲿ�ж�9-5��ʼ��
  * @param  void
  * @return void
  */
#if (BSP_EXTI9_5_EN & 0x01)
void bsp_exti9_5_init(void)
{
	#define BSP_EXTIx_CLK_ENABLE()       BSP_EXTI9_5_CLK_ENABLE()       /* �ⲿ�ж�ʱ��ʹ��             */
	#define BSP_EXTIx_MODE_IT            BSP_EXTI9_5_MODE_IT            /* �жϴ�����ʽ                 */
	#define BSP_EXTIx_IRQn               BSP_EXTI9_5_IRQn               /* �ж�ͨ��                     */
	#define BSP_EXTIx_PRE_INT_PRIO       BSP_EXTI9_5_PRE_INT_PRIO       /* ��ռ�ж����ȼ�               */
	#define BSP_EXTIx_SUB_INT_PRIO       BSP_EXTI9_5_SUB_INT_PRIO       /* ��Ӧ�ж����ȼ�               */
	#define BSP_EXTIx_GPIO               BSP_EXTI9_5_GPIO               /* �ⲿ�ж����ڶ˿�             */
	#define BSP_EXTIx_PIN                BSP_EXTI9_5_PIN                /* �ⲿ�ж����ڹܽ�             */
	#define BSP_EXTIx_IN_MODE            BSP_EXTI9_5_IN_MODE            /* ����ģʽ(����/����/����)     */
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	BSP_EXTIx_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = BSP_EXTIx_PIN;
	GPIO_InitStruct.Mode = BSP_EXTIx_MODE_IT;     //������ʽ
	GPIO_InitStruct.Pull = BSP_EXTIx_IN_MODE;     //����/����/����
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; //����
	HAL_GPIO_Init(BSP_EXTIx_GPIO, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(BSP_EXTIx_IRQn, BSP_EXTIx_PRE_INT_PRIO, BSP_EXTIx_SUB_INT_PRIO);
	HAL_NVIC_EnableIRQ(BSP_EXTIx_IRQn);
	
	#undef BSP_EXTIx_CLK_ENABLE
	#undef BSP_EXTIx_MODE_IT
	#undef BSP_EXTIx_IRQn
	#undef BSP_EXTIx_PRE_INT_PRIO
	#undef BSP_EXTIx_SUB_INT_PRIO
	#undef BSP_EXTIx_GPIO
	#undef BSP_EXTIx_PIN
	#undef BSP_EXTIx_IN_MODE
}
XT_CHIP_INIT_2_TAB_EXPORT(bsp_exti9_5_init, "bsp_exti9_5_init()");
#endif  //#if (BSP_EXTI9_5_EN & 0x01)

/**
  * @brief  �ⲿ�ж�15-10��ʼ��
  * @param  void
  * @return void
  */
#if (BSP_EXTI15_10_EN & 0x01)
void bsp_exti15_10_init(void)
{
	#define BSP_EXTIx_CLK_ENABLE()       BSP_EXTI15_10_CLK_ENABLE()     /* �ⲿ�ж�ʱ��ʹ��             */
	#define BSP_EXTIx_MODE_IT            BSP_EXTI15_10_MODE_IT          /* �жϴ�����ʽ                 */
	#define BSP_EXTIx_IRQn               BSP_EXTI15_10_IRQn             /* �ж�ͨ��                     */
	#define BSP_EXTIx_PRE_INT_PRIO       BSP_EXTI15_10_PRE_INT_PRIO     /* ��ռ�ж����ȼ�               */
	#define BSP_EXTIx_SUB_INT_PRIO       BSP_EXTI15_10_SUB_INT_PRIO     /* ��Ӧ�ж����ȼ�               */
	#define BSP_EXTIx_GPIO               BSP_EXTI15_10_GPIO             /* �ⲿ�ж����ڶ˿�             */
	#define BSP_EXTIx_PIN                BSP_EXTI15_10_PIN              /* �ⲿ�ж����ڹܽ�             */
	#define BSP_EXTIx_IN_MODE            BSP_EXTI15_10_IN_MODE          /* ����ģʽ(����/����/����)     */
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	BSP_EXTIx_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = BSP_EXTIx_PIN;
	GPIO_InitStruct.Mode = BSP_EXTIx_MODE_IT;     //������ʽ
	GPIO_InitStruct.Pull = BSP_EXTIx_IN_MODE;     //����/����/����
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; //����
	HAL_GPIO_Init(BSP_EXTIx_GPIO, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(BSP_EXTIx_IRQn, BSP_EXTIx_PRE_INT_PRIO, BSP_EXTIx_SUB_INT_PRIO);
	HAL_NVIC_EnableIRQ(BSP_EXTIx_IRQn);
	
	#undef BSP_EXTIx_CLK_ENABLE
	#undef BSP_EXTIx_MODE_IT
	#undef BSP_EXTIx_IRQn
	#undef BSP_EXTIx_PRE_INT_PRIO
	#undef BSP_EXTIx_SUB_INT_PRIO
	#undef BSP_EXTIx_GPIO
	#undef BSP_EXTIx_PIN
	#undef BSP_EXTIx_IN_MODE
}
XT_CHIP_INIT_2_TAB_EXPORT(bsp_exti15_10_init, "bsp_exti15_10_init()");
#endif  //#if (BSP_EXTI15_10_EN & 0x01)

#if 0
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

#endif  //#if 0
