// modifed Moraes  22/junho  11h15

#include <stdio.h>
#include <stdlib.h>
#include "lib/printf.h"

#include "params/0_bias_lut.h"
#include "params/3_bias_lut.h"
#include "params/6_bias_lut.h"
#include "params/0_weight_lut.h"
#include "params/3_weight_lut.h"
#include "params/6_weight_lut.h"
#include "params/classifier_1_weight_lut.h"
#include "params/classifier_2_weight_lut.h"
#include "params/classifier_1_bias_lut.h"
#include "params/classifier_2_bias_lut.h"

#include "params/0_weight_indices_compressed.h"
#include "params/0_bias_indices_compressed.h"
#include "params/3_weight_indices_compressed.h"
#include "params/3_bias_indices_compressed.h"
#include "params/6_weight_indices_compressed.h"
#include "params/6_bias_indices_compressed.h"
#include "params/classifier_1_bias_indices_compressed.h"
#include "params/classifier_1_weight_indices_compressed.h"
#include "params/classifier_2_bias_indices_compressed.h"
#include "params/classifier_2_weight_indices_compressed.h"


//// Main defines
#include "params/dataset120_eval_int.h" // 3923
#define BATCH_SIZE 32
#define DATASET_UNITS 1
#define INPUT_SIZE 120
#define NUM_FILTERS 64
#define KERNEL_SIZE 5
#define CONV0_INPUT_SIZE 120
#define CONV3_INPUT_SIZE 116
#define CONV6_INPUT_SIZE 112
#define FC1_OUTPUT_SIZE 128
#define FC2_OUTPUT_SIZE 5


// INT CNN defines
#define INPUT_MULTIP 1000 // This value MUST be the same used in Quantization


