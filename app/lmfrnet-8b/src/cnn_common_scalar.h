#ifndef __CNN_COMMON_SCALAR_H__
#define __CNN_COMMON_SCALAR_H__

#include <stdlib.h>
#include <string.h>

//{{{
KERNEL
void pad (
    const int H,
    const int W,
    const int C,
    const act_t in[],
    act_t out[]
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
KERNEL
void conv_chunk (
    const TensorShape *restrict shape,
    const act_t in[], // offset = x + y
    const weight_t w[],
    acc_t acc[],      // starts at the bias
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
                    acc[n] += in[idx_i]*w[idx_w+n];
                }
            }
        }
    }
}
//}}}
//{{{
KERNEL
void requant (const int C, const acc_t acc[], act_t out[], const int shift)
{
    for (int n = 0; n < C; n++)
    {
        out[n] = sat(acc[n] >> shift);
    }
}
//}}}
//{{{
KERNEL
void relu (const int C, act_t buf[])
{
    for (int n = 0; n < C; n++)
    {
        buf[n] = (buf[n] > 0) ? buf[n] : 0;
    }
}
//}}}
//{{{
KERNEL
void avg_pool_chunk (
    const act_t *in,    // (0, 0)
    const int W_in,
    const int C_in,
    act_t out[]
) {
    int sum = 0; // 4 act_t values don't fit in act_t
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
KERNEL
void gap_chunk (
    const TensorShape *restrict shape,
    const act_t in[],
    act_t out[]
) {
    const int N     = shape->H_in * shape->W_in;
    const int C_in  = shape->C_in;
    const int shift = __builtin_ctz(N); // log(2) if N is a power of 2, else undefined

    int sum; // N act_t values don't fit in act_t
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
KERNEL
void concat4_chunk (
    const int C_in,
    const act_t x[],
    const act_t y1[],
    const act_t y2[],
    const act_t y3[],
    act_t out[]
) {
    // Explicit element-wise copies (not memcpy): GCC's block-copy expansion
    // ("move by pieces") can emit RVV load/store pairs for memcpy on this
    // target independent of KERNEL's no-tree-vectorize attributes, since
    // it isn't gated by them. A plain scalar loop is.
    for (int n = 0; n < C_in; n++) out[n] = x[n];
    for (int n = 0; n < 12; n++)   out[C_in + n] = y1[n];
    for (int n = 0; n < 6; n++)    out[C_in + 12 + n] = y2[n];
    for (int n = 0; n < 6; n++)    out[C_in + 12 + 6 + n] = y3[n];
}
//}}}
//{{{
KERNEL
void avg_pool (
    const TensorShape *restrict shape,
    const act_t in[],
    act_t out[]
) {
    const int W_in  = shape->W_in;
    const int C_in  = shape->C_in;
    const int H_out = shape->H_out;
    const int W_out = shape->W_out;

    for (int row = 0; row < H_out; row++)
    {
        for (int col = 0; col < W_out; col++)
        {
            const act_t *in_chunk = in + (2*row*W_in + 2*col)*C_in;
            act_t *out_chunk = out + (row*W_out + col)*C_in;
            avg_pool_chunk (in_chunk, W_in, C_in, out_chunk);
        }
    }
}
//}}}
//{{{
KERNEL
void gap (
    const TensorShape *restrict shape,
    const act_t in[],
    act_t out[]
) {
    gap_chunk (shape, in, out);
}
//}}}
//{{{
KERNEL
void fc (
    const TensorShape *restrict shape,
    const ConvParams *restrict params,
    const act_t in[],
    act_t out[]
) {
    const int C_in  = shape->C_in;
    const int C_out = shape->C_out;
    const weight_t *w = params->w;

    // sums need acc_t, out is act_t: accumulate apart, starting at the bias (see conv_block)
    acc_t acc[C_out];
    for (int n = 0; n < C_out; n++) acc[n] = params->b[n];

    int idx_w;
    for (int m = 0; m < C_in; m++)
    {
        idx_w = m*C_out;
        for (int n = 0; n < C_out; n++)
        {
            acc[n] += in[m]*w[idx_w+n];
        }
    }

    requant (C_out, acc, out, params->shift); // logits: no ReLU
}
//}}}

#endif
