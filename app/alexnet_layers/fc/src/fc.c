/*
 * AlexNet Fully Connected Layers (FC6, FC7, FC8) — RS5 bare-metal port
 *
 * Input  : in_fc6.h      — in_fc6[FC6_IN_SIZE]  (9216, flattened conv5 maxpool)  (compiled in)
 *          weights_fc6.h — weights_fc6[FC6_OUT_SIZE * FC6_IN_SIZE]                (compiled in)
 *          bias_fc6.h    — bias_fc6[FC6_OUT_SIZE]                                 (compiled in)
 *          weights_fc7.h — weights_fc7[FC7_OUT_SIZE * FC7_IN_SIZE]                (compiled in)
 *          bias_fc7.h    — bias_fc7[FC7_OUT_SIZE]                                 (compiled in)
 *          weights_fc8.h — weights_fc8[FC8_OUT_SIZE * FC8_IN_SIZE]                (compiled in)
 *          bias_fc8.h    — bias_fc8[FC8_OUT_SIZE]                                 (compiled in)
 *
 * Timing : read_cycle64() — 64-bit cycle counter
 *   - FC6: matmul + bias + ReLU
 *   - FC7: matmul + bias + ReLU
 *   - FC8: matmul + bias (no ReLU — softmax is applied at host level)
 *   - total layer
 *
 * NOTE: The weight matrices are large; ensure MEM_SIZE in the Makefile is
 *       sufficient (default 512 MiB covers all three layers).
 */

#include <stdio.h>
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

#include "in_fc6.h"      /* in_fc6[FC6_IN_SIZE]                          */
#include "weights_fc6.h" /* weights_fc6[FC6_OUT_SIZE * FC6_IN_SIZE]      */
#include "bias_fc6.h"    /* bias_fc6[FC6_OUT_SIZE]                       */
#include "weights_fc7.h" /* weights_fc7[FC7_OUT_SIZE * FC7_IN_SIZE]      */
#include "bias_fc7.h"    /* bias_fc7[FC7_OUT_SIZE]                       */
#include "weights_fc8.h" /* weights_fc8[FC8_OUT_SIZE * FC8_IN_SIZE]      */
#include "bias_fc8.h"    /* bias_fc8[FC8_OUT_SIZE]                       */

static int fc6_out[FC6_OUT_SIZE];
static int fc7_out[FC7_OUT_SIZE];
static int fc8_out[FC8_OUT_SIZE];

int main(void)
{
    printf("Inicio fc\n");
    fflush(stdout);

    uint64_t tick_total_start = read_cycle64();

    /* ------------------------------------------------------------------ */
    /* FC6: 9216 -> 4096                                                   */
    /* ------------------------------------------------------------------ */
    uint64_t tick_fc6_start = read_cycle64();
    fc_layer(weights_fc6, (const int *)in_fc6, bias_fc6,
             fc6_out, FC6_IN_SIZE, FC6_OUT_SIZE);
    uint64_t tick_fc6_matmul_end = read_cycle64();

    relu(fc6_out, FC6_OUT_SIZE, 1, 1);
    uint64_t tick_fc6_end = read_cycle64();

    /* ------------------------------------------------------------------ */
    /* FC7: 4096 -> 4096                                                   */
    /* ------------------------------------------------------------------ */
    uint64_t tick_fc7_start = read_cycle64();
    fc_layer(weights_fc7, fc6_out, bias_fc7,
             fc7_out, FC7_IN_SIZE, FC7_OUT_SIZE);
    uint64_t tick_fc7_matmul_end = read_cycle64();

    relu(fc7_out, FC7_OUT_SIZE, 1, 1);
    uint64_t tick_fc7_end = read_cycle64();

    /* ------------------------------------------------------------------ */
    /* FC8: 4096 -> 1000 (no ReLU — softmax applied at inference host)    */
    /* ------------------------------------------------------------------ */
    uint64_t tick_fc8_start = read_cycle64();
    fc_layer(weights_fc8, fc7_out, bias_fc8,
             fc8_out, FC8_IN_SIZE, FC8_OUT_SIZE);
    uint64_t tick_fc8_end = read_cycle64();

    uint64_t tick_total_end = read_cycle64();

    /* ------------------------------------------------------------------ */
    /* Timing report                                                        */
    /* ------------------------------------------------------------------ */
    printf("=== fc timing report ===\n\n");

    printf("FC6 matmul+bias : %s cycles\n",
           u64_str((uint64_t)(tick_fc6_matmul_end - tick_fc6_start)));
    printf("FC6 ReLU        : %s cycles\n",
           u64_str((uint64_t)(tick_fc6_end        - tick_fc6_matmul_end)));
    printf("FC6 total       : %s cycles\n\n",
           u64_str((uint64_t)(tick_fc6_end        - tick_fc6_start)));

    printf("FC7 matmul+bias : %s cycles\n",
           u64_str((uint64_t)(tick_fc7_matmul_end - tick_fc7_start)));
    printf("FC7 ReLU        : %s cycles\n",
           u64_str((uint64_t)(tick_fc7_end        - tick_fc7_matmul_end)));
    printf("FC7 total       : %s cycles\n\n",
           u64_str((uint64_t)(tick_fc7_end        - tick_fc7_start)));

    printf("FC8 matmul+bias : %s cycles\n",
           u64_str((uint64_t)(tick_fc8_end        - tick_fc8_start)));
    printf("FC8 total       : %s cycles\n\n",
           u64_str((uint64_t)(tick_fc8_end        - tick_fc8_start)));

    printf("Total fc layers : %s cycles\n\n",
           u64_str((uint64_t)(tick_total_end - tick_total_start)));

    /* Print top-5 class indices (argmax) */
    printf("Output logits (first 10): [");
    for (int i = 0; i < 10; i++) {
        printf("%d", fc8_out[i]);
        if (i + 1 < 10) printf(", ");
    }
    printf(", ...]\n\n");

    printf("Fim fc\n");
    return 0;
}
