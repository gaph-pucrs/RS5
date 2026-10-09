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
 * mhpmcounter24H - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter24h(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter24h"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter24h(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter24h, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter24h(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter24h, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter25H - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter25h(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter25h"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter25h(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter25h, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter25h(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter25h, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter29H - MRW - Event Counters
 */
static inline uint64_t csr_read_mhpmcounter29h(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter29h"
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter29h(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter29h, %0"
                      : /* output: none */
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter29h(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter29h, %1"
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}


/*******************************************
 * mhpmcounter7H - MRW - Stall High (Upper 32 bits, RV32)
 */
static inline uint64_t csr_read_mhpmcounter7h(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter7h"
                      : "=r" (value)
                      :
                      :);
    return value;
}
static inline void csr_write_mhpmcounter7h(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter7h, %0"
                      :
                      : "r" (value)
                      :);
}
static inline uint64_t csr_read_write_mhpmcounter7h(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter7h, %1"
                      : "=r" (prev_value)
                      : "r" (new_value)
                      :);
    return prev_value;
}

/*******************************************
 * mhpmcounter9H - MRW - Add/Sub High (Upper 32 bits, RV32)
 */
static inline uint64_t csr_read_mhpmcounter9h(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter9h"
                      : "=r" (value)
                      :
                      :);
    return value;
}
static inline void csr_write_mhpmcounter9h(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter9h, %0"
                      :
                      : "r" (value)
                      :);
}
static inline uint64_t csr_read_write_mhpmcounter9h(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter9h, %1"
                      : "=r" (prev_value)
                      : "r" (new_value)
                      :);
    return prev_value;
}

/*******************************************
 * mhpmcounter13H - MRW - Load High (Upper 32 bits, RV32)
 */
static inline uint64_t csr_read_mhpmcounter13h(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter13h"
                      : "=r" (value)
                      :
                      :);
    return value;
}
static inline void csr_write_mhpmcounter13h(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter13h, %0"
                      :
                      : "r" (value)
                      :);
}
static inline uint64_t csr_read_write_mhpmcounter13h(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter13h, %1"
                      : "=r" (prev_value)
                      : "r" (new_value)
                      :);
    return prev_value;
}

/*******************************************
 * mhpmcounter30H - MRW - Vector Cycles High (Upper 32 bits, RV32)
 */
static inline uint64_t csr_read_mhpmcounter30h(void) {
    uint_csr64_t value;
    __asm__ volatile ("csrr    %0, mhpmcounter30h"
                      : "=r" (value)
                      :
                      :);
    return value;
}
static inline void csr_write_mhpmcounter30h(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter30h, %0"
                      :
                      : "r" (value)
                      :);
}
static inline uint64_t csr_read_write_mhpmcounter30h(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter30h, %1"
                      : "=r" (prev_value)
                      : "r" (new_value)
                      :);
    return prev_value;
}


/*******************************************
 * Utils
 */

static void read_hpms(uint32_t *hpm_values) {
  hpm_values[ 0] = csr_read_mcycle();
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

  /* Upper 32-bit registers for 64-bit counters (stored at 32 + index) */
  hpm_values[39] = csr_read_mhpmcounter7h();   /* Stall High: 32 + 7  = 39 */
  hpm_values[41] = csr_read_mhpmcounter9h();   /* Add/Sub High: 32 + 9  = 41 */
  hpm_values[45] = csr_read_mhpmcounter13h();  /* Load High: 32 + 13 = 45 */
  hpm_values[62] = csr_read_mhpmcounter30h();  /* Vector Cycles High: 32 + 30 = 62 */
}

/* Hardware Enable Bitmask Enum (mapped 1:1 to RS5 CSRBank.sv parameters) */
typedef enum {
    HPMCOUNTEREnable   = (1 << 0), /* Base RV32I, Pipeline & Overview Counters */
    AMOEXT             = (1 << 1), /* Atomic Instructions (AMO, LR, SC) */
    COMPRESSED         = (1 << 2), /* RVC Compressed Instructions & Misaligned Jumps */
    MULEXT             = (1 << 3), /* Multiplication & Division/Remainder */
    ZKNEnable          = (1 << 4), /* AES & SHA2 Cryptographic Extensions */
    XKYBEREnable       = (1 << 5), /* Kyber ML-KEM Post-Quantum Cryptography Accelerator */
    VEnable            = (1 << 6), /* Vector Extension Units (Add/Sub, Mul, Div, Mem, Cycles) */
    HPM_ALL            = (HPMCOUNTEREnable | AMOEXT | COMPRESSED | MULEXT | ZKNEnable | XKYBEREnable | VEnable)
} hpm_enable_e;

/* Convenience aliases with HPM_ prefix */
#define HPM_HPMCOUNTEREnable   HPMCOUNTEREnable
#define HPM_AMOEXT             AMOEXT
#define HPM_COMPRESSED         COMPRESSED
#define HPM_MULEXT             MULEXT
#define HPM_ZKNEnable          ZKNEnable
#define HPM_XKYBEREnable       XKYBEREnable
#define HPM_VEnable            VEnable
#define HPM_ENABLE_ALL         HPM_ALL

