# The weights alone are about 233 MiB: use the whole testbench RAM (MEM_ADDR_BITS = 28)
MEM_SIZE = 268435456
OPT      = -O2

ifeq ($(VEn), 1)
	DEFS += -DVECTOR
	ARCH  = rv32imc_zicsr_zve32x_zvl$(VLEN)b
else
	ARCH  = rv32imc_zicsr
endif

include ../common/common.mk

# Host build (-DNO_RISCV): scalar kernels, every layer output dumped to dump/
HOST_CC ?= gcc

native: build/alexnet_native

build/alexnet_weights.o: src/alexnet_weights.c src/alexnet_weights.h
	@mkdir -p build
	@printf "${RED}Compiling %s (host)...${NC}\n" "$<"
	@$(HOST_CC) -O2 -DNO_RISCV -c $< -o $@

build/alexnet_native: src/alexnet.c build/alexnet_weights.o $(wildcard src/*.h)
	@printf "${RED}Compiling %s (host)...${NC}\n" "$<"
	@$(HOST_CC) -O2 -Wall -DNO_RISCV -I$(COMMON_DIR)/include $< build/alexnet_weights.o -o $@

run-native: build/alexnet_native
	@mkdir -p dump
	@./build/alexnet_native

clean-native:
	@rm -rf build dump

.PHONY: native run-native clean-native
