ROOT_DIR := $(patsubst %/,%, $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
APPS_DIR := $(ROOT_DIR)
COMMON_DIR := $(ROOT_DIR)/common

APPS := $(patsubst $(APPS_DIR)/%/main.c,%,$(shell find $(APPS_DIR) -name "main.c"))

# CC=gcc
GCC_RISCV = riscv64-elf-gcc -march=rv32imv_zicsr -mabi=ilp32 -Os $(CFLAGS_STRIP) -DDEBUG_PORT -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -mno-relax -DPRINTF_DISABLE_SUPPORT_FLOAT=1
EXE=test

# Python
PYTHON ?= python3

# Choose the nr_lanes and vlen from config directory
CONFIG := default

ifeq ($(config),)
    CONFIG := default
else
    CONFIG := $(config)
endif

include config/$(CONFIG).mk
include $(COMMON_DIR)/default_args.mk

# Defines
MAKE_DEFINES = -DNR_LANES=$(nr_lanes) -DVLEN=$(vlen)

# Data generation
# Only some applications need to generate and then compile the data file
# Generate a dummy data file for applications that do not need it
ifeq ($(old_data),1)
else
define app_gen_data_template
$1/data.S:
	cd $1 && if [ -d script ]; then \
		${PYTHON} script/gen_data.py $(subst ",,$(def_args_$1)) > data.S ; \
	else \
	touch data.S; \
	fi
endef
# $(foreach app,$(APPS),$(eval $(call app_gen_data_template,$(app))))
# $(call app_gen_data_template, $@)
endif

ifeq ($(old_data),1)
else
define testando
$1/data.S:
	@cd $1 && if [ -d script ]; then \
		echo "found"; \
	else \
		echo "not found"; \
	fi
endef
endif

.PHONY: $(APPS)

all:	$(APPS)

$(APPS): %:  $(APPS_DIR)/%/main.c
	${PYTHON} $@/script/gen_data.py $(subst ",,$(def_args_$@)) > $@/data.S ; 
	@echo "Building $@ in $(APPS_DIR)/$@/"
	@echo $@
	$(GCC_RISCV) -c $(APPS_DIR)/$@/data.S -o data.o $(MAKE_DEFINES)
	$(GCC_RISCV) -c $(APPS_DIR)/$@/kernel/$@.c -o $@.o -I$(APPS_DIR)/$@/kernel
	$(GCC_RISCV) -c $(APPS_DIR)/common/printf.c -o printf.o -DPRINTF_INCLUDE_CONFIG_H -I$(APPS_DIR)/common
	$(GCC_RISCV) -c $(APPS_DIR)/common/util.c -o util.o -I$(APPS_DIR)/common
	$(GCC_RISCV) -c $(APPS_DIR)/$@/main.c -o main.o -I$(APPS_DIR)/$@/kernel -I$(APPS_DIR)/common $(MAKE_DEFINES)
	$(GCC_RISCV) -o test main.o printf.o $@.o util.o data.o -T$(APPS_DIR)/common/arch.link.ld

clean:
	rm $(EXE)
	echo $(ROOT_DIR)
	echo $(APPS_DIR)
	echo $(APPS)
	rm *.o


# missing gen data part and link asm with c