#ifndef KECCAK_H
#define KECCAK_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define LANE(x,y) ((x) + 5 * (y))
#define ROTL64(a, n) (((a) << (n)) | ((a) >> ((64 - (n)) % 64)))

#define ROTL32(a, n) (((a) << (n)) | ((a) >> ((32 - (n)) % 32)))


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

//amount of each rotate
static const uint8_t RHO[25] = {0,  1,  62, 28, 27,
                                36, 44,  6, 55, 20,
                                3,  10, 43, 25, 39,
                                41, 45, 15, 21,  8,
                                18,  2, 61, 56, 14};


typedef uint64_t keccak_state[25];
typedef uint32_t keccak_istate[25][2];


// keccak.c: standard version, one uint64_t per lane
void absorb(keccak_state st,  keccak_mode_e mode, uint8_t* msg, size_t len);
void print(keccak_state st);
void theta(keccak_state st);
void rho(keccak_state st);
void pi(keccak_state st);
void chi(keccak_state st);
void iota(keccak_state st, size_t round);
void keccak_f(keccak_state st, keccak_mode_e mode);
void squeeze(keccak_state st, keccak_mode_e mode, uint8_t* out, size_t outlen);
size_t hash(keccak_state st, keccak_mode_e mode, uint8_t* msg, size_t len, uint8_t* out, size_t outlen);
void print_bytes(uint8_t* b, size_t len);

// keccak_split.c: bit-interleaved version, even/odd uint32_t words per lane
void split_lane(uint64_t lane, uint32_t* even, uint32_t* odd);
uint64_t join_lane(uint32_t even, uint32_t odd);
void rotl_lane(uint32_t* even, uint32_t* odd, int r);
void to_istate(keccak_state st, keccak_istate ist);
void from_istate(keccak_istate ist, keccak_state st);
void split_theta(keccak_istate st);
void split_rho(keccak_istate st);
void split_pi(keccak_istate st);
void split_chi(keccak_istate st);
void split_iota(keccak_istate st, size_t round);
void split_keccak_f(keccak_istate st, keccak_mode_e mode);

#endif
