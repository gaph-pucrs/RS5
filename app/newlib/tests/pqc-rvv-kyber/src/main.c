/*
 * ML-KEM (Kyber) kernels written with RVV, run on RS5 and checked against the
 * scalar reference implementation (common/kyber_round3_ref).
 *
 * The vector code is PQRV's ntt_rvv_vlen128.S (https://github.com/Ji-Peng/PQRV,
 * commit 005d55d, MIT, see LICENSE-PQRV). It assumes VLEN = 128 and uses
 * vrgather, vmerge, vcompress, vcpop, vsext and vssra.
 *
 * Checks: polynomial product (NTT, basemul, inverse NTT), rejection sampling,
 * centered binomial sampling (eta = 2 and 3), Barrett reduction and conversion
 * to the Montgomery domain. Prints cycle counts next to the reference.
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "cbd.h"
#include "ntt.h"
#include "ntt_rvv_vlen128.h"
#include "params.h"
#include "poly.h"
#include "reduce.h"

#define REJ_BUFLEN 504   /* fixed in the RVV rejection sampler */

static int failures;

static uint32_t lcg_state = 12345;
static uint32_t rnd(void)
{
    lcg_state = lcg_state * 1664525u + 1013904223u;
    return lcg_state >> 8;
}

static uint32_t cycles(void)
{
    uint32_t c;
    __asm__ volatile("csrr %0, mcycle" : "=r"(c));
    return c;
}

static int16_t canonical(int16_t x)
{
    int32_t r = x % KYBER_Q;
    return (int16_t)(r < 0 ? r + KYBER_Q : r);
}

static void check(const char *name, const int16_t *got, const int16_t *exp, int n, int exact)
{
    for (int i = 0; i < n; i++) {
        int16_t g = exact ? got[i] : canonical(got[i]);
        int16_t e = exact ? exp[i] : canonical(exp[i]);
        if (g != e) {
            printf("%-28s FAILED at %d: got %d, expected %d\n", name, i, g, e);
            failures++;
            return;
        }
    }
    printf("%-28s PASSED\n", name);
}

/* Reference rejection sampling (static in the reference indcpa.c) */
static unsigned int rej_uniform_ref(int16_t *r, unsigned int len, const uint8_t *buf, unsigned int buflen)
{
    unsigned int ctr = 0, pos = 0;
    while (ctr < len && pos + 3 <= buflen) {
        uint16_t val0 = ((buf[pos + 0] >> 0) | ((uint16_t)buf[pos + 1] << 8)) & 0xFFF;
        uint16_t val1 = ((buf[pos + 1] >> 4) | ((uint16_t)buf[pos + 2] << 4)) & 0xFFF;
        pos += 3;
        if (val0 < KYBER_Q)
            r[ctr++] = val0;
        if (ctr < len && val1 < KYBER_Q)
            r[ctr++] = val1;
    }
    return ctr;
}

/* PQRV's wrapper: the vector code stops near the end, scalar code finishes */
static unsigned int rej_uniform_rvv(int16_t *r, const uint8_t *buf)
{
    uint32_t ctr, pos;
    rej_uniform_rvv_vlen128(r, buf, qdata_vlen128, &ctr, &pos);
    while (ctr < KYBER_N && pos <= REJ_BUFLEN - 3) {
        uint16_t val0 = ((buf[pos + 0] >> 0) | ((uint16_t)buf[pos + 1] << 8)) & 0xFFF;
        uint16_t val1 = ((buf[pos + 1] >> 4) | ((uint16_t)buf[pos + 2] << 4));
        pos += 3;
        if (val0 < KYBER_Q)
            r[ctr++] = val0;
        if (val1 < KYBER_Q && ctr < KYBER_N)
            r[ctr++] = val1;
    }
    return ctr;
}

static poly a, b, ref_r, ref_a, ref_b;
static int16_t va[KYBER_N] __attribute__((aligned(16)));
static int16_t vb[KYBER_N] __attribute__((aligned(16)));
static int16_t vr[KYBER_N + 8] __attribute__((aligned(16)));
static uint8_t buf[REJ_BUFLEN + 16] __attribute__((aligned(16)));

