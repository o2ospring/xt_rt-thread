/**
  * @file  xt_led_pwm.h
  * @brief LED调色调光模块（实现开关/调光/调色控制服务，以及控制参数保存与读出）
  * COPYRIGHT (C) 2023, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2023-03-01     o2ospring    原始版本
  */
#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#include <string.h> //////////////////////// <- 使用的字符处理，如: strcpy(), memcpy() 等
#include "xt_comdef.h" ///////////////////// <- 常用宏定义集合，如: XT_BIT_SET 等
#include "board.h"   /////////////////////// <- 工程所有硬件资源管理头文件!!!!!!!!!!!!!!!
#include "xt_led_pwm_stm32f1xx_hal.h" ////// <- 单片机【STM32F103xx】的LED调色调光模块
#include "xt_wiznet_vofa.h" //////////////// <- 使用网络虚拟数字示波器

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 参数配置 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

//相关测试配置
//#define XT_LEDM_DBUG_SAVE()       /*HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,1);*/ //掉电保存测试（用于检测掉电保存的响应时间，例如使用一个IO口输出高电平）
//#define XT_LEDM_DBUG_LIGHT_1()    /*HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,1);*/ //调色调光测试（开于检测调色调光在中断中的运行时间，例如IO口输出高电平）
//#define XT_LEDM_DBUG_LIGHT_2()    /*HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,0);*/ //调色调光测试（开于检测调色调光在中断中的运行时间，例如IO口输出低电平）
//#define XT_LEDM_DBUG_ADJUST_1()   /*HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,1);*/ //手控调光测试（开于检测手控调光运算处理的运行时间，例如IO口输出高电平）
//#define XT_LEDM_DBUG_ADJUST_2()   /*HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,0);*/ //手控调光测试（开于检测手控调光运算处理的运行时间，例如IO口输出低电平）
//#define XT_LEDM_DBUG_APP_OP_1()   /*HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);*/ //应用操作测试（开于检测应用调用控制函数的运行时间，例如IO口输出高电平）
//#define XT_LEDM_DBUG_APP_OP_2()   /*HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0);*/ //应用操作测试（开于检测应用调用控制函数的运行时间，例如IO口输出低电平）
#define XT_LEDPWM_HW_DRIVERS_EN     1                                          //是否使用本模块自带硬件驱动（0:不使用,1:STM32F1xx-PWM+溢出中断）
#define xt_led_pwm_printf(...)      rt_kprintf("ledm:" __VA_ARGS__)            //异常信息打印（目前还没用到可变参数，可以稍作修改本行宏即可支持C89语法）
#define xt_led_pwm_printf_c(cold)   xt_wizvofa_1ch_put(1, (float)(cold))       //打印冷光曲线（用于展示调光曲线）
#define xt_led_pwm_printf_w(warm)   xt_wizvofa_1ch_put(2, (float)(warm))       //打印暖光曲线（用于展示调光曲线）
#define XT_LEDM_COLD_PWM_RD2()      xt_led_pwm_hw_cold_pwm_rd2()               //打印调试时读:冷光当前硬件实际PWM值
#define XT_LEDM_WARM_PWM_RD2()      xt_led_pwm_hw_warm_pwm_rd2()               //打印调试时读:暖光当前硬件实际PWM值

//应用程序互斥                     （多线程任务需要加应用互斥）
#define XT_LEDM_APP_VARIAB()                                                   /* 应用互斥:变量声明     */
#define XT_LEDM_APP_LOCKED()        rt_enter_critical()                        /* 应用互斥:上锁         */
#define XT_LEDM_APP_UNLOCK()        rt_exit_critical()                         /* 应用互斥:解锁         */

//硬件全局互斥                     （目前规定为开关总中断开关）
#define XT_LEDM_HD_VARIAB()         register rt_base_t level;                  /* 硬件互斥:变量声明     */
#define XT_LEDM_HD_LOCKED()         level = rt_hw_interrupt_disable()          /* 硬件互斥:上锁         */
#define XT_LEDM_HD_UNLOCK()         rt_hw_interrupt_enable(level)              /* 硬件互斥:解锁         */

