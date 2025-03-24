#include <stdio.h>
#include <stdlib.h>

#define INPUT_HEIGHT    224
#define INPUT_WIDTH     224
#define INPUT_CHANNELS    3
#define CONV1_FEATUREMAP_HEIGHT 112
#define CONV1_FEATUREMAP_WIDTH  112

void _conv_block (
    const int input[],
    const int weights[],
    int output[], 
    int filters,
    const double alpha,
    const int kernel_size,
    const int stride
) {
    filters = (int)(filters*alpha);

    int *G = malloc(CONV1_FEATUREMAP_HEIGHT*CONV1_FEATUREMAP_WIDTH*filters*sizeof(int));

    const int offset1 = kernel_size*kernel_size;
    const int offset2 = INPUT_HEIGHT*INPUT_WIDTH;

    for (int k=0; k<CONV1_FEATUREMAP_HEIGHT; k++)
    {
        for (int l=0; l<CONV1_FEATUREMAP_WIDTH; l++)
        {
            for (int n=0; n<filters; n++)
            {
                int sum = 0;
                for (int m=0; m<INPUT_CHANNELS; m++)
                {
                    for (int i=0; i<kernel_size; i++)
                    {
                        for (int j=0; j<kernel_size; j++)
                        {
                            sum += weights[i+j+m*offset1] * input[
                        }
                    }
                }
                *G[<idx>] = sum/1000;
            }
        }
    }

    free(G);
}

int main()
{
    
    return 0;
}
