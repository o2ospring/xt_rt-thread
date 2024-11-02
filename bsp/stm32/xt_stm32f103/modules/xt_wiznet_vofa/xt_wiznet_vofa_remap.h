/**
  * @file  xt_wiznet_vofa.h
  * @brief UDP������������ʾ������VOFA+ ���ؼӣ�
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-12-16     o2ospring    ԭʼ�汾
  * 2023-05-17     o2ospring    ������[5555]�˿ڹ㲥����IP
  * 2023-11-17     o2ospring    �����ϵ���ͣˢ��ʾ��������
  * 2023-12-16     o2ospring    ���ӿ��޸�������λ���Ķ˿�
  */
#include <stdint.h> //////////////////////// <- ʹ�õ����ݶ��壬��: int8_t, uint32_t ��
#include <string.h> //////////////////////// <- ʹ�õ��ַ�������: strcpy(), memcpy() ��
#include <stdio.h> ///////////////////////// <- ʹ�ñ�׼����������磺sprintf(p,...) ��
#include <stdlib.h> //////////////////////// <- ʹ�õ��ַ�ת�����磺atoi(s) ��
#include "rtthread.h" ////////////////////// <- ʹ��RT-Thread����ϵͳ
#include "xt_wiznet.h" ///////////////////// <- �����������ģ��!!!!!!!!!!!!!!!!!!!!!!!!!

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ �������� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#define XT_WIZVOFA_POWERON_EN       1                                    //�Ƿ��ϵ翪��ʾ������0:��������
#define XT_WIZVOFA_REFRESH_TK       (100/*ms*//(1000/RT_TICK_PER_SECOND))//����ʾ����ˢ��ʱ�䣨0:�ϵ���ͣˢ��,@ϵͳ���ģ�
#define XT_WIZVOFA_SOCKET           (XT_SOCK_SUM - 2)                    //ʹ�õڼ���socket�ӿ�����ʾ����
#define XT_WIZVOFA_CH_SUM           4   /*Ŀǰ[VOFA+]û������*/          //ʾ����ͨ��������4:��4·��
#define XT_WIZVOFA_BIG_ENDIAN_SW    0   /*��Դ�˴������ſ���*/         //������˴�������0:���ã�
#define XT_WIZVOFA_CMD_MAX          100 /*ֻ֧��[rt-thread]ϵͳ*/        //ʾ�����������ַ���������Ĵ�С���ƣ�0:�ر�֧�֣�
#define xt_wizvofa_printf(...)      rt_kprintf("wizvofa:" __VA_ARGS__)   //�쳣��Ϣ��ӡ��Ŀǰ��û�õ��ɱ���������������޸ı��к꼴��֧��C89�﷨��

#define XT_WIZVOFA_VARIAB()         register rt_base_t level;            //���ݻ���:ʹ�õ��ı�������
#define XT_WIZVOFA_LOCKED()         level = rt_hw_interrupt_disable()    //���ݻ���:[��]�ж��ܿ���
#define XT_WIZVOFA_UNLOCK()         rt_hw_interrupt_enable(level)        //���ݻ���:[��]�ж��ܿ���

#if (defined XT_WIZNET_VOFA_C__) && (XT_APP_WIZNETVOFA_EN == XT_DEF_ENABLED)
uint8_t xt_wizvofa_ip[4]          = {192, 168, 3, 222};                  /* VOFA+ʾ�������(�����)��IP */
#endif
#define XT_WIZVOFA_SOCKET_NUM       1003                                 /* VOFA+ʾ�����˼�������UDP�˿�*/
#define XT_WIZVOFA_OS_TICK_T        rt_tick_t                            /* �������ϵͳ���ĵ���������  */
#define XT_WIZVOFA_OS_THREAD_T      rt_thread_t                          /* �������ϵͳ�̵߳���������  */
#define XT_WIZVOFA_OS_TICK_GET()    rt_tick_get()                        /* ��ȡ����ϵͳ�������ļ���ֵ  */
#define XT_WIZVOFA_OS_DLY_TICK(n)   rt_thread_delay(n)                   /* ϵͳ��ʱn������             */
#define XT_WIZVOFA_OS_TICK_LIMIT    10                                   /* �����߳����н���Ƶ������    */
#define XT_WIZVOFA_OS_TICK_OVMAX    (RT_TICK_MAX / 3)                    /* �жϲ���ϵͳ��������ת���ֵ*/
#define XT_WIZVOFA_THREAD_CREATE(p) p = rt_thread_create("xt_wizvofa", xt_wizvofa_thread_entry, 0, 480, 5, 4); \
                                    if (p != RT_NULL) rt_thread_startup(p)
#if (XT_WIZVOFA_REFRESH_TK < 0)
#error "" 
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ �������� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void xt_wizvofa_init(void); //�ϵ��ʼ��
extern void xt_wizvofa_open(void); //�ϵ��ʼ��
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
