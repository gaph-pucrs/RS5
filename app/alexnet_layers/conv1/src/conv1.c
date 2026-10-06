/*
 * AlexNet Conv Layer 1 — RS5 bare-metal port
 *
 * Input  : input_1.h   — in_1[IN_HEIGHT_1 * IN_WIDTH_1 * IN_DEPTH_1]      (compiled in)
 *          weights_1.h — weights_1[OUT_DEPTH_1*IN_DEPTH_1*FH*FW]          (compiled in)
 *          bias_1.h    — bias_1[OUT_DEPTH_1]                               (compiled in)
 *
 * Timing : csr_read_mcycle() — cycle counter
 *   - per output channel: conv + bias
 *   - total conv + bias
 *   - ReLU
 *   - MaxPool (3x3, stride 2)
 *   - total layer
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <riscv-csr.h>

#include "cnn_std.h"
#include "cnn_common.h"

#include "input_1.h"    /* in_1[IN_HEIGHT_1 * IN_WIDTH_1 * IN_DEPTH_1]                            */
#include "weights_1.h"  /* weights_1[OUT_DEPTH_1 * IN_DEPTH_1 * FILTER_HEIGHT_1 * FILTER_WIDTH_1] */
#include "bias_1.h"     /* bias_1[OUT_DEPTH_1]                                                     */

static uint32_t tick_ch_start[OUT_DEPTH_1];
static uint32_t tick_ch_end  [OUT_DEPTH_1];

static int out_conv[OUT_CONV_HEIGHT_1 * OUT_CONV_WIDTH_1 * OUT_DEPTH_1];
static int out_pool[OUT_HEIGHT_1      * OUT_WIDTH_1      * OUT_DEPTH_1];

int main(void)
{
    printf("Inicio conv1\n");
    /* ------------------------------------------------------------------ */
    /* Convolution + bias                                                   */
    /* ------------------------------------------------------------------ */
    uint32_t tick_total_start = csr_read_mcycle();

    for (int oc = 0; oc < OUT_DEPTH_1; oc++)
    {
        int *out_slice = &out_conv[oc * OUT_CONV_HEIGHT_1 * OUT_CONV_WIDTH_1];

        tick_ch_start[oc] = csr_read_mcycle();

        for (int ic = 0; ic < IN_DEPTH_1; ic++)
        {
            int *partial = conv_channel(
                weights_1, in_1, IN_DEPTH_1,
                oc, ic,
                FILTER_HEIGHT_1, FILTER_WIDTH_1,
                IN_HEIGHT_1, IN_WIDTH_1,
                OUT_CONV_HEIGHT_1, OUT_CONV_WIDTH_1,
                STRIDE_CONV_1);

            for (int j = 0; j < OUT_CONV_HEIGHT_1 * OUT_CONV_WIDTH_1; j++)
                out_slice[j] += partial[j];
            free(partial);
        }

        conv_sum_bias(OUT_CONV_HEIGHT_1, OUT_CONV_WIDTH_1, out_slice, bias_1, oc);

        tick_ch_end[oc] = csr_read_mcycle();
    }

    uint32_t tick_conv_end = csr_read_mcycle();

    /* ------------------------------------------------------------------ */
    /* ReLU                                                                 */
    /* ------------------------------------------------------------------ */
    uint32_t tick_relu_start = csr_read_mcycle();
    relu(out_conv, OUT_CONV_HEIGHT_1, OUT_CONV_WIDTH_1, OUT_DEPTH_1);
    uint32_t tick_relu_end = csr_read_mcycle();

    /* ------------------------------------------------------------------ */
    /* MaxPool                                                              */
    /* ------------------------------------------------------------------ */
    uint32_t tick_pool_start = csr_read_mcycle();
    maxpool(out_conv, out_pool,
            OUT_CONV_HEIGHT_1, OUT_CONV_WIDTH_1, OUT_DEPTH_1,
            OUT_HEIGHT_1,      OUT_WIDTH_1,      OUT_DEPTH_1,
            STRIDE_MAX_1, POOL_SIZE_1);
    uint32_t tick_pool_end = csr_read_mcycle();

    uint32_t tick_total_end = csr_read_mcycle();

    /* ------------------------------------------------------------------ */
    /* Timing report                                                        */
    /* ------------------------------------------------------------------ */
    printf("=== conv1 timing report ===\n\n");

    printf("Per-channel conv+bias  [(ch, cycles)]:\n[\n");
    for (int oc = 0; oc < OUT_DEPTH_1; oc++)
    {
        printf("  (%d, %u)", oc, (uint32_t)(tick_ch_end[oc] - tick_ch_start[oc]));
        if (oc + 1 != OUT_DEPTH_1) printf(",");
        printf("\n");
    }
    printf("]\n\n");

    printf("Total conv+bias : %u cycles\n", (uint32_t)(tick_conv_end   - tick_total_start));
    printf("ReLU            : %u cycles\n", (uint32_t)(tick_relu_end   - tick_relu_start));
    printf("MaxPool         : %u cycles\n", (uint32_t)(tick_pool_end   - tick_pool_start));
    printf("Total layer     : %u cycles\n\n", (uint32_t)(tick_total_end - tick_total_start));

    printf("Fim conv1\n");
    return 0;
}
