#ifndef ASCON_PRIM_H
#define ASCON_PRIM_H

#include <stddef.h>
#include <stdint.h>

#define ASCON_NAMESPACE(s) pqcrystals_ascon_ref##s

// #include "ascon.h"
// #include "constants.h"
#include "permutations.h"
#include "crypto_hash.h"

#define ASCON_HASH_RATE (64 / 8)

void kyber_ascon_absorb(ascon_state_t *state,
                        const uint8_t seed[KYBER_SYMBYTES],
                        uint8_t x,
                        uint8_t y);
void kyber_ascon_prf(uint8_t *out,
                        uint32_t outlen,
                        const uint8_t key[KYBER_SYMBYTES],
                        uint8_t nonce);
void ascon_squeezeblocks(uint8_t *out, uint32_t nblocks, ascon_state_t *state);

// #define shake128_absorb FIPS202_NAMESPACE(_shake128_absorb)
// void shake128_absorb(keccak_state *state, const uint8_t *in, size_t inlen);
// #define shake128_squeezeblocks FIPS202_NAMESPACE(_shake128_squeezeblocks)
// void shake128_squeezeblocks(uint8_t *out, size_t nblocks, keccak_state *state);

// #define shake256_absorb FIPS202_NAMESPACE(_shake256_absorb)
// void shake256_absorb(keccak_state *state, const uint8_t *in, size_t inlen);
// #define shake256_squeezeblocks FIPS202_NAMESPACE(_shake256_squeezeblocks)
// void shake256_squeezeblocks(uint8_t *out, size_t nblocks,  keccak_state *state);
// #define shake128 FIPS202_NAMESPACE(_shake128)
// void shake128(uint8_t *out, size_t outlen, const uint8_t *in, size_t inlen);
// #define shake256 FIPS202_NAMESPACE(_shake256)
// void shake256(uint8_t *out, size_t outlen, const uint8_t *in, size_t inlen);
// #define sha3_256 FIPS202_NAMESPACE(_sha3_256)
// void sha3_256(uint8_t h[32], const uint8_t *in, size_t inlen);
// #define sha3_512 FIPS202_NAMESPACE(_sha3_512)
// void sha3_512(uint8_t h[64], const uint8_t *in, size_t inlen);

#endif
