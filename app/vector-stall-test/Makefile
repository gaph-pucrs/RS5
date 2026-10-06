MEM_SIZE = 65536
ARCH     = rv32imc_zicsr_zve32x_zvl128b

include ../common/common.mk

# Only the inline asm may use the vector unit: no compiler-generated vector code
# (loop vectorization, and RVV block moves for struct/array initializers)
CFLAGS += -fno-tree-vectorize -mstringop-strategy=scalar
