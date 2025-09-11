#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <riscv-csr.h>
#include <stdint.h>

#define IMAGE_HEIGHT   32
#define IMAGE_WIDTH    32
#define IMAGE_CHANNELS  3

// #define NUM_SAMPLES 1001       // samples + 1
#define NUM_SAMPLES 2             // samples + 1
#define MULTIPLIER 8192

#define type int

//----------------------------
//      LMFRNet stages
//----------------------------
//{{{
    #include "../test-dataset-sume/image1.h"

    #include "../include-quant/stage_1.h"
    #include "../include-quant/stage_2.h"
    #include "../include-quant/stage_3.h"
    #include "../include-quant/stage_4.h"
    #include "../include-quant/stage_5.h"
    #include "../include-quant/stage_6.h"
//}}}

// [!] (sample, class, pred) = (1, 3, 156019)
// [!] (sample, class, pred) = (1, 3, 154876)

// #define PREDS_FILE "targets.txt"
// int confusion_matrix[STAGE_6_CLASSES][STAGE_6_CLASSES];

// full pad: adds a border of zeros
// {{{
void pad (
    const int HEIGHT,
    const int WIDTH,
    const int CHANNELS,
    const type in[],
    type out[]
) {
    // for (int i=0; i<HEIGHT; i++)
    // {
    //     for (int j=0; j<WIDTH; j++)
    //     {
    //         for (int k=0; k<CHANNELS; k++)
    //         {
    //             int idx_in = (k)+(j*CHANNELS)+(i*CHANNELS*WIDTH);
    //             int idx_out = (k)+((j+1)*CHANNELS)+((i+1)*CHANNELS*(WIDTH+2));
    //             out[idx_out] = in[idx_in];
    //         }
    //     }
    // }

    size_t vl;
    int ch;
    int *in_addr  = (int *) in;
    int *out_addr = (int *) out + CHANNELS*(WIDTH+3);

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            for (ch = CHANNELS; ch > 0; ch -= vl)
            {
                __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(ch));
                __asm__ volatile("vle32.v v16, (%0)" :: "r"(in_addr));
                __asm__ volatile("vse32.v v16, (%0)" :: "r"(out_addr));
                in_addr += vl;
                out_addr += vl;
            }
        }
        out_addr += 2*CHANNELS;
    }
}
// }}}

type max (const type x, const type y) {
    return (x < y) ? y : x;
}

//{{{
void _fc (
    const int INPUT_CHANNELS,
    const type in[],
    const type weights[],
    const type bias[],
    const int NEURONS,
    type out[]
) {
    // for (int ch=0; ch<INPUT_CHANNELS; ch++)
    // {
    //     for (int n=0; n<NEURONS; n++)
    //     {
    //         out[n] += in[ch]*weights[(n)+(ch*NEURONS)];
    //     }
    // }
    
    // // int handler
    // for (int n=0; n<NEURONS; n++) {
    //     out[n] >>= 13;
    // }

    // for (int n=0; n<NEURONS; n++) {
    //     out[n] += bias[n];
    // }

    size_t vl;
    int pixel;
    int *in_addr   = (int *) in;
    int *out_addr  = (int *) out;
    int *k_addr    = (int *) weights;
    int *bias_addr = (int *) bias;

    for (int ch = 0; ch < INPUT_CHANNELS; ch++)
    {
        pixel = *in_addr;
        out_addr = (int *) out;
        in_addr++;
        for (int n = NEURONS; n > 0; n -= vl)
        {
            __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(n));
            __asm__ volatile("vle32.v v8, (%0)" :: "r"(k_addr));
            __asm__ volatile("vle32.v v16, (%0)" :: "r"(out_addr));
            __asm__ volatile("vmacc.vx v16, %0, v8" :: "r"(pixel));
            __asm__ volatile("vse32.v v16, (%0)" :: "r"(out_addr));
            out_addr += vl;
            k_addr   += vl;
        }
    }

    // int handler + bias
    out_addr = (int *) out;
    for (int total = NEURONS; total > 0; total -= vl)
    {
        __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));
        __asm__ volatile("vle32.v v16, (%0)" :: "r"(out_addr));
        __asm__ volatile("vle32.v v8, (%0)" :: "r"(bias_addr));
        __asm__ volatile("vsra.vi v16, v16, 13"); // int_handler
        __asm__ volatile("vadd.vv v16, v16, v8"); // bias
        __asm__ volatile("vse32.v v16, (%0)" :: "r"(out_addr));
        out_addr  += vl;
        bias_addr += vl;
    }
}
//}}}

void relu (type in[], const int size) {
    for (int i=0; i<size; i++) {
        in[i] = max(in[i], 0);
    }
}

//{{{
void global_avg_pool (
    const int INPUT_HEIGHT,
    const int INPUT_WIDTH,
    const int INPUT_CHANNELS,
    const type in[],
    type out[]
) {
    // for (int i=0; i<INPUT_HEIGHT; i++)
    // {
    //     for (int j=0; j<INPUT_WIDTH; j++)
    //     {
    //         for (int k=0; k<INPUT_CHANNELS; k++)
    //         {
    //             out[k] += in[(k) + (j*INPUT_CHANNELS) + (i*INPUT_CHANNELS*INPUT_WIDTH)];
    //         }
    //     }
    // }

    // for (int i=0; i<INPUT_CHANNELS; i++)
    // {
    //     out[i] /= (INPUT_HEIGHT*INPUT_WIDTH);
    // }

    size_t vl;
    const int tmp = INPUT_HEIGHT*INPUT_WIDTH;
    int *in_addr  = (int *) in;
    int *out_addr = (int *) out;

    for (int total = (INPUT_HEIGHT*INPUT_WIDTH*INPUT_CHANNELS); total > 0; total -= INPUT_CHANNELS)
    {
        out_addr = (int *) out;
        for (int ch_out = INPUT_CHANNELS; ch_out > 0; ch_out -= vl)
        {
            __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(ch_out));
            __asm__ volatile("vle32.v v16, (%0)" :: "r"(in_addr));
            __asm__ volatile("vle32.v v24, (%0)" :: "r"(out_addr));
            __asm__ volatile("vadd.vv v24, v24, v16");
            __asm__ volatile("vse32.v v24, (%0)" :: "r"(out_addr));
            in_addr += vl;
            out_addr += vl;
        }
    }
    
    out_addr = (int *) out;
    for (int total = INPUT_CHANNELS; total > 0; total -= vl)
    {
        __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));
        __asm__ volatile("vle32.v v16, (%0)" :: "r"(out_addr));
        __asm__ volatile("vdiv.vx v16, v16, %0" ::"r"(tmp));
        __asm__ volatile("vse32.v v16, (%0)" :: "r"(out_addr));
        out_addr += vl;
    }
}
//}}}

//{{{
void avg_pool (
    const int INPUT_HEIGHT,
    const int INPUT_WIDTH,
    const int INPUT_CHANNELS,
    const type in[],
    const int OUTPUT_HEIGHT,
    const int OUTPUT_WIDTH,
    const int OUTPUT_CHANNELS,
    type out[]
) {
    // const int kernel_size = 2;
    // const int stride = 2;
    // int base_y=0, base_x=0;

    // for (int k=0; k<OUTPUT_HEIGHT; k++)
    // {
    //     base_x = 0;
    //     for (int l=0; l<OUTPUT_WIDTH; l++)
    //     {
    //         for (int i=0; i<kernel_size; i++)
    //         {
    //             for (int j=0; j<kernel_size; j++)
    //             {
    //                 for (int n=0; n<OUTPUT_CHANNELS; n++)
    //                 {
    //                     int idx_in = (n)+(base_x)+(base_y)+(j*INPUT_CHANNELS)+(i*INPUT_CHANNELS*(INPUT_WIDTH));
    //                     int idx_out = (n)+(l*OUTPUT_CHANNELS)+(k*OUTPUT_CHANNELS*OUTPUT_WIDTH);
    //                     out[idx_out] += in[idx_in];
    //                 }
    //             }
    //         }
    //         base_x += stride*INPUT_CHANNELS;
    //     }
    //     base_y += stride*INPUT_CHANNELS*(INPUT_WIDTH);
    // }

    // for (int k=0; k<OUTPUT_HEIGHT; k++)
    // {
    //     for (int l=0; l<OUTPUT_WIDTH; l++)
    //     {
    //         for (int n=0; n<OUTPUT_CHANNELS; n++)
    //         {
    //             int idx_out = (n) + (l*OUTPUT_CHANNELS) + (k*OUTPUT_CHANNELS*OUTPUT_WIDTH);
    //             out[idx_out] >>= 2;
    //         }
    //     }
    // }

    // for (int i=0; i<OUTPUT_HEIGHT*OUTPUT_WIDTH*OUTPUT_CHANNELS; i++) {
    //     out[i] >>= 2;
    // }

    const int kernel_size = 2;
    const int stride = 2;
    size_t vl;
    int base_y = 0, base_x = 0;
    int ch;
    int *in_addr  = (int *) in;
    int *out_addr = (int *) out;
    int *base_out = (int *) out;

    for (int k = 0; k < OUTPUT_HEIGHT; k++)
    {
        base_x = 0;
        for (int l = 0; l < OUTPUT_WIDTH; l++)
        {
            in_addr = (int *) in + base_x + base_y;
            for (int i = 0; i < kernel_size; i++)
            {
                for (int j = 0; j < kernel_size; j++)
                {
                    out_addr = (int *) base_out;
                    for (ch = OUTPUT_CHANNELS; ch > 0; ch -= vl)
                    {
                        __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(ch));
                        __asm__ volatile("vle32.v v16, (%0)" :: "r"(in_addr));
                        __asm__ volatile("vle32.v v24, (%0)" :: "r"(out_addr));
                        __asm__ volatile("vadd.vv v24, v24, v16");
                        __asm__ volatile("vse32.v v24, (%0)" :: "r"(out_addr));
                        in_addr  += vl;
                        out_addr += vl;
                    }
                }
                in_addr -= kernel_size*INPUT_CHANNELS;
                in_addr += INPUT_CHANNELS*INPUT_WIDTH;
            }
            base_out += OUTPUT_CHANNELS;
            base_x += stride*INPUT_CHANNELS;
        }
        base_y += stride*INPUT_CHANNELS*INPUT_WIDTH;
    }   
    
    out_addr = (int *) out;
    for (int total = OUTPUT_HEIGHT*OUTPUT_WIDTH*OUTPUT_CHANNELS; total > 0; total -= vl)
    {
        __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));
        __asm__ volatile("vle32.v v16, (%0)" :: "r"(out_addr));
        __asm__ volatile("vsra.vi v16, v16, 2");
        __asm__ volatile("vse32.v v16, (%0)" :: "r"(out_addr));
        out_addr += vl;
    }
}
//}}}