int main(){
    int i = 0;
    static int input_vector[INPUT_SIZE];
    int targetLabel;

    // Memory allocation to use compressed data
    // weight
    int weightCompressedData = 0;
    unsigned int weightCompressedIndex = 0;
    int weightDecompressedIndex = 0;
    // bias
    int biasCompressedData = 0;
    unsigned int biasCompressedIndex = 0;
    int biasDecompressedIndex = 0;

    // printf("##################################################### Starting Compressed\n");

    for(int datasetIndex = 0 ; datasetIndex < DATASET_UNITS ; datasetIndex++ ){

        // DATASET READING AND PREPARATION
        int startingIndex = datasetIndex * 121; //input + label
        targetLabel = dataset120[startingIndex + INPUT_SIZE]/INPUT_MULTIP;

        for(i = 0 ; i < INPUT_SIZE ; i++){
            input_vector[i] = dataset120[startingIndex + i];
        }


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// LAYER 1
    // CONVOLUTION 1
        static int INTconv0_featureMap[NUM_FILTERS][CONV0_INPUT_SIZE-4];
        static int INTconv0_currentKernel[KERNEL_SIZE];
        int INTconv0_current_bias = 0;


        //printf(" Conv0 #################################################################\n");
        for (int k = 0; k < NUM_FILTERS; k++)
        {
            // Load Current Weights
            for (i = 0; i < KERNEL_SIZE; i++)
            {
                int realIndex = i + (k * KERNEL_SIZE);

                weightDecompressedIndex = realIndex & 7;   // 3 bits menos significativos (indice)
                weightCompressedIndex   = realIndex >> 3;  // divide por 8
                if (!weightDecompressedIndex)              // se for zero tem que acessar um novo valor
                    weightCompressedData = conv0_weights_indices_compressed[weightCompressedIndex];

                INTconv0_currentKernel[i] = (int) (conv0_weights_lut[ (weightCompressedData >> (weightDecompressedIndex * 4)) & 0x0F ]);
            }

            // Load Current Bias
            int realIndex = k;
            biasDecompressedIndex = realIndex & 7;   // 3 bits menos significativos (indice)
            biasCompressedIndex   = realIndex >> 3;  // divide por 8
            if (!biasDecompressedIndex)
                biasCompressedData = conv0_bias_indices_compressed[biasCompressedIndex];

            INTconv0_current_bias = (int) (conv0_bias_lut[ (biasCompressedData >> (biasDecompressedIndex * 4)) & 0x0F ]);

            // Perform Kernel operation
            for (i = 0; i <= sizeof(input_vector)/sizeof(input_vector[0])-KERNEL_SIZE; i++)
            {
                int INTtotalSum = 0;

                for (int j = 0; j < KERNEL_SIZE; j++)
                    INTtotalSum += ((int)( input_vector[i+j] )) * INTconv0_currentKernel[j];

                INTconv0_featureMap[k][i] = INTtotalSum + INTconv0_current_bias;
            }

        }

        // divide the feature map items by INPUT_MULTIP and make the RELU
        for (int i = 0; i < NUM_FILTERS; i++)
            for (int j = 0; j < CONV0_INPUT_SIZE-4; j++)
            {
                INTconv0_featureMap[i][j] = (INTconv0_featureMap[i][j])/(INPUT_MULTIP);
                if (INTconv0_featureMap[i][j] <= 0)
                    INTconv0_featureMap[i][j] = 0;
            }

        // printf("############################# CONV1 DONE\n");

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// LAYER 3
    // CONVOLUTION 3

        static int INTconv3_featureMap[NUM_FILTERS][CONV3_INPUT_SIZE-4]; // 112
        int INTconv3_totalSum = 0;

        for (int filterToGenerate = 0 ; filterToGenerate < NUM_FILTERS ; filterToGenerate ++ ){
            for (int inputOffset = 0 ; inputOffset < CONV3_INPUT_SIZE-4 ; inputOffset++){
                INTconv3_totalSum = 0;
                for (int filterIn = 0 ; filterIn < NUM_FILTERS ; filterIn++){
                    for (int kernelIndex = 0 ; kernelIndex < KERNEL_SIZE ; kernelIndex++){
                        int weightIndex = kernelIndex + (filterIn * KERNEL_SIZE) + ( filterToGenerate * NUM_FILTERS * KERNEL_SIZE ) ;
                        int indexIn = kernelIndex + (inputOffset);

                        int realIndex = weightIndex;
                        weightDecompressedIndex = realIndex & 7;   // 3 bits menos significativos (indice)
                        weightCompressedIndex   = realIndex >> 3;  // divide por 8
                        if (!weightDecompressedIndex)              // se for zero tem que acessar um novo valor
                            weightCompressedData = conv3_weights_indices_compressed[weightCompressedIndex];

                        INTconv3_totalSum +=  INTconv0_featureMap[filterIn][indexIn]  *  ((int) (conv3_weights_lut[ (weightCompressedData >> (weightDecompressedIndex * 4)) & 0x0F ]) ) ;  
                    }
                }

                int realIndex = filterToGenerate;
                biasDecompressedIndex = realIndex & 7;   // 3 bits menos significativos (indice)
                biasCompressedIndex   = realIndex >> 3;  // divide por 8
                if (!biasDecompressedIndex)
                    biasCompressedData = conv3_bias_indices_compressed[biasCompressedIndex];

                INTconv3_totalSum += ( (int) conv3_bias_lut[ (biasCompressedData >> (biasDecompressedIndex * 4)) & 0x0F  ]);

                INTconv3_featureMap[filterToGenerate][inputOffset] = INTconv3_totalSum;
            }
        }


       // divide the feature map items by INPUT_MULTIP
        for (int i = 0; i < NUM_FILTERS; i++)
            for (int j = 0; j < CONV3_INPUT_SIZE-4; j++)
            {
                INTconv3_featureMap[i][j] = (INTconv3_featureMap[i][j])/(INPUT_MULTIP);
                if (INTconv3_featureMap[i][j] <= 0)
                    INTconv3_featureMap[i][j] = 0;
            }

        // printf("############################# CONV3 DONE\n");

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// LAYER 6
    // CONVOLUTION 6

        static int INTconv6_featureMap[NUM_FILTERS][CONV6_INPUT_SIZE-4];
        int INTconv6_totalSum = 0;

        for (int filterToGenerate = 0 ; filterToGenerate < NUM_FILTERS ; filterToGenerate ++ ){
            for (int inputOffset = 0 ; inputOffset < CONV6_INPUT_SIZE-4 ; inputOffset++){
                INTconv6_totalSum = 0;
                for (int filterIn = 0 ; filterIn < NUM_FILTERS ; filterIn++){
                    for (int kernelIndex = 0 ; kernelIndex < KERNEL_SIZE ; kernelIndex++){
                        int weightIndex = kernelIndex + (filterIn * KERNEL_SIZE) + ( filterToGenerate * NUM_FILTERS * KERNEL_SIZE ) ;
                        int indexIn = kernelIndex + (inputOffset);

                        // Decompress logic
                        int realIndex = weightIndex;
                        weightDecompressedIndex = realIndex & 7;   // 3 bits menos significativos (indice)
                        weightCompressedIndex   = realIndex >> 3;  // divide por 8
                        if (!weightDecompressedIndex)
                            weightCompressedData = conv6_weights_indices_compressed[weightCompressedIndex];

                        INTconv6_totalSum += INTconv3_featureMap[filterIn][indexIn] * ((int) (conv6_weights_lut[ (weightCompressedData >> (weightDecompressedIndex * 4)) & 0x0F ]));
                    }
                }

                int realIndex = filterToGenerate;
                biasDecompressedIndex = realIndex & 7;   // 3 bits menos significativos (indice)
                biasCompressedIndex   = realIndex >> 3;  // divide por 8
                if (!biasDecompressedIndex)
                    biasCompressedData = conv6_bias_indices_compressed[biasCompressedIndex];

                INTconv6_totalSum += ( (int) conv6_bias_lut[(biasCompressedData >> (biasDecompressedIndex * 4)) & 0x0F ]);

                INTconv6_featureMap[filterToGenerate][inputOffset] = INTconv6_totalSum;
            }
        }

        // divide the feature map items by INPUT_MULTIP
        for (int i = 0; i < NUM_FILTERS; i++)
          for (int j = 0; j < CONV6_INPUT_SIZE-4; j++)
            {
                INTconv6_featureMap[i][j] = (INTconv6_featureMap[i][j]/(INPUT_MULTIP)); 
                if (INTconv6_featureMap[i][j] <= 0)
                    INTconv6_featureMap[i][j] = 0;
            }

        // printf("############################# CONV6 DONE\n");

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// LAYER 2
    ////// FC 1 (6912 > 128)
    /////  Flatten
    /////
        static int INTflatten1_vector[NUM_FILTERS*(CONV6_INPUT_SIZE-4)];
        int index = 0;

        for (int k = 0; k < NUM_FILTERS; k++)
            for (int i = 0; i < CONV6_INPUT_SIZE-4; i++)
            {
                INTflatten1_vector[index] =  INTconv6_featureMap[k][i];
                index++;
            }

        static int INTfc1_out_vector[FC1_OUTPUT_SIZE];
        int INTtotalValue;
        const int fc1_inputSize = NUM_FILTERS*(CONV6_INPUT_SIZE-4); // 64* (112-4) = 6912

        for (int outputIndex = 0; outputIndex < FC1_OUTPUT_SIZE; outputIndex++){
            INTtotalValue = 0;
            int precalcIndex = fc1_inputSize * outputIndex;  // avoid a '*' inside the loop
            for (int i = 0; i < fc1_inputSize; i++)
            {
                int realIndex = precalcIndex + i;
                weightDecompressedIndex = realIndex & 7;   // 3 bits menos significativos (indice)
                weightCompressedIndex   = realIndex >> 3;  // divide por 8
                if (!weightDecompressedIndex)
                    weightCompressedData = fc1_weights_indices_compressed[weightCompressedIndex];

                int decompressedWeight = fc1_weights_lut[(weightCompressedData >> (weightDecompressedIndex * 4)) & 0x0F];

                INTtotalValue += INTflatten1_vector[i] * decompressedWeight;
            }

            int realIndex = outputIndex;
            biasDecompressedIndex = realIndex & 7;   // 3 bits menos significativos (indice)
            biasCompressedIndex   = realIndex >> 3;  // divide por 8
            if (!biasDecompressedIndex)
                biasCompressedData = fc1_bias_indices_compressed[biasCompressedIndex];

            INTfc1_out_vector[outputIndex] = INTtotalValue + fc1_bias_lut[(biasCompressedData >> (biasDecompressedIndex * 4)) & 0x0F];
        }

        // divide the feature map items by INPUT_MULTIP and make RELU
        for (int i = 0; i < FC1_OUTPUT_SIZE; i++)
        {
            INTfc1_out_vector[i] = INTfc1_out_vector[i] / INPUT_MULTIP;
            if ( INTfc1_out_vector[i] < 0 ) INTfc1_out_vector[i] = 0;
        }

        // printf("############################# FC1 DONE\n");

    ///////////////// FC 2 (128 > 5)
        static int INTfc2_out_vector[FC2_OUTPUT_SIZE];
        int INTfc2_totalValue;

        for (int outputIndex = 0; outputIndex < FC2_OUTPUT_SIZE; outputIndex++){
            INTfc2_totalValue = 0;
            for (int i = 0; i < FC1_OUTPUT_SIZE; i++)
            {
                int realIndex = (FC1_OUTPUT_SIZE*outputIndex)+i;
                weightDecompressedIndex = realIndex & 7;   // 3 bits menos significativos (indice)
                weightCompressedIndex   = realIndex >> 3;  // divide por 8
                if (!weightDecompressedIndex)
                    weightCompressedData = fc2_weights_indices_compressed[weightCompressedIndex];

                INTfc2_totalValue += INTfc1_out_vector[i] * ( (int) (fc2_weights_lut[ (weightCompressedData >> (weightDecompressedIndex * 4)) & 0x0F ])); 
            }
            int realIndex = outputIndex;
            biasDecompressedIndex = realIndex & 7;   // 3 bits menos significativos (indice)
            biasCompressedIndex   = realIndex >> 3;  // divide por 8
            if (!biasDecompressedIndex)
                biasCompressedData = fc2_bias_indices_compressed[biasCompressedIndex];

            INTfc2_out_vector[outputIndex] = INTfc2_totalValue + ( (int) fc2_bias_lut[ (biasCompressedData >> (biasDecompressedIndex * 4)) & 0x0F  ] );
        }



    //////////////////////////////// INT HANDLER
    // divide the feature map items by INPUT_MULTIP
        for (int i = 0; i < FC2_OUTPUT_SIZE; i++)
        {
            INTfc2_out_vector[i] = INTfc2_out_vector[i] / (INPUT_MULTIP*INPUT_MULTIP);
        }


    ////////////////////////// Result Classes
        // printf("\n############################################################## RESULT CLASSES\n");

        int calculatedLabel;
        int INTmaxValue;

        INTmaxValue =  INTfc2_out_vector[0];
        calculatedLabel = 0;
        for (int i = 0; i < 5; i++){
            if (INTfc2_out_vector[i] > INTmaxValue){
                INTmaxValue = INTfc2_out_vector[i];
                calculatedLabel = i;
            }
        }

        printf("%d,%d,",calculatedLabel,targetLabel);

    }

    return 0;

}
