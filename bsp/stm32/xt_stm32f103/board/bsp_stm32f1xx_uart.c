/**
  * @file  bsp_stm32f1xx_uart.c
  * @brief 全局串口驱动程序
  * @notice 本驱动只作为初始化参考代码，因为串口一般专用于某个应用模块
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    原始版本
  */
#define   BSP_STM32F1XX_UART_C__
#include "bsp_stm32f1xx_uart.h"
#ifdef    BSP_STM32F1XX_UART_X__
#undef    BSP_STM32F1XX_UART_H__
#include "bsp_stm32f1xx_uart.h"
#endif

#ifndef XT_CHIP_INIT_5_TAB_EXPORT
#define XT_CHIP_INIT_5_TAB_EXPORT(func,desc)
#endif

/**
  * @brief  串口1初始化
  * @param  void
  * @return void
  */
#if (BSP_USART1_EN & 0x01)
void bsp_usart1_init(void)
{
	#define BSP_UARTx                   BSP_UART1                       /* 使用的哪个串口               */
	#define BSP_UARTx_BAUD_RATE         BSP_UART1_BAUD_RATE             /* 通讯波特率: 9600bps          */
	#define BSP_UARTx_CLK_ENABLE()      BSP_UART1_CLK_ENABLE()          /* 串口时钟使能                 */
	#define BSP_UARTx_TX_CLK_ENABLE()   BSP_UART1_TX_CLK_ENABLE()       /* TX脚时钟使能                 */
	#define BSP_UARTx_RX_CLK_ENABLE()   BSP_UART1_RX_CLK_ENABLE()       /* RX脚时钟使能                 */
	#define BSP_UARTx_IRQn              BSP_UART1_IRQn                  /* 中断通道                     */
	#define BSP_UARTx_PRE_INT_PRIO      BSP_UART1_PRE_INT_PRIO          /* 抢占中断优先级               */
	#define BSP_UARTx_SUB_INT_PRIO      BSP_UART1_SUB_INT_PRIO          /* 响应中断优先级               */
	#define BSP_UARTx_TX_GPIO           BSP_UART1_TX_GPIO               /* TX 所在端口                  */
	#define BSP_UARTx_TX_PIN            BSP_UART1_TX_PIN                /* TX 所在管脚                  */
	#define BSP_UARTx_RX_GPIO           BSP_UART1_RX_GPIO               /* RX 所在端口                  */
	#define BSP_UARTx_RX_PIN            BSP_UART1_RX_PIN                /* RX 所在管脚                  */
	#define BSP_UARTx_RX_IN_MODE        BSP_UART1_RX_IN_MODE            /* RX 输入模式(上拉/悬空)       */
	#ifdef                              BSP_UART1_AFIO_REMAP
	#define BSP_UARTx_AFIO_REMAP()      BSP_UART1_AFIO_REMAP()          /* 串口引脚重映射(不使用则屏蔽) */
	#endif
	#ifdef                              BSP_UART1_HANDLER
	#define BSP_UARTx_HANDLER           BSP_UART1_HANDLER               /* 串口句柄(不使用全局句柄则屏蔽*/
	#endif
	
	GPIO_InitTypeDef GPIO_Initure;
	#ifndef BSP_UARTx_HANDLER
	#define BSP_UARTx_HANDLER UARTx_Handler
	UART_HandleTypeDef BSP_UARTx_HANDLER;      //串口句柄（HAL库标准用法则要求为全局变量）
	#endif
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > [时钟-引脚-优先级]初始化的HAL库内部实现写法为：
	// > `HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)`
	// >> `if (huart->gState == HAL_UART_STATE_RESET)`
	// >> `HAL_UART_MspInit(huart);`           //回调用户提供的回调函数(1.使能时钟, 2.设置引脚和中断优先级)
	BSP_UARTx_TX_CLK_ENABLE();
	BSP_UARTx_RX_CLK_ENABLE();
	BSP_UARTx_CLK_ENABLE();
	
	GPIO_Initure.Pin   = BSP_UARTx_TX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_AF_PP;      //复用推挽输出
	GPIO_Initure.Pull  = GPIO_PULLUP;          //上拉
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //高速
	HAL_GPIO_Init(BSP_UARTx_TX_GPIO, &GPIO_Initure);
	
	GPIO_Initure.Pin   = BSP_UARTx_RX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_INPUT;      //输入模式
	GPIO_Initure.Pull  = BSP_UARTx_RX_IN_MODE; //上拉/悬空
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //高速
	HAL_GPIO_Init(BSP_UARTx_RX_GPIO, &GPIO_Initure);
	
	#ifdef BSP_UARTx_AFIO_REMAP
	BSP_UARTx_AFIO_REMAP();
	#endif
	
	HAL_NVIC_SetPriority(BSP_UARTx_IRQn, BSP_UARTx_PRE_INT_PRIO, BSP_UARTx_SUB_INT_PRIO);
	HAL_NVIC_EnableIRQ(BSP_UARTx_IRQn);
	
	/* USARTx and USARTx configuration  */
	/* USART and USARTx configured as follow:
	   - BaudRate = 9600 baud  
	   - Word Length = 8 Bits
	   - One Stop Bit
	   - Even parity
	   - Hardware flow control disabled (RTS and CTS signals)
	   - Receive and transmit enabled
	*/
	BSP_UARTx_HANDLER.gState = HAL_UART_STATE_RESET;            // 初始化
	BSP_UARTx_HANDLER.Instance = BSP_UARTx;                     // 串口
	BSP_UARTx_HANDLER.Init.BaudRate = BSP_UARTx_BAUD_RATE;      // 波特率:9600
	BSP_UARTx_HANDLER.Init.WordLength = UART_WORDLENGTH_8B;     // 数据长度:8位
	BSP_UARTx_HANDLER.Init.StopBits = UART_STOPBITS_1;          // 停止位:1位
	BSP_UARTx_HANDLER.Init.Parity = UART_PARITY_NONE;           // 奇偶校验:无
	BSP_UARTx_HANDLER.Init.Mode = UART_MODE_TX_RX;              // 发送及接收使能(后面会关闭发送中断)
	BSP_UARTx_HANDLER.Init.HwFlowCtl = UART_HWCONTROL_NONE;     // 流控制:无
	BSP_UARTx_HANDLER.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&BSP_UARTx_HANDLER) != HAL_OK) {}
	
	__HAL_UART_DISABLE_IT(&BSP_UARTx_HANDLER, UART_IT_TXE);     // 关发送中断 ★★★★★★★★
	__HAL_UART_ENABLE_IT(&BSP_UARTx_HANDLER, UART_IT_RXNE);     // 开接收中断
	
	#undef BSP_UARTx
	#undef BSP_UARTx_CLK_ENABLE
	#undef BSP_UARTx_TX_CLK_ENABLE
	#undef BSP_UARTx_RX_CLK_ENABLE
	#undef BSP_UARTx_IRQn
	#undef BSP_UARTx_BAUD_RATE
	#undef BSP_UARTx_PRE_INT_PRIO
	#undef BSP_UARTx_SUB_INT_PRIO
	#undef BSP_UARTx_TX_GPIO
	#undef BSP_UARTx_TX_PIN
	#undef BSP_UARTx_RX_GPIO
	#undef BSP_UARTx_RX_PIN
	#undef BSP_UARTx_RX_IN_MODE
	#ifdef BSP_UARTx_AFIO_REMAP
	#undef BSP_UARTx_AFIO_REMAP
	#endif
	#undef BSP_UARTx_HANDLER
}
XT_CHIP_INIT_5_TAB_EXPORT(bsp_usart1_init, "bsp_usart1_init()");
#endif  //#if (BSP_USART1_EN & 0x01)

