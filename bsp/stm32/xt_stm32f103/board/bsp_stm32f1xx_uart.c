/**
  * @file  bsp_stm32f1xx_uart.c
  * @brief ȫ�ִ�����������
  * @notice ������ֻ��Ϊ��ʼ���ο����룬��Ϊ����һ��ר����ĳ��Ӧ��ģ��
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    ԭʼ�汾
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
  * @brief  ����1��ʼ��
  * @param  void
  * @return void
  */
#if (BSP_USART1_EN & 0x01)
void bsp_usart1_init(void)
{
	#define BSP_UARTx                   BSP_UART1                       /* ʹ�õ��ĸ�����               */
	#define BSP_UARTx_BAUD_RATE         BSP_UART1_BAUD_RATE             /* ͨѶ������: 9600bps          */
	#define BSP_UARTx_CLK_ENABLE()      BSP_UART1_CLK_ENABLE()          /* ����ʱ��ʹ��                 */
	#define BSP_UARTx_TX_CLK_ENABLE()   BSP_UART1_TX_CLK_ENABLE()       /* TX��ʱ��ʹ��                 */
	#define BSP_UARTx_RX_CLK_ENABLE()   BSP_UART1_RX_CLK_ENABLE()       /* RX��ʱ��ʹ��                 */
	#define BSP_UARTx_IRQn              BSP_UART1_IRQn                  /* �ж�ͨ��                     */
	#define BSP_UARTx_PRE_INT_PRIO      BSP_UART1_PRE_INT_PRIO          /* ��ռ�ж����ȼ�               */
	#define BSP_UARTx_SUB_INT_PRIO      BSP_UART1_SUB_INT_PRIO          /* ��Ӧ�ж����ȼ�               */
	#define BSP_UARTx_TX_GPIO           BSP_UART1_TX_GPIO               /* TX ���ڶ˿�                  */
	#define BSP_UARTx_TX_PIN            BSP_UART1_TX_PIN                /* TX ���ڹܽ�                  */
	#define BSP_UARTx_RX_GPIO           BSP_UART1_RX_GPIO               /* RX ���ڶ˿�                  */
	#define BSP_UARTx_RX_PIN            BSP_UART1_RX_PIN                /* RX ���ڹܽ�                  */
	#define BSP_UARTx_RX_IN_MODE        BSP_UART1_RX_IN_MODE            /* RX ����ģʽ(����/����)       */
	#ifdef                              BSP_UART1_AFIO_REMAP
	#define BSP_UARTx_AFIO_REMAP()      BSP_UART1_AFIO_REMAP()          /* ����������ӳ��(��ʹ��������) */
	#endif
	#ifdef                              BSP_UART1_HANDLER
	#define BSP_UARTx_HANDLER           BSP_UART1_HANDLER               /* ���ھ��(��ʹ��ȫ�־��������*/
	#endif
	
	GPIO_InitTypeDef GPIO_Initure;
	#ifndef BSP_UARTx_HANDLER
	#define BSP_UARTx_HANDLER UARTx_Handler
	UART_HandleTypeDef BSP_UARTx_HANDLER;      //���ھ����HAL���׼�÷���Ҫ��Ϊȫ�ֱ�����
	#endif
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > [ʱ��-����-���ȼ�]��ʼ����HAL���ڲ�ʵ��д��Ϊ��
	// > `HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)`
	// >> `if (huart->gState == HAL_UART_STATE_RESET)`
	// >> `HAL_UART_MspInit(huart);`           //�ص��û��ṩ�Ļص�����(1.ʹ��ʱ��, 2.�������ź��ж����ȼ�)
	BSP_UARTx_TX_CLK_ENABLE();
	BSP_UARTx_RX_CLK_ENABLE();
	BSP_UARTx_CLK_ENABLE();
	
	GPIO_Initure.Pin   = BSP_UARTx_TX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_AF_PP;      //�����������
	GPIO_Initure.Pull  = GPIO_PULLUP;          //����
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //����
	HAL_GPIO_Init(BSP_UARTx_TX_GPIO, &GPIO_Initure);
	
	GPIO_Initure.Pin   = BSP_UARTx_RX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_INPUT;      //����ģʽ
	GPIO_Initure.Pull  = BSP_UARTx_RX_IN_MODE; //����/����
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //����
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
	BSP_UARTx_HANDLER.gState = HAL_UART_STATE_RESET;            // ��ʼ��
	BSP_UARTx_HANDLER.Instance = BSP_UARTx;                     // ����
	BSP_UARTx_HANDLER.Init.BaudRate = BSP_UARTx_BAUD_RATE;      // ������:9600
	BSP_UARTx_HANDLER.Init.WordLength = UART_WORDLENGTH_8B;     // ���ݳ���:8λ
	BSP_UARTx_HANDLER.Init.StopBits = UART_STOPBITS_1;          // ֹͣλ:1λ
	BSP_UARTx_HANDLER.Init.Parity = UART_PARITY_NONE;           // ��żУ��:��
	BSP_UARTx_HANDLER.Init.Mode = UART_MODE_TX_RX;              // ���ͼ�����ʹ��(�����رշ����ж�)
	BSP_UARTx_HANDLER.Init.HwFlowCtl = UART_HWCONTROL_NONE;     // ������:��
	BSP_UARTx_HANDLER.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&BSP_UARTx_HANDLER) != HAL_OK) {}
	
	__HAL_UART_DISABLE_IT(&BSP_UARTx_HANDLER, UART_IT_TXE);     // �ط����ж� ���������
	__HAL_UART_ENABLE_IT(&BSP_UARTx_HANDLER, UART_IT_RXNE);     // �������ж�
	
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
  * @brief  ����2��ʼ��
  * @param  void
  * @return void
  */
