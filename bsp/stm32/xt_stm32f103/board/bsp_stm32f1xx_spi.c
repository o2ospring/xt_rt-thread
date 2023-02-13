/**
  * @file  bsp_stm32f1xx_spi.c
  * @brief 全局SPI主机驱动程序
  * @notice 本驱动只作为初始化参考代码，因为SPI一般专用于某个应用模块
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    原始版本
  */
#define   BSP_STM32F1XX_SPI_C__
#include "bsp_stm32f1xx_spi.h"
#ifdef    BSP_STM32F1XX_SPI_X__
#undef    BSP_STM32F1XX_SPI_H__
#include "bsp_stm32f1xx_spi.h"
#endif

#ifndef XT_CHIP_INIT_2_TAB_EXPORT
#define XT_CHIP_INIT_2_TAB_EXPORT(func,desc)
#endif

//HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);//发送数据
//HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout); //接收数据

/**
  * @brief  SPI1初始化
  * @param  void
  * @return void
  */
#if (BSP_SPI1_EN & 0x01)
void bsp_spi1_init(void)
{
	#define BSP_SPIx                    BSP_SPI1                        /* 使用的哪个SPI                */
	#define BSP_SPIx_BAUD_RATE          BSP_SPI1_BAUD_RATE              /* 速度(分频): 72/4=18Mbit/S    */
	#define BSP_SPIx_CLK_ENABLE()       BSP_SPI1_CLK_ENABLE()           /* SPI  时钟使能                */
	#define BSP_SPIx_CMS_CLK_ENABLE()   BSP_SPI1_CMS_CLK_ENABLE()       /* SCK-MOSI-MISO 脚时钟使能     */
	#define BSP_SPIx_NSS_CLK_ENABLE()   BSP_SPI1_NSS_CLK_ENABLE()       /* NSS  脚时钟使能              */
	#define BSP_SPIx_NSS_GPIO           BSP_SPI1_NSS_GPIO               /* NSS  所在端口(NSS由软件控制) */
	#define BSP_SPIx_NSS_PIN            BSP_SPI1_NSS_PIN                /* NSS  所在管脚(NSS由软件控制) */
	#define BSP_SPIx_SCK_GPIO           BSP_SPI1_SCK_GPIO               /* SCK  所在端口                */
	#define BSP_SPIx_SCK_PIN            BSP_SPI1_SCK_PIN                /* SCK  所在管脚                */
	#define BSP_SPIx_MISO_GPIO          BSP_SPI1_MISO_GPIO              /* MISO 所在端口                */
	#define BSP_SPIx_MISO_PIN           BSP_SPI1_MISO_PIN               /* MISO 所在管脚                */
	#define BSP_SPIx_MOSI_GPIO          BSP_SPI1_MOSI_GPIO              /* MOSI 所在端口                */
	#define BSP_SPIx_MOSI_PIN           BSP_SPI1_MOSI_PIN               /* MOSI 所在管脚                */
	#define BSP_SPIx_RX_IN_MODE         BSP_SPI1_RX_IN_MODE             /* MISO 输入模式(下拉/上拉/悬空)*/
	#define BSP_SPIx_DIRECTION_LINES    BSP_SPI1_DIRECTION_LINES        /* 收发使用几线(全双工/半双工)  */
	#ifdef                              BSP_SPI1_AFIO_REMAP
	#define BSP_SPIx_AFIO_REMAP()       BSP_SPI1_AFIO_REMAP()           /* SPI  引脚重映射(不使用则屏蔽)*/
	#endif
	#ifdef                              BSP_SPI1_HANDLER
	#define BSP_SPIx_HANDLER            BSP_SPI1_HANDLER                /* SPI  句柄                    */
	#endif
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	#ifndef BSP_SPIx_HANDLER
	#define BSP_SPIx_HANDLER SPIx_Handler
	SPI_HandleTypeDef BSP_SPIx_HANDLER;
	#endif
	
	BSP_SPIx_NSS_CLK_ENABLE();
	BSP_SPIx_CMS_CLK_ENABLE();
	BSP_SPIx_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = BSP_SPIx_NSS_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(BSP_SPIx_NSS_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = BSP_SPIx_SCK_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(BSP_SPIx_SCK_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = BSP_SPIx_MOSI_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(BSP_SPIx_MOSI_GPIO, &GPIO_InitStruct);
	
	#if (BSP_SPIx_DIRECTION_LINES == SPI_DIRECTION_2LINES)
	GPIO_InitStruct.Pin = BSP_SPIx_MISO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = BSP_SPIx_RX_IN_MODE;
	HAL_GPIO_Init(BSP_SPIx_MISO_GPIO, &GPIO_InitStruct);
	#endif
	
	#ifdef BSP_SPIx_AFIO_REMAP
	BSP_SPIx_AFIO_REMAP();
	#endif
	
	BSP_SPIx_HANDLER.Instance = BSP_SPIx;                              //第几SPI口
	BSP_SPIx_HANDLER.Init.Mode = SPI_MODE_MASTER;                      //主从机选择(Master:主机模式)
	BSP_SPIx_HANDLER.Init.Direction = BSP_SPIx_DIRECTION_LINES;        //收发使用几线(2:全双工，1:半双工)
	BSP_SPIx_HANDLER.Init.DataSize = SPI_DATASIZE_8BIT;                //数据长度是8bit还是16bit
	BSP_SPIx_HANDLER.Init.CLKPolarity = SPI_POLARITY_HIGH;             //High:时钟非工作时为高电平，Low:则为低电平
	BSP_SPIx_HANDLER.Init.CLKPhase = SPI_PHASE_2EDGE;                  //2Edge:时钟偶数跳变沿传输数据，1Edge:则为奇数跳变沿
	BSP_SPIx_HANDLER.Init.NSS = SPI_NSS_SOFT;                          //由软件控制NSS片选动作
	BSP_SPIx_HANDLER.Init.BaudRatePrescaler = BSP_SPIx_BAUD_RATE;      //分频(速度)，如: 72/4=18Mbit/S
	BSP_SPIx_HANDLER.Init.FirstBit = SPI_FIRSTBIT_MSB;                 //MSB:先传数据高位，LSB:先传数据低位
	BSP_SPIx_HANDLER.Init.TIMode = SPI_TIMODE_DISABLE;
	BSP_SPIx_HANDLER.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE; //CRC校验关闭
	BSP_SPIx_HANDLER.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&BSP_SPIx_HANDLER) != HAL_OK) {}
	
	#undef BSP_SPIx
	#undef BSP_SPIx_BAUD_RATE
	#undef BSP_SPIx_CLK_ENABLE
	#undef BSP_SPIx_CMS_CLK_ENABLE
	#undef BSP_SPIx_NSS_CLK_ENABLE
	#undef BSP_SPIx_NSS_GPIO
	#undef BSP_SPIx_NSS_PIN
	#undef BSP_SPIx_SCK_GPIO
	#undef BSP_SPIx_SCK_PIN
	#undef BSP_SPIx_MOSI_GPIO
	#undef BSP_SPIx_MOSI_PIN
	#undef BSP_SPIx_MISO_GPIO
	#undef BSP_SPIx_MISO_PIN
	#undef BSP_SPIx_RX_IN_MODE
	#undef BSP_SPIx_DIRECTION_LINES
	#ifdef BSP_SPIx_AFIO_REMAP
	#undef BSP_SPIx_AFIO_REMAP
	#endif
	#undef BSP_SPIx_HANDLER
}
XT_CHIP_INIT_2_TAB_EXPORT(bsp_spi1_init, "bsp_spi1_init()");
#endif  //#if (BSP_SPI1_EN & 0x01)

