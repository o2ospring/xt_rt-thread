/**
  * @file  xt_scom_sds.h
  * @brief 串口虚拟数字示波器（Visual Scope：Serial Digital Scope）
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-12-01     o2ospring    原始版本
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

#define XT_SCOMSDS_SCOM_NUM         0                                   //串口通讯服务通道编号
#define XT_SCOMSDS_BAUD_RATE        9600  /*由VisualScope软件配置决定*/ //串口通讯波特率, 如:9600,115200
#define XT_SCOMSDS_P_HW_OPEN_FN     0                                   //本服务模块提供的硬件驱动程序（0:不提供）
#define xt_scomsds_printf(...)      rt_kprintf("scomsds:" __VA_ARGS__)  //异常信息打印（目前还没用到可变参数，可以稍作修改本行宏即可支持C89语法）

#if (defined XT_SCOM_SDS_C__) && (XT_APP_SCOMSDS_EN == XT_DEF_ENABLED)
#define XT_SCOMSDS_CRC16(pd,sz)     xt_scomsds_crc16(pd,sz)                              //校验-CRC16
struct rt_mutex                     xt_scomsds_mutex;                                    //全局-互斥锁声明
#define XT_SCOMSDS_MUTEX_INIT()     rt_mutex_init(&xt_scomsds_mutex, "xt_scomsds_mutex", RT_IPC_FLAG_FIFO)
#define XT_SCOMSDS_MUTEX_LOCKED()   rt_mutex_take(&xt_scomsds_mutex, RT_WAITING_FOREVER) //程序-互斥使能
#define XT_SCOMSDS_MUTEX_UNLOCK()   rt_mutex_release(&xt_scomsds_mutex)                  //程序-互斥退出
struct rt_semaphore                 xt_scomsds_sem;                                      //全局-信号量声明
#define XT_SCOMSDS_TX_SEM_INIT()    rt_sem_init(&xt_scomsds_sem, "xt_scomsds_sem", 0, RT_IPC_FLAG_FIFO)
#define XT_SCOMSDS_TX_SEM_RESET()   rt_sem_control(&xt_scomsds_sem, RT_IPC_CMD_RESET, 0) //发送-重置信号
#define XT_SCOMSDS_TX_SEM_TAKE()    rt_sem_take(&xt_scomsds_sem, RT_WAITING_FOREVER)     //发送-等待完成
#define XT_SCOMSDS_TX_SEM_SEND()    rt_sem_release(&xt_scomsds_sem)                      //发送-完成触发
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 操作函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void xt_scomsds_init(void);
extern int xt_scomsds_1ch_put(uint8_t ch_n, int16_t chx);
extern int xt_scomsds_4ch_put(uint8_t ch_f, int16_t ch1, int16_t ch2, int16_t ch3, int16_t ch4);
extern int xt_scomsds_xch_put(uint8_t ch_s, int16_t *p_ch, uint8_t s_ch);

#ifdef __cplusplus
	}
#endif
