// http://arxiv.org/pdf/1603.07285v1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "params/data.h"
//------------------------------
// LAYER1
#include "params/conv1.h"
#include "params/conv_dw_1.h"

#ifdef BATCHNORMALIZATION
    #include "params/conv1_bn_mean.h"
    #include "params/conv1_bn_var.h"
    #include "params/conv1_bn_gamma.h"
    #include "params/conv1_bn_beta.h"
    #include "params/conv1_bn_eps.h"

    #include "params/conv_dw_1_bn_mean.h"
    #include "params/conv_dw_1_bn_var.h"
    #include "params/conv_dw_1_bn_gamma.h"
    #include "params/conv_dw_1_bn_beta.h"
    #include "params/conv_dw_1_bn_eps.h"
#endif

#define IMAGE_HEIGHT    225 // 224 + 1
#define IMAGE_WIDTH     225 // 224 + 1
#define IMAGE_CHANNELS    3
#define CONV1_FEATUREMAP_HEIGHT 112
#define CONV1_FEATUREMAP_WIDTH  112
#define CONV1_FILTERS       32

#define CONV_DW_1_HEIGHT        112
#define CONV_DW_1_WIDTH         112
#define CONV_DW_1_CHANNELS       32

#define type    double

// general use functions
type clamp(const type x, const type max, const type min) {
    return (x < min) ? min :
           (x > max) ? max : x;
}

void print(const type in[], const int h, const int w, const int c) {
    for (int i=0; i<h; i++)
    {
        for (int j=0; j<w; j++)
        {
            for (int k=0; k<c; k++)
            {
                int idx= (k)+((j)*(c))+((i)*(c)*(w));
                printf("%.6lf\n", in[idx]);
            }
        }
    }
}

void pad (
    const int HEIGHT,
    const int WIDTH,
    const int CHANNELS,
    type in[],
    type out[]
) {
    for (int i=0; i<HEIGHT; i++)
    {
        for (int j=0; j<WIDTH; j++)
        {
            for (int k=0; k<CHANNELS; k++)
            {
                int idx_i = (k)+(j*CHANNELS)+(i*CHANNELS*WIDTH); 
                int idx_out = (k)+((j+1)*(CHANNELS))+((i+1)*(CHANNELS)*(WIDTH+2));
                out[idx_out] = in[idx_i];
            }
        }
    }
}

// mobilenet functions
void batch_normalization (
    const int HEIGHT,
    const int WIDTH,
    const int CHANNELS,
    type input[],
    const type mean[],
    const type var[],
    const type gamma[],
    const type beta[],
    const double eps
) {
    for (int i=0; i<HEIGHT; i++) 
    {
        for (int j=0; j<WIDTH; j++) 
        {
            for (int n=0; n<CHANNELS; n++) 
            {
                int id = (n) + (j*CHANNELS) + (i*CHANNELS*WIDTH);
                input[id] -= mean[n];
                input[id] /= sqrt(var[n] + eps);
                input[id] *= gamma[n];
                input[id] += beta[n];
            }
        }
    }
}

void relu (
    const type max,
    type input[],
    const int size
) {
    for (int i=0; i<size; i++) {
        input[i] = clamp(input[i], max, 0);
    }
}

void _conv_block (
    const type input[],
    const type weights[],
    type output[], 
    int filters,
    const double alpha,
    const int kernel_size,
    const int stride
#ifdef BATCHNORMALIZATION
    ,
    const type mean[],
    const type var[],
    const type gamma[],
    const type beta[],
    const double eps
#endif
) {
    filters = (int)(filters*alpha);

    // "(0,0)" of the 3x3 image
    int base_y=0, base_x=0;

    for (int k=0; k<CONV1_FEATUREMAP_HEIGHT; k++)
    {
        base_x = 0;
        for (int l=0; l<CONV1_FEATUREMAP_WIDTH; l++)
        {
            for (int i=0; i<kernel_size; i++)
            {
                for (int j=0; j<kernel_size; j++)
                {
                    for (int m=0; m<IMAGE_CHANNELS; m++)
                    {
                        int idx_i = (m)+(base_x)+(base_y)+(j*IMAGE_CHANNELS)+(i*IMAGE_CHANNELS*IMAGE_WIDTH);
                        for (int n=0; n<filters; n++)
                        {
                            int idx_w = (n)+(m*filters)+(j*filters*IMAGE_CHANNELS)+(i*filters*IMAGE_CHANNELS*kernel_size);
                            int idx_out = (n)+(l*filters)+(k*filters*CONV1_FEATUREMAP_WIDTH);
                            output[idx_out] += input[idx_i]*weights[idx_w];
                        }
                    }
                }
            }
            base_x += stride*IMAGE_CHANNELS;
        }
        base_y += stride*IMAGE_CHANNELS*IMAGE_WIDTH;
    }

    #ifdef BATCHNORMALIZATION
    batch_normalization (
        CONV1_FEATUREMAP_HEIGHT,
        CONV1_FEATUREMAP_WIDTH,
        filters,
        output, 
        mean, 
        var, 
        gamma, 
        beta, 
        eps
    );
    #endif

    relu(6.0, output, CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH*filters);
}

