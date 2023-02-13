/**
  * @file  app_wiznet.c
  * @brief 网络服务模块演示
  * COPYRIGHT (C) 2022, XT 技术联合小组
  * Change Logs:
  * Date           Author       Notes
  * 2022-12-10     o2ospring    原始版本
  */
#define   APP_WIZNET_C__
#include "app_wiznet.h"
#if (defined(XT_APP_DEBUG) && (XT_APP_DEBUG == 20221210))
#if (defined(XT_APP_WIZNET_EN) && (XT_APP_WIZNET_EN == XT_DEF_ENABLED))
#ifdef    APP_WIZNET_X__
#undef    APP_WIZNET_H__
#include "app_wiznet.h"
#endif

#ifndef XT_APP_INIT_2_TAB_EXPORT
#define XT_APP_INIT_2_TAB_EXPORT(func,desc)
#endif

ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t app_udp_thread_stack[512];
static struct rt_thread app_udp_thread;
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t app_tcp_thread_stack[512];
static struct rt_thread app_tcp_thread;

void app_wiznet_init(void);
void app_udp_thread_entry(void *p_arg);
void app_tcp_thread_entry(void *p_arg);

/**
  * @brief  演示线程初始化
  * @param  void
  * @return void
  */
void app_wiznet_init(void)
{
    rt_thread_init(&app_udp_thread, "app_udp", app_udp_thread_entry, RT_NULL,
    /**/            app_udp_thread_stack, sizeof(app_udp_thread_stack), 11, 4);
    rt_thread_startup(&app_udp_thread);
    
    rt_thread_init(&app_tcp_thread, "app_tcp", app_tcp_thread_entry, RT_NULL,
    /**/            app_tcp_thread_stack, sizeof(app_tcp_thread_stack), 12, 4);
    rt_thread_startup(&app_tcp_thread);
}
XT_APP_INIT_2_TAB_EXPORT(app_wiznet_init, "app_wiznet_init()");

/**
  * @brief  UDP 演示线程
  * @param  void
  * @return void
  */
void app_udp_thread_entry(void *p_arg)
{
    unsigned char *pbuf;
    uint16_t    wkver, lkver;
    uint16_t    len, port;    //端口
    uint8_t     ip[4];        //IP地址
    #define UDP_SK_NUM   0    //使用第几个socket,0~7
    #define UDP_SK_BUFSZ 10   //缓冲大小
    
    while (0 == (pbuf = rt_malloc(UDP_SK_BUFSZ)))
    {
        rt_thread_delay(1);
    }
    udp_socket:
    while (((wkver = xt_net_get_rstver()) & 0x8000) == 0)    //等待网络初始化完成
    {
        rt_thread_delay(1);
    }
    rt_thread_delay(100);
    rt_kprintf("socket 0: net restart!\r\n");
    udp_link:
    while (((lkver = xt_net_get_lnkver()) & 0x8000) == 0)    //等待插上网线
    {
        rt_thread_delay(1);
    }
    rt_kprintf("socket 0: net link up!\r\n");
    udp_build:
    socket(UDP_SK_NUM, Sn_MR_UDP, 1001, 0);                  //打开socket（UDP协议,本机端口:1001）
    rt_kprintf("socket 0: open!\r\n");
    while (1)
    {                                                        //如果socket异常,则...
        if (xt_socket_chk(UDP_SK_NUM, Sn_MR_UDP, 0) == 0) goto udp_build; 
        if (wkver != xt_net_get_rstver()) goto udp_socket;   //如果网络重启了,则...
        if (lkver != xt_net_get_lnkver()) goto udp_link;     //如果网线拔掉了,则...
        xt_socket_ot_set(UDP_SK_NUM, 0xFFFFFFFF/*永久*/, 0); //修改本次socket超时操作为永远（可在另一线程使用 xt_socket_ot_set(UDP_SK_NUM,0,0) 强制超时退出）
        len = xt_socket_recv_chk(UDP_SK_NUM);                //检测socket是否收到数据　　　（可在另一线程使用 xt_socket_ot_set(UDP_SK_NUM,0,0) 强制超时退出）
        len = len > UDP_SK_BUFSZ ? UDP_SK_BUFSZ : len;       //处理数据大小与缓冲大小关系
        len = recvfrom(UDP_SK_NUM, pbuf, len, ip, &port);    //socket接收数据（同时得到对端的IP及端口）
        xt_socket_ot_set(UDP_SK_NUM, 50, 0);                 //修改本次socket超时操作为50个系统节拍
        if (sendto(UDP_SK_NUM, pbuf, len, ip, port) != len)  //socket发送数据（把收到的数据返回给对端）
        {                                                    //UDP为无连接,socket发送可随时向目标发送
            rt_kprintf("socket 0: sendto return error!\r\n");
        }
    }
}