/**
  * @brief  串口2初始化
  * @param  void
  * @return void
  */
#if (BSP_USART2_EN & 0x01)
void bsp_usart2_init(void)
{
	#define BSP_UARTx                   BSP_UART2                       /* 使用的哪个串口               */
	#define BSP_UARTx_BAUD_RATE         BSP_UART2_BAUD_RATE             /* 通讯波特率: 9600bps          */
	#define BSP_UARTx_CLK_ENABLE()      BSP_UART2_CLK_ENABLE()          /* 串口时钟使能                 */
	#define BSP_UARTx_TX_CLK_ENABLE()   BSP_UART2_TX_CLK_ENABLE()       /* TX脚时钟使能                 */
	#define BSP_UARTx_RX_CLK_ENABLE()   BSP_UART2_RX_CLK_ENABLE()       /* RX脚时钟使能                 */
	#define BSP_UARTx_IRQn              BSP_UART2_IRQn                  /* 中断通道                     */
	#define BSP_UARTx_PRE_INT_PRIO      BSP_UART2_PRE_INT_PRIO          /* 抢占中断优先级               */
	#define BSP_UARTx_SUB_INT_PRIO      BSP_UART2_SUB_INT_PRIO          /* 响应中断优先级               */
	#define BSP_UARTx_TX_GPIO           BSP_UART2_TX_GPIO               /* TX 所在端口                  */
	#define BSP_UARTx_TX_PIN            BSP_UART2_TX_PIN                /* TX 所在管脚                  */
	#define BSP_UARTx_RX_GPIO           BSP_UART2_RX_GPIO               /* RX 所在端口                  */
	#define BSP_UARTx_RX_PIN            BSP_UART2_RX_PIN                /* RX 所在管脚                  */
	#define BSP_UARTx_RX_IN_MODE        BSP_UART2_RX_IN_MODE            /* RX 输入模式(上拉/悬空)       */
	#ifdef                              BSP_UART2_AFIO_REMAP
	#define BSP_UARTx_AFIO_REMAP()      BSP_UART2_AFIO_REMAP()          /* 串口引脚重映射(不使用则屏蔽) */
	#endif
	#ifdef                              BSP_UART2_HANDLER
	#define BSP_UARTx_HANDLER           BSP_UART2_HANDLER               /* 串口句柄(不使用全局句柄则屏蔽*/
	#endif
	
	GPIO_InitTypeDef GPIO_Initure;
	#ifndef BSP_UARTx_HANDLER
	#define BSP_UARTx_HANDLER UARTx_Handler
	UART_HandleTypeDef BSP_UARTx_HANDLER;      //串口句柄（HAL库标准用法则要求为全局变量）
	#endif
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > [时钟-引脚-优先级]初始化的HAL库内部实现写法为：
	// > `HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)`
	// >> `if (huart->gState == HAL_UART_STATE_RESET)`
	// >> `HAL_UART_MspInit(huart);`           //回调用户提供的回调函数(1.使能时钟, 2.设置引脚和中断优先级)
	BSP_UARTx_TX_CLK_ENABLE();
	BSP_UARTx_RX_CLK_ENABLE();
	BSP_UARTx_CLK_ENABLE();
	
	GPIO_Initure.Pin   = BSP_UARTx_TX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_AF_PP;      //复用推挽输出
	GPIO_Initure.Pull  = GPIO_PULLUP;          //上拉
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //高速
	HAL_GPIO_Init(BSP_UARTx_TX_GPIO, &GPIO_Initure);
	
	GPIO_Initure.Pin   = BSP_UARTx_RX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_INPUT;      //输入模式
	GPIO_Initure.Pull  = BSP_UARTx_RX_IN_MODE; //上拉/悬空
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //高速
	HAL_GPIO_Init(BSP_UARTx_RX_GPIO, &GPIO_Initure);
	
	#ifdef BSP_UARTx_AFIO_REMAP
	BSP_UARTx_AFIO_REMAP();
	#endif
	
	HAL_NVIC_SetPriority(BSP_UARTx_IRQn, BSP_UARTx_PRE_INT_PRIO, BSP_UARTx_SUB_INT_PRIO);
	HAL_NVIC_EnableIRQ(BSP_UARTx_IRQn);
	
	/* USARTx and USARTx configuration  */
	/* USART and USARTx configured as follow:
	   - BaudRate = 9600 baud  
	   - Word Length = 8 Bits
	   - One Stop Bit
	   - Even parity
	   - Hardware flow control disabled (RTS and CTS signals)
	   - Receive and transmit enabled
	*/
	BSP_UARTx_HANDLER.gState = HAL_UART_STATE_RESET;            // 初始化
	BSP_UARTx_HANDLER.Instance = BSP_UARTx;                     // 串口
	BSP_UARTx_HANDLER.Init.BaudRate = BSP_UARTx_BAUD_RATE;      // 波特率:9600
	BSP_UARTx_HANDLER.Init.WordLength = UART_WORDLENGTH_8B;     // 数据长度:8位
	BSP_UARTx_HANDLER.Init.StopBits = UART_STOPBITS_1;          // 停止位:1位
	BSP_UARTx_HANDLER.Init.Parity = UART_PARITY_NONE;           // 奇偶校验:无
	BSP_UARTx_HANDLER.Init.Mode = UART_MODE_TX_RX;              // 发送及接收使能(后面会关闭发送中断)
	BSP_UARTx_HANDLER.Init.HwFlowCtl = UART_HWCONTROL_NONE;     // 流控制:无
	BSP_UARTx_HANDLER.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&BSP_UARTx_HANDLER) != HAL_OK) {}
	
	__HAL_UART_DISABLE_IT(&BSP_UARTx_HANDLER, UART_IT_TXE);     // 关发送中断 ★★★★★★★★
	__HAL_UART_ENABLE_IT(&BSP_UARTx_HANDLER, UART_IT_RXNE);     // 开接收中断
	
	#undef BSP_UARTx
	#undef BSP_UARTx_CLK_ENABLE
	#undef BSP_UARTx_TX_CLK_ENABLE
	#undef BSP_UARTx_RX_CLK_ENABLE
	#undef BSP_UARTx_IRQn
	#undef BSP_UARTx_BAUD_RATE
	#undef BSP_UARTx_PRE_INT_PRIO
	#undef BSP_UARTx_SUB_INT_PRIO
	#undef BSP_UARTx_TX_GPIO
	#undef BSP_UARTx_TX_PIN
	#undef BSP_UARTx_RX_GPIO
	#undef BSP_UARTx_RX_PIN
	#undef BSP_UARTx_RX_IN_MODE
	#ifdef BSP_UARTx_AFIO_REMAP
	#undef BSP_UARTx_AFIO_REMAP
	#endif
	#undef BSP_UARTx_HANDLER
}
XT_CHIP_INIT_5_TAB_EXPORT(bsp_usart2_init, "bsp_usart2_init()");
#endif  //#if (BSP_USART2_EN & 0x01)

