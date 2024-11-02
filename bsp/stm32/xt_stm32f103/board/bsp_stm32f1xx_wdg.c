/**
  * @file  bsp_stm32f1xx_wdg.c
  * @brief 全局看门狗驱动程序
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-18     o2ospring    原始版本
  */
#define   BSP_STM32F1XX_WDG_C__
#include "bsp_stm32f1xx_wdg.h"
#ifdef    BSP_STM32F1XX_WDG_X__
#undef    BSP_STM32F1XX_WDG_H__
#include "bsp_stm32f1xx_wdg.h"
#endif

#if (BSP_WDG_EN & 0x01)	
#if (BSP_WDG_CFG == 0)
#warning "[BSP_WDG_CFG]禁止时主要为仿真调试不受影响，正常产品请打开它"
#endif
#if (BSP_WDG_CFG >= 2)
#error "目前驱动不支持[窗口看门狗]操作，请重新配置[BSP_WDG_CFG]"
#endif
#endif

#ifndef XT_APP_TLOOP_1_TAB_EXPORT
#define XT_APP_TLOOP_1_TAB_EXPORT(func,ms)
#endif

#if (BSP_WDG_EN & 0x01)
#if (BSP_WDG_CFG == 1)
uint8_t iwdg_runner = 0;
#endif
/**
  * @brief  看门狗初始化
  * @param  void
  * @return void
  */
void bsp_wdg_init(void)
{
	#if (BSP_WDG_CFG == 1)
	// 独立看门狗初始化(主要用于监视硬件错误) ############################################################
	//                                  ┌→LSI时钟, 会温飘:手册说LSI时钟频率大约32kHz(在30kHz和60kHz之间)
	// 特别注意: 1. 独立看门狗时钟由内部32KHZ提供，所以不受主时钟影响，即一旦启动看门狗，即便在调试过程中，
	//              暂停程序运行，看门狗也将不会停止，在复位时间到后仍会将系统复位。
	//           2. 可能会出现这种情况：启用了硬件看门狗，然后就没法下载程序了（JTAG）。可能因为在烧录前一
	//              刻程序已启动看门狗，JTAG编程/擦除中途就被强行复位。建议程序上电至少1秒后才启动看门狗!!
	
	IWDG_HandleTypeDef hiwdg;
	
	hiwdg.Instance = IWDG;
	hiwdg.Init.Prescaler = IWDG_PRESCALER_32; // 40K时钟32分频(★32分频后，每周期约为【1ms】)
	hiwdg.Init.Reload = IWDG_TIMEOUT_SET;     // 计数器数值   (0-0x0FFF)(如:349->共计时 349+1 个周期)
	if (HAL_IWDG_Init(&hiwdg) != HAL_OK) {}   // 重启计数器   (IWDG timeout = 1ms * (349+1) = 350 ms)
	#endif
}

/**
  * @brief  设置看门狗操作者
  * @param  runner     操作者（0:软件定时器喂狗, 1:硬件定时器喂狗）
  * @return void
  */
void wdg_runner_set(uint8_t runner)
{
	#if (BSP_WDG_CFG == 1)
	if (runner > 1) return;
	iwdg_runner = runner;
	#endif
}

/**
  * @brief  看门狗重置（喂狗）
  * @param  runner     操作者（0:软件定时器喂狗, 1:硬件定时器喂狗）
  * @return void
  */
void wdg_reload_counter(uint8_t runner)
{
	#if (BSP_WDG_CFG == 1)
	// 关于独立看门狗喂狗
	// 注意: 应在设置溢出时间的一半时期内喂狗(保守1/3时间内),否则可能温飘导致意外复位
	struct { IWDG_TypeDef *Instance; }   hiwdg = { IWDG };
	                                     //IWDG_HandleTypeDef hiwdg;
	if (runner == iwdg_runner) {         //hiwdg.Instance = IWDG;
	__HAL_IWDG_RELOAD_COUNTER(&hiwdg); } //HAL_IWDG_Refresh(&hiwdg);  // 重启计数器（喂狗）
	#endif
}

//应用：软件定时器喂狗
void wdg_reload_software(void)
{
	wdg_reload_counter(0);
}
XT_APP_TLOOP_1_TAB_EXPORT(wdg_reload_software, 100/*ms*/);

#endif  //#if (BSP_WDG_EN & 0x01)