//数据存储操作                     （上电时读存储器(xt_led_pwm_dev_init())和掉电前写存储器(xt_led_pwm_main_loop()≤@10ms)）
#define XT_LEDM_ROM_ADDR            0                                          /* 存储器地址,共[4*2]字节*/
#define XT_LEDM_ROM_BOOT_RD(a,p,l)  ((uint16_t *)p)[0]=1000/*亮度‰*/|(0<<15);  /* 上电初始化时读多字节  */\
                                    ((uint16_t *)p)[1]=1000/*色温‰：纯冷光*/;                             \
                                    *((uint32_t *)(&(((uint16_t *)p)[2])))=(uint32_t)xt_ledm_tb_pwm
#define XT_LEDM_ROM_MUTEX_LOCKED()  /*rt_mutex_take(...)*/                     /* 存储器操作互斥:上锁   */
#define XT_LEDM_ROM_MUTEX_UNLOCK()  /*rt_mutex_release(...)*/                  /* 存储器操作互斥:解锁   */
#define XT_LEDM_ROM_WR(a,p,l)       /*eeprom_write(a,p,l)*/                    /* 存储器保存[4*2]字节   */
#define XT_LEDM_ROM_RD(a,p,l)       XT_LEDM_ROM_BOOT_RD(a,p,l)                 /* 存储器读出[4*2]字节   */

//单色还是双色调光
#define XT_LEDM_COLOR               2                                          /* 1:单色灯，2:双色灯    */

//PWM初始化                        （上电硬件初始化(xt_led_pwm_dev_init())）
#define XT_LEDM_HD_PWM_INIT()       xt_led_pwm_hw_init()                       /* PWM 硬件初始化函数    */

//PWM控制与参数                    （最大值:35999->频率1KHz）
//#define XT_LEDM_PWM_MIN           (300)/*目的主要为跳过不稳定会抖动的最低亮*//* PWM 最小值(输出限制)  */// → ★可剪裁★
#define XT_LEDM_PWM_MAX             (LEDM_TIMX_PWM_FREVOL)                     /* PWM 最大值            */
#define XT_LEDM_PWM_SUM_DIVISOR     (1000)/*如:(35999+1)/1000*/                /* PWM 最大值+1化简除数  */
#define XT_LEDM_COLD_PWM_WR(v)      xt_led_pwm_hw_cold_pwm_wr(v)               /* 写:冷光当前硬件PWM值  */
#define XT_LEDM_WARM_PWM_WR(v)      xt_led_pwm_hw_warm_pwm_wr(v)               /* 写:暖光当前硬件PWM值  */
#define XT_LEDM_COLD_PWM_RD()       xt_led_pwm_hw_cold_pwm_rd()                /* 读:冷光当前硬件PWM值  */
#define XT_LEDM_WARM_PWM_RD()       xt_led_pwm_hw_warm_pwm_rd()                /* 读:暖光当前硬件PWM值  */

//渐变直线表                        → ★可剪裁★
//#define XT_LEDM_LTB_PWM(i)        xt_ledm_ltb_read(i)                        /* 读渐变直线表组员PWM值 */// → ★可剪裁★
//#ifdef  XT_LED_PWM_C__
//uint16_t xt_ledm_ltb_read(uint8_t i)                                         /* 读直线表组员PWM值函数 */// → ★可剪裁★
//{	//假如 4560(PWM)/1230(分段) = 3 ~ 870(余数)
//	//  则 4560 = (((3)*(1230-870) + (3+1)*(870)))
//	if (i == 000) return 0;
//	if (i >= 254) return XT_LEDM_PWM_MAX;
//	if (i <= 254-((XT_LEDM_PWM_MAX+1)%254))
//	/**/          return (uint16_t)((XT_LEDM_PWM_MAX+1)/254+0) * (uint16_t)(i);
//	else          return (uint16_t)((XT_LEDM_PWM_MAX+1)/254+0) * (uint16_t)(  (254-((XT_LEDM_PWM_MAX+1)%254)))
//	/**/               + (uint16_t)((XT_LEDM_PWM_MAX+1)/254+1) * (uint16_t)(i-(254-((XT_LEDM_PWM_MAX+1)%254)));
//}
//#endif

