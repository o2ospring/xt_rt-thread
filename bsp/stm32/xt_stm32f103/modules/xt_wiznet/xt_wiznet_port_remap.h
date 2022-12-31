/**
  * @file  xt_wiznet_port.h
  * @brief 对接 WIZnet Hardwired TCP/IP Chips (WIZCHIP) 硬件TCP/IP协议栈（如：W5100S 芯片）
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-12-10     o2ospring    原始版本
  *                             仓库:   https://github.com/Wiznet/ioLibrary_Driver.git
  *                             Date:   Mon Feb 21 09:32:42 2022 +0900
  *                             Fix W5100S getIR()
  */
#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#include <string.h> //////////////////////// <- 使用的字符处理，如: strcpy(), memcpy() 等
#include "rtthread.h" ////////////////////// <- 使用RT-Thread操作系统
#include "rthw.h" ////////////////////////// <- 使用RT-Thread操作系统
#include "dhcp.h" ////////////////////////// <- 依赖 DHCP    服务模块
#include "socket.h" //////////////////////// <- 依赖 socket  服务模块
#if (defined(XT_WIZNET_PORT_C__) && (XT_APP_WIZNET_EN == XT_DEF_ENABLED))
#include "xt_wiznet_hspi_stm32f1xx_hal.h"/// <- 依赖 SPI总线 驱动模块
#include "xt_wiznet.h" ///////////////////// <- 依赖网络服务模块
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef XT_WIZNET_PORT_C__
#define XTWNPORT_EXT
#else
#define XTWNPORT_EXT  extern
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 参数配置 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#if (XT_APP_WIZNET_EN == XT_DEF_ENABLED)
#undef  _WIZCHIP_
#define _WIZCHIP_                 W5100S   /* W5100, W5100S, W5200, W5300, W5500 */
#if _WIZCHIP_ >= W5200
   #define XT_SOCK_SUM            8   ///< The count of independant socket of @b WIZCHIP
#else                             
   #define XT_SOCK_SUM            4   ///< The count of independant socket of @b WIZCHIP
#endif
//#define _DHCP_DEBUG_(...)       rt_kprintf("net:" __VA_ARGS__)        /* 打印DHCP工作状态             */
//分配一个socket给DHCP使用--------------------------------------------------------------------------------
#define XT_WIZ_SOCK_DHCP          (XT_SOCK_SUM - 1)                     /* 分配一个socket给DHCP使用     */
//数据临界处理--------------------------------------------------------------------------------------------
#define XT_WIZ_CPOINT_INIT()                                            /* 数据临界处理:初始化          */
#define XT_WIZ_CPOINT_VARIAB()    register rt_base_t level;             /* 数据临界处理:使用到的变量声明*/
#define XT_WIZ_CPOINT_LOCKED()    level = rt_hw_interrupt_disable()     /* 数据临界处理:进入临界(上锁)  */
#define XT_WIZ_CPOINT_UNLOCK()    rt_hw_interrupt_enable(level)         /* 数据临界处理:退出临界(解锁)  */
//SPI总线互斥---------------------------------------------------------------------------------------------
XTWNPORT_EXT struct rt_mutex      wspi_mutex;
#define XT_WIZ_SPI_MUTEX_INIT()   rt_mutex_init(&wspi_mutex, "wspi_mutex", RT_IPC_FLAG_FIFO)  /* 初始化 */
#define XT_WIZ_SPI_MUTEX_EN()     rt_mutex_take(&wspi_mutex, RT_WAITING_FOREVER) /* SPI总线操作互斥上锁 */
#define XT_WIZ_SPI_MUTEX_DI()     rt_mutex_release(&wspi_mutex)                  /* SPI总线操作互斥解锁 */
//全局操作与socket操作互斥--------------------------------------------------------------------------------
XTWNPORT_EXT struct rt_event      wsk_event;
#define XT_WIZ_IC_MUTEX_INIT()    rt_event_init(&wsk_event, "wsk_event", RT_IPC_FLAG_FIFO);   /* 初始化 */\
                                  rt_event_send(&wsk_event, 0x00FF)              /* 初始化event操作互斥 */
