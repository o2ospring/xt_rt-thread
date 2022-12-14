####################################################
# 1、定义编译器及环境公共参数，方便不同环境/平台移植
####################################################

SZ = arm-none-eabi-size
CP = arm-none-eabi-objcopy
AS = arm-none-eabi-gcc -x assembler-with-cpp
CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar
DB = arm-none-eabi-gdb
RM = rm
CFLAG_L =    -mcpu=cortex-m3 -mthumb -specs=nano.specs -T$(LDS_F) -Wl,-Map=$(TARGET).map,--cref -Wl,--gc-sections
CFLAG_O = -c -mcpu=cortex-m3 -mthumb -fdata-sections -ffunction-sections $(addprefix -D,$(sort $(G_DEF))) -Wa,-a,-ad,-alms=$(@:.o=.lst)
AFLAG_O = -c -mcpu=cortex-m3 -mthumb -fdata-sections -ffunction-sections $(addprefix -D,$(sort $(G_DEF)))
CFLAG_M = -MMD -MP -MF"$(@:%.o=%.d)"
ARFLAGS = rcs
RMFLAGS = -fr
MKDIR   = mkdir -p
#ECHO_SET = @set -e
#ECHO_END = 
VPATH  := $(SRCS_I)
SRCS_I := $(addprefix -I,$(SRCS_I) $(dir $(SRCS_F) $(SRCS_D)))

ifdef DEBUG
ifneq ($(DEBUG),0)
CFLAG_O += -g -gdwarf-2
endif
endif

ifdef TARGET
DEBUG_CMD = cgdb -d $(DB) \
-ex  'set remotetimeout 60' \
-iex 'target extended-remote | openocd -c "gdb_port pipe" -f "interface/jlink_swd.cfg" -f "target/stm32f1x.cfg"' \
-ex  'monitor sleep 1000' \
-ex  'monitor reset halt' \
-ex  'monitor sleep 1000' \
-ex  'file $(TARGET).elf' \
-ex  'load' \
-ex  'tb main' \
-ex  'c'
endif

ifdef TARGET
DOWNLOAD_CMD = openocd \
-f interface/jlink_swd.cfg -f target/stm32f1x.cfg \
-c init -c halt \
-c "reset halt; wait_halt; flash write_image erase $(TARGET).hex" \
-c reset -c shutdown
endif