/**
  * @brief  串口3初始化
  * @param  void
  * @return void
  */
#if (BSP_USART3_EN & 0x01)
void bsp_usart3_init(void)
{
	#define BSP_UARTx                   BSP_UART3                       /* 使用的哪个串口               */
	#define BSP_UARTx_BAUD_RATE         BSP_UART3_BAUD_RATE             /* 通讯波特率: 9600bps          */
	#define BSP_UARTx_CLK_ENABLE()      BSP_UART3_CLK_ENABLE()          /* 串口时钟使能                 */
	#define BSP_UARTx_TX_CLK_ENABLE()   BSP_UART3_TX_CLK_ENABLE()       /* TX脚时钟使能                 */
	#define BSP_UARTx_RX_CLK_ENABLE()   BSP_UART3_RX_CLK_ENABLE()       /* RX脚时钟使能                 */
	#define BSP_UARTx_IRQn              BSP_UART3_IRQn                  /* 中断通道                     */
	#define BSP_UARTx_PRE_INT_PRIO      BSP_UART3_PRE_INT_PRIO          /* 抢占中断优先级               */
	#define BSP_UARTx_SUB_INT_PRIO      BSP_UART3_SUB_INT_PRIO          /* 响应中断优先级               */
	#define BSP_UARTx_TX_GPIO           BSP_UART3_TX_GPIO               /* TX 所在端口                  */
	#define BSP_UARTx_TX_PIN            BSP_UART3_TX_PIN                /* TX 所在管脚                  */
	#define BSP_UARTx_RX_GPIO           BSP_UART3_RX_GPIO               /* RX 所在端口                  */
	#define BSP_UARTx_RX_PIN            BSP_UART3_RX_PIN                /* RX 所在管脚                  */
	#define BSP_UARTx_RX_IN_MODE        BSP_UART3_RX_IN_MODE            /* RX 输入模式(上拉/悬空)       */
	#ifdef                              BSP_UART3_AFIO_REMAP
	#define BSP_UARTx_AFIO_REMAP()      BSP_UART3_AFIO_REMAP()          /* 串口引脚重映射(不使用则屏蔽) */
	#endif
	#ifdef                              BSP_UART3_HANDLER
	#define BSP_UARTx_HANDLER           BSP_UART3_HANDLER               /* 串口句柄(不使用全局句柄则屏蔽*/
	#endif
	
	GPIO_InitTypeDef GPIO_Initure;
	#ifndef BSP_UARTx_HANDLER
	#define BSP_UARTx_HANDLER UARTx_Handler
	UART_HandleTypeDef BSP_UARTx_HANDLER;      //串口句柄（HAL库标准用法则要求为全局变量）
	#endif
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > [时钟-引脚-优先级]初始化的HAL库内部实现写法为：
	// > `HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)`
	// >> `if (huart->gState == HAL_UART_STATE_RESET)`
	// >> `HAL_UART_MspInit(huart);`           //回调用户提供的回调函数(1.使能时钟, 2.设置引脚和中断优先级)
	BSP_UARTx_TX_CLK_ENABLE();
	BSP_UARTx_RX_CLK_ENABLE();
	BSP_UARTx_CLK_ENABLE();
	
	GPIO_Initure.Pin   = BSP_UARTx_TX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_AF_PP;      //复用推挽输出
	GPIO_Initure.Pull  = GPIO_PULLUP;          //上拉
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //高速
	HAL_GPIO_Init(BSP_UARTx_TX_GPIO, &GPIO_Initure);
	
	GPIO_Initure.Pin   = BSP_UARTx_RX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_INPUT;      //输入模式
	GPIO_Initure.Pull  = BSP_UARTx_RX_IN_MODE; //上拉/悬空
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //高速
	HAL_GPIO_Init(BSP_UARTx_RX_GPIO, &GPIO_Initure);
	
	#ifdef BSP_UARTx_AFIO_REMAP
	BSP_UARTx_AFIO_REMAP();
	#endif
	
	HAL_NVIC_SetPriority(BSP_UARTx_IRQn, BSP_UARTx_PRE_INT_PRIO, BSP_UARTx_SUB_INT_PRIO);
	HAL_NVIC_EnableIRQ(BSP_UARTx_IRQn);
	
	/* USARTx and USARTx configuration  */
	/* USART and USARTx configured as follow:
	   - BaudRate = 9600 baud  
	   - Word Length = 8 Bits
	   - One Stop Bit
	   - Even parity
	   - Hardware flow control disabled (RTS and CTS signals)
	   - Receive and transmit enabled
	*/
	BSP_UARTx_HANDLER.gState = HAL_UART_STATE_RESET;            // 初始化
	BSP_UARTx_HANDLER.Instance = BSP_UARTx;                     // 串口
	BSP_UARTx_HANDLER.Init.BaudRate = BSP_UARTx_BAUD_RATE;      // 波特率:9600
	BSP_UARTx_HANDLER.Init.WordLength = UART_WORDLENGTH_8B;     // 数据长度:8位
	BSP_UARTx_HANDLER.Init.StopBits = UART_STOPBITS_1;          // 停止位:1位
	BSP_UARTx_HANDLER.Init.Parity = UART_PARITY_NONE;           // 奇偶校验:无
	BSP_UARTx_HANDLER.Init.Mode = UART_MODE_TX_RX;              // 发送及接收使能(后面会关闭发送中断)
	BSP_UARTx_HANDLER.Init.HwFlowCtl = UART_HWCONTROL_NONE;     // 流控制:无
	BSP_UARTx_HANDLER.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&BSP_UARTx_HANDLER) != HAL_OK) {}
	
	__HAL_UART_DISABLE_IT(&BSP_UARTx_HANDLER, UART_IT_TXE);     // 关发送中断 ★★★★★★★★
	__HAL_UART_ENABLE_IT(&BSP_UARTx_HANDLER, UART_IT_RXNE);     // 开接收中断
	
	#undef BSP_UARTx
	#undef BSP_UARTx_CLK_ENABLE
	#undef BSP_UARTx_TX_CLK_ENABLE
	#undef BSP_UARTx_RX_CLK_ENABLE
	#undef BSP_UARTx_IRQn
	#undef BSP_UARTx_BAUD_RATE
	#undef BSP_UARTx_PRE_INT_PRIO
	#undef BSP_UARTx_SUB_INT_PRIO
	#undef BSP_UARTx_TX_GPIO
	#undef BSP_UARTx_TX_PIN
	#undef BSP_UARTx_RX_GPIO
	#undef BSP_UARTx_RX_PIN
	#undef BSP_UARTx_RX_IN_MODE
	#ifdef BSP_UARTx_AFIO_REMAP
	#undef BSP_UARTx_AFIO_REMAP
	#endif
	#undef BSP_UARTx_HANDLER
}
XT_CHIP_INIT_5_TAB_EXPORT(bsp_usart3_init, "bsp_usart3_init()");
#endif  //#if (BSP_USART3_EN & 0x01)

