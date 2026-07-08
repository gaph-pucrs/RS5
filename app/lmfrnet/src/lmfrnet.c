#include <stdio.h>
#include <stdint.h>

#include <riscv-csr.h>

// uint64_t csr_read_mcycle(void) { return 0; }

// #define VECTOR

#include "./lmfrnet_common.h"
#include "./lmfrnet_params.h"

#include "../dataset/image1.h"

typedef struct {
    uint64_t to;
    uint64_t tf;
    uint64_t lapsed;
} time;

static time stemBlock_time;
static time mfBlock_time[19];
static time tran_conv_time[5];
static time fc_time;
static uint64_t data[24] = {0};

#define PRINT_DATA()                                                \
    do {                                                            \
        printf("--- STATS ----\n");                                 \
        printf("task,cycles\n");                                    \
        printf("p1,%lu\n", stemBlock_time.lapsed);                  \
        for (int i = 1; i <= 18; i++)                               \
            printf("p%d,%lu\n", i+1, mfBlock_time[i].lapsed);       \
        for (int i = 1; i <= 4; i++)                                \
            printf("p%d,%lu\n", i+19, tran_conv_time[i].lapsed);    \
        printf("p24,%lu\n", fc_time.lapsed);                        \
    } while(0)

#define PRINT_PIPELINE()                                            \
    do {                                                            \
        printf("--- PIPELINE STATS ----\n");                        \
        printf("task,cycles\n");                                    \
        for (int i = 0; i < 24; i++)                                \
            printf("p%d,%lu\n", i+1, data[i]);                      \
    } while(0)

