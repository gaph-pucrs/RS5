MEM_SIZE = 65536
ARCH     = rv32imc_zicsr_zve32x_zvl128b

include ../../common/common.mk

# The reference code stays scalar; the vector code under test is PQRV's
# assembly, which assumes VLEN = 128, and the Xkyber baseline (ntt_xkyber.c)
# needs Xkyber in the core: simulate with VLEN=128 XKYBER=1
CFLAGS += -fno-tree-vectorize -mstringop-strategy=scalar

# Scalar baselines built again at -O2 (the later -O2 overrides -Os)
src/ref_O2.o src/ntt_xkyber_O2.o: CFLAGS += -O2
