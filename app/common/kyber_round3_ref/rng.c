#include "rng.h"

TCCtrPrng_t prng_ctx;

void randombytes_init(unsigned char *entropy_input,
                 unsigned char *personalization_string,
                 int security_strength) {

    tc_ctr_prng_init(&prng_ctx, entropy_input, 48, personalization_string, 0);
}

int randombytes(unsigned char *x, unsigned long long xlen) {

    tc_ctr_prng_generate(&prng_ctx, NULL, 0, x, xlen);

    return RNG_SUCCESS;
}

