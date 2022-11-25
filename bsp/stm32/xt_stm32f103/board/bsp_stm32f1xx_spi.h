/**
  * @file  bsp_stm32f1xx_spi.h
  * @brief 全局SPI主机驱动程序
  * @notice 本驱动只作为初始化参考代码，因为SPI一般专用于某个应用模块
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    原始版本
  */
#ifndef BSP_STM32F1XX_SPI_H__
#define BSP_STM32F1XX_SPI_H__

#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#include "xt_comdef.h" ///////////////////// <- 常用宏定义集合，如: XT_BIT_SET 等
#include "board.h"   /////////////////////// <- 工程所有硬件资源管理头文件!!!!!!!!!!!!!!!
#include "stm32f1xx.h" ///////////////////// <- 依赖STM32F103单片机HAL库
/*
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_conf.h" */

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 引脚定义 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#ifdef BSP_STM32F1XX_SPI_C__
#undef  BSP_EXT
#define BSP_EXT
#else
#undef  BSP_EXT
#define BSP_EXT  extern
#endif

#if (BSP_SPI1_EN & 0x01) && !(defined BSP_SPI1) /////////////////////////
#define BSP_SPI1                     SPI1                               /* 使用的哪个SPI                */
#define BSP_SPI1_BAUD_RATE           SPI_BAUDRATEPRESCALER_4            /* 速度(分频): 72/4=18Mbit/S    */
#define BSP_SPI1_CLK_ENABLE()      __HAL_RCC_SPI1_CLK_ENABLE()          /* SPI  时钟使能                */
#define BSP_SPI1_CMS_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()         /* SCK-MOSI-MISO 脚时钟使能     */
#define BSP_SPI1_NSS_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()         /* NSS  脚时钟使能              */
#define BSP_SPI1_NSS_GPIO            GPIOA                              /* NSS  所在端口(NSS由软件控制) */
#define BSP_SPI1_NSS_PIN             GPIO_PIN_4                         /* NSS  所在管脚(NSS由软件控制) */
#define BSP_SPI1_SCK_GPIO            GPIOA                              /* SCK  所在端口                */
#define BSP_SPI1_SCK_PIN             GPIO_PIN_5                         /* SCK  所在管脚                */
#define BSP_SPI1_MISO_GPIO           GPIOA                              /* MISO 所在端口                */
#define BSP_SPI1_MISO_PIN            GPIO_PIN_6                         /* MISO 所在管脚                */
#define BSP_SPI1_MOSI_GPIO           GPIOA                              /* MOSI 所在端口                */
#define BSP_SPI1_MOSI_PIN            GPIO_PIN_7                         /* MOSI 所在管脚                */
#define BSP_SPI1_RX_IN_MODE          GPIO_NOPULL                        /* MISO 输入模式(下拉/上拉/悬空)*/
#define BSP_SPI1_DIRECTION_LINES     SPI_DIRECTION_2LINES               /* 收发使用几线(全双工/半双工)  //
#define BSP_SPI1_AFIO_REMAP()      __HAL_AFIO_REMAP_SPI1_ENABLE()       // SPI  引脚重映射(不使用则屏蔽)*/ //只有 SPI1,SPI3 才有映射 
#define BSP_SPI1_HANDLER             hspi1                              /* SPI  句柄                    */
BSP_EXT SPI_HandleTypeDef            hspi1;                             /* SPI  句柄(全局变量声明)      */
#endif ///////////////////////////////

