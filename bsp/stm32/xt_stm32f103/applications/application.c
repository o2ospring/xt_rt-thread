/**
  * @file  application.c
  * @brief ���������Դ����
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-18     o2ospring    ԭʼ�汾
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
  * @brief  �������˶��Դ���ʱ������Դ�ļ������ƺ�Դ�к�
  * @param  file       Դ�ļ�������
  * @param  line       Դ�к�
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
  * @brief  ϵͳӦ����Դ��ʼ��
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
	
	//4����Ϣ�ϵ��ʼ�����磺�ź����ȣ�
	for (p_tab=&msg_init_fn_app_tab_front+1; p_tab<&msg_init_fn_app_tab_limit; p_tab++)
	{
		#if (defined XT_PRINT_INIT_EN) && (XT_PRINT_INIT_EN != 0)
		rt_kprintf("xt_msg_init: %s\r\n", p_tab->desc);
		#endif
		(*(p_tab->p_fn))();
	}
	
	//5�������ϵ��ʼ�����磺�̵߳ȣ�
	for (p_tab=&app_init_fn_app_tab_front+1; p_tab<&app_init_fn_app_tab_limit; p_tab++)
	{
		#if (defined XT_PRINT_INIT_EN) && (XT_PRINT_INIT_EN != 0)
		rt_kprintf("xt_app_init: %s\r\n", p_tab->desc);
		#endif
		(*(p_tab->p_fn))();
	}
}

/**
  * @brief  ��ʱѭ���߳�
  * @param  *p_arg
  * @return void
  */
void rt_timer_thread_loop(void *p_arg)
{
	unsigned long ulCnt = 0;
	
	#if (BSP_WDG_EN & 0x01)
	bsp_wdg_init(); //��ʼ�����Ź�
	#endif
	
	while (1)
	{
		ulCnt++;
		if (ulCnt == 4000320000UL) ulCnt = 0;
		rt_thread_delay(10UL/*mS*//(1000/RT_TICK_PER_SECOND));
		
		#if (XT_APP_SCOMVOFA_EN == XT_DEF_ENABLED)
		xt_scomvofa_cmd_run();
		#endif
		// 20mS����һ��
		//if ((ulCnt % 2) == 0)
		//{
		//}
		// 50mS����һ��
		//if ((ulCnt % 5) == 0)
		//{
		//}
		//else{}
		// 100mS����һ��
		if ((ulCnt % 10) == 0)
		{
			#if (BSP_WDG_EN & 0x01)
			wdg_reload_counter(0); // ι��: �������Ź�(Ӱ��������)
			#endif
		}
		// 200mS����һ��
		if ((ulCnt % 20) == 0)
		{
			#if (defined(XT_APP_DEBUG) && (XT_APP_DEBUG == 20221201))
			#if (XT_APP_SCOMSDS_EN == XT_DEF_ENABLED)
			xt_scomsds_1ch_put(0x80, (signed short)(cpu10000_usage_get(1)));
			#endif
			#endif
			#if (defined(XT_APP_DEBUG) && (XT_APP_DEBUG == 20221203))
			#if (XT_APP_SCOMVOFA_EN == XT_DEF_ENABLED)
			xt_scomvofa_1ch_put(0x80, (float)(cpu10000_usage_get(1)) / 100);
			#endif
			#endif
			#if (defined(XT_APP_DEBUG) && (XT_APP_DEBUG == 20221216))
			#if (XT_APP_WIZNETVOFA_EN == XT_DEF_ENABLED)
			xt_wizvofa_1ch_put(0x00, (float)(cpu10000_usage_get(1)) / 100);
			#endif
			#endif
		}
		// 500mS����һ��
		//if ((ulCnt % 50) == 0)
		//{
		//}
		// 1000mS����һ��
		//if ((ulCnt % 100) == 0)
		//{
		//}
		// 1Сʱ����һ��
		//if ((ulCnt % 360000) == 0)
		//{
		//}
	}
}
