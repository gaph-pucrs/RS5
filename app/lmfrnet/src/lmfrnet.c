#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#ifdef NO_RISCV
    // Host build: runs the scalar kernels natively, to compare the checksums
    // of an RTL run against
    static inline uint64_t read_cycle64(void) { return 0; }
    static inline uint32_t read_mul(void) { return 0; }
    static inline uint32_t read_vmac(void) { return 0; }
#else
    #include <riscv-csr.h>

    // full 64-bit cycle counter on RV32, retrying if mcycleh changes between the reads
    static inline uint64_t read_cycle64(void) {
        uint32_t hi, lo, hi2;
        do {
            hi  = csr_read_mcycleh();
            lo  = (uint32_t)csr_read_mcycle();
            hi2 = csr_read_mcycleh();
        } while (hi != hi2);
        return ((uint64_t)hi << 32) | (uint64_t)lo;
    }

    // retired scalar mul and vector multiply-add (vmacc, vnmsac, vmadd, vnmsub)
    // instructions: 32-bit counters, mhpmcounter22h/27h are always 0
    static inline uint32_t read_mul(void) {
        uint32_t v;
        __asm__ volatile("csrr %0, mhpmcounter22" : "=r"(v));
        return v;
    }

    static inline uint32_t read_vmac(void) {
        uint32_t v;
        __asm__ volatile("csrr %0, mhpmcounter27" : "=r"(v));
        return v;
    }
#endif

#include <print_u64.h>

// #define VECTOR

#include "./lmfrnet_common.h"
#include "./lmfrnet_params.h"

#include "./images.h"

typedef struct {
    uint64_t to;
    uint64_t tf;
    uint64_t lapsed;
} timing;

//{{{
static type out_stemBlock[32*32*32];

static type out_mf1[32*32*56];
static type out_mf2[32*32*80];
static type out_mf3[32*32*104];
static type out_tran1[32*32*104];
static type out_pool1[16*16*104];

static type out_mf4[16*16*128];
static type out_mf5[16*16*152];
static type out_mf6[16*16*176];
static type out_mf7[16*16*200];
static type out_tran2[16*16*200];
static type out_pool2[8*8*200];

static type out_mf8[8*8*224];
static type out_mf9[8*8*248];
static type out_mf10[8*8*272];
static type out_mf11[8*8*296];
static type out_mf12[8*8*320];
static type out_mf13[8*8*344];
static type out_mf14[8*8*368];
static type out_mf15[8*8*392];
static type out_tran3[8*8*392];
static type out_pool3[4*4*392];

static type out_mf16[4*4*416];
static type out_mf17[4*4*440];
static type out_mf18[4*4*464];
static type out_tran4[4*4*464];
static type out_gap[464];
static type out_fc[10];
//}}}

enum {
    STEM,
    MF1, MF2, MF3, TRAN1,
    MF4, MF5, MF6, MF7, TRAN2,
    MF8, MF9, MF10, MF11, MF12, MF13, MF14, MF15, TRAN3,
    MF16, MF17, MF18, TRAN4,
    FC,
    N_LAYERS
};

// tranN rows time the transition conv and the pooling after it: out is the pooled output
static const struct {
    const char *name;
    const type *out;
    int size;
} layers[N_LAYERS] = {
    { "stem",  out_stemBlock, sizeof(out_stemBlock)/sizeof(type) },
    { "mf1",   out_mf1,       sizeof(out_mf1)/sizeof(type)       },
    { "mf2",   out_mf2,       sizeof(out_mf2)/sizeof(type)       },
    { "mf3",   out_mf3,       sizeof(out_mf3)/sizeof(type)       },
    { "tran1", out_pool1,     sizeof(out_pool1)/sizeof(type)     },
    { "mf4",   out_mf4,       sizeof(out_mf4)/sizeof(type)       },
    { "mf5",   out_mf5,       sizeof(out_mf5)/sizeof(type)       },
    { "mf6",   out_mf6,       sizeof(out_mf6)/sizeof(type)       },
    { "mf7",   out_mf7,       sizeof(out_mf7)/sizeof(type)       },
    { "tran2", out_pool2,     sizeof(out_pool2)/sizeof(type)     },
    { "mf8",   out_mf8,       sizeof(out_mf8)/sizeof(type)       },
    { "mf9",   out_mf9,       sizeof(out_mf9)/sizeof(type)       },
    { "mf10",  out_mf10,      sizeof(out_mf10)/sizeof(type)      },
    { "mf11",  out_mf11,      sizeof(out_mf11)/sizeof(type)      },
    { "mf12",  out_mf12,      sizeof(out_mf12)/sizeof(type)      },
    { "mf13",  out_mf13,      sizeof(out_mf13)/sizeof(type)      },
    { "mf14",  out_mf14,      sizeof(out_mf14)/sizeof(type)      },
    { "mf15",  out_mf15,      sizeof(out_mf15)/sizeof(type)      },
    { "tran3", out_pool3,     sizeof(out_pool3)/sizeof(type)     },
    { "mf16",  out_mf16,      sizeof(out_mf16)/sizeof(type)      },
    { "mf17",  out_mf17,      sizeof(out_mf17)/sizeof(type)      },
    { "mf18",  out_mf18,      sizeof(out_mf18)/sizeof(type)      },
    { "tran4", out_gap,       sizeof(out_gap)/sizeof(type)       },
    { "fc",    out_fc,        sizeof(out_fc)/sizeof(type)        },
};