/**
  * @brief  串口4初始化
  * @param  void
  * @return void
  */
#if (BSP_UART4_EN & 0x01)
void bsp_uart4_init(void)
{
	#define BSP_UARTx                   BSP_UART4                       /* 使用的哪个串口               */
	#define BSP_UARTx_BAUD_RATE         BSP_UART4_BAUD_RATE             /* 通讯波特率: 9600bps          */
	#define BSP_UARTx_CLK_ENABLE()      BSP_UART4_CLK_ENABLE()          /* 串口时钟使能                 */
	#define BSP_UARTx_TX_CLK_ENABLE()   BSP_UART4_TX_CLK_ENABLE()       /* TX脚时钟使能                 */
	#define BSP_UARTx_RX_CLK_ENABLE()   BSP_UART4_RX_CLK_ENABLE()       /* RX脚时钟使能                 */
	#define BSP_UARTx_IRQn              BSP_UART4_IRQn                  /* 中断通道                     */
	#define BSP_UARTx_PRE_INT_PRIO      BSP_UART4_PRE_INT_PRIO          /* 抢占中断优先级               */
	#define BSP_UARTx_SUB_INT_PRIO      BSP_UART4_SUB_INT_PRIO          /* 响应中断优先级               */
	#define BSP_UARTx_TX_GPIO           BSP_UART4_TX_GPIO               /* TX 所在端口                  */
	#define BSP_UARTx_TX_PIN            BSP_UART4_TX_PIN                /* TX 所在管脚                  */
	#define BSP_UARTx_RX_GPIO           BSP_UART4_RX_GPIO               /* RX 所在端口                  */
	#define BSP_UARTx_RX_PIN            BSP_UART4_RX_PIN                /* RX 所在管脚                  */
	#define BSP_UARTx_RX_IN_MODE        BSP_UART4_RX_IN_MODE            /* RX 输入模式(上拉/悬空)       */
	#ifdef                              BSP_UART4_AFIO_REMAP
	#define BSP_UARTx_AFIO_REMAP()      BSP_UART4_AFIO_REMAP()          /* 串口引脚重映射(不使用则屏蔽) */
	#endif
	#ifdef                              BSP_UART4_HANDLER
	#define BSP_UARTx_HANDLER           BSP_UART4_HANDLER               /* 串口句柄(不使用全局句柄则屏蔽*/
	#endif
	
	GPIO_InitTypeDef GPIO_Initure;
	#ifndef BSP_UARTx_HANDLER
	#define BSP_UARTx_HANDLER UARTx_Handler
	UART_HandleTypeDef BSP_UARTx_HANDLER;      //串口句柄（HAL库标准用法则要求为全局变量）
	#endif
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > [时钟-引脚-优先级]初始化的HAL库内部实现写法为：
	// > `HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)`
	// >> `if (huart->gState == HAL_UART_STATE_RESET)`
	// >> `HAL_UART_MspInit(huart);`           //回调用户提供的回调函数(1.使能时钟, 2.设置引脚和中断优先级)
	BSP_UARTx_TX_CLK_ENABLE();
	BSP_UARTx_RX_CLK_ENABLE();
	BSP_UARTx_CLK_ENABLE();
	
	GPIO_Initure.Pin   = BSP_UARTx_TX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_AF_PP;      //复用推挽输出
	GPIO_Initure.Pull  = GPIO_PULLUP;          //上拉
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //高速
	HAL_GPIO_Init(BSP_UARTx_TX_GPIO, &GPIO_Initure);
	
	GPIO_Initure.Pin   = BSP_UARTx_RX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_INPUT;      //输入模式
	GPIO_Initure.Pull  = BSP_UARTx_RX_IN_MODE; //上拉/悬空
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //高速
	HAL_GPIO_Init(BSP_UARTx_RX_GPIO, &GPIO_Initure);
	
	#ifdef BSP_UARTx_AFIO_REMAP
	BSP_UARTx_AFIO_REMAP();
	#endif
	
	HAL_NVIC_SetPriority(BSP_UARTx_IRQn, BSP_UARTx_PRE_INT_PRIO, BSP_UARTx_SUB_INT_PRIO);
	HAL_NVIC_EnableIRQ(BSP_UARTx_IRQn);
	
	/* USARTx and USARTx configuration  */
	/* USART and USARTx configured as follow:
	   - BaudRate = 9600 baud  
	   - Word Length = 8 Bits
	   - One Stop Bit
	   - Even parity
	   - Hardware flow control disabled (RTS and CTS signals)
	   - Receive and transmit enabled
	*/
	BSP_UARTx_HANDLER.gState = HAL_UART_STATE_RESET;            // 初始化
	BSP_UARTx_HANDLER.Instance = BSP_UARTx;                     // 串口
	BSP_UARTx_HANDLER.Init.BaudRate = BSP_UARTx_BAUD_RATE;      // 波特率:9600
	BSP_UARTx_HANDLER.Init.WordLength = UART_WORDLENGTH_8B;     // 数据长度:8位
	BSP_UARTx_HANDLER.Init.StopBits = UART_STOPBITS_1;          // 停止位:1位
	BSP_UARTx_HANDLER.Init.Parity = UART_PARITY_NONE;           // 奇偶校验:无
	BSP_UARTx_HANDLER.Init.Mode = UART_MODE_TX_RX;              // 发送及接收使能(后面会关闭发送中断)
	BSP_UARTx_HANDLER.Init.HwFlowCtl = UART_HWCONTROL_NONE;     // 流控制:无
	BSP_UARTx_HANDLER.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&BSP_UARTx_HANDLER) != HAL_OK) {}
	
	__HAL_UART_DISABLE_IT(&BSP_UARTx_HANDLER, UART_IT_TXE);     // 关发送中断 ★★★★★★★★
	__HAL_UART_ENABLE_IT(&BSP_UARTx_HANDLER, UART_IT_RXNE);     // 开接收中断
	
	#undef BSP_UARTx
	#undef BSP_UARTx_CLK_ENABLE
	#undef BSP_UARTx_TX_CLK_ENABLE
	#undef BSP_UARTx_RX_CLK_ENABLE
	#undef BSP_UARTx_IRQn
	#undef BSP_UARTx_BAUD_RATE
	#undef BSP_UARTx_PRE_INT_PRIO
	#undef BSP_UARTx_SUB_INT_PRIO
	#undef BSP_UARTx_TX_GPIO
	#undef BSP_UARTx_TX_PIN
	#undef BSP_UARTx_RX_GPIO
	#undef BSP_UARTx_RX_PIN
	#undef BSP_UARTx_RX_IN_MODE
	#ifdef BSP_UARTx_AFIO_REMAP
	#undef BSP_UARTx_AFIO_REMAP
	#endif
	#undef BSP_UARTx_HANDLER
}
XT_CHIP_INIT_5_TAB_EXPORT(bsp_uart4_init, "bsp_uart4_init()");
#endif  //#if (BSP_UART4_EN & 0x01)

