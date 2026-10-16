#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#ifdef NO_RISCV
    // Host build: runs the scalar kernels natively and dumps every layer
    // output to DUMP_DIR/<layer>.bin (raw int32) for alexnet-utils/validate.py
    static inline uint64_t read_cycle64(void) { return 0; }
    #ifndef DUMP_DIR
        #define DUMP_DIR "dump"
    #endif
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
#endif

#include <print_u64.h>

// #define VECTOR

#include "./alexnet_common.h"
#include "./alexnet_params.h"

#include "./images.h"

typedef struct {
    uint64_t to;
    uint64_t tf;
    uint64_t lapsed;
} timing;

//{{{
static type out_conv1[CONV1_CHANNELS*CONV1_HEIGHT*CONV1_WIDTH];
static type out_pool1[CONV1_CHANNELS*POOL1_HEIGHT*POOL1_WIDTH];
static type out_conv2[CONV2_CHANNELS*CONV2_HEIGHT*CONV2_WIDTH];
static type out_pool2[CONV2_CHANNELS*POOL2_HEIGHT*POOL2_WIDTH];
static type out_conv3[CONV3_CHANNELS*CONV3_HEIGHT*CONV3_WIDTH];
static type out_conv4[CONV4_CHANNELS*CONV4_HEIGHT*CONV4_WIDTH];
static type out_conv5[CONV5_CHANNELS*CONV5_HEIGHT*CONV5_WIDTH];
static type out_pool5[FC6_IN];
static type out_fc6[FC6_OUT];
static type out_fc7[FC7_OUT];
static type out_fc8[FC8_OUT];
//}}}

enum { CONV1, POOL1, CONV2, POOL2, CONV3, CONV4, CONV5, POOL5, FC6, FC7, FC8, N_LAYERS };

static const struct {
    const char *name;
    const type *out;
    int size;
} layers[N_LAYERS] = {
    { "conv1", out_conv1, sizeof(out_conv1)/sizeof(type) },
    { "pool1", out_pool1, sizeof(out_pool1)/sizeof(type) },
    { "conv2", out_conv2, sizeof(out_conv2)/sizeof(type) },
    { "pool2", out_pool2, sizeof(out_pool2)/sizeof(type) },
    { "conv3", out_conv3, sizeof(out_conv3)/sizeof(type) },
    { "conv4", out_conv4, sizeof(out_conv4)/sizeof(type) },
    { "conv5", out_conv5, sizeof(out_conv5)/sizeof(type) },
    { "pool5", out_pool5, sizeof(out_pool5)/sizeof(type) },
    { "fc6",   out_fc6,   sizeof(out_fc6)/sizeof(type)   },
    { "fc7",   out_fc7,   sizeof(out_fc7)/sizeof(type)   },
    { "fc8",   out_fc8,   sizeof(out_fc8)/sizeof(type)   },
};

static timing layer_time[N_LAYERS];
static timing total_cycles;

#define RUN_LAYER(L, CALL)                                              \
    do {                                                                \
        layer_time[L].to = read_cycle64();                              \
            CALL;                                                       \
        layer_time[L].tf = read_cycle64();                              \
        layer_time[L].lapsed = layer_time[L].tf - layer_time[L].to;     \
    } while (0)

#define PRINT_DATA()                                                    \
    do {                                                                \
        printf("--- PIPELINE STATS ----\n");                            \
        printf("task,cycles\n");                                        \
        for (int i = 0; i < N_LAYERS; i++)                              \
            printf("%s,%s\n", layers[i].name, u64_str(layer_time[i].lapsed)); \
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

#ifdef NO_RISCV
static void dump_layers(void)
{
    char path[256];
    for (int i = 0; i < N_LAYERS; i++)
    {
        snprintf(path, sizeof(path), "%s/%s.bin", DUMP_DIR, layers[i].name);
        FILE *f = fopen(path, "wb");
        if (f == NULL)
        {
            perror(path);
            exit(1);
        }
        fwrite(layers[i].out, sizeof(type), layers[i].size, f);
        fclose(f);
    }
    printf("layer outputs dumped to %s/\n", DUMP_DIR);
}
#endif

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

    printf("Running AlexNet on image1... (vlen = %" PRIu32 ")\n", vlen);

    total_cycles.to = read_cycle64();

    RUN_LAYER(CONV1, conv     (&conv1_shape, &conv1_params, images[0], out_conv1));
#ifdef STOP_AFTER_CONV1
    // quick RTL check: compare against the native conv1 checksum
    uint32_t sum = 0;
    for (int i = 0; i < layers[CONV1].size; i++)
        sum += (uint32_t)out_conv1[i];
    printf("conv1 cycles: %s\n", u64_str(layer_time[CONV1].lapsed));
    printf("conv1,%" PRIu32 "\n", sum);
    return 0;
#endif
    RUN_LAYER(POOL1, maxpool  (&pool1_shape, out_conv1, out_pool1));
    RUN_LAYER(CONV2, conv     (&conv2_shape, &conv2_params, out_pool1, out_conv2));
    RUN_LAYER(POOL2, maxpool  (&pool2_shape, out_conv2, out_pool2));
    RUN_LAYER(CONV3, conv     (&conv3_shape, &conv3_params, out_pool2, out_conv3));
    RUN_LAYER(CONV4, conv     (&conv4_shape, &conv4_params, out_conv3, out_conv4));
    RUN_LAYER(CONV5, conv     (&conv5_shape, &conv5_params, out_conv4, out_conv5));
    RUN_LAYER(POOL5, maxpool  (&pool5_shape, out_conv5, out_pool5));
    RUN_LAYER(FC6,   fc_relu  (&fc6_shape, &fc6_params, out_pool5, out_fc6));
    RUN_LAYER(FC7,   fc_relu  (&fc7_shape, &fc7_params, out_fc6, out_fc7));
    RUN_LAYER(FC8,   fc       (&fc8_shape, &fc8_params, out_fc7, out_fc8));

    type argmax = out_fc8[0];
    int class = 0;
    for (int i = 0; i < FC8_OUT; i++)
    {
        if (argmax < out_fc8[i])
        {
            argmax = out_fc8[i];
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

#ifdef NO_RISCV
    dump_layers();
#endif

    return 0;
}
