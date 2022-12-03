/**
  * @file  xt_scom.h
  * @brief 串行通信服务模块
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-27     o2ospring    原始版本
  */
#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#include <string.h> //////////////////////// <- 使用的字符处理，如: strcpy(), memcpy() 等
#include "board.h"   /////////////////////// <- 工程所有硬件资源管理头文件!!!!!!!!!!!!!!!
#include "rtthread.h" ////////////////////// <- 使用RT-Thread操作系统
#include "rthw.h" ////////////////////////// <- 使用RT-Thread操作系统

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 参数配置 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#define XT_SCOM_SUM                 1                                 //串行通信通道总数（由实际硬件决定，相关通道可以是TTL串口、RS232、RS485等总线）
#define XT_SCOM_HW_DRIVERS_EN       1                                 //是否使用本模块自带硬件驱动（0:不使用,1:串口+独立定时器,2:串口+公共定时）
#define xt_scom_printf(...)         rt_kprintf(__VA_ARGS__)           //异常信息打印（目前还没用到可变参数，可以稍作修改本行宏即可支持C89语法）

#define XT_SCOM_VARIAB()            register rt_base_t level;         //硬件互斥:使用到的变量声明
#define XT_SCOM_LOCKED()            level = rt_hw_interrupt_disable() //硬件互斥:[关]中断总开关
#define XT_SCOM_UNLOCK()            rt_hw_interrupt_enable(level)     //硬件互斥:[开]中断总开关

#define XT_SCOM_TASK_LOCKED()       rt_enter_critical()               //任务互斥:[进入]互斥
#define XT_SCOM_TASK_UNLOCK()       rt_exit_critical()                //任务互斥:[退出]互斥

#define XT_SCOM_OS_INT_ENTER()      rt_interrupt_enter()              //告知操作系统[进入]中断
#define XT_SCOM_OS_INT_EXIT()       rt_interrupt_leave()              //告知操作系统[退出]中断

#define XT_SCOM_SEND_DELAY_US(us)   bsp_delay0us125(us*8UL)           //加入接收与发送间隔延时可加强通讯稳定性，一般为5us左右

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 数据类型 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#define XT_SCOM_TYPE_DATA_FRAME     0        //串行通信为〖数据帧〗
#define XT_SCOM_TYPE_DATA_STREAM    1        //串行通信为〖数据流〗
#define XT_SCOM_TYPE_SUM            2        //类型总数

