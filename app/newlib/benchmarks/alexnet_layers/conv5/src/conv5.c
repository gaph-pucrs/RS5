/*
 * AlexNet Conv Layer 5 — RS5 bare-metal port
 *
 * Input  : in_layer5.h — in_layer5[IN_DEPTH_5 * OUT_CONV_HEIGHT_4 * OUT_CONV_WIDTH_4] (compiled in)
 *          weights_5.h — weights_5[OUT_DEPTH_5*IN_DEPTH_5*FH*FW]                      (compiled in)
 *          bias_5.h    — bias_5[OUT_DEPTH_5]                                           (compiled in)
 *
 * Timing : csr_read_mcycle() — cycle counter
 *   - padding phase
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
#include <print_u64.h>

/* Read the full 64-bit cycle counter on RV32.
 * Retry if mcycleh increments between the two half-reads. */
static inline uint64_t read_cycle64(void) {
    uint32_t hi, lo, hi2;
    do {
        hi  = csr_read_mcycleh();
        lo  = (uint32_t)csr_read_mcycle();
        hi2 = csr_read_mcycleh();
    } while (hi != hi2);
    return ((uint64_t)hi << 32) | (uint64_t)lo;
}

#include "cnn_std.h"
#include "cnn_common.h"

#include "in_layer5.h"  /* in_layer5[IN_DEPTH_5 * OUT_CONV_HEIGHT_4 * OUT_CONV_WIDTH_4] */
#include "weights_5.h"  /* weights_5[OUT_DEPTH_5 * IN_DEPTH_5 * FH * FW]               */
#include "bias_5.h"     /* bias_5[OUT_DEPTH_5]                                          */

static uint64_t tick_ch_start[OUT_DEPTH_5];
static uint64_t tick_ch_end  [OUT_DEPTH_5];

static int in_5    [IN_DEPTH_5  * IN_HEIGHT_5       * IN_WIDTH_5      ];
static int out_conv[OUT_DEPTH_5 * OUT_CONV_HEIGHT_5 * OUT_CONV_WIDTH_5];
static int out_pool[OUT_DEPTH_5 * OUT_HEIGHT_5      * OUT_WIDTH_5     ];

int main(void)
{
    printf("Inicio conv5\n");
    fflush(stdout);

    /* ------------------------------------------------------------------ */
    /* Padding: 13x13 -> 15x15 per channel                                 */
    /* ------------------------------------------------------------------ */
    uint64_t tick_pad_start = read_cycle64();
    for (int ic = 0; ic < IN_DEPTH_5; ic++)
        pad((int *)&in_layer5[ic * OUT_CONV_HEIGHT_4 * OUT_CONV_WIDTH_4],
            &in_5[ic * IN_HEIGHT_5 * IN_WIDTH_5],
            OUT_CONV_HEIGHT_4, OUT_CONV_WIDTH_4, 1, PAD_IN_5);
    uint64_t tick_pad_end = read_cycle64();

    /* ------------------------------------------------------------------ */
    /* Convolution + bias                                                   */
    /* ------------------------------------------------------------------ */
    uint64_t tick_total_start = read_cycle64();

    for (int oc = 0; oc < OUT_DEPTH_5; oc++)
    {
        int *out_slice = &out_conv[oc * OUT_CONV_HEIGHT_5 * OUT_CONV_WIDTH_5];

        tick_ch_start[oc] = read_cycle64();

        for (int ic = 0; ic < IN_DEPTH_5; ic++)
        {
            int *partial = conv_channel(
                weights_5, in_5, IN_DEPTH_5,
                oc, ic,
                FILTER_HEIGHT_5, FILTER_WIDTH_5,
                IN_HEIGHT_5, IN_WIDTH_5,
                OUT_CONV_HEIGHT_5, OUT_CONV_WIDTH_5,
                STRIDE_CONV_5);

            for (int j = 0; j < OUT_CONV_HEIGHT_5 * OUT_CONV_WIDTH_5; j++)
                out_slice[j] += partial[j];
            free(partial);
        }

        conv_sum_bias(OUT_CONV_HEIGHT_5, OUT_CONV_WIDTH_5, out_slice, bias_5, oc);

        tick_ch_end[oc] = read_cycle64();
    }

    uint64_t tick_conv_end = read_cycle64();

    /* ------------------------------------------------------------------ */
    /* ReLU                                                                 */
    /* ------------------------------------------------------------------ */
    uint64_t tick_relu_start = read_cycle64();
    relu(out_conv, OUT_CONV_HEIGHT_5, OUT_CONV_WIDTH_5, OUT_DEPTH_5);
    uint64_t tick_relu_end = read_cycle64();

    /* ------------------------------------------------------------------ */
    /* MaxPool                                                              */
    /* ------------------------------------------------------------------ */
    uint64_t tick_pool_start = read_cycle64();
    maxpool(out_conv, out_pool,
            OUT_CONV_HEIGHT_5, OUT_CONV_WIDTH_5, OUT_DEPTH_5,
            OUT_HEIGHT_5,      OUT_WIDTH_5,      OUT_DEPTH_5,
            STRIDE_MAX_5, POOL_SIZE_5);
    uint64_t tick_pool_end = read_cycle64();

    uint64_t tick_total_end = read_cycle64();

    /* ------------------------------------------------------------------ */
    /* Timing report                                                        */
    /* ------------------------------------------------------------------ */
    printf("=== conv5 timing report ===\n\n");

    printf("Padding         : %s cycles\n\n", u64_str((uint64_t)(tick_pad_end - tick_pad_start)));

    printf("Per-channel conv+bias  [(ch, cycles)]:\n[\n");
    for (int oc = 0; oc < OUT_DEPTH_5; oc++)
    {
        printf("  (%d, %s)", oc, u64_str((uint64_t)(tick_ch_end[oc] - tick_ch_start[oc])));
        if (oc + 1 != OUT_DEPTH_5) printf(",");
        printf("\n");
    }
    printf("]\n\n");

    printf("Total conv+bias : %s cycles\n", u64_str((uint64_t)(tick_conv_end  - tick_total_start)));
    printf("ReLU            : %s cycles\n", u64_str((uint64_t)(tick_relu_end  - tick_relu_start)));
    printf("MaxPool         : %s cycles\n", u64_str((uint64_t)(tick_pool_end  - tick_pool_start)));
    printf("Total layer     : %s cycles\n\n", u64_str((uint64_t)(tick_total_end - tick_total_start)));

    printf("Fim conv5\n");
    return 0;
}
