/**
  * @file  main.c
  * @brief 应用主函数
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-18     o2ospring    原始版本
  */
#define   MAIN_C__
#include "main.h"
#ifdef    MAIN_X__   //再次调用头文件,用于增加存在交叉关系的内容!
#undef    MAIN_H__
#include "main.h"
#endif

extern void rt_init_thread_entry(void *p_arg);
extern void rt_timer_thread_loop(void *p_arg);

int main(void)
{
	rt_init_thread_entry(0); //应用上电初始化
	rt_timer_thread_loop(0); //软件定时器循环
	return 0;
}
