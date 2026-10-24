MEM_SIZE = 131072
ARCH     = rv32imc_zicsr_zve32x_zvl128b

include ../../common/common.mk

# The reference code stays scalar; the vector code under test is PQRV's
# assembly, which assumes VLEN = 128 (simulate with VLEN=128)
CFLAGS += -fno-tree-vectorize -mstringop-strategy=scalar

# Scalar baseline built again at -O2 (the later -O2 overrides -Os)
src/ref_O2.o: CFLAGS += -O2