/* Individual HPM counter index definitions */
typedef enum {
    HPM_CYCLES          = 0,  /* Clock Cycles */
    HPM_TIME            = 1,  /* Timer */
    HPM_INSTRET         = 2,  /* Instructions Retired */
    HPM_FETCH_STALL     = 3,  /* Fetch Stalls */
    HPM_FETCH_MISALIGN  = 4,  /* Fetch Misaligned */
    HPM_INTERRUPTS      = 5,  /* Interrupt Count */
    HPM_HAZARDS         = 6,  /* Hazard Count */
    HPM_STALLS          = 7,  /* Pipeline Stalls */
    HPM_LOGIC           = 8,  /* Logic Instructions (AND, OR, XOR) */
    HPM_ADD_SUB         = 9,  /* Add / Sub Instructions */
    HPM_SHIFT_ROTATE    = 10, /* Shift / Rotate Instructions */
    HPM_BRANCHES        = 11, /* Conditional Branches */
    HPM_JUMPS           = 12, /* Jumps (JAL, JALR) */
    HPM_LOADS           = 13, /* Memory Loads */
    HPM_STORES          = 14, /* Memory Stores */
    HPM_AMO             = 15, /* Atomic Instructions (AMO) */
    HPM_SYSTEM          = 16, /* System Instructions */
    HPM_CSR             = 17, /* CSR Instructions */
    HPM_OTHER           = 18, /* LUI, AUIPC, SLT */
    HPM_COMPRESSED_INST = 19, /* Compressed Instructions (RVC) */
    HPM_MISALIGNED_JUMP = 20, /* Misaligned Jumps */
    HPM_MUL             = 21, /* Multiplication Instructions */
    HPM_DIV_REM         = 22, /* Division / Remainder */
    HPM_AES_SHA2        = 23, /* AES & SHA-2 Cryptographic Instructions */
    HPM_KYBER           = 24, /* Kyber Post-Quantum Instructions */
    HPM_VADD_SUB        = 25, /* Vector Add / Sub */
    HPM_VMUL            = 26, /* Vector Mul / MAC */
    HPM_VDIV_REM        = 27, /* Vector Div / Rem */
    HPM_VOTHERS         = 28, /* Vector Others */
    HPM_VMEM            = 29, /* Vector Memory (Load / Store) */
    HPM_VCYCLES         = 30  /* Vector Active Cycles */
} hpm_idx_e;

static inline void evaluate_hpm_single(uint32_t *hpm_values_0, uint32_t *hpm_values_1, int idx) {
    if (idx < 0 || idx >= 32) return;
    uint32_t val = hpm_values_1[idx] - hpm_values_0[idx];
    const char *name = "Counter";
    switch (idx) {
        case 0:  name = "Clock Cycles"; break;
        case 1:  name = "Timer"; break;
        case 2:  name = "Inst Retired"; break;
        case 3:  name = "Inst Killed"; break;
        case 4:  name = "Exceptions"; break;
        case 5:  name = "Interrupts"; break;
        case 6:  name = "Hazards"; break;
        case 7:  name = "Stalls"; break;
        case 8:  name = "Logic"; break;
        case 9:  name = "Add/Sub"; break;
        case 10: name = "Shift/Rotate"; break;
        case 11: name = "Branches"; break;
        case 12: name = "Jumps"; break;
        case 13: name = "Loads"; break;
        case 14: name = "Stores"; break;
        case 15: name = "Atomic (AMO)"; break;
        case 16: name = "System"; break;
        case 17: name = "CSR"; break;
        case 18: name = "LUI/AUIPC/SLT"; break;
        case 19: name = "Compressed"; break;
        case 20: name = "Misaligned Jump"; break;
        case 21: name = "Mul"; break;
        case 22: name = "Div/Rem"; break;
        case 23: name = "AES + SHA2"; break;
        case 24: name = "Kyber"; break;
        case 25: name = "Vector Add/Sub"; break;
        case 26: name = "Vector Mul/MAC"; break;
        case 27: name = "Vector Div/Rem"; break;
        case 28: name = "Vector Others"; break;
        case 29: name = "Vector Mem LS"; break;
        case 30: name = "Vector Cycl"; break;
        default: name = "Unknown"; break;
    }
    printf("\n================ HPM Counters ================\n");
    printf("Cycles[%2d] - %-16s %0u\n", idx, name, (unsigned int)val);
    printf("==============================================\n\n");
}


