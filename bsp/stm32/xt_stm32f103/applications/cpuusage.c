/**
  * @file  cpuusage.c
  * @brief CPUռ����ͳ������ģ��
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-16     o2ospring    ԭʼ�汾
  * 2023-01-03     o2ospring    ����ģ�鿪��
  */
#define   CPUUSAGE_C__
#include "cpuusage.h"
#if (defined XT_APP_CPUUSAGE_EN) && (XT_APP_CPUUSAGE_EN == XT_DEF_ENABLED)
#ifdef    CPUUSAGE_X__
#undef    CPUUSAGE_H__
#include "cpuusage.h"
#endif

#ifndef XT_MSG_INIT_1_TAB_EXPORT
#define XT_MSG_INIT_1_TAB_EXPORT(func,desc)
#endif

#ifdef RT_USING_FINSH

static uint32_t cpu_total_count = 0; //CPU-100%ռ��ʱ����ֵ
static uint8_t  cpu_usage_major = 0; //С���������λ���ݣ�����ֵ��
static uint8_t  cpu_usage_minor = 0; //С�����ұ���λ���ݣ�С��ֵ��
static uint8_t  cpu_usage_algo2 = 0; //CPUռ����ͳ���㷨2��ǰ�ζ�ȡ�󵽱��ζ�ȡǰ��֮�����ռ���ʣ�
static uint8_t  cpu_usage_major2= 0; //С���������λ���ݣ�����ֵ��
static uint8_t  cpu_usage_minor2= 0; //С�����ұ���λ���ݣ�С��ֵ��
static uint8_t  cpu_usage_enable;    //�Ƿ��ϵ�Ϳ���ͳ��

void cpu_usage_init(void);
static uint32_t cpu_count(void);
static void cpu_usage_idle_hook(void);
void cpu100_usage_get(uint8_t *major, uint8_t *minor, uint8_t algo2);
uint32_t cpu10000_usage_get(uint8_t algo2);

/**
  * @brief  ��ʼ��CPUռ����ͳ��ģ�飬
  *         ��ͳ�ƺ����󶨵�����ϵͳ�����̹߳�����
  * @param  void
  * @return void
  */
void cpu_usage_init(void)
{
	#if (XT_CPU_USAGE_EN == 0)
	cpu_usage_enable = 0;
	#else
	cpu_usage_enable = 1;
	#endif
	/* set idle thread hook */
	rt_thread_idle_sethook(cpu_usage_idle_hook);
}
XT_MSG_INIT_1_TAB_EXPORT(cpu_usage_init, "cpu_usage_init()");

/**
  * @brief  ͳ�ƿ��м���ֵ
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
		/* ����CPU-100%ռ��ʱ�ı궨���� */
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
  * @brief  ͳ��CPUռ����
  * @param  void
  * @return void
  */
static void cpu_usage_idle_hook(void)
{
	register rt_base_t level;
	uint32_t count;
	
	if (cpu_total_count == 0)
	{
		/* �����CPU-100%ռ��ʱ����ֵ */
		rt_enter_critical();  //���������� >>>>>>>>>>>> 
		count = cpu_total_count = cpu_count();
		rt_exit_critical();   //���������� <<<<<<<<<<<<
	}
	else
	{
		if (cpu_usage_enable == 0) return;
		
		/* �������ǰCPUռ��ʱ����ֵ */
		count = cpu_count();
	}
	if (cpu_usage_enable == 0) return;
	
	/* ������ֵ����ɰٷֱ�������С��ֵ */
	if (count < cpu_total_count)
	{
		count = cpu_total_count - count;
		level = rt_hw_interrupt_disable(); //�ر����ж� >>>>>>>>>>>>
		cpu_usage_major = ((count * 100) / cpu_total_count);
		cpu_usage_minor = ((count * 100) % cpu_total_count) * 100 / cpu_total_count;
		rt_hw_interrupt_enable(level);     //�������ж� <<<<<<<<<<<<
	}
	else
	{
		cpu_total_count = count;
		cpu_usage_major = 100;
		cpu_usage_minor = 0;
	}
	/* ǰ�ζ�ȡ�󵽱��ζ�ȡǰ��֮�����ռ���� */
	if ((cpu_usage_algo2 == 0)
	|| ((cpu_usage_major > cpu_usage_major2))
	|| ((cpu_usage_major == cpu_usage_major2)
	  &&(cpu_usage_minor > cpu_usage_minor2)))
	{
		level = rt_hw_interrupt_disable(); //�ر����ж� >>>>>>>>>>>>
		cpu_usage_algo2  = 1;
		cpu_usage_major2 = cpu_usage_major;
		cpu_usage_minor2 = cpu_usage_minor;
		rt_hw_interrupt_enable(level);     //�������ж� <<<<<<<<<<<<
	}
}

