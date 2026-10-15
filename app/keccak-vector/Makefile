MEM_SIZE = 65536
ARCH     = rv32imc_zicsr_zbkb_zve32x_zvl64b

include ../common/common.mk

# Keep vector code explicit (inline asm only): stop GCC from auto-vectorizing
# loops and from expanding memcpy/memset/struct copies with RVV instructions
CFLAGS += -fno-tree-vectorize -mstringop-strategy=scalar