typedef struct xt_scom_obj_
{
	uint32_t baud_rate;       //【串口属性】：通讯波特率（1200,2400,4800,9600,14400,19200,38400,57600,115200,128000,256000bps等）
	uint8_t  stop_bits   :4;  //【串口属性】：停止位（1:1位,2:2位）
	uint8_t  parity_bits :4;  //【串口属性】：校验位（0:无,1:奇,2:偶）
	uint8_t  data_bits;       //【串口属性】：数据位（8:8位）
	uint8_t  scom_num;        //【串口属性】：串行通信通道号（驱动层通道号）（＜XT_SCOM_SUM）
	
	uint8_t  len_offset;      //【协议属性】：〖数据帧〗接收长度码位置偏移（包含起始码在内整帧位置偏移，例如:5->整帧第6字节，0xFF:无效）
	uint8_t  len_arithm;      //【协议属性】：〖数据帧〗接收长度码整帧总长算法（5:5+长度码值=整帧总长,0xFF:只能超时分帧）/当{长度码位置偏移=0xFF}时表示接收固定长度
	uint8_t  section_code[2]; //【协议属性】：〖数据帧〗接收起始码（例如:{0xFF,0x55}）        /〖数据流〗接收结束码（例如:<CR><LF>）
	uint8_t  section_mode;    //【协议属性】：〖数据帧〗接收起始码大小（0:无,1:1字节,2:2字节）/〖数据流〗接收结束码模式（0:无,1:1字节结束码,2:2字节结束码,3:两字节任一结束码）
	uint16_t section_us;      //【协议属性】：分帧重置时间（单位:us，0:无效；可用于超时分帧或超时重置接收或接收完成等）
	uint8_t  rx_tim_flag;     //【运行状态】：是否要定时计数标志（0:分帧重置时间无需计时）
	uint8_t  tx_run_flag;     //【运行状态】：正处于发送之中标志（0:没启动发送,1:准备发送,2:已启动发送）
	uint8_t  *p_rx_buf;       //【协议属性】：接收缓冲（★绝不能为0★）
	uint8_t  *p_tx_buf;       //【协议属性】：发送缓冲（★绝不能为0★）
	uint16_t rx_buf_size;     //【协议属性】：接收缓冲大小（0:不支持接收，★及【硬件层】可强制设置为0★）
	uint16_t tx_buf_size;     //【协议属性】：发送缓冲大小（0:不支持发送，★及【硬件层】可强制设置为0★）
	uint16_t rx_cnt;          //【运行状态】：接收计数器（1:收到1字节数据）
	uint16_t tx_cnt;          //【运行状态】：发送计数器（1:正发1字节数据）
	uint16_t tx_sum;          //【运行状态】：发送总大小
	uint16_t tx_run_ver;      //【运行状态】：操作版本号，用于检测启动发送函数操作中途被关闭
	
	void (*p_scom_open_fn)(const struct xt_scom_obj_ *pob);              //【应用层服务】：串行通信服务成功打开协同操作函数（常用于设置上层应用标志）
	void (*p_scom_close_fn)(const struct xt_scom_obj_ *pob);             //【应用层服务】：串行通信服务成功关闭协同操作函数（常用于设置上层应用标志）
	void (*p_tx_complete_fn)(const struct xt_scom_obj_ *pob);            //【应用层服务】：中断中完成发送的通知函数        （内参传递:void）
	int  (*p_rx_data1_fn)(const struct xt_scom_obj_ *pob);               //【应用层服务】：中断中接收到第一字节数据通知函数（内参传递:pob->p_rx_buf）
	int  (*p_rx_data_fn)(const struct xt_scom_obj_ *pob, uint16_t size); //【应用层服务】：中断中接收到整一组数据的传递函数（内参传递:pob->p_rx_buf, size）
	
	void (*p_dv_uart_rx_reset)(struct xt_scom_obj_ *pob);                //【驱动层服务】：为[硬件层]中断提供调用-串口接收重置操作函数
	void (*p_dv_uart_tx_fn)(struct xt_scom_obj_ *pob);                   //【驱动层服务】：为[硬件层]中断提供调用-串口发送中断操作函数
	void (*p_dv_uart_rx_fn)(struct xt_scom_obj_ *pob);                   //【驱动层服务】：为[硬件层]中断提供调用-串口接收中断操作函数
	void (*p_dv_time_rx_fn)(struct xt_scom_obj_ *pob);                   //【驱动层服务】：为[硬件层]中断提供调用-接收定时中断操作函数
	
	int  (*p_hw_open_fn)(struct xt_scom_obj_ *p_ob);                     //【硬件层服务】：打开硬件（本接口以静态形式提供，它是[驱动层]对接[硬件层]超始通道，并由它来提供其它对接口）
	void (*p_hw_close_fn)(struct xt_scom_obj_ *p_ob);                    //【硬件层服务】：关闭硬件
	void (*p_hw_tx_putc_null_fn)(void);                                  //【硬件层服务】：要求[硬件层]启动发送空中断（★如果硬件不支持发送空中断,则设置为0★）
	void (*p_hw_tx_putc_fn)(uint16_t d, uint8_t f);                      //【硬件层服务】：中断中启动[硬件层]发送一字节（0:第1字节,1:中途1字节,2:最后1字节）
	void (*p_hw_tx_putc_end_fn)(void);                                   //【硬件层服务】：中断中通知[硬件层]已发送完最后一字节数据
	int  (*p_hw_rx_getc_fn)(void);                                       //【硬件层服务】：中断中获取[硬件层]接收到一字节数据
	uint8_t (*p_hw_rx_overtime_set_fn)(uint16_t us);                     //【硬件层服务】：中断中要求[硬件层]设置接收超时时间（返回0:表明被串口中断处理清除了，则无需处理超时事件）
}xt_scom_obj_t;

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 操作函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

//静态调用硬件层
//extern int xt_scom_hw_open(xt_scom_obj_t *p_ob);

//为应用提供服务
extern int xt_scom_open(xt_scom_obj_t *p_ob, uint8_t scom_type);
extern int xt_scom_close(xt_scom_obj_t *p_ob);
extern int xt_scom_send(xt_scom_obj_t *p_ob, const uint8_t *pb, uint16_t size, uint8_t delay);
extern void xt_scom_recv_reset(xt_scom_obj_t *p_ob);

#ifdef __cplusplus
	}
#endif