int main(void)
{
    uint32_t t0, t_ref, t_rvv;

    /* Polynomial product: ref (ntt, basemul, invntt) against the RVV kernels */
    for (int i = 0; i < KYBER_N; i++) {
        a.coeffs[i] = rnd() % KYBER_Q;
        b.coeffs[i] = rnd() % KYBER_Q;
    }
    ref_a = a;
    ref_b = b;
    memcpy(va, a.coeffs, sizeof(va));
    memcpy(vb, b.coeffs, sizeof(vb));

    t0 = cycles();
    poly_ntt(&ref_a);
    t_ref = cycles() - t0;
    poly_ntt(&ref_b);
    poly_basemul_montgomery(&ref_r, &ref_a, &ref_b);
    poly_invntt_tomont(&ref_r);

    t0 = cycles();
    ntt_rvv_vlen128(va, qdata_vlen128);
    t_rvv = cycles() - t0;
    ntt_rvv_vlen128(vb, qdata_vlen128);
    poly_basemul_rvv_vlen128(vr, va, vb, qdata_vlen128);
    intt_rvv_vlen128(vr, qdata_vlen128);

    check("ML-KEM polynomial product", vr, ref_r.coeffs, KYBER_N, 0);
    printf("  NTT cycles: reference %lu, RVV %lu\n", (unsigned long)t_ref, (unsigned long)t_rvv);

    /* Rejection sampling (vmsltu, vcpop, vcompress) */
    for (int i = 0; i < REJ_BUFLEN; i++)
        buf[i] = rnd();
    int16_t ref_rej[KYBER_N], rvv_rej[KYBER_N + 8];
    t0 = cycles();
    unsigned int n_ref = rej_uniform_ref(ref_rej, KYBER_N, buf, REJ_BUFLEN);
    t_ref = cycles() - t0;
    t0 = cycles();
    unsigned int n_rvv = rej_uniform_rvv(rvv_rej, buf);
    t_rvv = cycles() - t0;
    if (n_ref != n_rvv) {
        printf("%-28s FAILED: %u coefficients, expected %u\n", "ML-KEM rejection sampling", n_rvv, n_ref);
        failures++;
    }
    else {
        check("ML-KEM rejection sampling", rvv_rej, ref_rej, n_ref, 1);
    }
    printf("  cycles: reference %lu, RVV %lu\n", (unsigned long)t_ref, (unsigned long)t_rvv);

    /* Centered binomial sampling (vsext): eta2 = 2 and eta1 = 3 for ML-KEM-512 */
    poly ref_cbd;
    for (int i = 0; i < REJ_BUFLEN; i++)
        buf[i] = rnd();
    cbd_eta2(&ref_cbd, buf);
    cbd2_rvv_vlen128(vr, buf, qdata_vlen128);
    check("ML-KEM CBD eta = 2", vr, ref_cbd.coeffs, KYBER_N, 1);
    cbd_eta1(&ref_cbd, buf);
    cbd3_rvv_vlen128(vr, buf, qdata_vlen128);
    check("ML-KEM CBD eta = 3", vr, ref_cbd.coeffs, KYBER_N, 1);

    /* Barrett reduction (vssra with vxrm = rnu) and Montgomery conversion */
    poly ref_red;
    for (int i = 0; i < KYBER_N; i++)
        ref_red.coeffs[i] = (int16_t)rnd();
    memcpy(vr, ref_red.coeffs, KYBER_N * sizeof(int16_t));
    poly_reduce(&ref_red);
    poly_reduce_rvv_vlen128(vr);
    check("ML-KEM Barrett reduction", vr, ref_red.coeffs, KYBER_N, 0);

    for (int i = 0; i < KYBER_N; i++)
        ref_red.coeffs[i] = (int16_t)rnd();
    memcpy(vr, ref_red.coeffs, KYBER_N * sizeof(int16_t));
    poly_tomont(&ref_red);
    poly_tomont_rvv_vlen128(vr);
    check("ML-KEM to Montgomery", vr, ref_red.coeffs, KYBER_N, 0);

    if (failures)
        printf("PQC RVV KYBER: %d FAILED\n", failures);
    else
        printf("PQC RVV KYBER: PASSED\n");
    return failures;
}
