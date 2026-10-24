MEM_SIZE = 131072
ARCH     = rv32imc_zicsr_zve32x_zvl128b

include ../../common/common.mk

# The reference code stays scalar; the vector code under test is PQRV's
# assembly for VLEN = 128 or 256 (picked at run time), and the Xkyber baseline
# (ntt_xkyber.c) needs Xkyber in the core: simulate with VLEN=128 or 256 and XKYBER=1
CFLAGS += -fno-tree-vectorize -mstringop-strategy=scalar

# Scalar baselines built again at -O2 (the later -O2 overrides -Os)
src/ref_O2.o src/ntt_xkyber_O2.o: CFLAGS += -O2