//渐变曲线表
#define XT_LEDM_TB_T                const                                      /* 渐变曲线表数据类型    */
#ifdef  XT_LED_PWM_C__
XT_LEDM_TB_T uint16_t xt_ledm_tb_pwm[255/*★不能改★*/] = {
0    , 36   , 37   , 38   , 39   , 40   , 41   , 42   , 43   , 44   , 45   , 46   , 48   , 49   , 51   , 52   , 
54   , 55   , 57   , 58   , 60   , 62   , 64   , 66   , 68   , 70   , 72   , 74   , 76   , 78   , 80   , 82   , 
84   , 86   , 88   , 90   , 92   , 95   , 98   , 101  , 104  , 107  , 110  , 113  , 116  , 119  , 122  , 125  , 
129  , 133  , 137  , 140  , 144  , 148  , 153  , 157  , 161  , 166  , 170  , 175  , 180  , 185  , 190  , 195  , 
201  , 206  , 212  , 218  , 224  , 230  , 236  , 243  , 250  , 257  , 264  , 271  , 279  , 286  , 294  , 302  , 
311  , 319  , 328  , 337  , 347  , 356  , 366  , 376  , 387  , 397  , 408  , 420  , 431  , 443  , 456  , 468  , 
481  , 495  , 508  , 522  , 537  , 552  , 567  , 583  , 599  , 615  , 632  , 650  , 668  , 686  , 705  , 725  , 
745  , 766  , 787  , 809  , 831  , 854  , 878  , 902  , 927  , 953  , 979  , 1006 , 1034 , 1063 , 1092 , 1122 , 
1154 , 1186 , 1218 , 1252 , 1287 , 1322 , 1359 , 1397 , 1435 , 1475 , 1516 , 1558 , 1601 , 1645 , 1691 , 1738 , 
1786 , 1835 , 1886 , 1938 , 1992 , 2047 , 2104 , 2162 , 2222 , 2283 , 2347 , 2412 , 2478 , 2547 , 2617 , 2690 , 
2764 , 2841 , 2920 , 3000 , 3083 , 3169 , 3257 , 3347 , 3439 , 3535 , 3632 , 3733 , 3836 , 3943 , 4052 , 4164 , 
4279 , 4398 , 4519 , 4644 , 4773 , 4905 , 5041 , 5180 , 5324 , 5471 , 5623 , 5778 , 5938 , 6103 , 6272 , 6445 , 
6624 , 6807 , 6995 , 7189 , 7388 , 7592 , 7803 , 8019 , 8241 , 8469 , 8703 , 8944 , 9192 , 9446 , 9708 , 9976 , 
10252, 10536, 10828, 11128, 11436, 11752, 12077, 12412, 12755, 13108, 13471, 13844, 14227, 14621, 15026, 15442, 
15869, 16309, 16760, 17224, 17701, 18191, 18694, 19212, 19743, 20290, 20852, 21429, 22022, 22631, 23258, 23902, 
24563, 25243, 25942, 26660, 27398, 28156, 28936, 29737, 30560, 31406, 32275, 33168, 34086, 35030, 35999};
#else
extern XT_LEDM_TB_T uint16_t xt_ledm_tb_pwm[];
#endif

