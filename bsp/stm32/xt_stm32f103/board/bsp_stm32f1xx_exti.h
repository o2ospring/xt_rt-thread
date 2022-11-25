/**
  * @file  bsp_stm32f1xx_exti.h
  * @brief ȫ���ⲿ�ж���������
  * @notice ������һ��ֻ��Ϊ��ʼ���ο����룬��Ϊ�ⲿ�жϳ�ר����ĳ��Ӧ��ģ��
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-16     o2ospring    ԭʼ�汾
  */
#ifndef BSP_STM32F1XX_EXTI_H__
#define BSP_STM32F1XX_EXTI_H__

#include <stdint.h> //////////////////////// <- ʹ�õ����ݶ��壬��: int8_t, uint32_t ��
#ifdef BSP_STM32F1XX_EXTI_C__
#include "xt_comdef.h" ///////////////////// <- ���ú궨�弯�ϣ���: XT_BIT_SET ��
#include "board.h"   /////////////////////// <- ��������Ӳ����Դ����ͷ�ļ�!!!!!!!!!!!!!!!
#include "stm32f1xx.h" ///////////////////// <- ����STM32F103��Ƭ��HAL��
/*
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_conf.h" */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ ���Ŷ��� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#ifdef BSP_STM32F1XX_EXTI_C__ ////////////////////////// <- ֻ��[bsp_stm32f1xx_exti.c]�Ż�������Ŷ���!!!!

#ifndef BSP_EXTI0_CLK_ENABLE /////////
#define BSP_EXTI0_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()         /* �ⲿ�ж�ʱ��ʹ��             */
#define BSP_EXTI0_MODE_IT            GPIO_MODE_IT_FALLING               /* �жϴ�����ʽ                 */
#define BSP_EXTI0_IRQn               EXTI0_IRQn                         /* �ж�ͨ��                     */
#define BSP_EXTI0_PRE_INT_PRIO       0                                  /* ��ռ�ж����ȼ�               */
#define BSP_EXTI0_SUB_INT_PRIO       0                                  /* ��Ӧ�ж����ȼ�               */
#define BSP_EXTI0_GPIO               GPIOB                              /* �ⲿ�ж����ڶ˿�             */
#define BSP_EXTI0_PIN                GPIO_PIN_0                         /* �ⲿ�ж����ڹܽ�             */
#define BSP_EXTI0_IN_MODE            GPIO_PULLUP                        /* ����ģʽ(����/����/����)     */
#endif ///////////////////////////////

#ifndef BSP_EXTI1_CLK_ENABLE /////////
#define BSP_EXTI1_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()         /* �ⲿ�ж�ʱ��ʹ��             */
#define BSP_EXTI1_MODE_IT            GPIO_MODE_IT_FALLING               /* �жϴ�����ʽ                 */
#define BSP_EXTI1_IRQn               EXTI1_IRQn                         /* �ж�ͨ��                     */
#define BSP_EXTI1_PRE_INT_PRIO       0                                  /* ��ռ�ж����ȼ�               */
#define BSP_EXTI1_SUB_INT_PRIO       0                                  /* ��Ӧ�ж����ȼ�               */
#define BSP_EXTI1_GPIO               GPIOB                              /* �ⲿ�ж����ڶ˿�             */
#define BSP_EXTI1_PIN                GPIO_PIN_1                         /* �ⲿ�ж����ڹܽ�             */
#define BSP_EXTI1_IN_MODE            GPIO_PULLUP                        /* ����ģʽ(����/����/����)     */
#endif ///////////////////////////////

#ifndef BSP_EXTI2_CLK_ENABLE /////////
#define BSP_EXTI2_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()         /* �ⲿ�ж�ʱ��ʹ��             */
#define BSP_EXTI2_MODE_IT            GPIO_MODE_IT_FALLING               /* �жϴ�����ʽ                 */
#define BSP_EXTI2_IRQn               EXTI2_IRQn                         /* �ж�ͨ��                     */
#define BSP_EXTI2_PRE_INT_PRIO       0                                  /* ��ռ�ж����ȼ�               */
#define BSP_EXTI2_SUB_INT_PRIO       0                                  /* ��Ӧ�ж����ȼ�               */
#define BSP_EXTI2_GPIO               GPIOB                              /* �ⲿ�ж����ڶ˿�             */
#define BSP_EXTI2_PIN                GPIO_PIN_2                         /* �ⲿ�ж����ڹܽ�             */
#define BSP_EXTI2_IN_MODE            GPIO_PULLUP                        /* ����ģʽ(����/����/����)     */
#endif ///////////////////////////////

