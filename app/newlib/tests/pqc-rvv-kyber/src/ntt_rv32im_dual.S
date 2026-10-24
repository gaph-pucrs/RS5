/*
 * PQRV's dual-issue RV32IM NTT (pqrv/ntt_dualissue_plant_rv32im.S), with its symbols
 * renamed so both the single- and dual-issue versions can be linked.
 */
#define ntt_rv32im ntt_dual_rv32im
#define intt_rv32im intt_dual_rv32im
#define poly_basemul_acc_rv32im poly_basemul_acc_dual_rv32im
#define poly_basemul_acc_end_rv32im poly_basemul_acc_end_dual_rv32im
#define poly_basemul_cache_init_rv32im poly_basemul_cache_init_dual_rv32im
#define poly_basemul_acc_cache_init_rv32im poly_basemul_acc_cache_init_dual_rv32im
#define poly_basemul_acc_cache_init_end_rv32im poly_basemul_acc_cache_init_end_dual_rv32im
#define poly_basemul_acc_cached_rv32im poly_basemul_acc_cached_dual_rv32im
#define poly_basemul_acc_cache_end_rv32im poly_basemul_acc_cache_end_dual_rv32im
#define poly_plantard_rdc_rv32im poly_plantard_rdc_dual_rv32im
#define poly_toplant_rv32im poly_toplant_dual_rv32im

#include "pqrv/ntt_dualissue_plant_rv32im.S"
