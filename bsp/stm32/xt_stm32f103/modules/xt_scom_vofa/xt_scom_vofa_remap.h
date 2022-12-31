/**
  * @file  xt_scom_vofa.h
  * @brief 串口虚拟数字示波器（VOFA+ 伏特加）
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-12-03     o2ospring    原始版本
  * 2022-12-15     o2ospring    增加示波器发来命令的处理支持
  */
#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#include <string.h> //////////////////////// <- 使用的字符处理，如: strcpy(), memcpy() 等
#include "rtthread.h" ////////////////////// <- 使用RT-Thread操作系统
#include "xt_scom.h" /////////////////////// <- 依赖串行通信服务模块!!!!!!!!!!!!!!!!!!!!!

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 参数配置 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#define XT_SCOMVOFA_SCOM_NUM        0                                   //串口通讯服务通道编号
#define XT_SCOMVOFA_BAUD_RATE       9600  /*根据[VOFA+]配置决定*/       //串口通讯波特率, 如:9600,115200
#define XT_SCOMVOFA_P_HW_OPEN_FN    0                                   //本服务模块提供的硬件驱动程序（0:不提供）
#define XT_SCOMVOFA_CH_SUM          4     /*目前[VOFA+]没有限制*/       //示波器通道总数（4:共4路）
#define XT_SCOMVOFA_BIG_ENDIAN_SW   0     /*针对大端处理器才开启*/      //开启大端处理器（0:禁用）
#define XT_SCOMVOFA_CMD_MAX         100   /*只支持[rt-thread]系统*/     //示波器传来的字符控制命令的大小限制（0:关闭支持）
#define xt_scomvofa_printf(...)     rt_kprintf("scomvofa:" __VA_ARGS__) //异常信息打印（目前还没用到可变参数，可以稍作修改本行宏即可支持C89语法）

#if (defined XT_SCOM_VOFA_C__) && (XT_APP_SCOMVOFA_EN == XT_DEF_ENABLED)
struct rt_mutex                     xt_scomvofa_mutex;                                    //全局-互斥锁声明
#define XT_SCOMVOFA_MUTEX_INIT()    rt_mutex_init(&xt_scomvofa_mutex, "xt_scomvofa_mutex", RT_IPC_FLAG_FIFO)
#define XT_SCOMVOFA_MUTEX_LOCKED()  rt_mutex_take(&xt_scomvofa_mutex, RT_WAITING_FOREVER) //程序-互斥使能
#define XT_SCOMVOFA_MUTEX_UNLOCK()  rt_mutex_release(&xt_scomvofa_mutex)                  //程序-互斥退出
struct rt_semaphore                 xt_scomvofa_sem;                                      //全局-信号量声明
#define XT_SCOMVOFA_TX_SEM_INIT()   rt_sem_init(&xt_scomvofa_sem, "xt_scomvofa_sem", 0, RT_IPC_FLAG_FIFO)
#define XT_SCOMVOFA_TX_SEM_RESET()  rt_sem_control(&xt_scomvofa_sem, RT_IPC_CMD_RESET, 0) //发送-重置信号
#define XT_SCOMVOFA_TX_SEM_TAKE()   rt_sem_take(&xt_scomvofa_sem, RT_WAITING_FOREVER)     //发送-等待完成
#define XT_SCOMVOFA_TX_SEM_SEND()   rt_sem_release(&xt_scomvofa_sem)                      //发送-完成触发
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 操作函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void xt_scomvofa_init(void); //上电初始化
extern int xt_scomvofa_1ch_put(uint8_t ch_n, float chx);
extern int xt_scomvofa_4ch_put(uint8_t ch_f, float ch1, float ch2, float ch3, float ch4);
extern int xt_scomvofa_xch_put(uint8_t ch_s, float *p_ch, uint8_t s_ch);
extern void xt_scomvofa_cmd_run(void); //定时循环调用即可

#ifdef __cplusplus
	}
#endif
