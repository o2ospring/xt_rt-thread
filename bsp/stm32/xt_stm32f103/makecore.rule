####################################################
# 2、根据上面的相关配置，生成包括路径的相关文件对象
####################################################

VPATH += $(dir $(SRCS_F) $(SRCS_D))
VPATH := $(addsuffix /,$(VPATH))
VPATH := $(subst //,/,$(VPATH))
VPATH := $(sort $(VPATH))
SRCS_I := $(addsuffix /,$(SRCS_I))
SRCS_I := $(subst //,/,$(SRCS_I))
SRCS_I := $(sort $(SRCS_I))
OBJS_D := $(addsuffix /,$(OBJS_D))
OBJS_D := $(subst //,/,$(OBJS_D))
#DEPS_D:= $(OBJS_D)
DIRS := $(sort $(OBJS_D) $(dir $(TARGET)) $(dir $(LIB)))
SRCS := $(filter %.c, $(SRCS_F) $(wildcard $(SRCS_D))) $(filter %.C, $(SRCS_F) $(wildcard $(SRCS_D))) $(filter %.s, $(SRCS_F)) $(filter %.S, $(SRCS_F))
OBJS := $(SRCS:.c=.o)
OBJS := $(OBJS:.C=.o)
OBJS := $(OBJS:.s=.o)
OBJS := $(OBJS:.S=.o)
OBJS := $(addprefix $(OBJS_D),$(notdir $(OBJS)))
DEPS := $(SRCS:.c=.d)
DEPS := $(DEPS:.C=.d)
DEPS := $(DEPS:.s=.d)
DEPS := $(DEPS:.S=.d)
DEPS := $(addprefix $(OBJS_D),$(notdir $(DEPS)))
OBJX := $(sort $(OBJS) $(patsubst %.o,%.lst,$(OBJS)) $(DEPS) $(addsuffix .tmp,$(DEPS)))
LIBS := $(sort $(LIBS_F))

ifdef SRCS_I
CFLAG_O += $(SRCS_I)
#CFLAG_M += $(SRCS_I)
endif

####################################################
# 3、执行创建文件夹、生成依赖、编译、删除等相关操作
####################################################

.PHONY: all clean echo debug download

ifdef TARGET
all: $(TARGET).elf $(TARGET).hex $(TARGET).bin
endif

ifdef LIB
all: $(LIB)
endif

# 非执行"clean/echo"才包含
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),echo)
-include $(DEPS)
endif
endif

# 编译出最终执行文件
ifdef TARGET
$(TARGET).elf: $(OBJS) $(LIBS)
	@echo "[2]making $@..."
	@$(CC) $(CFLAG_L) -o $@ $(filter %.o, $^) $(LIBS) -lc -lm -lnosys
	@echo ------------------------------------------------
	@$(SZ) $@
	@echo ------------------------------------------------

$(TARGET).hex: $(TARGET).elf
	@echo "[3]making $@..."
	@$(CP) $< $@ -O ihex

$(TARGET).bin: $(TARGET).elf
	@echo "[3]making $@..."
	@$(CP) $< $@ -O binary -S
endif

# 打包生成静态库文件
ifdef LIB
$(LIB): $(OBJS)
	@echo "[2]making $@..."
	@$(AR) $(ARFLAGS) $@ $(filter %.o, $^)
endif

# 编译出中间目标文件
#$(OBJS_D)%.o: %.c
#	@echo "[1]making $@..."
#	@$(CC) $(CFLAG_O) $(CFLAG_M) $< -o $@
#
#$(OBJS_D)%.o: %.s
#	@echo "[1]making $@..."
#	@$(AS) $(AFLAG_O) $(CFLAG_M) $< -o $@

define FUNC_C
$1: $2
	@echo "[1]making $$@..."
	@$$(CC) $$(CFLAG_O) $$(CFLAG_M) $$< -o $$@
endef

define FUNC_S
$1: $2
	@echo "[1]making $$@..."
	@$$(AS) $$(AFLAG_O) $$(CFLAG_M) $$< -o $$@
endef

$(if             $(filter %.c, $(SRCS)),\
     $(foreach v,$(filter %.c, $(SRCS)),\
          $(eval $(call FUNC_C,$(addprefix $(OBJS_D),$(notdir $(v:%.c=%.o))),$(v)))))

$(if             $(filter %.C, $(SRCS)),\
     $(foreach v,$(filter %.C, $(SRCS)),\
          $(eval $(call FUNC_C,$(addprefix $(OBJS_D),$(notdir $(v:%.C=%.o))),$(v)))))

$(if             $(filter %.s, $(SRCS)),\
     $(foreach v,$(filter %.s, $(SRCS)),\
          $(eval $(call FUNC_S,$(addprefix $(OBJS_D),$(notdir $(v:%.s=%.o))),$(v)))))

$(if             $(filter %.S, $(SRCS)),\
     $(foreach v,$(filter %.S, $(SRCS)),\
          $(eval $(call FUNC_S,$(addprefix $(OBJS_D),$(notdir $(v:%.S=%.o))),$(v)))))

# 清除目标及执行文件
clean:
	$(MKDIR) $(DIRS)
	$(RM) $(RMFLAGS) $(OBJX) $(LIB) $(if $(TARGET),$(TARGET).map $(TARGET).elf $(TARGET).bin $(TARGET).hex)

# 查看变量对象相关值
echo:
	$(MKDIR) $(DIRS)
	@echo "VPATH: $(VPATH)"         # VPATH 为[make]工具增加搜索目录
	@echo "DIRS: $(DIRS)"           # DIRS 为编译过程需要创建的文件夹（如：build/）
	@echo "SRCS: $(SRCS)"           # SRCS 为全部源码文件及其路径    （如：usr/hello.c）
	@echo "OBJS: $(OBJS)"           # OBJS 为全部中间目标文件及其路径（如：build/hello.o）
	@echo "DEPS: $(DEPS)"           # DEPS 为全部依赖信息文件及其路径(源码文件包含其它文件的信息)（如：build/hello.d）
	@echo "OBJX: $(OBJX)"           # OBJX 为所有中间文件及其路径(包括：OBJS 和 DEPS)
	@echo "LIBS: $(LIBS)"           # LIBS 为编译包含的库文件及其路径（如：build/abc.a）
	@echo "CFLAG_O: $(CFLAG_O)"     # CFLAG_O 编译中间目标文件的选项参数（如：-c -I./usr/）
	@echo "CFLAG_M: $(CFLAG_M)"     # CFLAG_M 生成依赖信息文件的选项参数（如：-MM -I./usr/）
	@echo "-------------------"

# 调试程序
ifdef TARGET
debug:
	$(DEBUG_CMD)
endif

# 烧录固件
ifdef TARGET
download:
	$(DOWNLOAD_CMD)
endif
