#ifndef DILITHIUM_NTT_RVV_VLEN128_H
#define DILITHIUM_NTT_RVV_VLEN128_H

#include <stdint.h>

extern const int32_t qdata_vlen128[1296];
extern void ntt_rvv_vlen128(int32_t *r, const int32_t *table);
extern void intt_rvv_vlen128(int32_t *r, const int32_t *table);
extern void poly_basemul_rvv_vlen128(int32_t *r, const int32_t *a,
                                     const int32_t *b);
extern void poly_basemul_acc_rvv_vlen128(int32_t *r, const int32_t *a,
                                         const int32_t *b);
extern void ntt2normal_order_rvv_vlen128(int32_t *r, const int32_t *table);
extern void normal2ntt_order_rvv_vlen128(int32_t *r, const int32_t *table);
extern void poly_reduce_rvv_vlen128(int32_t *r);

#endif