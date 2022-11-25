/**
  * @file  bsp_stm32f1xx_uart.h
  * @brief ȫ�ִ�����������
  * @notice ������ֻ��Ϊ��ʼ���ο����룬��Ϊ����һ��ר����ĳ��Ӧ��ģ��
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    ԭʼ�汾
  */
#ifndef BSP_STM32F1XX_UART_H__
#define BSP_STM32F1XX_UART_H__

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

#ifdef BSP_STM32F1XX_UART_C__
#undef  BSP_EXT
#define BSP_EXT
#else
#undef  BSP_EXT
#define BSP_EXT  extern
#endif

#if (BSP_USART1_EN & 0x01) && !(defined BSP_UART1) //////////////////////
#define BSP_UART1                    USART1                             /* ʹ�õ��ĸ�����               */
#define BSP_UART1_BAUD_RATE          9600                               /* ͨѶ������: 9600bps          */
#define BSP_UART1_CLK_ENABLE()     __HAL_RCC_USART1_CLK_ENABLE()        /* ����ʱ��ʹ��                 */
#define BSP_UART1_TX_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()         /* TX��ʱ��ʹ��                 */
#define BSP_UART1_RX_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()         /* RX��ʱ��ʹ��                 */
#define BSP_UART1_IRQn               USART1_IRQn                        /* �ж�ͨ��                     */
#define BSP_UART1_PRE_INT_PRIO       0                                  /* ��ռ�ж����ȼ�               */
#define BSP_UART1_SUB_INT_PRIO       0                                  /* ��Ӧ�ж����ȼ�               */
#define BSP_UART1_TX_GPIO            GPIOA                              /* TX ���ڶ˿�                  */
#define BSP_UART1_TX_PIN             GPIO_PIN_9                         /* TX ���ڹܽ�                  */
#define BSP_UART1_RX_GPIO            GPIOA                              /* RX ���ڶ˿�                  */
#define BSP_UART1_RX_PIN             GPIO_PIN_10                        /* RX ���ڹܽ�                  */
#define BSP_UART1_RX_IN_MODE         GPIO_PULLUP                        /* RX ����ģʽ(����/����)       //
#define BSP_UART1_AFIO_REMAP()     __HAL_AFIO_REMAP_USART1_ENABLE()     // ����������ӳ��(��ʹ��������) //
#define BSP_UART1_HANDLER            huart1                             // ���ھ��(��ʹ��ȫ�־��������//
BSP_EXT UART_HandleTypeDef           huart1;                            // ���ھ��(ȫ�ֱ���,����ʱ����)*/
#endif ///////////////////////////////

#if (BSP_USART2_EN & 0x01) && !(defined BSP_UART2) //////////////////////
#define BSP_UART2                    USART2                             /* ʹ�õ��ĸ�����               */
#define BSP_UART2_BAUD_RATE          9600                               /* ͨѶ������: 9600bps          */
#define BSP_UART2_CLK_ENABLE()     __HAL_RCC_USART2_CLK_ENABLE()        /* ����ʱ��ʹ��                 */
#define BSP_UART2_TX_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()         /* TX��ʱ��ʹ��                 */
#define BSP_UART2_RX_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()         /* RX��ʱ��ʹ��                 */
#define BSP_UART2_IRQn               USART2_IRQn                        /* �ж�ͨ��                     */
#define BSP_UART2_PRE_INT_PRIO       0                                  /* ��ռ�ж����ȼ�               */
#define BSP_UART2_SUB_INT_PRIO       0                                  /* ��Ӧ�ж����ȼ�               */
#define BSP_UART2_TX_GPIO            GPIOA                              /* TX ���ڶ˿�                  */
#define BSP_UART2_TX_PIN             GPIO_PIN_2                         /* TX ���ڹܽ�                  */
#define BSP_UART2_RX_GPIO            GPIOA                              /* RX ���ڶ˿�                  */
#define BSP_UART2_RX_PIN             GPIO_PIN_3                         /* RX ���ڹܽ�                  */
#define BSP_UART2_RX_IN_MODE         GPIO_PULLUP                        /* RX ����ģʽ(����/����)       //
#define BSP_UART2_AFIO_REMAP()     __HAL_AFIO_REMAP_USART2_ENABLE()     // ����������ӳ��(��ʹ��������) //
#define BSP_UART2_HANDLER            huart2                             // ���ھ��(��ʹ��ȫ�־��������//
BSP_EXT UART_HandleTypeDef           huart2;                            // ���ھ��(ȫ�ֱ���,����ʱ����)*/
#endif ///////////////////////////////

