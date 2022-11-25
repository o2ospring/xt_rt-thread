/**
  * @file  bsp_stm32f1xx_spi.h
  * @brief ȫ��SPI������������
  * @notice ������ֻ��Ϊ��ʼ���ο����룬��ΪSPIһ��ר����ĳ��Ӧ��ģ��
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    ԭʼ�汾
  */
#ifndef BSP_STM32F1XX_SPI_H__
#define BSP_STM32F1XX_SPI_H__

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

#ifdef BSP_STM32F1XX_SPI_C__
#undef  BSP_EXT
#define BSP_EXT
#else
#undef  BSP_EXT
#define BSP_EXT  extern
#endif

#if (BSP_SPI1_EN & 0x01) && !(defined BSP_SPI1) /////////////////////////
#define BSP_SPI1                     SPI1                               /* ʹ�õ��ĸ�SPI                */
#define BSP_SPI1_BAUD_RATE           SPI_BAUDRATEPRESCALER_4            /* �ٶ�(��Ƶ): 72/4=18Mbit/S    */
#define BSP_SPI1_CLK_ENABLE()      __HAL_RCC_SPI1_CLK_ENABLE()          /* SPI  ʱ��ʹ��                */
#define BSP_SPI1_CMS_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()         /* SCK-MOSI-MISO ��ʱ��ʹ��     */
#define BSP_SPI1_NSS_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()         /* NSS  ��ʱ��ʹ��              */
#define BSP_SPI1_NSS_GPIO            GPIOA                              /* NSS  ���ڶ˿�(NSS���������) */
#define BSP_SPI1_NSS_PIN             GPIO_PIN_4                         /* NSS  ���ڹܽ�(NSS���������) */
#define BSP_SPI1_SCK_GPIO            GPIOA                              /* SCK  ���ڶ˿�                */
#define BSP_SPI1_SCK_PIN             GPIO_PIN_5                         /* SCK  ���ڹܽ�                */
#define BSP_SPI1_MISO_GPIO           GPIOA                              /* MISO ���ڶ˿�                */
#define BSP_SPI1_MISO_PIN            GPIO_PIN_6                         /* MISO ���ڹܽ�                */
#define BSP_SPI1_MOSI_GPIO           GPIOA                              /* MOSI ���ڶ˿�                */
#define BSP_SPI1_MOSI_PIN            GPIO_PIN_7                         /* MOSI ���ڹܽ�                */
#define BSP_SPI1_RX_IN_MODE          GPIO_NOPULL                        /* MISO ����ģʽ(����/����/����)*/
#define BSP_SPI1_DIRECTION_LINES     SPI_DIRECTION_2LINES               /* �շ�ʹ�ü���(ȫ˫��/��˫��)  //
#define BSP_SPI1_AFIO_REMAP()      __HAL_AFIO_REMAP_SPI1_ENABLE()       // SPI  ������ӳ��(��ʹ��������)*/ //ֻ�� SPI1,SPI3 ����ӳ�� 
#define BSP_SPI1_HANDLER             hspi1                              /* SPI  ���                    */
BSP_EXT SPI_HandleTypeDef            hspi1;                             /* SPI  ���(ȫ�ֱ�������)      */
#endif ///////////////////////////////