// {{{
void batch_normalization (
    const int HEIGHT,
    const int WIDTH,
    const int CHANNELS,
    type in[],
    const type gamma[],
    const type beta[],
    const type mean[],
    const type deviation[]
) {
    // for (int i=0; i<CHANNELS*HEIGHT*WIDTH; i++)
    // {
    //     printf("%x\n", in[i]);
    // }

    // for (int i=0; i<HEIGHT; i++) 
    // {
    //     for (int j=0; j<WIDTH; j++) 
    //     {
    //         for (int n=0; n<CHANNELS; n++) 
    //         {
    //             int id = (n) + (j*CHANNELS) + (i*CHANNELS*WIDTH);
                
    //             in[id] -= mean[n];
    //             in[id] /= deviation[n];
    //             in[id] *= gamma[n];
    //             in[id] += beta[n];
    //         }
    //     }
    // }

    size_t vl;
    int total;
    int ch;
    int *in_addr = (int *) in;
    int *gamma_addr;
    int *beta_addr;
    int *mean_addr;
    int *deviation_addr;

    for (total = HEIGHT*WIDTH*CHANNELS; total > 0; total -= CHANNELS)
    {
        mean_addr       = (int *) mean;
        deviation_addr  = (int *) deviation;
        gamma_addr      = (int *) gamma;
        beta_addr       = (int *) beta;

        for (ch = CHANNELS; ch > 0; ch -= vl)
        {
            __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(ch));
            __asm__ volatile("vle32.v v24, (%0)" :: "r"(in_addr));
            __asm__ volatile("vle32.v v16, (%0)" :: "r"(mean_addr));
            __asm__ volatile("vsub.vv v24, v24, v16");
            mean_addr += vl;
            __asm__ volatile("vle32.v v16, (%0)" :: "r"(deviation_addr));
            __asm__ volatile("vdiv.vv v24, v24, v16");
            deviation_addr += vl;
            __asm__ volatile("vle32.v v16, (%0)" :: "r"(gamma_addr));
            __asm__ volatile("vmul.vv v24, v24, v16");
            gamma_addr += vl;
            __asm__ volatile("vle32.v v16, (%0)" :: "r"(beta_addr));
            __asm__ volatile("vadd.vv v24, v24, v16");
            beta_addr += vl;
            __asm__ volatile("vmslt.vi v0, v24, 0"); // ReLU
            __asm__ volatile("vmerge.vim v24, v24, 0, v0");
            __asm__ volatile("vse32.v v24, (%0)" :: "r"(in_addr));
            in_addr += vl;
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
    const type deviation[]
) {
    int p = (OUTPUT_WIDTH)-(int)((INPUT_WIDTH-kernel_size)/stride)-1;
    type *in_pd = calloc((INPUT_CHANNELS)*(INPUT_WIDTH+p)*(INPUT_HEIGHT+p), sizeof(type));

    if (p == 2) {
        pad (INPUT_HEIGHT, INPUT_WIDTH, INPUT_CHANNELS, in, in_pd);
    }
    else {
        // // no padding
        // for (int i=0; i<INPUT_HEIGHT*INPUT_WIDTH*INPUT_CHANNELS; i++) {
        //     in_pd[i] = in[i];
        // }
        
        // no padding
        size_t vl;
        int total;
        int *in_addr    = (int *) in;
        int *in_pd_addr = (int *) in_pd;

        for (total = INPUT_HEIGHT*INPUT_WIDTH*INPUT_CHANNELS; total > 0; total -= vl)
        {   
            __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));
            __asm__ volatile("vle32.v v16, (%0)" :: "r"(in_addr));
            __asm__ volatile("vse32.v v16, (%0)" :: "r"(in_pd_addr));
            in_addr    += vl;
            in_pd_addr += vl;
        }
    }

    // // "(0,0)" of the 3x3 image
    // int base_y=0, base_x=0;

    // for (int k=0; k<OUTPUT_HEIGHT; k++)
    // {
    //     base_x = 0;
    //     for (int l=0; l<OUTPUT_WIDTH; l++)
    //     {
    //         for (int i=0; i<kernel_size; i++)
    //         {
    //             for (int j=0; j<kernel_size; j++)
    //             {
    //                 for (int m=0; m<INPUT_CHANNELS; m++)
    //                 {
    //                     int idx_i = (m)+(base_x)+(base_y)+(j*INPUT_CHANNELS)+(i*INPUT_CHANNELS*(INPUT_WIDTH+p));
    //                     for (int n=0; n<OUTPUT_CHANNELS; n++)
    //                     {
    //                         int idx_w = (n)+(m*OUTPUT_CHANNELS)+(j*OUTPUT_CHANNELS*INPUT_CHANNELS)+(i*OUTPUT_CHANNELS*INPUT_CHANNELS*kernel_size);
    //                         int idx_out = (n)+(l*OUTPUT_CHANNELS)+(k*OUTPUT_CHANNELS*OUTPUT_WIDTH);

    //                         out[idx_out] += in_pd[idx_i]*weights[idx_w];
    //                         // printf("w: %d o: %d\n", idx_w, idx_out);
    //                     }
    //                 }
    //             }
    //         }
    //         base_x += stride*INPUT_CHANNELS;
    //     }
    //     base_y += stride*INPUT_CHANNELS*(INPUT_WIDTH+p);
    // }

    // int handler
    // for (int i=0; i<OUTPUT_HEIGHT*OUTPUT_WIDTH*OUTPUT_CHANNELS; i++) {
    //     out[i] >>= 13;
    // }

    // if (bias != NULL)
    // {
    //     for (int k=0; k<OUTPUT_HEIGHT; k++)
    //     {
    //         for (int l=0; l<OUTPUT_WIDTH; l++)
    //         {
    //             for (int n=0; n<OUTPUT_CHANNELS; n++)
    //             {
    //                 out[(n)+(l*OUTPUT_CHANNELS)+(k*OUTPUT_CHANNELS*OUTPUT_WIDTH)] += bias[n];
    //             }
    //         }
    //     }
    // }

    size_t vl;
    int *in_addr  = (int *) in_pd;
    int *out_addr = (int *) out;
    int *base_out = (int *) out;
    int *k_addr   = (int *) weights;
    int base_x = 0, base_y = 0;     // "(0,0)" of the image
    int ch_out;
    int pixel;
    int width_padded = INPUT_WIDTH + p;


    for (int k=0; k<OUTPUT_HEIGHT; k++)
    {
        base_x = 0;
        for (int l=0; l<OUTPUT_WIDTH; l++)
        {
            in_addr = (int *) in_pd + base_x + base_y;
            k_addr = (int *) weights;
            for (int i=0; i<kernel_size; i++)
            {
                for (int j=0; j<kernel_size; j++)
                {
                    for (int m=0; m<INPUT_CHANNELS; m++)
                    {
                        pixel = *in_addr;
                        in_addr++;
                        out_addr = (int *) base_out;   
                        
                        for (ch_out = OUTPUT_CHANNELS; ch_out > 0; ch_out -= vl)
                        {
                            __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(ch_out));
                            __asm__ volatile("vle32.v v16, (%0)" :: "r"(k_addr));
                            __asm__ volatile("vle32.v v24, (%0)" :: "r"(out_addr));
                            __asm__ volatile("vmacc.vx v24, %0, v16" :: "r"(pixel));
                            __asm__ volatile("vse32.v v24, (%0)" :: "r"(out_addr));
                            k_addr   += vl;
                            out_addr += vl;
                        }
                    }
                }
                in_addr -= kernel_size*INPUT_CHANNELS;
                in_addr += INPUT_CHANNELS*width_padded;
            }
            base_out += OUTPUT_CHANNELS;
            base_x += stride*INPUT_CHANNELS; 
        }
        base_y += stride*INPUT_CHANNELS*width_padded;
    }

    // int handler
    out_addr = (int *) out;
    for (int total = OUTPUT_HEIGHT*OUTPUT_WIDTH*OUTPUT_CHANNELS; total > 0; total -= vl)
    {
        __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));
        __asm__ volatile("vle32.v v16, (%0)" :: "r"(out_addr));
        __asm__ volatile("vsra.vi v16, v16, 13");
        __asm__ volatile("vse32.v v16, (%0)" :: "r"(out_addr));
        out_addr += vl;
    }

    if (bias != NULL)
    {
        int *bias_addr = (int *) bias;
        int total, ch_out;
        out_addr = (int *) out;

        for (total = OUTPUT_HEIGHT*OUTPUT_WIDTH*OUTPUT_CHANNELS; total > 0; total -= OUTPUT_CHANNELS)
        {
            bias_addr = (int *) bias;
            for (ch_out = OUTPUT_CHANNELS; ch_out > 0; ch_out -= vl)
            {
                __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(ch_out));
                __asm__ volatile("vle32.v v16, (%0)" :: "r"(out_addr));
                __asm__ volatile("vle32.v v8, (%0)" :: "r"(bias_addr));
                __asm__ volatile("vadd.vv v16, v16, v8");
                __asm__ volatile("vse32.v v16, (%0)" :: "r"(out_addr));

                bias_addr += vl;
                out_addr += vl;
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
        deviation
    );

    // relu(out, OUTPUT_HEIGHT*OUTPUT_WIDTH*OUTPUT_CHANNELS);

    free(in_pd);
}
// }}}

