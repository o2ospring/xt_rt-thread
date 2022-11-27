/**
  * @file  app_debug.c
  * @brief 应用临时调试
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-27     o2ospring    原始版本
  */
#define   APP_DEBUG_C__
#include "app_debug.h"
#ifdef RT_USING_FINSH
#ifdef    APP_DEBUG_X__
#undef    APP_DEBUG_H__
#include "app_debug.h"
#endif

/**
  * @brief  读出CPU占用率
  * @param  命令: cpuusage   表示读出当前即时CPU占有率
  * @param  命令: cpuusage 0 表示读出当前即时CPU占有率
  * @param  命令: cpuusage 1 表示读出前次读后到现在的最大CPU占有率
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
