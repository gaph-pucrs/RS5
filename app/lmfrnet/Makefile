# VLEN     ?= 128
MEM_SIZE  = 16777216

ifeq ($(VEn), 1)
	CFLAGS += -DVECTOR
	ARCH      = rv32imc_zicsr_zve32x_zvl$(VLEN)b
endif

include ../common/common.mk