#if (BSP_USART2_EN & 0x01)
void bsp_usart2_init(void)
{
	#define BSP_UARTx                   BSP_UART2                       /* ʹ�õ��ĸ�����               */
	#define BSP_UARTx_BAUD_RATE         BSP_UART2_BAUD_RATE             /* ͨѶ������: 9600bps          */
	#define BSP_UARTx_CLK_ENABLE()      BSP_UART2_CLK_ENABLE()          /* ����ʱ��ʹ��                 */
	#define BSP_UARTx_TX_CLK_ENABLE()   BSP_UART2_TX_CLK_ENABLE()       /* TX��ʱ��ʹ��                 */
	#define BSP_UARTx_RX_CLK_ENABLE()   BSP_UART2_RX_CLK_ENABLE()       /* RX��ʱ��ʹ��                 */
	#define BSP_UARTx_IRQn              BSP_UART2_IRQn                  /* �ж�ͨ��                     */
	#define BSP_UARTx_PRE_INT_PRIO      BSP_UART2_PRE_INT_PRIO          /* ��ռ�ж����ȼ�               */
	#define BSP_UARTx_SUB_INT_PRIO      BSP_UART2_SUB_INT_PRIO          /* ��Ӧ�ж����ȼ�               */
	#define BSP_UARTx_TX_GPIO           BSP_UART2_TX_GPIO               /* TX ���ڶ˿�                  */
	#define BSP_UARTx_TX_PIN            BSP_UART2_TX_PIN                /* TX ���ڹܽ�                  */
	#define BSP_UARTx_RX_GPIO           BSP_UART2_RX_GPIO               /* RX ���ڶ˿�                  */
	#define BSP_UARTx_RX_PIN            BSP_UART2_RX_PIN                /* RX ���ڹܽ�                  */
	#define BSP_UARTx_RX_IN_MODE        BSP_UART2_RX_IN_MODE            /* RX ����ģʽ(����/����)       */
	#ifdef                              BSP_UART2_AFIO_REMAP
	#define BSP_UARTx_AFIO_REMAP()      BSP_UART2_AFIO_REMAP()          /* ����������ӳ��(��ʹ��������) */
	#endif
	#ifdef                              BSP_UART2_HANDLER
	#define BSP_UARTx_HANDLER           BSP_UART2_HANDLER               /* ���ھ��(��ʹ��ȫ�־��������*/
	#endif
	
	GPIO_InitTypeDef GPIO_Initure;
	#ifndef BSP_UARTx_HANDLER
	#define BSP_UARTx_HANDLER UARTx_Handler
	UART_HandleTypeDef BSP_UARTx_HANDLER;      //���ھ����HAL���׼�÷���Ҫ��Ϊȫ�ֱ�����
	#endif
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > [ʱ��-����-���ȼ�]��ʼ����HAL���ڲ�ʵ��д��Ϊ��
	// > `HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)`
	// >> `if (huart->gState == HAL_UART_STATE_RESET)`
	// >> `HAL_UART_MspInit(huart);`           //�ص��û��ṩ�Ļص�����(1.ʹ��ʱ��, 2.�������ź��ж����ȼ�)
	BSP_UARTx_TX_CLK_ENABLE();
	BSP_UARTx_RX_CLK_ENABLE();
	BSP_UARTx_CLK_ENABLE();
	
	GPIO_Initure.Pin   = BSP_UARTx_TX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_AF_PP;      //�����������
	GPIO_Initure.Pull  = GPIO_PULLUP;          //����
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //����
	HAL_GPIO_Init(BSP_UARTx_TX_GPIO, &GPIO_Initure);
	
	GPIO_Initure.Pin   = BSP_UARTx_RX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_INPUT;      //����ģʽ
	GPIO_Initure.Pull  = BSP_UARTx_RX_IN_MODE; //����/����
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //����
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
	BSP_UARTx_HANDLER.gState = HAL_UART_STATE_RESET;            // ��ʼ��
	BSP_UARTx_HANDLER.Instance = BSP_UARTx;                     // ����
	BSP_UARTx_HANDLER.Init.BaudRate = BSP_UARTx_BAUD_RATE;      // ������:9600
	BSP_UARTx_HANDLER.Init.WordLength = UART_WORDLENGTH_8B;     // ���ݳ���:8λ
	BSP_UARTx_HANDLER.Init.StopBits = UART_STOPBITS_1;          // ֹͣλ:1λ
	BSP_UARTx_HANDLER.Init.Parity = UART_PARITY_NONE;           // ��żУ��:��
	BSP_UARTx_HANDLER.Init.Mode = UART_MODE_TX_RX;              // ���ͼ�����ʹ��(�����رշ����ж�)
	BSP_UARTx_HANDLER.Init.HwFlowCtl = UART_HWCONTROL_NONE;     // ������:��
	BSP_UARTx_HANDLER.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&BSP_UARTx_HANDLER) != HAL_OK) {}
	
	__HAL_UART_DISABLE_IT(&BSP_UARTx_HANDLER, UART_IT_TXE);     // �ط����ж� ���������
	__HAL_UART_ENABLE_IT(&BSP_UARTx_HANDLER, UART_IT_RXNE);     // �������ж�
	
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
  * @brief  ����3��ʼ��
  * @param  void
  * @return void
  */