#define XT_WIZ_IC_MUTEX_EN(f)     rt_event_recv(&wsk_event, 0x00FF, RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, (rt_uint32_t *)(&(f))) /* 进入芯片全局互斥 */
#define XT_WIZ_IC_MUTEX_DI()      rt_event_send(&wsk_event, 0x00FF)                                                                                     /* 退出芯片全局互斥 */
#define XT_WIZ_SK_MUTEX_EN(s,f)   rt_event_recv(&wsk_event, 1UL<<s, RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, (rt_uint32_t *)(&(f))) /* 进入单socket互斥 */
#define XT_WIZ_SK_MUTEX_DI(s)     rt_event_send(&wsk_event, 1UL<<s)                                                                                     /* 退出单socket互斥 */
//线程初始化操作------------------------------------------------------------------------------------------
#ifdef XT_WIZNET_PORT_C__
#ifndef XTNET_THREAD_PRIO
#define XTNET_THREAD_PRIO               10 /*比socket线程优先级高*/     /* xt_net_thread_entry()        */
#endif
#ifndef XTNET_THREAD_STK_SIZE
#define XTNET_THREAD_STK_SIZE           512                             /* xt_net_thread_entry()        */
#endif
#ifndef XTNET_THREAD_PRIO_TIMESLICE
#define XTNET_THREAD_PRIO_TIMESLICE     4                               /* xt_net_thread_entry()        */
#endif
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t xt_net_thread_stack[XTNET_THREAD_STK_SIZE];
static struct rt_thread xt_net_thread;
void xt_net_thread_entry(void *p_arg);
#define XT_WIZ_THREAD_INIT()      rt_thread_init(&xt_net_thread, "xt_net", xt_net_thread_entry, RT_NULL, \
                                                (rt_uint8_t *)(&xt_net_thread_stack[0]), sizeof(xt_net_thread_stack), \
                                                 XTNET_THREAD_PRIO, XTNET_THREAD_PRIO_TIMESLICE);        \
                                  rt_thread_startup(&xt_net_thread)     /* 上电初始化网络服务主线程     */
#endif
#endif
//socket状态等待时线程调度处理----------------------------------------------------------------------------
#define XT_WIZ_OS_TICK_T          rt_tick_t                             /* 定义操作系统节拍的数据类型   */
#define XT_WIZ_OS_THREAD_T        rt_thread_t                           /* 定义操作系统线程的数据类型   */
#define XT_WIZ_OS_10MS(n)         rt_thread_delay(n*(10UL/(1000/RT_TICK_PER_SECOND)))/* 系统延时n个10mS */
#define XT_WIZ_OS_TICK_GET()      rt_tick_get()                         /* 获取操作系统节拍器的计数值   */
#define XT_WIZ_OS_TICK_OVMAX      (RT_TICK_MAX / 3)                     /* 判断操作系统节拍器翻转最大值 */
#define XT_WIZ_OS_THREAD_PRI_LOW  (RT_THREAD_PRIORITY_MAX - 1)          /* 操作系统线程最低优级前一级   */
#define XT_WIZ_OS_THREAD_YIELD()  rt_thread_yield()                     /* 操作系统线程让出机制函数     */
#define XT_WIZ_OS_THREAD_GET()    rt_thread_self()                      /* 获取操作系统当前线程指针     */
#define XT_WIZ_OS_THREAD_PRI_GET(pthr)   (pthr)->current_priority       /* 获取操作系统线程优先级       */
#define XT_WIZ_OS_THREAD_PRI_CHANGE(pthr, prio) rt_thread_control(pthr, RT_THREAD_CTRL_CHANGE_PRIORITY, &(prio))
																	    /* 修改操作系统线程优先级       */
