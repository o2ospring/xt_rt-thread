/**
  * @file  board.c
  * @brief 所有硬件资源管理
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-15     o2ospring    原始版本
  */
#define   BOARD_C__
#include "board.h"
#ifdef    BOARD_X__   //再次调用头文件,用于增加存在交叉关系的内容!
#undef    BOARD_H__
#include "board.h"
#endif

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	
	/** Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	/**/                        |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

//````````````````````````````````````````````````````````````````````````````````````````````````````````
void bsp_tab_front(void) {}
void bsp_tab_limit(void) {}
XT_CHIP_INIT_S_TAB_EXPORT(bsp_tab_front, " ");
XT_CHIP_INIT_E_TAB_EXPORT(bsp_tab_limit, " ");
XT_HARD_INIT_S_TAB_EXPORT(bsp_tab_front, " ");
XT_HARD_INIT_E_TAB_EXPORT(bsp_tab_limit, " ");
XT_DEV_INIT_S_TAB_EXPORT (bsp_tab_front, " ");
XT_DEV_INIT_E_TAB_EXPORT (bsp_tab_limit, " ");

int bsp_board_init(void)
{
	const xt_init_fn_tab_t *p_tab;
	
	/* disable interrupt */
	__set_PRIMASK(1);
	//__HAL_RCC_AFIO_CLK_ENABLE();
	
	//1、内核上电初始化（如：定时器等）
	for (p_tab=&chip_init_fn_bsp_tab_front+1; p_tab<&chip_init_fn_bsp_tab_limit; p_tab++)
	{
		//rt_kprintf("xt_chip_init: %s\r\n", p_tab->desc);
		(*(p_tab->p_fn))();
	}
	
	//2、硬件上电初始化（如：IC引脚等）
	for (p_tab=&hard_init_fn_bsp_tab_front+1; p_tab<&hard_init_fn_bsp_tab_limit; p_tab++)
	{
		//rt_kprintf("xt_hard_init: %s\r\n", p_tab->desc);
		(*(p_tab->p_fn))();
	}
	
	BSP_DEV_INIT_DELAY(); /////////////////////
	
	//3、器件上电初始化（如：传感器等）
	for (p_tab=&dev_init_fn_bsp_tab_front+1; p_tab<&dev_init_fn_bsp_tab_limit; p_tab++)
	{
		//rt_kprintf("xt_dev_init: %s\r\n", p_tab->desc);
		(*(p_tab->p_fn))();
	}
	
	return 0;
}
INIT_BOARD_EXPORT(bsp_board_init);

//````````````````````````````````````````````````````````````````````````````````````````````````````````
void bsp_delay10us(uint32_t at10us)
{
	uint32_t start, now, delta, reload;
	
	start = SysTick->VAL;
	reload = SysTick->LOAD;
	at10us = (SystemCoreClock / (1000000UL / 10)) * at10us;
	delta = 0;
	do
	{
		now = SysTick->VAL;
		delta += (start >= now ? start - now : reload + start - now);
		start = now;
	}
	while (delta < at10us);
}

void bsp_delay0us5(uint32_t at0us5)
{
	uint32_t start, now, delta, reload;
	
	start = SysTick->VAL;
	reload = SysTick->LOAD;
	at0us5 = (SystemCoreClock / (1000000UL * 2)) * at0us5;
	delta = 0;
	do
	{
		now = SysTick->VAL;
		delta += (start >= now ? start - now : reload + start - now);
		start = now;
	}
	while (delta < at0us5);
}

void bsp_delay0us125(uint32_t at0us125)
{
	uint32_t start, now, delta, reload;
	
	start = SysTick->VAL;
	reload = SysTick->LOAD;
	at0us125 = (SystemCoreClock / (1000000UL * 8)) * at0us125;
	delta = 0;
	do
	{
		now = SysTick->VAL;
		delta += (start >= now ? start - now : reload + start - now);
		start = now;
	}
	while (delta < at0us125);
}
//````````````````````````````````````````````````````````````````````````````````````````````````````````
