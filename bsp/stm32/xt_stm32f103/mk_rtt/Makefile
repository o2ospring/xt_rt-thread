####################################################
# 1、配置编译相关参数、编译文件(夹)、目标及中间文件
####################################################

# 定义生成目标，包括其路径及文件名【只能是一个对象】
LIB    = ../build/gcc/rtt.a

# 定义中间文件夹，用于存放中间文件【只能是一个对象】
OBJS_D = ../build/gcc

# 添加编译源文件，包括路径及文件名【多个用空格分隔】
# xxx.s复制来源: HAL库\Drivers\CMSIS\Device\ST\STM32F1xx\Source\Templates\gcc
SRCS_F = ../../../../components/drivers/ipc/completion.c  \
         ../../../../components/drivers/ipc/dataqueue.c   \
         ../../../../components/drivers/ipc/pipe.c        \
         ../../../../components/drivers/ipc/ringblk_buf.c \
         ../../../../components/drivers/ipc/ringbuffer.c  \
         ../../../../components/drivers/ipc/waitqueue.c   \
         ../../../../components/drivers/ipc/workqueue.c   \
         \
         ../../../../libcpu/arm/common/backtrace.c        \
         ../../../../libcpu/arm/common/div0.c             \
         ../../../../libcpu/arm/common/showmem.c          \
         ../../../../libcpu/arm/cortex-m3/cpuport.c       \
         ../../../../libcpu/arm/cortex-m3/context_gcc.S   \
         \
         ../../../../components/finsh/msh.c       \
         ../../../../components/finsh/msh_parse.c \
         ../../../../components/finsh/cmd.c       \
         \
         ../../../../src/clock.c                  \
         ../../../../src/components.c             \
         ../../../../src/device.c                 \
         ../../../../src/idle.c                   \
         ../../../../src/ipc.c                    \
         ../../../../src/irq.c                    \
         ../../../../src/kservice.c               \
         ../../../../src/mem.c                    \
         ../../../../src/mempool.c                \
         ../../../../src/object.c                 \
         ../../../../src/scheduler.c              \
         ../../../../src/signal.c                 \
         ../../../../src/thread.c                 \
         ../../../../src/timer.c

# 添加编译文件夹，要指定文件扩展名【多个用空格分隔】
SRCS_D = 

# 添加编译库文件，包括路径及文件名【多个用空格分隔】
LIBS_F = 

# 添加源码文件及包含文件所在的路径【多个用空格分隔】
SRCS_I = ../                                      \
         ../applications                          \
         ../../../../include                      \
         ../../../../components/drivers/include   \
         ../../../../components/drivers/include/drivers   \
         ../../../../components/drivers/include/ipc       \
         ../../../../components/finsh

# 定义编译器及其环境相关参数
include ../envi.rule
CFLAG_O += -Wall -Og

# 包含[Makefile]脚本公共代码
include ../make.rule

