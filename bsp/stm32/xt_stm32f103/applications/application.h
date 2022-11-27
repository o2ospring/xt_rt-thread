/**
  * @file  application.h
  * @brief 所有软件资源管理
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-10-15     o2ospring    原始版本
  */
#ifndef APPLICATION_H__
#define APPLICATION_H__

#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#include "xt_comdef.h" ///////////////////// <- 常用宏定义集合，如: XT_BIT_SET 等
#ifdef APPLICATION_C__
#include "board.h"
#include "bsp_stm32f1xx_wdg.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef APPLICATION_C__
#define APP_EXT
#else
#define APP_EXT  extern
#endif

/*********************************************************************************************************
 Board Version 目标板版本配置 ****************************************************************************
*********************************************************************************************************/

//-------------------------------------------
#define XT_HDWE_LED_A1_20221015         0                               /* 硬件版本: LED A1 20221015    */
//-------------------------------------------
#define XT_COMP_XXX                     0                               /* 部件搭配: 软件功能/硬件组件  */
//-------------------------------------------
#define XT_HDWE_VER                     XT_HDWE_LED_A1_20221015         /* 硬件版本选择（电路板版本）   */
#define XT_COMP_CFG                     XT_COMP_XXX                     /* 部件搭配选择（包括软硬件）   */

#if   (XT_HDWE_VER == XT_HDWE_LED_A1_20221015)
	#if   (XT_COMP_CFG == XT_COMP_XXX)
#define XT_PRINT_INIT_EN                1                           //是否开启打印初始过程信息（0:关闭）
#define XT_SFWE_VERSION                 "1.00.00.0.20221110"        //大版本号.小版本号.搭配号.测试号.日期
#define XT_HDWE_VERSION                 "1.0.00.00.20221015"        //大版本号.小版本号.搭配号.板编号.日期
	#endif
#endif

/*********************************************************************************************************
 Module Enable SW 模块启用开关 ***************************************************************************
*********************************************************************************************************/

//----------------------------------------
#define XT_DEF_DISABLED                 0                               /* 禁用模块                     */
#define XT_DEF_ENABLED                  1                               /* 使能模块                     */
//----------------------------------------
#define XT_APP_DEBUG                    20221126                        /* 开启[发送红外遥控码演示]     */
#define __XT_IR_SEND_REMAP_H
#ifndef XT_APP_IRSEND_EN
#define XT_APP_IRSEND_EN                XT_DEF_ENABLED                  /* 红外遥控发送服务模块         */
#endif

#include "rtthread.h" ////////////////////// <- 使用 RT-thread 操作系统头文件
/*********************************************************************************************************
 Task Priorities 线程优先级 (RT_THREAD_PRIORITY_MAX 为优先权最大值) (动态线程还要使能 RT_USING_HEAP) *****
*********************************************************************************************************/

//#define RT_TIMER_THREAD_PRIO          0    /*在<rtconfig.h>加入*/     /* _timer_thread_entry()        */
//#define FINSH_THREAD_PRIORITY         20   /*在<rtconfig.h>配置*/     /* finsh_thread_entry()         */
//#define RT_MAIN_THREAD_PRIORITY       5    /*在<rtconfig.h>配置*/     /* main_thread_entry()->main()  */

/*********************************************************************************************************
 Task Stack Sizes 线程堆栈大小 (须为4字节倍数) (一般比实际使用堆栈数大1/3倍) *****************************
*********************************************************************************************************/

//#define IDLE_THREAD_STACK_SIZE        512  /*在<rtconfig.h>配置*/     /* rt_thread_idle_entry()       */
//#define RT_TIMER_THREAD_STACK_SIZE    512  /*在<rtconfig.h>加入*/     /* _timer_thread_entry()        */
//#define FINSH_THREAD_STACK_SIZE       2048 /*在<rtconfig.h>配置*/     /* finsh_thread_entry()         */ //对象消耗:128+528(对象与堆栈优先使用动态内存分配)
//#define RT_MAIN_THREAD_STACK_SIZE     512  /*在<rtconfig.h>配置*/     /* main_thread_entry()->main()  */ //对象消耗:128    (对象与堆栈优先使用动态内存分配)

/*********************************************************************************************************
 Task Timeslice 线程同级调度节拍数 (RT_TICK_PER_SECOND 为每秒节拍数) *************************************
*********************************************************************************************************/

//#define XXX_THREAD_PRIO_TIMESLICE     4                               /* xxx_thread_entry()           */

/*********************************************************************************************************
 Event 事件标志 (使能 RT_USING_EVENT 配置) (动态事件标志还要使能 RT_USING_HEAP) **************************
*********************************************************************************************************/

//APP_EXT struct rt_event               xxx_event;                      /* xxx操作触发         事件标志 */

/*********************************************************************************************************
 Mutex 互斥量 (使能 RT_USING_MUTEX 配置) (动态互斥量还要使能 RT_USING_HEAP) ******************************
*********************************************************************************************************/

//APP_EXT struct rt_mutex               xxx_mutex;                      /* xxx操作互斥           互斥锁 */

/*********************************************************************************************************
 Semaphore 信号量 (使能 RT_USING_SEMAPHORE 配置) (动态信号量还要使能 RT_USING_HEAP) **********************
*********************************************************************************************************/

//APP_EXT struct rt_semaphore           xxx_sem;                        /* xxx状态触发           信号量 */

/*********************************************************************************************************
 Mailbox 邮箱 (使能 RT_USING_MAILBOX 配置) (动态邮箱还要使能 RT_USING_HEAP) ******************************
*********************************************************************************************************/

//APP_EXT struct rt_mailbox             xxx_mb;                         /* xxx交互                 邮箱 */
//#ifdef APPLICATION_C__
//ALIGN(RT_ALIGN_SIZE)
//static char xxx_mb_pool[5*4];         //须为4的倍数字节               /* xxx邮箱池                    */
//#endif

/*********************************************************************************************************
 Msg 消息 (使能 RT_USING_MESSAGEQUEUE 配置) (动态消息还要使能 RT_USING_HEAP) *****************************
*********************************************************************************************************/

//APP_EXT struct rt_messagequeue        xxx_mq;                         /* xxx交互                 消息 */
//#define XXX_MQ_SIZE                   128                             /* xxx每条信息大小              */
//#ifdef APPLICATION_C__
//ALIGN(RT_ALIGN_SIZE)
//static char xxx_mq_pool[1024];        //须为4的倍数字节               /* xxx信息池                    */
//#endif

/*********************************************************************************************************
* Task Stack 任务堆栈 ************************************************************************************
*********************************************************************************************************/

//#ifdef APPLICATION_C__
//ALIGN(RT_ALIGN_SIZE)
//static struct rt_thread xxx_thread;                                  /* xxx_thread_entry() 线程结构体 */
//static rt_uint8_t xxx_thread_stack[XXX_THREAD_STK_SIZE];             /* xxx_thread_entry() 线程的堆栈 */
//extern void xxx_thread_entry(void *p_arg);                           /* xxx_thread_entry() 线程       */
//#endif

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef APPLICATION_H__
