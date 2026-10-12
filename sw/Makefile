# ML-KEM-512 (FIPS 203) build: common/mlkem_ref = round-3 tree + ML-KEM KEM layer (README, step 01).
# Flags reproduce app/common/common.mk exactly; only the output location changes.
# Usage: make NAME=<build name> ARCH=<march string, may contain _xkyber> [EXTRA_DEFS=...] [SRC=kyber/src] [BUILD_DIR=build]
# (copy of the campaign Makefile; BUILD_DIR added, source/link order made explicit)
NAME     ?= base
ARCH     ?= rv32imc_zicsr_zkne_zknh
MEM_SIZE ?= 65536
SRC      ?= kyber/src
EXTRA_DEFS ?=

CC      = riscv64-elf-gcc
OBJDUMP = riscv64-elf-objdump
OBJCOPY = riscv64-elf-objcopy
NM      = riscv64-elf-nm

COMMON_DIR := $(abspath common)
ARCH_LOWER := $(shell echo $(ARCH) | tr '[:upper:]' '[:lower:]')
BUILD_DIR ?= build
B := $(BUILD_DIR)/$(NAME)

DEFS += -DTC_AES_256 -DRVK_ALGTEST_VERBOSE_SIO -DKYBER_K=2
DEFS += $(if $(findstring zkne,$(ARCH_LOWER)), -DAES_RISCV_ASM)
DEFS += $(if $(findstring zknh,$(ARCH_LOWER)), -DSHA256_ZKNH -DSHA512_ZKNH)
DEFS += $(if $(findstring zbkb,$(ARCH_LOWER)), -DRVKINTRIN_ASSEMBLER, -DRVKINTRIN_EMULATE)
DEFS += $(if $(findstring xkyber,$(ARCH_LOWER)), -DKYBER_ISE)
DEFS += $(EXTRA_DEFS)
MARCH := $(subst _xkyber,,$(ARCH))

CFLAGS  = -march=$(MARCH) -mabi=ilp32 -Os -fdata-sections -ffunction-sections -Wall -std=c23 -I$(SRC)/include -I$(COMMON_DIR)/include -I$(COMMON_DIR)/include/tinycrypt -I$(COMMON_DIR)/include/mlkem_ref $(DEFS)
LDFLAGS = --specs=nano.specs -T $(COMMON_DIR)/link.ld -Wl,--gc-sections -march=$(MARCH) -mabi=ilp32 -nostartfiles -lm -u _printf_float

# Explicit source order = link order of the paper's binaries (the original Makefile used
# $(wildcard), whose order depends on the file system and changes code placement).
COMMON_C    = newlib.c simple_system_common.c test_rvkat_sio.c rvk_emu_intrin.c
TINYCRYPT_C = ctr_prng.c sha512.c ccm_mode.c ctr_mode.c aes_encrypt_t_table.c sha256.c utils.c
KECCAK_C    = sha3_api.c sha3_f1600_rvb32.c
MLKEM_C     = cbd.c symmetric-aes.c polyvec.c rng.c symmetric-shake.c reduce.c verify.c ntt.c \
              kyber_sha256.c poly.c kem.c kyber_sha512.c indcpa.c
CCSRC = $(sort $(wildcard $(SRC)/*.c)) $(addprefix $(COMMON_DIR)/,$(COMMON_C)) \
        $(addprefix $(COMMON_DIR)/tinycrypt/,$(TINYCRYPT_C)) $(addprefix $(COMMON_DIR)/keccak/,$(KECCAK_C)) \
        $(addprefix $(COMMON_DIR)/mlkem_ref/,$(MLKEM_C))
ASSRC = $(wildcard $(SRC)/*.S) $(wildcard $(COMMON_DIR)/*.S)
OBJ   = $(addprefix $(B)/obj/,$(notdir $(CCSRC:.c=.o)) $(notdir $(ASSRC:.S=.o)))
vpath %.c $(sort $(dir $(CCSRC)))
vpath %.S $(sort $(dir $(ASSRC)))

all: $(B)/app.bin $(B)/app.lst $(B)/app.nm $(B)/flags.txt

$(B)/obj/%.o: %.c | $(B)/obj
	$(CC) -c $< -o $@ $(CFLAGS)
$(B)/obj/%.o: %.S | $(B)/obj
	$(CC) -c $< -o $@ $(CFLAGS) -march=$(MARCH) -DMEM_SIZE=$(MEM_SIZE)
$(B)/obj:
	mkdir -p $@
$(B)/app.elf: $(OBJ)
	$(CC) $(OBJ) -Wl,-Map=$(B)/app.map -N -o $@ $(LDFLAGS)
$(B)/app.bin: $(B)/app.elf
	$(OBJCOPY) $< $@ -O binary
$(B)/app.lst: $(B)/app.elf
	$(OBJDUMP) -d $< > $@
$(B)/app.nm: $(B)/app.elf
	$(NM) -S -n $< > $@
$(B)/flags.txt: $(B)/app.elf
	@{ echo "ARCH=$(ARCH)"; echo "MARCH=$(MARCH)"; echo "CFLAGS=$(CFLAGS)"; echo "LDFLAGS=$(LDFLAGS)"; echo "SRC=$(SRC)"; $(CC) --version | head -1; } > $@

clean:
	rm -rf $(B)
.PHONY: all clean
