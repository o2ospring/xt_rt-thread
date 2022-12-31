/**
  * @file  xt_cef2.h
  * @brief �����¼���־����ģ�飨Control Event Flag��
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-12-05     o2ospring    ԭʼ�汾
  */
#include <stdint.h> //////////////////////// <- ʹ�õ����ݶ��壬��: int8_t, uint32_t ��
#ifdef XT_CEF2_C__
#include <string.h> //////////////////////// <- ʹ�õ��ַ�������: strcpy(), memcpy() ��
#include "rtthread.h" ////////////////////// <- ʹ��RT-Thread����ϵͳ
#include "rthw.h" ////////////////////////// <- ʹ��RT-Thread����ϵͳ
#endif

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ �������� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#define XT_CEF2_VARIAB()             register rt_base_t level;              //Ӳ������:ʹ�õ��ı�������
#define XT_CEF2_LOCKED()             level = rt_hw_interrupt_disable()      //Ӳ������:[��]�ж��ܿ���
#define XT_CEF2_UNLOCK()             rt_hw_interrupt_enable(level)          //Ӳ������:[��]�ж��ܿ���

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ �������� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void xt_cef2_init(uint8_t *f, uint8_t size);                         //��ȫ��00������[����]���������־����ʼ����
extern void xt_cef2_reset_flag(uint8_t *f, uint8_t size, uint8_t i);        //��XX��00������[����]���������־
extern void xt_cef2_set_new_flag(uint8_t *f, uint8_t size, uint8_t i);      //��XX��1X��[����]������λ���µĿ��ƣ�
extern uint8_t xt_cef2_is_goto_run(uint8_t *f, uint8_t size, uint8_t i);    //��10��01��[����]�����λ��ִ�п��ƣ�
extern uint8_t xt_cef2_set_end_flag(uint8_t *f, uint8_t size, uint8_t i);   //��X1��X0��[����]�����ɣ�������ɣ�
extern uint8_t xt_cef2_set_retry_flag(uint8_t *f, uint8_t size, uint8_t i); //��X1��10��[����]������ã��������ã�
extern uint8_t xt_cef2_is_new(uint8_t *f, uint8_t size, uint8_t i);         //��1X��    ��չ���ܣ��ж�[����]�����Ƿ���Ч
extern uint8_t xt_cef2_is_run(uint8_t *f, uint8_t size, uint8_t i);         //��X1��    ��չ���ܣ��ж�[����]����Ƿ���Ч
extern uint8_t xt_cef2_is_nul(uint8_t *f, uint8_t size, uint8_t i);         //��00��    ��չ���ܣ��ж�[����]��������Ƿ�[��Ч]
extern uint8_t xt_cef2_is_any_new(uint8_t *f, uint8_t size);                //����һ1X����չ���ܣ��ж�[��һ]�����Ƿ���Ч
extern uint8_t xt_cef2_is_any_run(uint8_t *f, uint8_t size);                //����һX1����չ���ܣ��ж�[��һ]����Ƿ���Ч
extern uint8_t xt_cef2_is_any_tag(uint8_t *f, uint8_t size);                //����ȫ00����չ���ܣ��ж�[��һ]��������Ƿ���Ч

#ifdef __cplusplus
	}
#endif
