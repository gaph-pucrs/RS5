#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "test_rvkat.h"

#define KYBER_Q 3329

int test_cbd();
int test_arith();
int test_compress();

int test_cbd() {

    int fail_count_cbd2 = 0;
    int fail_count_cbd3 = 0;

    for (int i = 0; i < (1 << 8) - 1; i+=10) {

        printf("kybercbd2 i = 0x%x\n", i);

        int asm_val, asm_coeff_low, asm_coeff_high;
        __asm__("kybercbd2 %0, %1" :  "=r"(asm_val) : "r"(i));

        asm_coeff_low = asm_val & 0x0000FFFF;
        asm_coeff_high = (asm_val & 0xFFFF0000) >> 16;

        int ref_coeff_low, ref_coeff_high;

        ref_coeff_low = ((i & 1) + ((i & 2) >> 1)) - (((i & 4) >> 2) + ((i & 8) >> 3));
        ref_coeff_low = (ref_coeff_low < 0) ? ref_coeff_low + KYBER_Q : ref_coeff_low;

        ref_coeff_high = (((i & 16) >> 4) + ((i & 32) >> 5)) - (((i & 64) >> 6) + ((i & 128) >> 7));
        ref_coeff_high = (ref_coeff_high < 0) ? ref_coeff_high + KYBER_Q : ref_coeff_high;

        fail_count_cbd2 += rvkat_chku32("kybercbd2_coeff_low ", ref_coeff_low, asm_coeff_low);
        fail_count_cbd2 += rvkat_chku32("kybercbd2_coeff_high", ref_coeff_high, asm_coeff_high);
    }

    for (int i = 0; i < (1 << 12) - 1; i+=100) {

        printf("kybercbd3 i = 0x%x\n", i);

        int asm_val, asm_coeff_low, asm_coeff_high;
        __asm__("kybercbd3 %0, %1" :  "=r"(asm_val) : "r"(i));

        asm_coeff_low = asm_val & 0x0000FFFF;
        asm_coeff_high = (asm_val & 0xFFFF0000) >> 16;

        int ref_coeff_low, ref_coeff_high;

        ref_coeff_low = ((i & 1) + ((i & 2) >> 1) + ((i & 4) >> 2)) -
                        (((i & 8) >> 3) + ((i & 16) >> 4) + ((i & 32) >> 5));
        ref_coeff_low = (ref_coeff_low < 0) ? ref_coeff_low + KYBER_Q : ref_coeff_low;

        ref_coeff_high = (((i & 64) >> 6) + ((i & 128) >> 7) + ((i & 256) >> 8)) -
                         (((i & 512) >> 9) + ((i & 1024) >> 10) + ((i & 2048) >> 11));
        ref_coeff_high = (ref_coeff_high < 0) ? ref_coeff_high + KYBER_Q : ref_coeff_high;

        fail_count_cbd3 += rvkat_chku32("kybercbd3_coeff_low ", ref_coeff_low, asm_coeff_low);
        fail_count_cbd3 += rvkat_chku32("kybercbd3_coeff_high", ref_coeff_high, asm_coeff_high);
    }

    printf("\n");
    printf("test_cbd() cbd2 fail count: %d\n", fail_count_cbd2);
    printf("test_cbd() cbd3 fail count: %d\n\n", fail_count_cbd3);

    return fail_count_cbd2 + fail_count_cbd3;
}