static timing layer_time[N_LAYERS];
static timing total_cycles;
static uint32_t layer_mul[N_LAYERS];
static uint32_t layer_vmac[N_LAYERS];

#define RUN_LAYER(L, CALL)                                              \
    do {                                                                \
        uint32_t _mul  = read_mul();                                    \
        uint32_t _vmac = read_vmac();                                   \
        layer_time[L].to = read_cycle64();                              \
            CALL;                                                       \
        layer_time[L].tf = read_cycle64();                              \
        layer_mul[L]  = read_mul()  - _mul;                             \
        layer_vmac[L] = read_vmac() - _vmac;                            \
        layer_time[L].lapsed = layer_time[L].tf - layer_time[L].to;     \
    } while (0)

#define PRINT_DATA()                                                    \
    do {                                                                \
        printf("--- PIPELINE STATS ----\n");                            \
        printf("task,cycles,mul,vmac\n");                               \
        for (int i = 0; i < N_LAYERS; i++)                              \
            printf("%s,%s,%" PRIu32 ",%" PRIu32 "\n", layers[i].name,   \
                   u64_str(layer_time[i].lapsed), layer_mul[i], layer_vmac[i]); \
    } while(0)

// wrapping sum of a layer's outputs, to compare RTL runs against the native one
#define PRINT_CHECKSUMS()                                               \
    do {                                                                \
        printf("--- CHECKSUMS ----\n");                                 \
        printf("layer,checksum\n");                                     \
        for (int i = 0; i < N_LAYERS; i++) {                            \
            uint32_t _sum = 0;                                          \
            for (int _j = 0; _j < layers[i].size; _j++)                 \
                _sum += (uint32_t)layers[i].out[_j];                    \
            printf("%s,%" PRIu32 "\n", layers[i].name, _sum);           \
        }                                                               \
    } while(0)

