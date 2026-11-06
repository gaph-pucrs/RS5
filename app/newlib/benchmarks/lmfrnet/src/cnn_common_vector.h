#ifndef __CNN_COMMON_VECTOR_H__
#define __CNN_COMMON_VECTOR_H__

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

    type pixel;
    type *in_addr;
    type *k_addr = (type *) w;
    type *out_addr = (type *) out;

    size_t vl = 0;
    int total;

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            in_addr = in + j*C_in + i*C_in*W_in;
            for (int m = 0; m < C_in; m++)
            {
                pixel = *(in_addr);
                in_addr++;

                out_addr = (type *) out;
                for (total = C_out; total > 0; total -= vl)
                {
                    __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));
                    __asm__ volatile("vle32.v v16, (%0)" :: "r"(k_addr));
                    __asm__ volatile("vle32.v v24, (%0)" :: "r"(out_addr));
                    __asm__ volatile("vmacc.vx v24, %0, v16" :: "r"(pixel));
                    __asm__ volatile("vse32.v v24, (%0)" :: "r"(out_addr));

                    k_addr += vl;
                    out_addr += vl;
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
    // can be merged with sum_bias() as well to avoid VLOAD and VSTORE calls
    size_t vl = 0;
    int total;

    type *out_addr = (type *) buf;

    for (total = C; total > 0; total -= vl)
    {
        __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));
        __asm__ volatile("vle32.v v16, (%0)" :: "r"(out_addr));
        __asm__ volatile("vsra.vi v16, v16, 13");
        __asm__ volatile("vse32.v v16, (%0)" :: "r"(out_addr));

        out_addr += vl;
    }
}
//}}}
//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void sum_bias(const int C, type buf[], const type b[])
{
    size_t vl = 0;
    int total;

    type *out_addr = (type *) buf;
    type *bias_addr = (type *) b;

    for (total = C; total > 0; total -= vl)
    {
        __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));
        __asm__ volatile("vle32.v v16, (%0)" :: "r"(out_addr));
        __asm__ volatile("vle32.v  v8, (%0)" :: "r"(bias_addr));
        __asm__ volatile("vadd.vv v16, v16, v8");
    //--------------------- ReLU ---------------------------------
        __asm__ volatile("vmslt.vi v0, v16, 0");
        __asm__ volatile("vmerge.vim v16, v16, 0, v0");
    //------------------------------------------------------------
        __asm__ volatile("vse32.v v16, (%0)" :: "r"(out_addr));

        bias_addr += vl;
        out_addr += vl;
    }
}
//}}}
//{{{
__attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns"))) __attribute__((no_builtin))
void relu(const int C, type buf[])
{
    // merged with sum_bias()
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
    size_t vl = 0;
    int total;
    type *in_addr = (type *) in;
    type *offset;
    type *out_addr = (type *) out;

    for (total = C_in; total > 0; total -= vl)
    {
        offset = in_addr;
        __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));
        __asm__ volatile("vle32.v v16, (%0)" :: "r"(offset)); // (0, 0)

        offset += C_in;
        __asm__ volatile("vle32.v v24, (%0)" :: "r"(offset)); // (0, 1)
        __asm__ volatile("vadd.vv v16, v16, v24");

        offset += (W_in-1)*C_in;
        __asm__ volatile("vle32.v v24, (%0)" :: "r"(offset)); // (1, 0)
        __asm__ volatile("vadd.vv v16, v16, v24");

        offset += C_in;
        __asm__ volatile("vle32.v v24, (%0)" :: "r"(offset)); // (1, 1)
        __asm__ volatile("vadd.vv v16, v16, v24");

        __asm__ volatile("vsra.vi v16, v16, 2");
        __asm__ volatile("vse32.v v16, (%0)" :: "r"(out_addr));

        out_addr += vl;
        in_addr += vl;
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
    const int shift = __builtin_ctz(N); // N is a power of 2 (H_in, W_in are)

    size_t vl = 0;
    int total;
    type *base_addr = (type *) in;
    type *in_addr;
    type *out_addr = (type *) out;

    for (total = C_in; total > 0; total -= vl)
    {
        __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));

        in_addr = base_addr;
        __asm__ volatile("vle32.v v16, (%0)" :: "r"(in_addr)); // spatial position 0

        for (int i = 1; i < N; i++)
        {
            in_addr += C_in;
            __asm__ volatile("vle32.v v24, (%0)" :: "r"(in_addr));
            __asm__ volatile("vadd.vv v16, v16, v24");
        }

        __asm__ volatile("vsra.vx v16, v16, %0" :: "r"(shift));
        __asm__ volatile("vse32.v v16, (%0)" :: "r"(out_addr));

        base_addr += vl;
        out_addr += vl;
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
    memcpy(out                ,  x, C_in*sizeof(type));
    memcpy(out + C_in         , y1,   12*sizeof(type));
    memcpy(out + C_in + 12    , y2,    6*sizeof(type));
    memcpy(out + C_in + 12 + 6, y3,    6*sizeof(type));
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

    type pixel;
    type *k_addr = (type *) w;
    type *out_addr;

    size_t vl = 0;
    int total;

    for (int m = 0; m < C_in; m++)
    {
        pixel = in[m];

        out_addr = (type *) out;
        for (total = C_out; total > 0; total -= vl)
        {
            __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));
            __asm__ volatile("vle32.v v16, (%0)" :: "r"(k_addr));
            __asm__ volatile("vle32.v v24, (%0)" :: "r"(out_addr));
            __asm__ volatile("vmacc.vx v24, %0, v16" :: "r"(pixel));
            __asm__ volatile("vse32.v v24, (%0)" :: "r"(out_addr));

            k_addr += vl;
            out_addr += vl;
        }
    }

    int_handler (C_out, out);

    out_addr = (type *) out;
    type *bias_addr = (type *) b;
    for (total = C_out; total > 0; total -= vl)
    {
        __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));
        __asm__ volatile("vle32.v v16, (%0)" :: "r"(out_addr));
        __asm__ volatile("vle32.v  v8, (%0)" :: "r"(bias_addr));
        __asm__ volatile("vadd.vv v16, v16, v8");
        __asm__ volatile("vse32.v v16, (%0)" :: "r"(out_addr));

        bias_addr += vl;
        out_addr += vl;
    }
}
//}}}

#endif
