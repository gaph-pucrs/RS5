#include "keccak.h"


void split_lane(uint64_t lane, uint32_t* even, uint32_t* odd){
    *even = 0;
    *odd =  0;
    for(int i = 0; i < 32; i++){
        *even |= ((lane >>  (i * 2))      & (0x1)) << i;
        *odd  |= ((lane >> ((i * 2) + 1)) & (0x1)) << i;
    }
}

uint64_t join_lane(uint32_t even, uint32_t odd){
    uint64_t lane = 0;
    for(int i = 0; i < 64; i++){
        if(i % 2 == 0){
            lane |= ((uint64_t)((even >>  (i / 2)) & 0x1)) << i;
        } else {
            lane |= ((uint64_t)((odd  >>  (i / 2)) & 0x1)) << i;
        }
    }
    return lane;
}

void rotl_lane(uint32_t* even, uint32_t* odd, int r){
    if(r%2 == 0){
        *even = ROTL32(*even,((r / 2 ) % 32));
        *odd =  ROTL32(*odd, ((r / 2 ) % 32));
    } else {
        *even = *odd  ^ *even;
        *odd  = *even ^ *odd;
        *even = *odd  ^ *even;
        *even = ROTL32(*even, (((r / 2) + 1 ) % 32));
        *odd  = ROTL32(*odd,   ((r / 2)       % 32));
    }
}

void to_istate(keccak_state st, keccak_istate ist){
    for(int i = 0; i < 25; i++){
        split_lane(st[i], &ist[i][0], &ist[i][1]);
    }
}

void from_istate(keccak_istate ist, keccak_state st){
    for(int i = 0; i < 25; i++){
        st[i] = join_lane(ist[i][0], ist[i][1]);
    }
}

void split_theta(keccak_istate st){
    uint32_t C[5][2], D[5][2];

    for (int x = 0; x < 5; x++){
        C[x][0] = st[LANE(x,0)][0] ^ st[LANE(x,1)][0] ^ st[LANE(x,2)][0] ^ st[LANE(x,3)][0] ^ st[LANE(x,4)][0];
        C[x][1] = st[LANE(x,0)][1] ^ st[LANE(x,1)][1] ^ st[LANE(x,2)][1] ^ st[LANE(x,3)][1] ^ st[LANE(x,4)][1];

    }

    //odd rotate case
    for (int i = 0; i < 5; i++){
        D[i][0] = C[(i + 4) % 5][0] ^ ROTL32(C[(i + 1) % 5][1], 1);
        D[i][1] = C[(i + 4) % 5][1] ^        C[(i + 1) % 5][0];
    }

    for(int8_t i = 0; i < 5; i++){
        st[LANE(i,0)][0] ^= D[i][0];
        st[LANE(i,0)][1] ^= D[i][1];
        st[LANE(i,1)][0] ^= D[i][0];
        st[LANE(i,1)][1] ^= D[i][1];
        st[LANE(i,2)][0] ^= D[i][0];
        st[LANE(i,2)][1] ^= D[i][1];
        st[LANE(i,3)][0] ^= D[i][0];
        st[LANE(i,3)][1] ^= D[i][1];
        st[LANE(i,4)][0] ^= D[i][0];
        st[LANE(i,4)][1] ^= D[i][1];
    }

}

void split_rho(keccak_istate st){
    for(int i = 0; i < 25; i ++){
        rotl_lane(&st[i][0], &st[i][1], RHO[i]);
    }
};

void split_pi(keccak_istate st){
    keccak_istate temp;
    memcpy(temp, st, sizeof(keccak_istate));

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            st[LANE(i, j)][0] = temp[LANE((i+3 * j) % 5, i)][0];
            st[LANE(i, j)][1] = temp[LANE((i+3 * j) % 5, i)][1];

        }
    }
    memset(temp, 0, sizeof(keccak_istate));
}

void split_chi(keccak_istate st){
    uint32_t old_row[5][2];
    for(int j = 0; j < 5; j++){
        for(int i = 0; i < 5; i++){
            old_row[i][0] = st[LANE(i,j)][0];
            old_row[i][1] = st[LANE(i,j)][1];

        }
        for(int i = 0; i < 5; i++){
            st[(LANE(i,j))][0] = old_row[i][0] ^ (~old_row[(i+1) % 5][0] & old_row[(i+2) % 5][0]);
            st[(LANE(i,j))][1] = old_row[i][1] ^ (~old_row[(i+1) % 5][1] & old_row[(i+2) % 5][1]);
        }
    }
};

