RED  =\033[0;31m
NC   =\033[0m # No Color

COMMON_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

SHA256_ZKNH ?= 1

SHA512_ZKNH ?= 1

AES_ASM ?= 1

KYBER_ISE ?= 1

ifneq (${SHA256_ZKNH}, 0)
	DEFS += -DSHA256_ZKNH
endif

ifneq (${SHA512_ZKNH}, 0)
	DEFS += -DSHA512_ZKNH
endif

ifneq (${AES_ASM}, 0)
	DEFS += -DAES_RISCV_ASM
endif

ifneq (${KYBER_ISE}, 0)
	DEFS += -DKYBER_ISE
endif

DEFS += -DTC_AES_256

DEFS += -DKYBER_90S

DEFS += -DKYBER_K=2

DEFS += -DRVK_ALGTEST_VERBOSE_SIO

TARGET   ?= $(notdir $(CURDIR))
MEM_SIZE ?= 65536
ARCH     ?= rv32im_zicsr

CC 		= riscv64-elf-gcc
OBJDUMP = riscv64-elf-objdump
OBJCOPY = riscv64-elf-objcopy

SRCDIR  = src
INCDIR  = $(SRCDIR)/include
HEADERS = $(wildcard $(INCDIR)/*.h) $(wildcard $(COMMON_DIR)/include/*.h) $(wildcard $(COMMON_DIR)/include/kyber_round3_ref/*.h) $(wildcard $(COMMON_DIR)/include/tinycrypt/*.h)

CFLAGS  = -march=$(ARCH) -mabi=ilp32 -Os -Wall -std=c23 -I$(INCDIR) -I$(COMMON_DIR)/include -I$(COMMON_DIR)/include/kyber_round3_ref -I$(COMMON_DIR)/include/tinycrypt $(DEFS)
LDFLAGS = --specs=nano.specs -T $(COMMON_DIR)/link.ld -march=$(ARCH) -mabi=ilp32 -nostartfiles -lm -u _printf_float

CCSRC = $(wildcard $(SRCDIR)/*.c) $(wildcard $(COMMON_DIR)/*.c) $(wildcard $(COMMON_DIR)/kyber_round3_ref/*.c) $(wildcard $(COMMON_DIR)/tinycrypt/*.c)
CCOBJ = $(patsubst %.c, %.o, $(CCSRC))

ASSRC = $(wildcard $(SRCDIR)/*.S) $(wildcard $(COMMON_DIR)/*.S)
ASOBJ = $(patsubst %.S,%.o, $(ASSRC))

all: $(TARGET).bin $(TARGET).lst

$(TARGET).bin: $(TARGET).elf
	@printf "${RED}Generating %s...${NC}\n" "$@"
	@$(OBJCOPY) $< $@ -O binary

$(TARGET).lst: $(TARGET).elf
	@printf "${RED}Generating %s...${NC}\n" "$@"
	@$(OBJDUMP) -S $< > $@

$(TARGET).elf: $(CCOBJ) $(ASOBJ)
	@printf "${RED}Linking %s...${NC}\n" "$@"
	@$(CC) $(CCOBJ) $(ASOBJ) -Wl,-Map=$(TARGET).map -N -o $@ $(LDFLAGS)

%.o: %.S
	@printf "${RED}Assemblying %s...${NC}\n" "$<"
	@$(CC) -c $< -o $@ $(CFLAGS) -march=$(ARCH) -DMEM_SIZE=$(MEM_SIZE)

%.o: %.c $(HEADERS)
	@printf "${RED}Compiling %s...${NC}\n" "$<"
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@printf "Cleaning up\n"
	@rm -rf src/*.o
	@rm -rf $(COMMON_DIR)/*.o
	@rm -rf *.bin
	@rm -rf *.map
	@rm -rf *.lst
	@rm -rf *.elf

.PHONY: clean