/**
  * @brief  串口5初始化
  * @param  void
  * @return void
  */
#if (BSP_UART5_EN & 0x01)
void bsp_uart5_init(void)
{
	#define BSP_UARTx                   BSP_UART5                       /* 使用的哪个串口               */
	#define BSP_UARTx_BAUD_RATE         BSP_UART5_BAUD_RATE             /* 通讯波特率: 9600bps          */
	#define BSP_UARTx_CLK_ENABLE()      BSP_UART5_CLK_ENABLE()          /* 串口时钟使能                 */
	#define BSP_UARTx_TX_CLK_ENABLE()   BSP_UART5_TX_CLK_ENABLE()       /* TX脚时钟使能                 */
	#define BSP_UARTx_RX_CLK_ENABLE()   BSP_UART5_RX_CLK_ENABLE()       /* RX脚时钟使能                 */
	#define BSP_UARTx_IRQn              BSP_UART5_IRQn                  /* 中断通道                     */
	#define BSP_UARTx_PRE_INT_PRIO      BSP_UART5_PRE_INT_PRIO          /* 抢占中断优先级               */
	#define BSP_UARTx_SUB_INT_PRIO      BSP_UART5_SUB_INT_PRIO          /* 响应中断优先级               */
	#define BSP_UARTx_TX_GPIO           BSP_UART5_TX_GPIO               /* TX 所在端口                  */
	#define BSP_UARTx_TX_PIN            BSP_UART5_TX_PIN                /* TX 所在管脚                  */
	#define BSP_UARTx_RX_GPIO           BSP_UART5_RX_GPIO               /* RX 所在端口                  */
	#define BSP_UARTx_RX_PIN            BSP_UART5_RX_PIN                /* RX 所在管脚                  */
	#define BSP_UARTx_RX_IN_MODE        BSP_UART5_RX_IN_MODE            /* RX 输入模式(上拉/悬空)       */
	#ifdef                              BSP_UART5_AFIO_REMAP
	#define BSP_UARTx_AFIO_REMAP()      BSP_UART5_AFIO_REMAP()          /* 串口引脚重映射(不使用则屏蔽) */
	#endif
	#ifdef                              BSP_UART5_HANDLER
	#define BSP_UARTx_HANDLER           BSP_UART5_HANDLER               /* 串口句柄(不使用全局句柄则屏蔽*/
	#endif
	
	GPIO_InitTypeDef GPIO_Initure;
	#ifndef BSP_UARTx_HANDLER
	#define BSP_UARTx_HANDLER UARTx_Handler
	UART_HandleTypeDef BSP_UARTx_HANDLER;      //串口句柄（HAL库标准用法则要求为全局变量）
	#endif
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > [时钟-引脚-优先级]初始化的HAL库内部实现写法为：
	// > `HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)`
	// >> `if (huart->gState == HAL_UART_STATE_RESET)`
	// >> `HAL_UART_MspInit(huart);`           //回调用户提供的回调函数(1.使能时钟, 2.设置引脚和中断优先级)
	BSP_UARTx_TX_CLK_ENABLE();
	BSP_UARTx_RX_CLK_ENABLE();
	BSP_UARTx_CLK_ENABLE();
	
	GPIO_Initure.Pin   = BSP_UARTx_TX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_AF_PP;      //复用推挽输出
	GPIO_Initure.Pull  = GPIO_PULLUP;          //上拉
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //高速
	HAL_GPIO_Init(BSP_UARTx_TX_GPIO, &GPIO_Initure);
	
	GPIO_Initure.Pin   = BSP_UARTx_RX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_INPUT;      //输入模式
	GPIO_Initure.Pull  = BSP_UARTx_RX_IN_MODE; //上拉/悬空
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //高速
	HAL_GPIO_Init(BSP_UARTx_RX_GPIO, &GPIO_Initure);
	
	#ifdef BSP_UARTx_AFIO_REMAP
	BSP_UARTx_AFIO_REMAP();
	#endif
	
	HAL_NVIC_SetPriority(BSP_UARTx_IRQn, BSP_UARTx_PRE_INT_PRIO, BSP_UARTx_SUB_INT_PRIO);
	HAL_NVIC_EnableIRQ(BSP_UARTx_IRQn);
	
	/* USARTx and USARTx configuration  */
	/* USART and USARTx configured as follow:
	   - BaudRate = 9600 baud  
	   - Word Length = 8 Bits
	   - One Stop Bit
	   - Even parity
	   - Hardware flow control disabled (RTS and CTS signals)
	   - Receive and transmit enabled
	*/
	BSP_UARTx_HANDLER.gState = HAL_UART_STATE_RESET;            // 初始化
	BSP_UARTx_HANDLER.Instance = BSP_UARTx;                     // 串口
	BSP_UARTx_HANDLER.Init.BaudRate = BSP_UARTx_BAUD_RATE;      // 波特率:9600
	BSP_UARTx_HANDLER.Init.WordLength = UART_WORDLENGTH_8B;     // 数据长度:8位
	BSP_UARTx_HANDLER.Init.StopBits = UART_STOPBITS_1;          // 停止位:1位
	BSP_UARTx_HANDLER.Init.Parity = UART_PARITY_NONE;           // 奇偶校验:无
	BSP_UARTx_HANDLER.Init.Mode = UART_MODE_TX_RX;              // 发送及接收使能(后面会关闭发送中断)
	BSP_UARTx_HANDLER.Init.HwFlowCtl = UART_HWCONTROL_NONE;     // 流控制:无
	BSP_UARTx_HANDLER.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&BSP_UARTx_HANDLER) != HAL_OK) {}
	
	__HAL_UART_DISABLE_IT(&BSP_UARTx_HANDLER, UART_IT_TXE);     // 关发送中断 ★★★★★★★★
	__HAL_UART_ENABLE_IT(&BSP_UARTx_HANDLER, UART_IT_RXNE);     // 开接收中断
	
	#undef BSP_UARTx
	#undef BSP_UARTx_CLK_ENABLE
	#undef BSP_UARTx_TX_CLK_ENABLE
	#undef BSP_UARTx_RX_CLK_ENABLE
	#undef BSP_UARTx_IRQn
	#undef BSP_UARTx_BAUD_RATE
	#undef BSP_UARTx_PRE_INT_PRIO
	#undef BSP_UARTx_SUB_INT_PRIO
	#undef BSP_UARTx_TX_GPIO
	#undef BSP_UARTx_TX_PIN
	#undef BSP_UARTx_RX_GPIO
	#undef BSP_UARTx_RX_PIN
	#undef BSP_UARTx_RX_IN_MODE
	#ifdef BSP_UARTx_AFIO_REMAP
	#undef BSP_UARTx_AFIO_REMAP
	#endif
	#undef BSP_UARTx_HANDLER
}
XT_CHIP_INIT_5_TAB_EXPORT(bsp_uart5_init, "bsp_uart5_init()");
#endif  //#if (BSP_UART5_EN & 0x01)

