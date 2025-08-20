/*
   Register access functions for RISC-V system registers.
   SPDX-License-Identifier: Unlicense

   https://five-embeddev.com/

*/

#ifndef RISCV_CSR_HPM_H
#define RISCV_CSR_HPM_H

#include <stdint.h>

#if __riscv_xlen==32
typedef uint32_t uint_xlen_t;
typedef uint32_t uint_csr32_t;
typedef uint32_t uint_csr64_t;
#elif __riscv_xlen==64
typedef uint64_t uint_xlen_t;
typedef uint32_t uint_csr32_t;
typedef uint64_t uint_csr64_t;
#else
#error "Unknown XLEN"
#endif

// Test for Zicsr extension, if relevant
#if defined(__riscv_arch_test)
#if !defined(__riscv_zicsr)
#error "-march must include zicsr to access CSRs"
#endif
#endif

/*******************************************
 * mhpmcounter5 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter5(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter5"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter5(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter5, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter5(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter5, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter6 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter6(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter6"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter6(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter6, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter6(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter6, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter7 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter7(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter7"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter7(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter7, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter7(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter7, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter8 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter8(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter8"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter8(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter8, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter8(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter8, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter9 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter9(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter9"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter9(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter9, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter9(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter9, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter10 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter10(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter10"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter10(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter10, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter10(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter10, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter11 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter11(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter11"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter11(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter11, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter11(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter11, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter12 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter12(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter12"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter12(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter12, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter12(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter12, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter13 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter13(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter13"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter13(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter13, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter13(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter13, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter14 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter14(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter14"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter14(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter14, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter14(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter14, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter15 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter15(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter15"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter15(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter15, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter15(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter15, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter16 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter16(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter16"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter16(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter16, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter16(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter16, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter17 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter17(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter17"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter17(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter17, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter17(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter17, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter18 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter18(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter18"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter18(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter18, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter18(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter18, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter19 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter19(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter19"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter19(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter19, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter19(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter19, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter20 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter20(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter20"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter20(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter20, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter20(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter20, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter21 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter21(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter21"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter21(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter21, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter21(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter21, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter22 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter22(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter22"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter22(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter22, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter22(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter22, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter23 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter23(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter23"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter23(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter23, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter23(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter23, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter24 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter24(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter24"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter24(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter24, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter24(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter24, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter25 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter25(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter25"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter25(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter25, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter25(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter25, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter26 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter26(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter26"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter26(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter26, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter26(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter26, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter27 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter27(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter27"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter27(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter27, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter27(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter27, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter28 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter28(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter28"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter28(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter28, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter28(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter28, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter29 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter29(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter29"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter29(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter29, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter29(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter29, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter30 - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter30(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter30"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter30(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter30, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter30(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter30, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}


/*******************************************
 * Utils
 */

static void read_hpms(int *hpm_values) {
  hpm_values[ 0] = csr_read_mcycle();
  //hpm_values[ 1] = ();
  hpm_values[ 2] = csr_read_minstret();
  hpm_values[ 3] = csr_read_mhpmcounter3();
  hpm_values[ 4] = csr_read_mhpmcounter4();
  hpm_values[ 5] = csr_read_mhpmcounter5();
  hpm_values[ 6] = csr_read_mhpmcounter6();
  hpm_values[ 7] = csr_read_mhpmcounter7();
  hpm_values[ 8] = csr_read_mhpmcounter8();
  hpm_values[ 9] = csr_read_mhpmcounter9();
  hpm_values[10] = csr_read_mhpmcounter10();
  hpm_values[11] = csr_read_mhpmcounter11();
  hpm_values[12] = csr_read_mhpmcounter12();
  hpm_values[13] = csr_read_mhpmcounter13();
  hpm_values[14] = csr_read_mhpmcounter14();
  hpm_values[15] = csr_read_mhpmcounter15();
  hpm_values[16] = csr_read_mhpmcounter16();
  hpm_values[17] = csr_read_mhpmcounter17();
  hpm_values[18] = csr_read_mhpmcounter18();
  hpm_values[19] = csr_read_mhpmcounter19();
  hpm_values[20] = csr_read_mhpmcounter20();
  hpm_values[21] = csr_read_mhpmcounter21();
  hpm_values[22] = csr_read_mhpmcounter22();
  hpm_values[23] = csr_read_mhpmcounter23();
  hpm_values[24] = csr_read_mhpmcounter24();
  hpm_values[25] = csr_read_mhpmcounter25();
  hpm_values[26] = csr_read_mhpmcounter26();
  hpm_values[27] = csr_read_mhpmcounter27();
  hpm_values[28] = csr_read_mhpmcounter28();
  hpm_values[29] = csr_read_mhpmcounter29();
  hpm_values[30] = csr_read_mhpmcounter30();
  hpm_values[31] = csr_read_mhpmcounter31();
}