/**
  * @brief  SPI2初始化
  * @param  void
  * @return void
  */
#if (BSP_SPI2_EN & 0x01)
void bsp_spi2_init(void)
{
	#define BSP_SPIx                    BSP_SPI2                        /* 使用的哪个SPI                */
	#define BSP_SPIx_BAUD_RATE          BSP_SPI2_BAUD_RATE              /* 速度(分频): 72/4=18Mbit/S    */
	#define BSP_SPIx_CLK_ENABLE()       BSP_SPI2_CLK_ENABLE()           /* SPI  时钟使能                */
	#define BSP_SPIx_CMS_CLK_ENABLE()   BSP_SPI2_CMS_CLK_ENABLE()       /* SCK-MOSI-MISO 脚时钟使能     */
	#define BSP_SPIx_NSS_CLK_ENABLE()   BSP_SPI2_NSS_CLK_ENABLE()       /* NSS  脚时钟使能              */
	#define BSP_SPIx_NSS_GPIO           BSP_SPI2_NSS_GPIO               /* NSS  所在端口(NSS由软件控制) */
	#define BSP_SPIx_NSS_PIN            BSP_SPI2_NSS_PIN                /* NSS  所在管脚(NSS由软件控制) */
	#define BSP_SPIx_SCK_GPIO           BSP_SPI2_SCK_GPIO               /* SCK  所在端口                */
	#define BSP_SPIx_SCK_PIN            BSP_SPI2_SCK_PIN                /* SCK  所在管脚                */
	#define BSP_SPIx_MISO_GPIO          BSP_SPI2_MISO_GPIO              /* MISO 所在端口                */
	#define BSP_SPIx_MISO_PIN           BSP_SPI2_MISO_PIN               /* MISO 所在管脚                */
	#define BSP_SPIx_MOSI_GPIO          BSP_SPI2_MOSI_GPIO              /* MOSI 所在端口                */
	#define BSP_SPIx_MOSI_PIN           BSP_SPI2_MOSI_PIN               /* MOSI 所在管脚                */
	#define BSP_SPIx_RX_IN_MODE         BSP_SPI2_RX_IN_MODE             /* MISO 输入模式(下拉/上拉/悬空)*/
	#define BSP_SPIx_DIRECTION_LINES    BSP_SPI2_DIRECTION_LINES        /* 收发使用几线(全双工/半双工)  */
	#ifdef                              BSP_SPI2_AFIO_REMAP
	#define BSP_SPIx_AFIO_REMAP()       BSP_SPI2_AFIO_REMAP()           /* SPI  引脚重映射(不使用则屏蔽)*/
	#endif
	#ifdef                              BSP_SPI2_HANDLER
	#define BSP_SPIx_HANDLER            BSP_SPI2_HANDLER                /* SPI  句柄                    */
	#endif
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	#ifndef BSP_SPIx_HANDLER
	#define BSP_SPIx_HANDLER SPIx_Handler
	SPI_HandleTypeDef BSP_SPIx_HANDLER;
	#endif
	
	BSP_SPIx_NSS_CLK_ENABLE();
	BSP_SPIx_CMS_CLK_ENABLE();
	BSP_SPIx_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = BSP_SPIx_NSS_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(BSP_SPIx_NSS_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = BSP_SPIx_SCK_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(BSP_SPIx_SCK_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = BSP_SPIx_MOSI_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(BSP_SPIx_MOSI_GPIO, &GPIO_InitStruct);
	
	#if (BSP_SPIx_DIRECTION_LINES == SPI_DIRECTION_2LINES)
	GPIO_InitStruct.Pin = BSP_SPIx_MISO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = BSP_SPIx_RX_IN_MODE;
	HAL_GPIO_Init(BSP_SPIx_MISO_GPIO, &GPIO_InitStruct);
	#endif
	
	#ifdef BSP_SPIx_AFIO_REMAP
	BSP_SPIx_AFIO_REMAP();
	#endif
	
	BSP_SPIx_HANDLER.Instance = BSP_SPIx;                              //第几SPI口
	BSP_SPIx_HANDLER.Init.Mode = SPI_MODE_MASTER;                      //主从机选择(Master:主机模式)
	BSP_SPIx_HANDLER.Init.Direction = BSP_SPIx_DIRECTION_LINES;        //收发使用几线(2:全双工，1:半双工)
	BSP_SPIx_HANDLER.Init.DataSize = SPI_DATASIZE_8BIT;                //数据长度是8bit还是16bit
	BSP_SPIx_HANDLER.Init.CLKPolarity = SPI_POLARITY_HIGH;             //High:时钟非工作时为高电平，Low:则为低电平
	BSP_SPIx_HANDLER.Init.CLKPhase = SPI_PHASE_2EDGE;                  //2Edge:时钟偶数跳变沿传输数据，1Edge:则为奇数跳变沿
	BSP_SPIx_HANDLER.Init.NSS = SPI_NSS_SOFT;                          //由软件控制NSS片选动作
	BSP_SPIx_HANDLER.Init.BaudRatePrescaler = BSP_SPIx_BAUD_RATE;      //分频(速度)，如: 72/4=18Mbit/S
	BSP_SPIx_HANDLER.Init.FirstBit = SPI_FIRSTBIT_MSB;                 //MSB:先传数据高位，LSB:先传数据低位
	BSP_SPIx_HANDLER.Init.TIMode = SPI_TIMODE_DISABLE;
	BSP_SPIx_HANDLER.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE; //CRC校验关闭
	BSP_SPIx_HANDLER.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&BSP_SPIx_HANDLER) != HAL_OK) {}
	
	#undef BSP_SPIx
	#undef BSP_SPIx_BAUD_RATE
	#undef BSP_SPIx_CLK_ENABLE
	#undef BSP_SPIx_CMS_CLK_ENABLE
	#undef BSP_SPIx_NSS_CLK_ENABLE
	#undef BSP_SPIx_NSS_GPIO
	#undef BSP_SPIx_NSS_PIN
	#undef BSP_SPIx_SCK_GPIO
	#undef BSP_SPIx_SCK_PIN
	#undef BSP_SPIx_MOSI_GPIO
	#undef BSP_SPIx_MOSI_PIN
	#undef BSP_SPIx_MISO_GPIO
	#undef BSP_SPIx_MISO_PIN
	#undef BSP_SPIx_RX_IN_MODE
	#undef BSP_SPIx_DIRECTION_LINES
	#ifdef BSP_SPIx_AFIO_REMAP
	#undef BSP_SPIx_AFIO_REMAP
	#endif
	#undef BSP_SPIx_HANDLER
}
XT_CHIP_INIT_2_TAB_EXPORT(bsp_spi2_init, "bsp_spi2_init()");
#endif  //#if (BSP_SPI2_EN & 0x01)

