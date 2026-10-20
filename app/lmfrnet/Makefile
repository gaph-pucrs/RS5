MEM_SIZE = 16777216
OPT      = -O2

ifeq ($(VEn), 1)
	DEFS += -DVECTOR
	ARCH  = rv32imc_zicsr_zve32x_zvl$(VLEN)b
else
	ARCH  = rv32imc_zicsr
endif

include ../common/common.mk

# Host build (-DNO_RISCV): scalar kernels, prints the checksums to compare RTL runs against
HOST_CC ?= gcc

native: build/lmfrnet_native

build/lmfrnet_native: src/lmfrnet.c $(wildcard src/*.h)
	@mkdir -p build
	@printf "${RED}Compiling %s (host)...${NC}\n" "$<"
	@$(HOST_CC) -O2 -Wall -DNO_RISCV -I$(COMMON_DIR)/include $< -o $@

run-native: build/lmfrnet_native
	@./build/lmfrnet_native

clean-native:
	@rm -rf build

.PHONY: native run-native clean-native
