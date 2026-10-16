#ifndef __ALEXNET_COMMON_H__
#define __ALEXNET_COMMON_H__

#include <stdio.h>

#include "cnn_common.h"

//{{{
KERNEL
void conv_join (const int n, type out[], const type b)
{
    // out holds the sum of every input channel's partial result
    int_handler (n, out);
    sum_bias (n, out, b);
    relu (n, out);
}
//}}}
//{{{
KERNEL
void conv (
    const TensorShape *restrict shape,
    const ConvParams *restrict params,
    const type in[],
    type out[]
) {
    const int H_in  = shape->H_in;
    const int W_in  = shape->W_in;
    const int C_in  = shape->C_in;
    const int H_out = shape->H_out;
    const int W_out = shape->W_out;
    const int C_out = shape->C_out;
    const int p = params->p;

    type *in_pd = calloc(C_in*(H_in + 2*p)*(W_in + 2*p), sizeof(type));
    if (in_pd == NULL)
    {
        printf("conv: out of memory\n");
        exit(1);
    }

    pad (H_in, W_in, C_in, p, in, in_pd);

    // same order as app/alexnet: C_out, C_in, H_out, W_out, K_y, K_x
    for (int oc = 0; oc < C_out; oc++)
    {
        type *out_oc = out + oc*H_out*W_out;

        zero (H_out*W_out, out_oc);

        for (int ic = 0; ic < C_in; ic++)
        {
            conv_channel (shape, params, in_pd, out_oc, oc, ic);
        }

        conv_join (H_out*W_out, out_oc, params->b[oc]);
    }

    free (in_pd);
}
//}}}
//{{{
KERNEL
void fc_relu (
    const TensorShape *restrict shape,
    const ConvParams *restrict params,
    const type in[],
    type out[]
) {
    fc (shape, params, in, out);
    relu (shape->C_out, out);
}
//}}}

#endif
