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

#define IMAGE_HEIGHT    224
#define IMAGE_WIDTH     224
#define IMAGE_CHANNELS    3
#define CONV1_FEATUREMAP_HEIGHT 112
#define CONV1_FEATUREMAP_WIDTH  112
#define CONV1_FILTERS       32

#define type    double

void _conv_block (
    const type input[],
    const type weights[],
    type output[], 
    int filters,
    const double alpha,
    const int kernel_size,
    const int stride
) {
    filters = (int)(filters*alpha);

    int base_y = IMAGE_CHANNELS*(IMAGE_WIDTH+2), base_x = 0;
    for (int k=0; k<CONV1_FEATUREMAP_HEIGHT; k++)
    {
        base_x = 1;
        for (int l=0; l<CONV1_FEATUREMAP_WIDTH; l++)
        {
            for (int i=0; i<kernel_size; i++)
            {
                for (int j=0; j<kernel_size; j++)
                {
                    for (int m=0; m<IMAGE_CHANNELS; m++)
                    {
                        int ii = i-1, jj = j-1;
                        int idx_i = (m)+(base_y)+(base_x)+(jj*IMAGE_CHANNELS)+(ii*IMAGE_CHANNELS*(IMAGE_WIDTH+2));
                        // printf("idx_i: %d, %d %d %d %d %d %d %d\n", idx_i, m, base_y, base_x, jj, ii, k, l);
                        // printf("(%d,%d, %d): image[%d] = %lf\n", ii, jj, m, idx_i, input[idx_i]);
                        
                        for (int n=0; n<filters; n++)
                        {
                            int idx_w = (n)+(m*filters)+(j*filters*IMAGE_CHANNELS)+(i*filters*IMAGE_CHANNELS*kernel_size);
                            int idx_out = (n)+(filters)*((CONV1_FEATUREMAP_WIDTH+2)*(i+1)+(j+1));
                            output[idx_out] += input[idx_i]*weights[idx_w];
                            // printf("(%d,%d, %d): image[%d] = %lf ", ii, jj, m, idx_i, input[idx_i]);
                            // printf("kernel[%d] = %lf\n", idx_w, weights[idx_w]);
                        }
                    }
                }
            }
            // return;
            base_x += stride*IMAGE_CHANNELS;
        }
        base_y += stride*IMAGE_CHANNELS*(IMAGE_WIDTH+2);
    }
}

int main()
{
    double *l1_output = calloc(
            (CONV1_FEATUREMAP_HEIGHT+2)*(CONV1_FEATUREMAP_WIDTH+2)*CONV1_FILTERS,
            sizeof(double));

    _conv_block (
       img,
       conv1,
       l1_output, 
       CONV1_FILTERS,
       1,   // alpha
       3,   // kernel_size
       2    // stride
    );

    // printf("(!) finished conv_1 operations\n");

    for (int i=1; i<=112; i++) 
    {
        for (int j=1; j<=112; j++) 
        {
            for (int k=0; k<32; k++)
            {
                printf("%lf\n", l1_output[(114*i+j)*32+k]);
            }
        }
    }

    free(l1_output);

    return 0;
}