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

int conv_kernel(int *in_line, int *filter_slice, const unsigned int kernel_height, const unsigned int kernel_width, const unsigned int input_width);

void conv_channel(  const unsigned int input_depth,   const int          weights[],
                    unsigned int       o_channel,     unsigned int       i_channel,
                    const unsigned int kernel_height, const unsigned int kernel_width,
                    const int          in[],
                    const unsigned int input_height,  const unsigned int input_width,
                    const unsigned int output_height, const unsigned int output_width,
                    const unsigned int stride,                       int *outslice);

void conv(const int      in[],          const int      weights[],    const int       bias[],
          int            out[],         const unsigned kernel_height, const unsigned kernel_width,
          const unsigned input_height,  const unsigned input_width,   const unsigned input_depth,
          const unsigned output_height, const unsigned output_width,  const unsigned output_depth,
          const unsigned stride,        const unsigned process,       const unsigned channel,
          const unsigned PE_COUNT);

void conv_join(const int      bias[],        int            out[],        const unsigned input_depth,
               const unsigned output_height, const unsigned output_width, const unsigned output_depth,
               const unsigned process);

void conv_sum_bias(const unsigned int output_height, const unsigned int output_width, int *out_slice, const int bias[], unsigned int o_channel);

void pad(int in[], int out[],
         const unsigned input_height, const unsigned input_width, const unsigned input_depth,
         const unsigned pad);

void relu(int in[], const unsigned input_height, const unsigned input_width, const unsigned input_depth);

void maxpool(int in[], int out[],
             const unsigned input_height,  const unsigned input_width,  const unsigned input_depth,
             const unsigned output_height, const unsigned output_width, const unsigned output_depth,
             const unsigned stride,        const unsigned ps);
