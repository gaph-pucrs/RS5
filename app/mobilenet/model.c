#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include <math.h>

#include "params/data.h"
#include "layers.h"
#include "weights.h"

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
                printf("%.10lf\n", in[idx]);
            }
        }
    }
    
    printf("\n");
}

// full pad (border of 0's)
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
                int idx_i = (k)+(j*CHANNELS)+(i*CHANNELS*WIDTH); 
                int idx_out = (k)+((j+1)*(CHANNELS))+((i+1)*(CHANNELS)*(WIDTH+2));
                out[idx_out] = in[idx_i];
            }
        }
    }
}

// adds 1 dimension to the right and bottom
void half_pad (
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
                int idx_out = (k)+((j)*(CHANNELS))+((i)*(CHANNELS)*(WIDTH+1));
                out[idx_out] = in[idx_in];
            }
        }
    }
}

// mobilenet functions
void batch_normalization (
    const int HEIGHT,
    const int WIDTH,
    const int CHANNELS,
    type in[],
    const type mean[],
    const type var[],
    const type gamma[],
    const type beta[],
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

void relu (
    const type max,
    type in[],
    const int size
) {
    for (int i=0; i<size; i++) {
        in[i] = clamp(in[i], max, 0);
    }
}

void avg_pooling (
    const int HEIGHT,
    const int WIDTH,
    const int CHANNELS,
    const type *in,
    type *out
) {
    for (int h=0; h<HEIGHT; h++) 
    {
        for (int w=0; w<WIDTH; w++)
        {
            for (int c=0; c<CHANNELS; c++)
            {
                out[c] += in[(c)+(w*CHANNELS)+(h*CHANNELS*WIDTH)];
            }
        }
    }

    for (int c=0; c<CHANNELS; c++) {
        out[c] /= HEIGHT*WIDTH;
    }
}

void softmax (
    const int len,
    const type in[],
    type out[]
) {
    type sum = 0;
    for (int i=0; i<len; i++) {
        sum += exp(in[i]);
    }

    for (int i=0; i<len; i++) {
        out[i] = exp(in[i])/sum;
    }
}

void _conv_block (
    const int INPUT_HEIGHT,
    const int INPUT_WIDTH,
    const int INPUT_CHANNELS,
    const type in[],
    const type weights[],
    const int OUTPUT_HEIGHT,
    const int OUTPUT_WIDTH,
    const int OUTPUT_CHANNELS,
    type out[], 
    const int kernel_size,
    const int stride,
    const type mean[],
    const type var[],
    const type gamma[],
    const type beta[],
    const double eps
) {
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
                        int idx_i = (m)+(base_x)+(base_y)+(j*INPUT_CHANNELS)+(i*INPUT_CHANNELS*INPUT_WIDTH);
                        for (int n=0; n<OUTPUT_CHANNELS; n++)
                        {
                            int idx_w = (n)+(m*OUTPUT_CHANNELS)+(j*OUTPUT_CHANNELS*INPUT_CHANNELS)+(i*OUTPUT_CHANNELS*INPUT_CHANNELS*kernel_size);
                            int idx_out = (n)+(l*OUTPUT_CHANNELS)+(k*OUTPUT_CHANNELS*OUTPUT_WIDTH);
                            out[idx_out] += in[idx_i]*weights[idx_w];
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
            OUTPUT_HEIGHT,
            OUTPUT_WIDTH,
            OUTPUT_CHANNELS,
            out, 
            mean, 
            var, 
            gamma, 
            beta, 
            eps
        );
    #endif

    relu(6.0, out, OUTPUT_HEIGHT*OUTPUT_WIDTH*OUTPUT_CHANNELS);
}

void _depthwise_conv_block (
    const int INPUT_HEIGHT,
    const int INPUT_WIDTH,
    const int INPUT_CHANNELS,
    const type in[],
    const type weights[],
    const int OUTPUT_HEIGHT,
    const int OUTPUT_WIDTH,
    const int OUTPUT_CHANNELS,
    type out[],
    const int kernel_size,
    const int stride,
    const type mean[],
    const type var[],
    const type gamma[],
    const type beta[],
    const double eps
) {    
    const int p = (OUTPUT_WIDTH) - (int)((INPUT_WIDTH-kernel_size)/stride) - 1;
    type *in_pd = calloc((INPUT_CHANNELS)*(INPUT_WIDTH+p)*(INPUT_HEIGHT+p), sizeof(type));
    
    if (p == 1) {
        half_pad(INPUT_HEIGHT, INPUT_WIDTH, INPUT_CHANNELS, in, in_pd);
    }
    else if (p == 2) {
        pad(INPUT_HEIGHT, INPUT_WIDTH, INPUT_CHANNELS, in, in_pd);
    }
    
    int base_y = 0, base_x = 0;
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
                        int idx_i = (m)+(base_y)+(base_x)+(j*INPUT_CHANNELS)+(i*INPUT_CHANNELS*(INPUT_WIDTH+p));
                        int idx_w = (m)+(j*OUTPUT_CHANNELS)+(i*OUTPUT_CHANNELS*kernel_size);
                        int idx_out = (m)+(l*OUTPUT_CHANNELS)+(k*OUTPUT_CHANNELS*OUTPUT_WIDTH);
                        out[idx_out] += in_pd[idx_i]*weights[idx_w];
                    }
                }
            }
            base_x += (stride)*(INPUT_CHANNELS);
        }
        base_y += (stride)*(INPUT_CHANNELS)*(INPUT_WIDTH+p);
    }

    #ifdef BATCHNORMALIZATION
        batch_normalization (
            OUTPUT_HEIGHT,
            OUTPUT_WIDTH,
            OUTPUT_CHANNELS,
            out, 
            mean, 
            var, 
            gamma, 
            beta, 
            eps
        );
    #endif

    
    relu(6.0, out, OUTPUT_HEIGHT*OUTPUT_WIDTH*OUTPUT_CHANNELS);

    free(in_pd);
}

