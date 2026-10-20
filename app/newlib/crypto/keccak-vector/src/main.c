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

    // split_hash must match hash for every mode, around the block boundaries,
    // with SHAKE squeezing more than one rate block
    uint8_t msg[400];
    for (int i = 0; i < 400; i++){
        msg[i] = (uint8_t)(i * 7 + 3);
    }
    int hash_fails = 0, cases = 0;
    for (int m = 0; m < KECCAK_MODE_COUNT; m++){
        size_t rate = PARAMS[m].rate;
        size_t lens[] = {0, 1, rate - 1, rate, rate + 1, 2 * rate + 5};
        for (int k = 0; k < 6; k++){
            keccak_state st = {0};
            keccak_istate ist = {0};
            uint8_t want[200], got[200];
            size_t n  = hash(st, m, msg, lens[k], want, sizeof(want));
            size_t n2 = split_hash(ist, m, msg, lens[k], got, sizeof(got));
            cases++;
            if (n != n2 || memcmp(want, got, n) != 0){
                printf("FAIL mode %d len %d\n", m, (int)lens[k]);
                hash_fails++;
            }
        }
    }
    printf("split_hash test: %d failures in %d cases\n", hash_fails, cases);

    uint8_t out[64];
    keccak_istate hst = {0};
    size_t n = split_hash(hst, SHA3_256, (uint8_t*)"abc", 3, out, sizeof(out));
    printf("split SHA3-256(\"abc\"): ");
    print_bytes(out, n);
    printf("expect                3a985da74fe225b2045c172d6bd390bd855f086e3e9d525b46bfe24511431532\n");
    return 0;
}
