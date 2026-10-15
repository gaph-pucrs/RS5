#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define LANE(x,y) ((x) + 5 * (y))
#define ROTL64(a, n) (((a) << (n)) | ((a) >> ((64 - (n)) % 64)))


typedef enum {
    SHA3_224,
    SHA3_256,
    SHA3_384,
    SHA3_512,
    SHAKE128,
    SHAKE256,
    KECCAK_MODE_COUNT
} keccak_mode_e;    

typedef struct {
    size_t rate;
    uint8_t domain;
    uint8_t rounds;
} keccak_params;

static const keccak_params PARAMS[KECCAK_MODE_COUNT] = {
    [SHA3_224] = {144, 0x06, 24},    // designated initializers: index by enum name
    [SHA3_256] = {136, 0x06, 24},
    [SHA3_384] = {104, 0x06, 24},
    [SHA3_512] = { 72, 0x06, 24},
    [SHAKE128] = {168, 0x1F, 24},
    [SHAKE256] = {136, 0x1F, 24},
};


typedef uint64_t keccak_state[25];

void absorb(keccak_state st,  keccak_mode_e mode, uint8_t* msg, size_t len){
    
    size_t absorb_limit = PARAMS[mode].rate;
    size_t i;
    for (i = 0; (i < len) && (i < absorb_limit); i++){
        st[i/8]^= ((uint64_t)msg[i] << ((i*8) % 64));
    }
    st[i / 8] ^= (uint64_t)PARAMS[mode].domain << (8 * (i % 8));
    st[(absorb_limit - 1) / 8] ^= (uint64_t)0x80 << (8 * ((absorb_limit - 1) % 8));

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


//amount of each rotate
static const uint8_t RHO[25] = {0,  1,  62, 28, 27, 
                                36, 44,  6, 55, 20,
                                3,  10, 43, 25, 39,
                                41, 45, 15, 21,  8,
                                18,  2, 61, 56, 14};


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


int main (){

    keccak_state state = {0};    

    char msg[] = {"mensagemginhainicial\n"};

    absorb(state, SHA3_512, msg, sizeof(msg));
    print(state);
    printf("==============\n");
    keccak_f(state, SHA3_512);
    print(state);
    printf("==============\n");
    return 0;
}
