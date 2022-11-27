####################################################
# 1、配置编译相关参数、编译文件(夹)、目标及中间文件
####################################################

# 定义生成目标，包括其路径及文件名【只能是一个对象】
TARGET = ../build/gcc/rt-thread

# 定义中间文件夹，用于存放中间文件【只能是一个对象】
OBJS_D = ../build/gcc

# 添加编译源文件，包括路径及文件名【多个用空格分隔】
# xxx.s复制来源: HAL库\Drivers\CMSIS\Device\ST\STM32F1xx\Source\Templates\gcc
SRCS_F = \
         ../user/xt_ir_send_demo/app_ir_send.c \
         ../user/xt_ir_send_demo/app_ir_huilink.c \
         \
         ../modules/xt_ir_send/xt_ir_send_remap.h \
         \
         ../xt_modules/xt_macro/xt_comdef.h \
         ../xt_modules/xt_macro/xt_llist.h \
         ../xt_modules/xt_ir_send/xt_ir_send.c \
         ../xt_modules/xt_ir_send/xt_ir_send_pwm_dma_stm32f1xx_hal.c \
         \
         ./main.c \
         ./application.c \
         ./application.h \
         ../rtconfig.h \
         ./cpuusage.c \
         ./app_debug.c \
         ./app_debug.h \
         \
         ../../../../components/drivers/misc/pin.c \
         ../../../../components/drivers/serial/serial.c \
         \
         ../board/board.c \
         ../board/board.h \
         ../board/stm32f1xx_hal_conf.h \
         ../board/stm32f1xx_hal_msp.c \
         ../board/bsp_stm32f1xx_it.c \
         ../board/bsp_stm32f1xx_swj.c \
         ../board/bsp_stm32f1xx_exti.c \
         ../board/bsp_stm32f1xx_uart.c \
         ../board/bsp_stm32f1xx_spi.c \
         ../board/bsp_stm32f1xx_tim.c \
         ../board/bsp_stm32f1xx_pwm.c \
         ../board/bsp_stm32f1xx_flash_sz.c \
         ../board/bsp_stm32f1xx_id.c \
         ../board/bsp_stm32f1xx_crc.c \
         ../board/bsp_stm32f1xx_wdg.c \
         ../board/bsp_stm32f1xx_adc.c \
         \
         ../../libraries/HAL_Drivers/drv_gpio.c \
         ../../libraries/HAL_Drivers/drv_usart.c \
         ../../libraries/HAL_Drivers/drv_common.c \
         \
         ../$(STM32F103XX_ASM) \
         \
         ../../../../components/finsh/shell.c

# 添加编译文件夹，要指定文件扩展名【多个用空格分隔】
SRCS_D = 

# 添加编译库文件，包括路径及文件名【多个用空格分隔】
LIBS_F = ../build/gcc/hal.a \
         ../build/gcc/rtt.a

# 添加源码文件及包含文件所在的路径【多个用空格分隔】
SRCS_I = ../../../../include \
         ../../../../components/drivers/include \
         ../../../../components/drivers/include/drivers \
         ../../../../components/finsh \
         \
         ../../libraries/HAL_Drivers \
         ../../libraries/HAL_Drivers/config \
         ../../libraries/HAL_Drivers/CMSIS/Include \
         ../../libraries/STM32F1xx_HAL/CMSIS/Device/ST/STM32F1xx/Include \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Inc \
         ../../libraries/STM32F1xx_HAL/CMSIS/Include \
         \
         ./ \
         ../ \
         ../applications \
         ../board \
         ../board/ports/include \
         \
         ../modules/xt_ir_send \
         ../xt_modules/xt_ir_send \
         ../xt_modules/xt_macro \
         \
         ../user/xt_ir_send_demo

# 添加链接脚本文件，含路径和文件名【只能是一个对象】
LDS_F  = ../$(STM32F103XX_LD)

# 定义编译器及其环境相关参数
include ../envi.rule
CFLAG_O += -Wall -Og

# 包含[Makefile]脚本公共代码
include ../make.rule

