/**
  * @file  bsp_stm32f1xx_crc.c
  * @brief 全局CRC32运算驱动程序
  * @notice 为什么 bsp_stm32_crc32() 与 crc32(), crc32_mpeg_2() 或网上一些CRC计算工具的计算的结果不一样？
  *         因为STM32处理器为小端数据处理方式，CRC规则要求为大端数据处理方式（标准的CRC函数的入口以及内
  *         部处理都是以字节作为基本处理单元，这样可避免出现大小端格式问题），要想与CRC规则运算一样的结
  *         果，则需要在函数里每次对4字节原始数据运算前进行大小端变换，这样就可以计算出与工具一样的结果。
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-20     o2ospring    原始版本
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
  * @brief  CRC校验硬件初始化
  * @param  void
  * @return void
  */
void bsp_crc_init(void)
{
	// > 下面代码的HAL库内部实现写法为：
	// > `HAL_StatusTypeDef HAL_CRC_Init(CRC_HandleTypeDef *hcrc)`
	// >> `if (hcrc->State == HAL_CRC_STATE_RESET)`
	// >> `HAL_CRC_MspInit(hcrc);` //回调用户提供的回调函数(使能时钟)
	__HAL_RCC_CRC_CLK_ENABLE();
}
XT_CHIP_INIT_2_TAB_EXPORT(bsp_crc_init, "bsp_crc_init()");

/**
  * @brief  计算出CRC32校验值
  * @notice 调用本函数时必须先解决硬件互斥问题
  * @param  *p_dat         数据缓冲(注:8位数据缓冲)
  * @param  dat_len        要CRC数据长度(单位:字节)
  * @return 得出CRC32校验值
  */
uint32_t bsp_stm32_crc32(const uint8_t *p_dat, uint16_t dat_len)
{
	struct { CRC_TypeDef *Instance; } hcrc = { CRC };
	const uint32_t *p32;
	uint16_t i;
	uint8_t  k;
	
	k = dat_len % 4;
	dat_len /= 4;
	p32 = (uint32_t *)(p_dat); //STM32的变量中允许[char指针]转成[long指针]
	__HAL_CRC_DR_RESET(&hcrc);
	for (i=0; i<dat_len; i++)
	{
		CRC->DR = p32[i];
	}
	if (k != 0)
	{	//处理器数据为小端
		if (k == 1)
		CRC->DR = p32[i] & 0x000000FF; //非4字节对齐的3字节填充0
		else if (k == 2)
		CRC->DR = p32[i] & 0x0000FFFF; //非4字节对齐的2字节填充0
		else
		CRC->DR = p32[i] & 0x00FFFFFF; //非4字节对齐的1字节填充0
	}
	return (CRC->DR);
}
#endif  //#if (BSP_CRC_EN & 0x01)

#if 0
//【纯软件计算方法（32位处理方式)】:
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

//【纯软件计算方法（8位处理方式)】:
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
