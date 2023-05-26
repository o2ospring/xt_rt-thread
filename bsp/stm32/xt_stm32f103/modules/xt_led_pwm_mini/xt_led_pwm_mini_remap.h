/**
  * @file  xt_led_pwm_mini.h
  * @brief LED调色调光模块（实现直线调光/调色控制服务）
  * COPYRIGHT (C) 2023, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2023-05-08     o2ospring    参考【xt_led_pwm】精简而来，适合2K-ROM的单片机
  */
#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#include <string.h> //////////////////////// <- 使用的字符处理，如: strcpy(), memcpy() 等
#include "xt_comdef.h" ///////////////////// <- 常用宏定义集合，如: XT_BIT_SET 等
#include "board.h" ///////////////////////// <- 工程所有硬件资源管理头文件!!!!!!!!!!!!!!!
#include "xt_led_pwm_mini_stm32f1xx_hal.h"// <- 单片机【STM32F103xx】的LED调色调光模块
#include "xt_wiznet_vofa.h" //////////////// <- 使用网络虚拟数字示波器

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 参数配置 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

//相关测试配置
//#define XT_LEDMM_DBUG_SAVE()      /*HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,1);*/ //掉电保存测试（用于检测掉电保存的响应时间，例如使用一个IO口输出高电平）
//#define XT_LEDMM_DBUG_LIGHT_1()   /*HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,1);*/ //调色调光测试（开于检测调色调光在中断中的运行时间，例如IO口输出高电平）
//#define XT_LEDMM_DBUG_LIGHT_2()   /*HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,0);*/ //调色调光测试（开于检测调色调光在中断中的运行时间，例如IO口输出低电平）
//#define XT_LEDMM_DBUG_ADJUST_1()  /*HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,1);*/ //手控调光测试（开于检测手控调光运算处理的运行时间，例如IO口输出高电平）
//#define XT_LEDMM_DBUG_ADJUST_2()  /*HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,0);*/ //手控调光测试（开于检测手控调光运算处理的运行时间，例如IO口输出低电平）
//#define XT_LEDMM_DBUG_APP_OP_1()  /*HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);*/ //应用操作测试（开于检测应用调用控制函数的运行时间，例如IO口输出高电平）
//#define XT_LEDMM_DBUG_APP_OP_2()  /*HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,0);*/ //应用操作测试（开于检测应用调用控制函数的运行时间，例如IO口输出低电平）
#define XT_LEDPWMM_HW_DRIVERS_EN    1                                          //是否使用本模块自带硬件驱动（0:不使用,1:STM32F1xx-PWM+溢出中断,2:FT61F02x-PWM+溢出中断）
#define xt_led_pwmm_printf(...)     rt_kprintf("ledmm:" __VA_ARGS__)           //异常信息打印（目前还没用到可变参数，可以稍作修改本行宏即可支持C89语法）
#define xt_led_pwmm_printf_c(cold)  xt_wizvofa_1ch_put(1, (float)(cold))       //打印冷光曲线（用于展示调光曲线）
#define xt_led_pwmm_printf_w(warm)  xt_wizvofa_1ch_put(2, (float)(warm))       //打印暖光曲线（用于展示调光曲线）
#define XT_LEDMM_COLD_PWM_RD2()     xt_led_pwmm_hw_cold_pwm_rd2()              //打印调试时读:冷光当前硬件实际PWM值
#define XT_LEDMM_WARM_PWM_RD2()     xt_led_pwmm_hw_warm_pwm_rd2()              //打印调试时读:暖光当前硬件实际PWM值

//应用程序互斥                     （多线程任务需要加应用互斥）
#define XT_LEDMM_APP_VARIAB()                                                  /* 应用互斥:变量声明     */
#define XT_LEDMM_APP_LOCKED()       rt_enter_critical()                        /* 应用互斥:上锁         */
#define XT_LEDMM_APP_UNLOCK()       rt_exit_critical()                         /* 应用互斥:解锁         */

//硬件全局互斥                     （目前规定为开关总中断开关）
#define XT_LEDMM_HD_VARIAB()        register rt_base_t level;                  /* 硬件互斥:变量声明     */
#define XT_LEDMM_HD_LOCKED()        level = rt_hw_interrupt_disable()          /* 硬件互斥:上锁         */
#define XT_LEDMM_HD_UNLOCK()        rt_hw_interrupt_enable(level)              /* 硬件互斥:解锁         */

//单色还是双色调光
#define XT_LEDMM_COLOR              2                                          /* 1:单色灯，2:双色灯    */

