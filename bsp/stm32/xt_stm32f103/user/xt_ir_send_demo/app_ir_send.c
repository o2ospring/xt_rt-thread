/**
  * @file  app_ir_send.c
  * @brief 发送红外遥控码演示
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-26     o2ospring    原始版本
  */
#define   APP_IR_SEND_C__
#include "app_ir_send.h"
#if (defined(XT_APP_DEBUG) && ((XT_APP_DEBUG == 20221126) || (XT_APP_DEBUG == 20221203) || (XT_APP_DEBUG == 20221216)))
#if (defined(XT_APP_IRSEND_EN) && (XT_APP_IRSEND_EN == XT_DEF_ENABLED))
#ifdef    APP_IR_SEND_X__
#undef    APP_IR_SEND_H__
#include "app_ir_send.h"
#endif

//红外发送服务对象
xt_irsend_obj_t app_irsend_obj; //对象
uint16_t app_irsend_buf[1024];  //缓冲

//美的空调开关机指令（时间码：默认为有载波时间、无载波时间、有、无、…，直接发送即可）（单位：@1us，频率：38KHz）
const uint16_t data_midea_on []={0x1148,0x1165,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x1640,0x1148,0x1165,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205};
const uint16_t data_midea_off[]={0x1148,0x1165,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x1640,0x1148,0x1165,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x023D,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205,0x0676,0x0205};

//美的空调开关机指令（压缩码：需要解码得出时间码，优点为数据包很小，方便串口传输数据）（单位：@1us，频率：38KHz）
const uint8_t  code_midea_on []={0xA7,0x79,0x7E,0x0C,0x4D,0xC9,0x8F,0xA9,0xEC,0x80,0x52,0x44,0x0A,0x53,0xE2,0x2C,0x7B,0xCE,0xA0,0xA9,0xEA,0xF8,0x9A,0x60,0xDC,0x0B,0x10,0xC0,0x08,0x4C,0x1C,0x7A,0x44,0x53,0x68,0x9E,0xAF,0x4C,0x30,0x00,0xFA,0x8F,0x20,0x19,0x1A,0x89,0xA3,0xEE,0xEA,0x5F,0x7C,0x8F};
const uint8_t  code_midea_off[]={0xA7,0x79,0x7E,0x0C,0x4D,0xC9,0x8F,0xA9,0xEC,0x80,0x52,0x44,0x0A,0x53,0xE2,0x2C,0x7B,0xCE,0xA0,0xA9,0xEA,0xF8,0x9A,0x60,0xDC,0x0B,0x10,0xE3,0x2B,0x49,0x19,0x7A,0x44,0x53,0x68,0x9E,0xAF,0x4C,0x30,0x00,0xFA,0x8F,0x20,0x19,0x1A,0x89,0xA3,0xCD,0xC9,0x5A,0x79,0x8F};

//函数声明
void app_irsend_open_cb(const xt_irsend_obj_t *p_ob);
void app_irsend_close_cb(const xt_irsend_obj_t *p_ob);
void app_irsend_complete_cb(const xt_irsend_obj_t *p_ob);
void app_irsend_open(void);
void app_irsend_close(void);
void app_irsend_switch(int argc, char *argv[]);
void app_irsend_data(int argc, char *argv[]);
void app_irsend_code(int argc, char *argv[]);
void app_irsend_help(void);

/**
  * @brief  红外发送服务[打开]操作成功协同回调
  * @param  *p_ob      红外发送服务对象
  * @return void
  */
void app_irsend_open_cb(const xt_irsend_obj_t *p_ob)
{
	//XT_IRSEND_TASK_LOCKED(); //>>>>>>>>>>>>>>
	//...
	//XT_IRSEND_TASK_UNLOCK(); //<<<<<<<<<<<<<<
}

/**
  * @brief  红外发送服务[关闭]操作成功协同回调
  * @param  *p_ob      红外发送服务对象
  * @return void
  */
void app_irsend_close_cb(const xt_irsend_obj_t *p_ob)
{
	//XT_IRSEND_TASK_LOCKED(); //>>>>>>>>>>>>>>
	//...
	//XT_IRSEND_TASK_UNLOCK(); //<<<<<<<<<<<<<<
}

/**
  * @brief  红外发送刚刚[完成]通知回调
  * @param  *p_ob      红外发送服务对象
  * @return void
  */
void app_irsend_complete_cb(const xt_irsend_obj_t *p_ob)
{
	//注意：在中断中通知!!
	//根据实际通知应用程序...
}

/**
  * @brief  [打开]红外发送服务
  * @param  void
  * @return void
  */
