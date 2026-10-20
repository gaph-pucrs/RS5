#include "keccak.h"


// XOR every full rate block into the state and permute; the last block
// (possibly empty) gets the padding. The final permutation is left to the caller.
void absorb(keccak_state st,  keccak_mode_e mode, uint8_t* msg, size_t len){

    size_t rate = PARAMS[mode].rate;
    while (len >= rate){
        for (size_t i = 0; i < rate; i++){
            st[i/8] ^= ((uint64_t)msg[i] << ((i*8) % 64));
        }
        keccak_f(st, mode);
        msg += rate;
        len -= rate;
    }
    for (size_t i = 0; i < len; i++){
        st[i/8] ^= ((uint64_t)msg[i] << ((i*8) % 64));
    }
    st[len / 8] ^= (uint64_t)PARAMS[mode].domain << (8 * (len % 8));
    st[(rate - 1) / 8] ^= (uint64_t)0x80 << (8 * ((rate - 1) % 8));

}

void print(keccak_state st){
    for (int i = 0; i < 25; i++)
    printf("lane %2d: %08lx%08lx\n", i, (unsigned long)(st[i] >> 32), (unsigned long)st[i]);
};

void theta(keccak_state st){
    uint64_t C[5], D[5];
    for (int x = 0; x < 5; x++)
        C[x] = st[LANE(x,0)] ^ st[LANE(x,1)] ^ st[LANE(x,2)] ^ st[LANE(x,3)] ^ st[LANE(x,4)];

    for (int i = 0; i < 5; i++)
        D[i] = C[(i + 4) % 5] ^ ROTL64(C[(i + 1) % 5], 1);

    for(int8_t i = 0; i < 5; i++){
        st[LANE(i,0)] ^= D[i];
        st[LANE(i,1)] ^= D[i];
        st[LANE(i,2)] ^= D[i];
        st[LANE(i,3)] ^= D[i];
        st[LANE(i,4)] ^= D[i];
    }
}

void rho(keccak_state st){
    for(int i = 0; i < 25; i ++){
        st[i] = ROTL64(st[i], RHO[i]);
    }
};

void pi(keccak_state st){
    keccak_state temp;
    memcpy(temp, st, sizeof(keccak_state));

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            st[LANE(i, j)] = temp[LANE((i+3 * j) % 5, i)];
        }
    }
    memset(temp, 0, sizeof(keccak_state));
}

void chi(keccak_state st){
    uint64_t old_row[5];
    for(int j = 0; j < 5; j++){
        for(int i = 0; i < 5; i++){
            old_row[i] = st[LANE(i,j)];
        }
        for(int i = 0; i < 5; i++){
            st[(LANE(i,j))] = old_row[i] ^ (~old_row[(i+1) % 5] & old_row[(i+2) % 5]);
        }
    }
};

static const uint64_t IOTA[24] = {
    0x0000000000000001ULL, 0x0000000000008082ULL, 0x800000000000808AULL, 0x8000000080008000ULL,
    0x000000000000808BULL, 0x0000000080000001ULL, 0x8000000080008081ULL, 0x8000000000008009ULL,
    0x000000000000008AULL, 0x0000000000000088ULL, 0x0000000080008009ULL, 0x000000008000000AULL,
    0x000000008000808BULL, 0x800000000000008BULL, 0x8000000000008089ULL, 0x8000000000008003ULL,
    0x8000000000008002ULL, 0x8000000000000080ULL, 0x000000000000800AULL, 0x800000008000000AULL,
    0x8000000080008081ULL, 0x8000000000008080ULL, 0x0000000080000001ULL, 0x8000000080008008ULL
};

void iota(keccak_state st, size_t round){
    st[LANE(0,0)] = st[LANE(0,0)] ^ IOTA[round];
};

void keccak_f(keccak_state st, keccak_mode_e mode){
    for(size_t i = 0; i < PARAMS[mode].rounds; i++){
        theta(st);
        rho(st);
        pi(st);
        chi(st);
        iota(st, i);
    }
}

// Copy outlen bytes of output from the rate into out, permuting before
// each extra rate block (SHAKE outputs longer than the rate).
void squeeze(keccak_state st, keccak_mode_e mode, uint8_t* out, size_t outlen){

    size_t rate = PARAMS[mode].rate;
    for (size_t i = 0; i < outlen; i++){
        if (i > 0 && i % rate == 0){
            keccak_f(st, mode);
        }
        size_t j = i % rate;
        out[i] = (uint8_t)(st[j/8] >> (8 * (j % 8)));
    }
}

// SHA3: writes the (200 - rate) / 2 byte digest (outlen is ignored) and
// clears the state. SHAKE: writes outlen bytes and keeps the state, so more
// output can be squeezed (keccak_f then squeeze, after whole rate blocks).
// Returns the number of bytes written to out.
size_t hash(keccak_state st, keccak_mode_e mode, uint8_t* msg, size_t len, uint8_t* out, size_t outlen){

    int is_shake = (mode == SHAKE128) || (mode == SHAKE256);
    if (!is_shake){
        outlen = (200 - PARAMS[mode].rate) / 2;
    }
    absorb(st, mode, msg, len);
    keccak_f(st, mode);
    squeeze(st, mode, out, outlen);
    if (!is_shake){
        memset(st, 0, sizeof(keccak_state));
    }
    return outlen;
}

void print_bytes(uint8_t* b, size_t len){
    for (size_t i = 0; i < len; i++)
        printf("%02x", b[i]);
    printf("\n");
}
