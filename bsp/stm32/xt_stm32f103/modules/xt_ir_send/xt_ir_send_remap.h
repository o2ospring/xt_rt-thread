/**
  * @file  xt_ir_send.h
  * @brief 红外发送服务模块
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-16     o2ospring    原始版本
  */
#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#include <string.h> //////////////////////// <- 使用的字符处理，如: strcpy(), memcpy() 等
#include "rtthread.h" ////////////////////// <- 使用RT-Thread操作系统
#include "rthw.h" ////////////////////////// <- 使用RT-Thread操作系统

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 参数配置 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#define XT_IRSEND_SUM                  1                                  //红外发送通道总数（默认:1，因为向空间发送红外会互相干扰及不同载波问题,所以低层硬件一般只支持1通道发送）
#define XT_IRSEND_HW_DRIVERS_EN        1                                  //是否使用本模块自带硬件驱动（0:不使用,1:STM32F1xx-PWM+DMA）
#define xt_irsend_printf(...)          rt_kprintf("irsend:" __VA_ARGS__)  //异常信息打印（目前还没用到可变参数，可以稍作修改本行宏即可支持C89语法）

#define XT_IRSEND_VARIAB()             register rt_base_t level;          //硬件互斥:使用到的变量声明
#define XT_IRSEND_LOCKED()             level = rt_hw_interrupt_disable()  //硬件互斥:[关]中断总开关
#define XT_IRSEND_UNLOCK()             rt_hw_interrupt_enable(level)      //硬件互斥:[开]中断总开关

#define XT_IRSEND_TASK_LOCKED()        rt_enter_critical()                //任务互斥:[进入]互斥
#define XT_IRSEND_TASK_UNLOCK()        rt_exit_critical()                 //任务互斥:[退出]互斥

#define XT_IRSEND_OS_INT_ENTER()       rt_interrupt_enter()               //告知操作系统[进入]中断
#define XT_IRSEND_OS_INT_EXIT()        rt_interrupt_leave()               //告知操作系统[退出]中断

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 数据类型 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

typedef uint16_t (*xt_irsend_decode_fn_t)(void *pob_tmp, uint16_t *p_code, uint16_t *p_step);
typedef struct xt_irsend_obj_
{
	uint32_t end_us;                   //【红外属性】：固定在发送一组红外码后强插入间隔时间,为下一组红外码正常发送准备（0:不插入时间,≤500000,单位:uS）
	uint16_t *p_send_buf;              //【红外属性】：发送缓冲（★绝不能为0★）（数据单位:ir_xus）（每个数据的[bit0]同时用作是否有载波标志,bit0=1:表示此个数据为有载波时间）
	uint16_t send_buf_size;            //【红外属性】：发送缓冲大小（单位:字节）
	uint8_t  ir_khz;                   //【红外属性】：红外载波频率（一般:38KHz,≥30KHz,单位:KHz）
	uint8_t  ir_xus;                   //【红外属性】：红外数据单位（如：4表示单位为4us,推荐:1-4us）
	uint8_t  ir_num;                   //【红外属性】：红外发送通道编号（0:第1通道...）
	uint8_t  send_run_flag;            //【运行状态】：正处发送之中标志（0:没启动发送或前次已发完,1:准备发送,2:已启动发送）
	uint16_t send_run_ver;             //【运行状态】：操作版本号，用于检测启动发送函数操作中途被关闭
	uint16_t send_cnt;                 //【运行状态】：发送电平信号计数（1:已发送一个）
	uint16_t send_sum;                 //【运行状态】：发送电平信号总数（1:共1个原始码）
	
	xt_irsend_decode_fn_t p_decode_fn; //【红外属性】：在中断里即时解压出时间码发送（入口(*p_step=0)表开始,其返回高8位时间单位,低8位载波频率,
	uint32_t decode_tmp[1];            //【红外属性】：根据上行应用解压函数要求分配本缓存空间大小。      返回(*p_step==0xFFFF)表示最后一个码）
	
	void (*p_irsend_open_fn)(const struct xt_irsend_obj_ *pob);     //【应用层服务】：红外发送服务成功打开协同操作函数（常用于设置上层应用标志）
	void (*p_irsend_close_fn)(const struct xt_irsend_obj_ *pob);    //【应用层服务】：红外发送服务成功关闭协同操作函数（常用于设置上层应用标志）
	void (*p_irsend_complete_fn)(const struct xt_irsend_obj_ *pob); //【应用层服务】：完成发送的通知函数（在中断中通知）
	
	void (*p_dv_wave_fn)(struct xt_irsend_obj_ *p_ob);              //【驱动层服务】：为[硬件层]中断提供调用
	
	int  (*p_hw_open_fn)(struct xt_irsend_obj_ *p_ob);              //【硬件层服务】：打开硬件（本接口以静态形式提供，它是[驱动层]对接[硬件层]起始通道，并由它来提供其它对接口）
	void (*p_hw_close_fn)(struct xt_irsend_obj_ *p_ob);             //【硬件层服务】：关闭硬件
	void (*p_hw_putd_before_fn)(uint8_t khz);                       //【硬件层服务】：通知[硬件层]发送前准备（khz:红外载波频率,单位:KHz）
	void (*p_hw_putd_a_fn)(uint32_t us, uint8_t f);                 //【硬件层服务】：中断中启动[硬件层]去发送一个有载波码（us:有载波时间,f=0:第1个码,1:中途1个码,2:最后1个码）
	void (*p_hw_putd_b_fn)(uint32_t us, uint8_t f);                 //【硬件层服务】：中断中启动[硬件层]去发送一个无载波码（us:无载波时间,f=0:第1个码,1:中途1个码,2:最后1个码）
	void (*p_hw_putd_end_fn)(void);                                 //【硬件层服务】：中断中通知[硬件层]已发送完最后一个码
}xt_irsend_obj_t;

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 操作函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

//静态调用硬件层
//extern int xt_irsend_hw_open(xt_irsend_obj_t *p_ob);

//为应用提供服务
extern int xt_irsend_open(xt_irsend_obj_t *p_ob);
extern int xt_irsend_close(xt_irsend_obj_t *p_ob);
extern int xt_irsend_send(xt_irsend_obj_t *p_ob, const uint16_t *pd, uint16_t size, uint8_t xus, uint8_t khz);
extern int xt_irsend_decode_send(xt_irsend_obj_t *p_ob, const uint8_t *pd, uint16_t size, const xt_irsend_decode_fn_t p_fn);
extern int xt_irsend_state(xt_irsend_obj_t *p_ob);

#ifdef __cplusplus
	}
#endif
