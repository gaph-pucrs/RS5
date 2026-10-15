#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "params/1_in.h"
#include "params/1_weight.h"
#include "params/1_bias.h"

#include "params/2_weight.h"
#include "params/2_bias.h"

/******* Layer Conv 1 ********/
#define FILTER_HEIGHT_1 11
#define FILTER_WIDTH_1 11
#define IN_HEIGHT_1 227
#define IN_WIDTH_1 227
#define IN_DEPTH_1 3
#define OUT_CONV_HEIGHT_1 55
#define OUT_CONV_WIDTH_1 55
#define OUT_HEIGHT_1 27
#define OUT_WIDTH_1 27
#define OUT_DEPTH_1 96
// #define OUT_DEPTH_1        2
#define STRIDE_CONV_1 4
#define STRIDE_MAX_1 2
#define POOL_SIZE_1 3
/*****************************/

/******* Layer Conv 2 ********/
#define PAD_IN_2 2
#define FILTER_HEIGHT_2 5
#define FILTER_WIDTH_2 5
#define IN_HEIGHT_2 31
#define IN_WIDTH_2 31
#define IN_DEPTH_2 96
// #define IN_DEPTH_2        2
#define OUT_CONV_HEIGHT_2 27
#define OUT_CONV_WIDTH_2 27
#define OUT_HEIGHT_2 13
#define OUT_WIDTH_2 13
#define OUT_DEPTH_2 256
// #define OUT_DEPTH_2       4
#define STRIDE_CONV_2 1
#define STRIDE_MAX_2 2
#define POOL_SIZE_2 3
/*****************************/

int conv_kernel(int *in_line, int *filter_slice, const unsigned int kernel_height, const unsigned int kernel_width, const unsigned int input_width)
{
    int *in_el = in_line;
    int *f_el = filter_slice;
    int sum = 0.0;

    for (unsigned f_y = 0; f_y < kernel_height; f_y++)
    {
        for (unsigned f_x = 0; f_x < kernel_width; f_x++)
        {
            sum += f_el[f_x] * in_el[f_x];
        }
        f_el += kernel_width;
        in_el += input_width;
    }

    return sum;
}

int* conv_channel(const unsigned int input_depth, const int weights[],
                  unsigned int o_channel, unsigned int i_channel, const unsigned int kernel_height, const unsigned int kernel_width, const int in[],
                  const unsigned int input_height, const unsigned int input_width, const unsigned int output_height, const unsigned int output_width, const unsigned int stride)
{
    int *filter_slice = &weights[(o_channel * kernel_height * kernel_width * input_depth) + (i_channel * kernel_height * kernel_width)];
    int *in_slice = &in[i_channel * input_height * input_width];
    unsigned ls = stride * input_height;

    size_t alloc_size = output_height * output_width;
    int *out_slice = malloc(alloc_size * sizeof(int));
    if (!out_slice)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    };

    // Inicializa
    for (unsigned i = 0; i < output_height * output_width; ++i)
    {
        out_slice[i] = 0;
    }

    int *o_line = out_slice;

    for (unsigned o_y = 0; o_y < output_height; o_y++)
    {
        int *in_line = in_slice;
        for (unsigned o_x = 0; o_x < output_width; o_x++)
        {
            int sum = conv_kernel(in_line, filter_slice, kernel_height, kernel_width, input_width);
            o_line[o_x] += sum;

            in_line += stride;
        }
        o_line += output_width;
        in_slice += ls;
    }

    return out_slice;
}

void conv_sum_bias(const unsigned int output_height, const unsigned int output_width, int *out_slice, const int bias[], unsigned int o_channel)
{
    for (unsigned o_x = 0; o_x < output_height * output_width; o_x++)
    {
        out_slice[o_x] += bias[o_channel];
        out_slice[o_x]  = out_slice[o_x] / 1024;
    }
}

