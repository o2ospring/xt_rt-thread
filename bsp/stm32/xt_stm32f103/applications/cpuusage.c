/**
  * @file  cpuusage.c
  * @brief CPU占用率统计驱动模块
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-16     o2ospring    原始版本
  */
#define   CPUUSAGE_C__
#include "cpuusage.h"
#ifdef    CPUUSAGE_X__
#undef    CPUUSAGE_H__
#include "cpuusage.h"
#endif

#ifndef XT_MSG_INIT_1_TAB_EXPORT
#define XT_MSG_INIT_1_TAB_EXPORT(func,name)
#endif

#ifdef RT_USING_FINSH

static uint32_t cpu_total_count = 0; //CPU-100%占用时计数值
static uint8_t  cpu_usage_major = 0; //小数点左边两位数据（整数值）
static uint8_t  cpu_usage_minor = 0; //小数点右边两位数据（小数值）
static uint8_t  cpu_usage_algo2 = 0; //CPU占用率统计算法2（前次读取后到本次读取前的之间最大占用率）
static uint8_t  cpu_usage_major2= 0; //小数点左边两位数据（整数值）
static uint8_t  cpu_usage_minor2= 0; //小数点右边两位数据（小数值）

void cpu_usage_init(void);
static uint32_t cpu_count(void);
static void cpu_usage_idle_hook(void);
void cpu100_usage_get(uint8_t *major, uint8_t *minor, uint8_t algo2);
uint32_t cpu10000_usage_get(uint8_t algo2);

/**
  * @brief  初始化CPU占用率统计模块，
  *         将统计函数绑定到操作系统空闲线程勾子上
  * @param  void
  * @return void
  */
void cpu_usage_init(void)
{
	/* set idle thread hook */
	rt_thread_idle_sethook(cpu_usage_idle_hook);
}
XT_MSG_INIT_1_TAB_EXPORT(cpu_usage_init, "cpu_usage_init()");

/**
  * @brief  统计空闲计数值
  * @param  void
  * @return void
  */
static uint32_t cpu_count(void)
{
	static rt_tick_t tick = 0;
	uint32_t count;
	uint32_t loop;
	count = 0;
	if (cpu_total_count == 0)
	{
		/* 计算CPU-100%占用时的标定操作 */
		tick = rt_tick_get();
		while (tick == rt_tick_get()) {;}
		tick = rt_tick_get();
	}
	while (rt_tick_get() - tick < CPU_USAGE_CALC_TICK)
	{
		count ++;
		loop  = 0;
		while (loop < CPU_USAGE_LOOP) loop ++;
	}
	tick += CPU_USAGE_CALC_TICK;
	return (count);
}

/**
  * @brief  统计CPU占用率
  * @param  void
  * @return void
  */
static void cpu_usage_idle_hook(void)
{
	register rt_base_t level;
	uint32_t count;
	
	if (cpu_total_count == 0)
	{
		/* 计算出CPU-100%占用时计数值 */
		rt_enter_critical();  //调度器上锁 >>>>>>>>>>>> 
		count = cpu_total_count = cpu_count();
		rt_exit_critical();   //调度器解锁 <<<<<<<<<<<<
	}
	else
	{
		/* 计算出当前CPU占用时计数值 */
		count = cpu_count();
	}
	
	/* 将计数值换算成百分比整数与小数值 */
	if (count < cpu_total_count)
	{
		count = cpu_total_count - count;
		level = rt_hw_interrupt_disable(); //关闭总中断 >>>>>>>>>>>>
		cpu_usage_major = ((count * 100) / cpu_total_count);
		cpu_usage_minor = ((count * 100) % cpu_total_count) * 100 / cpu_total_count;
		rt_hw_interrupt_enable(level);     //开启总中断 <<<<<<<<<<<<
	}
	else
	{
		cpu_total_count = count;
		cpu_usage_major = 100;
		cpu_usage_minor = 0;
	}
	/* 前次读取后到本次读取前的之间最大占用率 */
	if ((cpu_usage_algo2 == 0)
	|| ((cpu_usage_major > cpu_usage_major2))
	|| ((cpu_usage_major == cpu_usage_major2)
	  &&(cpu_usage_minor > cpu_usage_minor2)))
	{
		level = rt_hw_interrupt_disable(); //关闭总中断 >>>>>>>>>>>>
		cpu_usage_algo2  = 1;
		cpu_usage_major2 = cpu_usage_major;
		cpu_usage_minor2 = cpu_usage_minor;
		rt_hw_interrupt_enable(level);     //开启总中断 <<<<<<<<<<<<
	}
}

/**
  * @brief  读出当前CPU占用率（单位：xx.xx%）
  * @param  *major   百分比小数点左边两位数据（整数值）
  * @param  *minor   百分比小数点右边两位数据（小数值）
  * @param  algo2    是否使用算法2统计（非0->前次读取后到本次读取前的之间最大占用率）
  * @return void
  */
void cpu100_usage_get(uint8_t *major, uint8_t *minor, uint8_t algo2)
{
	RT_ASSERT(major != RT_NULL);
	RT_ASSERT(minor != RT_NULL);
	
	if (algo2 == 0)
	{
		*major = cpu_usage_major;
		*minor = cpu_usage_minor;
	}
	else
	{
		cpu_usage_algo2 = 0;
		*major = cpu_usage_major2;
		*minor = cpu_usage_minor2;
	}
}

/**
  * @brief  读出当前CPU占用率（单位：xxxx‰o）
  * @param  algo2    是否使用算法2统计（非0->前次读取后到本次读取前的之间最大占用率）
  * @return 万分比的CPU占用率（整数值）
  */
uint32_t cpu10000_usage_get(uint8_t algo2)
{
	if (algo2 == 0)
	{
		return ((uint32_t)cpu_usage_major * 100UL + (uint32_t)cpu_usage_minor);
	}
	else
	{
		cpu_usage_algo2 = 0;
		return ((uint32_t)cpu_usage_major2 * 100UL + (uint32_t)cpu_usage_minor2);
	}
}

#endif