/*--------------------------------------------------------------------------------------------------------
关于PWM控制细节，不同MCU有不同机制，例如：
MC51F003A4：在PWM1输出波形时，若当前周期或占空比被修改，不会立即生效，需要等到下个周期来到才会相应改变。
STM32Fxxxx：在PWM模式下(CNT<CCR)时输出一种电平，(CNT>CCR)时输出相反的电平。即修改占空比可能是即时生效！
但如果模式是(CNT==CCR)时取反输出电平，则不适合用于高速PWM占空比控制，因为修改其占空比操作必须在PWM中断
中操作，当PWM中断频率太高，会影响程序正常运行！所以要根据上述细节综合决定 xt_led_pwm_isr_loop() 函数是
在PWM中断中调用还是在普通定时器中调用！
--------------------------------------------------------------------------------------------------------*/

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 数据类型 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

//控制参数++++++++++++++++++++++
#define XT_LEDM_OP_SW          0 //开关控制（v=0:关灯,v=1:开灯,v=2:开关灯）
#define XT_LEDM_OP_MODE_SW     1 //切换模式（v=0~XT_LEDM_MODE_SUM-1:指定色温模式,v=0x7F:开灯时切换色温,v=0xFF:强制开灯并切换色温）→ ★可剪裁★
#define XT_LEDM_OP_LIGHT       2 //调节亮度（v=10~1000:亮度千分比,如v=10:10‰）                   → ★可剪裁★
#define XT_LEDM_OP_ADJUST      3 //手控调光（v=0:结束手控调光,v=1:手控向上调光,v=2:手控向下调光）→ ★可剪裁★
#define XT_LEDM_OP_SUM         4 //↓
extern void xt_led_pwm_set(uint8_t c, uint16_t v, uint16_t t); //LED调色调光操作

