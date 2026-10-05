MEM_SIZE = 16777216
OPT      = -O2

ifeq ($(VEn), 1)
	DEFS += -DVECTOR
	ARCH  = rv32imc_zicsr_zve32x_zvl$(VLEN)b
else
	ARCH  = rv32imc_zicsr
endif

include ../common/common.mk