void conv(const int in[], const int weights[], const int bias[], int out[],
          const unsigned kernel_height, const unsigned kernel_width,
          const unsigned input_height,  const unsigned input_width,  const unsigned input_depth,
          const unsigned output_height, const unsigned output_width, const unsigned output_depth,
          const unsigned stride)
{

    for (unsigned o_channel = 0; o_channel < output_depth; o_channel++)
    {
        int *out_slice = &out[o_channel * output_height * output_width];

        for (unsigned i_channel = 0; i_channel < input_depth; i_channel++)
        {
            int* result = conv_channel(input_depth, weights, o_channel, i_channel, kernel_height, kernel_width, in, input_height, input_width, output_height, output_width, stride);

            for (unsigned o_x = 0; o_x < output_height * output_width; o_x++)
            {
                out_slice[o_x] += result[o_x];
            }
        }

        conv_sum_bias(output_height, output_width, out_slice, bias, o_channel);
    }
}

void relu(int in[], const unsigned input_height, const unsigned input_width, const unsigned input_depth)
{
    unsigned size = input_height * input_width * input_depth;
    unsigned i;

    for (i = 0; i < size; ++i)
    {
        if (in[i] < 0.0)
        {
            in[i] = 0.0;
        }
    }
}

void pad(int in[], int out[],
         const unsigned input_height, const unsigned input_width, const unsigned input_depth,
         const unsigned pad)
{
    unsigned output_height = input_height + 2 * pad;
    unsigned output_width = input_width + 2 * pad;
    unsigned d, x, y, o_idx, i_idx;

    for (d = 0; d < input_depth; ++d)
    {
        for (y = 0; y < output_height; ++y)
        {
            for (x = 0; x < output_width; ++x)
            {

                o_idx = (output_height * d + y) * output_width + x;
                i_idx = 0;
                if (y < pad || y > (input_height + pad - 1) || x < pad || x > (input_width + pad - 1))
                {
                    out[o_idx] = 0.0;
                }
                else
                {
                    i_idx = (input_height * d + y - pad) * input_width + x - pad;
                    out[o_idx] = in[i_idx];
                }
            }
        }
    }
}

void maxpool(int in[], int out[],
             const unsigned input_height,  const unsigned input_width,  const unsigned input_depth,
             const unsigned output_height, const unsigned output_width, const unsigned output_depth,
             const unsigned stride,        const unsigned ps)
{
    // Assuming input values above zero (in our case maxpool always come after a relu)

    unsigned x_o, y_o, k, wx, wy;
    unsigned in_idx, out_idx;
    int max;

    for (k = 0; k < output_depth; ++k)
    {
        for (y_o = 0; y_o < output_height; y_o++)
        {
            for (x_o = 0; x_o < output_width; x_o++)
            {
                max = 0.0;
                for (wy = 0; wy < ps; wy++)
                {
                    for (wx = 0; wx < ps; wx++)
                    {
                        in_idx = (input_height * k + (y_o * stride + wy)) * input_width + (x_o * stride + wx);
                        if (in[in_idx] > max)
                        {
                            max = in[in_idx];
                        }
                    }
                }
                out_idx = (output_height * k + y_o) * output_width + x_o;
                out[out_idx] = max;
            }
        }
    }
}

/******************************** MAIN ***********************************/
/******************************** MAIN ***********************************/
/******************************** MAIN ***********************************/