static const uint32_t IOTA_I[24][2] = {
    {0x00000001U, 0x00000000U}, {0x00000000U, 0x00000089U}, {0x00000000U, 0x8000008BU}, {0x00000000U, 0x80008080U},
    {0x00000001U, 0x0000008BU}, {0x00000001U, 0x00008000U}, {0x00000001U, 0x80008088U}, {0x00000001U, 0x80000082U},
    {0x00000000U, 0x0000000BU}, {0x00000000U, 0x0000000AU}, {0x00000001U, 0x00008082U}, {0x00000000U, 0x00008003U},
    {0x00000001U, 0x0000808BU}, {0x00000001U, 0x8000000BU}, {0x00000001U, 0x8000008AU}, {0x00000001U, 0x80000081U},
    {0x00000000U, 0x80000081U}, {0x00000000U, 0x80000008U}, {0x00000000U, 0x00000083U}, {0x00000000U, 0x80008003U},
    {0x00000001U, 0x80008088U}, {0x00000000U, 0x80000088U}, {0x00000001U, 0x00008000U}, {0x00000000U, 0x80008082U},
};

void split_iota(keccak_istate st, size_t round){
    st[LANE(0,0)][0] = st[LANE(0,0)][0] ^ IOTA_I[round][0];
    st[LANE(0,0)][1] = st[LANE(0,0)][1] ^ IOTA_I[round][1];
};

void split_keccak_f(keccak_istate st, keccak_mode_e mode){
    for(size_t i = 0; i < PARAMS[mode].rounds; i++){
        split_theta(st);
        split_rho(st);
        split_pi(st);
        split_chi(st);
        split_iota(st, i);
    }
}

// XOR one rate-sized block into the state: build each 64-bit lane from
// 8 message bytes, then split it, since XOR commutes with the interleaving.
static void split_xor_block(keccak_istate st, uint8_t* block, size_t rate){
    for (size_t i = 0; i < rate / 8; i++){
        uint64_t lane = 0;
        for (int b = 0; b < 8; b++){
            lane |= (uint64_t)block[8 * i + b] << (8 * b);
        }
        uint32_t even, odd;
        split_lane(lane, &even, &odd);
        st[i][0] ^= even;
        st[i][1] ^= odd;
    }
}

// Same as absorb, but the last block (possibly empty) is padded in a byte
// buffer first, so every block goes through split_xor_block.
void split_absorb(keccak_istate st, keccak_mode_e mode, uint8_t* msg, size_t len){

    size_t rate = PARAMS[mode].rate;
    while (len >= rate){
        split_xor_block(st, msg, rate);
        split_keccak_f(st, mode);
        msg += rate;
        len -= rate;
    }
    uint8_t block[200] = {0};
    memcpy(block, msg, len);
    block[len] ^= PARAMS[mode].domain;
    block[rate - 1] ^= 0x80;
    split_xor_block(st, block, rate);
    memset(block, 0, sizeof(block));
}

// Same as squeeze, joining each lane back to 64 bits once, at its first byte.
void split_squeeze(keccak_istate st, keccak_mode_e mode, uint8_t* out, size_t outlen){

    size_t rate = PARAMS[mode].rate;
    uint64_t lane = 0;
    for (size_t i = 0; i < outlen; i++){
        if (i > 0 && i % rate == 0){
            split_keccak_f(st, mode);
        }
        size_t j = i % rate;
        if (j % 8 == 0){
            lane = join_lane(st[j/8][0], st[j/8][1]);
        }
        out[i] = (uint8_t)(lane >> (8 * (j % 8)));
    }
}

// Same contract as hash, on the interleaved state.
size_t split_hash(keccak_istate st, keccak_mode_e mode, uint8_t* msg, size_t len, uint8_t* out, size_t outlen){

    int is_shake = (mode == SHAKE128) || (mode == SHAKE256);
    if (!is_shake){
        outlen = (200 - PARAMS[mode].rate) / 2;
    }
    split_absorb(st, mode, msg, len);
    split_keccak_f(st, mode);
    split_squeeze(st, mode, out, outlen);
    if (!is_shake){
        memset(st, 0, sizeof(keccak_istate));
    }
    return outlen;
}
