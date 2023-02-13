/**
  * @file  xt_ir_send.h
  * @brief ���ⷢ�ͷ���ģ��
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-16     o2ospring    ԭʼ�汾
  */
#include <stdint.h> //////////////////////// <- ʹ�õ����ݶ��壬��: int8_t, uint32_t ��
#include <string.h> //////////////////////// <- ʹ�õ��ַ�������: strcpy(), memcpy() ��
#include "rtthread.h" ////////////////////// <- ʹ��RT-Thread����ϵͳ
#include "rthw.h" ////////////////////////// <- ʹ��RT-Thread����ϵͳ

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ �������� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#define XT_IRSEND_SUM                  1                                  //���ⷢ��ͨ��������Ĭ��:1����Ϊ��ռ䷢�ͺ���ụ����ż���ͬ�ز�����,���ԵͲ�Ӳ��һ��ֻ֧��1ͨ�����ͣ�
#define XT_IRSEND_HW_DRIVERS_EN        1                                  //�Ƿ�ʹ�ñ�ģ���Դ�Ӳ��������0:��ʹ��,1:STM32F1xx-PWM+DMA��
#define xt_irsend_printf(...)          rt_kprintf("irsend:" __VA_ARGS__)  //�쳣��Ϣ��ӡ��Ŀǰ��û�õ��ɱ���������������޸ı��к꼴��֧��C89�﷨��

#define XT_IRSEND_VARIAB()             register rt_base_t level;          //Ӳ������:ʹ�õ��ı�������
#define XT_IRSEND_LOCKED()             level = rt_hw_interrupt_disable()  //Ӳ������:[��]�ж��ܿ���
#define XT_IRSEND_UNLOCK()             rt_hw_interrupt_enable(level)      //Ӳ������:[��]�ж��ܿ���

#define XT_IRSEND_TASK_LOCKED()        rt_enter_critical()                //���񻥳�:[����]����
#define XT_IRSEND_TASK_UNLOCK()        rt_exit_critical()                 //���񻥳�:[�˳�]����

#define XT_IRSEND_OS_INT_ENTER()       rt_interrupt_enter()               //��֪����ϵͳ[����]�ж�
#define XT_IRSEND_OS_INT_EXIT()        rt_interrupt_leave()               //��֪����ϵͳ[�˳�]�ж�

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ �������� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

typedef uint16_t (*xt_irsend_decode_fn_t)(void *pob_tmp, uint16_t *p_code, uint16_t *p_step);
typedef struct xt_irsend_obj_
{
	uint32_t end_us;                   //���������ԡ����̶��ڷ���һ��������ǿ������ʱ��,Ϊ��һ���������������׼����0:������ʱ��,��500000,��λ:uS��
	uint16_t *p_send_buf;              //���������ԡ������ͻ��壨�������Ϊ0������ݵ�λ:ir_xus����ÿ�����ݵ�[bit0]ͬʱ�����Ƿ����ز���־,bit0=1:��ʾ�˸�����Ϊ���ز�ʱ�䣩
	uint16_t send_buf_size;            //���������ԡ������ͻ����С����λ:�ֽڣ�
	uint8_t  ir_khz;                   //���������ԡ��������ز�Ƶ�ʣ�һ��:38KHz,��30KHz,��λ:KHz��
	uint8_t  ir_xus;                   //���������ԡ����������ݵ�λ���磺4��ʾ��λΪ4us,�Ƽ�:1-4us��
	uint8_t  ir_num;                   //���������ԡ������ⷢ��ͨ����ţ�0:��1ͨ��...��
	uint8_t  send_run_flag;            //������״̬������������֮�б�־��0:û�������ͻ�ǰ���ѷ���,1:׼������,2:���������ͣ�
	uint16_t send_run_ver;             //������״̬���������汾�ţ����ڼ���������ͺ���������;���ر�
	uint16_t send_cnt;                 //������״̬�������͵�ƽ�źż�����1:�ѷ���һ����
	uint16_t send_sum;                 //������״̬�������͵�ƽ�ź�������1:��1��ԭʼ�룩
	
	xt_irsend_decode_fn_t p_decode_fn; //���������ԡ������ж��Ｔʱ��ѹ��ʱ���뷢�ͣ����(*p_step=0)��ʼ,�䷵�ظ�8λʱ�䵥λ,��8λ�ز�Ƶ��,
	uint32_t decode_tmp[1];            //���������ԡ�����������Ӧ�ý�ѹ����Ҫ����䱾����ռ��С��      ����(*p_step==0xFFFF)��ʾ���һ���룩
	
	void (*p_irsend_open_fn)(const struct xt_irsend_obj_ *pob);     //��Ӧ�ò���񡿣����ⷢ�ͷ���ɹ���Эͬ���������������������ϲ�Ӧ�ñ�־��
	void (*p_irsend_close_fn)(const struct xt_irsend_obj_ *pob);    //��Ӧ�ò���񡿣����ⷢ�ͷ���ɹ��ر�Эͬ���������������������ϲ�Ӧ�ñ�־��
	void (*p_irsend_complete_fn)(const struct xt_irsend_obj_ *pob); //��Ӧ�ò���񡿣���ɷ��͵�֪ͨ���������ж���֪ͨ��
	
	void (*p_dv_wave_fn)(struct xt_irsend_obj_ *p_ob);              //����������񡿣�Ϊ[Ӳ����]�ж��ṩ����
	
	int  (*p_hw_open_fn)(struct xt_irsend_obj_ *p_ob);              //��Ӳ������񡿣���Ӳ�������ӿ��Ծ�̬��ʽ�ṩ������[������]�Խ�[Ӳ����]��ʼͨ�������������ṩ�����Խӿڣ�
	void (*p_hw_close_fn)(struct xt_irsend_obj_ *p_ob);             //��Ӳ������񡿣��ر�Ӳ��
	void (*p_hw_putd_before_fn)(uint8_t khz);                       //��Ӳ������񡿣�֪ͨ[Ӳ����]����ǰ׼����khz:�����ز�Ƶ��,��λ:KHz��
	void (*p_hw_putd_a_fn)(uint32_t us, uint8_t f);                 //��Ӳ������񡿣��ж�������[Ӳ����]ȥ����һ�����ز��루us:���ز�ʱ��,f=0:��1����,1:��;1����,2:���1���룩
	void (*p_hw_putd_b_fn)(uint32_t us, uint8_t f);                 //��Ӳ������񡿣��ж�������[Ӳ����]ȥ����һ�����ز��루us:���ز�ʱ��,f=0:��1����,1:��;1����,2:���1���룩
	void (*p_hw_putd_end_fn)(void);                                 //��Ӳ������񡿣��ж���֪ͨ[Ӳ����]�ѷ��������һ����
}xt_irsend_obj_t;

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ �������� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

//��̬����Ӳ����
//extern int xt_irsend_hw_open(xt_irsend_obj_t *p_ob);

//ΪӦ���ṩ����
extern int xt_irsend_open(xt_irsend_obj_t *p_ob);
extern int xt_irsend_close(xt_irsend_obj_t *p_ob);
extern int xt_irsend_send(xt_irsend_obj_t *p_ob, const uint16_t *pd, uint16_t size, uint8_t xus, uint8_t khz);
extern int xt_irsend_decode_send(xt_irsend_obj_t *p_ob, const uint8_t *pd, uint16_t size, const xt_irsend_decode_fn_t p_fn);
extern int xt_irsend_state(xt_irsend_obj_t *p_ob);

#ifdef __cplusplus
	}
#endif
