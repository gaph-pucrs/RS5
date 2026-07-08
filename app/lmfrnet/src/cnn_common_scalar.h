#ifndef __CNN_COMMON_SCALAR_H__
#define __CNN_COMMON_SCALAR_H__

#include <stdlib.h>
#include <string.h>

//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void pad (
    const int H,
    const int W,
    const int C,
    const type in[],
    type out[]
) {
    int idx_in, idx_out;

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            for (int k = 0; k < C; k++)
            {
                idx_in = k + j*C + i*C*W;
                idx_out = k + (j+1)*C + (i+1)*C*(W+2);

                out[idx_out] = in[idx_in];
            }
        }
    }
}
//}}}
//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void conv_chunk (
    const TensorShape *restrict shape,
    const type in[], // offset = x + y
    const type w[],
    type out[],
    const int p, 
    const int k
) {
    const int W_in  = shape->W_in + p;
    const int C_in  = shape->C_in;
    const int C_out = shape->C_out;

    int idx_i, idx_w;

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            for (int m = 0; m < C_in; m++)
            {
                idx_i = m + j*C_in + i*C_in*W_in;
                idx_w = m*C_out + j*C_out*C_in + i*C_out*C_in*k;
                for (int n = 0; n < C_out; n++)
                {
                    out[n] += in[idx_i]*w[idx_w+n];
                }
            }
        }
    }
}
//}}}
//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void int_handler (const int C, type buf[])
{
    for (int n = 0; n < C; n++)
    {
        buf[n] >>= 13;
    }
}
//}}}
//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void sum_bias(const int C, type buf[], const type b[])
{
    for (int n = 0; n < C; n++)
    {
        buf[n] += b[n];
    }
}
//}}}
//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void relu(const int C, type buf[])
{
    for (int n = 0; n < C; n++)
    {
        buf[n] = (buf[n] > 0) ? buf[n] : 0;
    }
}
//}}}
//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void avg_pool_chunk (
    const type *in,     // (0, 0)
    const int W_in,
    const int C_in,
    type out[]
) {
    type sum = 0;
    for (int n = 0; n < C_in; n++) {
        sum  = in[n];                       // (0, 0)
        sum += in[n + C_in];                // (0, 1)
        sum += in[n + W_in*C_in];           // (1, 0)
        sum += in[n + W_in*C_in + C_in];    // (1, 1)

        out[n] = sum >> 2;
    }
}
//}}}
//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void gap_chunk (
    const TensorShape *restrict shape,
    const type in[],
    type out[]
) {
    const int N     = shape->H_in * shape->W_in;
    const int C_in  = shape->C_in;
    const int shift = __builtin_ctz(N); // log(2) if N is a power of 2, else undefined

    type sum;
    for (int n = 0; n < C_in; n++) {
        sum = 0;
        for (int i = 0; i < N; i++) {
            sum += in[n + i*C_in];
        }
        out[n] = sum >> shift;
    }
}
//}}}
//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void concat4_chunk (
    const int C_in,
    const type x[],
    const type y1[],
    const type y2[],
    const type y3[],
    type out[]
) {
    // Explicit element-wise copies (not memcpy): GCC's block-copy expansion
    // ("move by pieces") can emit RVV load/store pairs for memcpy on this
    // target independent of the no-tree-vectorize/no_builtin attributes
    // above, since it isn't gated by either. A plain scalar loop is.
    for (int n = 0; n < C_in; n++) out[n] = x[n];
    for (int n = 0; n < 12; n++)   out[C_in + n] = y1[n];
    for (int n = 0; n < 6; n++)    out[C_in + 12 + n] = y2[n];
    for (int n = 0; n < 6; n++)    out[C_in + 12 + 6 + n] = y3[n];
}
//}}}
//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void avg_pool (
    const TensorShape *restrict shape,
    const type in[],
    type out[]
) {
    const int W_in  = shape->W_in;
    const int C_in  = shape->C_in;
    const int H_out = shape->H_out;
    const int W_out = shape->W_out;

    for (int row = 0; row < H_out; row++)
    {
        for (int col = 0; col < W_out; col++)
        {
            const type *in_chunk = in + (2*row*W_in + 2*col)*C_in;
            type *out_chunk = out + (row*W_out + col)*C_in;
            avg_pool_chunk (in_chunk, W_in, C_in, out_chunk);
        }
    }
}
//}}}
//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void gap (
    const TensorShape *restrict shape,
    const type in[],
    type out[]
) {
    gap_chunk (shape, in, out);
}
//}}}
//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void fc (
    const TensorShape *restrict shape,
    const ConvParams *restrict params,
    const type in[],
    type out[]
) {
    const int C_in  = shape->C_in;
    const int C_out = shape->C_out;
    const type *w = params->w;
    const type *b = params->b;

    int idx_w;
    for (int m = 0; m < C_in; m++)
    {
        idx_w = m*C_out;
        for (int n = 0; n < C_out; n++)
        {
            out[n] += in[m]*w[idx_w+n];
        }
    }

    int_handler (C_out, out);
    sum_bias (C_out, out, b);
}
//}}}

#endif
