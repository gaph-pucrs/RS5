################################################################################
## Configurable parameters
################################################################################

MEM_SIZE ?= 65536
ARCH     ?= rv32im_zicsr_zkne_zknh

################################################################################
## Build rules
################################################################################

RED  =\033[0;31m
NC   =\033[0m # No Color
TARGET   ?= $(notdir $(CURDIR))

CC 		= riscv64-elf-gcc
OBJDUMP = riscv64-elf-objdump
OBJCOPY = riscv64-elf-objcopy

COMMON_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
ARCH_LOWER := $(shell echo $(ARCH) | tr '[:upper:]' '[:lower:]')
ARCH_STAMP     := $(COMMON_DIR)/.arch_stamp
MEM_SIZE_STAMP := $(COMMON_DIR)/.mem_size_stamp
$(shell \
  if [ "$$(cat $(ARCH_STAMP) 2>/dev/null)" != "$(ARCH_LOWER)" ]; then \
    echo "$(ARCH_LOWER)" > $(ARCH_STAMP) && \
    printf "$(RED)ARCH stamp updated: $(ARCH_LOWER)$(NC)\n" >&2; \
  fi)
$(shell \
  if [ "$$(cat $(MEM_SIZE_STAMP) 2>/dev/null)" != "$(MEM_SIZE)" ]; then \
    echo "$(MEM_SIZE)" > $(MEM_SIZE_STAMP) && \
    printf "$(RED)MEM_SIZE stamp updated: $(MEM_SIZE)$(NC)\n" >&2; \
  fi)

SRCDIR  = src
INCDIR  = $(SRCDIR)/include
HEADERS = $(wildcard $(INCDIR)/*.h) $(wildcard $(COMMON_DIR)/include/*.h) $(wildcard $(COMMON_DIR)/include/tinycrypt/*.h) $(wildcard $(COMMON_DIR)/include/kyber_round3_ref/*.h)

DEFS += -DTC_AES_256 -DRVK_ALGTEST_VERBOSE_SIO -DKYBER_K=2

# Zkne -> AES_RISCV_ASM; without -> don't define
DEFS += $(if $(findstring zkne,$(ARCH_LOWER)), -DAES_RISCV_ASM)
# Zknh -> SHA2 flags; without -> don't define
DEFS += $(if $(findstring zknh,$(ARCH_LOWER)), -DSHA256_ZKNH -DSHA512_ZKNH)
# Zbkb -> assembler; without -> emulate
DEFS += $(if $(findstring zbkb,$(ARCH_LOWER)), -DRVKINTRIN_ASSEMBLER, -DRVKINTRIN_EMULATE)
# Xkyber -> assembler; without -> emulate
DEFS += $(if $(findstring xkyber,$(ARCH_LOWER)), -DKYBER_ISE)

ARCH := $(subst _xkyber,,$(ARCH))

CFLAGS  = -march=$(ARCH) -mabi=ilp32 -Os -fdata-sections -ffunction-sections -Wall -std=c23 -I$(INCDIR) -I$(COMMON_DIR)/include -I$(COMMON_DIR)/include/tinycrypt -I$(COMMON_DIR)/include/kyber_round3_ref $(DEFS)
LDFLAGS = --specs=nano.specs -T $(COMMON_DIR)/link.ld -Wl,--gc-sections -march=$(ARCH) -mabi=ilp32 -nostartfiles -lm -u _printf_float

CCSRC = $(wildcard $(SRCDIR)/*.c) $(wildcard $(COMMON_DIR)/*.c) $(wildcard $(COMMON_DIR)/tinycrypt/*.c) $(wildcard $(COMMON_DIR)/keccak/*.c) $(wildcard $(COMMON_DIR)/kyber_round3_ref/*.c)
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

%.o: %.S $(ARCH_STAMP) $(MEM_SIZE_STAMP)
	@printf "${RED}Assemblying %s...${NC}\n" "$<"
	@$(CC) -c $< -o $@ $(CFLAGS) -march=$(ARCH) -DMEM_SIZE=$(MEM_SIZE)

%.o: %.c $(HEADERS) $(ARCH_STAMP)
	@printf "${RED}Compiling %s...${NC}\n" "$<"
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@printf "Cleaning up\n"
	@rm -rf src/*.o
	@rm -rf $(COMMON_DIR)/*.o
	@rm -rf $(COMMON_DIR)/tinycrypt/*.o
	@rm -rf $(COMMON_DIR)/keccak/*.o
	@rm -rf $(COMMON_DIR)/kyber_round3_ref/*.o
	@rm -rf *.bin
	@rm -rf *.map
	@rm -rf *.lst
	@rm -rf *.elf
	@rm -f $(COMMON_DIR)/$(ARCH_STAMP) $(COMMON_DIR)/$(MEM_SIZE_STAMP)

.PHONY: clean
