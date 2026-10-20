#ifndef __CNN_COMMON_VECTOR_OPT_H__
#define __CNN_COMMON_VECTOR_OPT_H__

#include <stdlib.h>

// Register use: v24 accumulator, v16 and v8 operands (LMUL = 8).
// The loads and stores clobber "memory" so GCC keeps the scalar stores
// around them (e.g. pad()) in program order once everything is inlined.

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
    // explicit stores, not memset: GCC can expand memset into RVV stores of its own
    size_t vl = 0;
    int total;

    type *out_addr = buf;

    for (total = n; total > 0; total -= vl)
    {
        __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));
        __asm__ volatile("vmv.v.i v16, 0");
        __asm__ volatile("vse32.v v16, (%0)" :: "r"(out_addr) : "memory");

        out_addr += vl;
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
    //
    // Vectorized over ox: vl output pixels of a row at a time, each (ky, kx)
    // adds w[ky][kx] times the vl input pixels under it. Those pixels are s
    // apart, so a strided load is used when s > 1 (conv1), a unit-stride one
    // otherwise (strided accesses go one element per cycle)
    const int C_in  = shape->C_in;
    const int H_out = shape->H_out;
    const int W_out = shape->W_out;
    const int K = params->K;
    const int s = params->s;
    const int Hp = shape->H_in + 2*params->p;
    const int Wp = shape->W_in + 2*params->p;

    const type *w = params->w + (oc*C_in + ic)*K*K;
    const type *in_c = in + ic*Hp*Wp;
    const int stride = s*sizeof(type);

    size_t vl = 0;

    for (int oy = 0; oy < H_out; oy++)
    {
        type *out_addr = out + oy*W_out;

        for (int ox = 0; ox < W_out; ox += vl)
        {
            __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(W_out - ox));
            __asm__ volatile("vle32.v v24, (%0)" :: "r"(out_addr) : "memory");

            for (int ky = 0; ky < K; ky++)
            {
                const type *in_addr = in_c + (oy*s + ky)*Wp + ox*s;

                for (int kx = 0; kx < K; kx++)
                {
                    if (s == 1)
                        __asm__ volatile("vle32.v v16, (%0)" :: "r"(in_addr) : "memory");
                    else
                        __asm__ volatile("vlse32.v v16, (%0), %1" :: "r"(in_addr), "r"(stride) : "memory");
                    __asm__ volatile("vmacc.vx v24, %0, v16" :: "r"(w[ky*K + kx]));

                    in_addr++;
                }
            }

            __asm__ volatile("vse32.v v24, (%0)" :: "r"(out_addr) : "memory");

            out_addr += vl;
        }
    }
}
//}}}
//{{{
KERNEL
void int_handler (const int n, type buf[])
{
    size_t vl = 0;
    int total;

    type *out_addr = buf;

    for (total = n; total > 0; total -= vl)
    {
        __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));
        __asm__ volatile("vle32.v v16, (%0)" :: "r"(out_addr) : "memory");
        __asm__ volatile("vsra.vx v16, v16, %0" :: "r"(QUANT_SHIFT));
        __asm__ volatile("vse32.v v16, (%0)" :: "r"(out_addr) : "memory");

        out_addr += vl;
    }
}
//}}}
//{{{
KERNEL
void sum_bias (const int n, type buf[], const type b)
{
    size_t vl = 0;
    int total;

    type *out_addr = buf;

    for (total = n; total > 0; total -= vl)
    {
        __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));
        __asm__ volatile("vle32.v v16, (%0)" :: "r"(out_addr) : "memory");
        __asm__ volatile("vadd.vx v16, v16, %0" :: "r"(b));
        __asm__ volatile("vse32.v v16, (%0)" :: "r"(out_addr) : "memory");

        out_addr += vl;
    }
}
//}}}
//{{{
KERNEL
void add_bias (const int n, type buf[], const type b[])
{
    size_t vl = 0;
    int total;

    type *out_addr = buf;
    const type *bias_addr = b;

    for (total = n; total > 0; total -= vl)
    {
        __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));
        __asm__ volatile("vle32.v v16, (%0)" :: "r"(out_addr) : "memory");
        __asm__ volatile("vle32.v  v8, (%0)" :: "r"(bias_addr) : "memory");
        __asm__ volatile("vadd.vv v16, v16, v8");
        __asm__ volatile("vse32.v v16, (%0)" :: "r"(out_addr) : "memory");

        bias_addr += vl;
        out_addr += vl;
    }
}
//}}}
//{{{
KERNEL
void relu (const int n, type buf[])
{
    size_t vl = 0;
    int total;

    type *out_addr = buf;

    for (total = n; total > 0; total -= vl)
    {
        __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));
        __asm__ volatile("vle32.v v16, (%0)" :: "r"(out_addr) : "memory");
        __asm__ volatile("vmslt.vi v0, v16, 0");
        __asm__ volatile("vmerge.vim v16, v16, 0, v0");
        __asm__ volatile("vse32.v v16, (%0)" :: "r"(out_addr) : "memory");

        out_addr += vl;
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
    // 3x3 window, stride 2. Vectorized over ox: the windows of vl consecutive
    // outputs start 2 pixels apart, so each of the 9 window positions is one
    // stride-2 load
    const int stride = 2*sizeof(type);

    size_t vl = 0;

    type *out_addr = out;

    for (int ox = 0; ox < W_out; ox += vl)
    {
        const type *win = in + 2*ox;

        __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(W_out - ox));
        __asm__ volatile("vlse32.v v24, (%0), %1" :: "r"(win), "r"(stride) : "memory");

        for (int dy = 0; dy < 3; dy++)
        {
            for (int dx = 0; dx < 3; dx++)
            {
                if (dy == 0 && dx == 0)
                    continue;
                __asm__ volatile("vlse32.v v16, (%0), %1" :: "r"(win + dy*W_in + dx), "r"(stride) : "memory");
                __asm__ volatile("vmax.vv v24, v24, v16");
            }
        }

        __asm__ volatile("vse32.v v24, (%0)" :: "r"(out_addr) : "memory");

        out_addr += vl;
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
    const int C_in  = shape->C_in;  // >= VLMAX for every VLEN in use
    const int C_out = shape->C_out;

    size_t vl = 0;
    int total;
    type acc;

    for (int o = 0; o < C_out; o++)
    {
        const type *k_addr = params->w + o*C_in;
        const type *in_addr = in;

        // v24 holds VLMAX partial sums; tail-undisturbed keeps them intact if
        // the last chunk is shorter than VLMAX
        __asm__ volatile("vsetvli %0, %1, e32, m8, tu, mu" : "=r"(vl) : "r"(C_in));
        __asm__ volatile("vmv.v.i v24, 0");

        for (total = C_in; total > 0; total -= vl)
        {
            __asm__ volatile("vsetvli %0, %1, e32, m8, tu, mu" : "=r"(vl) : "r"(total));
            __asm__ volatile("vle32.v v16, (%0)" :: "r"(k_addr) : "memory");
            __asm__ volatile("vle32.v  v8, (%0)" :: "r"(in_addr) : "memory");
            __asm__ volatile("vmacc.vv v24, v16, v8");

            k_addr += vl;
            in_addr += vl;
        }

        __asm__ volatile("vsetvli %0, %1, e32, m8, tu, mu" : "=r"(vl) : "r"(C_in));
        __asm__ volatile("vmv.s.x v8, zero");
        __asm__ volatile("vredsum.vs v8, v24, v8");
        __asm__ volatile("vmv.x.s %0, v8" : "=r"(acc));

        out[o] = acc;
    }

    int_handler (C_out, out);
    add_bias (C_out, out, params->b);
}
//}}}

#endif
