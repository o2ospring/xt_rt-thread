/**
  * @file  bsp_stm32f1xx_id.h
  * @brief ����STM32F103ID��������
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    ԭʼ�汾
  */
#ifndef BSP_STM32F1XX_ID_H__
#define BSP_STM32F1XX_ID_H__

#include <stdint.h> //////////////////////// <- ʹ�õ����ݶ��壬��: int8_t, uint32_t ��
#include <string.h> //////////////////////// <- ʹ�õ��ַ�������: strcpy(), memcpy() ��
#include "board.h"   /////////////////////// <- ��������Ӳ����Դ����ͷ�ļ�!!!!!!!!!!!!!!!
#include "bsp_stm32f1xx_crc.h" ///////////// <- ʹ�õ�STM32��Ӳ��CRC

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ �������� ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern int bsp_stm32_id12_cmp(uint8_t *p_dat);  //ע��:������û��ȫ���
extern void bsp_stm32_id12_get(uint8_t *p_buf); //ע��:������û��ȫ���

#if (BSP_CRC_EN & 0x01)   //�õ�STM32��Ӳ��CRC,��Ҫ���ȴ���Ӳ�����⣡
extern void bsp_unique_id_generate(uint8_t *p_buf, uint8_t id_size);
#endif

#ifdef __cplusplus
	}
#endif

#endif  //#ifndef BSP_STM32F1XX_ID_H__


