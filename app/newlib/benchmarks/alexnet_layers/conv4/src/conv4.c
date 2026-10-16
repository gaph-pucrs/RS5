/*
 * AlexNet Conv Layer 4 — RS5 bare-metal port
 *
 * Input  : in_layer4.h — in_layer4[IN_DEPTH_4 * OUT_CONV_HEIGHT_3 * OUT_CONV_WIDTH_3] (compiled in)
 *          weights_4.h — weights_4[OUT_DEPTH_4*IN_DEPTH_4*FH*FW]                      (compiled in)
 *          bias_4.h    — bias_4[OUT_DEPTH_4]                                           (compiled in)
 *
 * No MaxPool after Conv4 in AlexNet.
 *
 * Timing : csr_read_mcycle() — cycle counter
 *   - padding phase
 *   - per output channel: conv + bias
 *   - total conv + bias
 *   - ReLU
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

#include "in_layer4.h"  /* in_layer4[IN_DEPTH_4 * OUT_CONV_HEIGHT_3 * OUT_CONV_WIDTH_3] */
#include "weights_4.h"  /* weights_4[OUT_DEPTH_4 * IN_DEPTH_4 * FH * FW]               */
#include "bias_4.h"     /* bias_4[OUT_DEPTH_4]                                          */

static uint64_t tick_ch_start[OUT_DEPTH_4];
static uint64_t tick_ch_end  [OUT_DEPTH_4];

static int in_4    [IN_DEPTH_4  * IN_HEIGHT_4       * IN_WIDTH_4      ];
static int out_conv[OUT_DEPTH_4 * OUT_CONV_HEIGHT_4 * OUT_CONV_WIDTH_4];

int main(void)
{
    printf("Inicio conv4\n");
    fflush(stdout);

    /* ------------------------------------------------------------------ */
    /* Padding: 13x13 -> 15x15 per channel                                 */
    /* ------------------------------------------------------------------ */
    uint64_t tick_pad_start = read_cycle64();
    for (int ic = 0; ic < IN_DEPTH_4; ic++)
        pad((int *)&in_layer4[ic * OUT_CONV_HEIGHT_3 * OUT_CONV_WIDTH_3],
            &in_4[ic * IN_HEIGHT_4 * IN_WIDTH_4],
            OUT_CONV_HEIGHT_3, OUT_CONV_WIDTH_3, 1, PAD_IN_4);
    uint64_t tick_pad_end = read_cycle64();

    /* ------------------------------------------------------------------ */
    /* Convolution + bias                                                   */
    /* ------------------------------------------------------------------ */
    uint64_t tick_total_start = read_cycle64();

    for (int oc = 0; oc < OUT_DEPTH_4; oc++)
    {
        int *out_slice = &out_conv[oc * OUT_CONV_HEIGHT_4 * OUT_CONV_WIDTH_4];

        tick_ch_start[oc] = read_cycle64();

        for (int ic = 0; ic < IN_DEPTH_4; ic++)
        {
            int *partial = conv_channel(
                weights_4, in_4, IN_DEPTH_4,
                oc, ic,
                FILTER_HEIGHT_4, FILTER_WIDTH_4,
                IN_HEIGHT_4, IN_WIDTH_4,
                OUT_CONV_HEIGHT_4, OUT_CONV_WIDTH_4,
                STRIDE_CONV_4);

            for (int j = 0; j < OUT_CONV_HEIGHT_4 * OUT_CONV_WIDTH_4; j++)
                out_slice[j] += partial[j];
            free(partial);
        }

        conv_sum_bias(OUT_CONV_HEIGHT_4, OUT_CONV_WIDTH_4, out_slice, bias_4, oc);

        tick_ch_end[oc] = read_cycle64();
    }

    uint64_t tick_conv_end = read_cycle64();

    /* ------------------------------------------------------------------ */
    /* ReLU (no MaxPool after Conv4 in AlexNet)                            */
    /* ------------------------------------------------------------------ */
    uint64_t tick_relu_start = read_cycle64();
    relu(out_conv, OUT_CONV_HEIGHT_4, OUT_CONV_WIDTH_4, OUT_DEPTH_4);
    uint64_t tick_relu_end = read_cycle64();

    uint64_t tick_total_end = read_cycle64();

    /* ------------------------------------------------------------------ */
    /* Timing report                                                        */
    /* ------------------------------------------------------------------ */
    printf("=== conv4 timing report ===\n\n");

    printf("Padding         : %s cycles\n\n", u64_str((uint64_t)(tick_pad_end - tick_pad_start)));

    printf("Per-channel conv+bias  [(ch, cycles)]:\n[\n");
    for (int oc = 0; oc < OUT_DEPTH_4; oc++)
    {
        printf("  (%d, %s)", oc, u64_str((uint64_t)(tick_ch_end[oc] - tick_ch_start[oc])));
        if (oc + 1 != OUT_DEPTH_4) printf(",");
        printf("\n");
    }
    printf("]\n\n");

    printf("Total conv+bias : %s cycles\n", u64_str((uint64_t)(tick_conv_end  - tick_total_start)));
    printf("ReLU            : %s cycles\n", u64_str((uint64_t)(tick_relu_end  - tick_relu_start)));
    printf("Total layer     : %s cycles\n\n", u64_str((uint64_t)(tick_total_end - tick_total_start)));

    printf("Fim conv4\n");
    return 0;
}