void _depthwise_conv_block (
    const int INPUT_HEIGHT,
    const int INPUT_WIDTH,
    const int INPUT_CHANNELS,
    const type input[],
    const type weights[],
    const int OUTPUT_HEIGHT,
    const int OUTPUT_WIDTH,
    const int OUTPUT_CHANNELS,
    type output[],
    const double alpha,
    const int kernel_size,
    const int stride
#ifdef BATCHNORMALIZATION
    ,
    const type mean[],
    const type var[],
    const type gamma[],
    const type beta[],
    const double eps
#endif
) {
    int base_y = (INPUT_CHANNELS)*(INPUT_WIDTH+2), base_x = (INPUT_CHANNELS);
    // int base_y = 0, base_x = 0;
    for (int k=0; k<OUTPUT_HEIGHT; k++)
    {
        base_x = (INPUT_CHANNELS);
        // base_x = 0;
        for (int l=0; l<OUTPUT_WIDTH; l++)
        {
            for (int i=0; i<kernel_size; i++)
            {
                for (int j=0; j<kernel_size; j++)
                {
                    for (int m=0; m<OUTPUT_CHANNELS; m++)
                    {
                        int idx_i = (m)+(j*32)+(i*32*114)+(l*stride*32)+(k*stride*32*114);
                        int idx_w = (m)+(j*OUTPUT_CHANNELS)+(i*OUTPUT_CHANNELS*kernel_size);
                        int idx_out = (m)+(l*OUTPUT_CHANNELS)+(k*OUTPUT_CHANNELS*OUTPUT_WIDTH);
                        double partial_sum = input[idx_i]*weights[idx_w];
                        output[idx_out] += partial_sum;
                    }
                }
            }
            base_x += (INPUT_CHANNELS);
        }
        base_y += (INPUT_CHANNELS)*(INPUT_WIDTH+2);
    }

    #ifdef BATCHNORMALIZATION
    batch_normalization (
        OUTPUT_HEIGHT,
        OUTPUT_WIDTH,
        OUTPUT_CHANNELS,
        output, 
        mean, 
        var, 
        gamma, 
        beta, 
        eps
    );
    #endif

    relu(6.0, output, OUTPUT_HEIGHT*OUTPUT_WIDTH*OUTPUT_CHANNELS);
}

int main()
{
    type *conv1_out = calloc(
            CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH*CONV1_FILTERS,
            sizeof(type));

    _conv_block (
       img,
       conv1,
       conv1_out, 
       CONV1_FILTERS,
       1,   // alpha
       3,   // kernel_size
       2    // stride
    #ifdef BATCHNORMALIZATION
       ,
       conv1_bn_mean,
       conv1_bn_var,
       conv1_bn_gamma,
       conv1_bn_beta,
       conv1_bn_eps
    #endif
    );

    type *conv_dw_1_out = calloc((CONV_DW_1_CHANNELS)*(CONV_DW_1_HEIGHT)*(CONV_DW_1_WIDTH), sizeof(type));
    type *conv1_out_pad = calloc((CONV_DW_1_CHANNELS)*(CONV_DW_1_HEIGHT+2)*(CONV_DW_1_WIDTH+2), sizeof(type));

    pad (
        CONV_DW_1_HEIGHT,
        CONV_DW_1_WIDTH,
        CONV_DW_1_CHANNELS,
        conv1_out,
        conv1_out_pad
    );

    _depthwise_conv_block (
        CONV1_FEATUREMAP_HEIGHT,
        CONV1_FEATUREMAP_WIDTH,
        CONV1_FILTERS,
        conv1_out_pad,
        conv_dw_1,
        CONV_DW_1_HEIGHT,
        CONV_DW_1_WIDTH,
        CONV_DW_1_CHANNELS,
        conv_dw_1_out,
        1.0,    // alpha
        3,      // kernel_size
        1       // stride
    #ifdef BATCHNORMALIZATION
        ,
        conv_dw_1_bn_mean,
        conv_dw_1_bn_var,
        conv_dw_1_bn_gamma,
        conv_dw_1_bn_beta,
        conv_dw_1_bn_eps
     #endif
    );

    print(conv_dw_1_out, 112, 112, 32);

    free(conv1_out);
    free(conv1_out_pad);
    free(conv_dw_1_out);

    return 0;
}