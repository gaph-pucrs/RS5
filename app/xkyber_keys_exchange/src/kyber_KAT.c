// Derived from "PQCgenKAT_kem.c" in Kyber reference implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rng.h"
#include "api.h"

#include <test_rvkat.h>
#include "kyber_round3_kat_values.h"

int main() {

    // Runtime obtained values
    unsigned char   seed[48];
    unsigned char   entropy_input[48];
    unsigned char   ct[CRYPTO_CIPHERTEXTBYTES];
    unsigned char   ss[CRYPTO_BYTES];
    unsigned char   ss1[CRYPTO_BYTES];
    unsigned char   pk[CRYPTO_PUBLICKEYBYTES];
    unsigned char   sk[CRYPTO_SECRETKEYBYTES];
    int             ret_val = 0;

    // Constant values to be compared with runtime obtained values
    unsigned char   seed_KAT[48];
    unsigned char   ct_KAT[CRYPTO_CIPHERTEXTBYTES];
    unsigned char   ss_KAT[CRYPTO_BYTES];
    unsigned char   ss1_KAT[CRYPTO_BYTES];
    unsigned char   pk_KAT[CRYPTO_PUBLICKEYBYTES];
    unsigned char   sk_KAT[CRYPTO_SECRETKEYBYTES];

    // Initialize KAT values as defined in "kyber_round3_kat_value.h"
    // rvkat_gethex(seed_KAT, sizeof(seed_KAT), KYBER_KAT_SEED);
    // rvkat_gethex(ct_KAT, sizeof(ct_KAT), KYBER_KAT_CT);
    // rvkat_gethex(ss_KAT, sizeof(ss_KAT), KYBER_KAT_SS);
    // rvkat_gethex(ss1_KAT, sizeof(ss1_KAT), KYBER_KAT_SS);
    // rvkat_gethex(pk_KAT, sizeof(pk_KAT), KYBER_KAT_PK);
    // rvkat_gethex(sk_KAT, sizeof(sk_KAT), KYBER_KAT_SK);

	rvkat_info("=== Beginning of " CRYPTO_ALGNAME " test ===");

    data_ind_timing_enable(1);

    for (int i=0; i<48; i++)
        entropy_input[i] = i;

    randombytes_init(entropy_input, NULL, 256);
    randombytes(seed, 48);
    // rvkat_chkhex("SEED", seed, sizeof(seed), seed_KAT);
    rvkat_chkhex("SEED", seed, sizeof(seed), KYBER_KAT_SEED);

    randombytes_init(seed, NULL, 256);

    // Generate the public/private keypair
    if ( (ret_val += crypto_kem_keypair(pk, sk)) != 0)
        rvkat_info("crypto_kem_keypair() failed");

    rvkat_chkhex("PK", pk, sizeof(pk), KYBER_KAT_PK);
    rvkat_chkhex("SK", sk, sizeof(sk), KYBER_KAT_SK);

    // Encapsulate shared secret (generated inside enc())
    if ( (ret_val += crypto_kem_enc(ct, ss, pk)) != 0)
        rvkat_info("crypto_kem_enc() failed");

    rvkat_chkhex("CT", ct, sizeof(ct), KYBER_KAT_CT);
    rvkat_chkhex("SS", ss, sizeof(ss), KYBER_KAT_SS);

    // Decapsulate ciphertext, should yield same shared secred generated in encapsulation step
    if ( (ret_val += crypto_kem_dec(ss1, ct, sk)) != 0)
        rvkat_info("crypto_kem_dec() failed");

    rvkat_chkhex("SS_DECAPS", ss1, sizeof(ss1), KYBER_KAT_SS);

	rvkat_info("=== End of " CRYPTO_ALGNAME " test ===");

    return ret_val;
}