int test_arith() {

    int fail_count_add = 0;
    int fail_count_sub = 0;
    int fail_count_mul = 0;

    for (int coeff = 1; coeff < KYBER_Q; coeff+= 100) {

        printf("kyberadd coeffs = 0x%x | 0x%x\n", coeff, coeff+1);

        int asm_val, asm_coeff_high, asm_coeff_low;

        __asm__("kyberadd %0, %1, %2" :  "=r"(asm_val)
                : "r"(coeff | (coeff << 16)),
                  "r"(coeff | ((coeff+1) << 16)));

        asm_coeff_low = (asm_val & 0x0000FFFF);
        asm_coeff_high = (asm_val >> 16);

        int ref_coeff_low = (coeff + coeff) % KYBER_Q;
        int ref_coeff_high = (coeff + coeff + 1) % KYBER_Q;

        fail_count_add += rvkat_chku32("kyberadd_coeff_low", ref_coeff_low, asm_coeff_low);
        fail_count_add += rvkat_chku32("kyberadd_coeff_high", ref_coeff_high, asm_coeff_high);
    }

    for (int coeff = 1; coeff < KYBER_Q; coeff+= 100) {

        printf("kybersub coeffs = 0x%x\n", coeff);

        int asm_val, asm_coeff_high, asm_coeff_low;

        __asm__("kybersub %0, %1, %2" :  "=r"(asm_val)
                : "r"(1500 | (1500 << 16)),
                  "r"(coeff | ((coeff+1) << 16)));

        asm_coeff_low = (asm_val & 0x0000FFFF);
        asm_coeff_high = (asm_val >> 16);

        int ref_coeff_low = (1500 - coeff);
        ref_coeff_low = (ref_coeff_low < 0) ? ref_coeff_low + KYBER_Q : ref_coeff_low;

        int ref_coeff_high = (1500 - (coeff+1));
        ref_coeff_high = (ref_coeff_high < 0) ? ref_coeff_high + KYBER_Q : ref_coeff_high;

        fail_count_sub += rvkat_chku32("kybersub_coeff_low ", ref_coeff_low, asm_coeff_low);
        fail_count_sub += rvkat_chku32("kybersub_coeff_high", ref_coeff_high, asm_coeff_high);
    }

    for (int coeff = 1; coeff < KYBER_Q; coeff+= 100) {

        printf("kybermul coeff = 0x%x\n", coeff);

        int asm_val;
        __asm__("kybermul %0, %1, %2" :  "=r"(asm_val) : "r"(coeff), "r"(coeff));

        int ref_val = (coeff * coeff) % KYBER_Q;

        fail_count_mul += rvkat_chku32("kybermul_coeff", ref_val, asm_val);
    }

    printf("\n");
    printf("test_arith() add fail count: %d\n", fail_count_add);
    printf("test_arith() sub fail count: %d\n", fail_count_sub);
    printf("test_arith() mul fail count: %d\n\n", fail_count_mul);

    return fail_count_add + fail_count_sub + fail_count_mul;
}

int test_compress() {

    int fail_count = 0;
    int compress_d[5] = {1, 4, 5, 10, 11};

    for (int i = 0; i < 5; i++)
        for (int coeff = 0; coeff < KYBER_Q; coeff+=100) {

            printf("kybercompress d = %d | coeff = 0x%x\n", compress_d[i], coeff);

            int asm_val;
            __asm__("kybercompress %0, %1, %2"
                    : "=r"(asm_val)
                    : "r"(coeff), "r"(compress_d[i]));

            int ref_val = (((coeff << compress_d[i]) + KYBER_Q/2)/KYBER_Q)
                          & ((1 << compress_d[i]) - 1);

            fail_count += rvkat_chku32("kybercompress_coeff", ref_val, asm_val);
        }

    return fail_count;
}

int main() {

    int test_cbd_fail_count      = 0; 
    int test_arith_fail_count    = 0;
    int test_compress_fail_count = 0;

    //test_cbd_fail_count = test_cbd();
    test_arith_fail_count = test_arith();
    //test_compress_fail_count = test_compress();

    printf("\n");
    //printf("test_cbd() fail count: %d\n", test_cbd_fail_count);
    printf("test_arith() fail count: %d\n", test_arith_fail_count);
    //printf("test_compress() fail count: %d\n", test_compress_fail_count);

    return test_cbd_fail_count + test_arith_fail_count + test_compress_fail_count;
}