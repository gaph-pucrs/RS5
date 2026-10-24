/*
 * Scalar baseline: the reference NTT with the Xkyber instructions (kybermul,
 * kyberadd, kybersub), which is its KYBER_ISE path. KYBER_ISE is defined only
 * here, so the reference everywhere else stays plain RV32IM.
 * The core must have Xkyber: simulate with XKYBER=1.
 */
#define KYBER_ISE
#include "params.h"
#undef KYBER_NAMESPACE
#define KYBER_NAMESPACE(s) kyber_xkyber##s

#include "../../../common/kyber_round3_ref/reduce.c"
#include "../../../common/kyber_round3_ref/ntt.c"
