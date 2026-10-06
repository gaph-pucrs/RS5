/*
 * AlexNet — full network (conv1..conv5, fc6..fc8) in a single RS5 bare-metal application
 *
 * Kernels and data are shared with app/alexnet_layers (same code and data as the
 * Memphis cnn5 experiments):
 *   ../alexnet_layers/include  — cnn_std.h, cnn_common.h
 *   ../alexnet_layers/data     — input_1.h, weights_N.h, bias_N.h, *_fc*.h
 *
 * Timing : read_cycle64() — 64-bit cycle counter.
 *   Every phase of every layer is timestamped during the run, and nothing is
 *   printed until the whole network has finished, so the report does not affect
 *   the measured cycles.
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

#include "input_1.h"     /* in_1[IN_DEPTH_1 * IN_HEIGHT_1 * IN_WIDTH_1]   */
#include "weights_1.h"
#include "bias_1.h"
#include "weights_2.h"
#include "bias_2.h"
#include "weights_3.h"
#include "bias_3.h"
#include "weights_4.h"
#include "bias_4.h"
#include "weights_5.h"
#include "bias_5.h"
#include "weights_fc6.h"
#include "bias_fc6.h"
#include "weights_fc7.h"
#include "bias_fc7.h"
#include "weights_fc8.h"
#include "bias_fc8.h"

/* ---------------------------------------------------------------------- */
/* Buffers                                                                  */
/* ---------------------------------------------------------------------- */
static int conv_1[OUT_DEPTH_1 * OUT_CONV_HEIGHT_1 * OUT_CONV_WIDTH_1];
static int pool_1[OUT_DEPTH_1 * OUT_HEIGHT_1      * OUT_WIDTH_1     ];

static int in_2  [IN_DEPTH_2  * IN_HEIGHT_2       * IN_WIDTH_2      ];
static int conv_2[OUT_DEPTH_2 * OUT_CONV_HEIGHT_2 * OUT_CONV_WIDTH_2];
static int pool_2[OUT_DEPTH_2 * OUT_HEIGHT_2      * OUT_WIDTH_2     ];

static int in_3  [IN_DEPTH_3  * IN_HEIGHT_3       * IN_WIDTH_3      ];
static int conv_3[OUT_DEPTH_3 * OUT_CONV_HEIGHT_3 * OUT_CONV_WIDTH_3];

static int in_4  [IN_DEPTH_4  * IN_HEIGHT_4       * IN_WIDTH_4      ];
static int conv_4[OUT_DEPTH_4 * OUT_CONV_HEIGHT_4 * OUT_CONV_WIDTH_4];

static int in_5  [IN_DEPTH_5  * IN_HEIGHT_5       * IN_WIDTH_5      ];
static int conv_5[OUT_DEPTH_5 * OUT_CONV_HEIGHT_5 * OUT_CONV_WIDTH_5];
static int pool_5[OUT_DEPTH_5 * OUT_HEIGHT_5      * OUT_WIDTH_5     ];

static int fc6_out[FC6_OUT_SIZE];
static int fc7_out[FC7_OUT_SIZE];
static int fc8_out[FC8_OUT_SIZE];

/* ---------------------------------------------------------------------- */
/* Timestamps (printed only at the end)                                     */
/* ---------------------------------------------------------------------- */
enum { CONV1, CONV2, CONV3, CONV4, CONV5, FC6, FC7, FC8, N_LAYERS };

static const char *layer_name[N_LAYERS] = {
    "conv1", "conv2", "conv3", "conv4", "conv5", "fc6", "fc7", "fc8"
};

typedef struct {
    uint64_t start;      /* layer start (before padding)    */
    uint64_t pad;        /* padding done                    */
    uint64_t compute;    /* conv+bias / matmul+bias done    */
    uint64_t relu;       /* ReLU done                       */
    uint64_t end;        /* layer end (after maxpool)       */
} layer_ticks_t;

static layer_ticks_t ticks[N_LAYERS];

/* ---------------------------------------------------------------------- */
/* Layer helpers                                                            */
/* ---------------------------------------------------------------------- */

/* Pad every channel of in[depth][h][w] by p into out[depth][h+2p][w+2p] */
static void pad_layer(const int *in, int *out, unsigned depth, unsigned h, unsigned w, unsigned p)
{
    for (unsigned c = 0; c < depth; c++)
        pad((int *)&in[c * h * w], &out[c * (h + 2 * p) * (w + 2 * p)], h, w, 1, p);
}

/* Convolution + bias for all output channels (same loop as alexnet_layers) */
static void conv_layer(const int *weights, const int *in, const int *bias, int *out,
                       unsigned in_depth, unsigned out_depth, unsigned k,
                       unsigned in_h, unsigned in_w, unsigned out_h, unsigned out_w,
                       unsigned stride)
{
    for (unsigned oc = 0; oc < out_depth; oc++)
    {
        int *out_slice = &out[oc * out_h * out_w];

        for (unsigned ic = 0; ic < in_depth; ic++)
        {
            int *partial = conv_channel(weights, in, in_depth, oc, ic, k, k,
                                        in_h, in_w, out_h, out_w, stride);

            for (unsigned j = 0; j < out_h * out_w; j++)
                out_slice[j] += partial[j];
            free(partial);
        }

        conv_sum_bias(out_h, out_w, out_slice, bias, oc);
    }
}