// KERNEL here too: GCC would auto-vectorize the argmax/checksum loops, and the
// vector build should only run the hand-written RVV code
KERNEL
int main()
{
    uint32_t vlen = 0;
#ifdef VECTOR
    __asm__ volatile("csrr %0, vlenb" : "=r"(vlen));
    vlen *= 8;
#endif

    printf("Running LMFRNet on image1... (vlen = %" PRIu32 ")\n", vlen);

    total_cycles.to = read_cycle64();

    // the tranN rows run two calls: joined with the comma operator so they stay one macro argument
    RUN_LAYER(STEM,  stemBlock (&stemBlock_shape, &stemBlock_params, images[0], out_stemBlock));

    RUN_LAYER(MF1,   MFBlock   (&MMCBlock1_mmLayer1_shapes, &MMCBlock1_mmLayer1_params, out_stemBlock, out_mf1));
    RUN_LAYER(MF2,   MFBlock   (&MMCBlock1_mmLayer2_shapes, &MMCBlock1_mmLayer2_params, out_mf1, out_mf2));
    RUN_LAYER(MF3,   MFBlock   (&MMCBlock1_mmLayer3_shapes, &MMCBlock1_mmLayer3_params, out_mf2, out_mf3));
    RUN_LAYER(TRAN1, (tran_conv(&tran_ConvNormRelu1_shape, &tran_ConvNormRelu1_params, out_mf3, out_tran1),
                      avg_pool (&pool1_shape, out_tran1, out_pool1)));

    RUN_LAYER(MF4,   MFBlock   (&MMCBlock2_mmLayer1_shapes, &MMCBlock2_mmLayer1_params, out_pool1, out_mf4));
    RUN_LAYER(MF5,   MFBlock   (&MMCBlock2_mmLayer2_shapes, &MMCBlock2_mmLayer2_params, out_mf4, out_mf5));
    RUN_LAYER(MF6,   MFBlock   (&MMCBlock2_mmLayer3_shapes, &MMCBlock2_mmLayer3_params, out_mf5, out_mf6));
    RUN_LAYER(MF7,   MFBlock   (&MMCBlock2_mmLayer4_shapes, &MMCBlock2_mmLayer4_params, out_mf6, out_mf7));
    RUN_LAYER(TRAN2, (tran_conv(&tran_ConvNormRelu2_shape, &tran_ConvNormRelu2_params, out_mf7, out_tran2),
                      avg_pool (&pool2_shape, out_tran2, out_pool2)));

    RUN_LAYER(MF8,   MFBlock   (&MMCBlock3_mmLayer1_shapes, &MMCBlock3_mmLayer1_params, out_pool2, out_mf8));
    RUN_LAYER(MF9,   MFBlock   (&MMCBlock3_mmLayer2_shapes, &MMCBlock3_mmLayer2_params, out_mf8, out_mf9));
    RUN_LAYER(MF10,  MFBlock   (&MMCBlock3_mmLayer3_shapes, &MMCBlock3_mmLayer3_params, out_mf9, out_mf10));
    RUN_LAYER(MF11,  MFBlock   (&MMCBlock3_mmLayer4_shapes, &MMCBlock3_mmLayer4_params, out_mf10, out_mf11));
    RUN_LAYER(MF12,  MFBlock   (&MMCBlock3_mmLayer5_shapes, &MMCBlock3_mmLayer5_params, out_mf11, out_mf12));
    RUN_LAYER(MF13,  MFBlock   (&MMCBlock3_mmLayer6_shapes, &MMCBlock3_mmLayer6_params, out_mf12, out_mf13));
    RUN_LAYER(MF14,  MFBlock   (&MMCBlock3_mmLayer7_shapes, &MMCBlock3_mmLayer7_params, out_mf13, out_mf14));
    RUN_LAYER(MF15,  MFBlock   (&MMCBlock3_mmLayer8_shapes, &MMCBlock3_mmLayer8_params, out_mf14, out_mf15));
    RUN_LAYER(TRAN3, (tran_conv(&tran_ConvNormRelu3_shape, &tran_ConvNormRelu3_params, out_mf15, out_tran3),
                      avg_pool (&pool3_shape, out_tran3, out_pool3)));

    RUN_LAYER(MF16,  MFBlock   (&MMCBlock4_mmLayer1_shapes, &MMCBlock4_mmLayer1_params, out_pool3, out_mf16));
    RUN_LAYER(MF17,  MFBlock   (&MMCBlock4_mmLayer2_shapes, &MMCBlock4_mmLayer2_params, out_mf16, out_mf17));
    RUN_LAYER(MF18,  MFBlock   (&MMCBlock4_mmLayer3_shapes, &MMCBlock4_mmLayer3_params, out_mf17, out_mf18));
    RUN_LAYER(TRAN4, (tran_conv(&tran_ConvNormRelu4_shape, &tran_ConvNormRelu4_params, out_mf18, out_tran4),
                      gap      (&gap_shape, out_tran4, out_gap)));

    RUN_LAYER(FC,    fc        (&fc_shape, &fc_params, out_gap, out_fc));

    type argmax = out_fc[0];
    int class = 0;
    for (int i = 0; i < 10; i++)
    {
        if (argmax < out_fc[i])
        {
            argmax = out_fc[i];
            class = i;
        }
    }

    total_cycles.tf = read_cycle64();
    total_cycles.lapsed = total_cycles.tf - total_cycles.to;

    printf("predicted class: %d (val = %d)\n", class, argmax);

#ifndef NO_RISCV
    printf("total_cycles: %s\n", u64_str(total_cycles.lapsed));

    PRINT_DATA();
#endif

    PRINT_CHECKSUMS();

    return 0;
}
