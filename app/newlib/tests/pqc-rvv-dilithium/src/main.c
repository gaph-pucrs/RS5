/*
 * ML-DSA (Dilithium) kernels written with RVV, run on RS5 and checked against
 * the scalar reference implementation (ntt.c, reduce.c from pq-crystals).
 *
 * The vector code is PQRV's ntt_rvv_vlen128.S for Dilithium
 * (https://github.com/Ji-Peng/PQRV, commit 005d55d, MIT, see LICENSE-PQRV).
 * It assumes VLEN = 128 and uses vrgather, vmerge and SEW = 32 vmul/vmulh.
 *
 * Checks: polynomial product (NTT, pointwise Montgomery product, inverse NTT),
 * the RVV NTT against the reference NTT after reordering, the order
 * conversions, and reduction. Prints cycle counts next to the reference.
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "ntt.h"
#include "ntt_rvv_vlen128.h"
#include "params.h"
#include "reduce.h"

static int failures;

static uint32_t lcg_state = 54321;
static uint32_t rnd(void)
{
    lcg_state = lcg_state * 1664525u + 1013904223u;
    return lcg_state;
}

static uint32_t cycles(void)
{
    uint32_t c;
    __asm__ volatile("csrr %0, mcycle" : "=r"(c));
    return c;
}

static int32_t canonical(int32_t x)
{
    int32_t r = x % Q;
    return r < 0 ? r + Q : r;
}

static void check(const char *name, const int32_t *got, const int32_t *exp, int n)
{
    for (int i = 0; i < n; i++) {
        if (canonical(got[i]) != canonical(exp[i])) {
            printf("%-30s FAILED at %d: got %ld, expected %ld\n", name, i,
                   (long)canonical(got[i]), (long)canonical(exp[i]));
            failures++;
            return;
        }
    }
    printf("%-30s PASSED\n", name);
}

static int32_t a[N], b[N], ref_a[N], ref_b[N], ref_c[N];
static int32_t va[N] __attribute__((aligned(16)));
static int32_t vb[N] __attribute__((aligned(16)));
static int32_t vc[N] __attribute__((aligned(16)));

int main(void)
{
    uint32_t t0, t_ref, t_rvv;

    for (int i = 0; i < N; i++) {
        a[i] = rnd() % Q;
        b[i] = rnd() % Q;
    }

    /* Polynomial product: ref (ntt, pointwise, intt) against the RVV kernels */
    memcpy(ref_a, a, sizeof(a));
    memcpy(ref_b, b, sizeof(b));
    t0 = cycles();
    ntt(ref_a);
    t_ref = cycles() - t0;
    ntt(ref_b);
    for (int i = 0; i < N; i++)
        ref_c[i] = montgomery_reduce((int64_t)ref_a[i] * ref_b[i]);
    intt(ref_c);

    memcpy(va, a, sizeof(a));
    memcpy(vb, b, sizeof(b));
    t0 = cycles();
    ntt_rvv_vlen128(va, qdata_vlen128);
    t_rvv = cycles() - t0;
    ntt_rvv_vlen128(vb, qdata_vlen128);
    poly_basemul_rvv_vlen128(vc, va, vb);
    intt_rvv_vlen128(vc, qdata_vlen128);

    check("ML-DSA polynomial product", vc, ref_c, N);
    printf("  NTT cycles: reference %lu, RVV %lu\n", (unsigned long)t_ref, (unsigned long)t_rvv);

    /* The RVV NTT keeps its own coefficient order: back to the reference order */
    memcpy(va, a, sizeof(a));
    ntt_rvv_vlen128(va, qdata_vlen128);
    ntt2normal_order_rvv_vlen128(va, qdata_vlen128);
    check("ML-DSA NTT in reference order", va, ref_a, N);

    /* normal -> NTT order -> normal is the identity */
    memcpy(va, a, sizeof(a));
    normal2ntt_order_rvv_vlen128(va, qdata_vlen128);
    ntt2normal_order_rvv_vlen128(va, qdata_vlen128);
    check("ML-DSA order round trip", va, a, N);

    /* Reduction */
    for (int i = 0; i < N; i++)
        va[i] = (int32_t)(rnd() >> 1) - (1 << 30);
    for (int i = 0; i < N; i++)
        ref_c[i] = reduce32(va[i]);
    poly_reduce_rvv_vlen128(va);
    check("ML-DSA reduction", va, ref_c, N);

    if (failures)
        printf("PQC RVV DILITHIUM: %d FAILED\n", failures);
    else
        printf("PQC RVV DILITHIUM: PASSED\n");
    return failures;
}