#if (BSP_USART3_EN & 0x01) && !(defined BSP_UART3) //////////////////////
#define BSP_UART3                    USART3                             /* ʹ�õ��ĸ�����               */
#define BSP_UART3_BAUD_RATE          9600                               /* ͨѶ������: 9600bps          */
#define BSP_UART3_CLK_ENABLE()     __HAL_RCC_USART3_CLK_ENABLE()        /* ����ʱ��ʹ��                 */
#define BSP_UART3_TX_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()         /* TX��ʱ��ʹ��                 */
#define BSP_UART3_RX_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()         /* RX��ʱ��ʹ��                 */
#define BSP_UART3_IRQn               USART3_IRQn                        /* �ж�ͨ��                     */
#define BSP_UART3_PRE_INT_PRIO       0                                  /* ��ռ�ж����ȼ�               */
#define BSP_UART3_SUB_INT_PRIO       0                                  /* ��Ӧ�ж����ȼ�               */
#define BSP_UART3_TX_GPIO            GPIOB                              /* TX ���ڶ˿�                  */
#define BSP_UART3_TX_PIN             GPIO_PIN_10                        /* TX ���ڹܽ�                  */
#define BSP_UART3_RX_GPIO            GPIOB                              /* RX ���ڶ˿�                  */
#define BSP_UART3_RX_PIN             GPIO_PIN_11                        /* RX ���ڹܽ�                  */
#define BSP_UART3_RX_IN_MODE         GPIO_PULLUP                        /* RX ����ģʽ(����/����)       //
#define BSP_UART3_AFIO_REMAP()     __HAL_AFIO_REMAP_USART3_ENABLE()     // ����������ӳ��(��ʹ��������) //
#define BSP_UART3_HANDLER            huart3                             // ���ھ��(��ʹ��ȫ�־��������//
BSP_EXT UART_HandleTypeDef           huart3;                            // ���ھ��(ȫ�ֱ���,����ʱ����)*/
#endif ///////////////////////////////

#if (BSP_UART4_EN & 0x01) && !(defined BSP_UART4) ///////////////////////
#define BSP_UART4                    UART4                              /* ʹ�õ��ĸ�����               */
#define BSP_UART4_BAUD_RATE          9600                               /* ͨѶ������: 9600bps          */
#define BSP_UART4_CLK_ENABLE()     __HAL_RCC_UART4_CLK_ENABLE()         /* ����ʱ��ʹ��                 */
#define BSP_UART4_TX_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()         /* TX��ʱ��ʹ��                 */
#define BSP_UART4_RX_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()         /* RX��ʱ��ʹ��                 */
#define BSP_UART4_IRQn               UART4_IRQn                         /* �ж�ͨ��                     */
#define BSP_UART4_PRE_INT_PRIO       0                                  /* ��ռ�ж����ȼ�               */
#define BSP_UART4_SUB_INT_PRIO       0                                  /* ��Ӧ�ж����ȼ�               */
#define BSP_UART4_TX_GPIO            GPIOC                              /* TX ���ڶ˿�                  */
#define BSP_UART4_TX_PIN             GPIO_PIN_10                        /* TX ���ڹܽ�                  */
#define BSP_UART4_RX_GPIO            GPIOC                              /* RX ���ڶ˿�                  */
#define BSP_UART4_RX_PIN             GPIO_PIN_11                        /* RX ���ڹܽ�                  */
#define BSP_UART4_RX_IN_MODE         GPIO_PULLUP                        /* RX ����ģʽ(����/����)       //
#define BSP_UART4_AFIO_REMAP()     __HAL_AFIO_REMAP_USART1_ENABLE()     // ����������ӳ��(��ʹ��������) //
#define BSP_UART4_HANDLER            huart4                             // ���ھ��(��ʹ��ȫ�־��������//
BSP_EXT UART_HandleTypeDef           huart4;                            // ���ھ��(ȫ�ֱ���,����ʱ����)*/
#endif ///////////////////////////////

#if (BSP_UART5_EN & 0x01) && !(defined BSP_UART5) ///////////////////////
#define BSP_UART5                    UART5                              /* ʹ�õ��ĸ�����               */
#define BSP_UART5_BAUD_RATE          9600                               /* ͨѶ������: 9600bps          */
#define BSP_UART5_CLK_ENABLE()     __HAL_RCC_UART5_CLK_ENABLE()         /* ����ʱ��ʹ��                 */
#define BSP_UART5_TX_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()         /* TX��ʱ��ʹ��                 */
#define BSP_UART5_RX_CLK_ENABLE()  __HAL_RCC_GPIOD_CLK_ENABLE()         /* RX��ʱ��ʹ��                 */
#define BSP_UART5_IRQn               UART5_IRQn                         /* �ж�ͨ��                     */
#define BSP_UART5_PRE_INT_PRIO       0                                  /* ��ռ�ж����ȼ�               */
#define BSP_UART5_SUB_INT_PRIO       0                                  /* ��Ӧ�ж����ȼ�               */
#define BSP_UART5_TX_GPIO            GPIOC                              /* TX ���ڶ˿�                  */
#define BSP_UART5_TX_PIN             GPIO_PIN_12                        /* TX ���ڹܽ�                  */
#define BSP_UART5_RX_GPIO            GPIOD                              /* RX ���ڶ˿�                  */
#define BSP_UART5_RX_PIN             GPIO_PIN_2                         /* RX ���ڹܽ�                  */
#define BSP_UART5_RX_IN_MODE         GPIO_PULLUP                        /* RX ����ģʽ(����/����)       //
#define BSP_UART5_AFIO_REMAP()     __HAL_AFIO_REMAP_USART1_ENABLE()     // ����������ӳ��(��ʹ��������) //
#define BSP_UART5_HANDLER            huart5                             // ���ھ��(��ʹ��ȫ�־��������//
BSP_EXT UART_HandleTypeDef           huart5;                            // ���ھ��(ȫ�ֱ���,����ʱ����)*/
#endif ///////////////////////////////

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ ��ʼ���� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void bsp_usart1_init(void);
extern void bsp_usart2_init(void);
extern void bsp_usart3_init(void);
extern void bsp_uart4_init(void);
extern void bsp_uart5_init(void);

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef BSP_STM32F1XX_UART_H__
