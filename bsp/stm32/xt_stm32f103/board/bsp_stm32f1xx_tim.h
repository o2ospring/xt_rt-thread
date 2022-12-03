/**
  * @file  bsp_stm32f1xx_tim.h
  * @brief ȫ�ֶ�ʱ����ʱ��������
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-16     o2ospring    ԭʼ�汾
  */
#ifndef BSP_STM32F1XX_TIM_H__
#define BSP_STM32F1XX_TIM_H__

#include <stdint.h> //////////////////////// <- ʹ�õ����ݶ��壬��: int8_t, uint32_t ��
#include "xt_comdef.h" ///////////////////// <- ���ú궨�弯�ϣ���: XT_BIT_SET ��
#include "board.h"   /////////////////////// <- ��������Ӳ����Դ����ͷ�ļ�!!!!!!!!!!!!!!!
#include "bsp_stm32f1xx_wdg.h" ///////////// <- ���ÿ��Ź�����
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

#ifndef BSP_TIM1 /////////////////////
#define BSP_TIM1                     TIM1                               /* ��ʱ��                       */
#define BSP_TIM1_CLK_ENABLE()      __HAL_RCC_TIM1_CLK_ENABLE()          /* ��ʱ��ʱ��ʹ��               */
#define BSP_TIM1_IRQn                TIM1_CC_IRQn                       /* ��ʱ���ж�ͨ��               */
#define BSP_TIM1_PRE_INT_PRIO        0                                  /* ��ʱ����ռ�ж����ȼ�         */
#define BSP_TIM1_SUB_INT_PRIO        0                                  /* ��ʱ����Ӧ�ж����ȼ�         */
#define BSP_TIM1_TICK_US             10/*����:72000000/(1000000/10)*/   /* ��ʱ����������(��:10->10us)  */
#define BSP_TIM1_CCR1                100    /*1ms ��ͨ�ö�ʱ��*/        /* ��ʱ��CCR1                   */
#define BSP_TIM1_CCR2                0xFFF0 /*��������Ӧ��ʹ��*/        /* ��ʱ��CCR2                   */
#define BSP_TIM1_CCR3                0xFFF0 /*��������Ӧ��ʹ��*/        /* ��ʱ��CCR3                   */
#define BSP_TIM1_CCR4                0xFFF0 /*��������Ӧ��ʹ��*/        /* ��ʱ��CCR4                   */
#endif ///////////////////////////////

#ifndef BSP_TIM2 /////////////////////
#define BSP_TIM2                     TIM2                               /* ��ʱ��                       */
#define BSP_TIM2_CLK_ENABLE()      __HAL_RCC_TIM2_CLK_ENABLE()          /* ��ʱ��ʱ��ʹ��               */
#define BSP_TIM2_IRQn                TIM2_IRQn                          /* ��ʱ���ж�ͨ��               */
#define BSP_TIM2_PRE_INT_PRIO        0                                  /* ��ʱ����ռ�ж����ȼ�         */
#define BSP_TIM2_SUB_INT_PRIO        0                                  /* ��ʱ����Ӧ�ж����ȼ�         */
#define BSP_TIM2_TICK_US             10/*����:72000000/(1000000/10)*/   /* ��ʱ����������(��:10->10us)  */
#define BSP_TIM2_CCR1                100    /*1ms ��ͨ�ö�ʱ��*/        /* ��ʱ��CCR1                   */
#define BSP_TIM2_CCR2                0xFFF0 /*��������Ӧ��ʹ��*/        /* ��ʱ��CCR2                   */
#define BSP_TIM2_CCR3                0xFFF0 /*��������Ӧ��ʹ��*/        /* ��ʱ��CCR3                   */
#define BSP_TIM2_CCR4                0xFFF0 /*��������Ӧ��ʹ��*/        /* ��ʱ��CCR4                   */
#endif ///////////////////////////////

