/**
  * @file  app_debug.c
  * @brief 应用临时调试
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-11-27     o2ospring    原始版本
  */
#define   APP_DEBUG_C__
#include "app_debug.h"
#ifdef RT_USING_FINSH
#ifdef    APP_DEBUG_X__
#undef    APP_DEBUG_H__
#include "app_debug.h"
#endif

#if (XT_APP_WIZNET_EN == XT_DEF_ENABLED)
#ifdef XT_APP_DEBUG
#include "xt_wiznet.h"
void dhcpset(void) //开启动态IP
{
	xt_net_set_dhcp();
}
FINSH_FUNCTION_EXPORT(dhcpset, dhcpset);
MSH_CMD_EXPORT(dhcpset, dhcpset);

void ipset(void) //设置固定IP
{
	unsigned char ip[4] = {192,168,3,148};
	unsigned char gw[4] = {192,168,3,1};
	unsigned char sn[4] = {255,255,255,0};
	xt_net_set_ipgwsn(ip, gw, sn);
}
FINSH_FUNCTION_EXPORT(ipset, ipset);
MSH_CMD_EXPORT(ipset, ipset);

void ipget(void) //读取当前IP
{
	unsigned char ip[4];
	unsigned char gw[4];
	unsigned char sn[4];
	xt_net_get_ipgwsn(ip, gw, sn);
	rt_kprintf("ip:%d.%d.%d.%d\r\n", ip[0], ip[1], ip[2], ip[3]);
	rt_kprintf("gw:%d.%d.%d.%d\r\n", gw[0], gw[1], gw[2], gw[3]);
	rt_kprintf("sn:%d.%d.%d.%d\r\n", sn[0], sn[1], sn[2], sn[3]);
}
FINSH_FUNCTION_EXPORT(ipget, ipget);
MSH_CMD_EXPORT(ipget, ipget);

void netrestart(void) //复位网络
{
	xt_net_set_restart();
}
FINSH_FUNCTION_EXPORT(netrestart, netrestart);
MSH_CMD_EXPORT(netrestart, netrestart);
#endif
#endif

#endif
