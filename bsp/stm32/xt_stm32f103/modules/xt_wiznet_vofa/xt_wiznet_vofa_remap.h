/**
  * @file  xt_wiznet_vofa.h
  * @brief UDP网络虚拟数字示波器（VOFA+ 伏特加）
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-12-16     o2ospring    原始版本
  * 2023-05-17     o2ospring    增加向[5555]端口广播本机IP
  * 2023-11-17     o2ospring    增加上电暂停刷新示波器功能
  * 2023-12-16     o2ospring    增加可修改连接上位机的端口
  */
#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#include <string.h> //////////////////////// <- 使用的字符处理，如: strcpy(), memcpy() 等
#include <stdio.h> ///////////////////////// <- 使用标准输入输出，如：sprintf(p,...) 等
#include <stdlib.h> //////////////////////// <- 使用到字符转换，如：atoi(s) 等
#include "rtthread.h" ////////////////////// <- 使用RT-Thread操作系统
#include "xt_wiznet.h" ///////////////////// <- 依赖网络服务模块!!!!!!!!!!!!!!!!!!!!!!!!!

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 参数配置 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#define XT_WIZVOFA_POWERON_EN       1                                    //是否上电开启示波器（0:不开启）
#define XT_WIZVOFA_REFRESH_TK       (100/*ms*//(1000/RT_TICK_PER_SECOND))//设置示波器刷新时间（0:上电暂停刷新,@系统节拍）
#define XT_WIZVOFA_SOCKET           (XT_SOCK_SUM - 2)                    //使用第几个socket接口连接示波器
#define XT_WIZVOFA_CH_SUM           4   /*目前[VOFA+]没有限制*/          //示波器通道总数（4:共4路）
#define XT_WIZVOFA_BIG_ENDIAN_SW    0   /*针对大端处理器才开启*/         //开启大端处理器（0:禁用）
#define XT_WIZVOFA_CMD_MAX          100 /*只支持[rt-thread]系统*/        //示波器传来的字符控制命令的大小限制（0:关闭支持）
#define xt_wizvofa_printf(...)      rt_kprintf("wizvofa:" __VA_ARGS__)   //异常信息打印（目前还没用到可变参数，可以稍作修改本行宏即可支持C89语法）

#define XT_WIZVOFA_VARIAB()         register rt_base_t level;            //数据互斥:使用到的变量声明
#define XT_WIZVOFA_LOCKED()         level = rt_hw_interrupt_disable()    //数据互斥:[关]中断总开关
#define XT_WIZVOFA_UNLOCK()         rt_hw_interrupt_enable(level)        //数据互斥:[开]中断总开关

#if (defined XT_WIZNET_VOFA_C__) && (XT_APP_WIZNETVOFA_EN == XT_DEF_ENABLED)
uint8_t xt_wizvofa_ip[4]          = {192, 168, 3, 222};                  /* VOFA+示波器软件(服务端)的IP */
#endif
#define XT_WIZVOFA_SOCKET_NUM       1003                                 /* VOFA+示波器端及本机的UDP端口*/
#define XT_WIZVOFA_OS_TICK_T        rt_tick_t                            /* 定义操作系统节拍的数据类型  */
#define XT_WIZVOFA_OS_THREAD_T      rt_thread_t                          /* 定义操作系统线程的数据类型  */
#define XT_WIZVOFA_OS_TICK_GET()    rt_tick_get()                        /* 获取操作系统节拍器的计数值  */
#define XT_WIZVOFA_OS_DLY_TICK(n)   rt_thread_delay(n)                   /* 系统延时n个节拍             */
#define XT_WIZVOFA_OS_TICK_LIMIT    10                                   /* 工作线程运行节拍频率限制    */
#define XT_WIZVOFA_OS_TICK_OVMAX    (RT_TICK_MAX / 3)                    /* 判断操作系统节拍器翻转最大值*/
#define XT_WIZVOFA_THREAD_CREATE(p) p = rt_thread_create("xt_wizvofa", xt_wizvofa_thread_entry, 0, 480, 5, 4); \
                                    if (p != RT_NULL) rt_thread_startup(p)
#if (XT_WIZVOFA_REFRESH_TK < 0)
#error "" 
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 操作函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void xt_wizvofa_init(void); //上电初始化
extern void xt_wizvofa_open(void); //上电初始化
extern void xt_wizvofa_cycl(XT_WIZVOFA_OS_TICK_T tk);
extern int xt_wizvofa_1ch_put(uint8_t ch_n, float chx);
extern int xt_wizvofa_4ch_put(uint8_t ch_f, float ch1, float ch2, float ch3, float ch4);
extern int xt_wizvofa_xch_put(uint8_t ch_s, float *p_ch, uint8_t s_ch);

//extern void xt_wizvofa_ip_set(int argc, char *argv[]);
//extern void xt_wizvofa_port_set(int argc, char *argv[]);
//extern void xt_wizvofa_cycl_set(int argc, char *argv[]);
//extern void xt_wizvofa_help(void);

#ifdef __cplusplus
	}
#endif