/**
  * @brief  SPI3初始化
  * @param  void
  * @return void
  */
#if (BSP_SPI3_EN & 0x01)
void bsp_spi3_init(void)
{
	#define BSP_SPIx                    BSP_SPI3                        /* 使用的哪个SPI                */
	#define BSP_SPIx_BAUD_RATE          BSP_SPI3_BAUD_RATE              /* 速度(分频): 72/4=18Mbit/S    */
	#define BSP_SPIx_CLK_ENABLE()       BSP_SPI3_CLK_ENABLE()           /* SPI  时钟使能                */
	#define BSP_SPIx_CMS_CLK_ENABLE()   BSP_SPI3_CMS_CLK_ENABLE()       /* SCK-MOSI-MISO 脚时钟使能     */
	#define BSP_SPIx_NSS_CLK_ENABLE()   BSP_SPI3_NSS_CLK_ENABLE()       /* NSS  脚时钟使能              */
	#define BSP_SPIx_NSS_GPIO           BSP_SPI3_NSS_GPIO               /* NSS  所在端口(NSS由软件控制) */
	#define BSP_SPIx_NSS_PIN            BSP_SPI3_NSS_PIN                /* NSS  所在管脚(NSS由软件控制) */
	#define BSP_SPIx_SCK_GPIO           BSP_SPI3_SCK_GPIO               /* SCK  所在端口                */
	#define BSP_SPIx_SCK_PIN            BSP_SPI3_SCK_PIN                /* SCK  所在管脚                */
	#define BSP_SPIx_MISO_GPIO          BSP_SPI3_MISO_GPIO              /* MISO 所在端口                */
	#define BSP_SPIx_MISO_PIN           BSP_SPI3_MISO_PIN               /* MISO 所在管脚                */
	#define BSP_SPIx_MOSI_GPIO          BSP_SPI3_MOSI_GPIO              /* MOSI 所在端口                */
	#define BSP_SPIx_MOSI_PIN           BSP_SPI3_MOSI_PIN               /* MOSI 所在管脚                */
	#define BSP_SPIx_RX_IN_MODE         BSP_SPI3_RX_IN_MODE             /* MISO 输入模式(下拉/上拉/悬空)*/
	#define BSP_SPIx_DIRECTION_LINES    BSP_SPI3_DIRECTION_LINES        /* 收发使用几线(全双工/半双工)  */
	#ifdef                              BSP_SPI3_AFIO_REMAP
	#define BSP_SPIx_AFIO_REMAP()       BSP_SPI3_AFIO_REMAP()           /* SPI  引脚重映射(不使用则屏蔽)*/
	#endif
	#ifdef                              BSP_SPI3_HANDLER
	#define BSP_SPIx_HANDLER            BSP_SPI3_HANDLER                /* SPI  句柄                    */
	#endif
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	#ifndef BSP_SPIx_HANDLER
	#define BSP_SPIx_HANDLER SPIx_Handler
	SPI_HandleTypeDef BSP_SPIx_HANDLER;
	#endif
	
	BSP_SPIx_NSS_CLK_ENABLE();
	BSP_SPIx_CMS_CLK_ENABLE();
	BSP_SPIx_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = BSP_SPIx_NSS_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(BSP_SPIx_NSS_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = BSP_SPIx_SCK_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(BSP_SPIx_SCK_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = BSP_SPIx_MOSI_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(BSP_SPIx_MOSI_GPIO, &GPIO_InitStruct);
	
	#if (BSP_SPIx_DIRECTION_LINES == SPI_DIRECTION_2LINES)
	GPIO_InitStruct.Pin = BSP_SPIx_MISO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = BSP_SPIx_RX_IN_MODE;
	HAL_GPIO_Init(BSP_SPIx_MISO_GPIO, &GPIO_InitStruct);
	#endif
	
	#ifdef BSP_SPIx_AFIO_REMAP
	BSP_SPIx_AFIO_REMAP();
	#endif
	
	BSP_SPIx_HANDLER.Instance = BSP_SPIx;                              //第几SPI口
	BSP_SPIx_HANDLER.Init.Mode = SPI_MODE_MASTER;                      //主从机选择(Master:主机模式)
	BSP_SPIx_HANDLER.Init.Direction = BSP_SPIx_DIRECTION_LINES;        //收发使用几线(2:全双工，1:半双工)
	BSP_SPIx_HANDLER.Init.DataSize = SPI_DATASIZE_8BIT;                //数据长度是8bit还是16bit
	BSP_SPIx_HANDLER.Init.CLKPolarity = SPI_POLARITY_HIGH;             //High:时钟非工作时为高电平，Low:则为低电平
	BSP_SPIx_HANDLER.Init.CLKPhase = SPI_PHASE_2EDGE;                  //2Edge:时钟偶数跳变沿传输数据，1Edge:则为奇数跳变沿
	BSP_SPIx_HANDLER.Init.NSS = SPI_NSS_SOFT;                          //由软件控制NSS片选动作
	BSP_SPIx_HANDLER.Init.BaudRatePrescaler = BSP_SPIx_BAUD_RATE;      //分频(速度)，如: 72/4=18Mbit/S
	BSP_SPIx_HANDLER.Init.FirstBit = SPI_FIRSTBIT_MSB;                 //MSB:先传数据高位，LSB:先传数据低位
	BSP_SPIx_HANDLER.Init.TIMode = SPI_TIMODE_DISABLE;
	BSP_SPIx_HANDLER.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE; //CRC校验关闭
	BSP_SPIx_HANDLER.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&BSP_SPIx_HANDLER) != HAL_OK) {}
	
	#undef BSP_SPIx
	#undef BSP_SPIx_BAUD_RATE
	#undef BSP_SPIx_CLK_ENABLE
	#undef BSP_SPIx_CMS_CLK_ENABLE
	#undef BSP_SPIx_NSS_CLK_ENABLE
	#undef BSP_SPIx_NSS_GPIO
	#undef BSP_SPIx_NSS_PIN
	#undef BSP_SPIx_SCK_GPIO
	#undef BSP_SPIx_SCK_PIN
	#undef BSP_SPIx_MOSI_GPIO
	#undef BSP_SPIx_MOSI_PIN
	#undef BSP_SPIx_MISO_GPIO
	#undef BSP_SPIx_MISO_PIN
	#undef BSP_SPIx_RX_IN_MODE
	#undef BSP_SPIx_DIRECTION_LINES
	#ifdef BSP_SPIx_AFIO_REMAP
	#undef BSP_SPIx_AFIO_REMAP
	#endif
	#undef BSP_SPIx_HANDLER
}
XT_CHIP_INIT_2_TAB_EXPORT(bsp_spi3_init, "bsp_spi3_init()");
#endif  //#if (BSP_SPI3_EN & 0x01)
