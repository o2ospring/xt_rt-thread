/**
  * @file  bsp_stm32f1xx_id.c
  * @brief 读出STM32F103ID驱动程序
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    原始版本
  */
#define   BSP_STM32F1XX_ID_C__
#include "bsp_stm32f1xx_id.h"
#ifdef    BSP_STM32F1XX_ID_X__
#undef    BSP_STM32F1XX_ID_H__
#include "bsp_stm32f1xx_id.h"
#endif

/**
  * @brief  比较STM32的ID （注意:缓冲器没安全检测）
  * @param  *p_dat         源数据指针（共12字节）
  * @return 0->数据与ID一样, 其它->不一样
  */
int bsp_stm32_id12_cmp(uint8_t *p_dat)
{
	return memcmp(p_dat, (uint8_t *)(0x1FFFF7E8), 12);
}

/**
  * @brief  读出STM32的ID （注意:缓冲器没安全检测）
  * @param  *p_buf         目标缓冲（共12字节）
  * @return void
  */
void bsp_stm32_id12_get(uint8_t *p_buf)
{
	memcpy(p_buf, (const uint8_t *)(0x1FFFF7E8), 12);
	return;
}

#if (BSP_CRC_EN & 0x01)
/**
  * @brief  生成唯一ID    （建议生成≤12字节）
  * @param  *p_buf         目标缓冲
  * @param  id_size        生成唯一ID的大小（字节）
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
