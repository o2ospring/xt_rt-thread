/**
  * @file  bsp_stm32f1xx_swj.c
  * @brief 开启SWJ调试口驱动程序
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    原始版本
  */
#define   BSP_STM32F1XX_SWJ_C__
#include "bsp_stm32f1xx_swj.h"
#ifdef    BSP_STM32F1XX_SWJ_X__
#undef    BSP_STM32F1XX_SWJ_H__
#include "bsp_stm32f1xx_swj.h"
#endif

#ifndef XT_CHIP_INIT_2_TAB_EXPORT
#define XT_CHIP_INIT_2_TAB_EXPORT(func,desc)
#endif

#if (BSP_JTAG_DI_SW_EN & 0x01)
/**
  * @brief  开启SWJ调试口初始化
  * @param  void
  * @return void
  */
void bsp_swj_init(void)
{
	__HAL_AFIO_REMAP_SWJ_NOJTAG();
}
XT_CHIP_INIT_2_TAB_EXPORT(bsp_swj_init, "bsp_swj_init()");
#endif  //#if (BSP_JTAG_DI_SW_EN & 0x01)