#ifndef BSP_TIM3 /////////////////////
#define BSP_TIM3                     TIM3                               /* ��ʱ��                       */
#define BSP_TIM3_CLK_ENABLE()      __HAL_RCC_TIM3_CLK_ENABLE()          /* ��ʱ��ʱ��ʹ��               */
#define BSP_TIM3_IRQn                TIM3_IRQn                          /* ��ʱ���ж�ͨ��               */
#define BSP_TIM3_PRE_INT_PRIO        0                                  /* ��ʱ����ռ�ж����ȼ�         */
#define BSP_TIM3_SUB_INT_PRIO        0                                  /* ��ʱ����Ӧ�ж����ȼ�         */
#define BSP_TIM3_TICK_US             10/*����:72000000/(1000000/10)*/   /* ��ʱ����������(��:10->10us)  */
#define BSP_TIM3_CCR1                100    /*1ms ��ͨ�ö�ʱ��*/        /* ��ʱ��CCR1                   */
#define BSP_TIM3_CCR2                0xFFF0 /*��������Ӧ��ʹ��*/        /* ��ʱ��CCR2                   */
#define BSP_TIM3_CCR3                0xFFF0 /*��������Ӧ��ʹ��*/        /* ��ʱ��CCR3                   */
#define BSP_TIM3_CCR4                0xFFF0 /*��������Ӧ��ʹ��*/        /* ��ʱ��CCR4                   */
#endif ///////////////////////////////

#ifndef BSP_TIM4 /////////////////////
#define BSP_TIM4                     TIM4                               /* ��ʱ��                       */
#define BSP_TIM4_CLK_ENABLE()      __HAL_RCC_TIM4_CLK_ENABLE()          /* ��ʱ��ʱ��ʹ��               */
#define BSP_TIM4_IRQn                TIM4_IRQn                          /* ��ʱ���ж�ͨ��               */
#define BSP_TIM4_PRE_INT_PRIO        0                                  /* ��ʱ����ռ�ж����ȼ�         */
#define BSP_TIM4_SUB_INT_PRIO        0                                  /* ��ʱ����Ӧ�ж����ȼ�         */
#define BSP_TIM4_TICK_US             10/*����:72000000/(1000000/10)*/   /* ��ʱ����������(��:10->10us)  */
#define BSP_TIM4_CCR1                100    /*1ms ��ͨ�ö�ʱ��*/        /* ��ʱ��CCR1                   */
#define BSP_TIM4_CCR2                0xFFF0 /*��������Ӧ��ʹ��*/        /* ��ʱ��CCR2                   */
#define BSP_TIM4_CCR3                0xFFF0 /*��������Ӧ��ʹ��*/        /* ��ʱ��CCR3                   */
#define BSP_TIM4_CCR4                0xFFF0 /*��������Ӧ��ʹ��*/        /* ��ʱ��CCR4                   */
#endif ///////////////////////////////

/********************************************************************************************************/
/*+++++++++++++++++++++++++++++++++++++++++++++++ Ӳ�������� +++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#ifdef BSP_STM32F1XX_TIM_C__
volatile uint32_t time_1ms_tick = 0;
volatile uint32_t time_10ms_tick = 0;
volatile uint32_t time_100ms_tick = 0;
#else
extern volatile uint32_t time_1ms_tick;
extern volatile uint32_t time_10ms_tick;
extern volatile uint32_t time_100ms_tick;
#endif

#if (BSP_WDG_EN & 0x01)
#define WDG_RELOAD()     wdg_reload_counter(1)
#else
#define WDG_RELOAD()
#endif

#if (XT_APP_SCOM_EN == XT_DEF_ENABLED) && (XT_SCOM_HW_DRIVERS_EN == 2)
             extern void xt_scomx_tim_irqhandler(void);
#define XT_SCOMX_OVT()   xt_scomx_tim_irqhandler()
#else
#define XT_SCOMX_OVT()
#endif

#define TIME_MS_TICK()   do                                                                              \
{                                                                                                        \
    static uint8_t time_1ms_cnt = 0;                                                                     \
    time_1ms_tick++;                      /*1ms   Ӳ��������*/                                           \
	XT_SCOMX_OVT();                                                                                      \
    if ((++time_1ms_cnt % 10) == 0)                                                                      \
    {                                                                                                    \
        time_10ms_tick++;                 /*10ms  Ӳ��������*/                                           \
        if ((time_1ms_cnt % 100) == 0)                                                                   \
        {    time_1ms_cnt = 0;                                                                           \
             time_100ms_tick++;           /*100ms Ӳ��������*/                                           \
			 WDG_RELOAD();                                                                               \
        }                                                                                                \
    }                                                                                                    \
}   while (0)

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ ��ʼ���� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void bsp_tim1cc_init(void);
extern void bsp_tim2_init(void);
extern void bsp_tim3_init(void);
extern void bsp_tim4_init(void);
extern void bsp_tim5_init(void);
extern void bsp_tim6_init(void);
extern void bsp_tim7_init(void);
extern void bsp_tim8cc_init(void);

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef BSP_STM32F1XX_TIM_H__
