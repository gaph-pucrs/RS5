#include <stddef.h>
#include <stdint.h>
#include "params.h"
#include "symmetric-aes.h"
// #include "symmetric.h"
#include <stdio.h>

uint32_t _encrypt_and_increment_iv(const uint8_t *out, uint8_t *iv, const TCAesKeySched_t key_exp, uint32_t block_num) {

  // Encrypt IV, store to "out" buffer
  tc_aes_encrypt(out, iv, key_exp);

  // Update IV for next iteration
  block_num++;
	iv[12] = (uint8_t) (block_num >> 24);
	iv[13] = (uint8_t) (block_num >> 16);
	iv[14] = (uint8_t) (block_num >> 8);
	iv[15] = (uint8_t) (block_num);

  return block_num;

}

void kyber_aes256ctr_xof_absorb(aes256ctr_ctx *state, const uint8_t seed[KYBER_SYMBYTES], uint8_t x, uint8_t y) {
#if KYBER_SYMBYTES != 32
#error "Kyber-90s only supports KYBER_SYMBYTES = 32!"
#endif

  // printf("kyber_aes256ctr_xof_absorb() start\n");

  state->iv[0] = x;
  state->iv[1] = y;

  for (int i = 2; i < TC_AES_BLOCK_SIZE; i++)
    state->iv[i] = 0;

  tc_aes256_set_encrypt_key(&state->key_exp, seed);

  // printf("kyber_aes256ctr_xof_absorb() end\n");

}

void kyber_aes256ctr_xof_squeezeblocks(uint8_t *out, size_t nblocks, aes256ctr_ctx *state) {

  uint32_t block_num = (state->iv[12] << 24) | (state->iv[13] << 16) | (state->iv[14] << 8) | (state->iv[15]);

  // printf("kyber_aes256ctr_xof_squeezeblocks() start\n");

  for (int i = 0; i < nblocks; i++, out += TC_AES_BLOCK_SIZE)
    block_num = _encrypt_and_increment_iv(out, state->iv, &state->key_exp, block_num);

  // printf("kyber_aes256ctr_xof_squeezeblocks() end\n");

}

void kyber_aes256ctr_prf(uint8_t *out, size_t outlen, const uint8_t key[32], uint8_t nonce) {

  aes256ctr_ctx state;

  // printf("kyber_aes256ctr_prf() start\n");

  kyber_aes256ctr_xof_absorb(&state, key, nonce, 0);
  kyber_aes256ctr_xof_squeezeblocks(out, outlen/TC_AES_BLOCK_SIZE, &state);

  int leftover_bytes_len = outlen & (TC_AES_BLOCK_SIZE-1);  // 0 <= leftover_bytes < 16
  uint8_t leftover_bytes[TC_AES_BLOCK_SIZE];

  // printf("outlen: %d\n", outlen);
  // printf("leftover_bytes_len: %d\n", leftover_bytes_len);

  if (leftover_bytes_len) {

    tc_aes_encrypt(leftover_bytes, state.iv, &state.key_exp);

    out += outlen/TC_AES_BLOCK_SIZE;

    for (int i = 0; i < leftover_bytes_len; i++)
      out[i] = leftover_bytes[i];

  }

  // printf("kyber_aes256ctr_prf() end\n");

}
