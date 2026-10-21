#ifndef SYMMETRIC_AES_H
#define SYMMETRIC_AES_H

#include <stddef.h>
#include <stdint.h>
#include <aes.h>

#define AES256CTR_BLOCKBYTES 16

#define AES256CTR_NAMESPACE(s) pqcrystals_aes256ctr_ref##s

typedef struct {
	struct tc_aes_key_sched_struct key_exp;
  uint8_t iv[TC_AES_BLOCK_SIZE];
} aes256ctr_ctx;

#define kyber_aes256ctr_prf AES256CTR_NAMESPACE(_prf)
void kyber_aes256ctr_prf(uint8_t *out,
                         size_t outlen,
                         const uint8_t key[32],
                        //  const uint8_t nonce[12]);
                         const uint8_t nonce);

#define aes256ctr_init AES256CTR_NAMESPACE(_init)
void aes256ctr_init(aes256ctr_ctx *state,
                    const uint8_t key[32],
                    const uint8_t nonce[12]);

#define kyber_aes256ctr_xof_squeezeblocks AES256CTR_NAMESPACE(_absorb)
void kyber_aes256ctr_xof_absorb(aes256ctr_ctx *state,
                                const uint8_t seed[KYBER_SYMBYTES],
                                uint8_t x,
                                uint8_t y);

#define kyber_aes256ctr_xof_squeezeblocks AES256CTR_NAMESPACE(_squeezeblocks)
void kyber_aes256ctr_xof_squeezeblocks(uint8_t *out,
                                      size_t nblocks,
                                      aes256ctr_ctx *state);

#endif