void _pointwise_conv_block (
    const int INPUT_HEIGHT,
    const int INPUT_WIDTH,
    const int INPUT_CHANNELS,
    const type in[],
    const type weights[],
    const int OUTPUT_HEIGHT,
    const int OUTPUT_WIDTH,
    const int OUTPUT_CHANNELS,
    type out[],
    const type mean[],
    const type var[],
    const type gamma[],
    const type beta[],
    const double eps
) {
    _conv_block (
        INPUT_HEIGHT,
        INPUT_WIDTH,
        INPUT_CHANNELS,
        in,
        weights,
        OUTPUT_HEIGHT,
        OUTPUT_WIDTH,
        OUTPUT_CHANNELS,
        out,
        1,
        1,
        mean,
        var,
        gamma,
        beta,
        eps
    );
}

void _fc (
    const int INPUT_CHANNELS,
    const type in[],
    const type weights[],
    const type bias[],
    const int NEURONS,
    type out[]
) {
    for (int ch=0; ch<INPUT_CHANNELS; ch++)
    {
        for (int n=0; n<NEURONS; n++)
        {
            out[n] += in[ch]*weights[(n)+((ch)*NEURONS)];
        }
    }

    for (int n=0; n<NEURONS; n++) {
        out[n] += bias[n];
    }
}

