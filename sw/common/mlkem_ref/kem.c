/* ML-KEM (FIPS 203) KEM layer.
 * Ported from pq-crystals/kyber ref/kem.c (main @ 3edd5af, ML-KEM) onto the
 * RS5 verification tree (Keccak via sha3_api / sha3_f1600_rvb32, XKyber hooks
 * in the lattice files). Differences to round 3 (kem.c.round3.orig):
 *  - keypair: coins = d||z drawn with one randombytes(64) call (as in pq-crystals);
 *  - enc: m is used directly (no H(m)), K = first half of G(m||H(pk)) (no KDF);
 *  - dec: implicit rejection K_bar = J(z||c) = SHAKE256(z||c, 32) (rkprf).  */
#include <stddef.h>
#include <stdint.h>
#include "kem.h"
#include "params.h"
#include "rng.h"
#include "symmetric.h"
#include "verify.h"
#include "indcpa.h"

int crypto_kem_keypair(unsigned char *pk, unsigned char *sk)
{
  size_t i;
  uint8_t coins[2*KYBER_SYMBYTES];
  randombytes(coins, 2*KYBER_SYMBYTES);
  indcpa_keypair(pk, sk, coins);
  for(i=0;i<KYBER_PUBLICKEYBYTES;i++)
    sk[i+KYBER_INDCPA_SECRETKEYBYTES] = pk[i];
  hash_h(sk+KYBER_SECRETKEYBYTES-2*KYBER_SYMBYTES, pk, KYBER_PUBLICKEYBYTES);
  /* Value z for pseudo-random output on reject */
  for(i=0;i<KYBER_SYMBYTES;i++)
    sk[KYBER_SECRETKEYBYTES-KYBER_SYMBYTES+i] = coins[KYBER_SYMBYTES+i];
  return 0;
}

int crypto_kem_enc(unsigned char *ct,
                   unsigned char *ss,
                   const unsigned char *pk)
{
  size_t i;
  uint8_t buf[2*KYBER_SYMBYTES];
  /* Will contain key, coins */
  uint8_t kr[2*KYBER_SYMBYTES];

  randombytes(buf, KYBER_SYMBYTES);
  /* Multitarget countermeasure for coins + contributory KEM */
  hash_h(buf+KYBER_SYMBYTES, pk, KYBER_PUBLICKEYBYTES);
  hash_g(kr, buf, 2*KYBER_SYMBYTES);
  /* coins are in kr+KYBER_SYMBYTES */
  indcpa_enc(ct, buf, pk, kr+KYBER_SYMBYTES);
  for(i=0;i<KYBER_SSBYTES;i++)
    ss[i] = kr[i];
  return 0;
}

int crypto_kem_dec(unsigned char *ss,
                   const unsigned char *ct,
                   const unsigned char *sk)
{
  size_t i;
  int fail;
  uint8_t buf[2*KYBER_SYMBYTES];
  /* Will contain key, coins */
  uint8_t kr[2*KYBER_SYMBYTES];
  uint8_t cmp[KYBER_CIPHERTEXTBYTES];
  const uint8_t *pk = sk+KYBER_INDCPA_SECRETKEYBYTES;

  indcpa_dec(buf, ct, sk);
  /* Multitarget countermeasure for coins + contributory KEM */
  for(i=0;i<KYBER_SYMBYTES;i++)
    buf[KYBER_SYMBYTES+i] = sk[KYBER_SECRETKEYBYTES-2*KYBER_SYMBYTES+i];
  hash_g(kr, buf, 2*KYBER_SYMBYTES);
  /* coins are in kr+KYBER_SYMBYTES */
  indcpa_enc(cmp, buf, pk, kr+KYBER_SYMBYTES);
  fail = verify(ct, cmp, KYBER_CIPHERTEXTBYTES);
  /* Compute rejection key */
  rkprf(ss, sk+KYBER_SECRETKEYBYTES-KYBER_SYMBYTES, ct);
  /* Copy true key to return buffer if fail is false */
  cmov(ss, kr, KYBER_SYMBYTES, !fail);
  return 0;
}