#if (BSP_SPI2_EN & 0x01) && !(defined BSP_SPI2) /////////////////////////
#define BSP_SPI2                     SPI2                               /* 使用的哪个SPI                */
#define BSP_SPI2_BAUD_RATE           SPI_BAUDRATEPRESCALER_4            /* 速度(分频): 72/4=18Mbit/S    */
#define BSP_SPI2_CLK_ENABLE()      __HAL_RCC_SPI2_CLK_ENABLE()          /* SPI  时钟使能                */
#define BSP_SPI2_CMS_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()         /* SCK-MOSI-MISO 脚时钟使能     */
#define BSP_SPI2_NSS_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()         /* NSS  脚时钟使能              */
#define BSP_SPI2_NSS_GPIO            GPIOB                              /* NSS  所在端口(NSS由软件控制) */
#define BSP_SPI2_NSS_PIN             GPIO_PIN_12                        /* NSS  所在管脚(NSS由软件控制) */
#define BSP_SPI2_SCK_GPIO            GPIOB                              /* SCK  所在端口                */
#define BSP_SPI2_SCK_PIN             GPIO_PIN_13                        /* SCK  所在管脚                */
#define BSP_SPI2_MISO_GPIO           GPIOB                              /* MISO 所在端口                */
#define BSP_SPI2_MISO_PIN            GPIO_PIN_14                        /* MISO 所在管脚                */
#define BSP_SPI2_MOSI_GPIO           GPIOB                              /* MOSI 所在端口                */
#define BSP_SPI2_MOSI_PIN            GPIO_PIN_15                        /* MOSI 所在管脚                */
#define BSP_SPI2_RX_IN_MODE          GPIO_NOPULL                        /* MISO 输入模式(下拉/上拉/悬空)*/
#define BSP_SPI2_DIRECTION_LINES     SPI_DIRECTION_2LINES               /* 收发使用几线(全双工/半双工)  //
#define BSP_SPI2_AFIO_REMAP()      __HAL_AFIO_REMAP_SPI1_ENABLE()       // SPI  引脚重映射(不使用则屏蔽)*/ //只有 SPI1,SPI3 才有映射 
#define BSP_SPI2_HANDLER             hspi2                              /* SPI  句柄                    */
BSP_EXT SPI_HandleTypeDef            hspi2;                             /* SPI  句柄(全局变量声明)      */
#endif ///////////////////////////////

#if (BSP_SPI3_EN & 0x01) && !(defined BSP_SPI3) /////////////////////////
#define BSP_SPI3                     SPI3                               /* 使用的哪个SPI                */
#define BSP_SPI3_BAUD_RATE           SPI_BAUDRATEPRESCALER_4            /* 速度(分频): 72/4=18Mbit/S    */
#define BSP_SPI3_CLK_ENABLE()      __HAL_RCC_SPI3_CLK_ENABLE()          /* SPI  时钟使能                */
#define BSP_SPI3_CMS_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()         /* SCK-MOSI-MISO 脚时钟使能     */
#define BSP_SPI3_NSS_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()         /* NSS  脚时钟使能              */
#define BSP_SPI3_NSS_GPIO            GPIOA                              /* NSS  所在端口(NSS由软件控制) */
#define BSP_SPI3_NSS_PIN             GPIO_PIN_15                        /* NSS  所在管脚(NSS由软件控制) */
#define BSP_SPI3_SCK_GPIO            GPIOB                              /* SCK  所在端口                */
#define BSP_SPI3_SCK_PIN             GPIO_PIN_3                         /* SCK  所在管脚                */
#define BSP_SPI3_MISO_GPIO           GPIOB                              /* MISO 所在端口                */
#define BSP_SPI3_MISO_PIN            GPIO_PIN_4                         /* MISO 所在管脚                */
#define BSP_SPI3_MOSI_GPIO           GPIOB                              /* MOSI 所在端口                */
#define BSP_SPI3_MOSI_PIN            GPIO_PIN_5                         /* MOSI 所在管脚                */
#define BSP_SPI3_RX_IN_MODE          GPIO_NOPULL                        /* MISO 输入模式(下拉/上拉/悬空)*/
#define BSP_SPI3_DIRECTION_LINES     SPI_DIRECTION_2LINES               /* 收发使用几线(全双工/半双工)  //
#define BSP_SPI3_AFIO_REMAP()      __HAL_AFIO_REMAP_SPI3_ENABLE()       // SPI  引脚重映射(不使用则屏蔽)*/ //只有 SPI1,SPI3 才有映射 
#define BSP_SPI3_HANDLER             hspi3                              /* SPI  句柄                    */
BSP_EXT SPI_HandleTypeDef            hspi3;                             /* SPI  句柄(全局变量声明)      */
#endif ///////////////////////////////

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 初始函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void bsp_spi1_init(void);
extern void bsp_spi2_init(void);
extern void bsp_spi3_init(void);

//HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);//发送数据
//HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout); //接收数据

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef BSP_STM32F1XX_SPI_H__
