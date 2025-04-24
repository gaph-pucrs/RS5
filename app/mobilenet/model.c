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

#define type    double

void batch_normalization (
    type input[],
    const int filters,
    const int size,
    const type mean[],
    const type var[],
    const type gamma[],
    const type beta[],
    const double eps
) {
    for (int i=0; i<CONV1_FEATUREMAP_HEIGHT; i++) 
    {
        for (int j=0; j<CONV1_FEATUREMAP_WIDTH; j++) 
        {
            for (int n=0; n<CONV1_FILTERS; n++) 
            {
                int id = n + j*CONV1_FILTERS + i*CONV1_FILTERS*CONV1_FEATUREMAP_WIDTH;
                input[id] -= mean[n];
                input[id] /= sqrt(var[n] + eps);
                input[id] *= gamma[n];
                input[id] += beta[n];
            }
        }
    }
}

void relu (
    type input[],
    const int size
) {
    for (int i=0; i<size; i++) {
        input[i] = (input[i] >= 0.0) ? input[i] : 0.0;
        input[i] = (input[i] > 6.0) ? 6.0 : input[i];
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
        output, 
        filters, 
        CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH, 
        mean, 
        var, 
        gamma, 
        beta, 
        eps
    );
    #endif

    // return;

    relu(output, CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH*filters);
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
    int base_y = 0, base_x = 0;
    int cont = 0;

    for (int k=0; k<OUTPUT_HEIGHT; k++)
    {
        base_x = 0;
        for (int l=0; l<OUTPUT_WIDTH; l++)
        {
            for (int i=0; i<kernel_size; i++)
            {
                for (int j=0; j<kernel_size; j++)
                {
                    for (int m=0; m<OUTPUT_CHANNELS; m++)
                    {
                        // int idx_i = (m)+(base_x)+(base_y)+(j*INPUT_CHANNELS)+(i*INPUT_CHANNELS*INPUT_WIDTH);
                        int idx_i = (m)+(j*32)+(i*32*112)+(l*stride*32)+(k*stride*32*112);
                        int idx_w = (m)+(j*OUTPUT_CHANNELS)+(i*OUTPUT_CHANNELS*kernel_size);
                        int idx_out = (m)+(l*OUTPUT_CHANNELS)+(k*OUTPUT_CHANNELS*OUTPUT_WIDTH);
                        double partial_sum = input[idx_i]*weights[idx_w];
                        // printf("\nidx_i = %d, idx_w = %d e idx_out = %d\n", idx_i, idx_w, idx_out);
                        cont++;
                        output[idx_out] += partial_sum;
                        // if (isnan(partial_sum)) {
                        //     printf("partial_sum: %lf idx:(%d, %d), base_x:%d base_y:%d\n", idx_i, idx_w, base_x, base_y);
                        // }
                    }
                    // if(cont >= 280) return;
                }
            }
            base_x += stride*INPUT_CHANNELS;
        }
        base_y += stride*INPUT_CHANNELS*INPUT_WIDTH;
    }
}

int main()
{
    double *l1_output = calloc(
            CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH*CONV1_FILTERS,
            sizeof(double));

    _conv_block (
       img,
       conv1,
       l1_output, 
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

    double *l2_output = calloc(112*112*32, sizeof(double));

#if 0
    _depthwise_conv_block (
        112,
        112,
        32,
        l1_output,
        conv_dw_1,
        112,
        112,
        32,
        l2_output,
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
#endif
    const int size = CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH*CONV1_FILTERS;

    for (int i=0; i<size; i++) {
        if (l1_output[i] == 0.0)
            printf("0.0\n");
        else
            printf("%.8lf\n", l1_output[i]);
    }

    // for (int i=0; i<size; i++) {
    //     printf("%lf\n", l2_output[i]);
    // }

    free(l1_output);
    free(l2_output);

    return 0;
}