static void evaluate_hpms_filtered(uint32_t *hpm_values_0, uint32_t *hpm_values_1, uint32_t enable_mask) {
  int hpms [64];

  for (int i = 0; i < 32; i++) {
    hpms[i] = (int)(hpm_values_1[i] - hpm_values_0[i]);
  }

  hpms[39] = (int)(hpm_values_1[39] - hpm_values_0[39]);
  hpms[41] = (int)(hpm_values_1[41] - hpm_values_0[41]);
  hpms[45] = (int)(hpm_values_1[45] - hpm_values_0[45]);
  hpms[62] = (int)(hpm_values_1[62] - hpm_values_0[62]);

  printf("\n================ HPM Counters ================\n");
  if (enable_mask & HPMCOUNTEREnable) {
    printf("Cycles[ 0] - Clock Cycles:     %0u\n", (unsigned int)hpms[ 0]);
    printf("Cycles[ 2] - Inst Retired:     %0u\n", (unsigned int)hpms[ 2]);

    printf("\n-- Pipeline & Telemetria --\n");
    printf("Cycles[ 3] - Inst Killed:      %0u\n", (unsigned int)hpms[ 3]);
    printf("Cycles[ 4] - Exceptions:       %0u\n", (unsigned int)hpms[ 4]);
    printf("Cycles[ 5] - Interrupts:       %0u\n", (unsigned int)hpms[ 5]);
    printf("Cycles[ 6] - Hazards:          %0u\n", (unsigned int)hpms[ 6]);
    if (hpms[39])
      printf("Cycles[ 7] - Stalls (64b):     0x%x%08x\n", (unsigned int)hpms[39], (unsigned int)hpms[ 7]);
    else
      printf("Cycles[ 7] - Stalls:           %0u\n", (unsigned int)hpms[ 7]);

    printf("\n-- Base RV32I --\n");
    printf("Cycles[ 8] - Logic:            %0u\n", (unsigned int)hpms[ 8]);
    if (hpms[41])
      printf("Cycles[ 9] - Add/Sub (64b):    0x%x%08x\n", (unsigned int)hpms[41], (unsigned int)hpms[ 9]);
    else
      printf("Cycles[ 9] - Add/Sub:          %0u\n", (unsigned int)hpms[ 9]);
    printf("Cycles[10] - Shift/Rotate:     %0u\n", (unsigned int)hpms[10]);
    printf("Cycles[11] - Branches:         %0u\n", (unsigned int)hpms[11]);
    printf("Cycles[12] - Jumps:            %0u\n", (unsigned int)hpms[12]);
    if (hpms[45])
      printf("Cycles[13] - Loads (64b):      0x%x%08x\n", (unsigned int)hpms[45], (unsigned int)hpms[13]);
    else
      printf("Cycles[13] - Loads:            %0u\n", (unsigned int)hpms[13]);
    printf("Cycles[14] - Stores:           %0u\n", (unsigned int)hpms[14]);
    printf("Cycles[16] - System:           %0u\n", (unsigned int)hpms[16]);
    printf("Cycles[17] - CSR:              %0u\n", (unsigned int)hpms[17]);
    printf("Cycles[18] - LUI/AUIPC/SLT:    %0u\n", (unsigned int)hpms[18]);
  }

  if (enable_mask & AMOEXT) {
    printf("\n-- AMOEXT --\n");
    printf("Cycles[15] - Atomic (AMO):     %0u\n", (unsigned int)hpms[15]);
  }

  if (enable_mask & COMPRESSED) {
    printf("\n-- COMPRESSED --\n");
    printf("Cycles[19] - Compressed:       %0u\n", (unsigned int)hpms[19]);
    printf("Cycles[20] - Misaligned Jump:  %0u\n", (unsigned int)hpms[20]);
  }

  if (enable_mask & MULEXT) {
    printf("\n-- MULEXT --\n");
    printf("Cycles[21] - Mul:              %0u\n", (unsigned int)hpms[21]);
    printf("Cycles[22] - Div/Rem:          %0u\n", (unsigned int)hpms[22]);
  }

  if (enable_mask & ZKNEnable) {
    printf("\n-- Crypto (ZKNEnable) --\n");
    printf("Cycles[23] - AES + SHA2:       %0u\n", (unsigned int)hpms[23]);
  }

  if (enable_mask & XKYBEREnable) {
    printf("\n-- Crypto (XKYBEREnable) --\n");
    printf("Cycles[24] - Kyber:            %0u\n", (unsigned int)hpms[24]);
  }

  if (enable_mask & VEnable) {
    printf("\n-- VEnable (Extensao Vetorial) --\n");
    printf("Cycles[25] - Vector Add/Sub:   %0u\n", (unsigned int)hpms[25]);
    printf("Cycles[26] - Vector Mul/MAC:   %0u\n", (unsigned int)hpms[26]);
    printf("Cycles[27] - Vector Div/Rem:   %0u\n", (unsigned int)hpms[27]);
    printf("Cycles[28] - Vector Others:    %0u\n", (unsigned int)hpms[28]);
    printf("Cycles[29] - Vector Mem LS:    %0u\n", (unsigned int)hpms[29]);
    if (hpms[62])
      printf("Cycles[30] - Vector Cycl (64b):0x%x%08x\n", (unsigned int)hpms[62], (unsigned int)hpms[30]);
    else
      printf("Cycles[30] - Vector Cycl:      %0u\n", (unsigned int)hpms[30]);
  }

  printf("==============================================\n\n");
}

/* Backward-compatible evaluate_hpms() that evaluates all enabled counters */
static inline void evaluate_hpms(uint32_t *hpm_values_0, uint32_t *hpm_values_1) {
  evaluate_hpms_filtered(hpm_values_0, hpm_values_1, HPM_ALL);
}

#endif // #define RISCV_CSR_HPM_H
