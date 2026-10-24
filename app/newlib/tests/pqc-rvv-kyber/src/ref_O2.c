/*
 * Scalar baseline: the reference NTT and rejection sampling built at -O2
 * (see Makefile). ntt.c and reduce.c share this translation unit, so the
 * compiler can inline montgomery_reduce, as it would with LTO.
 */
#include "params.h"
#undef KYBER_NAMESPACE
#define KYBER_NAMESPACE(s) kyber_ref_O2##s

#include "../../../common/kyber_round3_ref/reduce.c"
#include "../../../common/kyber_round3_ref/ntt.c"

#define rej_uniform_ref rej_uniform_ref_O2
#include "rej_uniform_ref.h"
