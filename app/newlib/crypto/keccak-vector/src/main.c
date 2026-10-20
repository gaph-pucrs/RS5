#include "keccak.h"


int compare_istate(keccak_state ref, keccak_istate ist){
    keccak_state got;
    from_istate(ist, got);
    int fails = 0;
    for (int i = 0; i < 25; i++){
        if (got[i] != ref[i]){
            printf("FAIL lane %2d got=%08lx%08lx want=%08lx%08lx\n", i,
                   (unsigned long)(got[i] >> 32), (unsigned long)got[i],
                   (unsigned long)(ref[i] >> 32), (unsigned long)ref[i]);
            fails++;
        }
    }
    return fails;
}


int main (){

    keccak_state ref;
    keccak_istate ist;
    uint64_t x = 0x0123456789ABCDEFULL;
    for (int i = 0; i < 25; i++){
        x ^= x << 13; x ^= x >> 7; x ^= x << 17;   // xorshift64
        ref[i] = x;
    }
    to_istate(ref, ist);
 // Several permutations back to back, like a multi-block absorb
    int fails = 0;
    for (int p = 0; p < 4; p++){
        keccak_f(ref, SHA3_256);
        split_keccak_f(ist, SHA3_256);
        int f = compare_istate(ref, ist);
        if (f){
            printf("permutation %d: %d failing lanes\n", p, f);
            fails += f;
            break;
        }
    }
    printf("split_keccak_f test: %d failing lanes\n", fails);

    // Known answer: Keccak-f[1600] of the all-zero state, lane 0
    keccak_istate zero = {0};
    split_keccak_f(zero, SHA3_256);
    uint64_t lane0 = join_lane(zero[0][0], zero[0][1]);
    printf("zero-state lane 0: %08lx%08lx (expect f1258f7940e1dde7)\n",
           (unsigned long)(lane0 >> 32), (unsigned long)lane0);

    return 0;
}
