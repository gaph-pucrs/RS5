#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lib/printf.h"

#include "params/0_bias_int.h"
#include "params/3_bias_int.h"
#include "params/6_bias_int.h"
#include "params/0_weight_int.h"
#include "params/3_weight_int.h"
#include "params/6_weight_int.h"
#include "params/classifier_1_weight_int.h"
#include "params/classifier_2_weight_int.h"
#include "params/classifier_1_bias_int.h"
#include "params/classifier_2_bias_int.h"


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
// Do not change these values if you don't know what you are doing, many files must be changed accordingly
#define MULTIP_conv1 1000
#define MULTIP_conv3 1000
#define MULTIP_conv6 1000
#define MULTIP_fc1 1000
#define MULTIP_fc2 1000

int main(){
    int i = 0;
    static int input_vector[INPUT_SIZE];
    int targetLabel;

    for(int datasetIndex = 0 ; datasetIndex < DATASET_UNITS ; datasetIndex++ ){
        int startingIndex = datasetIndex * 121; //input + label
        targetLabel = dataset120[startingIndex + INPUT_SIZE]/1000;

        // printf( "ix %4d  target %4d  -------- \n" , startingIndex + INPUT_SIZE, targetLabel);

        for(i = 0 ; i < INPUT_SIZE ; i++){
            input_vector[i] = dataset120[startingIndex + i];
        }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// LAYER 1
    // CONVOLUTION 1
        static int INTconv0_featureMap[NUM_FILTERS][CONV0_INPUT_SIZE-4];
        static int INTconv0_currentKernel[KERNEL_SIZE];
        int INTconv0_current_bias = 0;

        for (int k = 0; k < NUM_FILTERS; k++)
        {
            // Load Current Weights
            for (i = 0; i < KERNEL_SIZE; i++)
            {
                INTconv0_currentKernel[i] = (int) (conv0_weights[i + (k * KERNEL_SIZE)]);
            }

            // Load Current Bias
            INTconv0_current_bias = (int) (conv0_bias[k]);

            // Perform Kernel operation
            for (i = 0; i <= sizeof(input_vector)/sizeof(input_vector[0])-KERNEL_SIZE; i++)
            {
                int INTtotalSum = 0;
                for (int j = 0; j < KERNEL_SIZE; j++)
                {
                INTtotalSum += (input_vector[i+j]) * INTconv0_currentKernel[j];
                }
                INTconv0_featureMap[k][i] = INTtotalSum + INTconv0_current_bias * MULTIP_conv1 ;  // moraes
            }
        }

    //////////////////////////////// INT HANDLER
    // divide the feature map items by MULTIP_conv1
        for (int i = 0; i < NUM_FILTERS; i++)
        {
            for (int j = 0; j < CONV0_INPUT_SIZE-4; j++)
            {
                INTconv0_featureMap[i][j] = (INTconv0_featureMap[i][j])/(MULTIP_conv1);
            }
        }

    ///// RELU
        for (int i = 0; i < NUM_FILTERS; i++)
        {
            for (int j = 0; j < CONV0_INPUT_SIZE-4; j++)
            {
                if (INTconv0_featureMap[i][j] <= 0)
                    INTconv0_featureMap[i][j] = 0;
            }
        }

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

                        INTconv3_totalSum += ((INTconv0_featureMap[filterIn][indexIn] * MULTIP_conv3) / MULTIP_conv1)    *  ((int) (conv3_weights[weightIndex]))  ; 
                    }
                }
                INTconv3_totalSum += ( (int) conv3_bias[filterToGenerate])* MULTIP_conv3 ;  // moraes;
                INTconv3_featureMap[filterToGenerate][inputOffset] = INTconv3_totalSum;
            }
        }

    //////////////////////////////// INT HANDLER
    // divide the feature map items by MULTIP_conv3
        for (int i = 0; i < NUM_FILTERS; i++)
        {
            for (int j = 0; j < CONV3_INPUT_SIZE-4; j++)
            {
                INTconv3_featureMap[i][j] = (INTconv3_featureMap[i][j])/(MULTIP_conv3);
            }
        }

    ///// RELU
        for (int i = 0; i < NUM_FILTERS; i++)
        {
            for (int j = 0; j < CONV3_INPUT_SIZE-4; j++)
            {
                if (INTconv3_featureMap[i][j] <= 0)
                    INTconv3_featureMap[i][j] = 0;
            }
        }

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
                        INTconv6_totalSum += ((INTconv3_featureMap[filterIn][indexIn] * MULTIP_conv6)/MULTIP_conv3) * ((int) (conv6_weights[weightIndex]));
                    }
                }
                INTconv6_totalSum += ( (int) conv6_bias[filterToGenerate]) * MULTIP_conv6 ;  // moraes
                INTconv6_featureMap[filterToGenerate][inputOffset] = INTconv6_totalSum;
            }
        }

    //////////////////////////////// INT HANDLER
    // divide the feature map items by MULTIP_conv6
        for (int i = 0; i < NUM_FILTERS; i++)
        {
            for (int j = 0; j < CONV6_INPUT_SIZE-4; j++)
            {
                INTconv6_featureMap[i][j] = (INTconv6_featureMap[i][j]/(MULTIP_conv6)); // 5000
            }
        }

    /////////////////////////// RELU
        for (int i = 0; i < NUM_FILTERS; i++)
        {
            for (int j = 0; j < CONV6_INPUT_SIZE-4; j++)
            {
                if (INTconv6_featureMap[i][j] <= 0)
                    INTconv6_featureMap[i][j] = 0;
            }
        }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// LAYER 2
    ////////////////////////////////////////// FC Layer
    ///// Flatten

        static int INTflatten1_vector[NUM_FILTERS*(CONV6_INPUT_SIZE-4)];
        int index = 0;

        for (int k = 0; k < NUM_FILTERS; k++)
        {
            for (int i = 0; i < CONV6_INPUT_SIZE-4; i++)
            {
                INTflatten1_vector[index] =  INTconv6_featureMap[k][i];
                index++;
            }
        }

    /////// FC 1 (6912 > 128)

        static int INTfc1_out_vector[FC1_OUTPUT_SIZE];
        int INTtotalValue;
        int fc1_inputSize = NUM_FILTERS*(CONV6_INPUT_SIZE-4); // 6912


        for (int outputIndex = 0; outputIndex < FC1_OUTPUT_SIZE; outputIndex++){
            INTtotalValue = 0;
            for (int i = 0; i < fc1_inputSize; i++)
            {
                INTtotalValue += ((INTflatten1_vector[i]*MULTIP_fc1)/MULTIP_conv6) * ( (int) (fc1_weights[(fc1_inputSize*outputIndex)+i]) );
            }
            INTfc1_out_vector[outputIndex] = INTtotalValue + ((int) fc1_bias[outputIndex]) * MULTIP_fc1 ;  // moraes
        }

    //////////////////////////////// INT HANDLER
    // divide the feature map items by MULTIP_fc1
        for (int i = 0; i < FC1_OUTPUT_SIZE; i++)
        {
            INTfc1_out_vector[i] = INTfc1_out_vector[i] / MULTIP_fc1;
        }

    ////////////////// RELU
        for (int i = 0; i < FC1_OUTPUT_SIZE ; i++){
            if ( INTfc1_out_vector[i] < 0 ) INTfc1_out_vector[i] = 0;
        }

    ///////////////// FC 1 (128 > 5)
        static int INTfc2_out_vector[FC2_OUTPUT_SIZE];
        int INTfc2_totalValue;

        for (int outputIndex = 0; outputIndex < FC2_OUTPUT_SIZE; outputIndex++){
            INTfc2_totalValue = 0;
            // if ( datasetIndex == 4)  printf("totalvalue------");
            for (int i = 0; i < FC1_OUTPUT_SIZE; i++)
            {
                INTfc2_totalValue += ((INTfc1_out_vector[i] * MULTIP_fc2 ) / MULTIP_fc1) * ( (int) (fc2_weights[(FC1_OUTPUT_SIZE*outputIndex)+i])); 
                // if ( datasetIndex == 4) printf("%f  %d \n ",fc2_totalValue,INTfc2_totalValue);
            }
            INTfc2_out_vector[outputIndex] = INTfc2_totalValue + ( (int) fc2_bias[outputIndex]) * MULTIP_fc2; // moraes
            // if ( datasetIndex == 4) printf("%f  %d \n ",fc2_out_vector[outputIndex],INTfc2_out_vector[outputIndex]);
        }

    //////////////////////////////// INT HANDLER
    // divide the feature map items by MULTIP_fc2
        for (int i = 0; i < FC2_OUTPUT_SIZE; i++)
        {
            INTfc2_out_vector[i] = INTfc2_out_vector[i] / (MULTIP_fc2*MULTIP_fc2);
        }

    ////////////////////////// Result Classes
        //printf("\n############################################################## RESULT CLASSES");

        int maxValue =  INTfc2_out_vector[0];
        int calculatedLabel = 0;
        for (int i = 0; i < 5; i++){
            if (INTfc2_out_vector[i] > maxValue){
                maxValue = INTfc2_out_vector[i];
                calculatedLabel = i;
            }
        }

        printf("%d,%d,",calculatedLabel,targetLabel);
    }
    return 0;
}