void app_irsend_open(void)
{
	app_irsend_obj.end_us               = 100000;                 //发完1帧红外码后强行插入间隔时间（单位:us）
	app_irsend_obj.ir_khz               = 38;                     //红外载波频率（预设）（单位:KHz）
	app_irsend_obj.ir_num               = 0;                      //红外发送通道编号（＜IRSEND_SUM）
	app_irsend_obj.send_buf_size        = sizeof(app_irsend_buf); //红外发送缓冲大小（单位：字节）
	app_irsend_obj.p_send_buf           = app_irsend_buf;         //红外发送缓冲
	app_irsend_obj.p_irsend_open_fn     = app_irsend_open_cb;     //红外发送服务[打开]操作成功协同回调
	app_irsend_obj.p_irsend_close_fn    = app_irsend_close_cb;    //红外发送服务[关闭]操作成功协同回调
	app_irsend_obj.p_irsend_complete_fn = app_irsend_complete_cb; //红外发送刚刚[完成]通知回调
	app_irsend_obj.p_hw_open_fn         = 0;                      //本应用模块不提供硬件驱动程序
	if (xt_irsend_open(&app_irsend_obj) < 0)
	{
		rt_kprintf("xt_irsend_open return error!\r\n");
	}
}
FINSH_FUNCTION_EXPORT(app_irsend_open, app_irsend_open);
MSH_CMD_EXPORT(app_irsend_open, app_irsend_open);

/**
  * @brief  [关闭]红外发送服务
  * @param  void
  * @return void
  */
void app_irsend_close(void)
{
	if (xt_irsend_close(&app_irsend_obj) < 0)
	{
		rt_kprintf("xt_irsend_close return error!\r\n");
	}
}
FINSH_FUNCTION_EXPORT(app_irsend_close, app_irsend_close);
MSH_CMD_EXPORT(app_irsend_close, app_irsend_close);

/**
  * @brief  [开关]红外发送服务
  * @param  argc       入口参数数量
  * @param  argv       入口相关参数
  * @return void
  */
void app_irsend_switch(int argc, char *argv[])
{
	uint32_t n = atoi(argv[1]);
	
	if ((argc != 2) || (n > 1))
	{
		rt_kprintf("app_irsend_switch input arg error!\r\n");
		return;
	}
	if (n == 1)
	{	//打开模块（命令: app_irsend_switch 1）
		app_irsend_open();
	}
	else
	{	//关闭模块（命令: app_irsend_switch 0）
		app_irsend_close();
	}
}
FINSH_FUNCTION_EXPORT(app_irsend_switch, app_irsend_switch 1 or 0);
MSH_CMD_EXPORT(app_irsend_switch, app_irsend_switch 1 or 0);

/**
  * @brief  [发送]红外码示例【直接发送时间码】
  * @param  argc       入口参数数量
  * @param  argv       入口相关参数
  * @return void
  */
void app_irsend_data(int argc, char *argv[])
{
	uint32_t n = atoi(argv[1]);
	
	if ((argc != 2) || (n > 1))
	{
		rt_kprintf("app_irsend_data input arg error!\r\n");
		return;
	}
	if (n == 1)
	{	//打开空调（测试命令: app_irsend_data 1）
		if (xt_irsend_send(&app_irsend_obj, data_midea_on , sizeof(data_midea_on) , 1/*us*/, 38/*KHz*/) < 0)
		{
			rt_kprintf("xt_irsend_send return error!\r\n");
		}
	}
	else
	{	//关闭空调（测试命令: app_irsend_data 0）
		if (xt_irsend_send(&app_irsend_obj, data_midea_off, sizeof(data_midea_off), 1/*us*/, 38/*KHz*/) < 0)
		{
			rt_kprintf("xt_irsend_send return error!\r\n");
		}
	}
}
FINSH_FUNCTION_EXPORT(app_irsend_data, app_irsend_data 1 or 0);
MSH_CMD_EXPORT(app_irsend_data, app_irsend_data 1 or 0);

/**
  * @brief  [发送]红外码示例【一边发一边解码】
  * @param  argc       入口参数数量
  * @param  argv       入口相关参数
  * @return void
  */
void app_irsend_code(int argc, char *argv[])
{
	uint32_t n = atoi(argv[1]);
	
	if ((argc != 2) || (n > 1))
	{
		rt_kprintf("app_irsend_code input arg error!\r\n");
		return;
	}
	if (n == 1)
	{	//打开空调（测试命令: app_irsend_code 1）
		uint8_t buf[sizeof(code_midea_on)];
		memcpy(buf, code_midea_on, sizeof(code_midea_on));
		n = Api_Ir_ConvCode(buf, sizeof(code_midea_on));                  /*初步解码*/
		if (xt_irsend_decode_send(&app_irsend_obj, buf, n, Api_Ir_DataSend/*解码函数*/) < 0)
		{
			rt_kprintf("xt_irsend_decode_send return error!\r\n");
		}
	}
	else
	{	//关闭空调（测试命令: app_irsend_code 0）
		uint8_t buf[sizeof(code_midea_off)];
		memcpy(buf, code_midea_off, sizeof(code_midea_off));
		n = Api_Ir_ConvCode(buf, sizeof(code_midea_off));                 /*初步解码*/
		if (xt_irsend_decode_send(&app_irsend_obj, buf, n, Api_Ir_DataSend/*解码函数*/) < 0)
		{
			rt_kprintf("xt_irsend_decode_send return error!\r\n");
		}
	}
}
FINSH_FUNCTION_EXPORT(app_irsend_code, app_irsend_code 1 or 0);
MSH_CMD_EXPORT(app_irsend_code, app_irsend_code 1 or 0);

#endif  //#if (XT_APP_IRSEND_EN == XT_DEF_ENABLED)
#endif
