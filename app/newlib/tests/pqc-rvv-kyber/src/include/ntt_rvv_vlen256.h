#ifndef KYBER_NTT_RVV_VLEN256_H
#define KYBER_NTT_RVV_VLEN256_H

#include <stdint.h>

extern const int16_t qdata_vlen256[1110];
extern void ntt_rvv_vlen256(int16_t *r, const int16_t *table);
extern void intt_rvv_vlen256(int16_t *r, const int16_t *table);

extern void poly_basemul_rvv_vlen256(int16_t *r, const int16_t *a,
                                     const int16_t *b,
                                     const int16_t *table);
extern void poly_basemul_acc_rvv_vlen256(int16_t *r, const int16_t *a,
                                         const int16_t *b,
                                         const int16_t *table);
extern void poly_basemul_cache_init_rvv_vlen256(int16_t *r,
                                                const int16_t *a,
                                                const int16_t *b,
                                                const int16_t *table,
                                                int16_t *b_cache);
extern void poly_basemul_acc_cache_init_rvv_vlen256(int16_t *r,
                                                    const int16_t *a,
                                                    const int16_t *b,
                                                    const int16_t *table,
                                                    int16_t *b_cache);
extern void poly_basemul_cached_rvv_vlen256(int16_t *r, const int16_t *a,
                                            const int16_t *b,
                                            const int16_t *table,
                                            int16_t *b_cache);
extern void poly_basemul_acc_cached_rvv_vlen256(int16_t *r,
                                                const int16_t *a,
                                                const int16_t *b,
                                                const int16_t *table,
                                                int16_t *b_cache);
extern void poly_reduce_rvv_vlen256(int16_t *r);
extern void poly_tomont_rvv_vlen256(int16_t *r);

extern void ntt2normal_order_rvv_vlen256(int16_t *r, const int16_t *table);
extern void normal2ntt_order_rvv_vlen256(int16_t *r, const int16_t *table);
extern void rej_uniform_rvv_vlen256(int16_t *r, const uint8_t *buf,
                                    const int16_t *table, uint32_t *ctr_p,
                                    uint32_t *pos_p);
extern void cbd2_rvv_vlen256(int16_t *r, const uint8_t *buf,
                             const int16_t *table);
extern void cbd3_rvv_vlen256(int16_t *r, const uint8_t *buf,
                             const int16_t *table);

#endif