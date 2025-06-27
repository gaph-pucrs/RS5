#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "c-dataset/image1.h"

#define IMAGE_CHANNELS  3
#define IMAGE_HEIGHT   32
#define IMAGE_WIDTH    32

//----------------------------
//      LMFRNet stages
//----------------------------
    #include "include/stage_1.h"
//

void pad (
    const int HEIGHT,
    const int WIDTH,
    const int CHANNELS,
    const type in[],
    type out[]
) {
    for (int i=0; i<HEIGHT; i++)
    {
        for (int j=0; j<WIDTH; j++)
        {
            for (int k=0; k<CHANNELS; k++)
            {
                int idx_in = (k)+(j*CHANNELS)+(i*CHANNELS*WIDTH);
                int idx_out = (k)+((j+1)*CHANNELS)+((i+1)*CHANNELS*(WIDTH+2));
                out[idx_out] = in[idx_in];
            }
        }
    }
}

type max (const type x, const type y) {
    return (x < y) ? y : x;
}

void relu (type in[], const int size) {
    for (int i=0; i<size; i++) {
        in[i] = max(in[i], 0);
    }
}

void batch_normalization (
    const int HEIGHT,
    const int WIDTH,
    const int CHANNELS,
    type in[],
    const type gamma[],
    const type beta[],
    const type mean[],
    const type var[],
    const type eps
) {
    for (int i=0; i<HEIGHT; i++) 
    {
        for (int j=0; j<WIDTH; j++) 
        {
            for (int n=0; n<CHANNELS; n++) 
            {
                int id = (n) + (j*CHANNELS) + (i*CHANNELS*WIDTH);
                in[id] -= mean[n];
                in[id] /= sqrt(var[n] + eps);
                in[id] *= gamma[n];
                in[id] += beta[n];
            }
        }
    }
}

void _conv_block (
    const int INPUT_WIDTH,
    const int INPUT_HEIGHT,
    const int INPUT_CHANNELS,
    const type in[],
    const type weights[],
    const type bias[],
    const int OUTPUT_WIDTH,
    const int OUTPUT_HEIGHT,
    const int OUTPUT_CHANNELS,
    type out[], 
    const int kernel_size,
    const int stride,
    const type gamma[],
    const type beta[],
    const type mean[],
    const type var[],
    const double eps
) {
    int p = (OUTPUT_WIDTH)-(int)((INPUT_WIDTH-kernel_size)/stride)-1;
    type *in_pd = calloc((INPUT_CHANNELS)*(INPUT_WIDTH+p)*(INPUT_HEIGHT+p), sizeof(type));

    if (p == 2) {
        pad (INPUT_HEIGHT, INPUT_WIDTH, INPUT_CHANNELS, in, in_pd);
    }

    // "(0,0)" of the 3x3 image
    int base_y=0, base_x=0;

    for (int k=0; k<OUTPUT_HEIGHT; k++)
    {
        base_x = 0;
        for (int l=0; l<OUTPUT_WIDTH; l++)
        {
            for (int i=0; i<kernel_size; i++)
            {
                for (int j=0; j<kernel_size; j++)
                {
                    for (int m=0; m<INPUT_CHANNELS; m++)
                    {
                        int idx_i = (m)+(base_x)+(base_y)+(j*INPUT_CHANNELS)+(i*INPUT_CHANNELS*(INPUT_WIDTH+p));
                        for (int n=0; n<OUTPUT_CHANNELS; n++)
                        {
                            int idx_w = (n)+(m*OUTPUT_CHANNELS)+(j*OUTPUT_CHANNELS*INPUT_CHANNELS)+(i*OUTPUT_CHANNELS*INPUT_CHANNELS*kernel_size);
                            int idx_out = (n)+(l*OUTPUT_CHANNELS)+(k*OUTPUT_CHANNELS*OUTPUT_WIDTH);
                            out[idx_out] += in_pd[idx_i]*weights[idx_w];
                        }
                    }
                }
            }
            base_x += stride*INPUT_CHANNELS;
        }
        base_y += stride*INPUT_CHANNELS*(INPUT_WIDTH+p);
    }

    for (int k=0; k<OUTPUT_HEIGHT; k++)
    {
        for (int l=0; l<OUTPUT_WIDTH; l++)
        {
            for (int n=0; n<OUTPUT_CHANNELS; n++)
            {
                out[(n)+(l*OUTPUT_CHANNELS)+(k*OUTPUT_CHANNELS*OUTPUT_WIDTH)] += bias[n];
            }
        }
    }

    batch_normalization (
        OUTPUT_HEIGHT,
        OUTPUT_WIDTH,
        OUTPUT_CHANNELS,
        out, 
        gamma, 
        beta, 
        mean, 
        var, 
        eps
    );

    relu(out, OUTPUT_HEIGHT*OUTPUT_WIDTH*OUTPUT_CHANNELS);

    free(in_pd);
}

void print(type v[], int size) {
    for (int i=0; i<size; i++) {
        printf("%.10f\n", v[i]);
    }
}

int main()
{
    type *stage_1_out = calloc(STAGE_1_WIDTH*STAGE_1_HEIGHT*STAGE_1_CHANNELS, sizeof(type));

    _conv_block (
        IMAGE_WIDTH,
        IMAGE_HEIGHT,
        IMAGE_CHANNELS,
        image1,
        stemBlock_stemConv_conv_weight,
        stemBlock_stemConv_conv_bias,
        STAGE_1_WIDTH,
        STAGE_1_HEIGHT,
        STAGE_1_CHANNELS,
        stage_1_out, 
        3,
        STAGE_1_STRIDE,
        stemBlock_stemConv_bn_gamma,
        stemBlock_stemConv_bn_beta,
        stemBlock_stemConv_bn_running_mean,
        stemBlock_stemConv_bn_running_var,
        1e-5
    );

    print(stage_1_out, STAGE_1_WIDTH*STAGE_1_HEIGHT*STAGE_1_CHANNELS);
    free(stage_1_out);

    return 0;
}