#if 0
/**
  * @brief  串口2中断
  * @param  void
  * @return void
  */
#if (BSP_USART2_EN & 0x10)
void USART2_IRQHandler(void)
{
	struct { USART_TypeDef *Instance; } huart = { USART2 };
	
	/* enter interrupt */
	rt_interrupt_enter();
	
	//接收数据--------------------------------------------------------------------------------------------
	// > HAL库内部实现写法为：
	// > `void USART2_IRQHandler(void)`                                                //中断向量函数
	// >> `void HAL_UART_IRQHandler(UART_HandleTypeDef *huart)`                        //中断事件服务函数
	// >>> `if (((isrflags & USART_SR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))`
	// >>> `UART_Receive_IT(huart);`                                                   //接收函数
	// >>>> `*huart->pRxBuffPtr++ = (uint8_t)(huart->Instance->DR & (uint8_t)0x00FF);` //接收数据
	if (((USART2->SR & USART_SR_RXNE) != RESET) 
	&&  ((USART2->CR1 & USART_CR1_RXNEIE) != RESET))
	{
		unsigned short usBuf = USART2->DR & 0x01FF; //对DR的读操作可将RXNE位清零
		if ((usBuf & 0x0100) == 0){} else{}
		//.......................................
	}
	
	//发送数据--------------------------------------------------------------------------------------------
	// > HAL库内部实现写法为：
	// > `void USART2_IRQHandler(void)`                                                //中断向量函数
	// >> `void HAL_UART_IRQHandler(UART_HandleTypeDef *huart)`                        //中断事件服务函数
	// >>> `if (((isrflags & USART_SR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))`  //空中断
	// >>> `UART_Transmit_IT(huart);`                                                  //发送函数
	// >>>> `huart->Instance->DR = (uint8_t)(*huart->pTxBuffPtr++ & (uint8_t)0x00FF);` //发送数据
	if (((USART2->SR & USART_SR_TXE) != RESET)
	&&  ((USART2->CR1 & USART_CR1_TXEIE) != RESET))
	{
		static unsigned short usTxCnt = 10;
		USART2->DR = usTxCnt;                   //对DR的写操作可将空中断标志清零
		if (--usTxCnt == 0)
		{
			__HAL_UART_DISABLE_IT(&huart, UART_IT_TXE);
			__HAL_UART_ENABLE_IT(&huart, UART_IT_TC);
		}
	}
	// > HAL库内部实现写法为：
	// > `void USART2_IRQHandler(void)`                                                //中断向量函数
	// >> `void HAL_UART_IRQHandler(UART_HandleTypeDef *huart)`                        //中断事件服务函数
	// >>> `if (((isrflags & USART_SR_TC) != RESET) && ((cr1its & USART_CR1_TCIE) != RESET))`  //完成中断
	// >>> `UART_EndTransmit_IT(huart);`                                               //发送完成函数
	// >>>> `__HAL_UART_DISABLE_IT(huart, UART_IT_TC);`                                //关闭完成中断
	if (((USART2->SR & USART_SR_TC) != RESET)
	&&  ((USART2->CR1 & USART_CR1_TCIE) != RESET))
	{
		__HAL_UART_DISABLE_IT(&huart, UART_IT_TC);
		__HAL_UART_CLEAR_FLAG(&huart, UART_FLAG_TC);
	}
	
	//接收溢出--------------------------------------------------------------------------------------------
	if ((USART2->SR & USART_SR_ORE) != RESET)
	{
		if (USART2->SR & USART_SR_ORE){} else{} //读SR其实就是清除标志
		if (USART2->DR & 0x01FF)      {} else{} //读DR
	}
	
	/* leave interrupt */
	rt_interrupt_leave();
}
#endif

#endif  //#if 0