#if (BSP_USART3_EN & 0x01)
void bsp_usart3_init(void)
{
	#define BSP_UARTx                   BSP_UART3                       /* ʹ�õ��ĸ�����               */
	#define BSP_UARTx_BAUD_RATE         BSP_UART3_BAUD_RATE             /* ͨѶ������: 9600bps          */
	#define BSP_UARTx_CLK_ENABLE()      BSP_UART3_CLK_ENABLE()          /* ����ʱ��ʹ��                 */
	#define BSP_UARTx_TX_CLK_ENABLE()   BSP_UART3_TX_CLK_ENABLE()       /* TX��ʱ��ʹ��                 */
	#define BSP_UARTx_RX_CLK_ENABLE()   BSP_UART3_RX_CLK_ENABLE()       /* RX��ʱ��ʹ��                 */
	#define BSP_UARTx_IRQn              BSP_UART3_IRQn                  /* �ж�ͨ��                     */
	#define BSP_UARTx_PRE_INT_PRIO      BSP_UART3_PRE_INT_PRIO          /* ��ռ�ж����ȼ�               */
	#define BSP_UARTx_SUB_INT_PRIO      BSP_UART3_SUB_INT_PRIO          /* ��Ӧ�ж����ȼ�               */
	#define BSP_UARTx_TX_GPIO           BSP_UART3_TX_GPIO               /* TX ���ڶ˿�                  */
	#define BSP_UARTx_TX_PIN            BSP_UART3_TX_PIN                /* TX ���ڹܽ�                  */
	#define BSP_UARTx_RX_GPIO           BSP_UART3_RX_GPIO               /* RX ���ڶ˿�                  */
	#define BSP_UARTx_RX_PIN            BSP_UART3_RX_PIN                /* RX ���ڹܽ�                  */
	#define BSP_UARTx_RX_IN_MODE        BSP_UART3_RX_IN_MODE            /* RX ����ģʽ(����/����)       */
	#ifdef                              BSP_UART3_AFIO_REMAP
	#define BSP_UARTx_AFIO_REMAP()      BSP_UART3_AFIO_REMAP()          /* ����������ӳ��(��ʹ��������) */
	#endif
	#ifdef                              BSP_UART3_HANDLER
	#define BSP_UARTx_HANDLER           BSP_UART3_HANDLER               /* ���ھ��(��ʹ��ȫ�־��������*/
	#endif
	
	GPIO_InitTypeDef GPIO_Initure;
	#ifndef BSP_UARTx_HANDLER
	#define BSP_UARTx_HANDLER UARTx_Handler
	UART_HandleTypeDef BSP_UARTx_HANDLER;      //���ھ����HAL���׼�÷���Ҫ��Ϊȫ�ֱ�����
	#endif
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > [ʱ��-����-���ȼ�]��ʼ����HAL���ڲ�ʵ��д��Ϊ��
	// > `HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)`
	// >> `if (huart->gState == HAL_UART_STATE_RESET)`
	// >> `HAL_UART_MspInit(huart);`           //�ص��û��ṩ�Ļص�����(1.ʹ��ʱ��, 2.�������ź��ж����ȼ�)
	BSP_UARTx_TX_CLK_ENABLE();
	BSP_UARTx_RX_CLK_ENABLE();
	BSP_UARTx_CLK_ENABLE();
	
	GPIO_Initure.Pin   = BSP_UARTx_TX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_AF_PP;      //�����������
	GPIO_Initure.Pull  = GPIO_PULLUP;          //����
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //����
	HAL_GPIO_Init(BSP_UARTx_TX_GPIO, &GPIO_Initure);
	
	GPIO_Initure.Pin   = BSP_UARTx_RX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_INPUT;      //����ģʽ
	GPIO_Initure.Pull  = BSP_UARTx_RX_IN_MODE; //����/����
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //����
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
	BSP_UARTx_HANDLER.gState = HAL_UART_STATE_RESET;            // ��ʼ��
	BSP_UARTx_HANDLER.Instance = BSP_UARTx;                     // ����
	BSP_UARTx_HANDLER.Init.BaudRate = BSP_UARTx_BAUD_RATE;      // ������:9600
	BSP_UARTx_HANDLER.Init.WordLength = UART_WORDLENGTH_8B;     // ���ݳ���:8λ
	BSP_UARTx_HANDLER.Init.StopBits = UART_STOPBITS_1;          // ֹͣλ:1λ
	BSP_UARTx_HANDLER.Init.Parity = UART_PARITY_NONE;           // ��żУ��:��
	BSP_UARTx_HANDLER.Init.Mode = UART_MODE_TX_RX;              // ���ͼ�����ʹ��(�����رշ����ж�)
	BSP_UARTx_HANDLER.Init.HwFlowCtl = UART_HWCONTROL_NONE;     // ������:��
	BSP_UARTx_HANDLER.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&BSP_UARTx_HANDLER) != HAL_OK) {}
	
	__HAL_UART_DISABLE_IT(&BSP_UARTx_HANDLER, UART_IT_TXE);     // �ط����ж� ���������
	__HAL_UART_ENABLE_IT(&BSP_UARTx_HANDLER, UART_IT_RXNE);     // �������ж�
	
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
  * @brief  ����4��ʼ��
  * @param  void
  * @return void
  */
