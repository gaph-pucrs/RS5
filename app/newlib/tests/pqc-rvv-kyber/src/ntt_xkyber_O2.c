/* Scalar baseline: the Xkyber NTT of ntt_xkyber.c, built at -O2 (see Makefile) */
#define KYBER_ISE
#include "params.h"
#undef KYBER_NAMESPACE
#define KYBER_NAMESPACE(s) kyber_xkyber_O2##s

#include "../../../common/kyber_round3_ref/reduce.c"
#include "../../../common/kyber_round3_ref/ntt.c"