/* ---------------------------------------------------------------------- */
/* Report                                                                   */
/* ---------------------------------------------------------------------- */
static void print_row(const char *label, uint64_t cycles)
{
    printf("  %-16s: %s cycles\n", label, u64_str(cycles));
}

static void print_report(uint64_t total_start, uint64_t total_end)
{
    printf("=== AlexNet timing report ===\n\n");

    for (int l = CONV1; l <= CONV5; l++)
    {
        layer_ticks_t *t = &ticks[l];
        printf("%s\n", layer_name[l]);
        if (l != CONV1)
            print_row("Padding", t->pad - t->start);
        print_row("Conv+bias", t->compute - t->pad);
        print_row("ReLU", t->relu - t->compute);
        if (l == CONV1 || l == CONV2 || l == CONV5)
            print_row("MaxPool", t->end - t->relu);
        print_row("Total", t->end - t->start);
        printf("\n");
    }

    for (int l = FC6; l <= FC8; l++)
    {
        layer_ticks_t *t = &ticks[l];
        printf("%s\n", layer_name[l]);
        print_row("Matmul+bias", t->compute - t->start);
        if (l != FC8)
            print_row("ReLU", t->relu - t->compute);
        print_row("Total", t->end - t->start);
        printf("\n");
    }

    printf("Summary [(layer, cycles)]:\n[\n");
    for (int l = 0; l < N_LAYERS; l++)
    {
        printf("  (%s, %s)", layer_name[l], u64_str(ticks[l].end - ticks[l].start));
        if (l + 1 != N_LAYERS) printf(",");
        printf("\n");
    }
    printf("]\n\n");

    printf("Total AlexNet   : %s cycles\n\n", u64_str(total_end - total_start));

    /* Classification result */
    int best = 0;
    for (int i = 1; i < FC8_OUT_SIZE; i++)
        if (fc8_out[i] > fc8_out[best])
            best = i;

    printf("Output logits (first 10): [");
    for (int i = 0; i < 10; i++)
    {
        printf("%d", fc8_out[i]);
        if (i + 1 < 10) printf(", ");
    }
    printf(", ...]\n");
    printf("Predicted class : %d (logit %d)\n\n", best, fc8_out[best]);
}

