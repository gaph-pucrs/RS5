/* Conv, pad, ReLU and maxpool are identical to Memphis cnn5/cnn_common.h.
 * fc_layer is RS5-only (cnn5 has no FC layers). */

#include <stdlib.h>
#include <stdio.h>

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

int* conv_channel(  const          int weights[],     const int          in[],          const unsigned int input_depth,
                    unsigned       int o_channel,     unsigned int       i_channel,     const unsigned int kernel_height,
                    const unsigned int kernel_width,  const unsigned int input_height,  const unsigned int input_width,
                    const unsigned int output_height, const unsigned int output_width,  const unsigned int stride)
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
        out_slice[o_x] = out_slice[o_x] / 1024;
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

static inline void fc_layer(
    const int * __restrict__ weights,
    const int * __restrict__ in,
    const int * __restrict__ bias,
    int * __restrict__ out,
    const unsigned int in_size,
    const unsigned int out_size)
{
    for (unsigned int o = 0; o < out_size; o++)
    {
        int acc = bias[o];
        const int *w_row = &weights[o * in_size];

        for (unsigned int i = 0; i < in_size; i++)
            acc += w_row[i] * in[i];

        out[o] = acc >> 10;
    }
}
