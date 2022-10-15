####################################################
# 1、配置编译相关参数、编译文件(夹)、目标及中间文件
####################################################

# 定义生成目标，包括其路径及文件名【只能是一个对象】
LIB    = ../build/gcc/hal.a

# 定义中间文件夹，用于存放中间文件【只能是一个对象】
OBJS_D = ../build/gcc

# 添加编译源文件，包括路径及文件名【多个用空格分隔】
# xxx.s复制来源: HAL库\Drivers\CMSIS\Device\ST\STM32F1xx\Source\Templates\gcc
SRCS_F = ../../libraries/STM32F1xx_HAL/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c                      \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc.c                  \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc_ex.c               \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_can.c                  \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c               \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_crc.c                  \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dac.c                  \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dac_ex.c               \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c                  \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c                \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c             \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c                 \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c              \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2c.c                  \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2s.c                  \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_iwdg.c                 \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c                  \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c               \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rtc.c                  \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rtc_ex.c               \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.c                  \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c                  \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c               \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c                 \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_usart.c                \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_wwdg.c

# 添加编译文件夹，要指定文件扩展名【多个用空格分隔】
SRCS_D = 

# 添加编译库文件，包括路径及文件名【多个用空格分隔】
LIBS_F = 

# 添加源码文件及包含文件所在的路径【多个用空格分隔】
SRCS_I = ../board                                 \
         ../board/ports/include                   \
         ../board/CubeMX_Config/Inc               \
         ../../libraries/HAL_Drivers                                     \
         ../../libraries/HAL_Drivers/config                              \
         ../../libraries/HAL_Drivers/CMSIS/Include                       \
         ../../libraries/STM32F1xx_HAL/CMSIS/Device/ST/STM32F1xx/Include \
         ../../libraries/STM32F1xx_HAL/STM32F1xx_HAL_Driver/Inc          \
         ../../libraries/STM32F1xx_HAL/CMSIS/Include

# 定义编译器及其环境相关参数
include ../envi.rule
CFLAG_O += -Wall -Og

# 包含[Makefile]脚本公共代码
include ../make.rule