//PWM初始化                        （上电硬件初始化(xt_led_pwmm_dev_init())）
#define XT_LEDMM_HD_PWM_INIT()      xt_led_pwmm_hw_init()                      /* PWM 硬件初始化函数    */

//PWM控制与参数                    （最大值:35999->频率1KHz）
//#define XT_LEDMM_PWM_MIN          (300)/*目的主要为跳过不稳定会抖动的最低亮*//* PWM 最小值(输出限制)  */// → ★可剪裁★
#define XT_LEDMM_PWM_MAX            (LEDMM_TIMX_PWM_FREVOL)                    /* PWM 最大值            */
#define XT_LEDMM_PWM_SUM_DIVISOR    (1000)/*如:(35999+1)/1000*/                /* PWM 最大值+1化简除数  */
#define XT_LEDMM_COLD_PWM_WR(v)     xt_led_pwmm_hw_cold_pwm_wr(v)              /* 写:冷光当前硬件PWM值  */
#define XT_LEDMM_WARM_PWM_WR(v)     xt_led_pwmm_hw_warm_pwm_wr(v)              /* 写:暖光当前硬件PWM值  */
#define XT_LEDMM_COLD_PWM_RD()      xt_led_pwmm_hw_cold_pwm_rd()               /* 读:冷光当前硬件PWM值  */
#define XT_LEDMM_WARM_PWM_RD()      xt_led_pwmm_hw_warm_pwm_rd()               /* 读:暖光当前硬件PWM值  */

/*--------------------------------------------------------------------------------------------------------
关于PWM控制细节，不同MCU有不同机制，例如：
MC51F003A4：在PWM1输出波形时，若当前周期或占空比被修改，不会立即生效，需要等到下个周期来到才会相应改变。
STM32Fxxxx：在PWM模式下(CNT<CCR)时输出一种电平，(CNT>CCR)时输出相反的电平。即修改占空比可能是即时生效！
但如果模式是(CNT==CCR)时取反输出电平，则不适合用于高速PWM占空比控制，因为修改其占空比操作必须在PWM中断
中操作，当PWM中断频率太高，会影响程序正常运行！所以要根据上述细节综合决定 xt_led_pwmm_isr_loop()函数是
在PWM中断中调用还是在普通定时器中调用！
--------------------------------------------------------------------------------------------------------*/

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 数据类型 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

typedef struct led_pwmm_obj_
{
	//亮度参数+++++++++++++++++++++++++++++++++
	#define  XT_LEDMM_BG_MIN        10UL      //亮度可调光范围的最小值（单位：‰）
	#define  XT_LEDMM_BG_MAX        1000UL    //亮度可调光范围的最大值（单位：‰）
	uint16_t brightness;                      //相对亮度（10~1000‰）
	uint8_t  led_flag;                        //工作标志（bit0=1:关灯,bit1=1:手控上调,bit2=1:手控下调,bit3=1:全程渐变时间(渐变速率)
	                                          //          bit4=1:应用控制锁,bit5=1:保存参数,bit6=1:禁止控制,bit7=1:过载保护）
	//渐变参数+++++++++++++++++++++++++++++++++
	uint8_t  seg_flag;                        //换算关系标志（[bit0-1]->保留,[bit2-3]->tik:pwm,[bit4-5]->保留,[bit6-7]->保留）
	
	uint16_t tik_pwm_q[XT_LEDMM_COLOR];       //商值 ◆◆渐变行程【节拍数】与【PWM值】的换算关系◆◆
	uint16_t tik_pwm_w[XT_LEDMM_COLOR];       //关系式分界（PWM值）
	uint16_t tik_pwm_c[XT_LEDMM_COLOR];       //一个PWM多节拍计数
	
	#define  XT_LEDMM_RUN_TIK_FULL_EN         //使能时间支持全程渐变(即指定渐变速率)
	uint16_t run_tik[XT_LEDMM_COLOR];         //现场行程渐变时间节拍数（节拍周期为[XT_LEDMM_ONE_TKMS]）
	uint16_t end_pwm[XT_LEDMM_COLOR];         //最终PWM值（亮灯值）
	
	#define  XT_LEDMM_CC_TM0S1      20UL      //默认的[换色]渐变时间（@0.1秒）( | 0x8000 表示全程渐变时间，即指定渐变速率)
	#define  XT_LEDMM_MIN_TM0S1     1UL       //输入控制的最短渐变时间（@0.1秒）-> 固化为0.1秒，不建议改！
	#define  XT_LEDMM_MAX_TM0S1     1000UL    //输入控制的最长渐变时间（@0.1秒）-> 固化为100秒，不建议改！
	#define  XT_LEDMM_ONE_TKMS      2UL       //调光调色的渐变节拍周期（@2ms）---> 固化为2毫秒，不建议改！
	//uint8_t  tm_cnt;                        //通用周期计数器（与 xt_led_pwmm_isr_loop() 调用频率相关：每[XT_LEDMM_ONE_TKMS]ms一次）
	
	//色温参数+++++++++++++++++++++++++++++++++
	#if (XT_LEDMM_COLOR == 2)
	#define  XT_LEDMM_FULL_CL_27_65_EN        //使能色温支持27~65色阶换算控制（屏蔽则只支持0~100%等级控制）→ ★可剪裁★
	uint8_t  full_cl[XT_LEDMM_COLOR];         //单通道最亮%值（[0]冷色，[1]暖色）
	#endif
}led_pwmm_obj_t;