int main()
{
    uint32_t vlenb;
    __asm__ volatile("csrr %0, vlenb" : "=r"(vlenb));

    printf("Running LMFRNet on image1... (vlen = %d)\n", vlenb*8);

//{{{
    type out_stemBlock[32*32*32] = {0};

    type out_mf1[32*32*56] = {0};
    type out_mf2[32*32*80] = {0};
    type out_mf3[32*32*104] = {0};
    type out_tran1[32*32*104] = {0};
    type out_pool1[16*16*104] = {0};

    type out_mf4[16*16*128] = {0};
    type out_mf5[16*16*152] = {0};
    type out_mf6[16*16*176] = {0};
    type out_mf7[16*16*200] = {0};
    type out_tran2[16*16*200] = {0};
    type out_pool2[8*8*200] = {0};

    type out_mf8[8*8*224] = {0};
    type out_mf9[8*8*248] = {0};
    type out_mf10[8*8*272] = {0};
    type out_mf11[8*8*296] = {0};
    type out_mf12[8*8*320] = {0};
    type out_mf13[8*8*344] = {0};
    type out_mf14[8*8*368] = {0};
    type out_mf15[8*8*392] = {0};
    type out_tran3[8*8*392] = {0};
    type out_pool3[4*4*392] = {0};

    type out_mf16[4*4*416] = {0};
    type out_mf17[4*4*440] = {0};
    type out_mf18[4*4*464] = {0};
    type out_tran4[4*4*464] = {0};
    type out_gap[464] = {0};
    type out_fc[10] = {0};
//}}}

    stemBlock_time.to = csr_read_mcycle();
        stemBlock(&stemBlock_shape, &stemBlock_params, image1, out_stemBlock);
    stemBlock_time.tf = csr_read_mcycle();
    stemBlock_time.lapsed = stemBlock_time.tf - stemBlock_time.to;
    data[0] = stemBlock_time.lapsed;

    mfBlock_time[1].to = csr_read_mcycle();
        MFBlock(&MMCBlock1_mmLayer1_shapes, &MMCBlock1_mmLayer1_params, out_stemBlock, out_mf1);
    mfBlock_time[1].tf = csr_read_mcycle();
    mfBlock_time[1].lapsed = mfBlock_time[1].tf - mfBlock_time[1].to;
    data[1] = mfBlock_time[1].lapsed;

    mfBlock_time[2].to = csr_read_mcycle();
        MFBlock(&MMCBlock1_mmLayer2_shapes, &MMCBlock1_mmLayer2_params, out_mf1, out_mf2);
    mfBlock_time[2].tf = csr_read_mcycle();
    mfBlock_time[2].lapsed = mfBlock_time[2].tf - mfBlock_time[2].to;
    data[2] = mfBlock_time[2].lapsed;

    mfBlock_time[3].to = csr_read_mcycle();
        MFBlock(&MMCBlock1_mmLayer3_shapes, &MMCBlock1_mmLayer3_params, out_mf2, out_mf3);
    mfBlock_time[3].tf = csr_read_mcycle();
    mfBlock_time[3].lapsed = mfBlock_time[3].tf - mfBlock_time[3].to;
    data[3] = mfBlock_time[3].lapsed;

    tran_conv_time[1].to = csr_read_mcycle();
        tran_conv(&tran_ConvNormRelu1_shape, &tran_ConvNormRelu1_params, out_mf3, out_tran1);
        avg_pool(&pool1_shape, out_tran1, out_pool1);
    tran_conv_time[1].tf = csr_read_mcycle();
    tran_conv_time[1].lapsed = tran_conv_time[1].tf - tran_conv_time[1].to;
    data[4] = tran_conv_time[1].lapsed;

    mfBlock_time[4].to = csr_read_mcycle();
        MFBlock(&MMCBlock2_mmLayer1_shapes, &MMCBlock2_mmLayer1_params, out_pool1, out_mf4);
    mfBlock_time[4].tf = csr_read_mcycle();
    mfBlock_time[4].lapsed = mfBlock_time[4].tf - mfBlock_time[4].to;
    data[5] = mfBlock_time[4].lapsed;

    mfBlock_time[5].to = csr_read_mcycle();
        MFBlock(&MMCBlock2_mmLayer2_shapes, &MMCBlock2_mmLayer2_params, out_mf4, out_mf5);
    mfBlock_time[5].tf = csr_read_mcycle();
    mfBlock_time[5].lapsed = mfBlock_time[5].tf - mfBlock_time[5].to;
    data[6] = mfBlock_time[5].lapsed;

    mfBlock_time[6].to = csr_read_mcycle();
        MFBlock(&MMCBlock2_mmLayer3_shapes, &MMCBlock2_mmLayer3_params, out_mf5, out_mf6);
    mfBlock_time[6].tf = csr_read_mcycle();
    mfBlock_time[6].lapsed = mfBlock_time[6].tf - mfBlock_time[6].to;
    data[7] = mfBlock_time[6].lapsed;

    mfBlock_time[7].to = csr_read_mcycle();
        MFBlock(&MMCBlock2_mmLayer4_shapes, &MMCBlock2_mmLayer4_params, out_mf6, out_mf7);
    mfBlock_time[7].tf = csr_read_mcycle();
    mfBlock_time[7].lapsed = mfBlock_time[7].tf - mfBlock_time[7].to;
    data[8] = mfBlock_time[7].lapsed;

    tran_conv_time[2].to = csr_read_mcycle();
        tran_conv(&tran_ConvNormRelu2_shape, &tran_ConvNormRelu2_params, out_mf7, out_tran2);
        avg_pool(&pool2_shape, out_tran2, out_pool2);
    tran_conv_time[2].tf = csr_read_mcycle();
    tran_conv_time[2].lapsed = tran_conv_time[2].tf - tran_conv_time[2].to;
    data[9] = tran_conv_time[2].lapsed;

    mfBlock_time[8].to = csr_read_mcycle();
        MFBlock(&MMCBlock3_mmLayer1_shapes, &MMCBlock3_mmLayer1_params, out_pool2, out_mf8);
    mfBlock_time[8].tf = csr_read_mcycle();
    mfBlock_time[8].lapsed = mfBlock_time[8].tf - mfBlock_time[8].to;
    data[10] = mfBlock_time[8].lapsed;

    mfBlock_time[9].to = csr_read_mcycle();
        MFBlock(&MMCBlock3_mmLayer2_shapes, &MMCBlock3_mmLayer2_params, out_mf8, out_mf9);
    mfBlock_time[9].tf = csr_read_mcycle();
    mfBlock_time[9].lapsed = mfBlock_time[9].tf - mfBlock_time[9].to;
    data[11] = mfBlock_time[9].lapsed;

    mfBlock_time[10].to = csr_read_mcycle();
        MFBlock(&MMCBlock3_mmLayer3_shapes, &MMCBlock3_mmLayer3_params, out_mf9, out_mf10);
    mfBlock_time[10].tf = csr_read_mcycle();
    mfBlock_time[10].lapsed = mfBlock_time[10].tf - mfBlock_time[10].to;
    data[12] = mfBlock_time[10].lapsed;

    mfBlock_time[11].to = csr_read_mcycle();
        MFBlock(&MMCBlock3_mmLayer4_shapes, &MMCBlock3_mmLayer4_params, out_mf10, out_mf11);
    mfBlock_time[11].tf = csr_read_mcycle();
    mfBlock_time[11].lapsed = mfBlock_time[11].tf - mfBlock_time[11].to;
    data[13] = mfBlock_time[11].lapsed;

    mfBlock_time[12].to = csr_read_mcycle();
        MFBlock(&MMCBlock3_mmLayer5_shapes, &MMCBlock3_mmLayer5_params, out_mf11, out_mf12);
    mfBlock_time[12].tf = csr_read_mcycle();
    mfBlock_time[12].lapsed = mfBlock_time[12].tf - mfBlock_time[12].to;
    data[14] = mfBlock_time[12].lapsed;

    mfBlock_time[13].to = csr_read_mcycle();
        MFBlock(&MMCBlock3_mmLayer6_shapes, &MMCBlock3_mmLayer6_params, out_mf12, out_mf13);
    mfBlock_time[13].tf = csr_read_mcycle();
    mfBlock_time[13].lapsed = mfBlock_time[13].tf - mfBlock_time[13].to;
    data[15] = mfBlock_time[13].lapsed;

    mfBlock_time[14].to = csr_read_mcycle();
        MFBlock(&MMCBlock3_mmLayer7_shapes, &MMCBlock3_mmLayer7_params, out_mf13, out_mf14);
    mfBlock_time[14].tf = csr_read_mcycle();
    mfBlock_time[14].lapsed = mfBlock_time[14].tf - mfBlock_time[14].to;
    data[16] = mfBlock_time[14].lapsed;

    mfBlock_time[15].to = csr_read_mcycle();
        MFBlock(&MMCBlock3_mmLayer8_shapes, &MMCBlock3_mmLayer8_params, out_mf14, out_mf15);
    mfBlock_time[15].tf = csr_read_mcycle();
    mfBlock_time[15].lapsed = mfBlock_time[15].tf - mfBlock_time[15].to;
    data[17] = mfBlock_time[15].lapsed;

    tran_conv_time[3].to = csr_read_mcycle();
        tran_conv(&tran_ConvNormRelu3_shape, &tran_ConvNormRelu3_params, out_mf15, out_tran3);
        avg_pool(&pool3_shape, out_tran3, out_pool3);
    tran_conv_time[3].tf = csr_read_mcycle();
    tran_conv_time[3].lapsed = tran_conv_time[3].tf - tran_conv_time[3].to;
    data[18] = tran_conv_time[3].lapsed;

    mfBlock_time[16].to = csr_read_mcycle();
        MFBlock(&MMCBlock4_mmLayer1_shapes, &MMCBlock4_mmLayer1_params, out_pool3, out_mf16);
    mfBlock_time[16].tf = csr_read_mcycle();
    mfBlock_time[16].lapsed = mfBlock_time[16].tf - mfBlock_time[16].to;
    data[19] = mfBlock_time[16].lapsed;

    mfBlock_time[17].to = csr_read_mcycle();
        MFBlock(&MMCBlock4_mmLayer2_shapes, &MMCBlock4_mmLayer2_params, out_mf16, out_mf17);
    mfBlock_time[17].tf = csr_read_mcycle();
    mfBlock_time[17].lapsed = mfBlock_time[17].tf - mfBlock_time[17].to;
    data[20] = mfBlock_time[17].lapsed;

    mfBlock_time[18].to = csr_read_mcycle();
        MFBlock(&MMCBlock4_mmLayer3_shapes, &MMCBlock4_mmLayer3_params, out_mf17, out_mf18);
    mfBlock_time[18].tf = csr_read_mcycle();
    mfBlock_time[18].lapsed = mfBlock_time[18].tf - mfBlock_time[18].to;
    data[21] = mfBlock_time[18].lapsed;

    tran_conv_time[4].to = csr_read_mcycle();
        tran_conv(&tran_ConvNormRelu4_shape, &tran_ConvNormRelu4_params, out_mf18, out_tran4);
        gap(&gap_shape, out_tran4, out_gap);
    tran_conv_time[4].tf = csr_read_mcycle();
    tran_conv_time[4].lapsed = tran_conv_time[4].tf - tran_conv_time[4].to;
    data[22] = tran_conv_time[4].lapsed;

    fc_time.to = csr_read_mcycle();
        fc(&fc_shape, &fc_params, out_gap, out_fc);
    fc_time.tf = csr_read_mcycle();
    fc_time.lapsed = fc_time.tf - fc_time.to;
    data[23] = fc_time.lapsed;

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

    printf("predicted class: %d (val = %d)\n", class, argmax);

    PRINT_DATA();
    PRINT_PIPELINE();

    return 0;
}