#if (BSP_UART4_EN & 0x01)
void bsp_uart4_init(void)
{
	#define BSP_UARTx                   BSP_UART4                       /* ʹ�õ��ĸ�����               */
	#define BSP_UARTx_BAUD_RATE         BSP_UART4_BAUD_RATE             /* ͨѶ������: 9600bps          */
	#define BSP_UARTx_CLK_ENABLE()      BSP_UART4_CLK_ENABLE()          /* ����ʱ��ʹ��                 */
	#define BSP_UARTx_TX_CLK_ENABLE()   BSP_UART4_TX_CLK_ENABLE()       /* TX��ʱ��ʹ��                 */
	#define BSP_UARTx_RX_CLK_ENABLE()   BSP_UART4_RX_CLK_ENABLE()       /* RX��ʱ��ʹ��                 */
	#define BSP_UARTx_IRQn              BSP_UART4_IRQn                  /* �ж�ͨ��                     */
	#define BSP_UARTx_PRE_INT_PRIO      BSP_UART4_PRE_INT_PRIO          /* ��ռ�ж����ȼ�               */
	#define BSP_UARTx_SUB_INT_PRIO      BSP_UART4_SUB_INT_PRIO          /* ��Ӧ�ж����ȼ�               */
	#define BSP_UARTx_TX_GPIO           BSP_UART4_TX_GPIO               /* TX ���ڶ˿�                  */
	#define BSP_UARTx_TX_PIN            BSP_UART4_TX_PIN                /* TX ���ڹܽ�                  */
	#define BSP_UARTx_RX_GPIO           BSP_UART4_RX_GPIO               /* RX ���ڶ˿�                  */
	#define BSP_UARTx_RX_PIN            BSP_UART4_RX_PIN                /* RX ���ڹܽ�                  */
	#define BSP_UARTx_RX_IN_MODE        BSP_UART4_RX_IN_MODE            /* RX ����ģʽ(����/����)       */
	#ifdef                              BSP_UART4_AFIO_REMAP
	#define BSP_UARTx_AFIO_REMAP()      BSP_UART4_AFIO_REMAP()          /* ����������ӳ��(��ʹ��������) */
	#endif
	#ifdef                              BSP_UART4_HANDLER
	#define BSP_UARTx_HANDLER           BSP_UART4_HANDLER               /* ���ھ��(��ʹ��ȫ�־��������*/
	#endif
	
	GPIO_InitTypeDef GPIO_Initure;
	#ifndef BSP_UARTx_HANDLER
	#define BSP_UARTx_HANDLER UARTx_Handler
	UART_HandleTypeDef BSP_UARTx_HANDLER;      //���ھ����HAL���׼�÷���Ҫ��Ϊȫ�ֱ�����
	#endif
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > [ʱ��-����-���ȼ�]��ʼ����HAL���ڲ�ʵ��д��Ϊ��
	// > `HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)`
	// >> `if (huart->gState == HAL_UART_STATE_RESET)`
	// >> `HAL_UART_MspInit(huart);`           //�ص��û��ṩ�Ļص�����(1.ʹ��ʱ��, 2.�������ź��ж����ȼ�)
	BSP_UARTx_TX_CLK_ENABLE();
	BSP_UARTx_RX_CLK_ENABLE();
	BSP_UARTx_CLK_ENABLE();
	
	GPIO_Initure.Pin   = BSP_UARTx_TX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_AF_PP;      //�����������
	GPIO_Initure.Pull  = GPIO_PULLUP;          //����
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //����
	HAL_GPIO_Init(BSP_UARTx_TX_GPIO, &GPIO_Initure);
	
	GPIO_Initure.Pin   = BSP_UARTx_RX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_INPUT;      //����ģʽ
	GPIO_Initure.Pull  = BSP_UARTx_RX_IN_MODE; //����/����
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //����
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
	BSP_UARTx_HANDLER.gState = HAL_UART_STATE_RESET;            // ��ʼ��
	BSP_UARTx_HANDLER.Instance = BSP_UARTx;                     // ����
	BSP_UARTx_HANDLER.Init.BaudRate = BSP_UARTx_BAUD_RATE;      // ������:9600
	BSP_UARTx_HANDLER.Init.WordLength = UART_WORDLENGTH_8B;     // ���ݳ���:8λ
	BSP_UARTx_HANDLER.Init.StopBits = UART_STOPBITS_1;          // ֹͣλ:1λ
	BSP_UARTx_HANDLER.Init.Parity = UART_PARITY_NONE;           // ��żУ��:��
	BSP_UARTx_HANDLER.Init.Mode = UART_MODE_TX_RX;              // ���ͼ�����ʹ��(�����رշ����ж�)
	BSP_UARTx_HANDLER.Init.HwFlowCtl = UART_HWCONTROL_NONE;     // ������:��
	BSP_UARTx_HANDLER.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&BSP_UARTx_HANDLER) != HAL_OK) {}
	
	__HAL_UART_DISABLE_IT(&BSP_UARTx_HANDLER, UART_IT_TXE);     // �ط����ж� ���������
	__HAL_UART_ENABLE_IT(&BSP_UARTx_HANDLER, UART_IT_RXNE);     // �������ж�
	
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
  * @brief  ����5��ʼ��
  * @param  void
  * @return void
  */
