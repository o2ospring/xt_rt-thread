/**
  * @file  bsp_stm32f1xx_id.c
  * @brief ����STM32F103ID��������
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    ԭʼ�汾
  */
#define   BSP_STM32F1XX_ID_C__
#include "bsp_stm32f1xx_id.h"
#ifdef    BSP_STM32F1XX_ID_X__
#undef    BSP_STM32F1XX_ID_H__
#include "bsp_stm32f1xx_id.h"
#endif

/**
  * @brief  �Ƚ�STM32��ID ��ע��:������û��ȫ��⣩
  * @param  *p_dat         Դ����ָ�루��12�ֽڣ�
  * @return 0->������IDһ��, ����->��һ��
  */
int bsp_stm32_id12_cmp(uint8_t *p_dat)
{
	return memcmp(p_dat, (uint8_t *)(0x1FFFF7E8), 12);
}

/**
  * @brief  ����STM32��ID ��ע��:������û��ȫ��⣩
  * @param  *p_buf         Ŀ�껺�壨��12�ֽڣ�
  * @return void
  */
void bsp_stm32_id12_get(uint8_t *p_buf)
{
	memcpy(p_buf, (const uint8_t *)(0x1FFFF7E8), 12);
	return;
}

#if (BSP_CRC_EN & 0x01)
/**
  * @brief  ����ΨһID    ���������ɡ�12�ֽڣ�
  * @param  *p_buf         Ŀ�껺��
  * @param  id_size        ����ΨһID�Ĵ�С���ֽڣ�
  * @return void
  */
void bsp_unique_id_generate(uint8_t *p_buf, uint8_t id_size)
{
	uint32_t d;
	
	if (id_size >= 12)
	{
		while (1)
		{
			if (id_size > 12)
			{
				memcpy(p_buf, (const uint8_t *)(0x1FFFF7E8), 12);
				p_buf += 12;
				id_size -= 12;
			}
			else
			{
				memcpy(p_buf, (const uint8_t *)(0x1FFFF7E8), id_size);
				return;
			}
		}
	}
	else
	{
		d = bsp_stm32_crc32((const uint8_t *)(0x1FFFF7E8), 12);
		if (id_size > 4)
		{
			memcpy(p_buf, (const uint8_t *)(&d), 4);
			p_buf += 4;
			id_size -= 4;
		}
		else
		{
			memcpy(p_buf, (const uint8_t *)(&d), id_size);
			return;
		}
		d = bsp_stm32_crc32((const uint8_t *)(0x1FFFF7E8), 8);
		if (id_size > 4)
		{
			memcpy(p_buf, (const uint8_t *)(&d), 4);
			p_buf += 4;
			id_size -= 4;
		}
		else
		{
			memcpy(p_buf, (const uint8_t *)(&d), id_size);
			return;
		}
		d = bsp_stm32_crc32((const uint8_t *)(0x1FFFF7E8+4), 8);
		memcpy(p_buf, (const uint8_t *)(&d), id_size);
		return;
	}
}
#endif
