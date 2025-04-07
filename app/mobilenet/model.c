#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "params/data.h"
//------------------------------
// LAYER1
#include "params/conv1.h"

#ifdef BATCHNORMALIZATION
    #include "params/conv1_bn_mean.h"
    #include "params/conv1_bn_var.h"
    #include "params/conv1_bn_gamma.h"
    #include "params/conv1_bn_beta.h"
    #include "params/conv1_bn_eps.h"
#endif

#define INPUT_HEIGHT    224
#define INPUT_WIDTH     224
#define INPUT_CHANNELS    3
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
        input[i] = (input[i] >= 0) ? input[i] : 0;
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
                    for (int m=0; m<INPUT_CHANNELS; m++)
                    {
                        int idx_i = (m)+(base_x)+(base_y)+(j*INPUT_CHANNELS+i*INPUT_CHANNELS*INPUT_WIDTH);
                        for (int n=0; n<filters; n++)
                        {
                            int idx_w = (n)+(m*filters)+(j*filters*INPUT_CHANNELS)+(i*filters*INPUT_CHANNELS*kernel_size);
                            int idx_out = (n)+(l*filters)+(k*filters*CONV1_FEATUREMAP_WIDTH);
                            output[idx_out] += input[idx_i]*weights[idx_w];
                        }
                    }
                }
            }
            base_x += stride*INPUT_CHANNELS;
        }
        base_y += stride*INPUT_CHANNELS*INPUT_WIDTH;
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

    relu(output, CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH*filters);
}

int main()
{
    
    double *output = malloc(CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH*CONV1_FILTERS*sizeof(double));

    _conv_block (
       img,
       conv1,
       output, 
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

    const int size = CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH*CONV1_FILTERS;

    for (int i=0; i<size; i++) {
        if (output[i] == 0.0)
            printf("0.0\n");
        else
            printf("%.8lf\n", output[i]);
    }

    free(output);

    return 0;
}