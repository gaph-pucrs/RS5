#include <stdio.h>
#include <stdlib.h>

#include "params/data.h"
#include "params/conv1.h"

#define INPUT_HEIGHT    224
#define INPUT_WIDTH     224
#define INPUT_CHANNELS    3
#define CONV1_FEATUREMAP_HEIGHT 112
#define CONV1_FEATUREMAP_WIDTH  112
#define CONV1_FILTERS       32

#define type    double

void batch_normaliztion (
    int input[],
    const int mean[],
    const int avg[]
) {
}

void relu (
    type input[]
) {
    const int size = CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH*CONV1_FILTERS;

    for (int i=0; i<size; i++) {
        if (input[i] < 0) {
            input[i] = 0;
        }
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
) {
    filters = (int)(filters*alpha);

    //type *G = malloc(CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH*filters*sizeof(type));

    const int offset1 = kernel_size*kernel_size;
    const int offset2 = INPUT_HEIGHT*INPUT_WIDTH;

    int basex = 0, basey = 0;
    for (int n=0; n<filters; n++)
    {
        basex = 0;
        for (int k=0; k<CONV1_FEATUREMAP_HEIGHT; k++)
        {
            basey = 0;
            for (int l=0; l<CONV1_FEATUREMAP_WIDTH; l++)
            {
                type sum = 0;
                for (int m=0; m<INPUT_CHANNELS; m++)
                {
                    for (int i=0; i<kernel_size; i++)
                    {
                        for (int j=0; j<kernel_size; j++)
                        {
                            int idw = j+i*kernel_size+m*offset1+n*INPUT_CHANNELS*offset1;
                            int idi = basex+basey+j+i*INPUT_WIDTH+m*offset2;
                            sum += weights[idw]*input[idi];
                        }
                    }
                }

                //*G[k*CONV1_FEATUREMAP_WIDTH + l] = sum/1000;
                int ido = k*CONV1_FEATUREMAP_WIDTH + l + n*CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH;
                output[ido] = sum;
                basey += stride;
            }
            
            basex += stride*INPUT_WIDTH;
        }

    }

    //relu(output);

    //free(G);
}

int main()
{
    
    double *output = malloc(CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH*CONV1_FILTERS*sizeof(double));

    _conv_block (
       img,
       conv1,
       output, 
       CONV1_FILTERS,
       1,
       3,
       2
    );

    const int size = CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH*CONV1_FILTERS;
    
    for (int i=0; i<size; i++) {
        printf("%lf\n", output[i]);
    }

    free(output);

    return 0;
}