typedef struct led_pwm_obj_
{
	//亮度参数+++++++++++++++++++++++++++++++++
	#define  XT_LEDM_BG_MIN         10UL      //亮度可调光范围的最小值（单位：‰）
	#define  XT_LEDM_BG_MAX         1000UL    //亮度可调光范围的最大值（单位：‰）
	uint16_t brightness;                      //相对亮度（10~1000‰）
	#ifdef XT_LEDM_OP_MODE_SW
	uint8_t  led_mode_n;                      //工作模式（0~XT_LEDM_MODE_SUM-1）
	#endif
	uint8_t  led_flag;                        //工作标志（bit0=1:关灯,bit1=1:手控上调,bit2=1:手控下调,bit3=1:全程渐变时间(渐变速率)
	                                          //          bit4=1:应用控制锁,bit5=1:保存参数,bit6=1:禁止控制,bit7=1:过载保护）
	uint8_t  opt_flag;                        //操作标志（bit0=1:直线调光,bit1=1:临时直线调光,bit2=1:将判断是否要临时直线调光）
	
	#define  XT_LEDM_ST_CNT_100MS   100UL     //时间100ms计时值（当(tm_cnt - st_cnt >= XT_LEDM_ST_CNT_100MS)时,则(st_save)可能计数一次）
	#define  XT_LEDM_ST_SAVE_FV     51UL      //状态掉电前执行保存数据的标志值（每 XT_LEDM_ST_CNT_100MS 计数一次，约5秒）
	uint8_t  st_save;                         //状态掉电前操作标志及锁定记数器（0:表示锁定结束，≥XT_LEDM_ST_SAVE_FV:表示掉电前保存数据）
	#define  XT_LEDM_ST_SAVE_RESET  130UL     //定时检测掉电保存是否没必要操作（每 XT_LEDM_ST_CNT_100MS 计数一次，约13秒）
	uint8_t  st_save_reset;                   //定时检测掉电保存是否没必要操作记数器
	
	//渐变参数+++++++++++++++++++++++++++++++++
	uint8_t  seg_flag;                        //换算关系标志（[bit0-1]->tik:seg,[bit2-3]->tik:pwm,[bit4-5]->在一段内,[bit6-7]->开始渐变）
	uint8_t  tik_seg_n[XT_LEDM_COLOR];        //所在曲线分段的编号（0xFF:渐变参数无效）
	
	uint16_t tik_pwm_q[XT_LEDM_COLOR];        //商值 ◆◆渐变行程【节拍数】与【PWM值】的换算关系◆◆
	uint16_t tik_pwm_w[XT_LEDM_COLOR];        //关系式分界（PWM值）
	uint16_t tik_pwm_c[XT_LEDM_COLOR];        //一个PWM多节拍计数
	
	uint16_t run_tik[XT_LEDM_COLOR];          //现场行程渐变时间节拍数（节拍周期为[XT_LEDM_ONE_TKMS]）
	uint16_t min_254[XT_LEDM_COLOR];          //调光档位值（最高精度1/(254UL<<8)）或 起点与终点的254分比
	uint16_t max_lim[XT_LEDM_COLOR];          //调光档位值（最高精度1/(254UL<<8)）或 分段关系式分界及终点所在分段
	uint16_t end_pwm[XT_LEDM_COLOR];          //最终PWM值（亮灯值）
	
	#define  XT_LEDM_PB_TM0S1       2UL       //默认的[前置]渐变时间（@0.1秒）( | 0x8000 表示全程渐变时间，即指定渐变速率)
	#define  XT_LEDM_SW_TM0S1       20UL      //默认的[开关]渐变时间（@0.1秒）( | 0x8000 表示全程渐变时间，即指定渐变速率)
	#define  XT_LEDM_CC_TM0S1       20UL      //默认的[换色]渐变时间（@0.1秒）( | 0x8000 表示全程渐变时间，即指定渐变速率)
	#define  XT_LEDM_BG_TM0S1       30UL      //默认的[调光]渐变时间（@0.1秒）( | 0x8000 表示全程渐变时间，即指定渐变速率)
	#define  XT_LEDM_MB_TM0S1       1UL       //默认的[手调]渐变时间（@0.1秒）( | 0x8000 表示全程渐变时间，即指定渐变速率)
	#define  XT_LEDM_MB_BGVAL       30U       //1000‰~3分界：手控调光每小截递进亮度（单位：‰）
	#define  XT_LEDM_MB_BGVAL2      10U       //3分界~2分界：手控调光每小截递进亮度（单位：‰）→ ★可剪裁★
	#define  XT_LEDM_MB_BGVAL1      2U        //2分界~1分界：手控调光每小截递进亮度（单位：‰）→ ★可剪裁★
	#define  XT_LEDM_MB_BGVAL0      1U        //1分界~0000‰：手控调光每小截递进亮度（单位：‰）→ ★可剪裁★
	#define  XT_LEDM_MB_LIMIT3      220U      //3分界折线点：手控调光分界3)的亮度值（单位：‰）→ ★可剪裁★
	#define  XT_LEDM_MB_LIMIT2      60U       //2分界折线点：手控调光分界2)的亮度值（单位：‰）→ ★可剪裁★
	#define  XT_LEDM_MB_LIMIT1      15U       //1分界折线点：手控调光分界1)的亮度值（单位：‰）→ ★可剪裁★
	#define  XT_LEDM_MIN_TM0S1      1UL       //输入控制的最短渐变时间（@0.1秒）-> 固化为0.1秒，不建议改！
	#define  XT_LEDM_MAX_TM0S1      1000UL    //输入控制的最长渐变时间（@0.1秒）-> 固化为100秒，不建议改！
	#define  XT_LEDM_ONE_TKMS       2UL       //调光调色的渐变节拍周期（@2ms）---> 固化为2毫秒，不建议改！
	uint8_t  tm_cnt;                          //通用周期计数器（与 xt_led_pwm_isr_loop() 调用频率相关：每[XT_LEDM_ONE_TKMS]ms一次）
	uint8_t  st_cnt;                          //状态保存后锁定计时（数据类型必须与[tm_cnt]相同）
	XT_LEDM_TB_T uint16_t *p_tb_pwm;          //渐变曲线表
	
	//色温参数+++++++++++++++++++++++++++++++++
	#if (XT_LEDM_COLOR == 2)
	uint16_t full_cl[XT_LEDM_COLOR];          //单通道最亮‰值（[0]冷色，[1]暖色）
	#endif
	
	//特殊用途+++++++++++++++++++++++++++++++++
	#define  XT_LEDM_HD_BG_MIN      1UL       //前置交流相位调光器联动调节亮度范围 → ★可剪裁★
	#define  XT_LEDM_HD_BG_MAX      100UL     //前置交流相位调光器联动调节亮度范围 → ★可剪裁★
	#if (defined XT_LEDM_HD_BG_MIN) && (defined XT_LEDM_HD_BG_MAX)
	uint8_t  hd_brightness_new;               //前置交流相位调光器联动调节亮度（1~100%）→ 是%,非‰
	uint8_t  hd_brightness_old;               //前置交流相位调光器联动调节亮度（1~100%）→ 是%,非‰
	#endif
}led_pwm_obj_t;