int main()
{
//------------------------------
//          CONV 1
//------------------------------
    type *img_padded = calloc((IMAGE_CHANNELS)*(IMAGE_WIDTH+1)*(IMAGE_HEIGHT+1), sizeof(type));
    type *conv1_out = calloc(CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH*CONV1_FILTERS, sizeof(type));

    half_pad (
        IMAGE_HEIGHT,
        IMAGE_WIDTH,
        IMAGE_CHANNELS,
        img,
        img_padded
    );

    _conv_block (
        IMAGE_HEIGHT+1,
        IMAGE_WIDTH+1,
        IMAGE_CHANNELS,
        img_padded,
        conv1,
        CONV1_FEATUREMAP_HEIGHT,
        CONV1_FEATUREMAP_WIDTH,
        CONV1_FILTERS,
        conv1_out, 
        3,   // kernel_size
        CONV1_STRIDE,
        conv1_bn_mean,
        conv1_bn_var,
        conv1_bn_gamma,
        conv1_bn_beta,
        conv1_bn_eps
    );

    free(img_padded);

//------------------------------
//          BLOCK 1
//------------------------------
    type *conv_dw_1_out = calloc(CONV_DW_1_CHANNELS*CONV_DW_1_WIDTH*CONV_DW_1_HEIGHT, sizeof(type));    
    type *conv_pw_1_out = calloc(CONV_PW_1_CHANNELS*CONV_PW_1_WIDTH*CONV_PW_1_HEIGHT, sizeof(type));
    
    _depthwise_conv_block (
        CONV1_FEATUREMAP_HEIGHT,
        CONV1_FEATUREMAP_WIDTH,
        CONV1_FILTERS,
        conv1_out,
        conv_dw_1,
        CONV_DW_1_HEIGHT,
        CONV_DW_1_WIDTH,
        CONV_DW_1_CHANNELS,
        conv_dw_1_out,
        3,      // kernel_size,
        CONV_DW_1_STRIDE,      
        conv_dw_1_bn_mean,
        conv_dw_1_bn_var,
        conv_dw_1_bn_gamma,
        conv_dw_1_bn_beta,
        conv_dw_1_bn_eps
    );

    _pointwise_conv_block (
        CONV_DW_1_HEIGHT,
        CONV_DW_1_WIDTH,
        CONV_DW_1_CHANNELS,
        conv_dw_1_out,
        conv_pw_1,
        CONV_PW_1_HEIGHT,
        CONV_PW_1_WIDTH,
        CONV_PW_1_CHANNELS,
        conv_pw_1_out,
        conv_pw_1_bn_mean,
        conv_pw_1_bn_var,
        conv_pw_1_bn_gamma,
        conv_pw_1_bn_beta,
        conv_pw_1_bn_eps
    ); 

    free(conv1_out);
    free(conv_dw_1_out);

//------------------------------
//          BLOCK 2
//------------------------------
    type *conv_dw_2_out = calloc((CONV_DW_2_CHANNELS)*(CONV_DW_2_HEIGHT)*(CONV_DW_2_WIDTH), sizeof(type));
    type *conv_pw_2_out = calloc(CONV_PW_2_CHANNELS*CONV_PW_2_WIDTH*CONV_PW_2_HEIGHT, sizeof(type));

    _depthwise_conv_block (
        CONV_PW_1_HEIGHT,
        CONV_PW_1_WIDTH,
        CONV_PW_1_CHANNELS,
        conv_pw_1_out,
        conv_dw_2,
        CONV_DW_2_HEIGHT,
        CONV_DW_2_WIDTH,
        CONV_DW_2_CHANNELS,
        conv_dw_2_out,
        3,      // kernel_size
        CONV_DW_2_STRIDE,
        conv_dw_2_bn_mean,
        conv_dw_2_bn_var,
        conv_dw_2_bn_gamma,
        conv_dw_2_bn_beta,
        conv_dw_2_bn_eps
    );

    _pointwise_conv_block (
        CONV_DW_2_HEIGHT,
        CONV_DW_2_WIDTH,
        CONV_DW_2_CHANNELS,
        conv_dw_2_out,
        conv_pw_2,
        CONV_PW_2_HEIGHT,
        CONV_PW_2_WIDTH,
        CONV_PW_2_CHANNELS,
        conv_pw_2_out,
        conv_pw_2_bn_mean,
        conv_pw_2_bn_var,
        conv_pw_2_bn_gamma,
        conv_pw_2_bn_beta,
        conv_pw_2_bn_eps
    ); 

    free(conv_pw_1_out);
    free(conv_dw_2_out);

//------------------------------
//          BLOCK 3
//------------------------------
    type *conv_dw_3_out = calloc((CONV_DW_3_CHANNELS)*(CONV_DW_3_HEIGHT)*(CONV_DW_3_WIDTH), sizeof(type));
    type *conv_pw_3_out = calloc(CONV_PW_3_CHANNELS*CONV_PW_3_WIDTH*CONV_PW_3_HEIGHT, sizeof(type));
    
    _depthwise_conv_block (
        CONV_PW_2_HEIGHT,
        CONV_PW_2_WIDTH,
        CONV_PW_2_CHANNELS,
        conv_pw_2_out,
        conv_dw_3,
        CONV_DW_3_HEIGHT,
        CONV_DW_3_WIDTH,
        CONV_DW_3_CHANNELS,
        conv_dw_3_out,
        3,      // kernel_size
        CONV_DW_3_STRIDE, 
        conv_dw_3_bn_mean,
        conv_dw_3_bn_var,
        conv_dw_3_bn_gamma,
        conv_dw_3_bn_beta,
        conv_dw_3_bn_eps
    );
    
    _pointwise_conv_block (
        CONV_DW_3_HEIGHT,
        CONV_DW_3_WIDTH,
        CONV_DW_3_CHANNELS,
        conv_dw_3_out,
        conv_pw_3,
        CONV_PW_3_HEIGHT,
        CONV_PW_3_WIDTH,
        CONV_PW_3_CHANNELS,
        conv_pw_3_out,
        conv_pw_3_bn_mean,
        conv_pw_3_bn_var,
        conv_pw_3_bn_gamma,
        conv_pw_3_bn_beta,
        conv_pw_3_bn_eps
    ); 

    free(conv_pw_2_out);
    free(conv_dw_3_out);

//------------------------------
//          BLOCK 4
//------------------------------
    type *conv_dw_4_out = calloc((CONV_DW_4_CHANNELS)*(CONV_DW_4_HEIGHT)*(CONV_DW_4_WIDTH), sizeof(type));
    type *conv_pw_4_out = calloc(CONV_PW_4_CHANNELS*CONV_PW_4_WIDTH*CONV_PW_4_HEIGHT, sizeof(type));
    
    _depthwise_conv_block (
        CONV_PW_3_HEIGHT,
        CONV_PW_3_WIDTH,
        CONV_PW_3_CHANNELS,
        conv_pw_3_out,
        conv_dw_4,
        CONV_DW_4_HEIGHT,
        CONV_DW_4_WIDTH,
        CONV_DW_4_CHANNELS,
        conv_dw_4_out,
        3,      // kernel_size
        CONV_DW_4_STRIDE,   
        conv_dw_4_bn_mean,
        conv_dw_4_bn_var,
        conv_dw_4_bn_gamma,
        conv_dw_4_bn_beta,
        conv_dw_4_bn_eps
    );
    
    _pointwise_conv_block (
        CONV_DW_4_HEIGHT,
        CONV_DW_4_WIDTH,
        CONV_DW_4_CHANNELS,
        conv_dw_4_out,
        conv_pw_4,
        CONV_PW_4_HEIGHT,
        CONV_PW_4_WIDTH,
        CONV_PW_4_CHANNELS,
        conv_pw_4_out,
        conv_pw_4_bn_mean,
        conv_pw_4_bn_var,
        conv_pw_4_bn_gamma,
        conv_pw_4_bn_beta,
        conv_pw_4_bn_eps
    ); 

    free(conv_pw_3_out);
    free(conv_dw_4_out);


//------------------------------
//          BLOCK 5
//------------------------------
    type *conv_dw_5_out = calloc((CONV_DW_5_CHANNELS)*(CONV_DW_5_HEIGHT)*(CONV_DW_5_WIDTH), sizeof(type));
    type *conv_pw_5_out = calloc(CONV_PW_5_CHANNELS*CONV_PW_5_WIDTH*CONV_PW_5_HEIGHT, sizeof(type));

    _depthwise_conv_block (
        CONV_PW_4_HEIGHT,
        CONV_PW_4_WIDTH,
        CONV_PW_4_CHANNELS,
        conv_pw_4_out,
        conv_dw_5,
        CONV_DW_5_HEIGHT,
        CONV_DW_5_WIDTH,
        CONV_DW_5_CHANNELS,
        conv_dw_5_out,
        3,      // kernel_size
        CONV_DW_5_STRIDE,   
        conv_dw_5_bn_mean,
        conv_dw_5_bn_var,
        conv_dw_5_bn_gamma,
        conv_dw_5_bn_beta,
        conv_dw_5_bn_eps
    );

    _pointwise_conv_block (
        CONV_DW_5_HEIGHT,
        CONV_DW_5_WIDTH,
        CONV_DW_5_CHANNELS,
        conv_dw_5_out,
        conv_pw_5,
        CONV_PW_5_HEIGHT,
        CONV_PW_5_WIDTH,
        CONV_PW_5_CHANNELS,
        conv_pw_5_out,
        conv_pw_5_bn_mean,
        conv_pw_5_bn_var,
        conv_pw_5_bn_gamma,
        conv_pw_5_bn_beta,
        conv_pw_5_bn_eps
    ); 

    free(conv_pw_4_out);
    free(conv_dw_5_out);


//------------------------------
//          BLOCK 6
//------------------------------
    type *conv_dw_6_out = calloc((CONV_DW_6_CHANNELS)*(CONV_DW_6_HEIGHT)*(CONV_DW_6_WIDTH), sizeof(type));
    type *conv_pw_6_out = calloc(CONV_PW_6_CHANNELS*CONV_PW_6_WIDTH*CONV_PW_6_HEIGHT, sizeof(type));

    _depthwise_conv_block (
        CONV_PW_5_HEIGHT,
        CONV_PW_5_WIDTH,
        CONV_PW_5_CHANNELS,
        conv_pw_5_out,
        conv_dw_6,
        CONV_DW_6_HEIGHT,
        CONV_DW_6_WIDTH,
        CONV_DW_6_CHANNELS,
        conv_dw_6_out,
        3,      // kernel_size
        CONV_DW_6_STRIDE,   
        conv_dw_6_bn_mean,
        conv_dw_6_bn_var,
        conv_dw_6_bn_gamma,
        conv_dw_6_bn_beta,
        conv_dw_6_bn_eps
    );

    _pointwise_conv_block (
        CONV_DW_6_HEIGHT,
        CONV_DW_6_WIDTH,
        CONV_DW_6_CHANNELS,
        conv_dw_6_out,
        conv_pw_6,
        CONV_PW_6_HEIGHT,
        CONV_PW_6_WIDTH,
        CONV_PW_6_CHANNELS,
        conv_pw_6_out,
        conv_pw_6_bn_mean,
        conv_pw_6_bn_var,
        conv_pw_6_bn_gamma,
        conv_pw_6_bn_beta,
        conv_pw_6_bn_eps
    ); 

    free(conv_pw_5_out);
    free(conv_dw_6_out);

//------------------------------
//          BLOCK 7
//------------------------------
    type *conv_dw_7_out = calloc((CONV_DW_7_CHANNELS)*(CONV_DW_7_HEIGHT)*(CONV_DW_7_WIDTH), sizeof(type));
    type *conv_pw_7_out = calloc(CONV_PW_7_CHANNELS*CONV_PW_7_WIDTH*CONV_PW_7_HEIGHT, sizeof(type));

    _depthwise_conv_block (
        CONV_PW_6_HEIGHT,
        CONV_PW_6_WIDTH,
        CONV_PW_6_CHANNELS,
        conv_pw_6_out,
        conv_dw_7,
        CONV_DW_7_HEIGHT,
        CONV_DW_7_WIDTH,
        CONV_DW_7_CHANNELS,
        conv_dw_7_out,
        3,      // kernel_size
        CONV_DW_7_STRIDE,   
        conv_dw_7_bn_mean,
        conv_dw_7_bn_var,
        conv_dw_7_bn_gamma,
        conv_dw_7_bn_beta,
        conv_dw_7_bn_eps
    );

    _pointwise_conv_block (
        CONV_DW_7_HEIGHT,
        CONV_DW_7_WIDTH,
        CONV_DW_7_CHANNELS,
        conv_dw_7_out,
        conv_pw_7,
        CONV_PW_7_HEIGHT,
        CONV_PW_7_WIDTH,
        CONV_PW_7_CHANNELS,
        conv_pw_7_out,
        conv_pw_7_bn_mean,
        conv_pw_7_bn_var,
        conv_pw_7_bn_gamma,
        conv_pw_7_bn_beta,
        conv_pw_7_bn_eps
    ); 

    free(conv_pw_6_out);
    free(conv_dw_7_out);
    
//------------------------------
//          BLOCK 8
//------------------------------
    type *conv_dw_8_out = calloc((CONV_DW_8_CHANNELS)*(CONV_DW_8_HEIGHT)*(CONV_DW_8_WIDTH), sizeof(type));
    type *conv_pw_8_out = calloc(CONV_PW_8_CHANNELS*CONV_PW_8_WIDTH*CONV_PW_8_HEIGHT, sizeof(type));

    _depthwise_conv_block (
        CONV_PW_7_HEIGHT,
        CONV_PW_7_WIDTH,
        CONV_PW_7_CHANNELS,
        conv_pw_7_out,
        conv_dw_8,
        CONV_DW_8_HEIGHT,
        CONV_DW_8_WIDTH,
        CONV_DW_8_CHANNELS,
        conv_dw_8_out,
        3,      // kernel_size
        CONV_DW_8_STRIDE,   
        conv_dw_8_bn_mean,
        conv_dw_8_bn_var,
        conv_dw_8_bn_gamma,
        conv_dw_8_bn_beta,
        conv_dw_8_bn_eps
    );

    _pointwise_conv_block (
        CONV_DW_8_HEIGHT,
        CONV_DW_8_WIDTH,
        CONV_DW_8_CHANNELS,
        conv_dw_8_out,
        conv_pw_8,
        CONV_PW_8_HEIGHT,
        CONV_PW_8_WIDTH,
        CONV_PW_8_CHANNELS,
        conv_pw_8_out,
        conv_pw_8_bn_mean,
        conv_pw_8_bn_var,
        conv_pw_8_bn_gamma,
        conv_pw_8_bn_beta,
        conv_pw_8_bn_eps
    ); 

    free(conv_pw_7_out);
    free(conv_dw_8_out);

//------------------------------
//          BLOCK 9
//------------------------------
    type *conv_dw_9_out = calloc((CONV_DW_9_CHANNELS)*(CONV_DW_9_HEIGHT)*(CONV_DW_9_WIDTH), sizeof(type));
    type *conv_pw_9_out = calloc(CONV_PW_9_CHANNELS*CONV_PW_9_WIDTH*CONV_PW_9_HEIGHT, sizeof(type));

    _depthwise_conv_block (
        CONV_PW_8_HEIGHT,
        CONV_PW_8_WIDTH,
        CONV_PW_8_CHANNELS,
        conv_pw_8_out,
        conv_dw_9,
        CONV_DW_9_HEIGHT,
        CONV_DW_9_WIDTH,
        CONV_DW_9_CHANNELS,
        conv_dw_9_out,
        3,      // kernel_size
        CONV_DW_9_STRIDE,   
        conv_dw_9_bn_mean,
        conv_dw_9_bn_var,
        conv_dw_9_bn_gamma,
        conv_dw_9_bn_beta,
        conv_dw_9_bn_eps
    );

    _pointwise_conv_block (
        CONV_DW_9_HEIGHT,
        CONV_DW_9_WIDTH,
        CONV_DW_9_CHANNELS,
        conv_dw_9_out,
        conv_pw_9,
        CONV_PW_9_HEIGHT,
        CONV_PW_9_WIDTH,
        CONV_PW_9_CHANNELS,
        conv_pw_9_out,
        conv_pw_9_bn_mean,
        conv_pw_9_bn_var,
        conv_pw_9_bn_gamma,
        conv_pw_9_bn_beta,
        conv_pw_9_bn_eps
    ); 

    free(conv_pw_8_out);
    free(conv_dw_9_out);

//------------------------------
//          BLOCK 10
//------------------------------
    type *conv_dw_10_out = calloc((CONV_DW_10_CHANNELS)*(CONV_DW_10_HEIGHT)*(CONV_DW_10_WIDTH), sizeof(type));
    type *conv_pw_10_out = calloc(CONV_PW_10_CHANNELS*CONV_PW_10_WIDTH*CONV_PW_10_HEIGHT, sizeof(type));

    _depthwise_conv_block (
        CONV_PW_9_HEIGHT,
        CONV_PW_9_WIDTH,
        CONV_PW_9_CHANNELS,
        conv_pw_9_out,
        conv_dw_10,
        CONV_DW_10_HEIGHT,
        CONV_DW_10_WIDTH,
        CONV_DW_10_CHANNELS,
        conv_dw_10_out,
        3,      // kernel_size
        CONV_DW_10_STRIDE,   
        conv_dw_10_bn_mean,
        conv_dw_10_bn_var,
        conv_dw_10_bn_gamma,
        conv_dw_10_bn_beta,
        conv_dw_10_bn_eps
    );

    _pointwise_conv_block (
        CONV_DW_10_HEIGHT,
        CONV_DW_10_WIDTH,
        CONV_DW_10_CHANNELS,
        conv_dw_10_out,
        conv_pw_10,
        CONV_PW_10_HEIGHT,
        CONV_PW_10_WIDTH,
        CONV_PW_10_CHANNELS,
        conv_pw_10_out,
        conv_pw_10_bn_mean,
        conv_pw_10_bn_var,
        conv_pw_10_bn_gamma,
        conv_pw_10_bn_beta,
        conv_pw_10_bn_eps
    ); 

    free(conv_pw_9_out);
    free(conv_dw_10_out);

//------------------------------
//          BLOCK 11
//------------------------------
    type *conv_dw_11_out = calloc((CONV_DW_11_CHANNELS)*(CONV_DW_11_HEIGHT)*(CONV_DW_11_WIDTH), sizeof(type));
    type *conv_pw_11_out = calloc(CONV_PW_11_CHANNELS*CONV_PW_11_WIDTH*CONV_PW_11_HEIGHT, sizeof(type));

    _depthwise_conv_block (
        CONV_PW_10_HEIGHT,
        CONV_PW_10_WIDTH,
        CONV_PW_10_CHANNELS,
        conv_pw_10_out,
        conv_dw_11,
        CONV_DW_11_HEIGHT,
        CONV_DW_11_WIDTH,
        CONV_DW_11_CHANNELS,
        conv_dw_11_out,
        3,      // kernel_size
        CONV_DW_11_STRIDE,   
        conv_dw_11_bn_mean,
        conv_dw_11_bn_var,
        conv_dw_11_bn_gamma,
        conv_dw_11_bn_beta,
        conv_dw_11_bn_eps
    );

    _pointwise_conv_block (
        CONV_DW_11_HEIGHT,
        CONV_DW_11_WIDTH,
        CONV_DW_11_CHANNELS,
        conv_dw_11_out,
        conv_pw_11,
        CONV_PW_11_HEIGHT,
        CONV_PW_11_WIDTH,
        CONV_PW_11_CHANNELS,
        conv_pw_11_out,
        conv_pw_11_bn_mean,
        conv_pw_11_bn_var,
        conv_pw_11_bn_gamma,
        conv_pw_11_bn_beta,
        conv_pw_11_bn_eps
    ); 

    free(conv_pw_10_out);
    free(conv_dw_11_out);

//------------------------------
//          BLOCK 12
//------------------------------
    type *conv_dw_12_out = calloc((CONV_DW_12_CHANNELS)*(CONV_DW_12_HEIGHT)*(CONV_DW_12_WIDTH), sizeof(type));
    type *conv_pw_12_out = calloc(CONV_PW_12_CHANNELS*CONV_PW_12_WIDTH*CONV_PW_12_HEIGHT, sizeof(type));

    _depthwise_conv_block (
        CONV_PW_11_HEIGHT,
        CONV_PW_11_WIDTH,
        CONV_PW_11_CHANNELS,
        conv_pw_11_out,
        conv_dw_12,
        CONV_DW_12_HEIGHT,
        CONV_DW_12_WIDTH,
        CONV_DW_12_CHANNELS,
        conv_dw_12_out,
        3,      // kernel_size
        CONV_DW_12_STRIDE,   
        conv_dw_12_bn_mean,
        conv_dw_12_bn_var,
        conv_dw_12_bn_gamma,
        conv_dw_12_bn_beta,
        conv_dw_12_bn_eps
    );

    _pointwise_conv_block (
        CONV_DW_12_HEIGHT,
        CONV_DW_12_WIDTH,
        CONV_DW_12_CHANNELS,
        conv_dw_12_out,
        conv_pw_12,
        CONV_PW_12_HEIGHT,
        CONV_PW_12_WIDTH,
        CONV_PW_12_CHANNELS,
        conv_pw_12_out,
        conv_pw_12_bn_mean,
        conv_pw_12_bn_var,
        conv_pw_12_bn_gamma,
        conv_pw_12_bn_beta,
        conv_pw_12_bn_eps
    ); 

    free(conv_pw_11_out);
    free(conv_dw_12_out);

//------------------------------
//          BLOCK 13
//------------------------------
    type *conv_dw_13_out = calloc((CONV_DW_13_CHANNELS)*(CONV_DW_13_HEIGHT)*(CONV_DW_13_WIDTH), sizeof(type));
    type *conv_pw_13_out = calloc(CONV_PW_13_CHANNELS*CONV_PW_13_WIDTH*CONV_PW_13_HEIGHT, sizeof(type));

    _depthwise_conv_block (
        CONV_PW_12_HEIGHT,
        CONV_PW_12_WIDTH,
        CONV_PW_12_CHANNELS,
        conv_pw_12_out,
        conv_dw_13,
        CONV_DW_13_HEIGHT,
        CONV_DW_13_WIDTH,
        CONV_DW_13_CHANNELS,
        conv_dw_13_out,
        3,      // kernel_size
        CONV_DW_13_STRIDE,   
        conv_dw_13_bn_mean,
        conv_dw_13_bn_var,
        conv_dw_13_bn_gamma,
        conv_dw_13_bn_beta,
        conv_dw_13_bn_eps
    );

    _pointwise_conv_block (
        CONV_DW_13_HEIGHT,
        CONV_DW_13_WIDTH,
        CONV_DW_13_CHANNELS,
        conv_dw_13_out,
        conv_pw_13,
        CONV_PW_13_HEIGHT,
        CONV_PW_13_WIDTH,
        CONV_PW_13_CHANNELS,
        conv_pw_13_out,
        conv_pw_13_bn_mean,
        conv_pw_13_bn_var,
        conv_pw_13_bn_gamma,
        conv_pw_13_bn_beta,
        conv_pw_13_bn_eps
    ); 

    free(conv_pw_12_out);
    free(conv_dw_13_out);
    
//------------------------------
//      Average Pooling
//------------------------------
    type *pool = calloc(CONV_PW_13_CHANNELS, sizeof(type));
    avg_pooling (
        CONV_PW_13_HEIGHT,
        CONV_PW_13_WIDTH,
        CONV_PW_13_CHANNELS,
        conv_pw_13_out,
        pool
    ); 

    free(conv_pw_13_out);

//------------------------------
//    Fully Connnected Layer
//------------------------------  
    type *preds = calloc(CLASSES, sizeof(type));

    _fc (
        CONV_PW_13_CHANNELS,
        pool,
        conv_preds,
        conv_preds_bias,
        CLASSES,
        preds
    );
    
    free(pool);

//------------------------------
//         Predictions
//------------------------------
    // type *probs = calloc(CLASSES, sizeof(type));
    type *probs = calloc(CLASSES, sizeof(type));
    softmax (
        CLASSES,
        preds,
        probs
    );

    free(preds);

//------------------------------
//          ~ END ~
//------------------------------

    int classf = 0;
    float predf = 0.0;
    for (int i=0; i<CLASSES; i++) {
        if (probs[i] > predf) {
            predf = probs[i];
            classf = i;

        }
    }

    printf("%d %f\n", classf, predf);

    free(probs);

    return 0;
}