/**
  * @brief  ������ǰCPUռ���ʣ���λ��xx.xx%��
  * @param  *major   �ٷֱ�С���������λ���ݣ�����ֵ��
  * @param  *minor   �ٷֱ�С�����ұ���λ���ݣ�С��ֵ��
  * @param  algo2    �Ƿ�ʹ���㷨2ͳ�ƣ���0->ǰ�ζ�ȡ�󵽱��ζ�ȡǰ��֮�����ռ���ʣ�
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
  * @brief  ������ǰCPUռ���ʣ���λ��xxxx��o��
  * @param  algo2    �Ƿ�ʹ���㷨2ͳ�ƣ���0->ǰ�ζ�ȡ�󵽱��ζ�ȡǰ��֮�����ռ���ʣ�
  * @return ��ֱȵ�CPUռ���ʣ�����ֵ��
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

/**
  * @brief  �����Ƿ���ͳ��CPUռ����
  * @param  argc     ��ڲ�������
  * @param  argv[1]  �Ƿ���ͳ��CPUռ���ʣ�0:�رգ�
  * @return void
  */
void cpuusage_set(int argc, char *argv[])
{
	register rt_base_t level;
	if (argc < 2)
	{
		rt_kprintf("cpuusage_set input argc error!\r\n");
	}
	cpu_usage_enable = (atoi(argv[1]) == 0) ? 0 : 1;
	if (cpu_usage_enable == 0)
	{
		level = rt_hw_interrupt_disable(); //�ر����ж� >>>>>>>>>>>>
		cpu_usage_major  = 0;
		cpu_usage_minor  = 0;
		cpu_usage_major2 = 0;
		cpu_usage_minor2 = 0;
		rt_hw_interrupt_enable(level);     //�������ж� <<<<<<<<<<<<
	}
}
FINSH_FUNCTION_EXPORT(cpuusage_set, cpuusage_set 1 or 0);
MSH_CMD_EXPORT(cpuusage_set, cpuusage_set 1 or 0);

/**
  * @brief  ����CPUռ����
  * @param  ����: cpuusage   ��ʾ������ǰ��ʱCPUռ����
  * @param  ����: cpuusage 0 ��ʾ������ǰ��ʱCPUռ����
  * @param  ����: cpuusage 1 ��ʾ����ǰ�ζ������ڵ����CPUռ����
  * @return void
  */
void cpuusage(int argc, char *argv[])
{
	unsigned char major, minor;
	if ((argc < 2)
	||  (atoi(argv[1]) == 0))
	{
		cpu100_usage_get(&major, &minor, 0);
	}
	else
	{
		cpu100_usage_get(&major, &minor, 1);
	}
	rt_kprintf("CPU:%d.%02d%%\r\n", major, minor);
}
FINSH_FUNCTION_EXPORT(cpuusage, cpuusage 1 or 0);
MSH_CMD_EXPORT(cpuusage, cpuusage 1 or 0);

#endif
#endif //#if (XT_APP_CPUUSAGE_EN == XT_DEF_ENABLED)