/* ---------------------------------------------------------------------- */
/* Main                                                                     */
/* ---------------------------------------------------------------------- */
int main(void)
{
    printf("Inicio alexnet_full\n");
    fflush(stdout);

    uint64_t total_start = read_cycle64();

    /* conv1: 3x227x227 -> conv 64x55x55 -> pool 64x27x27 (no padding) */
    ticks[CONV1].start = ticks[CONV1].pad = read_cycle64();
    conv_layer(weights_1, in_1, bias_1, conv_1, IN_DEPTH_1, OUT_DEPTH_1, FILTER_HEIGHT_1,
               IN_HEIGHT_1, IN_WIDTH_1, OUT_CONV_HEIGHT_1, OUT_CONV_WIDTH_1, STRIDE_CONV_1);
    ticks[CONV1].compute = read_cycle64();
    relu(conv_1, OUT_CONV_HEIGHT_1, OUT_CONV_WIDTH_1, OUT_DEPTH_1);
    ticks[CONV1].relu = read_cycle64();
    maxpool(conv_1, pool_1,
            OUT_CONV_HEIGHT_1, OUT_CONV_WIDTH_1, OUT_DEPTH_1,
            OUT_HEIGHT_1,      OUT_WIDTH_1,      OUT_DEPTH_1,
            STRIDE_MAX_1, POOL_SIZE_1);
    ticks[CONV1].end = read_cycle64();

    /* conv2: pad 27->31 -> conv 192x27x27 -> pool 192x13x13 */
    ticks[CONV2].start = read_cycle64();
    pad_layer(pool_1, in_2, IN_DEPTH_2, OUT_HEIGHT_1, OUT_WIDTH_1, PAD_IN_2);
    ticks[CONV2].pad = read_cycle64();
    conv_layer(weights_2, in_2, bias_2, conv_2, IN_DEPTH_2, OUT_DEPTH_2, FILTER_HEIGHT_2,
               IN_HEIGHT_2, IN_WIDTH_2, OUT_CONV_HEIGHT_2, OUT_CONV_WIDTH_2, STRIDE_CONV_2);
    ticks[CONV2].compute = read_cycle64();
    relu(conv_2, OUT_CONV_HEIGHT_2, OUT_CONV_WIDTH_2, OUT_DEPTH_2);
    ticks[CONV2].relu = read_cycle64();
    maxpool(conv_2, pool_2,
            OUT_CONV_HEIGHT_2, OUT_CONV_WIDTH_2, OUT_DEPTH_2,
            OUT_HEIGHT_2,      OUT_WIDTH_2,      OUT_DEPTH_2,
            STRIDE_MAX_2, POOL_SIZE_2);
    ticks[CONV2].end = read_cycle64();

    /* conv3: pad 13->15 -> conv 384x13x13 (no pool) */
    ticks[CONV3].start = read_cycle64();
    pad_layer(pool_2, in_3, IN_DEPTH_3, OUT_HEIGHT_2, OUT_WIDTH_2, PAD_IN_3);
    ticks[CONV3].pad = read_cycle64();
    conv_layer(weights_3, in_3, bias_3, conv_3, IN_DEPTH_3, OUT_DEPTH_3, FILTER_HEIGHT_3,
               IN_HEIGHT_3, IN_WIDTH_3, OUT_CONV_HEIGHT_3, OUT_CONV_WIDTH_3, STRIDE_CONV_3);
    ticks[CONV3].compute = read_cycle64();
    relu(conv_3, OUT_CONV_HEIGHT_3, OUT_CONV_WIDTH_3, OUT_DEPTH_3);
    ticks[CONV3].relu = ticks[CONV3].end = read_cycle64();

    /* conv4: pad 13->15 -> conv 256x13x13 (no pool) */
    ticks[CONV4].start = read_cycle64();
    pad_layer(conv_3, in_4, IN_DEPTH_4, OUT_CONV_HEIGHT_3, OUT_CONV_WIDTH_3, PAD_IN_4);
    ticks[CONV4].pad = read_cycle64();
    conv_layer(weights_4, in_4, bias_4, conv_4, IN_DEPTH_4, OUT_DEPTH_4, FILTER_HEIGHT_4,
               IN_HEIGHT_4, IN_WIDTH_4, OUT_CONV_HEIGHT_4, OUT_CONV_WIDTH_4, STRIDE_CONV_4);
    ticks[CONV4].compute = read_cycle64();
    relu(conv_4, OUT_CONV_HEIGHT_4, OUT_CONV_WIDTH_4, OUT_DEPTH_4);
    ticks[CONV4].relu = ticks[CONV4].end = read_cycle64();

    /* conv5: pad 13->15 -> conv 256x13x13 -> pool 256x6x6 */
    ticks[CONV5].start = read_cycle64();
    pad_layer(conv_4, in_5, IN_DEPTH_5, OUT_CONV_HEIGHT_4, OUT_CONV_WIDTH_4, PAD_IN_5);
    ticks[CONV5].pad = read_cycle64();
    conv_layer(weights_5, in_5, bias_5, conv_5, IN_DEPTH_5, OUT_DEPTH_5, FILTER_HEIGHT_5,
               IN_HEIGHT_5, IN_WIDTH_5, OUT_CONV_HEIGHT_5, OUT_CONV_WIDTH_5, STRIDE_CONV_5);
    ticks[CONV5].compute = read_cycle64();
    relu(conv_5, OUT_CONV_HEIGHT_5, OUT_CONV_WIDTH_5, OUT_DEPTH_5);
    ticks[CONV5].relu = read_cycle64();
    maxpool(conv_5, pool_5,
            OUT_CONV_HEIGHT_5, OUT_CONV_WIDTH_5, OUT_DEPTH_5,
            OUT_HEIGHT_5,      OUT_WIDTH_5,      OUT_DEPTH_5,
            STRIDE_MAX_5, POOL_SIZE_5);
    ticks[CONV5].end = read_cycle64();

    /* fc6: 9216 -> 4096, ReLU */
    ticks[FC6].start = ticks[FC6].pad = read_cycle64();
    fc_layer(weights_fc6, pool_5, bias_fc6, fc6_out, FC6_IN_SIZE, FC6_OUT_SIZE);
    ticks[FC6].compute = read_cycle64();
    relu(fc6_out, FC6_OUT_SIZE, 1, 1);
    ticks[FC6].relu = ticks[FC6].end = read_cycle64();

    /* fc7: 4096 -> 4096, ReLU */
    ticks[FC7].start = ticks[FC7].pad = read_cycle64();
    fc_layer(weights_fc7, fc6_out, bias_fc7, fc7_out, FC7_IN_SIZE, FC7_OUT_SIZE);
    ticks[FC7].compute = read_cycle64();
    relu(fc7_out, FC7_OUT_SIZE, 1, 1);
    ticks[FC7].relu = ticks[FC7].end = read_cycle64();

    /* fc8: 4096 -> 1000 (no ReLU) */
    ticks[FC8].start = ticks[FC8].pad = read_cycle64();
    fc_layer(weights_fc8, fc7_out, bias_fc8, fc8_out, FC8_IN_SIZE, FC8_OUT_SIZE);
    ticks[FC8].compute = ticks[FC8].relu = ticks[FC8].end = read_cycle64();

    uint64_t total_end = read_cycle64();

    print_report(total_start, total_end);

    printf("Fim alexnet_full\n");
    return 0;
}
