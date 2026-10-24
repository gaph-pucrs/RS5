/*
 * ML-KEM (Kyber) kernels written with RVV, run on RS5 and checked against the
 * scalar reference implementation (common/kyber_round3_ref).
 *
 * The vector code is PQRV's ntt_rvv_vlen128.S and ntt_rvv_vlen256.S
 * (https://github.com/Ji-Peng/PQRV, commit 005d55d, MIT, see LICENSE-PQRV).
 * Each one assumes its VLEN, so main picks one from vlenb: the same binary runs
 * at VLEN 128 and 256. They use vrgather, vmerge, vcompress, vcpop, vsext and
 * vssra.
 *
 * Checks: polynomial product (NTT, basemul, inverse NTT), rejection sampling,
 * centered binomial sampling (eta = 2 and 3), Barrett reduction and conversion
 * to the Montgomery domain.
 *
 * Prints cycle counts next to scalar baselines built from the same reference
 * code: -Os (the common.mk default), -O2 (ref_O2.c), and the Xkyber NTT
 * (ntt_xkyber.c, ntt_xkyber_O2.c), which needs the core simulated with XKYBER=1.
 * Also next to PQRV's hand-written RV32IM NTTs for single- and dual-issue cores
 * (ntt_rv32im_single.S, ntt_rv32im_dual.S).
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cbd.h"
#include "ntt.h"
#include "ntt_rvv_vlen128.h"
#include "ntt_rvv_vlen256.h"
#include "params.h"
#include "poly.h"
#include "reduce.h"
#include "rej_uniform_ref.h"

#define REJ_BUFLEN 504   /* fixed in the RVV rejection sampler */

/* Scalar baselines (ref_O2.c, ntt_xkyber.c, ntt_xkyber_O2.c) */
void kyber_ref_O2_ntt(int16_t r[KYBER_N]);
void kyber_xkyber_ntt(int16_t r[KYBER_N]);
void kyber_xkyber_O2_ntt(int16_t r[KYBER_N]);
unsigned int rej_uniform_ref_O2(int16_t *r, unsigned int len, const uint8_t *buf, unsigned int buflen);

/* PQRV's RV32IM NTTs (ntt_rv32im_single.S, ntt_rv32im_dual.S) and their twiddles (zetas_rv32im.c) */
void ntt_single_rv32im(int16_t *r, uint32_t *zetas);
void ntt_dual_rv32im(int16_t *r, uint32_t *zetas);
extern uint32_t zetas_ntt_rv32im[128];

static void ntt_asm_single(int16_t *r) { ntt_single_rv32im(r, zetas_ntt_rv32im); }
static void ntt_asm_dual(int16_t *r) { ntt_dual_rv32im(r, zetas_ntt_rv32im); }

/* PQRV's RVV kernels for the VLEN of the core, chosen in main */
static int vlen256;
#define RVV(f) (vlen256 ? f##_rvv_vlen256 : f##_rvv_vlen128)
#define QDATA  (vlen256 ? qdata_vlen256 : qdata_vlen128)

static int failures;

static uint32_t lcg_state = 12345;
static uint32_t rnd(void)
{
    lcg_state = lcg_state * 1664525u + 1013904223u;
    return lcg_state >> 8;
}

