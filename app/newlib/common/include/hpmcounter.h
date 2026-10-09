/**
 * @file hpmcounter.h
 * @brief Simple and ergonomic interface for RS5 Hardware Performance Monitor (HPM) counters.
 *
 * Usage:
 *   #include "hpmcounter.h"
 *
 *   int main() {
 *       start_counter();   // optional: marks the start of the block to profile
 *
 *       // ... your code / benchmark ...
 *
 *       print_counter_group(ZKNEnable); // prints only specific instruction group
 *       // or
 *       print_counter();                // prints all counters (default)
 *       return 0;
 *   }
 */

#ifndef HPMCOUNTER_H
#define HPMCOUNTER_H

#include <stdint.h>
#include <stdio.h>
#include "riscv-csr.h"
#include "riscv-csr-hpm.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Internal snapshot storage */
static uint32_t _hpm_internal_start[64];
static uint32_t _hpm_internal_end[64];
static int      _hpm_internal_active = 0;

/**
 * @brief Starts HPM profiling.
 * Takes a snapshot of all counter values and un-inhibits (enables) counters.
 */
static inline void start_counter(void) {
    csr_write_mcountinhibit(~0U);   /* Pause counters to take a clean snapshot */
    read_hpms(_hpm_internal_start);
    _hpm_internal_active = 1;
    csr_write_mcountinhibit(0);     /* Enable all counters */
}

/**
 * @brief Stops HPM profiling without printing yet.
 * Freezes the end snapshot at this exact moment.
 */
static inline void stop_counter(void) {
    csr_write_mcountinhibit(~0U);   /* Inhibit / pause counters */
    read_hpms(_hpm_internal_end);
    _hpm_internal_active = 2;       /* Mark snapshot as frozen */
}

/**
 * @brief Prints HPM counters filtered by a bitmask of hardware enables.
 *
 * Examples:
 *   print_counter_group(ZKNEnable);                     // Only AES/SHA2
 *   print_counter_group(ZKNEnable | HPMCOUNTEREnable);  // AES/SHA2 + Base cycles
 *   print_counter_group(VEnable);                       // Only Vector instructions
 *   print_counter_group(HPM_ALL);                       // All counters
 *
 * @param enable_mask Bitmask of hpm_enable_e flags to print.
 */
static inline void print_counter_group(uint32_t enable_mask) {
    csr_write_mcountinhibit(~0U);   /* Inhibit counters during reading/printing */
    if (_hpm_internal_active != 2) {
        read_hpms(_hpm_internal_end);
    }

    if (_hpm_internal_active) {
        evaluate_hpms_filtered(_hpm_internal_start, _hpm_internal_end, enable_mask);
    } else {
        /* Print absolute values since reset */
        uint32_t zero_baseline[64] = {0};
        evaluate_hpms_filtered(zero_baseline, _hpm_internal_end, enable_mask);
    }
}

/**
 * @brief Prints all HPM counters (default behavior, 100% backward compatible).
 */
static inline void print_counter(void) {
    print_counter_group(HPM_ALL);
}

/**
 * @brief Resets the baseline snapshot.
 */
static inline void reset_counter(void) {
    for (int i = 0; i < 64; i++) {
        _hpm_internal_start[i] = 0;
        _hpm_internal_end[i] = 0;
    }
    _hpm_internal_active = 0;
    csr_write_mcountinhibit(0);
}

/* Plural aliases for convenience */
static inline void start_counters(void) { start_counter(); }
static inline void stop_counters(void)  { stop_counter(); }
static inline void print_counters(void) { print_counter(); }
static inline void reset_counters(void) { reset_counter(); }

/**
 * @brief Independent counter snapshot structure for profiling multiple distinct code blocks.
 * Example:
 *   hpm_counter_t h_kp, h_dec;
 *   hpm_start(&h_kp);  crypto_kem_keypair(...); hpm_stop(&h_kp);
 *   hpm_start(&h_dec); crypto_kem_dec(...);     hpm_stop(&h_dec);
 *   hpm_print_group(&h_kp, XKYBEREnable);
 *   hpm_print_group(&h_dec, XKYBEREnable);
 */
typedef struct {
    uint32_t start[64];
    uint32_t end[64];
} hpm_counter_t;

static inline void hpm_start(hpm_counter_t *h) {
    csr_write_mcountinhibit(~0U);
    read_hpms(h->start);
    csr_write_mcountinhibit(0);
}

static inline void hpm_stop(hpm_counter_t *h) {
    csr_write_mcountinhibit(~0U);
    read_hpms(h->end);
}

static inline void hpm_print_group(hpm_counter_t *h, uint32_t enable_mask) {
    evaluate_hpms_filtered(h->start, h->end, enable_mask);
}

static inline void hpm_print(hpm_counter_t *h) {
    hpm_print_group(h, HPM_ALL);
}

/**
 * @brief Returns the value (delta) of a single HPM counter index.
 */
static inline uint32_t hpm_get(const hpm_counter_t *h, int idx) {
    if (idx >= 0 && idx < 64) {
        return h->end[idx] - h->start[idx];
    }
    return 0;
}

/**
 * @brief Prints a single HPM counter in the standard box format.
 */
static inline void hpm_print_counter(const hpm_counter_t *h, int idx) {
    evaluate_hpm_single((uint32_t*)h->start, (uint32_t*)h->end, idx);
}
static inline void hpm_print_single(const hpm_counter_t *h, int idx) {
    hpm_print_counter(h, idx);
}

/**
 * @brief Global single counter getters and printers (for start_counter/stop_counter workflow)
 */
static inline uint32_t get_counter(int idx) {
    if (idx >= 0 && idx < 64) {
        if (_hpm_internal_active != 2) {
            read_hpms(_hpm_internal_end);
        }
        return _hpm_internal_end[idx] - _hpm_internal_start[idx];
    }
    return 0;
}

static inline void print_counter_single(int idx) {
    csr_write_mcountinhibit(~0U);
    if (_hpm_internal_active != 2) {
        read_hpms(_hpm_internal_end);
    }
    evaluate_hpm_single(_hpm_internal_start, _hpm_internal_end, idx);
}

#ifdef __cplusplus
}
#endif

#endif /* HPMCOUNTER_H */