#if (BSP_UART5_EN & 0x01)
void bsp_uart5_init(void)
{
	#define BSP_UARTx                   BSP_UART5                       /* ʹ�õ��ĸ�����               */
	#define BSP_UARTx_BAUD_RATE         BSP_UART5_BAUD_RATE             /* ͨѶ������: 9600bps          */
	#define BSP_UARTx_CLK_ENABLE()      BSP_UART5_CLK_ENABLE()          /* ����ʱ��ʹ��                 */
	#define BSP_UARTx_TX_CLK_ENABLE()   BSP_UART5_TX_CLK_ENABLE()       /* TX��ʱ��ʹ��                 */
	#define BSP_UARTx_RX_CLK_ENABLE()   BSP_UART5_RX_CLK_ENABLE()       /* RX��ʱ��ʹ��                 */
	#define BSP_UARTx_IRQn              BSP_UART5_IRQn                  /* �ж�ͨ��                     */
	#define BSP_UARTx_PRE_INT_PRIO      BSP_UART5_PRE_INT_PRIO          /* ��ռ�ж����ȼ�               */
	#define BSP_UARTx_SUB_INT_PRIO      BSP_UART5_SUB_INT_PRIO          /* ��Ӧ�ж����ȼ�               */
	#define BSP_UARTx_TX_GPIO           BSP_UART5_TX_GPIO               /* TX ���ڶ˿�                  */
	#define BSP_UARTx_TX_PIN            BSP_UART5_TX_PIN                /* TX ���ڹܽ�                  */
	#define BSP_UARTx_RX_GPIO           BSP_UART5_RX_GPIO               /* RX ���ڶ˿�                  */
	#define BSP_UARTx_RX_PIN            BSP_UART5_RX_PIN                /* RX ���ڹܽ�                  */
	#define BSP_UARTx_RX_IN_MODE        BSP_UART5_RX_IN_MODE            /* RX ����ģʽ(����/����)       */
	#ifdef                              BSP_UART5_AFIO_REMAP
	#define BSP_UARTx_AFIO_REMAP()      BSP_UART5_AFIO_REMAP()          /* ����������ӳ��(��ʹ��������) */
	#endif
	#ifdef                              BSP_UART5_HANDLER
	#define BSP_UARTx_HANDLER           BSP_UART5_HANDLER               /* ���ھ��(��ʹ��ȫ�־��������*/
	#endif
	
	GPIO_InitTypeDef GPIO_Initure;
	#ifndef BSP_UARTx_HANDLER
	#define BSP_UARTx_HANDLER UARTx_Handler
	UART_HandleTypeDef BSP_UARTx_HANDLER;      //���ھ����HAL���׼�÷���Ҫ��Ϊȫ�ֱ�����
	#endif
	
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	// > [ʱ��-����-���ȼ�]��ʼ����HAL���ڲ�ʵ��д��Ϊ��
	// > `HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)`
	// >> `if (huart->gState == HAL_UART_STATE_RESET)`
	// >> `HAL_UART_MspInit(huart);`           //�ص��û��ṩ�Ļص�����(1.ʹ��ʱ��, 2.�������ź��ж����ȼ�)
	BSP_UARTx_TX_CLK_ENABLE();
	BSP_UARTx_RX_CLK_ENABLE();
	BSP_UARTx_CLK_ENABLE();
	
	GPIO_Initure.Pin   = BSP_UARTx_TX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_AF_PP;      //�����������
	GPIO_Initure.Pull  = GPIO_PULLUP;          //����
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //����
	HAL_GPIO_Init(BSP_UARTx_TX_GPIO, &GPIO_Initure);
	
	GPIO_Initure.Pin   = BSP_UARTx_RX_PIN;
	GPIO_Initure.Mode  = GPIO_MODE_INPUT;      //����ģʽ
	GPIO_Initure.Pull  = BSP_UARTx_RX_IN_MODE; //����/����
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //����
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
	BSP_UARTx_HANDLER.gState = HAL_UART_STATE_RESET;            // ��ʼ��
	BSP_UARTx_HANDLER.Instance = BSP_UARTx;                     // ����
	BSP_UARTx_HANDLER.Init.BaudRate = BSP_UARTx_BAUD_RATE;      // ������:9600
	BSP_UARTx_HANDLER.Init.WordLength = UART_WORDLENGTH_8B;     // ���ݳ���:8λ
	BSP_UARTx_HANDLER.Init.StopBits = UART_STOPBITS_1;          // ֹͣλ:1λ
	BSP_UARTx_HANDLER.Init.Parity = UART_PARITY_NONE;           // ��żУ��:��
	BSP_UARTx_HANDLER.Init.Mode = UART_MODE_TX_RX;              // ���ͼ�����ʹ��(�����رշ����ж�)
	BSP_UARTx_HANDLER.Init.HwFlowCtl = UART_HWCONTROL_NONE;     // ������:��
	BSP_UARTx_HANDLER.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&BSP_UARTx_HANDLER) != HAL_OK) {}
	
	__HAL_UART_DISABLE_IT(&BSP_UARTx_HANDLER, UART_IT_TXE);     // �ط����ж� ���������
	__HAL_UART_ENABLE_IT(&BSP_UARTx_HANDLER, UART_IT_RXNE);     // �������ж�
	
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
  * @brief  ����2�ж�
  * @param  void
  * @return void
  */
