#ifndef SYMMETRIC_H
#define SYMMETRIC_H

#include <stddef.h>
#include <stdint.h>
#include "params.h"

// #ifdef KYBER_90S
#if defined(KYBER_90S)

// #include "aes256ctr.h"
#include "symmetric-aes.h"
#include "kyber_sha2.h"

#if (KYBER_SSBYTES != 32)
#error "90s variant of Kyber can only generate keys of length 256 bits"
#endif

typedef aes256ctr_ctx xof_state;

// #define kyber_aes256ctr_xof_absorb KYBER_NAMESPACE(kyber_aes256ctr_xof_absorb)
// void kyber_aes256ctr_xof_absorb(aes256ctr_ctx *state,
//                                 const uint8_t seed[KYBER_SYMBYTES],
//                                 uint8_t x,
//                                 uint8_t y);

// #define kyber_aes256ctr_prf AES256CTR_NAMESPACE(_kyber_aes256ctr_prf)
// void kyber_aes256ctr_prf(uint8_t *out,
//                          size_t outlen,
//                          const uint8_t key[KYBER_SYMBYTES],
//                          uint8_t nonce);

#define XOF_BLOCKBYTES AES256CTR_BLOCKBYTES

#define hash_h(OUT, IN, INBYTES) sha256(OUT, IN, INBYTES)
#define hash_g(OUT, IN, INBYTES) sha512(OUT, IN, INBYTES)
#define xof_absorb(STATE, SEED, X, Y) \
        kyber_aes256ctr_xof_absorb(STATE, SEED, X, Y)
#define xof_squeezeblocks(OUT, OUTBLOCKS, STATE) \
        kyber_aes256ctr_xof_squeezeblocks(OUT, OUTBLOCKS, STATE)
#define prf(OUT, OUTBYTES, KEY, NONCE) \
        kyber_aes256ctr_prf(OUT, OUTBYTES, KEY, NONCE)
#define kdf(OUT, IN, INBYTES) sha256(OUT, IN, INBYTES)


#elif defined(KYBER_ASCON)


#include "ascon_prim.h"

#define XOF_BLOCKBYTES ASCON_HASH_RATE
typedef ascon_state_t xof_state;

// int ascon_hash(const unsigned char *m, uint32_t mlen, unsigned char *c, uint32_t outlen, int xof)

// #define hash_h(OUT, IN, INBYTES) crypto_hash(OUT, 32, IN, INBYTES)
#define hash_h(OUT, IN, INBYTES) ascon_hash(IN, INBYTES, OUT, 32, 1)
// #define hash_g(OUT, IN, INBYTES) crypto_hash(OUT, 64, IN, INBYTES)
#define hash_g(OUT, IN, INBYTES) ascon_hash(IN, INBYTES, OUT, 64, 1)
#define xof_absorb(STATE, SEED, X, Y) kyber_ascon_absorb(STATE, SEED, X, Y)
#define xof_squeezeblocks(OUT, OUTBLOCKS, STATE) \
        ascon_squeezeblocks(OUT, OUTBLOCKS, STATE)
#define prf(OUT, OUTBYTES, KEY, NONCE) \
        kyber_ascon_prf(OUT, OUTBYTES, KEY, NONCE)
#define kdf(OUT, IN, INBYTES) ascon_hash(IN, INBYTES, OUT, KYBER_SSBYTES, 1)


#else


// #include "fips202.h"
#include "sha3_api.h"

// typedef keccak_state xof_state;
typedef sha3_ctx_t xof_state;

#define XOF_BLOCKBYTES SHAKE128_RATE

// #define hash_h(OUT, IN, INBYTES) sha3_256(OUT, IN, INBYTES)
// #define hash_h(OUT, IN, INBYTES) sha3(OUT, 32, IN, INBYTES)
#if defined(TURBOSHAKE)
#define hash_h(OUT, IN, INBYTES) kyber_shake256(OUT, 32, IN, INBYTES)
#define hash_g(OUT, IN, INBYTES) kyber_shake256(OUT, 64, IN, INBYTES)
#else
#define hash_h(OUT, IN, INBYTES) sha3(OUT, 32, IN, INBYTES)
#define hash_g(OUT, IN, INBYTES) sha3(OUT, 64, IN, INBYTES)
#endif
// #define hash_g(OUT, IN, INBYTES) sha3_512(OUT, IN, INBYTES)
// #define hash_g(OUT, IN, INBYTES) sha3(OUT, 64, IN, INBYTES)
#define xof_absorb(STATE, SEED, X, Y) kyber_shake128_absorb(STATE, SEED, X, Y)
// #define xof_squeezeblocks(OUT, OUTBLOCKS, STATE) shake128_squeezeblocks(OUT, OUTBLOCKS, STATE)
#define xof_squeezeblocks(OUT, OUTBLOCKS, STATE) shake128_squeeze(STATE, OUT, OUTBLOCKS*XOF_BLOCKBYTES)
#define prf(OUT, OUTBYTES, KEY, NONCE) kyber_shake256_prf(OUT, OUTBYTES, KEY, NONCE)
// #define kdf(OUT, IN, INBYTES) shake256(OUT, KYBER_SSBYTES, IN, INBYTES)
#define kdf(OUT, IN, INBYTES) kyber_shake256(OUT, KYBER_SSBYTES, IN, INBYTES)

#endif /* KYBER_90S */

#endif /* SYMMETRIC_H */
