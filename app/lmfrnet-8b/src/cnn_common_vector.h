#ifndef __CNN_COMMON_VECTOR_H__
#define __CNN_COMMON_VECTOR_H__

// The RVV kernels need vwmacc.vx and vnclip (with the vxrm CSR),
// which RS5 doesn't implement yet: build with VEn=0 or NO_RISCV
#error "lmfrnet-8b has no vector kernels yet"

#endif
