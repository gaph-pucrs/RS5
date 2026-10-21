#include <stddef.h>
#include <stdint.h>
#include "kyber_sha2.h"

void sha512(uint8_t *out, const uint8_t *in, size_t inlen) {

  struct tc_sha512_state_struct state;

  // printf("sha512() start\n");

  (void) tc_sha512_init(&state);
  tc_sha512_update(&state, in, inlen);
  (void) tc_sha512_final(out, &state);

  // printf("sha512() end\n");

}