#if (XT_APP_WIZNET_EN == XT_DEF_ENABLED)
#ifdef XT_WIZNET_PORT_C__
#define MS(m)                     (m/(1000/RT_TICK_PER_SECOND))         //时间[ms]换算为[系统节拍数]
static volatile XT_WIZ_OS_TICK_T  xt_wiz_waite_tick[8] = {MS(250), MS(250), MS(250), MS(250), MS(250), MS(250), MS(250), MS(250)}; //推荐默认250mS
const  static   XT_WIZ_OS_TICK_T  xt_wiz_waite_init[8] = {MS(250), MS(250), MS(250), MS(250), MS(250), MS(250), MS(250), MS(250)}; //推荐默认250mS
static volatile uint8_t           xt_wiz_waite_flag[8] = {0};
const uint8_t xt_wiz_tx_size_tab[8] = {2, 2, 2, 2, 2, 2, 2, 2};         //(W5100:8K/W5500:16K，注意：数值只能设置为 1、2、4、8)
const uint8_t xt_wiz_rx_size_tab[8] = {2, 2, 2, 2, 2, 2, 2, 2};         //(W5100:8K/W5500:16K，注意：数值只能设置为 1、2、4、8)
ALIGN(RT_ALIGN_SIZE) uint8_t xt_wiz_dhcp_buf[1024];                     //DHCP用到的缓冲器
#endif
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 数据类型 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

//socket工作等待超时管理
typedef struct xt_wizchip_
{
	uint8_t flag;            //状态标志
	uint8_t prio;            //记录线程优先级
	uint8_t wtfg;            //等待工作模式标志
	uint8_t fixed;           //强制固定等待时间
	uint8_t scheduler_ver;   //调度版本
	uint8_t scheduler_cnt;   //调度计数
	uint8_t scheduler_max;   //调度限制
	XT_WIZ_OS_TICK_T   tick; //计时器/计数器
	XT_WIZ_OS_THREAD_T pthr; //当前程序指针
}xt_wizchip_t;

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 操作函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

//供给[xt_wiznet.c]模块使用
extern void xt_wiz_pin_init(void);
extern void xt_wiz_reset(void);
extern void xt_wiz_init(void);
extern void xt_wiz_set_rxtx_buf_size(uint8_t *p_rx, uint8_t *p_tx);
extern void xt_wiz_set_retx_time(uint16_t x100us);
extern void xt_wiz_set_retx_cnt(uint8_t retry);
extern void xt_wiz_set_mac(uint8_t *p_mac);
extern void xt_wiz_set_ip(uint8_t *p_ip);
extern void xt_wiz_set_sn(uint8_t *p_sn);
extern void xt_wiz_set_gw(uint8_t *p_gw);
extern void xt_wiz_get_mac(uint8_t *p_mac);
extern void xt_wiz_get_ip(uint8_t *p_ip);
extern void xt_wiz_get_sn(uint8_t *p_sn);
extern void xt_wiz_get_gw(uint8_t *p_gw);
extern uint8_t xt_wiz_get_link(void);
extern void xt_wiz_dhcp_init(void);
extern uint8_t xt_wiz_dhcp_run(void);
extern void xt_wiz_dhcp_timer(uint32_t ms);
extern void xt_wiz_dhcp_reset(void);
extern void xt_wiz_ipc_init(void);
extern void xt_wiz_thread_init(void);

//供给[socket.c]模块使用
extern uint8_t xt_wiz_socket_rst_chk(uint8_t s);
extern void xt_wiz_waite_sta(xt_wizchip_t *pwt, uint8_t s, uint8_t fixed, uint8_t max);
extern uint8_t xt_wiz_waite_chk(xt_wizchip_t *pwt, uint8_t s, uint8_t ver, uint8_t max);
extern uint8_t xt_wiz_waite_end(xt_wizchip_t *pwt, uint8_t s);

//供给[应用程序]使用
extern void xt_socket_ot_rst(uint8_t s);
extern void xt_socket_ot_set(uint8_t s, XT_WIZ_OS_TICK_T ostick, uint8_t flag);
extern uint16_t xt_socket_recv_chk(uint8_t s);
extern uint8_t xt_socket_chk(uint8_t s, uint8_t protocol, uint8_t server);

#ifdef __cplusplus
	}
#endif