// concatenate 4 tensors (MFBlock filter concatenation)
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
    // int C = CH0 + CH1 + CH2 + CH3;
    // for (int i=0; i<H; i++)
    // {
    //     for (int j=0; j<W; j++)
    //     {
    //         int offset = 0;
    //         for (int k=0; k<CH0; k++) {
    //             out[k + j*C + i*C*W] = v0[k + j*CH0 + i*CH0*W];
    //         }
    //         offset += CH0;
    //         for (int k=0; k<CH0; k++) {
    //             out[k + offset + j*C + i*C*W] = v1[k + j*CH1 + i*CH1*W];
    //         }

    //         offset += CH1;
    //         for (int k=0; k<CH0; k++) {
    //             out[k + offset + j*C + i*C*W] = v2[k + j*CH2 + i*CH2*W];
    //         }

    //         offset += CH2;
    //         for (int k=0; k<CH0; k++) {
    //             out[k + offset + j*C + i*C*W] = v3[k + j*CH3 + i*CH3*W];
    //         }
    //     }
    // }

    int C = CH0 + CH1 + CH2 + CH3;
    int *v0_addr = (int *)v0;
    int *v1_addr = (int *)v1;
    int *v2_addr = (int *)v2;
    int *v3_addr = (int *)v3;
    int *out_addr = (int *)out;
    size_t vl;
    int total;
    int v0_processed_elements;
    int v1_processed_elements;
    int v2_processed_elements;
    int v3_processed_elements;

    for (total = H*W*C; total > 0; total -= (CH0+CH1+CH2+CH3))
    {
        for (v0_processed_elements = CH0; v0_processed_elements > 0; v0_processed_elements -= vl)
        {
            __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(v0_processed_elements));
            __asm__ volatile("vle32.v v24, (%0)" :: "r"(v0_addr));
            __asm__ volatile("vse32.v v24, (%0)" :: "r"(out_addr));
            v0_addr  += vl;
            out_addr += vl;
        }

        for (v1_processed_elements = CH1; v1_processed_elements > 0; v1_processed_elements -= vl)
        {
            __asm__ volatile("vsetvli %0, %1, e32, m2, ta, ma" : "=r"(vl) : "r"(v1_processed_elements));
            __asm__ volatile("vle32.v v24, (%0)" :: "r"(v1_addr));
            __asm__ volatile("vse32.v v24, (%0)" :: "r"(out_addr));
            v1_addr  += vl;
            out_addr += vl;
        }

        for (v2_processed_elements = CH2; v2_processed_elements > 0; v2_processed_elements -= vl)
        {
            __asm__ volatile("vsetvli %0, %1, e32, m1, ta, ma" : "=r"(vl) : "r"(v2_processed_elements));
            __asm__ volatile("vle32.v v24, (%0)" :: "r"(v2_addr));
            __asm__ volatile("vse32.v v24, (%0)" :: "r"(out_addr));
            v2_addr  += vl;
            out_addr += vl;
        }

        for (v3_processed_elements = CH3; v3_processed_elements > 0; v3_processed_elements -= vl)
        {
            __asm__ volatile("vsetvli %0, %1, e32, m1, ta, ma" : "=r"(vl) : "r"(v3_processed_elements));
            __asm__ volatile("vle32.v v24, (%0)" :: "r"(v3_addr));
            __asm__ volatile("vse32.v v24, (%0)" :: "r"(out_addr));
            v3_addr  += vl;
            out_addr += vl;
        }
    }
}
//}}}

void vector_memset0(type v[], const int size) {
    int total;
    size_t vl;
    int *addr = (int *) v;

    for (total = size; total > 0; total -= vl)
    {
        __asm__ volatile("vsetvli %0, %1, e32, m8, ta, ma" : "=r"(vl) : "r"(total));
        __asm__ volatile("vmv.v.i v24, 0");
        __asm__ volatile("vse32.v v24, (%0)" :: "r"(addr));
        addr += vl;
    }
}

