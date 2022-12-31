/**
  * @file  xt_cef2.h
  * @brief 控制事件标志服务模块（Control Event Flag）
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-12-05     o2ospring    原始版本
  */
#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#ifdef XT_CEF2_C__
#include <string.h> //////////////////////// <- 使用的字符处理，如: strcpy(), memcpy() 等
#include "rtthread.h" ////////////////////// <- 使用RT-Thread操作系统
#include "rthw.h" ////////////////////////// <- 使用RT-Thread操作系统
#endif

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 参数配置 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#define XT_CEF2_VARIAB()             register rt_base_t level;              //硬件互斥:使用到的变量声明
#define XT_CEF2_LOCKED()             level = rt_hw_interrupt_disable()      //硬件互斥:[关]中断总开关
#define XT_CEF2_UNLOCK()             rt_hw_interrupt_enable(level)          //硬件互斥:[开]中断总开关

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 操作函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void xt_cef2_init(uint8_t *f, uint8_t size);                         //（全清00）重置[所有]输入输出标志（初始化）
extern void xt_cef2_reset_flag(uint8_t *f, uint8_t size, uint8_t i);        //（XX→00）重置[单个]输入输出标志
extern void xt_cef2_set_new_flag(uint8_t *f, uint8_t size, uint8_t i);      //（XX→1X）[单个]输入置位（新的控制）
extern uint8_t xt_cef2_is_goto_run(uint8_t *f, uint8_t size, uint8_t i);    //（10→01）[单个]输出置位（执行控制）
extern uint8_t xt_cef2_set_end_flag(uint8_t *f, uint8_t size, uint8_t i);   //（X1→X0）[单个]输出完成（控制完成）
extern uint8_t xt_cef2_set_retry_flag(uint8_t *f, uint8_t size, uint8_t i); //（X1→10）[单个]输出重置（控制重置）
extern uint8_t xt_cef2_is_new(uint8_t *f, uint8_t size, uint8_t i);         //（1X）    扩展功能：判断[单个]输入是否有效
extern uint8_t xt_cef2_is_run(uint8_t *f, uint8_t size, uint8_t i);         //（X1）    扩展功能：判断[单个]输出是否有效
extern uint8_t xt_cef2_is_nul(uint8_t *f, uint8_t size, uint8_t i);         //（00）    扩展功能：判断[单个]输入输出是否都[无效]
extern uint8_t xt_cef2_is_any_new(uint8_t *f, uint8_t size);                //（任一1X）扩展功能：判断[任一]输入是否有效
extern uint8_t xt_cef2_is_any_run(uint8_t *f, uint8_t size);                //（任一X1）扩展功能：判断[任一]输出是否有效
extern uint8_t xt_cef2_is_any_tag(uint8_t *f, uint8_t size);                //（非全00）扩展功能：判断[任一]输入输出是否有效

#ifdef __cplusplus
	}
#endif
