/**
  * @file  xt_wiznet.h
  * @brief 网络服务模块（目前只针对 WIZnet Hardwired TCP/IP Chips (WIZCHIP)）
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-12-10     o2ospring    原始版本
  */
#include <stdint.h> //////////////////////// <- 使用的数据定义，如: int8_t, uint32_t 等
#include <string.h> //////////////////////// <- 使用的字符处理，如: strcpy(), memcpy() 等
#include "bsp_stm32f1xx_id.h" ////////////// <- 使用芯片机身码生成MAC函数
#include "wizchip_conf.h" ////////////////// <- 依赖WIZnet(wizchip)硬件TCP/IP协议栈(包含:xt_wiznet_port.h)

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 参数配置 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

#define XT_NET_HW_DRIVERS_EN     1            //是否使用本模块自带硬件驱动（0:不使用,1:STM32F1xx-SPI）
//#define XT_NET_PIN_INIT                     //使能定义:将控制引脚初始化操作放到本模块线程中完成（但需要手工取消board.c的初始化）
//#define XT_NET_CFG_INIT                     //使能定义:将网络芯片初始化操作放到本模块线程中完成（但需要手工取消board.c的初始化）
#define XT_NET_PRINTF(...)       rt_kprintf("wiznet:" __VA_ARGS__)            //工作大流程打印

#if (defined(XT_WIZNET_C__) && (XT_APP_WIZNET_EN == XT_DEF_ENABLED))
#if 1 //////////////////////////////////////////
// a)上电初始网络工作于[DHCP]模式
#define XT_NET_INIT1()           bsp_unique_id_generate(xt_netcfg.mac, 6);                   /*生成 MAC*/\
                                 xt_net_set_mac(xt_netcfg.mac);                              /*设置 MAC*/\
                                 xt_net_set_dhcp()                                           /*开启DHCP*/\
                                                                              //上电设置网络IP(固定IP)。注：被 xt_net_pin_init() 调用
#define XT_NET_INIT2()           /*此处可从[EEPROM]读取参数对网络进一步设置*/ //上电设置网络IP(可改IP)。注：被 xt_net_cfg_init() 调用
#else //////////////////////////////////////////
// b)上电初始网络工作于[静态IP]模式
uint8_t xt_net_ip[4] = {192, 168,  1 , 101};
uint8_t xt_net_gw[4] = {192, 168,  1 ,  1 };
uint8_t xt_net_sn[4] = {255, 255, 255,  0 };
#define XT_NET_INIT1()           bsp_unique_id_generate(xt_netcfg.mac, 6);                   /*生成 MAC*/\
                                 xt_net_set_mac(xt_netcfg.mac);                              /*设置 MAC*/\
                                 xt_net_set_ipgwsn(xt_net_ip, xt_net_gw, xt_net_sn)          /*设置网络*/\
                                                                              //上电设置网络IP(固定IP)。注：被 xt_net_pin_init() 调用
#define XT_NET_INIT2()           /*此处可从[EEPROM]读取参数对网络进一步设置*/ //上电设置网络IP(可改IP)。注：被 xt_net_cfg_init() 调用
#endif
#endif

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 数据类型 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

typedef struct xt_net_
{
	volatile uint16_t rstver;    //复位版本（bit15只作为标志位,=0表示准备或复位中,=1完成复位）
	volatile uint16_t lnkver;    //LINK版本（bit15只作为标志位,=0网线断开或连接中,=1网线连接）
	volatile uint8_t  newrst;    //新复位操作标志
	uint8_t  dhcp;               //是否开启DHCP
	uint8_t  mac[6];             //MAC地址
	uint8_t  ip[4];              //IP地址
	uint8_t  gw[4];              //网关
	uint8_t  sn[4];              //子网掩码
	uint8_t  dns[4];             //DNS地址
}xt_net_t; 

/********************************************************************************************************/
/*++++++++++++++++++++++++++++++++++++++++++++++ 操作函数 ++++++++++++++++++++++++++++++++++++++++++++++*/
/********************************************************************************************************/

extern void xt_net_pin_init(void);                                      /* 硬件引脚初始化               */
extern void xt_net_cfg_init(void);                                      /* 网络参数初始化               */
extern void xt_net_ipc_init(void);                                      /* 网络信息初始化               */
extern void xt_net_thread_init(void);                                   /* 网络线程初始化               */

extern uint16_t xt_net_get_rstver(void);                                /* 获取:复位版本                */
extern uint16_t xt_net_get_lnkver(void);                                /* 获取:LINK版本                */
extern uint8_t xt_net_get_dhcp(void);                                   /* 获取:DHCP是否开启            */
extern uint8_t xt_net_get_mac(uint8_t *mac);                            /* 获取:MAC地址                 */
extern uint8_t xt_net_get_ip(uint8_t *ip);                              /* 获取:IP地址                  */
extern uint8_t xt_net_get_gw(uint8_t *gw);                              /* 获取:网关地址                */
extern uint8_t xt_net_get_sn(uint8_t *sn);                              /* 获取:子网掩码                */
extern uint8_t xt_net_get_dns(uint8_t *dns);                            /* 获取:DNS地址                 */
extern uint8_t xt_net_get_ipgwsn(uint8_t *ip, uint8_t *gw, uint8_t *sn);/* 获取:网络地址                */
extern uint8_t xt_net_chk_ip(uint8_t *ip);                              /* 检测:IP地址是否为同一网段    */

extern void xt_net_set_restart(void);                                   /* 操作:复位网络                */
extern void xt_net_set_dhcp(void);                                      /* 操作:使能自动设置IP          */
extern void xt_net_set_ipgwsn(const uint8_t *ip, const uint8_t *gw, const uint8_t *sn); /* 操作:使能手动设置IP          */
extern void xt_net_set_mac(const uint8_t *mac);                         /* 操作:设置MAC地址             */
extern void xt_net_set_dns(const uint8_t *dns);                         /* 操作:设置DNS地址             */

//extern void xt_socket_ot_rst(uint8_t s);
//extern void xt_socket_ot_set(uint8_t s, XT_WIZ_OS_TICK_T ostick, uint8_t flag);
//extern uint16_t xt_socket_recv_chk(uint8_t s);
//extern uint8_t xt_socket_chk(uint8_t s, uint8_t protocol, uint8_t server);

//extern int8_t  socket(uint8_t sn, uint8_t protocol, uint16_t port, uint8_t flag);
//extern int8_t  close(uint8_t sn);
//extern int8_t  listen(uint8_t sn);
//extern int8_t  connect(uint8_t sn, uint8_t * addr, uint16_t port);
//extern int8_t  disconnect(uint8_t sn);
//extern int32_t send(uint8_t sn, uint8_t * buf, uint16_t len);
//extern int32_t recv(uint8_t sn, uint8_t * buf, uint16_t len);
//extern int32_t sendto(uint8_t sn, uint8_t * buf, uint16_t len, uint8_t * addr, uint16_t port);
//extern int32_t recvfrom(uint8_t sn, uint8_t * buf, uint16_t len, uint8_t * addr, uint16_t *port);
//extern int8_t  ctlsocket(uint8_t sn, ctlsock_type cstype, void* arg);
//extern int8_t  setsockopt(uint8_t sn, sockopt_type sotype, void* arg);
//extern int8_t  getsockopt(uint8_t sn, sockopt_type sotype, void* arg);

//extern void xt_net_dhcp_reset(void);
//extern void xt_net_dhcp_ipget(uint8_t *ip, uint8_t *gw, uint8_t *sn);
//extern uint8_t xt_net_chk_socket_reset(void);

#ifdef __cplusplus
	}
#endif