static void evaluate_hpms(int *hpm_values_0, int *hpm_values_1) {
  int hpms[32];

  hpms[ 0] = (int)(hpm_values_1[ 0] - hpm_values_0[ 0]);
  hpms[ 1] = (int)(hpm_values_1[ 1] - hpm_values_0[ 1]);
  hpms[ 2] = (int)(hpm_values_1[ 2] - hpm_values_0[ 2]);
  hpms[ 3] = (int)(hpm_values_1[ 3] - hpm_values_0[ 3]);
  hpms[ 4] = (int)(hpm_values_1[ 4] - hpm_values_0[ 4]);
  hpms[ 5] = (int)(hpm_values_1[ 5] - hpm_values_0[ 5]);
  hpms[ 6] = (int)(hpm_values_1[ 6] - hpm_values_0[ 6]);
  hpms[ 7] = (int)(hpm_values_1[ 7] - hpm_values_0[ 7]);
  hpms[ 8] = (int)(hpm_values_1[ 8] - hpm_values_0[ 8]);
  hpms[ 9] = (int)(hpm_values_1[ 9] - hpm_values_0[ 9]);
  hpms[10] = (int)(hpm_values_1[10] - hpm_values_0[10]);
  hpms[11] = (int)(hpm_values_1[11] - hpm_values_0[11]);
  hpms[12] = (int)(hpm_values_1[12] - hpm_values_0[12]);
  hpms[13] = (int)(hpm_values_1[13] - hpm_values_0[13]);
  hpms[14] = (int)(hpm_values_1[14] - hpm_values_0[14]);
  hpms[15] = (int)(hpm_values_1[15] - hpm_values_0[15]);
  hpms[16] = (int)(hpm_values_1[16] - hpm_values_0[16]);
  hpms[17] = (int)(hpm_values_1[17] - hpm_values_0[17]);
  hpms[18] = (int)(hpm_values_1[18] - hpm_values_0[18]);
  hpms[19] = (int)(hpm_values_1[19] - hpm_values_0[19]);
  hpms[20] = (int)(hpm_values_1[20] - hpm_values_0[20]);
  hpms[21] = (int)(hpm_values_1[21] - hpm_values_0[21]);
  hpms[22] = (int)(hpm_values_1[22] - hpm_values_0[22]);
  hpms[23] = (int)(hpm_values_1[23] - hpm_values_0[23]);
  hpms[24] = (int)(hpm_values_1[24] - hpm_values_0[24]);
  hpms[25] = (int)(hpm_values_1[25] - hpm_values_0[25]);
  hpms[26] = (int)(hpm_values_1[26] - hpm_values_0[26]);
  hpms[27] = (int)(hpm_values_1[27] - hpm_values_0[27]);
  hpms[28] = (int)(hpm_values_1[28] - hpm_values_0[28]);
  hpms[29] = (int)(hpm_values_1[29] - hpm_values_0[29]);
  hpms[30] = (int)(hpm_values_1[30] - hpm_values_0[30]);
  hpms[31] = (int)(hpm_values_1[31] - hpm_values_0[31]);



  printf("HPM Counters - Cycles Measured:\n");
  printf("Cycles[ 0] - Cycles:       %0d\n", hpms[ 0]);
//printf("Cycles[ 1] - Time:         %0d\n", hpms[ 1]);
  printf("Cycles[ 2] - Inst Retired: %0d\n", hpms[ 2]);
  printf("Cycles[ 3] - Inst Killed:  %0d\n", hpms[ 3]);
  printf("Cycles[ 4] - Cntxt Switch: %0d\n", hpms[ 4]);
  printf("Cycles[ 5] - Exceptions:   %0d\n", hpms[ 5]);
  printf("Cycles[ 6] - Interrupts:   %0d\n", hpms[ 6]);
  printf("Cycles[ 7] - Hazards:      %0d\n", hpms[ 7]);
  printf("Cycles[ 8] - Stalls:       %0d\n", hpms[ 8]);
  printf("Cycles[ 9] - NOPS:         %0d\n", hpms[ 9]);
  printf("Cycles[10] - Logics:       %0d\n", hpms[10]);
  printf("Cycles[11] - Add-Subs:     %0d\n", hpms[11]);
  printf("Cycles[12] - Shifts:       %0d\n", hpms[12]);
  printf("Cycles[13] - Branches:     %0d\n", hpms[13]);
  printf("Cycles[14] - Jumps:        %0d\n", hpms[14]);
  printf("Cycles[15] - Loads:        %0d\n", hpms[15]);
  printf("Cycles[16] - Stores:       %0d\n", hpms[16]);
  printf("Cycles[17] - Sys:          %0d\n", hpms[17]);
  printf("Cycles[18] - CSR:          %0d\n", hpms[18]);
  printf("Cycles[19] - Lui/SLT:      %0d\n", hpms[19]);
  printf("Cycles[20] - Compressed:   %0d\n", hpms[20]);
  printf("Cycles[21] - Misaligned:   %0d\n", hpms[21]);
  printf("Cycles[22] - Mults:        %0d\n", hpms[22]);
  printf("Cycles[23] - Divs:         %0d\n", hpms[23]);
  printf("Cycles[24] - V-Add-Subs:   %0d\n", hpms[24]);
  printf("Cycles[25] - V-Mults:      %0d\n", hpms[25]);
  printf("Cycles[26] - V-Divs:       %0d\n", hpms[26]);
  printf("Cycles[27] - V-Macs:       %0d\n", hpms[27]);
  printf("Cycles[28] - V-Reductions: %0d\n", hpms[28]);
  printf("Cycles[29] - V-Load-Store: %0d\n", hpms[29]);
  printf("Cycles[30] - V-Others:     %0d\n", hpms[30]);
//printf("Cycles[31] -  :            %0d\n", hpms[31]);
  printf("Scalar LOAD-STORES  = %0d\n", hpms[15] + hpms[16]);
  printf("Vector Instructions = %0d\n", hpms[24] + hpms[25] + hpms[26] + hpms[27] + hpms[28] + hpms[29] + hpms[30]);
  printf("Vector LOAD-STORES  = %0d\n", hpms[29]);
  printf("\n");

}

#endif // #define RISCV_CSR_HPM_H
