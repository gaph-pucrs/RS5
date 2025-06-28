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
    #include "include/stage_2.h"
//

// full pad: adds a border of zeros
// {{{
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
// }}}

type max (const type x, const type y) {
    return (x < y) ? y : x;
}

void relu (type in[], const int size) {
    for (int i=0; i<size; i++) {
        in[i] = max(in[i], 0);
    }
}

// {{{
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
// }}}

// {{{
void _conv_block (
    const int INPUT_HEIGHT,
    const int INPUT_WIDTH,
    const int INPUT_CHANNELS,
    const type in[],
    const type weights[],
    const type bias[],
    const int OUTPUT_HEIGHT,
    const int OUTPUT_WIDTH,
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

    //printf("padding: %d\n", p);
    if (p == 2) {
        pad (INPUT_HEIGHT, INPUT_WIDTH, INPUT_CHANNELS, in, in_pd);
    }
    else {
        // no padding
        for (int i=0; i<INPUT_HEIGHT*INPUT_WIDTH*INPUT_CHANNELS; i++) {
            in_pd[i] = in[i];
        }
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
    
    if (bias != NULL)
    {
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
// }}}

// cooncatenate 4 tensors (MFBlock filter concatenation)
//{{{
void concat4 (
    const int H,
    const int W,
    const int CH0,
    const int CH1,
    const int CH2,
    const int CH3,
    const type *v0,
    const type *v1,
    const type *v2,
    const type *v3,
    type *out
) {
    int C = CH0 + CH1 + CH2 + CH3;
    for (int i=0; i<H; i++)
    {
        for (int j=0; j<W; j++)
        {
            int offset = 0;
            for (int k=0; k<CH0; k++) {
                out[k + j*C + i*C*W] = v0[k + j*CH0 + i*CH0*W];
            }
            offset += CH0;
            for (int k=0; k<CH0; k++) {
                out[k + offset + j*C + i*C*W] = v1[k + j*CH1 + i*CH1*W];
            }

            offset += CH1;
            for (int k=0; k<CH0; k++) {
                out[k + offset + j*C + i*C*W] = v2[k + j*CH2 + i*CH2*W];
            }

            offset += CH2;
            for (int k=0; k<CH0; k++) {
                out[k + offset + j*C + i*C*W] = v3[k + j*CH3 + i*CH3*W];
            }
        }
    }
}
//}}}

void print(type v[], int size) {
    for (int i=0; i<size; i++) {
        printf("%.10f\n", v[i]);
    }
}

int main()
{
//-------------------------------------------
//                STAGE_1
//-------------------------------------------
    //{{{
    type *stage_1_out = calloc(STAGE_1_WIDTH*STAGE_1_HEIGHT*STAGE_1_CHANNELS, sizeof(type));

    _conv_block (
        IMAGE_HEIGHT,
        IMAGE_WIDTH,
        IMAGE_CHANNELS,
        image1,
        stemBlock_stemConv_conv_weight,
        stemBlock_stemConv_conv_bias,
        STAGE_1_HEIGHT,
        STAGE_1_WIDTH,
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
    //}}}

//    print(stage_1_out, STAGE_1_WIDTH*STAGE_1_HEIGHT*STAGE_1_CHANNELS);

//-------------------------------------------
//              STAGE_2
//-------------------------------------------
    //-----------------------------------------------
    //                  Layer1
    //-----------------------------------------------
        //{{{
        type *y0 = calloc(12*32*32, sizeof(type)); 
        type *y1 = calloc(12*32*32, sizeof(type));    
        type *y2 = calloc(6*32*32, sizeof(type));    
        type *y3 = calloc(6*32*32, sizeof(type));    
        type *MMCBlock1_mmLayer1_out = calloc(56*32*32, sizeof(type));

        _conv_block (
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            STAGE_1_CHANNELS,
            stage_1_out,
            MMCBlock1_mmLayer1_branch11_conv_weight,
            NULL,
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer1_branch11_CHANNELS,
            y0,
            1,
            1,
            MMCBlock1_mmLayer1_branch11_bn_gamma,
            MMCBlock1_mmLayer1_branch11_bn_beta,
            MMCBlock1_mmLayer1_branch11_bn_running_mean,
            MMCBlock1_mmLayer1_branch11_bn_running_var,
            1e-5
        );

        _conv_block (
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer1_branch11_CHANNELS,
            y0,
            MMCBlock1_mmLayer1_branch33a_conv_weight,
            NULL,
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer1_branch33a_CHANNELS,
            y1,
            3,
            1,
            MMCBlock1_mmLayer1_branch33a_bn_gamma,
            MMCBlock1_mmLayer1_branch33a_bn_beta,
            MMCBlock1_mmLayer1_branch33a_bn_running_mean,
            MMCBlock1_mmLayer1_branch33a_bn_running_var,
            1e-5
        );

        _conv_block (
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer1_branch33a_CHANNELS,
            y1,
            MMCBlock1_mmLayer1_branch33b_conv_weight,
            NULL,
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer1_branch33b_CHANNELS,
            y2,
            3,
            1,
            MMCBlock1_mmLayer1_branch33b_bn_gamma,
            MMCBlock1_mmLayer1_branch33b_bn_beta,
            MMCBlock1_mmLayer1_branch33b_bn_running_mean,
            MMCBlock1_mmLayer1_branch33b_bn_running_var,
            1e-5
        );

        _conv_block (
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer1_branch33b_CHANNELS,
            y2,
            MMCBlock1_mmLayer1_branch33c_conv_weight,
            NULL,
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer1_branch33c_CHANNELS,
            y3,
            3,
            1,
            MMCBlock1_mmLayer1_branch33c_bn_gamma,
            MMCBlock1_mmLayer1_branch33c_bn_beta,
            MMCBlock1_mmLayer1_branch33c_bn_running_mean,
            MMCBlock1_mmLayer1_branch33c_bn_running_var,
            1e-5
        );

        // concat em MMCBlock1_mmLayer1_out
        concat4 (
            32, 
            32, 
            32,
            12,
            6,
            6,
            stage_1_out, 
            y1, 
            y2, 
            y3, 
            MMCBlock1_mmLayer1_out
        );

        free(stage_1_out);
        free(y0);
        free(y1);
        free(y2);
        free(y3);
        //}}} 

    //-----------------------------------------------
    //                  Layer2
    //-----------------------------------------------
        //{{{
        y0 = calloc(12*32*32, sizeof(type)); 
        y1 = calloc(12*32*32, sizeof(type));    
        y2 = calloc(6*32*32, sizeof(type));    
        y3 = calloc(6*32*32, sizeof(type));    
        type *MMCBlock1_mmLayer2_out = calloc(80*32*32, sizeof(type));

        _conv_block (
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer1_CHANNELS,
            MMCBlock1_mmLayer1_out,
            MMCBlock1_mmLayer2_branch11_conv_weight,
            NULL,
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer2_branch11_CHANNELS,
            y0,
            1,
            1,
            MMCBlock1_mmLayer2_branch11_bn_gamma,
            MMCBlock1_mmLayer2_branch11_bn_beta,
            MMCBlock1_mmLayer2_branch11_bn_running_mean,
            MMCBlock1_mmLayer2_branch11_bn_running_var,
            1e-5
        );

        _conv_block (
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer2_branch11_CHANNELS,
            y0,
            MMCBlock1_mmLayer2_branch33a_conv_weight,
            NULL,
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer2_branch33a_CHANNELS,
            y1,
            3,
            1,
            MMCBlock1_mmLayer2_branch33a_bn_gamma,
            MMCBlock1_mmLayer2_branch33a_bn_beta,
            MMCBlock1_mmLayer2_branch33a_bn_running_mean,
            MMCBlock1_mmLayer2_branch33a_bn_running_var,
            1e-5
        );

        _conv_block (
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer2_branch33a_CHANNELS,
            y1,
            MMCBlock1_mmLayer2_branch33b_conv_weight,
            NULL,
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer2_branch33b_CHANNELS,
            y2,
            3,
            1,
            MMCBlock1_mmLayer2_branch33b_bn_gamma,
            MMCBlock1_mmLayer2_branch33b_bn_beta,
            MMCBlock1_mmLayer2_branch33b_bn_running_mean,
            MMCBlock1_mmLayer2_branch33b_bn_running_var,
            1e-5
        );

        _conv_block (
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer2_branch33b_CHANNELS,
            y2,
            MMCBlock1_mmLayer2_branch33c_conv_weight,
            NULL,
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer2_branch33c_CHANNELS,
            y3,
            3,
            1,
            MMCBlock1_mmLayer2_branch33c_bn_gamma,
            MMCBlock1_mmLayer2_branch33c_bn_beta,
            MMCBlock1_mmLayer2_branch33c_bn_running_mean,
            MMCBlock1_mmLayer2_branch33c_bn_running_var,
            1e-5
        );

        // concat em MMCBlock1_mmLayer2_out
        concat4 (
            32, 
            32, 
            56,
            12,
            6,
            6,
            MMCBlock1_mmLayer1_out, 
            y1, 
            y2, 
            y3, 
            MMCBlock1_mmLayer2_out
        );

        free(MMCBlock1_mmLayer1_out);
        free(y0);
        free(y1);
        free(y2);
        free(y3);
        //}}}

    //-----------------------------------------------
    //                  Layer3
    //-----------------------------------------------
        //{{{
        y0 = calloc(12*32*32, sizeof(type)); 
        y1 = calloc(12*32*32, sizeof(type));    
        y2 = calloc(6*32*32, sizeof(type));    
        y3 = calloc(6*32*32, sizeof(type));    
        type *MMCBlock1_mmLayer3_out = calloc(104*32*32, sizeof(type));

        _conv_block (
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer2_CHANNELS,
            MMCBlock1_mmLayer2_out,
            MMCBlock1_mmLayer3_branch11_conv_weight,
            NULL,
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer3_branch11_CHANNELS,
            y0,
            1,
            1,
            MMCBlock1_mmLayer3_branch11_bn_gamma,
            MMCBlock1_mmLayer3_branch11_bn_beta,
            MMCBlock1_mmLayer3_branch11_bn_running_mean,
            MMCBlock1_mmLayer3_branch11_bn_running_var,
            1e-5
        );

        _conv_block (
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer3_branch11_CHANNELS,
            y0,
            MMCBlock1_mmLayer3_branch33a_conv_weight,
            NULL,
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer3_branch33a_CHANNELS,
            y1,
            3,
            1,
            MMCBlock1_mmLayer3_branch33a_bn_gamma,
            MMCBlock1_mmLayer3_branch33a_bn_beta,
            MMCBlock1_mmLayer3_branch33a_bn_running_mean,
            MMCBlock1_mmLayer3_branch33a_bn_running_var,
            1e-5
        );

        _conv_block (
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer3_branch33a_CHANNELS,
            y1,
            MMCBlock1_mmLayer3_branch33b_conv_weight,
            NULL,
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer3_branch33b_CHANNELS,
            y2,
            3,
            1,
            MMCBlock1_mmLayer3_branch33b_bn_gamma,
            MMCBlock1_mmLayer3_branch33b_bn_beta,
            MMCBlock1_mmLayer3_branch33b_bn_running_mean,
            MMCBlock1_mmLayer3_branch33b_bn_running_var,
            1e-5
        );

        _conv_block (
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer3_branch33b_CHANNELS,
            y2,
            MMCBlock1_mmLayer3_branch33c_conv_weight,
            NULL,
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            MMCBlock1_mmLayer3_branch33c_CHANNELS,
            y3,
            3,
            1,
            MMCBlock1_mmLayer3_branch33c_bn_gamma,
            MMCBlock1_mmLayer3_branch33c_bn_beta,
            MMCBlock1_mmLayer3_branch33c_bn_running_mean,
            MMCBlock1_mmLayer3_branch33c_bn_running_var,
            1e-5
        );

        // concat em MMCBlock1_mmLayer2_out
        concat4 (
            32, 
            32, 
            80,
            12,
            6,
            6,
            MMCBlock1_mmLayer2_out, 
            y1, 
            y2, 
            y3, 
            MMCBlock1_mmLayer3_out
        );

        free(MMCBlock1_mmLayer2_out);
        free(y0);
        free(y1);
        free(y2);
        free(y3);

        print(MMCBlock1_mmLayer3_out, 32*32*104);
        //}}}




    // concat(x, y1, y2, y3)

    free(stage_1_out);

    return 0;
}
