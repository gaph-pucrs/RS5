/*
 * cnn_std.h
 *
 *  Created on: 05/11/2024
 *      Author: Willian
 */

#ifndef CNN_STD_H_
#define CNN_STD_H_

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
#define OUT_DEPTH_1 64
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
#define IN_DEPTH_2 64
#define OUT_CONV_HEIGHT_2 27
#define OUT_CONV_WIDTH_2 27
#define OUT_HEIGHT_2 13
#define OUT_WIDTH_2 13
#define OUT_DEPTH_2 192
#define STRIDE_CONV_2 1
#define STRIDE_MAX_2 2
#define POOL_SIZE_2 3
/*****************************/

/******* Layer Conv 3 ********/
#define PAD_IN_3 1
#define FILTER_HEIGHT_3 3
#define FILTER_WIDTH_3 3
#define IN_HEIGHT_3 15
#define IN_WIDTH_3 15
#define IN_DEPTH_3 192
#define OUT_CONV_HEIGHT_3 13
#define OUT_CONV_WIDTH_3 13
#define OUT_DEPTH_3 384
#define STRIDE_CONV_3 1
/*****************************/

/******* Layer Conv 4 ********/
#define PAD_IN_4 1
#define FILTER_HEIGHT_4 3
#define FILTER_WIDTH_4 3
#define IN_HEIGHT_4 15
#define IN_WIDTH_4 15
#define IN_DEPTH_4 384
#define OUT_CONV_HEIGHT_4 13
#define OUT_CONV_WIDTH_4 13
#define OUT_DEPTH_4 256
#define STRIDE_CONV_4 1
/*****************************/

/******* Layer Conv 5 ********/
#define PAD_IN_5 1
#define FILTER_HEIGHT_5 3
#define FILTER_WIDTH_5 3
#define IN_HEIGHT_5 15
#define IN_WIDTH_5 15
#define IN_DEPTH_5 256
#define OUT_CONV_HEIGHT_5 13
#define OUT_CONV_WIDTH_5 13
#define OUT_HEIGHT_5 6
#define OUT_WIDTH_5 6
#define OUT_DEPTH_5 256
#define STRIDE_CONV_5 1
#define STRIDE_MAX_5 2
#define POOL_SIZE_5 3
/*****************************/

/******* Fully Connected Layers ********/
#define FC6_IN_SIZE   9216   /* 6*6*256 — flattened conv5 maxpool output */
#define FC6_OUT_SIZE  4096
#define FC7_IN_SIZE   4096
#define FC7_OUT_SIZE  4096
#define FC8_IN_SIZE   4096
#define FC8_OUT_SIZE  1000
/***************************************/

#ifndef P1_MSG_SIZE
    #define P1_MSG_SIZE OUT_CONV_HEIGHT_1*OUT_CONV_WIDTH_1
#endif

#ifndef P2_MSG_SIZE
    #define P2_MSG_SIZE OUT_HEIGHT_1*OUT_WIDTH_1
#endif

#ifndef P3_MSG_SIZE
    #define P3_MSG_SIZE OUT_CONV_HEIGHT_2*OUT_CONV_WIDTH_2
#endif

#ifndef P4_MSG_SIZE
    #define P4_MSG_SIZE OUT_HEIGHT_2*OUT_WIDTH_2
#endif

#ifndef P5_MSG_SIZE
    #define P5_MSG_SIZE OUT_CONV_HEIGHT_3*OUT_CONV_WIDTH_3
#endif

#ifndef P6_MSG_SIZE
    #define P6_MSG_SIZE OUT_CONV_HEIGHT_3*OUT_CONV_WIDTH_3
#endif

#ifndef P7_MSG_SIZE
    #define P7_MSG_SIZE OUT_CONV_HEIGHT_4*OUT_CONV_WIDTH_4
#endif

#ifndef P8_MSG_SIZE
    #define P8_MSG_SIZE OUT_CONV_HEIGHT_4*OUT_CONV_WIDTH_4
#endif

#ifndef P9_MSG_SIZE
    #define P9_MSG_SIZE OUT_CONV_HEIGHT_5*OUT_CONV_WIDTH_5
#endif

#ifndef INFERENCES
    #define INFERENCES	 1
#endif


#endif /* PROD_CONS_STD_H_ */
