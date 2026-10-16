#ifndef __CNN_COMMON_SCALAR_H__
#define __CNN_COMMON_SCALAR_H__

#include <stdlib.h>

//{{{
KERNEL
void pad (
    const int H,
    const int W,
    const int C,
    const int p,
    const type in[],
    type out[]  // zeroed, [C][H+2p][W+2p]
) {
    const int Hp = H + 2*p;
    const int Wp = W + 2*p;

    for (int c = 0; c < C; c++)
    {
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                out[(c*Hp + i + p)*Wp + j + p] = in[(c*H + i)*W + j];
            }
        }
    }
}
//}}}
//{{{
KERNEL
void zero (const int n, type buf[])
{
    // explicit loop, not memset: GCC can expand memset into RVV stores
    for (int i = 0; i < n; i++)
    {
        buf[i] = 0;
    }
}
//}}}
//{{{
KERNEL
void conv_channel (
    const TensorShape *restrict shape,
    const ConvParams *restrict params,
    const type in[],  // padded input, [C_in][H_in+2p][W_in+2p]
    type out[],       // partial sums of channel oc, [H_out][W_out]
    const int oc,
    const int ic
) {
    // out[oy][ox] += sum_{ky,kx} w[oc][ic][ky][kx] * in[ic][oy*s+ky][ox*s+kx]
    const int C_in  = shape->C_in;
    const int H_out = shape->H_out;
    const int W_out = shape->W_out;
    const int K = params->K;
    const int s = params->s;
    const int Hp = shape->H_in + 2*params->p;
    const int Wp = shape->W_in + 2*params->p;

    const type *w = params->w + (oc*C_in + ic)*K*K;
    const type *in_c = in + ic*Hp*Wp;

    for (int oy = 0; oy < H_out; oy++)
    {
        for (int ox = 0; ox < W_out; ox++)
        {
            const type *in_win = in_c + oy*s*Wp + ox*s;
            type acc = 0;
            for (int ky = 0; ky < K; ky++)
            {
                for (int kx = 0; kx < K; kx++)
                {
                    acc += w[ky*K + kx]*in_win[ky*Wp + kx];
                }
            }
            out[oy*W_out + ox] += acc;
        }
    }
}
//}}}
//{{{
KERNEL
void int_handler (const int n, type buf[])
{
    for (int i = 0; i < n; i++)
    {
        buf[i] >>= QUANT_SHIFT;
    }
}
//}}}
//{{{
KERNEL
void sum_bias (const int n, type buf[], const type b)
{
    for (int i = 0; i < n; i++)
    {
        buf[i] += b;
    }
}
//}}}
//{{{
KERNEL
void add_bias (const int n, type buf[], const type b[])
{
    for (int i = 0; i < n; i++)
    {
        buf[i] += b[i];
    }
}
//}}}
//{{{
KERNEL
void relu (const int n, type buf[])
{
    for (int i = 0; i < n; i++)
    {
        buf[i] = (buf[i] > 0) ? buf[i] : 0;
    }
}
//}}}
//{{{
KERNEL
void maxpool_chunk (
    const type *in,  // first input row of the window
    const int W_in,
    const int W_out,
    type out[]       // [W_out]
) {
    // 3x3 window, stride 2
    for (int ox = 0; ox < W_out; ox++)
    {
        const type *win = in + 2*ox;
        type max = win[0];
        for (int dy = 0; dy < 3; dy++)
        {
            for (int dx = 0; dx < 3; dx++)
            {
                max = (win[dy*W_in + dx] > max) ? win[dy*W_in + dx] : max;
            }
        }
        out[ox] = max;
    }
}
//}}}
//{{{
KERNEL
void maxpool (
    const TensorShape *restrict shape,
    const type in[],
    type out[]
) {
    const int H_in  = shape->H_in;
    const int W_in  = shape->W_in;
    const int C_in  = shape->C_in;
    const int H_out = shape->H_out;
    const int W_out = shape->W_out;

    for (int c = 0; c < C_in; c++)
    {
        for (int oy = 0; oy < H_out; oy++)
        {
            maxpool_chunk (in + (c*H_in + 2*oy)*W_in, W_in, W_out, out + (c*H_out + oy)*W_out);
        }
    }
}
//}}}
//{{{
KERNEL
void fc (
    const TensorShape *restrict shape,
    const ConvParams *restrict params,
    const type in[],
    type out[]
) {
    const int C_in  = shape->C_in;
    const int C_out = shape->C_out;

    for (int o = 0; o < C_out; o++)
    {
        const type *w_row = params->w + o*C_in;
        type acc = 0;
        for (int i = 0; i < C_in; i++)
        {
            acc += w_row[i]*in[i];
        }
        out[o] = acc;
    }

    int_handler (C_out, out);
    add_bias (C_out, out, params->b);
}
//}}}

#endif