//参数检测+++++++++++++++++++++++++++++++++++++
#if ((XT_LEDMM_PWM_MAX+1) > 65535UL) || (((XT_LEDMM_PWM_MAX+1) % XT_LEDMM_PWM_SUM_DIVISOR) != 0) || ((1000000 % XT_LEDMM_PWM_SUM_DIVISOR) != 0) \
||  ((XT_LEDMM_COLOR == 2) && ((1000UL/*亮度‰*/ * 100UL/*色温%*/) > (0xFFFFFFFF / ((XT_LEDMM_PWM_MAX+1)/XT_LEDMM_PWM_SUM_DIVISOR))))
#error "[XT_LEDMM_PWM_MAX][XT_LEDMM_PWM_SUM_DIVISOR] config error!"
#endif
#if (XT_LEDMM_BG_MIN <= 0) || (XT_LEDMM_BG_MAX != 1000)
#error "[XT_LEDMM_BG_MIN][XT_LEDMM_BG_MAX] config error!"
#endif
#if (defined XT_LEDMM_MB_LIMIT1) && (defined XT_LEDMM_MB_LIMIT2) && (defined XT_LEDMM_MB_LIMIT3) \
&& ((XT_LEDMM_MB_LIMIT1 >= XT_LEDMM_MB_LIMIT2) || (XT_LEDMM_MB_LIMIT2 >= XT_LEDMM_MB_LIMIT3) \
||  (XT_LEDMM_BG_MIN    >= XT_LEDMM_MB_LIMIT1) || (XT_LEDMM_MB_LIMIT3 >= XT_LEDMM_BG_MAX))
#error "[XT_LEDMM_MB_LIMIT1][XT_LEDMM_MB_LIMIT2][XT_LEDMM_MB_LIMIT3][XT_LEDMM_BG_MIN][XT_LEDMM_BG_MAX] config error!"
#endif
#if ((XT_LEDMM_MAX_TM0S1/*@0.1秒*/ * 10UL) > 65535UL)
#error "[XT_LEDMM_MAX_TM0S1] config error!"
#endif
#if ((XT_LEDMM_MAX_TM0S1 * 100UL / XT_LEDMM_ONE_TKMS) > 0xFFFF)
#error "[XT_LEDMM_MAX_TM0S1][XT_LEDMM_ONE_TKMS] config error!"
#endif
#if ((100UL/*@ms*/ % XT_LEDMM_ONE_TKMS) != 0) || (XT_LEDMM_ONE_TKMS > 10)
#error "[XT_LEDMM_ONE_TKMS] config error!"
#endif
#if (XT_LEDMM_COLOR != 1) && (XT_LEDMM_COLOR != 2)
#error "[XT_LEDMM_COLOR] config error!"
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 操作函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern uint16_t xt_led_pwmm_brightness_get(void);                         //获取亮度‰
extern uint8_t xt_led_pwmm_color_temp_get(void);                          //获取色温%
extern void xt_led_pwmm_cct_set(uint8_t c, uint16_t v, uint16_t t);       //LED色温设置操作
extern void xt_led_pwmm_isr_loop(void);       //LED调色调光运转函数（在中断中运行）(在硬件定时器定时调用)
extern void xt_led_pwmm_chip_init(void);      //LED内核级初始化函数（应在其它中断初始化前操作）
extern void xt_led_pwmm_dev_init(void);       //LED芯片级初始化函数（本函数会读取EEPROM数据）
extern void xt_led_pwmm_msg_init(void);       //LED应用级初始化函数

#ifdef __cplusplus
    }
#endif
