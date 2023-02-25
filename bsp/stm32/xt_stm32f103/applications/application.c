/**
  * @file  application.c
  * @brief 所有软件资源管理
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-18     o2ospring    原始版本
  */
#define   APPLICATION_C__
#include "application.h"
#ifdef    APPLICATION_X__
#undef    APPLICATION_H__
#include "application.h"
#endif

#if (FAULT_BACKTRACE_EN == XT_DEF_ENABLED)
#include "cm_backtrace.h"
#define EXCUTABLE_NAME                  "rt-thread"
#define SOFTWARE_VERSION                XT_SFWE_VERSION
#define HARDWARE_VERSION                XT_HDWE_VERSION
#endif

/**
  * @brief  当发生了断言错误时，报告源文件的名称和源行号
  * @param  file       源文件的名称
  * @param  line       源行号
  * @return void
  */
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
	rt_kprintf("\n\r Wrong parameter value detected on\r\n");
	rt_kprintf("       file  %s\r\n", file);
	rt_kprintf("       line  %d\r\n", line);
	
	while (1) ;
}
#endif

#if (FAULT_BACKTRACE_EN == XT_DEF_ENABLED)
static rt_err_t cm_exception_hook(void *context)
{
	extern long list_thread(void);
	uint8_t _continue = 1;
	
	cm_backtrace_fault(*((uint32_t *)(cmb_get_sp() + sizeof(uint32_t) * 8)), cmb_get_sp() + sizeof(uint32_t) * 9);
	
	#ifdef RT_USING_FINSH
	list_thread();
	#endif
	
	while (_continue == 1);
	
	return RT_EOK;
}
#endif

void app_tab_front(void) {}
void app_tab_limit(void) {}
XT_MSG_INIT_S_TAB_EXPORT(app_tab_front, " ");
XT_MSG_INIT_E_TAB_EXPORT(app_tab_limit, " ");
XT_APP_INIT_S_TAB_EXPORT(app_tab_front, " ");
XT_APP_INIT_E_TAB_EXPORT(app_tab_limit, " ");

/**
  * @brief  系统应用资源初始化
  * @param  *p_arg
  * @return void
  */
void rt_init_thread_entry(void *p_arg)
{
	const xt_init_fn_tab_t *p_tab;
	
	/* backtrace initialize */
	#if (FAULT_BACKTRACE_EN == XT_DEF_ENABLED)
	cm_backtrace_init(EXCUTABLE_NAME, HARDWARE_VERSION, SOFTWARE_VERSION);
	#endif
	
	/* set exception hook */
	#if (FAULT_BACKTRACE_EN == XT_DEF_ENABLED)
	rt_hw_exception_install(cm_exception_hook);
	#endif
	
	//4、信息上电初始化（如：信号量等）
	for (p_tab=&msg_init_fn_app_tab_front+1; p_tab<&msg_init_fn_app_tab_limit; p_tab++)
	{
		#if (defined XT_PRINT_INIT_EN) && (XT_PRINT_INIT_EN != 0)
		rt_kprintf("xt_msg_init: %s\r\n", p_tab->desc);
		#endif
		(*(p_tab->p_fn))();
	}
	
	//5、程序上电初始化（如：线程等）
	for (p_tab=&app_init_fn_app_tab_front+1; p_tab<&app_init_fn_app_tab_limit; p_tab++)
	{
		#if (defined XT_PRINT_INIT_EN) && (XT_PRINT_INIT_EN != 0)
		rt_kprintf("xt_app_init: %s\r\n", p_tab->desc);
		#endif
		(*(p_tab->p_fn))();
	}
}

void loop_tab_front(void) {}
void loop_tab_limit(void) {}
XT_APP_TLOOP_S_TAB_EXPORT(loop_tab_front, 100);
XT_APP_TLOOP_E_TAB_EXPORT(loop_tab_limit, 100);

/**
  * @brief  定时循环线程
  * @param  *p_arg
  * @return void
  */
void rt_timer_thread_loop(void *p_arg)
{
	const xt_tloop_fn_tab_t *p_tab;
	uint32_t ms = 0;
	
	#if (BSP_WDG_EN & 0x01)
	bsp_wdg_init(); //初始化看门狗
	#endif
	
	while (1)
	{
		ms += 10;
		if (ms == 4000320000UL) ms = 0;
		rt_thread_delay(10UL/*mS*//(1000/RT_TICK_PER_SECOND));
		
		//6、定时调用函数（如：扫描等）
		for (p_tab=&app_tloop_fn_loop_tab_front+1; p_tab<&app_tloop_fn_loop_tab_limit; p_tab++)
		{
			if ((ms % p_tab->ms) == 0)
			{
				(*(p_tab->p_fn))();
			}
		}
		
		// 20mS调用一次
		//if ((ms % 20) == 0)
		//{
		//}
		// 100mS调用一次
		//if ((ms % 100) == 0)
		//{
		//}
	}
}