#if (BSP_USART2_EN & 0x10)
void USART2_IRQHandler(void)
{
	struct { USART_TypeDef *Instance; } huart = { USART2 };
	
	/* enter interrupt */
	rt_interrupt_enter();
	
	//��������--------------------------------------------------------------------------------------------
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void USART2_IRQHandler(void)`                                                //�ж���������
	// >> `void HAL_UART_IRQHandler(UART_HandleTypeDef *huart)`                        //�ж��¼�������
	// >>> `if (((isrflags & USART_SR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))`
	// >>> `UART_Receive_IT(huart);`                                                   //���պ���
	// >>>> `*huart->pRxBuffPtr++ = (uint8_t)(huart->Instance->DR & (uint8_t)0x00FF);` //��������
	if (((USART2->SR & USART_SR_RXNE) != RESET) 
	&&  ((USART2->CR1 & USART_CR1_RXNEIE) != RESET))
	{
		unsigned short usBuf = USART2->DR & 0x01FF; //��DR�Ķ������ɽ�RXNEλ����
		if ((usBuf & 0x0100) == 0){} else{}
		//.......................................
	}
	
	//��������--------------------------------------------------------------------------------------------
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void USART2_IRQHandler(void)`                                                //�ж���������
	// >> `void HAL_UART_IRQHandler(UART_HandleTypeDef *huart)`                        //�ж��¼�������
	// >>> `if (((isrflags & USART_SR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))`  //���ж�
	// >>> `UART_Transmit_IT(huart);`                                                  //���ͺ���
	// >>>> `huart->Instance->DR = (uint8_t)(*huart->pTxBuffPtr++ & (uint8_t)0x00FF);` //��������
	if (((USART2->SR & USART_SR_TXE) != RESET)
	&&  ((USART2->CR1 & USART_CR1_TXEIE) != RESET))
	{
		static unsigned short usTxCnt = 10;
		USART2->DR = usTxCnt;                   //��DR��д�����ɽ����жϱ�־����
		if (--usTxCnt == 0)
		{
			__HAL_UART_DISABLE_IT(&huart, UART_IT_TXE);
			__HAL_UART_ENABLE_IT(&huart, UART_IT_TC);
		}
	}
	// > HAL���ڲ�ʵ��д��Ϊ��
	// > `void USART2_IRQHandler(void)`                                                //�ж���������
	// >> `void HAL_UART_IRQHandler(UART_HandleTypeDef *huart)`                        //�ж��¼�������
	// >>> `if (((isrflags & USART_SR_TC) != RESET) && ((cr1its & USART_CR1_TCIE) != RESET))`  //����ж�
	// >>> `UART_EndTransmit_IT(huart);`                                               //������ɺ���
	// >>>> `__HAL_UART_DISABLE_IT(huart, UART_IT_TC);`                                //�ر�����ж�
	if (((USART2->SR & USART_SR_TC) != RESET)
	&&  ((USART2->CR1 & USART_CR1_TCIE) != RESET))
	{
		__HAL_UART_DISABLE_IT(&huart, UART_IT_TC);
		__HAL_UART_CLEAR_FLAG(&huart, UART_FLAG_TC);
	}
	
	//�������--------------------------------------------------------------------------------------------
	if ((USART2->SR & USART_SR_ORE) != RESET)
	{
		if (USART2->SR & USART_SR_ORE){} else{} //��SR��ʵ���������־
		if (USART2->DR & 0x01FF)      {} else{} //��DR
	}
	
	/* leave interrupt */
	rt_interrupt_leave();
}
#endif

#endif  //#if 0
