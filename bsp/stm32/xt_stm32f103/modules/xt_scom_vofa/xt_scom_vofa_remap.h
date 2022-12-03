/**
  * @file  xt_scom_vofa.h
  * @brief ������������ʾ������VOFA+ ���ؼӣ�
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-12-03     o2ospring    ԭʼ�汾
  */
#include <stdint.h> //////////////////////// <- ʹ�õ����ݶ��壬��: int8_t, uint32_t ��
#include <string.h> //////////////////////// <- ʹ�õ��ַ�������: strcpy(), memcpy() ��
#include "rtthread.h" ////////////////////// <- ʹ��RT-Thread����ϵͳ
#include "xt_scom.h" /////////////////////// <- ��������ͨ�ŷ���ģ��!!!!!!!!!!!!!!!!!!!!!

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ �������� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#define XT_SCOMVOFA_SCOM_NUM        0                                   //����ͨѶ����ͨ�����
#define XT_SCOMVOFA_BAUD_RATE       9600  /*����[VOFA+]���þ���*/       //����ͨѶ������, ��:9600,115200
#define XT_SCOMVOFA_CH_SUM          4     /*Ŀǰ[VOFA+]û������*/       //ʾ����ͨ������
#define XT_SCOMVOFA_BIG_ENDIAN_SW   0     /*��Դ�˴������ſ���*/      //������˴�����
#define xt_scomvofa_printf(...)     rt_kprintf(__VA_ARGS__)             //�쳣��Ϣ��ӡ��Ŀǰ��û�õ��ɱ���������������޸ı��к꼴��֧��C89�﷨��

#if (defined XT_SCOM_VOFA_C__) && (XT_APP_SCOMVOFA_EN == XT_DEF_ENABLED)
struct rt_mutex                     xt_scomvofa_mutex;                                    //ȫ��-����������
#define XT_SCOMVOFA_MUTEX_INIT()    rt_mutex_init(&xt_scomvofa_mutex, "xt_scomvofa_mutex", RT_IPC_FLAG_FIFO)
#define XT_SCOMVOFA_MUTEX_LOCKED()  rt_mutex_take(&xt_scomvofa_mutex, RT_WAITING_FOREVER) //����-����ʹ��
#define XT_SCOMVOFA_MUTEX_UNLOCK()  rt_mutex_release(&xt_scomvofa_mutex)                  //����-�����˳�
struct rt_semaphore                 xt_scomvofa_sem;                                      //ȫ��-�ź�������
#define XT_SCOMVOFA_TX_SEM_INIT()   rt_sem_init(&xt_scomvofa_sem, "xt_scomvofa_sem", 0, RT_IPC_FLAG_FIFO)
#define XT_SCOMVOFA_TX_SEM_RESET()  rt_sem_control(&xt_scomvofa_sem, RT_IPC_CMD_RESET, 0) //����-�����ź�
#define XT_SCOMVOFA_TX_SEM_TAKE()   rt_sem_take(&xt_scomvofa_sem, RT_WAITING_FOREVER)     //����-�ȴ����
#define XT_SCOMVOFA_TX_SEM_SEND()   rt_sem_release(&xt_scomvofa_sem)                      //����-��ɴ���
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ �������� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void xt_scomvofa_init(void);
extern int xt_scomvofa_1ch_put(uint8_t ch_n, float chx);
extern int xt_scomvofa_4ch_put(uint8_t ch_f, float ch1, float ch2, float ch3, float ch4);
extern int xt_scomvofa_xch_put(uint8_t ch_s, float *p_ch);

#ifdef __cplusplus
	}
#endif
