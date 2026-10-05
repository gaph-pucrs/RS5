#include <stddef.h>
#include <stdint.h>
#include "kyber_sha2.h"

void sha256(uint8_t *out, const uint8_t *in, size_t inlen) {

  struct tc_sha256_state_struct state;

  // printf("sha256() start\n");

  (void) tc_sha256_init(&state);
  tc_sha256_update(&state, in, inlen);
  (void) tc_sha256_final(out, &state);

  // printf("sha256() end\n");

}