//参数检测+++++++++++++++++++++++++++++++++++++
#if ((XT_LEDM_PWM_MAX+1) > 65535UL) || (((XT_LEDM_PWM_MAX+1) % XT_LEDM_PWM_SUM_DIVISOR) != 0) || ((1000000 % XT_LEDM_PWM_SUM_DIVISOR) != 0)
#error "[XT_LEDM_PWM_MAX][XT_LEDM_PWM_SUM_DIVISOR] config error!"
#endif
#if (XT_LEDM_BG_MIN <= 0) || (XT_LEDM_BG_MAX != 1000) || ((defined XT_LEDM_HD_BG_MAX) && (XT_LEDM_HD_BG_MAX != 100))
#error "[XT_LEDM_BG_MIN][XT_LEDM_BG_MAX][XT_LEDM_HD_BG_MAX] config error!"
#endif
#if (defined XT_LEDM_MB_LIMIT1) && (defined XT_LEDM_MB_LIMIT2) && (defined XT_LEDM_MB_LIMIT3) \
&& ((XT_LEDM_MB_LIMIT1 >= XT_LEDM_MB_LIMIT2) || (XT_LEDM_MB_LIMIT2 >= XT_LEDM_MB_LIMIT3) \
||  (XT_LEDM_BG_MIN    >= XT_LEDM_MB_LIMIT1) || (XT_LEDM_MB_LIMIT3 >= XT_LEDM_BG_MAX))
#error "[XT_LEDM_MB_LIMIT1][XT_LEDM_MB_LIMIT2][XT_LEDM_MB_LIMIT3][XT_LEDM_BG_MIN][XT_LEDM_BG_MAX] config error!"
#endif
#if ((XT_LEDM_MAX_TM0S1/*@0.1秒*/ * 10UL) > 65535UL)
#error "[XT_LEDM_MAX_TM0S1] config error!"
#endif
#if ((XT_LEDM_MAX_TM0S1 * 100UL / XT_LEDM_ONE_TKMS) > 0xFFFF)
#error "[XT_LEDM_MAX_TM0S1][XT_LEDM_ONE_TKMS] config error!"
#endif
#if ((100UL/*@ms*/ % XT_LEDM_ONE_TKMS) != 0) || (XT_LEDM_ONE_TKMS > 10)
#error "[XT_LEDM_ONE_TKMS] config error!"
#endif
#if ((XT_LEDM_ST_CNT_100MS % XT_LEDM_ONE_TKMS) != 0)
#error "[XT_LEDM_ST_CNT_100MS][XT_LEDM_ONE_TKMS] config error!"
#endif
#if ((defined XT_LEDM_HD_BG_MAX) && ((XT_LEDM_BG_MAX * XT_LEDM_BG_MAX) > (0xFFFFFFFF / XT_LEDM_HD_BG_MAX)))
#error "[XT_LEDM_BG_MAX][XT_LEDM_HD_BG_MAX] config error!"
#endif
#if ((defined XT_LEDM_HD_BG_MAX) && ((XT_LEDM_BG_MAX * XT_LEDM_BG_MAX * XT_LEDM_HD_BG_MAX) > (0xFFFFFFFF / ((XT_LEDM_PWM_MAX+1)/XT_LEDM_PWM_SUM_DIVISOR))))
#error "[XT_LEDM_BG_MAX][XT_LEDM_HD_BG_MAX] config error!"
#endif
#if (XT_LEDM_COLOR != 1) && (XT_LEDM_COLOR != 2)
#error "[XT_LEDM_COLOR] config error!"
#endif
#if (defined XT_LEDM_OP_MODE_SW) && (XT_LEDM_COLOR == 1)
#error "[XT_LEDM_COLOR][XT_LEDM_OP_MODE_SW] config error!"
#endif
#if (XT_LEDM_ST_SAVE_FV > 250) || (XT_LEDM_ST_SAVE_RESET > 250)
#error "[XT_LEDM_ST_SAVE_FV][XT_LEDM_ST_SAVE_RESET] config error!"
#endif

