/*
 * Scalar baseline: the reference NTT built at -O2 (see Makefile), under other
 * names. ntt.c and reduce.c share this translation unit, so the compiler can
 * inline montgomery_reduce, as it would with LTO.
 */
#define ntt               ntt_O2
#define intt              intt_O2
#define montgomery_reduce montgomery_reduce_O2
#define reduce32          reduce32_O2
#define caddq             caddq_O2
#define freeze            freeze_O2

#include "reduce.c"
#include "ntt.c"
