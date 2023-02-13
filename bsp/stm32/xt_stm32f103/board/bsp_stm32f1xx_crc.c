/**
  * @file  bsp_stm32f1xx_crc.c
  * @brief ȫ��CRC32������������
  * @notice Ϊʲô bsp_stm32_crc32() �� crc32(), crc32_mpeg_2() ������һЩCRC���㹤�ߵļ���Ľ����һ����
  *         ��ΪSTM32������ΪС�����ݴ���ʽ��CRC����Ҫ��Ϊ������ݴ���ʽ����׼��CRC����������Լ���
  *         �����������ֽ���Ϊ��������Ԫ�������ɱ�����ִ�С�˸�ʽ���⣩��Ҫ����CRC��������һ���Ľ�
  *         ��������Ҫ�ں�����ÿ�ζ�4�ֽ�ԭʼ��������ǰ���д�С�˱任�������Ϳ��Լ�����빤��һ���Ľ����
  * COPYRIGHT (C) 2022, XT ��������С��
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    ԭʼ�汾
  */
#define   BSP_STM32F1XX_CRC_C__
#include "bsp_stm32f1xx_crc.h"
#ifdef    BSP_STM32F1XX_CRC_X__
#undef    BSP_STM32F1XX_CRC_H__
#include "bsp_stm32f1xx_crc.h"
#endif

#ifndef XT_CHIP_INIT_2_TAB_EXPORT
#define XT_CHIP_INIT_2_TAB_EXPORT(func,desc)
#endif

#if (BSP_CRC_EN & 0x01)
/**
  * @brief  CRCУ��Ӳ����ʼ��
  * @param  void
  * @return void
  */
void bsp_crc_init(void)
{
	// > ��������HAL���ڲ�ʵ��д��Ϊ��
	// > `HAL_StatusTypeDef HAL_CRC_Init(CRC_HandleTypeDef *hcrc)`
	// >> `if (hcrc->State == HAL_CRC_STATE_RESET)`
	// >> `HAL_CRC_MspInit(hcrc);` //�ص��û��ṩ�Ļص�����(ʹ��ʱ��)
	__HAL_RCC_CRC_CLK_ENABLE();
}
XT_CHIP_INIT_2_TAB_EXPORT(bsp_crc_init, "bsp_crc_init()");

/**
  * @brief  �����CRC32У��ֵ
  * @notice ���ñ�����ʱ�����Ƚ��Ӳ����������
  * @param  *p_dat         ���ݻ���(ע:8λ���ݻ���)
  * @param  dat_len        ҪCRC���ݳ���(��λ:�ֽ�)
  * @return �ó�CRC32У��ֵ
  */
uint32_t bsp_stm32_crc32(const uint8_t *p_dat, uint16_t dat_len)
{
	struct { CRC_TypeDef *Instance; } hcrc = { CRC };
	const uint32_t *p32;
	uint16_t i;
	uint8_t  k;
	
	k = dat_len % 4;
	dat_len /= 4;
	p32 = (uint32_t *)(p_dat); //STM32�ı���������[charָ��]ת��[longָ��]
	__HAL_CRC_DR_RESET(&hcrc);
	for (i=0; i<dat_len; i++)
	{
		CRC->DR = p32[i];
	}
	if (k != 0)
	{	//����������ΪС��
		if (k == 1)
		CRC->DR = p32[i] & 0x000000FF; //��4�ֽڶ����3�ֽ����0
		else if (k == 2)
		CRC->DR = p32[i] & 0x0000FFFF; //��4�ֽڶ����2�ֽ����0
		else
		CRC->DR = p32[i] & 0x00FFFFFF; //��4�ֽڶ����1�ֽ����0
	}
	return (CRC->DR);
}
#endif  //#if (BSP_CRC_EN & 0x01)

#if 0
//����������㷽����32λ����ʽ)��:
/******************************************************************************
 * Name:    CRC-32/MPEG-2  x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x+1
 * Poly:    0x4C11DB7
 * Init:    0xFFFFFFF
 * Refin:   False
 * Refout:  False
 * Xorout:  0x0000000
 * Note:
 *****************************************************************************/
uint32_t crc32(uint32_t *addr, int num)
{
    int i;
    uint32_t crc = 0xffffffff;
	while (num--)
    {
        crc = crc ^ (*addr++);
        for (i = 0; i < 32; i++)
        {
            if (crc & 0x80000000)
                crc = (crc << 1) ^ 0x04C11DB7;
            else
                crc <<= 1;
        }
    }
    return(crc);
}

//����������㷽����8λ����ʽ)��:
/******************************************************************************
 * Name:    CRC-32/MPEG-2  x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x+1
 * Poly:    0x4C11DB7
 * Init:    0xFFFFFFF
 * Refin:   False
 * Refout:  False
 * Xorout:  0x0000000
 * Note:
 *****************************************************************************/
uint32_t crc32_mpeg_2(uint8_t *data, uint16_t length)
{
    uint8_t i;
    uint32_t crc = 0xffffffff;  // Initial value
    while(length--)
    {
        crc ^= (uint32_t)(*data++) << 24;// crc ^=(uint32_t)(*data)<<24; data++;
        for (i = 0; i < 8; ++i)
        {
            if ( crc & 0x80000000 )
                crc = (crc << 1) ^ 0x04C11DB7;
            else
                crc <<= 1;
        }
    }
    return crc;
}
#endif