int main(int argc, char **argv)
{
    size_t alloc_size;

    unsigned i;
    unsigned o_x;

    /******************************** Layer 1 ***********************************/
    // alloc_size = OUT_CONV_WIDTH_1 * OUT_CONV_HEIGHT_1 * OUT_DEPTH_1;
    // int *out_1 = malloc(alloc_size * sizeof(int));
    // if (!out_1)
    // {
    //     perror("malloc failed");
    //     exit(EXIT_FAILURE);
    // };
    static int out_1[OUT_CONV_WIDTH_1 * OUT_CONV_HEIGHT_1 * OUT_DEPTH_1];

    // Inicializa out_1
    for (i = 0; i < OUT_CONV_WIDTH_1 * OUT_CONV_HEIGHT_1 * OUT_DEPTH_1; ++i)
    {
        out_1[i] = 0;
    }

    conv(in_1, weight_1, bias_1, out_1,
         FILTER_HEIGHT_1, FILTER_WIDTH_1,
         IN_HEIGHT_1, IN_WIDTH_1, IN_DEPTH_1,
         OUT_CONV_HEIGHT_1, OUT_CONV_WIDTH_1, OUT_DEPTH_1,
         STRIDE_CONV_1);

    // FILE *out_f_w = fopen("transfer_files/NET_OUT_1.dat", "w");
    // for (o_x = 0; o_x < OUT_CONV_WIDTH_1 * OUT_CONV_HEIGHT_1 * OUT_DEPTH_1; o_x++)
    // {
    //     printf("%d\n", out_1[o_x]);
    // }

    relu(out_1, OUT_CONV_HEIGHT_1, OUT_CONV_WIDTH_1, OUT_DEPTH_1);

    // alloc_size = OUT_HEIGHT_1 * OUT_WIDTH_1 * OUT_DEPTH_1;
    // int *out_pool_1 = malloc(alloc_size * sizeof(int));
    // if (!out_pool_1)
    // {
    //     perror("malloc failed");
    //     exit(EXIT_FAILURE);
    // };
    static int out_pool_1[OUT_HEIGHT_1 * OUT_WIDTH_1 * OUT_DEPTH_1];

    maxpool(out_1, out_pool_1, OUT_CONV_HEIGHT_1, OUT_CONV_WIDTH_1, OUT_DEPTH_1,
            OUT_HEIGHT_1, OUT_WIDTH_1, OUT_DEPTH_1,
            STRIDE_MAX_1, POOL_SIZE_1);

    /******************************** Layer 2 ***********************************/
    static int in_2[IN_HEIGHT_2 * IN_WIDTH_2 * IN_DEPTH_2];

    pad(out_pool_1, in_2, OUT_HEIGHT_1, OUT_WIDTH_1, OUT_DEPTH_1, PAD_IN_2);

    static int out_2[OUT_CONV_WIDTH_2 * OUT_CONV_HEIGHT_2 * OUT_DEPTH_2];

    // Inicializa out_2
    for (i = 0; i < OUT_CONV_WIDTH_2 * OUT_CONV_HEIGHT_2 * OUT_DEPTH_2; ++i)
    {
        out_2[i] = 0;
    }

    conv(in_2, weight_2, bias_2, out_2,
         FILTER_HEIGHT_2, FILTER_WIDTH_2,
         IN_HEIGHT_2, IN_WIDTH_2, IN_DEPTH_2,
         OUT_CONV_HEIGHT_2, OUT_CONV_WIDTH_2, OUT_DEPTH_2,
         STRIDE_CONV_2);

    // FILE *out_f_w2 = fopen("transfer_files/NET_OUT_2.dat", "w");
    // for (o_x = 0; o_x < OUT_CONV_WIDTH_2 * OUT_CONV_HEIGHT_2 * OUT_DEPTH_2; o_x++)
    // {
    //     fprintf(out_f_w2, "%d\n", out_2[o_x]);
    // }

    relu(out_2, OUT_CONV_HEIGHT_2, OUT_CONV_WIDTH_2, OUT_DEPTH_2);

    static int out_pool_2[OUT_HEIGHT_2 * OUT_WIDTH_2 * OUT_DEPTH_2];

    maxpool(out_2, out_pool_2, OUT_CONV_HEIGHT_2, OUT_CONV_WIDTH_2, OUT_DEPTH_2,
            OUT_HEIGHT_2, OUT_WIDTH_2, OUT_DEPTH_2,
            STRIDE_MAX_2, POOL_SIZE_2);

    return 0;
}