//色温模式+++++++++++++++++++++++++++++++++++++
#ifdef XT_LEDM_OP_MODE_SW
#define XT_LEDM_MODE_COLD      0              //冷色模式 → ★可剪裁★
#define XT_LEDM_MODE_NEUTRAL   1              //中性模式 → ★可剪裁★
#define XT_LEDM_MODE_WARM      2              //暖色模式 → ★可剪裁★
#define XT_LEDM_MODE_SUM       3              //总数
#ifdef  XT_LED_PWM_C__     /* ↓ */
const uint8_t xt_ledm_mode[XT_LEDM_MODE_SUM][2] = {
/*	冷光(%) 暖光(%)  */    /* ↑ */           //注意 → 是%,非‰
	{  100,      0}, //XT_LEDM_MODE_COLD
	{   50,     50}, //XT_LEDM_MODE_NEUTRAL
	{    0,    100}  //XT_LEDM_MODE_WARM
};
#endif
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 操作函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void xt_led_pwm_cct_set(uint8_t c, uint16_t v, uint16_t t);        //LED色温设置操作
extern void xt_led_pwm_set(uint8_t c, uint16_t v, uint16_t t);            //LED调色调光操作
extern uint8_t xt_led_pwm_curve_tb_replace(XT_LEDM_TB_T uint16_t *p_pwm); //替换渐变曲线表
extern void xt_led_pwm_ctrl_locked(void);     //LED调色调光控制锁定（禁止应用控制）(★特殊用途★) (不禁LED前置联动调节亮度)
extern void xt_led_pwm_ctrl_unlock(void);     //LED调色调光控制解除（解禁应用控制）(★特殊用途★)
extern void xt_led_pwm_alarm_locked(void);    //LED调色调光急停控制（用于过载保护）(在中断中触发)
extern uint8_t xt_led_pwm_alarm_unlock(void); //LED调色调光急停清除（过载保护恢复）(须由应用调用) (★清除锁定并保持关灯★)
extern void xt_led_pwm_st_save_trigger(void); //LED状态掉电保存触发（在中断中触发）(作掉电前保存)
extern void xt_led_pwm_pre_dimmer(uint8_t v); //LED前置联动调节亮度（在中断中触发）(★特殊用途★)
extern uint8_t xt_led_pwm_tm(void);           //获取LED调色调光模块内部定时器计数值(★扩展用途★)
extern uint16_t xt_led_pwm_bg(void);          //获取LED开时亮度（但不能判断开关灯）(★扩展用途★)
extern void xt_led_pwm_isr_loop(void);        //LED调色调光运转函数（在中断中运行）(在硬件定时器定时调用)
extern void xt_led_pwm_main_loop(void);       //LED调色调光运转函数（主函数中运行）(一般要求≤10ms调用一次)
extern void xt_led_pwm_chip_init(void);       //LED内核级初始化函数（应在其它中断初始化前操作）
extern void xt_led_pwm_dev_init(void);        //LED芯片级初始化函数（本函数会读取EEPROM数据）
extern void xt_led_pwm_msg_init(void);        //LED应用级初始化函数

#ifdef __cplusplus
    }
#endif