#ifndef BSP_EXTI3_CLK_ENABLE /////////
#define BSP_EXTI3_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()         /* �ⲿ�ж�ʱ��ʹ��             */
#define BSP_EXTI3_MODE_IT            GPIO_MODE_IT_FALLING               /* �жϴ�����ʽ                 */
#define BSP_EXTI3_IRQn               EXTI3_IRQn                         /* �ж�ͨ��                     */
#define BSP_EXTI3_PRE_INT_PRIO       0                                  /* ��ռ�ж����ȼ�               */
#define BSP_EXTI3_SUB_INT_PRIO       0                                  /* ��Ӧ�ж����ȼ�               */
#define BSP_EXTI3_GPIO               GPIOB                              /* �ⲿ�ж����ڶ˿�             */
#define BSP_EXTI3_PIN                GPIO_PIN_3                         /* �ⲿ�ж����ڹܽ�             */
#define BSP_EXTI3_IN_MODE            GPIO_PULLUP                        /* ����ģʽ(����/����/����)     */
#endif ///////////////////////////////

#ifndef BSP_EXTI4_CLK_ENABLE /////////
#define BSP_EXTI4_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()         /* �ⲿ�ж�ʱ��ʹ��             */
#define BSP_EXTI4_MODE_IT            GPIO_MODE_IT_FALLING               /* �жϴ�����ʽ                 */
#define BSP_EXTI4_IRQn               EXTI4_IRQn                         /* �ж�ͨ��                     */
#define BSP_EXTI4_PRE_INT_PRIO       0                                  /* ��ռ�ж����ȼ�               */
#define BSP_EXTI4_SUB_INT_PRIO       0                                  /* ��Ӧ�ж����ȼ�               */
#define BSP_EXTI4_GPIO               GPIOB                              /* �ⲿ�ж����ڶ˿�             */
#define BSP_EXTI4_PIN                GPIO_PIN_4                         /* �ⲿ�ж����ڹܽ�             */
#define BSP_EXTI4_IN_MODE            GPIO_PULLUP                        /* ����ģʽ(����/����/����)     */
#endif ///////////////////////////////

#ifndef BSP_EXTI9_5_CLK_ENABLE /////////
#define BSP_EXTI9_5_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()         /* �ⲿ�ж�ʱ��ʹ��             */
#define BSP_EXTI9_5_MODE_IT          GPIO_MODE_IT_FALLING               /* �жϴ�����ʽ                 */
#define BSP_EXTI9_5_IRQn             EXTI9_5_IRQn                       /* �ж�ͨ��                     */
#define BSP_EXTI9_5_PRE_INT_PRIO     0                                  /* ��ռ�ж����ȼ�               */
#define BSP_EXTI9_5_SUB_INT_PRIO     0                                  /* ��Ӧ�ж����ȼ�               */
#define BSP_EXTI9_5_GPIO             GPIOB                              /* �ⲿ�ж����ڶ˿�             */
#define BSP_EXTI9_5_PIN              GPIO_PIN_8                         /* �ⲿ�ж����ڹܽ�             */
#define BSP_EXTI9_5_IN_MODE          GPIO_PULLUP                        /* ����ģʽ(����/����/����)     */
#endif ///////////////////////////////

#ifndef BSP_EXTI15_10_CLK_ENABLE /////////
#define BSP_EXTI15_10_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()         /* �ⲿ�ж�ʱ��ʹ��             */
#define BSP_EXTI15_10_MODE_IT        GPIO_MODE_IT_FALLING               /* �жϴ�����ʽ                 */
#define BSP_EXTI15_10_IRQn           EXTI15_10_IRQn                     /* �ж�ͨ��                     */
#define BSP_EXTI15_10_PRE_INT_PRIO   0                                  /* ��ռ�ж����ȼ�               */
#define BSP_EXTI15_10_SUB_INT_PRIO   0                                  /* ��Ӧ�ж����ȼ�               */
#define BSP_EXTI15_10_GPIO           GPIOB                              /* �ⲿ�ж����ڶ˿�             */
#define BSP_EXTI15_10_PIN            GPIO_PIN_14                        /* �ⲿ�ж����ڹܽ�             */
#define BSP_EXTI15_10_IN_MODE        GPIO_PULLUP                        /* ����ģʽ(����/����/����)     */
#endif ///////////////////////////////

#endif ///////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ ��ʼ���� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void bsp_exti0_init(void);
extern void bsp_exti1_init(void);
extern void bsp_exti2_init(void);
extern void bsp_exti3_init(void);
extern void bsp_exti4_init(void);
extern void bsp_exti9_5_init(void);
extern void bsp_exti15_10_init(void);

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef BSP_STM32F1XX_EXTI_H__
