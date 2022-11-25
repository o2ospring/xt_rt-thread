/**
  * @file  bsp_stm32f1xx_pwm.h
  * @brief ȫ�ֶ�ʱ��PWM��������
  * @notice ������ֻ��Ϊ��ʼ���ο����룬��ΪPWMһ��ר����ĳ��Ӧ��ģ��
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-19     o2ospring    ԭʼ�汾
  */
#ifndef BSP_STM32F1XX_PWM_H__
#define BSP_STM32F1XX_PWM_H__

#include <stdint.h> //////////////////////// <- ʹ�õ����ݶ��壬��: int8_t, uint32_t ��
#include "xt_comdef.h" ///////////////////// <- ���ú궨�弯�ϣ���: XT_BIT_SET ��
#include "board.h"   /////////////////////// <- ��������Ӳ����Դ����ͷ�ļ�!!!!!!!!!!!!!!!
#include "stm32f1xx.h" ///////////////////// <- ����STM32F103��Ƭ��HAL��
/*
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_conf.h" */

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ ���Ŷ��� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#ifdef BSP_STM32F1XX_PWM_C__
#undef  BSP_EXT
#define BSP_EXT
#else
#undef  BSP_EXT
#define BSP_EXT  extern
#endif

#if (BSP_TIMX_PWM_EN & 0x01) && !(defined XXX_TIMX) /////////////////////

// ����PWMƵ�ʵ�
#define XXX_TIMX_DIV         2                                                      //��ʱ����ʱ�ӷ�Ƶ
#define XXX_TIMX_PWM_FRE     1000                                                   //PWM ���Ƶ��
#define XXX_TIMX_PWM_FREVOL  ((72000000 / (XXX_TIMX_DIV+1) / XXX_TIMX_PWM_FRE) - 1) //PWM 100%��ֵ(��0xFFFF)

// ����PWM��ʱ��
#define XXX_TIMX                     TIM2                               /* ��ʱ��                       */
#define XXX_TIMX_CLK_ENABLE()      __HAL_RCC_TIM2_CLK_ENABLE()          /* ��ʱ��ʱ��ʹ��               //
#define XXX_TIMX_AFIO_REMAP()      __HAL_AFIO_REMAP_TIM2_PARTIAL_1()    // ��ʱ��������ӳ��(����������) // //ֻ�� TIM1~5 ����ӳ�� (��:��ӳ��[TIM4~5]�����ֺ���ȫ��ӳ��TIM1~3)
#define XXX_TIMX_HANDLER             htim2                              // ��ʱ�����(����ȫ�־��������//
BSP_EXT TIM_HandleTypeDef            htim2;                             // ��ʱ�����(ȫ�ֱ���,��������)*/

// ����PWM1
#define XXX_PWM1_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()         /* PWM1 �ܽ�ʱ��ʹ��(����������)*/
#define XXX_PWM1_GPIO                GPIOA                              /* PWM1 ���ڶ˿�                */
#define XXX_PWM1_PIN                 GPIO_PIN_0                         /* PWM1 ���ڹܽ�                */
#define XXX_PWM1_OCMODE              TIM_OCMODE_PWM1                    /* PWM1 �������ģʽ(2�򷴼���) */ //ʹ����:��0%,��ֹͣ
#define XXX_PWM1_OCPOLARITY          TIM_OCPOLARITY_HIGH                /* PWM1 ��Чռ�ձ�����ĵ�ƽ    // //����ͨ��
#define XXX_PWM1_OCIDLESTATE         TIM_OCIDLESTATE_RESET              // PWM1 ����ʱ��ƽ(����������)  */ //ֻ���TIM1,������ʱ��Ĭ��Ϊ�͵�ƽ
#define XXX_PWM1_CCRx                CCR1                               /* PWM1 XXX_TIMX->XXX_PWM1_CCRx */ //ռ�ձ�

// ����PWM2
#define XXX_PWM2_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()         /* PWM2 �ܽ�ʱ��ʹ��(����������)*/
#define XXX_PWM2_GPIO                GPIOA                              /* PWM2 ���ڶ˿�                */
#define XXX_PWM2_PIN                 GPIO_PIN_1                         /* PWM2 ���ڹܽ�                */
#define XXX_PWM2_OCMODE              TIM_OCMODE_PWM1                    /* PWM2 �������ģʽ(2�򷴼���) */ //ʹ����:��0%,��ֹͣ
#define XXX_PWM2_OCPOLARITY          TIM_OCPOLARITY_HIGH                /* PWM2 ��Чռ�ձ�����ĵ�ƽ    // //����ͨ��
#define XXX_PWM2_OCIDLESTATE         TIM_OCIDLESTATE_RESET              // PWM2 ����ʱ��ƽ(����������)  */ //ֻ���TIM1,������ʱ��Ĭ��Ϊ�͵�ƽ
#define XXX_PWM2_CCRx                CCR2                               /* PWM2 XXX_TIMX->XXX_PWM2_CCRx */ //ռ�ձ�

// ����PWM3
#define XXX_PWM3_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()         /* PWM3 �ܽ�ʱ��ʹ��(����������)*/
#define XXX_PWM3_GPIO                GPIOA                              /* PWM3 ���ڶ˿�                */
#define XXX_PWM3_PIN                 GPIO_PIN_2                         /* PWM3 ���ڹܽ�                */
#define XXX_PWM3_OCMODE              TIM_OCMODE_PWM1                    /* PWM3 �������ģʽ(2�򷴼���) */ //ʹ����:��0%,��ֹͣ
#define XXX_PWM3_OCPOLARITY          TIM_OCPOLARITY_HIGH                /* PWM3 ��Чռ�ձ�����ĵ�ƽ    // //����ͨ��
#define XXX_PWM3_OCIDLESTATE         TIM_OCIDLESTATE_RESET              // PWM3 ����ʱ��ƽ(����������)  */ //ֻ���TIM1,������ʱ��Ĭ��Ϊ�͵�ƽ
#define XXX_PWM3_CCRx                CCR3                               /* PWM3 XXX_TIMX->XXX_PWM3_CCRx */ //ռ�ձ�

// ����PWM4
#define XXX_PWM4_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()         /* PWM4 �ܽ�ʱ��ʹ��(����������)*/
#define XXX_PWM4_GPIO                GPIOA                              /* PWM4 ���ڶ˿�                */
#define XXX_PWM4_PIN                 GPIO_PIN_3                         /* PWM4 ���ڹܽ�                */
#define XXX_PWM4_OCMODE              TIM_OCMODE_PWM1                    /* PWM4 �������ģʽ(2�򷴼���) */ //ʹ����:��0%,��ֹͣ
#define XXX_PWM4_OCPOLARITY          TIM_OCPOLARITY_HIGH                /* PWM4 ��Чռ�ձ�����ĵ�ƽ    // //����ͨ��
#define XXX_PWM4_OCIDLESTATE         TIM_OCIDLESTATE_RESET              // PWM4 ����ʱ��ƽ(����������)  */ //ֻ���TIM1,������ʱ��Ĭ��Ϊ�͵�ƽ
#define XXX_PWM4_CCRx                CCR4                               /* PWM4 XXX_TIMX->XXX_PWM4_CCRx */ //ռ�ձ�

#endif ///////////////////////////////

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ ��ʼ���� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void bsp_pwm_init(void);

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef BSP_STM32F1XX_PWM_H__