/* A core without Xkyber traps on kybermul: report it instead of restarting */
static void __attribute__((interrupt("machine"), aligned(4))) trap_handler(void)
{
    uint32_t mcause, mepc;
    __asm__ volatile("csrr %0, mcause" : "=r"(mcause));
    __asm__ volatile("csrr %0, mepc" : "=r"(mepc));
    printf("TRAP: mcause %lu at %08lx (the Xkyber baseline needs XKYBER=1)\n",
           (unsigned long)mcause, (unsigned long)mepc);
    exit(1);
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

/* PQRV's wrapper: the vector code stops near the end, scalar code finishes */
static unsigned int rej_uniform_rvv(int16_t *r, const uint8_t *buf)
{
    uint32_t ctr, pos;
    RVV(rej_uniform)(r, buf, QDATA, &ctr, &pos);
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

/* Runs one scalar NTT on a copy of in, checks it against exp and returns its cycles */
static uint32_t scalar_ntt(const char *name, void (*f)(int16_t *), const poly *in, const int16_t *exp)
{
    int16_t r[KYBER_N];
    memcpy(r, in->coeffs, sizeof(r));
    uint32_t t0 = cycles();
    f(r);
    uint32_t t = cycles() - t0;
    check(name, r, exp, KYBER_N, 0);
    return t;
}

static poly a, b, ref_r, ref_a, ref_b;
static int16_t va[KYBER_N] __attribute__((aligned(16)));
static int16_t vb[KYBER_N] __attribute__((aligned(16)));
static int16_t vr[KYBER_N + 8] __attribute__((aligned(16)));
static uint8_t buf[REJ_BUFLEN + 16] __attribute__((aligned(16)));

int main(void)
{
    uint32_t t0, t_ref, t_rvv;

    __asm__ volatile("csrw mtvec, %0" : : "r"(trap_handler));

    uint32_t vlenb;
    __asm__ volatile("csrr %0, vlenb" : "=r"(vlenb));
    if (vlenb != 16 && vlenb != 32) {
        printf("PQRV's RVV kernels need VLEN 128 or 256, not %lu\n", (unsigned long)vlenb * 8);
        return 1;
    }
    vlen256 = vlenb == 32;
    printf("VLEN %lu\n", (unsigned long)vlenb * 8);

    /* Polynomial product: ref (ntt, basemul, invntt) against the RVV kernels */
    for (int i = 0; i < KYBER_N; i++) {
        a.coeffs[i] = rnd() % KYBER_Q;
        b.coeffs[i] = rnd() % KYBER_Q;
    }
    ref_a = a;
    ref_b = b;
    memcpy(va, a.coeffs, sizeof(va));
    memcpy(vb, b.coeffs, sizeof(vb));

    poly_ntt(&ref_a);
    poly_ntt(&ref_b);
    poly_basemul_montgomery(&ref_r, &ref_a, &ref_b);
    poly_invntt_tomont(&ref_r);

    RVV(ntt)(va, QDATA);
    RVV(ntt)(vb, QDATA);
    RVV(poly_basemul)(vr, va, vb, QDATA);
    RVV(intt)(vr, QDATA);

    check("ML-KEM polynomial product", vr, ref_r.coeffs, KYBER_N, 0);

    /* NTT alone (poly_ntt adds a Barrett reduction): every baseline gives the reference result mod q */
    uint32_t t_os  = scalar_ntt("ML-KEM NTT reference -Os", ntt, &a, ref_a.coeffs);
    uint32_t t_o2  = scalar_ntt("ML-KEM NTT reference -O2", kyber_ref_O2_ntt, &a, ref_a.coeffs);
    uint32_t t_xos = scalar_ntt("ML-KEM NTT Xkyber -Os", kyber_xkyber_ntt, &a, ref_a.coeffs);
    uint32_t t_xo2 = scalar_ntt("ML-KEM NTT Xkyber -O2", kyber_xkyber_O2_ntt, &a, ref_a.coeffs);
    uint32_t t_as  = scalar_ntt("ML-KEM NTT RV32IM asm single", ntt_asm_single, &a, ref_a.coeffs);
    uint32_t t_ad  = scalar_ntt("ML-KEM NTT RV32IM asm dual", ntt_asm_dual, &a, ref_a.coeffs);
    memcpy(va, a.coeffs, sizeof(va));
    t0 = cycles();
    RVV(ntt)(va, QDATA);
    t_rvv = cycles() - t0;
    printf("  NTT cycles: reference -Os %lu, reference -O2 %lu, Xkyber -Os %lu, Xkyber -O2 %lu,\n"
           "              RV32IM asm single %lu, RV32IM asm dual %lu, RVV %lu\n",
           (unsigned long)t_os, (unsigned long)t_o2, (unsigned long)t_xos, (unsigned long)t_xo2,
           (unsigned long)t_as, (unsigned long)t_ad, (unsigned long)t_rvv);

    /* Rejection sampling (vmsltu, vcpop, vcompress) */
    for (int i = 0; i < REJ_BUFLEN; i++)
        buf[i] = rnd();
    int16_t ref_rej[KYBER_N], o2_rej[KYBER_N], rvv_rej[KYBER_N + 8];
    t0 = cycles();
    unsigned int n_ref = rej_uniform_ref(ref_rej, KYBER_N, buf, REJ_BUFLEN);
    t_ref = cycles() - t0;
    t0 = cycles();
    rej_uniform_ref_O2(o2_rej, KYBER_N, buf, REJ_BUFLEN);
    uint32_t t_ref_o2 = cycles() - t0;
    check("ML-KEM rej. sampling -O2", o2_rej, ref_rej, n_ref, 1);
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
    printf("  cycles: reference -Os %lu, reference -O2 %lu, RVV %lu\n", (unsigned long)t_ref,
           (unsigned long)t_ref_o2, (unsigned long)t_rvv);

    /* Centered binomial sampling (vsext): eta2 = 2 and eta1 = 3 for ML-KEM-512 */
    poly ref_cbd;
    for (int i = 0; i < REJ_BUFLEN; i++)
        buf[i] = rnd();
    cbd_eta2(&ref_cbd, buf);
    RVV(cbd2)(vr, buf, QDATA);
    check("ML-KEM CBD eta = 2", vr, ref_cbd.coeffs, KYBER_N, 1);
    cbd_eta1(&ref_cbd, buf);
    RVV(cbd3)(vr, buf, QDATA);
    check("ML-KEM CBD eta = 3", vr, ref_cbd.coeffs, KYBER_N, 1);

    /* Barrett reduction (vssra with vxrm = rnu) and Montgomery conversion */
    poly ref_red;
    for (int i = 0; i < KYBER_N; i++)
        ref_red.coeffs[i] = (int16_t)rnd();
    memcpy(vr, ref_red.coeffs, KYBER_N * sizeof(int16_t));
    poly_reduce(&ref_red);
    RVV(poly_reduce)(vr);
    check("ML-KEM Barrett reduction", vr, ref_red.coeffs, KYBER_N, 0);

    for (int i = 0; i < KYBER_N; i++)
        ref_red.coeffs[i] = (int16_t)rnd();
    memcpy(vr, ref_red.coeffs, KYBER_N * sizeof(int16_t));
    poly_tomont(&ref_red);
    RVV(poly_tomont)(vr);
    check("ML-KEM to Montgomery", vr, ref_red.coeffs, KYBER_N, 0);

    if (failures)
        printf("PQC RVV KYBER: %d FAILED\n", failures);
    else
        printf("PQC RVV KYBER: PASSED\n");
    return failures;
}
