/**
  * @file  app_debug.h
  * @brief 应用临时调试
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-27     o2ospring    原始版本
  */
#ifndef APP_DEBUG_H__
#define APP_DEBUG_H__

#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#ifdef APP_DEBUG_C__
#include <string.h> //////////////////////// <- 使用的字符处理，如: strcpy(), memcpy() 等
#include <stdlib.h> //////////////////////// <- 使用到字符转换，如：atoi(s) 等
#include "application.h" /////////////////// <- 工程所有软件资源管理头文件!!!!!!!!!!!!!!!
#include "rtthread.h" ////////////////////// <- 使用RT-Thread操作系统
#include "rthw.h" ////////////////////////// <- 使用RT-Thread操作系统
#include "rtconfig.h" ////////////////////// <- 使用RT-Thread操作系统
#include "finsh.h" ///////////////////////// <- 使用RT-Thread操作系统
#include "cpuusage.h" ////////////////////// <- 使用CPU占有率统计模块
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if 0 ////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef RT_DEBUG
#warning "[RT_DEBUG]使能时主要用于测试,正常产品可以关闭它"
#endif
#ifdef RT_USING_CONSOLE
#warning "[RT_USING_CONSOLE]使能时主要用于测试,正常产品可以关闭它"
#endif
#ifdef RT_USING_FINSH
#warning "[RT_USING_FINSH]使能时主要用于测试,正常产品可以关闭它"
#endif
#ifdef FINSH_USING_MSH
#warning "[FINSH_USING_MSH]使能时主要用于测试,正常产品可以关闭它"
#endif

#if !defined(RT_USING_FINSH) \
&&  (defined(RT_USING_SERIAL) || defined(BSP_USING_UART1) ||\
     defined(BSP_USING_UART2) || defined(BSP_USING_UART3) ||\
     defined(BSP_USING_UART4) || defined(BSP_USING_UART5))
#warning "[RT_USING_FINSH]没使能时,如果应用没使用系统[串行设备],则建议将[RT_USING_SERIAL][BSP_USING_UARTx]关闭,并且将[serial.c][drv_usart.c]从工程树移除"
#endif
#endif ///////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef APP_DEBUG_H__
