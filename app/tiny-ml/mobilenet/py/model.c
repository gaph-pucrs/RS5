#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "params/data.h"
//------------------------------
// LAYER1
#include "params/conv1.h"
#include "params/conv1_bn_avg.h"
#include "params/conv1_bn_var.h"
#include "params/conv1_bn_gamma.h"
#include "params/conv1_bn_beta.h"
#include "params/conv1_bn_eps.h"

#define INPUT_HEIGHT    224
#define INPUT_WIDTH     224
#define INPUT_CHANNELS    3
#define CONV1_FEATUREMAP_HEIGHT 112
#define CONV1_FEATUREMAP_WIDTH  112
#define CONV1_FILTERS       32

#define type    double

void batch_normalization (
    const int filters,
    const int size,
    type input[],
    const type mean[],
    const type var[],
    const type gamma[],
    const type beta[],
    const double eps
) {
    for (int i=0; i<CONV1_FEATUREMAP_HEIGHT; i++) {
        for (int j=0; j<CONV1_FEATUREMAP_WIDTH; j++) {
            for (int n=0; n<CONV1_FILTERS; n++) {
                int id = n + j*CONV1_FILTERS + i*CONV1_FILTERS*CONV1_FEATUREMAP_WIDTH;
                input[id] -= mean[n];
                input[id] /= sqrt(var[n] + eps);
                input[id] *= gamma[n];
                input[id] += beta[n];
            }
        }
    }
}

void _conv_block2 (
    const type input[],
    const type weights[],
    type output[], 
    int filters,
    const double alpha,
    const int kernel_size,
    const int stride,
    const type mean[],
    const type var[],
    const type gamma[],
    const type beta[],
    const double eps
) {
    filters = (int)(filters*alpha);

    int base_y=0, base_x=0;

    for (int k=0; k<CONV1_FEATUREMAP_HEIGHT; k++)
    {
        //printf("k: %d\n", k);
        for (int l=0; l<CONV1_FEATUREMAP_WIDTH; l++)
        {
            for (int i=0; i<INPUT_HEIGHT; i++)
            {
                for (int j=0; j<INPUT_WIDTH; j++)
                {
                    for (int m=0; m<INPUT_CHANNELS; m++)
                    {
                        for (int n=0; n<filters; n++)
                        {
                            output[k*filters*CONV1_FEATUREMAP_WIDTH+l+n] += input[m+j*3+i*3*INPUT_WIDTH]*weights[n+m*32];
                            // BE CAREFUL WITH THIS PRINTF
                            //printf("output[%d] = input[%d] * weights[%d] : %lf = %lf * \%lf\n", n, m+j*3+i*3*INPUT_WIDTH, n+m*32, output[n], input[m+j*3+i*3*INPUT_WIDTH], weights[n+m*32]);
                        }
                    }
                }
            }
            base_x += stride;
        }
        base_y += 3*stride*INPUT_WIDTH;
    }
    const int size = CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH;
    batch_normalization(filters, size, output, mean, var, gamma, beta, eps);
}

int main()
{
    
    double *output = malloc(CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH*CONV1_FILTERS*sizeof(double));

    _conv_block2 (
       img,
       conv1,
       output, 
       CONV1_FILTERS,
       1,
       3,
       2,
       conv1_bn_avg,
       conv1_bn_var,
       conv1_bn_gamma,
       conv1_bn_beta,
       conv1_bn_eps
    );

    const int size = CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH*CONV1_FILTERS;

    for (int i=0; i<5; i++) {
        printf("%lf\n", output[i]);
    }

    free(output);

    return 0;
}
