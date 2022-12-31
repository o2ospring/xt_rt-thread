<!-- +++
author = "XT"
comments = false
date  = "2022-11-26"
draft = false
share = false
image = ""
menu  = ""
slug  = ""
title = "发送红外遥控码演示"
+++ -->

### 简介

使用【xt_ir_send】红外发送服务模块，演示遥控【美的】空调开关机，包括两种方式发送：一、直接发送红外码；二、对压缩码边解码边发送。

### 演示

1、在 "application.h" 头文件加入下面宏定义，开启发送红外遥控码演示，并且重新编译程序。

```c
#define XT_APP_DEBUG                    20221126                        /* 开启演示                     */

#define __XT_IR_SEND_REMAP_H
#ifndef XT_APP_IRSEND_EN
#define XT_APP_IRSEND_EN                XT_DEF_ENABLED                  /* 红外遥控发送服务模块         */
#endif
```

2、下载运行程序，利用 rt-thread 的调试串口，输入下面命令进行测试。

```bash
app_irsend_open    #【打开】红外发送服务
app_irsend_data 1  #【发送】红外码：直接发送〖开机〗红外码
app_irsend_data 0  #【发送】红外码：直接发送〖关机〗红外码
app_irsend_code 1  #【发送】红外码：对压缩码边解码边发送〖开机〗红外码
app_irsend_code 0  #【发送】红外码：对压缩码边解码边发送〖关机〗红外码
app_irsend_close   #【关闭】红外发送服务
```
