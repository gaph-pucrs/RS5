/*
 * PQRV's single-issue RV32IM NTT (pqrv/ntt_singleissue_mont_rv32im.S), with its symbols
 * renamed so both the single- and dual-issue versions can be linked.
 */
#define ntt_rv32im ntt_single_rv32im
#define intt_rv32im intt_single_rv32im
#define poly_basemul_8l_init_rv32im poly_basemul_8l_init_single_rv32im
#define poly_basemul_8l_acc_rv32im poly_basemul_8l_acc_single_rv32im
#define poly_basemul_8l_acc_end_rv32im poly_basemul_8l_acc_end_single_rv32im
#define poly_basemul_8l_rv32im poly_basemul_8l_single_rv32im
#define polyvec_basemul_poly_8l_rv32im polyvec_basemul_poly_8l_single_rv32im
#define poly_reduce_rv32im poly_reduce_single_rv32im

#include "pqrv/ntt_singleissue_mont_rv32im.S"