/**
  * @brief  TCP 客户端演示线程
  * @param  void
  * @return void
  */
void app_tcp_thread_entry(void *p_arg)
{
    unsigned char *pbuf;
    uint16_t    wkver, lkver, cnt;   
    uint16_t    rlen,  tlen,  port = 1002;  //对端端口!!!!!!
    uint8_t     ip[4] = {192, 168, 3, 222}; //对端IP地址!!!!
    uint8_t     t = 1;       //自动维持TCP连接(@5秒)
    #define TCP_SK_NUM   1   //使用第几个socket,0~7
    #define TCP_SK_BUFSZ 100 //缓冲大小
    
    while (0 == (pbuf = rt_malloc(TCP_SK_BUFSZ)))
    {
        rt_thread_delay(1);
    }
    tcp_socket:
    while (((wkver = xt_net_get_rstver()) & 0x8000) == 0)    //等待网络初始化完成
    {
        rt_thread_delay(1);
    }
    rt_thread_delay(300);
    rt_kprintf("socket 1: net restart!\r\n");
    tcp_link:
    while (((lkver = xt_net_get_lnkver()) & 0x8000) == 0)    //等待插上网线
    {
        rt_thread_delay(1);
    }
    rt_kprintf("socket 1: net link up!\r\n");
    while (1)
    {
        tcp_build:
        setsockopt(TCP_SK_NUM, SO_KEEPALIVEAUTO, &t);        //打开TCP连接自动维持(@5秒)(keepalive帧)
        do
        {
           if (wkver != xt_net_get_rstver()) goto tcp_socket;//如果网络重启了,则...
           if (lkver != xt_net_get_lnkver()) goto tcp_link;  //如果网线拔掉了,则...
           rt_thread_delay(2);
           
           socket(TCP_SK_NUM, Sn_MR_TCP, 1002, Sn_MR_ND);    //打开socket（TCP协议,本机端口:1002）
        }
        while (connect(TCP_SK_NUM, ip, port) <= 0);          //连接TCP服务端
        //rt_kprintf("socket 1: open and connected!\r\n");
        
        //setsockopt(TCP_SK_NUM, SO_KEEPALIVESEND, 0);       //如果没有打开TCP连接自动维持,则要求应用定时发送维持帧
        tlen = sizeof("tcp client send data!") - 1;
        memcpy(pbuf,  "tcp client send data!", tlen);
        if (send(TCP_SK_NUM, pbuf, tlen) != tlen)            //socket发送数据
        {
            rt_kprintf("socket 1: send len error!\r\n");
            disconnect(TCP_SK_NUM);                          //断开TCP连接
            close(TCP_SK_NUM);                               //关闭socket
            goto tcp_build;
        }
        for (cnt = 0; cnt < tlen; cnt += rlen)               //socket接收数据
        {
            xt_socket_ot_set(TCP_SK_NUM, 100/*1秒*/, 0);     //修改本次socket超时操作为1秒（可在另一线程使用 xt_socket_ot_set(TCP_SK_NUM,0,0) 强制超时退出）
            rlen = xt_socket_recv_chk(TCP_SK_NUM);           //检测socket是否收到数据　 　（可在另一线程使用 xt_socket_ot_set(TCP_SK_NUM,0,0) 强制超时退出）
            rlen = rlen > TCP_SK_BUFSZ ? TCP_SK_BUFSZ : rlen;//处理数据大小与缓冲大小关系
            rlen = recv(TCP_SK_NUM, pbuf, rlen);             //socket接收数据（要求服务端返回客户端发送数据）
            //break;
        }
                                                             //如果socket异常,则...
        if (xt_socket_chk(TCP_SK_NUM, Sn_MR_TCP, 0) == 0) goto tcp_build; 
        //if (wkver != xt_net_get_rstver()) goto tcp_socket;
        //if (lkver != xt_net_get_lnkver()) goto tcp_link;
        
        disconnect(TCP_SK_NUM);                              //断开TCP连接
        close(TCP_SK_NUM);                                   //关闭socket
        //rt_kprintf("socket 1: closed!\r\n");
    }
}

#endif  //#if (XT_APP_WIZNET_EN == XT_DEF_ENABLED)
#endif
