/*
 * PQRV's dual-issue RV32IM NTT (pqrv/ntt_dualissue_mont_rv32im.S), with its symbols
 * renamed so both the single- and dual-issue versions can be linked.
 */
#define ntt_rv32im ntt_dual_rv32im
#define intt_rv32im intt_dual_rv32im
#define poly_basemul_8l_init_rv32im poly_basemul_8l_init_dual_rv32im
#define poly_basemul_8l_acc_rv32im poly_basemul_8l_acc_dual_rv32im
#define poly_basemul_8l_acc_end_rv32im poly_basemul_8l_acc_end_dual_rv32im
#define poly_basemul_8l_rv32im poly_basemul_8l_dual_rv32im
#define polyvec_basemul_poly_8l_rv32im polyvec_basemul_poly_8l_dual_rv32im
#define poly_reduce_rv32im poly_reduce_dual_rv32im

#include "pqrv/ntt_dualissue_mont_rv32im.S"
