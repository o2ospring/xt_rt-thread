/**
  * @file  cpuusage.h
  * @brief CPU占用率统计驱动模块
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-16     o2ospring    原始版本
  * 2023-01-03     o2ospring    增加模块开关
  */
#ifndef CPUUSAGE_H__
#define CPUUSAGE_H__

#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#include <stdlib.h> //////////////////////// <- 使用到字符转换，如：atoi(s) 等
#ifdef CPUUSAGE_C__
#include "application.h" /////////////////// <- 按规定[application.h]作为工程所有软件资源管理头文件！
#include "xt_comdef.h" ///////////////////// <- 常用宏定义集合，如: XT_BIT_SET 等
#include "rtthread.h" ////////////////////// <- 使用RT-Thread操作系统
#include "rthw.h" ////////////////////////// <- 使用RT-Thread操作系统
#endif

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 参数配置 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#ifdef CPUUSAGE_C__ ////////////////////////////////////////////// <- 只有[cpuusage.c]才会包含引脚定义!!!!

#if   (RT_TICK_PER_SECOND == 100)
#define CPU_USAGE_CALC_TICK         10        //配置每次统计时间长度（多少个系统节拍,值越大计算越准但越久）
#define CPU_USAGE_LOOP              100       //统计计数基础代码计算单元值（至少运行多少条指令,典型值:100）
#elif (RT_TICK_PER_SECOND == 1000)
#define CPU_USAGE_CALC_TICK         100       //配置每次统计时间长度（多少个系统节拍,值越大计算越准但越久）
#define CPU_USAGE_LOOP              100       //统计计数基础代码计算单元值（至少运行多少条指令,典型值:100）
#else
#define CPU_USAGE_CALC_TICK         (RT_TICK_PER_SECOND/10)
#define CPU_USAGE_LOOP              100 
#endif
#ifndef XT_CPU_USAGE_EN
#define XT_CPU_USAGE_EN             1         //是否上电就开启统计（0:上电默认关闭统计CPU占用率）
#endif

#endif ///////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 操作函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void cpu_usage_init(void);
extern void cpu100_usage_get(uint8_t *major, uint8_t *minor, uint8_t algo2);
extern uint32_t cpu10000_usage_get(uint8_t algo2);

//extern void cpuusage_set(int argc, char *argv[]);
//extern void cpuusage(int argc, char *argv[]);

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef CPUUSAGE_H__
