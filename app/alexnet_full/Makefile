# Full AlexNet (conv1..conv5 + fc6..fc8). The FC weight matrices are large;
# 512 MiB covers all layers.
MEM_SIZE = 536870912

VLEN    ?= 128

ifeq ($(VLEN),0)
ARCH     = rv32im_zicsr
else
ARCH     = rv32im_zicsr_zve32x_zvl$(VLEN)b
endif

include ../common/common.mk

# Kernels and data shared with alexnet_layers (FC weights: run
# ../alexnet_layers/prepare_fc_inputs.py first)
CFLAGS += -I../alexnet_layers/include -I../alexnet_layers/data
ifneq ($(VLEN),0)
CFLAGS += -mrvv-vector-bits=zvl -O2
endif