int main()
{   
    // FILE *preds_file = fopen(PREDS_FILE, "r");
    uint64_t cycles_start, cycles_end;
    uint32_t cycles[NUM_SAMPLES];

    // load_confusion_matrix();
    for (int n_sample=1; n_sample<NUM_SAMPLES; n_sample++)
    {
        cycles_start = csr_read_mcycle();
        // char *filename = malloc(100);
        // snprintf(filename, 100, "test-dataset/%d.bin", n_sample);
    //-------------------------------------------
    //                STAGE_1
    //-------------------------------------------
    //{{{
        type *image = calloc(IMAGE_HEIGHT*IMAGE_WIDTH*IMAGE_CHANNELS, sizeof(type));
        type *stage_1_out = calloc(STAGE_1_WIDTH*STAGE_1_HEIGHT*STAGE_1_CHANNELS, sizeof(type));
        
        // read_bin_file(filename, image, IMAGE_HEIGHT*IMAGE_WIDTH*IMAGE_CHANNELS);

        _conv_block (
            IMAGE_HEIGHT,
            IMAGE_WIDTH,
            IMAGE_CHANNELS,
            // image,
            image1,
            stemBlock_stemConv_conv_weight,
            stemBlock_stemConv_conv_bias,
            STAGE_1_HEIGHT,
            STAGE_1_WIDTH,
            STAGE_1_CHANNELS,
            stage_1_out, 
            3,      // kernel_size
            STAGE_1_STRIDE,
            stemBlock_stemConv_bn_gamma,
            stemBlock_stemConv_bn_beta,
            stemBlock_stemConv_bn_running_mean,
            stemBlock_stemConv_bn_deviation
        );

        free(image);

        // for (int i=0; i<STAGE_1_HEIGHT*STAGE_1_WIDTH*STAGE_1_CHANNELS; i++) {
        //     printf("%x\n", stage_1_out[i]);
        // }

        // return 0;
    //}}}

    type *y0 = calloc(MMCBlock1_mmLayer1_branch11_CHANNELS*STAGE_1_HEIGHT*STAGE_1_WIDTH , sizeof(type));
    type *y1 = calloc(MMCBlock1_mmLayer1_branch33a_CHANNELS*STAGE_1_HEIGHT*STAGE_1_WIDTH, sizeof(type));    
    type *y2 = calloc(MMCBlock1_mmLayer1_branch33b_CHANNELS*STAGE_1_HEIGHT*STAGE_1_WIDTH, sizeof(type));    
    type *y3 = calloc(MMCBlock1_mmLayer1_branch33c_CHANNELS*STAGE_1_HEIGHT*STAGE_1_WIDTH, sizeof(type));    
    type *tmp1 = calloc(STAGE_2_CHANNELS*STAGE_1_HEIGHT*STAGE_1_WIDTH, sizeof(type));
    type *tmp2 = calloc(STAGE_2_CHANNELS*STAGE_1_HEIGHT*STAGE_1_WIDTH, sizeof(type));

    //-------------------------------------------
    //              STAGE_2
    //-------------------------------------------
    //{{{
        //-----------------------------------------------
        //                  Layer1
        //-----------------------------------------------
        //{{{
            _conv_block (
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                STAGE_1_CHANNELS,
                stage_1_out,
                MMCBlock1_mmLayer1_branch11_conv_weight,
                NULL,   // bias
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer1_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride
                MMCBlock1_mmLayer1_branch11_bn_gamma,
                MMCBlock1_mmLayer1_branch11_bn_beta,
                MMCBlock1_mmLayer1_branch11_bn_running_mean,
                MMCBlock1_mmLayer1_branch11_bn_deviation
            );

            _conv_block (
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer1_branch11_CHANNELS,
                y0,
                MMCBlock1_mmLayer1_branch33a_conv_weight,
                NULL,   // bias
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer1_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride
                MMCBlock1_mmLayer1_branch33a_bn_gamma,
                MMCBlock1_mmLayer1_branch33a_bn_beta,
                MMCBlock1_mmLayer1_branch33a_bn_running_mean,
                MMCBlock1_mmLayer1_branch33a_bn_deviation
            );
          
            _conv_block (
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer1_branch33a_CHANNELS,
                y1,
                MMCBlock1_mmLayer1_branch33b_conv_weight,
                NULL,   // bias
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer1_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock1_mmLayer1_branch33b_bn_gamma,
                MMCBlock1_mmLayer1_branch33b_bn_beta,
                MMCBlock1_mmLayer1_branch33b_bn_running_mean,
                MMCBlock1_mmLayer1_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer1_branch33b_CHANNELS,
                y2,
                MMCBlock1_mmLayer1_branch33c_conv_weight,
                NULL,   // bias
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer1_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock1_mmLayer1_branch33c_bn_gamma,
                MMCBlock1_mmLayer1_branch33c_bn_beta,
                MMCBlock1_mmLayer1_branch33c_bn_running_mean,
                MMCBlock1_mmLayer1_branch33c_bn_deviation
            );

            concat4 (
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                STAGE_1_CHANNELS,
                MMCBlock1_mmLayer1_branch33a_CHANNELS,
                MMCBlock1_mmLayer1_branch33b_CHANNELS,
                MMCBlock1_mmLayer1_branch33c_CHANNELS,
                stage_1_out, 
                y1, 
                y2, 
                y3, 
                tmp1
            );

            free(stage_1_out);
        //}}} 
        //-----------------------------------------------
        //                  Layer2
        //-----------------------------------------------
        //{{{
            vector_memset0(y0, MMCBlock1_mmLayer2_branch11_CHANNELS*STAGE_1_HEIGHT*STAGE_1_WIDTH);
            vector_memset0(y1, MMCBlock1_mmLayer2_branch33a_CHANNELS*STAGE_1_HEIGHT*STAGE_1_WIDTH);
            vector_memset0(y2, MMCBlock1_mmLayer2_branch33b_CHANNELS*STAGE_1_HEIGHT*STAGE_1_WIDTH);
            vector_memset0(y3, MMCBlock1_mmLayer2_branch33c_CHANNELS*STAGE_1_HEIGHT*STAGE_1_WIDTH);

            _conv_block (
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer1_CHANNELS,
                tmp1,
                MMCBlock1_mmLayer2_branch11_conv_weight,
                NULL,   // bias
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer2_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride 
                MMCBlock1_mmLayer2_branch11_bn_gamma,
                MMCBlock1_mmLayer2_branch11_bn_beta,
                MMCBlock1_mmLayer2_branch11_bn_running_mean,
                MMCBlock1_mmLayer2_branch11_bn_deviation
            );

            _conv_block (
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer2_branch11_CHANNELS,
                y0,
                MMCBlock1_mmLayer2_branch33a_conv_weight,
                NULL,   // bias
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer2_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride
                MMCBlock1_mmLayer2_branch33a_bn_gamma,
                MMCBlock1_mmLayer2_branch33a_bn_beta,
                MMCBlock1_mmLayer2_branch33a_bn_running_mean,
                MMCBlock1_mmLayer2_branch33a_bn_deviation
            );

            _conv_block (
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer2_branch33a_CHANNELS,
                y1,
                MMCBlock1_mmLayer2_branch33b_conv_weight,
                NULL,   // bias
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer2_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock1_mmLayer2_branch33b_bn_gamma,
                MMCBlock1_mmLayer2_branch33b_bn_beta,
                MMCBlock1_mmLayer2_branch33b_bn_running_mean,
                MMCBlock1_mmLayer2_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer2_branch33b_CHANNELS,
                y2,
                MMCBlock1_mmLayer2_branch33c_conv_weight,
                NULL,   // bias
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer2_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock1_mmLayer2_branch33c_bn_gamma,
                MMCBlock1_mmLayer2_branch33c_bn_beta,
                MMCBlock1_mmLayer2_branch33c_bn_running_mean,
                MMCBlock1_mmLayer2_branch33c_bn_deviation
            );

            concat4 (
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer1_CHANNELS,
                MMCBlock1_mmLayer2_branch33a_CHANNELS,
                MMCBlock1_mmLayer2_branch33b_CHANNELS,
                MMCBlock1_mmLayer2_branch33c_CHANNELS,
                tmp1,
                y1, 
                y2, 
                y3, 
                tmp2
            );
        //}}}
        //-----------------------------------------------
        //                  Layer3
        //-----------------------------------------------
        //{{{
            vector_memset0(y0, MMCBlock1_mmLayer3_branch11_CHANNELS*STAGE_1_HEIGHT*STAGE_1_WIDTH);
            vector_memset0(y1, MMCBlock1_mmLayer3_branch33a_CHANNELS*STAGE_1_HEIGHT*STAGE_1_WIDTH);
            vector_memset0(y2, MMCBlock1_mmLayer3_branch33b_CHANNELS*STAGE_1_HEIGHT*STAGE_1_WIDTH);
            vector_memset0(y3, MMCBlock1_mmLayer3_branch33c_CHANNELS*STAGE_1_HEIGHT*STAGE_1_WIDTH);

            _conv_block (
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer2_CHANNELS,
                tmp2,
                MMCBlock1_mmLayer3_branch11_conv_weight,
                NULL,   // bias
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer3_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride
                MMCBlock1_mmLayer3_branch11_bn_gamma,
                MMCBlock1_mmLayer3_branch11_bn_beta,
                MMCBlock1_mmLayer3_branch11_bn_running_mean,
                MMCBlock1_mmLayer3_branch11_bn_deviation
            );

            _conv_block (
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer3_branch11_CHANNELS,
                y0,
                MMCBlock1_mmLayer3_branch33a_conv_weight,
                NULL,   // bias
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer3_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride 
                MMCBlock1_mmLayer3_branch33a_bn_gamma,
                MMCBlock1_mmLayer3_branch33a_bn_beta,
                MMCBlock1_mmLayer3_branch33a_bn_running_mean,
                MMCBlock1_mmLayer3_branch33a_bn_deviation
            );

            _conv_block (
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer3_branch33a_CHANNELS,
                y1,
                MMCBlock1_mmLayer3_branch33b_conv_weight,
                NULL,   // bias
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer3_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock1_mmLayer3_branch33b_bn_gamma,
                MMCBlock1_mmLayer3_branch33b_bn_beta,
                MMCBlock1_mmLayer3_branch33b_bn_running_mean,
                MMCBlock1_mmLayer3_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer3_branch33b_CHANNELS,
                y2,
                MMCBlock1_mmLayer3_branch33c_conv_weight,
                NULL,   // bias
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer3_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock1_mmLayer3_branch33c_bn_gamma,
                MMCBlock1_mmLayer3_branch33c_bn_beta,
                MMCBlock1_mmLayer3_branch33c_bn_running_mean,
                MMCBlock1_mmLayer3_branch33c_bn_deviation
            );

            concat4 (
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                MMCBlock1_mmLayer2_CHANNELS,
                MMCBlock1_mmLayer3_branch33a_CHANNELS,
                MMCBlock1_mmLayer3_branch33b_CHANNELS,
                MMCBlock1_mmLayer3_branch33c_CHANNELS,
                tmp2,
                y1, 
                y2, 
                y3, 
                tmp1
            );
        //}}}
        //-----------------------------------------------
        //                  Conv1
        //-----------------------------------------------
        //{{{
            vector_memset0(tmp2, STAGE_2_CHANNELS*STAGE_1_HEIGHT*STAGE_1_WIDTH);

            _conv_block (
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                STAGE_2_CHANNELS,
                tmp1,
                tran_ConvNormRelu1_conv_weight,
                NULL,   // bias
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                STAGE_2_CHANNELS,
                tmp2,
                1,      // kernel_size
                1,      // stride
                tran_ConvNormRelu1_bn_gamma,
                tran_ConvNormRelu1_bn_beta,
                tran_ConvNormRelu1_bn_running_mean,
                tran_ConvNormRelu1_bn_deviation
            );
        //}}}
        //-----------------------------------------------
        //                 Pooling1 
        //-----------------------------------------------
        //{{{
            vector_memset0(tmp1, STAGE_2_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);

            avg_pool (
                STAGE_1_HEIGHT,
                STAGE_1_WIDTH,
                STAGE_2_CHANNELS,
                tmp2,
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                STAGE_2_CHANNELS,
                tmp1
            );
        //}}}
    //}}}
    //-------------------------------------------
    //              STAGE_3
    //-------------------------------------------
    //{{{
        //-----------------------------------------------
        //                  Layer1
        //-----------------------------------------------
        //{{{
            vector_memset0(y0, MMCBlock2_mmLayer1_branch11_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);
            vector_memset0(y1, MMCBlock2_mmLayer1_branch33a_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);
            vector_memset0(y2, MMCBlock2_mmLayer1_branch33b_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);
            vector_memset0(y3, MMCBlock2_mmLayer1_branch33c_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);

            _conv_block (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                STAGE_2_CHANNELS,
                tmp1,
                MMCBlock2_mmLayer1_branch11_conv_weight,
                NULL,   // bias
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer1_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride
                MMCBlock2_mmLayer1_branch11_bn_gamma,
                MMCBlock2_mmLayer1_branch11_bn_beta,
                MMCBlock2_mmLayer1_branch11_bn_running_mean,
                MMCBlock2_mmLayer1_branch11_bn_deviation
            );

            _conv_block (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer1_branch11_CHANNELS,
                y0,
                MMCBlock2_mmLayer1_branch33a_conv_weight,
                NULL,   // bias
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer1_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride
                MMCBlock2_mmLayer1_branch33a_bn_gamma,
                MMCBlock2_mmLayer1_branch33a_bn_beta,
                MMCBlock2_mmLayer1_branch33a_bn_running_mean,
                MMCBlock2_mmLayer1_branch33a_bn_deviation
            );

            _conv_block (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer1_branch33a_CHANNELS,
                y1,
                MMCBlock2_mmLayer1_branch33b_conv_weight,
                NULL,   // bias
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer1_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock2_mmLayer1_branch33b_bn_gamma,
                MMCBlock2_mmLayer1_branch33b_bn_beta,
                MMCBlock2_mmLayer1_branch33b_bn_running_mean,
                MMCBlock2_mmLayer1_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer1_branch33b_CHANNELS,
                y2,
                MMCBlock2_mmLayer1_branch33c_conv_weight,
                NULL,   // bias
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer1_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock2_mmLayer1_branch33c_bn_gamma,
                MMCBlock2_mmLayer1_branch33c_bn_beta,
                MMCBlock2_mmLayer1_branch33c_bn_running_mean,
                MMCBlock2_mmLayer1_branch33c_bn_deviation
            );

            concat4 (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                STAGE_2_CHANNELS,
                MMCBlock2_mmLayer1_branch33a_CHANNELS,
                MMCBlock2_mmLayer1_branch33b_CHANNELS,
                MMCBlock2_mmLayer1_branch33c_CHANNELS,
                tmp1,
                y1, 
                y2, 
                y3, 
                tmp2
            );
        //}}} 
        //-----------------------------------------------
        //                  Layer2
        //-----------------------------------------------
        //{{{
            vector_memset0(y0, MMCBlock2_mmLayer2_branch11_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);
            vector_memset0(y1, MMCBlock2_mmLayer2_branch33a_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);
            vector_memset0(y2, MMCBlock2_mmLayer2_branch33b_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);
            vector_memset0(y3, MMCBlock2_mmLayer2_branch33c_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);

            _conv_block (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer1_CHANNELS,
                tmp2,
                MMCBlock2_mmLayer2_branch11_conv_weight,
                NULL,   // bias
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer2_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride 
                MMCBlock2_mmLayer2_branch11_bn_gamma,
                MMCBlock2_mmLayer2_branch11_bn_beta,
                MMCBlock2_mmLayer2_branch11_bn_running_mean,
                MMCBlock2_mmLayer2_branch11_bn_deviation
            );

            _conv_block (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer2_branch11_CHANNELS,
                y0,
                MMCBlock2_mmLayer2_branch33a_conv_weight,
                NULL,   // bias
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer2_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride
                MMCBlock2_mmLayer2_branch33a_bn_gamma,
                MMCBlock2_mmLayer2_branch33a_bn_beta,
                MMCBlock2_mmLayer2_branch33a_bn_running_mean,
                MMCBlock2_mmLayer2_branch33a_bn_deviation
            );

            _conv_block (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer2_branch33a_CHANNELS,
                y1,
                MMCBlock2_mmLayer2_branch33b_conv_weight,
                NULL,   // bias
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer2_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock2_mmLayer2_branch33b_bn_gamma,
                MMCBlock2_mmLayer2_branch33b_bn_beta,
                MMCBlock2_mmLayer2_branch33b_bn_running_mean,
                MMCBlock2_mmLayer2_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer2_branch33b_CHANNELS,
                y2,
                MMCBlock2_mmLayer2_branch33c_conv_weight,
                NULL,   // bias
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer2_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock2_mmLayer2_branch33c_bn_gamma,
                MMCBlock2_mmLayer2_branch33c_bn_beta,
                MMCBlock2_mmLayer2_branch33c_bn_running_mean,
                MMCBlock2_mmLayer2_branch33c_bn_deviation
            );

            concat4 (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer1_CHANNELS,
                MMCBlock2_mmLayer2_branch33a_CHANNELS,
                MMCBlock2_mmLayer2_branch33b_CHANNELS,
                MMCBlock2_mmLayer2_branch33c_CHANNELS,
                tmp2,
                y1, 
                y2, 
                y3, 
                tmp1
            );
        //}}}
        //-----------------------------------------------
        //                  Layer3
        //-----------------------------------------------
        //{{{
            vector_memset0(y0, MMCBlock2_mmLayer3_branch11_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);
            vector_memset0(y1, MMCBlock2_mmLayer3_branch33a_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);
            vector_memset0(y2, MMCBlock2_mmLayer3_branch33b_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);
            vector_memset0(y3, MMCBlock2_mmLayer3_branch33c_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);

            _conv_block (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer2_CHANNELS,
                tmp1,
                MMCBlock2_mmLayer3_branch11_conv_weight,
                NULL,   // bias
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer3_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride
                MMCBlock2_mmLayer3_branch11_bn_gamma,
                MMCBlock2_mmLayer3_branch11_bn_beta,
                MMCBlock2_mmLayer3_branch11_bn_running_mean,
                MMCBlock2_mmLayer3_branch11_bn_deviation
            );

            _conv_block (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer3_branch11_CHANNELS,
                y0,
                MMCBlock2_mmLayer3_branch33a_conv_weight,
                NULL,   // bias
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer3_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride 
                MMCBlock2_mmLayer3_branch33a_bn_gamma,
                MMCBlock2_mmLayer3_branch33a_bn_beta,
                MMCBlock2_mmLayer3_branch33a_bn_running_mean,
                MMCBlock2_mmLayer3_branch33a_bn_deviation
            );

            _conv_block (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer3_branch33a_CHANNELS,
                y1,
                MMCBlock2_mmLayer3_branch33b_conv_weight,
                NULL,   // bias
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer3_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock2_mmLayer3_branch33b_bn_gamma,
                MMCBlock2_mmLayer3_branch33b_bn_beta,
                MMCBlock2_mmLayer3_branch33b_bn_running_mean,
                MMCBlock2_mmLayer3_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer3_branch33b_CHANNELS,
                y2,
                MMCBlock2_mmLayer3_branch33c_conv_weight,
                NULL,   // bias
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer3_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock2_mmLayer3_branch33c_bn_gamma,
                MMCBlock2_mmLayer3_branch33c_bn_beta,
                MMCBlock2_mmLayer3_branch33c_bn_running_mean,
                MMCBlock2_mmLayer3_branch33c_bn_deviation
            );

            concat4 (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer2_CHANNELS,
                MMCBlock2_mmLayer3_branch33a_CHANNELS,
                MMCBlock2_mmLayer3_branch33b_CHANNELS,
                MMCBlock2_mmLayer3_branch33c_CHANNELS,
                tmp1,
                y1, 
                y2, 
                y3, 
                tmp2
            );
        //}}}
        //-----------------------------------------------
        //                  Layer4
        //-----------------------------------------------
        //{{{
            vector_memset0(y0, MMCBlock2_mmLayer4_branch11_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);
            vector_memset0(y1, MMCBlock2_mmLayer4_branch33a_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);
            vector_memset0(y2, MMCBlock2_mmLayer4_branch33b_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);
            vector_memset0(y3, MMCBlock2_mmLayer4_branch33c_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);

            _conv_block (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer3_CHANNELS,
                tmp2,
                MMCBlock2_mmLayer4_branch11_conv_weight,
                NULL,   // bias
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer4_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride
                MMCBlock2_mmLayer4_branch11_bn_gamma,
                MMCBlock2_mmLayer4_branch11_bn_beta,
                MMCBlock2_mmLayer4_branch11_bn_running_mean,
                MMCBlock2_mmLayer4_branch11_bn_deviation
            );

            _conv_block (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer4_branch11_CHANNELS,
                y0,
                MMCBlock2_mmLayer4_branch33a_conv_weight,
                NULL,   // bias
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer4_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride 
                MMCBlock2_mmLayer4_branch33a_bn_gamma,
                MMCBlock2_mmLayer4_branch33a_bn_beta,
                MMCBlock2_mmLayer4_branch33a_bn_running_mean,
                MMCBlock2_mmLayer4_branch33a_bn_deviation
            );

            _conv_block (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer4_branch33a_CHANNELS,
                y1,
                MMCBlock2_mmLayer4_branch33b_conv_weight,
                NULL,   // bias
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer4_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock2_mmLayer4_branch33b_bn_gamma,
                MMCBlock2_mmLayer4_branch33b_bn_beta,
                MMCBlock2_mmLayer4_branch33b_bn_running_mean,
                MMCBlock2_mmLayer4_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer4_branch33b_CHANNELS,
                y2,
                MMCBlock2_mmLayer4_branch33c_conv_weight,
                NULL,   // bias
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer4_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock2_mmLayer4_branch33c_bn_gamma,
                MMCBlock2_mmLayer4_branch33c_bn_beta,
                MMCBlock2_mmLayer4_branch33c_bn_running_mean,
                MMCBlock2_mmLayer4_branch33c_bn_deviation
            );

            concat4 (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                MMCBlock2_mmLayer3_CHANNELS,
                MMCBlock2_mmLayer4_branch33a_CHANNELS,
                MMCBlock2_mmLayer4_branch33b_CHANNELS,
                MMCBlock2_mmLayer4_branch33c_CHANNELS,
                tmp2,
                y1, 
                y2, 
                y3, 
                tmp1
            );
        //}}}
        //-----------------------------------------------
        //                  Conv2
        //-----------------------------------------------
        //{{{
            vector_memset0(tmp2, STAGE_3_CHANNELS*STAGE_2_HEIGHT*STAGE_2_WIDTH);

            _conv_block (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                STAGE_3_CHANNELS,
                tmp1,
                tran_ConvNormRelu2_conv_weight,
                NULL,   // bias
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                STAGE_3_CHANNELS,
                tmp2,
                1,      // kernel_size
                1,      // stride
                tran_ConvNormRelu2_bn_gamma,
                tran_ConvNormRelu2_bn_beta,
                tran_ConvNormRelu2_bn_running_mean,
                tran_ConvNormRelu2_bn_deviation
            );
        //}}}
        //-----------------------------------------------
        //                 Pooling2 
        //-----------------------------------------------
        //{{{
            vector_memset0(tmp1, STAGE_3_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);

            avg_pool (
                STAGE_2_HEIGHT,
                STAGE_2_WIDTH,
                STAGE_3_CHANNELS,
                tmp2,
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                STAGE_3_CHANNELS,
                tmp1
            );
        //}}}
    //}}}
    //-------------------------------------------
    //              STAGE_4
    //-------------------------------------------
    //{{{
        //-----------------------------------------------
        //                  Layer1
        //-----------------------------------------------
        //{{{
            vector_memset0(y0, MMCBlock3_mmLayer1_branch11_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y1, MMCBlock3_mmLayer1_branch33a_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y2, MMCBlock3_mmLayer1_branch33b_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y3, MMCBlock3_mmLayer1_branch33c_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                STAGE_3_CHANNELS,
                tmp1,
                MMCBlock3_mmLayer1_branch11_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer1_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer1_branch11_bn_gamma,
                MMCBlock3_mmLayer1_branch11_bn_beta,
                MMCBlock3_mmLayer1_branch11_bn_running_mean,
                MMCBlock3_mmLayer1_branch11_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer1_branch11_CHANNELS,
                y0,
                MMCBlock3_mmLayer1_branch33a_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer1_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer1_branch33a_bn_gamma,
                MMCBlock3_mmLayer1_branch33a_bn_beta,
                MMCBlock3_mmLayer1_branch33a_bn_running_mean,
                MMCBlock3_mmLayer1_branch33a_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer1_branch33a_CHANNELS,
                y1,
                MMCBlock3_mmLayer1_branch33b_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer1_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer1_branch33b_bn_gamma,
                MMCBlock3_mmLayer1_branch33b_bn_beta,
                MMCBlock3_mmLayer1_branch33b_bn_running_mean,
                MMCBlock3_mmLayer1_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer1_branch33b_CHANNELS,
                y2,
                MMCBlock3_mmLayer1_branch33c_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer1_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer1_branch33c_bn_gamma,
                MMCBlock3_mmLayer1_branch33c_bn_beta,
                MMCBlock3_mmLayer1_branch33c_bn_running_mean,
                MMCBlock3_mmLayer1_branch33c_bn_deviation
            );

            concat4 (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                STAGE_3_CHANNELS,
                MMCBlock3_mmLayer1_branch33a_CHANNELS,
                MMCBlock3_mmLayer1_branch33b_CHANNELS,
                MMCBlock3_mmLayer1_branch33c_CHANNELS,
                tmp1,
                y1, 
                y2, 
                y3, 
                tmp2
            );
        //}}} 
        //-----------------------------------------------
        //                  Layer2
        //-----------------------------------------------
        //{{{
            vector_memset0(y0, MMCBlock3_mmLayer2_branch11_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y1, MMCBlock3_mmLayer2_branch33a_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y2, MMCBlock3_mmLayer2_branch33b_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y3, MMCBlock3_mmLayer2_branch33c_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer1_CHANNELS,
                tmp2,
                MMCBlock3_mmLayer2_branch11_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer2_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride 
                MMCBlock3_mmLayer2_branch11_bn_gamma,
                MMCBlock3_mmLayer2_branch11_bn_beta,
                MMCBlock3_mmLayer2_branch11_bn_running_mean,
                MMCBlock3_mmLayer2_branch11_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer2_branch11_CHANNELS,
                y0,
                MMCBlock3_mmLayer2_branch33a_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer2_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer2_branch33a_bn_gamma,
                MMCBlock3_mmLayer2_branch33a_bn_beta,
                MMCBlock3_mmLayer2_branch33a_bn_running_mean,
                MMCBlock3_mmLayer2_branch33a_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer2_branch33a_CHANNELS,
                y1,
                MMCBlock3_mmLayer2_branch33b_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer2_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer2_branch33b_bn_gamma,
                MMCBlock3_mmLayer2_branch33b_bn_beta,
                MMCBlock3_mmLayer2_branch33b_bn_running_mean,
                MMCBlock3_mmLayer2_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer2_branch33b_CHANNELS,
                y2,
                MMCBlock3_mmLayer2_branch33c_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer2_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer2_branch33c_bn_gamma,
                MMCBlock3_mmLayer2_branch33c_bn_beta,
                MMCBlock3_mmLayer2_branch33c_bn_running_mean,
                MMCBlock3_mmLayer2_branch33c_bn_deviation
            );

            concat4 (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer1_CHANNELS,
                MMCBlock3_mmLayer2_branch33a_CHANNELS,
                MMCBlock3_mmLayer2_branch33b_CHANNELS,
                MMCBlock3_mmLayer2_branch33c_CHANNELS,
                tmp2,
                y1, 
                y2, 
                y3, 
                tmp1
            );
        //}}}
        //-----------------------------------------------
        //                  Layer3
        //-----------------------------------------------
        //{{{
            vector_memset0(y0, MMCBlock3_mmLayer3_branch11_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y1, MMCBlock3_mmLayer3_branch33a_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y2, MMCBlock3_mmLayer3_branch33b_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y3, MMCBlock3_mmLayer3_branch33c_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer2_CHANNELS,
                tmp1,
                MMCBlock3_mmLayer3_branch11_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer3_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer3_branch11_bn_gamma,
                MMCBlock3_mmLayer3_branch11_bn_beta,
                MMCBlock3_mmLayer3_branch11_bn_running_mean,
                MMCBlock3_mmLayer3_branch11_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer3_branch11_CHANNELS,
                y0,
                MMCBlock3_mmLayer3_branch33a_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer3_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride 
                MMCBlock3_mmLayer3_branch33a_bn_gamma,
                MMCBlock3_mmLayer3_branch33a_bn_beta,
                MMCBlock3_mmLayer3_branch33a_bn_running_mean,
                MMCBlock3_mmLayer3_branch33a_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer3_branch33a_CHANNELS,
                y1,
                MMCBlock3_mmLayer3_branch33b_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer3_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer3_branch33b_bn_gamma,
                MMCBlock3_mmLayer3_branch33b_bn_beta,
                MMCBlock3_mmLayer3_branch33b_bn_running_mean,
                MMCBlock3_mmLayer3_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer3_branch33b_CHANNELS,
                y2,
                MMCBlock3_mmLayer3_branch33c_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer3_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer3_branch33c_bn_gamma,
                MMCBlock3_mmLayer3_branch33c_bn_beta,
                MMCBlock3_mmLayer3_branch33c_bn_running_mean,
                MMCBlock3_mmLayer3_branch33c_bn_deviation
            );

            concat4 (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer2_CHANNELS,
                MMCBlock3_mmLayer3_branch33a_CHANNELS,
                MMCBlock3_mmLayer3_branch33b_CHANNELS,
                MMCBlock3_mmLayer3_branch33c_CHANNELS,
                tmp1,
                y1, 
                y2, 
                y3, 
                tmp2
            );
        //}}}
        //-----------------------------------------------
        //                  Layer4
        //-----------------------------------------------
        //{{{
            vector_memset0(y0, MMCBlock3_mmLayer4_branch11_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y1, MMCBlock3_mmLayer4_branch33a_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y2, MMCBlock3_mmLayer4_branch33b_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y3, MMCBlock3_mmLayer4_branch33c_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer3_CHANNELS,
                tmp2,
                MMCBlock3_mmLayer4_branch11_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer4_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer4_branch11_bn_gamma,
                MMCBlock3_mmLayer4_branch11_bn_beta,
                MMCBlock3_mmLayer4_branch11_bn_running_mean,
                MMCBlock3_mmLayer4_branch11_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer4_branch11_CHANNELS,
                y0,
                MMCBlock3_mmLayer4_branch33a_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer4_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride 
                MMCBlock3_mmLayer4_branch33a_bn_gamma,
                MMCBlock3_mmLayer4_branch33a_bn_beta,
                MMCBlock3_mmLayer4_branch33a_bn_running_mean,
                MMCBlock3_mmLayer4_branch33a_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer4_branch33a_CHANNELS,
                y1,
                MMCBlock3_mmLayer4_branch33b_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer4_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer4_branch33b_bn_gamma,
                MMCBlock3_mmLayer4_branch33b_bn_beta,
                MMCBlock3_mmLayer4_branch33b_bn_running_mean,
                MMCBlock3_mmLayer4_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer4_branch33b_CHANNELS,
                y2,
                MMCBlock3_mmLayer4_branch33c_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer4_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer4_branch33c_bn_gamma,
                MMCBlock3_mmLayer4_branch33c_bn_beta,
                MMCBlock3_mmLayer4_branch33c_bn_running_mean,
                MMCBlock3_mmLayer4_branch33c_bn_deviation
            );

            concat4 (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer3_CHANNELS,
                MMCBlock3_mmLayer4_branch33a_CHANNELS,
                MMCBlock3_mmLayer4_branch33b_CHANNELS,
                MMCBlock3_mmLayer4_branch33c_CHANNELS,
                tmp2,
                y1, 
                y2, 
                y3, 
                tmp1
            );
        //}}}
        //-----------------------------------------------
        //                  Layer5
        //-----------------------------------------------
        //{{{
            vector_memset0(y0, MMCBlock3_mmLayer5_branch11_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y1, MMCBlock3_mmLayer5_branch33a_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y2, MMCBlock3_mmLayer5_branch33b_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y3, MMCBlock3_mmLayer5_branch33c_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer4_CHANNELS,
                tmp1,
                MMCBlock3_mmLayer5_branch11_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer5_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer5_branch11_bn_gamma,
                MMCBlock3_mmLayer5_branch11_bn_beta,
                MMCBlock3_mmLayer5_branch11_bn_running_mean,
                MMCBlock3_mmLayer5_branch11_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer5_branch11_CHANNELS,
                y0,
                MMCBlock3_mmLayer5_branch33a_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer5_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride 
                MMCBlock3_mmLayer5_branch33a_bn_gamma,
                MMCBlock3_mmLayer5_branch33a_bn_beta,
                MMCBlock3_mmLayer5_branch33a_bn_running_mean,
                MMCBlock3_mmLayer5_branch33a_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer5_branch33a_CHANNELS,
                y1,
                MMCBlock3_mmLayer5_branch33b_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer5_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer5_branch33b_bn_gamma,
                MMCBlock3_mmLayer5_branch33b_bn_beta,
                MMCBlock3_mmLayer5_branch33b_bn_running_mean,
                MMCBlock3_mmLayer5_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer5_branch33b_CHANNELS,
                y2,
                MMCBlock3_mmLayer5_branch33c_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer5_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer5_branch33c_bn_gamma,
                MMCBlock3_mmLayer5_branch33c_bn_beta,
                MMCBlock3_mmLayer5_branch33c_bn_running_mean,
                MMCBlock3_mmLayer5_branch33c_bn_deviation
            );

            concat4 (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer4_CHANNELS,
                MMCBlock3_mmLayer5_branch33a_CHANNELS,
                MMCBlock3_mmLayer5_branch33b_CHANNELS,
                MMCBlock3_mmLayer5_branch33c_CHANNELS,
                tmp1,
                y1, 
                y2, 
                y3, 
                tmp2
            );
        //}}}
        //-----------------------------------------------
        //                  Layer6
        //-----------------------------------------------
        //{{{
            vector_memset0(y0, MMCBlock3_mmLayer6_branch11_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y1, MMCBlock3_mmLayer6_branch33a_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y2, MMCBlock3_mmLayer6_branch33b_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y3, MMCBlock3_mmLayer6_branch33c_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer5_CHANNELS,
                tmp2,
                MMCBlock3_mmLayer6_branch11_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer6_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer6_branch11_bn_gamma,
                MMCBlock3_mmLayer6_branch11_bn_beta,
                MMCBlock3_mmLayer6_branch11_bn_running_mean,
                MMCBlock3_mmLayer6_branch11_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer6_branch11_CHANNELS,
                y0,
                MMCBlock3_mmLayer6_branch33a_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer6_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride 
                MMCBlock3_mmLayer6_branch33a_bn_gamma,
                MMCBlock3_mmLayer6_branch33a_bn_beta,
                MMCBlock3_mmLayer6_branch33a_bn_running_mean,
                MMCBlock3_mmLayer6_branch33a_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer6_branch33a_CHANNELS,
                y1,
                MMCBlock3_mmLayer6_branch33b_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer6_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer6_branch33b_bn_gamma,
                MMCBlock3_mmLayer6_branch33b_bn_beta,
                MMCBlock3_mmLayer6_branch33b_bn_running_mean,
                MMCBlock3_mmLayer6_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer6_branch33b_CHANNELS,
                y2,
                MMCBlock3_mmLayer6_branch33c_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer6_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer6_branch33c_bn_gamma,
                MMCBlock3_mmLayer6_branch33c_bn_beta,
                MMCBlock3_mmLayer6_branch33c_bn_running_mean,
                MMCBlock3_mmLayer6_branch33c_bn_deviation
            );

            concat4 (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer5_CHANNELS,
                MMCBlock3_mmLayer6_branch33a_CHANNELS,
                MMCBlock3_mmLayer6_branch33b_CHANNELS,
                MMCBlock3_mmLayer6_branch33c_CHANNELS,
                tmp2,
                y1, 
                y2, 
                y3, 
                tmp1
            );
        //}}}
        //-----------------------------------------------
        //                  Layer7
        //-----------------------------------------------
        //{{{
            vector_memset0(y0, MMCBlock3_mmLayer7_branch11_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y1, MMCBlock3_mmLayer7_branch33a_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y2, MMCBlock3_mmLayer7_branch33b_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y3, MMCBlock3_mmLayer7_branch33c_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer6_CHANNELS,
                tmp1,
                MMCBlock3_mmLayer7_branch11_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer7_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer7_branch11_bn_gamma,
                MMCBlock3_mmLayer7_branch11_bn_beta,
                MMCBlock3_mmLayer7_branch11_bn_running_mean,
                MMCBlock3_mmLayer7_branch11_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer7_branch11_CHANNELS,
                y0,
                MMCBlock3_mmLayer7_branch33a_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer7_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride 
                MMCBlock3_mmLayer7_branch33a_bn_gamma,
                MMCBlock3_mmLayer7_branch33a_bn_beta,
                MMCBlock3_mmLayer7_branch33a_bn_running_mean,
                MMCBlock3_mmLayer7_branch33a_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer7_branch33a_CHANNELS,
                y1,
                MMCBlock3_mmLayer7_branch33b_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer7_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer7_branch33b_bn_gamma,
                MMCBlock3_mmLayer7_branch33b_bn_beta,
                MMCBlock3_mmLayer7_branch33b_bn_running_mean,
                MMCBlock3_mmLayer7_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer7_branch33b_CHANNELS,
                y2,
                MMCBlock3_mmLayer7_branch33c_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer7_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer7_branch33c_bn_gamma,
                MMCBlock3_mmLayer7_branch33c_bn_beta,
                MMCBlock3_mmLayer7_branch33c_bn_running_mean,
                MMCBlock3_mmLayer7_branch33c_bn_deviation
            );

            concat4 (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer6_CHANNELS,
                MMCBlock3_mmLayer7_branch33a_CHANNELS,
                MMCBlock3_mmLayer7_branch33b_CHANNELS,
                MMCBlock3_mmLayer7_branch33c_CHANNELS,
                tmp1,
                y1, 
                y2, 
                y3, 
                tmp2
            );
        //}}}
        //-----------------------------------------------
        //                  Layer8
        //-----------------------------------------------
        //{{{
            vector_memset0(y0, MMCBlock3_mmLayer8_branch11_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y1, MMCBlock3_mmLayer8_branch33a_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y2, MMCBlock3_mmLayer8_branch33b_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);
            vector_memset0(y3, MMCBlock3_mmLayer8_branch33c_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer7_CHANNELS,
                tmp2,
                MMCBlock3_mmLayer8_branch11_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer8_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer8_branch11_bn_gamma,
                MMCBlock3_mmLayer8_branch11_bn_beta,
                MMCBlock3_mmLayer8_branch11_bn_running_mean,
                MMCBlock3_mmLayer8_branch11_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer8_branch11_CHANNELS,
                y0,
                MMCBlock3_mmLayer8_branch33a_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer8_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride 
                MMCBlock3_mmLayer8_branch33a_bn_gamma,
                MMCBlock3_mmLayer8_branch33a_bn_beta,
                MMCBlock3_mmLayer8_branch33a_bn_running_mean,
                MMCBlock3_mmLayer8_branch33a_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer8_branch33a_CHANNELS,
                y1,
                MMCBlock3_mmLayer8_branch33b_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer8_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer8_branch33b_bn_gamma,
                MMCBlock3_mmLayer8_branch33b_bn_beta,
                MMCBlock3_mmLayer8_branch33b_bn_running_mean,
                MMCBlock3_mmLayer8_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer8_branch33b_CHANNELS,
                y2,
                MMCBlock3_mmLayer8_branch33c_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer8_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock3_mmLayer8_branch33c_bn_gamma,
                MMCBlock3_mmLayer8_branch33c_bn_beta,
                MMCBlock3_mmLayer8_branch33c_bn_running_mean,
                MMCBlock3_mmLayer8_branch33c_bn_deviation
            );

            concat4 (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                MMCBlock3_mmLayer7_CHANNELS,
                MMCBlock3_mmLayer8_branch33a_CHANNELS,
                MMCBlock3_mmLayer8_branch33b_CHANNELS,
                MMCBlock3_mmLayer8_branch33c_CHANNELS,
                tmp2,
                y1, 
                y2, 
                y3, 
                tmp1
            );
        //}}}
        //-----------------------------------------------
        //                  Conv3
        //-----------------------------------------------
        //{{{
            vector_memset0(tmp2, STAGE_4_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);

            _conv_block (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                STAGE_4_CHANNELS,
                tmp1,
                tran_ConvNormRelu3_conv_weight,
                NULL,   // bias
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                STAGE_4_CHANNELS,
                tmp2,
                1,      // kernel_size
                1,      // stride
                tran_ConvNormRelu3_bn_gamma,
                tran_ConvNormRelu3_bn_beta,
                tran_ConvNormRelu3_bn_running_mean,
                tran_ConvNormRelu3_bn_deviation
            );
        //}}}
        //-----------------------------------------------
        //                 Pooling3 
        //-----------------------------------------------
        //{{{
            vector_memset0(tmp1, STAGE_4_CHANNELS*STAGE_4_HEIGHT*STAGE_4_WIDTH);

            avg_pool (
                STAGE_3_HEIGHT,
                STAGE_3_WIDTH,
                STAGE_4_CHANNELS,
                tmp2,
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                STAGE_4_CHANNELS,
                tmp1
            );
        //}}}
    //}}}
    //-------------------------------------------
    //              STAGE_5
    //-------------------------------------------
    //{{{
        //-----------------------------------------------
        //                  Layer1
        //-----------------------------------------------
        //{{{
            vector_memset0(y0, MMCBlock4_mmLayer1_branch11_CHANNELS*STAGE_4_HEIGHT*STAGE_4_WIDTH);
            vector_memset0(y1, MMCBlock4_mmLayer1_branch33a_CHANNELS*STAGE_4_HEIGHT*STAGE_4_WIDTH);
            vector_memset0(y2, MMCBlock4_mmLayer1_branch33b_CHANNELS*STAGE_4_HEIGHT*STAGE_4_WIDTH);
            vector_memset0(y3, MMCBlock4_mmLayer1_branch33c_CHANNELS*STAGE_4_HEIGHT*STAGE_4_WIDTH);

            _conv_block (
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                STAGE_4_CHANNELS,
                tmp1,
                MMCBlock4_mmLayer1_branch11_conv_weight,
                NULL,   // bias
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer1_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride
                MMCBlock4_mmLayer1_branch11_bn_gamma,
                MMCBlock4_mmLayer1_branch11_bn_beta,
                MMCBlock4_mmLayer1_branch11_bn_running_mean,
                MMCBlock4_mmLayer1_branch11_bn_deviation
            );

            _conv_block (
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer1_branch11_CHANNELS,
                y0,
                MMCBlock4_mmLayer1_branch33a_conv_weight,
                NULL,   // bias
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer1_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride
                MMCBlock4_mmLayer1_branch33a_bn_gamma,
                MMCBlock4_mmLayer1_branch33a_bn_beta,
                MMCBlock4_mmLayer1_branch33a_bn_running_mean,
                MMCBlock4_mmLayer1_branch33a_bn_deviation
            );

            _conv_block (
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer1_branch33a_CHANNELS,
                y1,
                MMCBlock4_mmLayer1_branch33b_conv_weight,
                NULL,   // bias
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer1_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock4_mmLayer1_branch33b_bn_gamma,
                MMCBlock4_mmLayer1_branch33b_bn_beta,
                MMCBlock4_mmLayer1_branch33b_bn_running_mean,
                MMCBlock4_mmLayer1_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer1_branch33b_CHANNELS,
                y2,
                MMCBlock4_mmLayer1_branch33c_conv_weight,
                NULL,   // bias
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer1_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock4_mmLayer1_branch33c_bn_gamma,
                MMCBlock4_mmLayer1_branch33c_bn_beta,
                MMCBlock4_mmLayer1_branch33c_bn_running_mean,
                MMCBlock4_mmLayer1_branch33c_bn_deviation
            );

            concat4 (
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                STAGE_4_CHANNELS,
                MMCBlock4_mmLayer1_branch33a_CHANNELS,
                MMCBlock4_mmLayer1_branch33b_CHANNELS,
                MMCBlock4_mmLayer1_branch33c_CHANNELS,
                tmp1,
                y1, 
                y2, 
                y3, 
                tmp2
            );
        //}}} 
        //-----------------------------------------------
        //                  Layer2
        //-----------------------------------------------
        //{{{
            vector_memset0(y0, MMCBlock4_mmLayer2_branch11_CHANNELS*STAGE_4_HEIGHT*STAGE_4_WIDTH);
            vector_memset0(y1, MMCBlock4_mmLayer2_branch33a_CHANNELS*STAGE_4_HEIGHT*STAGE_4_WIDTH);
            vector_memset0(y2, MMCBlock4_mmLayer2_branch33b_CHANNELS*STAGE_4_HEIGHT*STAGE_4_WIDTH);
            vector_memset0(y3, MMCBlock4_mmLayer2_branch33c_CHANNELS*STAGE_4_HEIGHT*STAGE_4_WIDTH);

            _conv_block (
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer1_CHANNELS,
                tmp2,
                MMCBlock4_mmLayer2_branch11_conv_weight,
                NULL,   // bias
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer2_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride 
                MMCBlock4_mmLayer2_branch11_bn_gamma,
                MMCBlock4_mmLayer2_branch11_bn_beta,
                MMCBlock4_mmLayer2_branch11_bn_running_mean,
                MMCBlock4_mmLayer2_branch11_bn_deviation
            );

            _conv_block (
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer2_branch11_CHANNELS,
                y0,
                MMCBlock4_mmLayer2_branch33a_conv_weight,
                NULL,   // bias
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer2_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride
                MMCBlock4_mmLayer2_branch33a_bn_gamma,
                MMCBlock4_mmLayer2_branch33a_bn_beta,
                MMCBlock4_mmLayer2_branch33a_bn_running_mean,
                MMCBlock4_mmLayer2_branch33a_bn_deviation
            );

            _conv_block (
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer2_branch33a_CHANNELS,
                y1,
                MMCBlock4_mmLayer2_branch33b_conv_weight,
                NULL,   // bias
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer2_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock4_mmLayer2_branch33b_bn_gamma,
                MMCBlock4_mmLayer2_branch33b_bn_beta,
                MMCBlock4_mmLayer2_branch33b_bn_running_mean,
                MMCBlock4_mmLayer2_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer2_branch33b_CHANNELS,
                y2,
                MMCBlock4_mmLayer2_branch33c_conv_weight,
                NULL,   // bias
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer2_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock4_mmLayer2_branch33c_bn_gamma,
                MMCBlock4_mmLayer2_branch33c_bn_beta,
                MMCBlock4_mmLayer2_branch33c_bn_running_mean,
                MMCBlock4_mmLayer2_branch33c_bn_deviation
            );

            concat4 (
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer1_CHANNELS,
                MMCBlock4_mmLayer2_branch33a_CHANNELS,
                MMCBlock4_mmLayer2_branch33b_CHANNELS,
                MMCBlock4_mmLayer2_branch33c_CHANNELS,
                tmp2,
                y1, 
                y2, 
                y3, 
                tmp1
            );
        //}}}
        //-----------------------------------------------
        //                  Layer3
        //-----------------------------------------------
        //{{{
            vector_memset0(y0, MMCBlock4_mmLayer3_branch11_CHANNELS*STAGE_4_HEIGHT*STAGE_4_WIDTH);
            vector_memset0(y1, MMCBlock4_mmLayer3_branch33a_CHANNELS*STAGE_4_HEIGHT*STAGE_4_WIDTH);
            vector_memset0(y2, MMCBlock4_mmLayer3_branch33b_CHANNELS*STAGE_4_HEIGHT*STAGE_4_WIDTH);
            vector_memset0(y3, MMCBlock4_mmLayer3_branch33c_CHANNELS*STAGE_4_HEIGHT*STAGE_4_WIDTH);

            _conv_block (
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer2_CHANNELS,
                tmp1,
                MMCBlock4_mmLayer3_branch11_conv_weight,
                NULL,   // bias
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer3_branch11_CHANNELS,
                y0,
                1,      // kernel_size
                1,      // stride
                MMCBlock4_mmLayer3_branch11_bn_gamma,
                MMCBlock4_mmLayer3_branch11_bn_beta,
                MMCBlock4_mmLayer3_branch11_bn_running_mean,
                MMCBlock4_mmLayer3_branch11_bn_deviation
            );

            _conv_block (
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer3_branch11_CHANNELS,
                y0,
                MMCBlock4_mmLayer3_branch33a_conv_weight,
                NULL,   // bias
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer3_branch33a_CHANNELS,
                y1,
                3,      // kernel_size
                1,      // stride 
                MMCBlock4_mmLayer3_branch33a_bn_gamma,
                MMCBlock4_mmLayer3_branch33a_bn_beta,
                MMCBlock4_mmLayer3_branch33a_bn_running_mean,
                MMCBlock4_mmLayer3_branch33a_bn_deviation
            );

            _conv_block (
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer3_branch33a_CHANNELS,
                y1,
                MMCBlock4_mmLayer3_branch33b_conv_weight,
                NULL,   // bias
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer3_branch33b_CHANNELS,
                y2,
                3,      // kernel_size
                1,      // stride
                MMCBlock4_mmLayer3_branch33b_bn_gamma,
                MMCBlock4_mmLayer3_branch33b_bn_beta,
                MMCBlock4_mmLayer3_branch33b_bn_running_mean,
                MMCBlock4_mmLayer3_branch33b_bn_deviation
            );

            _conv_block (
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer3_branch33b_CHANNELS,
                y2,
                MMCBlock4_mmLayer3_branch33c_conv_weight,
                NULL,   // bias
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer3_branch33c_CHANNELS,
                y3,
                3,      // kernel_size
                1,      // stride
                MMCBlock4_mmLayer3_branch33c_bn_gamma,
                MMCBlock4_mmLayer3_branch33c_bn_beta,
                MMCBlock4_mmLayer3_branch33c_bn_running_mean,
                MMCBlock4_mmLayer3_branch33c_bn_deviation
            );

            concat4 (
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                MMCBlock4_mmLayer2_CHANNELS,
                MMCBlock4_mmLayer3_branch33a_CHANNELS,
                MMCBlock4_mmLayer3_branch33b_CHANNELS,
                MMCBlock4_mmLayer3_branch33c_CHANNELS,
                tmp1,
                y1, 
                y2, 
                y3, 
                tmp2
            );
        //}}}
        //-----------------------------------------------
        //                  Conv4
        //-----------------------------------------------
        //{{{
            vector_memset0(tmp1, STAGE_4_CHANNELS*STAGE_3_HEIGHT*STAGE_3_WIDTH);

            _conv_block (
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                STAGE_5_CHANNELS,
                tmp2,
                tran_ConvNormRelu4_conv_weight,
                NULL,   // bias
                STAGE_4_HEIGHT,
                STAGE_4_WIDTH,
                STAGE_5_CHANNELS,
                tmp1,
                1,      // kernel_size
                1,      // stride
                tran_ConvNormRelu4_bn_gamma,
                tran_ConvNormRelu4_bn_beta,
                tran_ConvNormRelu4_bn_running_mean,
                tran_ConvNormRelu4_bn_deviation
            );
        //}}}

        //-----------------------------------------------
        //            Global Average Pool 
        //-----------------------------------------------
        //{{{
            vector_memset0(tmp2, STAGE_5_CHANNELS);

            global_avg_pool (
                STAGE_5_HEIGHT,
                STAGE_5_WIDTH,
                STAGE_5_CHANNELS,
                tmp1,
                tmp2
            );
        //}}}
    //}}}
    //-------------------------------------------
    //              STAGE_6
    //-------------------------------------------
    //{{{
            vector_memset0(tmp1, STAGE_6_CLASSES);

            _fc (
                STAGE_5_CHANNELS,
                tmp2,
                classifier_weight,
                classifier_bias,
                STAGE_6_CLASSES,
                tmp1
            );

            int pred = 0;
            type argmax = tmp1[0];

            for (int i=0; i<STAGE_6_CLASSES; i++)
            {
                if (argmax < tmp1[i])
                {
                    argmax = tmp1[i];
                    pred = i;
                }
            }
    //}}}

        // int target;
        // fscanf(preds_file, "%d", &target);
        // confusion_matrix[target][pred]++;

        printf("[!] (sample, class, pred) = (%d, %d, %d)\n", n_sample, pred, argmax);

        cycles_end = csr_read_mcycle();
        cycles[n_sample] = cycles_end - cycles_start;
        // printf("[!] Scalar LMFRNet: %lu cycles!\n", cycles[n_sample]);
        // printf("[!] Vectorized LMFRNet (256b): %lu cycles!\n", cycles[n_sample]);
        printf("[VECTOR] The execution took %ld cycles.\n", cycles[n_sample]);
        // printf("[SCALAR] The execution took %ld cycles.\n", cycles[n_sample]);

        free(y0);
        free(y1);
        free(y2);
        free(y3);
        free(tmp1);
        free(tmp2);

        // free(filename);
    }

    // save_confusion_matrix();
    // fclose(preds_file);

    return 0;
}
