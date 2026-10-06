/*
 * AlexNet Conv Layer 3 — RS5 bare-metal port
 *
 * Input  : in_layer3.h — in_layer3[IN_DEPTH_3 * OUT_HEIGHT_2 * OUT_WIDTH_2] (compiled in)
 *          weights_3.h — weights_3[OUT_DEPTH_3*IN_DEPTH_3*FH*FW]            (compiled in)
 *          bias_3.h    — bias_3[OUT_DEPTH_3]                                 (compiled in)
 *
 * No MaxPool after Conv3 in AlexNet.
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

#include "in_layer3.h"  /* in_layer3[IN_DEPTH_3 * OUT_HEIGHT_2 * OUT_WIDTH_2] */
#include "weights_3.h"  /* weights_3[OUT_DEPTH_3 * IN_DEPTH_3 * FH * FW]      */
#include "bias_3.h"     /* bias_3[OUT_DEPTH_3]                                 */

static uint64_t tick_ch_start[OUT_DEPTH_3];
static uint64_t tick_ch_end  [OUT_DEPTH_3];

static int in_3    [IN_DEPTH_3  * IN_HEIGHT_3       * IN_WIDTH_3      ];
static int out_conv[OUT_DEPTH_3 * OUT_CONV_HEIGHT_3 * OUT_CONV_WIDTH_3];

int main(void)
{
    printf("Inicio conv3\n");
    fflush(stdout);

    /* ------------------------------------------------------------------ */
    /* Padding: 13x13 -> 15x15 per channel                                 */
    /* ------------------------------------------------------------------ */
    uint64_t tick_pad_start = read_cycle64();
    for (int ic = 0; ic < IN_DEPTH_3; ic++)
        pad((int *)&in_layer3[ic * OUT_HEIGHT_2 * OUT_WIDTH_2],
            &in_3[ic * IN_HEIGHT_3 * IN_WIDTH_3],
            OUT_HEIGHT_2, OUT_WIDTH_2, 1, PAD_IN_3);
    uint64_t tick_pad_end = read_cycle64();

    /* ------------------------------------------------------------------ */
    /* Convolution + bias                                                   */
    /* ------------------------------------------------------------------ */
    uint64_t tick_total_start = read_cycle64();

    for (int oc = 0; oc < OUT_DEPTH_3; oc++)
    {
        int *out_slice = &out_conv[oc * OUT_CONV_HEIGHT_3 * OUT_CONV_WIDTH_3];

        tick_ch_start[oc] = read_cycle64();

        for (int ic = 0; ic < IN_DEPTH_3; ic++)
        {
            int *partial = conv_channel(
                weights_3, in_3, IN_DEPTH_3,
                oc, ic,
                FILTER_HEIGHT_3, FILTER_WIDTH_3,
                IN_HEIGHT_3, IN_WIDTH_3,
                OUT_CONV_HEIGHT_3, OUT_CONV_WIDTH_3,
                STRIDE_CONV_3);

            for (int j = 0; j < OUT_CONV_HEIGHT_3 * OUT_CONV_WIDTH_3; j++)
                out_slice[j] += partial[j];
            free(partial);
        }

        conv_sum_bias(OUT_CONV_HEIGHT_3, OUT_CONV_WIDTH_3, out_slice, bias_3, oc);

        tick_ch_end[oc] = read_cycle64();
    }

    uint64_t tick_conv_end = read_cycle64();

    /* ------------------------------------------------------------------ */
    /* ReLU (no MaxPool after Conv3 in AlexNet)                            */
    /* ------------------------------------------------------------------ */
    uint64_t tick_relu_start = read_cycle64();
    relu(out_conv, OUT_CONV_HEIGHT_3, OUT_CONV_WIDTH_3, OUT_DEPTH_3);
    uint64_t tick_relu_end = read_cycle64();

    uint64_t tick_total_end = read_cycle64();

    /* ------------------------------------------------------------------ */
    /* Timing report                                                        */
    /* ------------------------------------------------------------------ */
    printf("=== conv3 timing report ===\n\n");

    printf("Padding         : %s cycles\n\n", u64_str((uint64_t)(tick_pad_end - tick_pad_start)));

    printf("Per-channel conv+bias  [(ch, cycles)]:\n[\n");
    for (int oc = 0; oc < OUT_DEPTH_3; oc++)
    {
        printf("  (%d, %s)", oc, u64_str((uint64_t)(tick_ch_end[oc] - tick_ch_start[oc])));
        if (oc + 1 != OUT_DEPTH_3) printf(",");
        printf("\n");
    }
    printf("]\n\n");

    printf("Total conv+bias : %s cycles\n", u64_str((uint64_t)(tick_conv_end  - tick_total_start)));
    printf("ReLU            : %s cycles\n", u64_str((uint64_t)(tick_relu_end  - tick_relu_start)));
    printf("Total layer     : %s cycles\n\n", u64_str((uint64_t)(tick_total_end - tick_total_start)));

    printf("Fim conv3\n");
    return 0;
}