#if (BSP_SPI2_EN & 0x01) && !(defined BSP_SPI2) /////////////////////////
#define BSP_SPI2                     SPI2                               /* ʹ�õ��ĸ�SPI                */
#define BSP_SPI2_BAUD_RATE           SPI_BAUDRATEPRESCALER_4            /* �ٶ�(��Ƶ): 72/4=18Mbit/S    */
#define BSP_SPI2_CLK_ENABLE()      __HAL_RCC_SPI2_CLK_ENABLE()          /* SPI  ʱ��ʹ��                */
#define BSP_SPI2_CMS_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()         /* SCK-MOSI-MISO ��ʱ��ʹ��     */
#define BSP_SPI2_NSS_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()         /* NSS  ��ʱ��ʹ��              */
#define BSP_SPI2_NSS_GPIO            GPIOB                              /* NSS  ���ڶ˿�(NSS���������) */
#define BSP_SPI2_NSS_PIN             GPIO_PIN_12                        /* NSS  ���ڹܽ�(NSS���������) */
#define BSP_SPI2_SCK_GPIO            GPIOB                              /* SCK  ���ڶ˿�                */
#define BSP_SPI2_SCK_PIN             GPIO_PIN_13                        /* SCK  ���ڹܽ�                */
#define BSP_SPI2_MISO_GPIO           GPIOB                              /* MISO ���ڶ˿�                */
#define BSP_SPI2_MISO_PIN            GPIO_PIN_14                        /* MISO ���ڹܽ�                */
#define BSP_SPI2_MOSI_GPIO           GPIOB                              /* MOSI ���ڶ˿�                */
#define BSP_SPI2_MOSI_PIN            GPIO_PIN_15                        /* MOSI ���ڹܽ�                */
#define BSP_SPI2_RX_IN_MODE          GPIO_NOPULL                        /* MISO ����ģʽ(����/����/����)*/
#define BSP_SPI2_DIRECTION_LINES     SPI_DIRECTION_2LINES               /* �շ�ʹ�ü���(ȫ˫��/��˫��)  //
#define BSP_SPI2_AFIO_REMAP()      __HAL_AFIO_REMAP_SPI1_ENABLE()       // SPI  ������ӳ��(��ʹ��������)*/ //ֻ�� SPI1,SPI3 ����ӳ�� 
#define BSP_SPI2_HANDLER             hspi2                              /* SPI  ���                    */
BSP_EXT SPI_HandleTypeDef            hspi2;                             /* SPI  ���(ȫ�ֱ�������)      */
#endif ///////////////////////////////

#if (BSP_SPI3_EN & 0x01) && !(defined BSP_SPI3) /////////////////////////
#define BSP_SPI3                     SPI3                               /* ʹ�õ��ĸ�SPI                */
#define BSP_SPI3_BAUD_RATE           SPI_BAUDRATEPRESCALER_4            /* �ٶ�(��Ƶ): 72/4=18Mbit/S    */
#define BSP_SPI3_CLK_ENABLE()      __HAL_RCC_SPI3_CLK_ENABLE()          /* SPI  ʱ��ʹ��                */
#define BSP_SPI3_CMS_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()         /* SCK-MOSI-MISO ��ʱ��ʹ��     */
#define BSP_SPI3_NSS_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()         /* NSS  ��ʱ��ʹ��              */
#define BSP_SPI3_NSS_GPIO            GPIOA                              /* NSS  ���ڶ˿�(NSS���������) */
#define BSP_SPI3_NSS_PIN             GPIO_PIN_15                        /* NSS  ���ڹܽ�(NSS���������) */
#define BSP_SPI3_SCK_GPIO            GPIOB                              /* SCK  ���ڶ˿�                */
#define BSP_SPI3_SCK_PIN             GPIO_PIN_3                         /* SCK  ���ڹܽ�                */
#define BSP_SPI3_MISO_GPIO           GPIOB                              /* MISO ���ڶ˿�                */
#define BSP_SPI3_MISO_PIN            GPIO_PIN_4                         /* MISO ���ڹܽ�                */
#define BSP_SPI3_MOSI_GPIO           GPIOB                              /* MOSI ���ڶ˿�                */
#define BSP_SPI3_MOSI_PIN            GPIO_PIN_5                         /* MOSI ���ڹܽ�                */
#define BSP_SPI3_RX_IN_MODE          GPIO_NOPULL                        /* MISO ����ģʽ(����/����/����)*/
#define BSP_SPI3_DIRECTION_LINES     SPI_DIRECTION_2LINES               /* �շ�ʹ�ü���(ȫ˫��/��˫��)  //
#define BSP_SPI3_AFIO_REMAP()      __HAL_AFIO_REMAP_SPI3_ENABLE()       // SPI  ������ӳ��(��ʹ��������)*/ //ֻ�� SPI1,SPI3 ����ӳ�� 
#define BSP_SPI3_HANDLER             hspi3                              /* SPI  ���                    */
BSP_EXT SPI_HandleTypeDef            hspi3;                             /* SPI  ���(ȫ�ֱ�������)      */
#endif ///////////////////////////////

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ ��ʼ���� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void bsp_spi1_init(void);
extern void bsp_spi2_init(void);
extern void bsp_spi3_init(void);

//HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);//��������
//HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout); //��������

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef BSP_STM32F1XX_SPI_H__
