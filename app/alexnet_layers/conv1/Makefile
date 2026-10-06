MEM_SIZE = 16777216
VLEN    ?= 128

ifeq ($(VLEN),0)
ARCH     = rv32im_zicsr
else
ARCH     = rv32im_zicsr_zve32x_zvl$(VLEN)b
endif

include ../../common/common.mk

CFLAGS += -I../include -I../data
ifneq ($(VLEN),0)
CFLAGS += -mrvv-vector-bits=zvl -O2
endif
