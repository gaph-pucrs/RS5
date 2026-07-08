#ifndef __LMFRNET_COMMON_H__
#define __LMFRNET_COMMON_H__

#include "cnn_common.h"

//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void conv_block (
    const TensorShape *restrict shape,
    const ConvParams *restrict params,
    const type in[],
    type out_chunk[],
    const int p
) {
    conv_chunk (shape, in, params->w, out_chunk, p, params->K);
    int_handler (shape->C_out, out_chunk);
    sum_bias (shape->C_out, out_chunk, params->b);
    relu (shape->C_out, out_chunk);
}
//}}}
//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void conv (
    const TensorShape *restrict shape,
    const ConvParams *restrict params,
    const type in[],
    type out[],
    const int p
) {
    const int W_in  = shape->W_in;
    const int H_out = shape->H_out;
    const int W_out = shape->W_out;
    const int C_in  = shape->C_in;
    const int C_out = shape->C_out;

    // stride 1
    for (int row = 0; row < H_out; row++)
    {
        for (int col = 0; col < W_out; col++)
        {
            type *out_chunk = out + (row*W_out + col)*C_out;
            conv_block (shape, params, in + (row*(W_in+p) + col)*C_in, out_chunk, p);
        }
    }
}
//}}}
//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void stemBlock (
    const TensorShape *restrict shape,
    const ConvParams *restrict params,
    const type in[],
    type out[]
) {
    const int H_in  = shape->H_in;
    const int W_in  = shape->W_in;
    const int C_in  = shape->C_in;
    const int W_out = shape->W_out;

    const int K = params->K;
    const int s = params->s;

    const int p = W_out - (int)((W_in-K)/s) - 1;
    type *in_pd = calloc(C_in*(W_in+p)*(H_in+p), sizeof(type));

    if (p == 2) pad (H_in, W_in, C_in, in, in_pd);
    else { for (int n = 0; n < H_in*W_in*C_in; n++) in_pd[n] = in[n]; }

    conv (shape, params, in_pd, out, p);

    free (in_pd);
}
//}}}
//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void MFBlock (
    const MFBlockShapes *restrict shapes,
    const MFBlockParams *restrict params,
    const type x[],
    type out[]
) {
    const int H_in   = shapes->b11.H_in;
    const int W_in   = shapes->b11.W_in;
    const int C_in   = shapes->b11.C_in;
    const int C_out  = C_in + 24; // universal architecture constant, like C_b11 etc below

    const ConvParams *restrict p_b11  = &params->b11;
    const ConvParams *restrict p_b33a = &params->b33a;
    const ConvParams *restrict p_b33b = &params->b33b;
    const ConvParams *restrict p_b33c = &params->b33c;

    const int C_b11  = 12;
    const int C_b33a = 12;
    const int C_b33b =  6;
    const int C_b33c =  6;

    // b11
    type *y0_pd = calloc((H_in+2)*(W_in+2)*C_b11, sizeof(type));

    for (int row = 0; row < H_in; row++)
    {
        for (int col = 0; col < W_in; col++)
        {
            type *y0_chunk = y0_pd + (row+1)*(W_in+2)*C_b11 + (col+1)*C_b11;
            conv_block (&shapes->b11, p_b11, x + (row*W_in + col)*C_in, y0_chunk, 0);
        }
    }

    // b33a
    type *y1_pd = calloc((H_in+2)*(W_in+2)*C_b33a, sizeof(type));

    for (int row = 0; row < H_in; row++)
    {
        for (int col = 0; col < W_in; col++)
        {
            type *y1_chunk = y1_pd + (row+1)*(W_in+2)*C_b33a + (col+1)*C_b33a;
            conv_block (&shapes->b33a, p_b33a, y0_pd + row*(W_in+2)*C_b11 + col*C_b11, y1_chunk, 2);
        }
    }
    free (y0_pd);

    // b33b
    type *y2_pd = calloc((H_in+2)*(W_in+2)*C_b33b, sizeof(type));

    for (int row = 0; row < H_in; row++)
    {
        for (int col = 0; col < W_in; col++)
        {
            type *y2_chunk = y2_pd + (row+1)*(W_in+2)*C_b33b + (col+1)*C_b33b;
            conv_block (&shapes->b33b, p_b33b, y1_pd + row*(W_in+2)*C_b33a + col*C_b33a, y2_chunk, 2);
        }
    }

    // b33c
    type *y3 = calloc(H_in*W_in*C_b33c, sizeof(type));

    for (int row = 0; row < H_in; row++)
    {
        for (int col = 0; col < W_in; col++)
        {
            type *y3_chunk = y3 + (row*W_in + col)*C_b33c;
            conv_block (&shapes->b33c, p_b33c, y2_pd + row*(W_in+2)*C_b33b + col*C_b33b, y3_chunk, 2);
        }
    }

    // concat:
    for (int row = 0; row < H_in; row++)
    {
        for (int col = 0; col < W_in; col++)
        {
            int idx = row*W_in + col;
            concat4_chunk (
                C_in,
                x + idx*C_in,
                y1_pd + (row+1)*(W_in+2)*C_b33a + (col+1)*C_b33a,
                y2_pd + (row+1)*(W_in+2)*C_b33b + (col+1)*C_b33b,
                y3 + idx*C_b33c,
                out + idx*C_out
            );
        }
    }

    free (y1_pd);
    free (y2_pd);
    free (y3);
}
//}}}
//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void tran_conv (
    const TensorShape *restrict shape,
    const ConvParams *restrict params,
    const type in[],
    type out[]
) {
    conv (shape, params, in, out, 0);
}
//}}}

#endif
