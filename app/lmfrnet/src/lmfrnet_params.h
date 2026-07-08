#ifndef __LMFRNET_PARAMS_H__
#define __LMFRNET_PARAMS_H__

#include "cnn_common.h" // for `type`, used by ConvParams below
#include "lmfrnet_weights.h"

// --- stemBlock ---
const TensorShape stemBlock_shape = {
    32, 32, 3, 32, 32, 32
};

const ConvParams stemBlock_params = {
    stemBlock_stemConv_0_0_weight,
    stemBlock_stemConv_0_0_bias,
    3, 1
};

// --- MMCBlock1_mmLayer1 (MFBlock) ---
const MFBlockShapes MMCBlock1_mmLayer1_shapes = {
    { 32, 32, 32, 32, 32, 12 }, // b11
    { 32, 32, 12, 32, 32, 12 }, // b33a
    { 32, 32, 12, 32, 32,  6 }, // b33b
    { 32, 32,  6, 32, 32,  6 }, // b33c
};

const MFBlockParams MMCBlock1_mmLayer1_params = {
    { MMCBlock1_mmLayer1_branch11_conv_0_weight,  MMCBlock1_mmLayer1_branch11_conv_0_bias,  1, 1 },
    { MMCBlock1_mmLayer1_branch33a_conv_0_weight, MMCBlock1_mmLayer1_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock1_mmLayer1_branch33b_conv_0_weight, MMCBlock1_mmLayer1_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock1_mmLayer1_branch33c_conv_0_weight, MMCBlock1_mmLayer1_branch33c_conv_0_bias, 3, 1 },
};

// --- MMCBlock1_mmLayer2 (MFBlock) --- 
const MFBlockShapes MMCBlock1_mmLayer2_shapes = {
    { 32, 32, 56, 32, 32, 12 }, // b11
    { 32, 32, 12, 32, 32, 12 }, // b33a
    { 32, 32, 12, 32, 32,  6 }, // b33b
    { 32, 32,  6, 32, 32,  6 }, // b33c
};

const MFBlockParams MMCBlock1_mmLayer2_params = {
    { MMCBlock1_mmLayer2_branch11_conv_0_weight,  MMCBlock1_mmLayer2_branch11_conv_0_bias,  1, 1 },
    { MMCBlock1_mmLayer2_branch33a_conv_0_weight, MMCBlock1_mmLayer2_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock1_mmLayer2_branch33b_conv_0_weight, MMCBlock1_mmLayer2_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock1_mmLayer2_branch33c_conv_0_weight, MMCBlock1_mmLayer2_branch33c_conv_0_bias, 3, 1 },
};

// --- MMCBlock1_mmLayer3 (MFBlock) --- 
const MFBlockShapes MMCBlock1_mmLayer3_shapes = {
    { 32, 32, 80, 32, 32, 12 }, // b11
    { 32, 32, 12, 32, 32, 12 }, // b33a
    { 32, 32, 12, 32, 32,  6 }, // b33b
    { 32, 32,  6, 32, 32,  6 }, // b33c
};

const MFBlockParams MMCBlock1_mmLayer3_params = {
    { MMCBlock1_mmLayer3_branch11_conv_0_weight,  MMCBlock1_mmLayer3_branch11_conv_0_bias,  1, 1 },
    { MMCBlock1_mmLayer3_branch33a_conv_0_weight, MMCBlock1_mmLayer3_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock1_mmLayer3_branch33b_conv_0_weight, MMCBlock1_mmLayer3_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock1_mmLayer3_branch33c_conv_0_weight, MMCBlock1_mmLayer3_branch33c_conv_0_bias, 3, 1 },
};

// --- tran_ConvNormRelu1 (tran_conv) ---
const TensorShape tran_ConvNormRelu1_shape = {
    32, 32, 104, 32, 32, 104
};

const ConvParams tran_ConvNormRelu1_params = {
    tran_ConvNormRelu1_conv_0_weight,
    tran_ConvNormRelu1_conv_0_bias,
    1, 1
};

// --- pool1 (avg_pool) ---
const TensorShape pool1_shape = {
    32, 32, 104, 16, 16, 104
};

// --- MMCBlock2_mmLayer1 (MFBlock) --- 
const MFBlockShapes MMCBlock2_mmLayer1_shapes = {
    {  16,  16, 104,  16,  16,  12 }, // b11
    {  16,  16,  12,  16,  16,  12 }, // b33a
    {  16,  16,  12,  16,  16,   6 }, // b33b
    {  16,  16,   6,  16,  16,   6 }, // b33c
};

const MFBlockParams MMCBlock2_mmLayer1_params = {
    { MMCBlock2_mmLayer1_branch11_conv_0_weight,  MMCBlock2_mmLayer1_branch11_conv_0_bias,  1, 1 },
    { MMCBlock2_mmLayer1_branch33a_conv_0_weight, MMCBlock2_mmLayer1_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock2_mmLayer1_branch33b_conv_0_weight, MMCBlock2_mmLayer1_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock2_mmLayer1_branch33c_conv_0_weight, MMCBlock2_mmLayer1_branch33c_conv_0_bias, 3, 1 },
};

// --- MMCBlock2_mmLayer2 (MFBlock) --- 
const MFBlockShapes MMCBlock2_mmLayer2_shapes = {
    {  16,  16, 128,  16,  16,  12 }, // b11
    {  16,  16,  12,  16,  16,  12 }, // b33a
    {  16,  16,  12,  16,  16,   6 }, // b33b
    {  16,  16,   6,  16,  16,   6 }, // b33c
};

const MFBlockParams MMCBlock2_mmLayer2_params = {
    { MMCBlock2_mmLayer2_branch11_conv_0_weight,  MMCBlock2_mmLayer2_branch11_conv_0_bias,  1, 1 },
    { MMCBlock2_mmLayer2_branch33a_conv_0_weight, MMCBlock2_mmLayer2_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock2_mmLayer2_branch33b_conv_0_weight, MMCBlock2_mmLayer2_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock2_mmLayer2_branch33c_conv_0_weight, MMCBlock2_mmLayer2_branch33c_conv_0_bias, 3, 1 },
};

// --- MMCBlock2_mmLayer3 (MFBlock) --- 
const MFBlockShapes MMCBlock2_mmLayer3_shapes = {
    {  16,  16, 152,  16,  16,  12 }, // b11
    {  16,  16,  12,  16,  16,  12 }, // b33a
    {  16,  16,  12,  16,  16,   6 }, // b33b
    {  16,  16,   6,  16,  16,   6 }, // b33c
};

const MFBlockParams MMCBlock2_mmLayer3_params = {
    { MMCBlock2_mmLayer3_branch11_conv_0_weight,  MMCBlock2_mmLayer3_branch11_conv_0_bias,  1, 1 },
    { MMCBlock2_mmLayer3_branch33a_conv_0_weight, MMCBlock2_mmLayer3_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock2_mmLayer3_branch33b_conv_0_weight, MMCBlock2_mmLayer3_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock2_mmLayer3_branch33c_conv_0_weight, MMCBlock2_mmLayer3_branch33c_conv_0_bias, 3, 1 },
};

// --- MMCBlock2_mmLayer4 (MFBlock) --- 
const MFBlockShapes MMCBlock2_mmLayer4_shapes = {
    {  16,  16, 176,  16,  16,  12 }, // b11
    {  16,  16,  12,  16,  16,  12 }, // b33a
    {  16,  16,  12,  16,  16,   6 }, // b33b
    {  16,  16,   6,  16,  16,   6 }, // b33c
};

const MFBlockParams MMCBlock2_mmLayer4_params = {
    { MMCBlock2_mmLayer4_branch11_conv_0_weight,  MMCBlock2_mmLayer4_branch11_conv_0_bias,  1, 1 },
    { MMCBlock2_mmLayer4_branch33a_conv_0_weight, MMCBlock2_mmLayer4_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock2_mmLayer4_branch33b_conv_0_weight, MMCBlock2_mmLayer4_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock2_mmLayer4_branch33c_conv_0_weight, MMCBlock2_mmLayer4_branch33c_conv_0_bias, 3, 1 },
};

// --- tran_ConvNormRelu2 (tran_conv) --- 
const TensorShape tran_ConvNormRelu2_shape = {
    16, 16, 200, 16, 16, 200
};

const ConvParams tran_ConvNormRelu2_params = {
    tran_ConvNormRelu2_conv_0_weight,
    tran_ConvNormRelu2_conv_0_bias,
    1, 1
};

// --- pool2 (avg_pool) ---
const TensorShape pool2_shape = {
    16, 16, 200, 8, 8, 200
};

// --- MMCBlock3_mmLayer1 (MFBlock) --- 
const MFBlockShapes MMCBlock3_mmLayer1_shapes = {
    {  8,  8, 200,  8,  8,  12 }, // b11
    {  8,  8,  12,  8,  8,  12 }, // b33a
    {  8,  8,  12,  8,  8,   6 }, // b33b
    {  8,  8,   6,  8,  8,   6 }, // b33c
};

const MFBlockParams MMCBlock3_mmLayer1_params = {
    { MMCBlock3_mmLayer1_branch11_conv_0_weight,  MMCBlock3_mmLayer1_branch11_conv_0_bias,  1, 1 },
    { MMCBlock3_mmLayer1_branch33a_conv_0_weight, MMCBlock3_mmLayer1_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock3_mmLayer1_branch33b_conv_0_weight, MMCBlock3_mmLayer1_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock3_mmLayer1_branch33c_conv_0_weight, MMCBlock3_mmLayer1_branch33c_conv_0_bias, 3, 1 },
};

// --- MMCBlock3_mmLayer2 (MFBlock) --- 
const MFBlockShapes MMCBlock3_mmLayer2_shapes = {
    {  8,  8, 224,  8,  8,  12 }, // b11
    {  8,  8,  12,  8,  8,  12 }, // b33a
    {  8,  8,  12,  8,  8,   6 }, // b33b
    {  8,  8,   6,  8,  8,   6 }, // b33c
};

const MFBlockParams MMCBlock3_mmLayer2_params = {
    { MMCBlock3_mmLayer2_branch11_conv_0_weight,  MMCBlock3_mmLayer2_branch11_conv_0_bias,  1, 1 },
    { MMCBlock3_mmLayer2_branch33a_conv_0_weight, MMCBlock3_mmLayer2_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock3_mmLayer2_branch33b_conv_0_weight, MMCBlock3_mmLayer2_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock3_mmLayer2_branch33c_conv_0_weight, MMCBlock3_mmLayer2_branch33c_conv_0_bias, 3, 1 },
};

// --- MMCBlock3_mmLayer3 (MFBlock) --- 
const MFBlockShapes MMCBlock3_mmLayer3_shapes = {
    {  8,  8, 248,  8,  8,  12 }, // b11
    {  8,  8,  12,  8,  8,  12 }, // b33a
    {  8,  8,  12,  8,  8,   6 }, // b33b
    {  8,  8,   6,  8,  8,   6 }, // b33c
};

const MFBlockParams MMCBlock3_mmLayer3_params = {
    { MMCBlock3_mmLayer3_branch11_conv_0_weight,  MMCBlock3_mmLayer3_branch11_conv_0_bias,  1, 1 },
    { MMCBlock3_mmLayer3_branch33a_conv_0_weight, MMCBlock3_mmLayer3_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock3_mmLayer3_branch33b_conv_0_weight, MMCBlock3_mmLayer3_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock3_mmLayer3_branch33c_conv_0_weight, MMCBlock3_mmLayer3_branch33c_conv_0_bias, 3, 1 },
};

// --- MMCBlock3_mmLayer4 (MFBlock) --- 
const MFBlockShapes MMCBlock3_mmLayer4_shapes = {
    {  8,  8, 272,  8,  8,  12 }, // b11
    {  8,  8,  12,  8,  8,  12 }, // b33a
    {  8,  8,  12,  8,  8,   6 }, // b33b
    {  8,  8,   6,  8,  8,   6 }, // b33c
};

const MFBlockParams MMCBlock3_mmLayer4_params = {
    { MMCBlock3_mmLayer4_branch11_conv_0_weight,  MMCBlock3_mmLayer4_branch11_conv_0_bias,  1, 1 },
    { MMCBlock3_mmLayer4_branch33a_conv_0_weight, MMCBlock3_mmLayer4_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock3_mmLayer4_branch33b_conv_0_weight, MMCBlock3_mmLayer4_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock3_mmLayer4_branch33c_conv_0_weight, MMCBlock3_mmLayer4_branch33c_conv_0_bias, 3, 1 },
};

// --- MMCBlock3_mmLayer5 (MFBlock) --- 
const MFBlockShapes MMCBlock3_mmLayer5_shapes = {
    {  8,  8, 296,  8,  8,  12 }, // b11
    {  8,  8,  12,  8,  8,  12 }, // b33a
    {  8,  8,  12,  8,  8,   6 }, // b33b
    {  8,  8,   6,  8,  8,   6 }, // b33c
};

const MFBlockParams MMCBlock3_mmLayer5_params = {
    { MMCBlock3_mmLayer5_branch11_conv_0_weight,  MMCBlock3_mmLayer5_branch11_conv_0_bias,  1, 1 },
    { MMCBlock3_mmLayer5_branch33a_conv_0_weight, MMCBlock3_mmLayer5_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock3_mmLayer5_branch33b_conv_0_weight, MMCBlock3_mmLayer5_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock3_mmLayer5_branch33c_conv_0_weight, MMCBlock3_mmLayer5_branch33c_conv_0_bias, 3, 1 },
};

// --- MMCBlock3_mmLayer6 (MFBlock) --- 
const MFBlockShapes MMCBlock3_mmLayer6_shapes = {
    {  8,  8, 320,  8,  8,  12 }, // b11
    {  8,  8,  12,  8,  8,  12 }, // b33a
    {  8,  8,  12,  8,  8,   6 }, // b33b
    {  8,  8,   6,  8,  8,   6 }, // b33c
};

const MFBlockParams MMCBlock3_mmLayer6_params = {
    { MMCBlock3_mmLayer6_branch11_conv_0_weight,  MMCBlock3_mmLayer6_branch11_conv_0_bias,  1, 1 },
    { MMCBlock3_mmLayer6_branch33a_conv_0_weight, MMCBlock3_mmLayer6_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock3_mmLayer6_branch33b_conv_0_weight, MMCBlock3_mmLayer6_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock3_mmLayer6_branch33c_conv_0_weight, MMCBlock3_mmLayer6_branch33c_conv_0_bias, 3, 1 },
};

// --- MMCBlock3_mmLayer7 (MFBlock) --- 
const MFBlockShapes MMCBlock3_mmLayer7_shapes = {
    {  8,  8, 344,  8,  8,  12 }, // b11
    {  8,  8,  12,  8,  8,  12 }, // b33a
    {  8,  8,  12,  8,  8,   6 }, // b33b
    {  8,  8,   6,  8,  8,   6 }, // b33c
};

const MFBlockParams MMCBlock3_mmLayer7_params = {
    { MMCBlock3_mmLayer7_branch11_conv_0_weight,  MMCBlock3_mmLayer7_branch11_conv_0_bias,  1, 1 },
    { MMCBlock3_mmLayer7_branch33a_conv_0_weight, MMCBlock3_mmLayer7_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock3_mmLayer7_branch33b_conv_0_weight, MMCBlock3_mmLayer7_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock3_mmLayer7_branch33c_conv_0_weight, MMCBlock3_mmLayer7_branch33c_conv_0_bias, 3, 1 },
};

// --- MMCBlock3_mmLayer8 (MFBlock) --- 
const MFBlockShapes MMCBlock3_mmLayer8_shapes = {
    {  8,  8, 368,  8,  8,  12 }, // b11
    {  8,  8,  12,  8,  8,  12 }, // b33a
    {  8,  8,  12,  8,  8,   6 }, // b33b
    {  8,  8,   6,  8,  8,   6 }, // b33c
};

const MFBlockParams MMCBlock3_mmLayer8_params = {
    { MMCBlock3_mmLayer8_branch11_conv_0_weight,  MMCBlock3_mmLayer8_branch11_conv_0_bias,  1, 1 },
    { MMCBlock3_mmLayer8_branch33a_conv_0_weight, MMCBlock3_mmLayer8_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock3_mmLayer8_branch33b_conv_0_weight, MMCBlock3_mmLayer8_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock3_mmLayer8_branch33c_conv_0_weight, MMCBlock3_mmLayer8_branch33c_conv_0_bias, 3, 1 },
};

// --- tran_ConvNormRelu3 (tran_conv) --- 
const TensorShape tran_ConvNormRelu3_shape = {
    8, 8, 392, 8, 8, 392
};

const ConvParams tran_ConvNormRelu3_params = {
    tran_ConvNormRelu3_conv_0_weight,
    tran_ConvNormRelu3_conv_0_bias,
    1, 1
};

// --- pool3 (avg_pool) ---
const TensorShape pool3_shape = {
    8, 8, 392, 4, 4, 392
};

// --- MMCBlock4_mmLayer1 (MFBlock) --- 
const MFBlockShapes MMCBlock4_mmLayer1_shapes = {
    {  4,  4, 392,  4,  4,  12 }, // b11
    {  4,  4,  12,  4,  4,  12 }, // b33a
    {  4,  4,  12,  4,  4,   6 }, // b33b
    {  4,  4,   6,  4,  4,   6 }, // b33c
};

const MFBlockParams MMCBlock4_mmLayer1_params = {
    { MMCBlock4_mmLayer1_branch11_conv_0_weight,  MMCBlock4_mmLayer1_branch11_conv_0_bias,  1, 1 },
    { MMCBlock4_mmLayer1_branch33a_conv_0_weight, MMCBlock4_mmLayer1_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock4_mmLayer1_branch33b_conv_0_weight, MMCBlock4_mmLayer1_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock4_mmLayer1_branch33c_conv_0_weight, MMCBlock4_mmLayer1_branch33c_conv_0_bias, 3, 1 },
};

// --- MMCBlock4_mmLayer2 (MFBlock) --- 
const MFBlockShapes MMCBlock4_mmLayer2_shapes = {
    {  4,  4, 416,  4,  4,  12 }, // b11
    {  4,  4,  12,  4,  4,  12 }, // b33a
    {  4,  4,  12,  4,  4,   6 }, // b33b
    {  4,  4,   6,  4,  4,   6 }, // b33c
};

const MFBlockParams MMCBlock4_mmLayer2_params = {
    { MMCBlock4_mmLayer2_branch11_conv_0_weight,  MMCBlock4_mmLayer2_branch11_conv_0_bias,  1, 1 },
    { MMCBlock4_mmLayer2_branch33a_conv_0_weight, MMCBlock4_mmLayer2_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock4_mmLayer2_branch33b_conv_0_weight, MMCBlock4_mmLayer2_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock4_mmLayer2_branch33c_conv_0_weight, MMCBlock4_mmLayer2_branch33c_conv_0_bias, 3, 1 },
};

// --- MMCBlock4_mmLayer3 (MFBlock) --- 
const MFBlockShapes MMCBlock4_mmLayer3_shapes = {
    {  4,  4, 440,  4,  4,  12 }, // b11
    {  4,  4,  12,  4,  4,  12 }, // b33a
    {  4,  4,  12,  4,  4,   6 }, // b33b
    {  4,  4,   6,  4,  4,   6 }, // b33c
};

const MFBlockParams MMCBlock4_mmLayer3_params = {
    { MMCBlock4_mmLayer3_branch11_conv_0_weight,  MMCBlock4_mmLayer3_branch11_conv_0_bias,  1, 1 },
    { MMCBlock4_mmLayer3_branch33a_conv_0_weight, MMCBlock4_mmLayer3_branch33a_conv_0_bias, 3, 1 },
    { MMCBlock4_mmLayer3_branch33b_conv_0_weight, MMCBlock4_mmLayer3_branch33b_conv_0_bias, 3, 1 },
    { MMCBlock4_mmLayer3_branch33c_conv_0_weight, MMCBlock4_mmLayer3_branch33c_conv_0_bias, 3, 1 },
};

// --- tran_ConvNormRelu4 (tran_conv) --- 
const TensorShape tran_ConvNormRelu4_shape = {
    4, 4, 464, 4, 4, 464
};

const ConvParams tran_ConvNormRelu4_params = {
    tran_ConvNormRelu4_conv_0_weight,
    tran_ConvNormRelu4_conv_0_bias,
    1, 1
};

// --- gap ---
const TensorShape gap_shape = {
    4, 4, 464, 1, 1, 464
};

// --- fc ---
const TensorShape fc_shape = {
    1, 1, 464, 1, 1, 10
};

const ConvParams fc_params = {
    fc_weight,
    fc_bias,
    0, 0 // K, s unused by fc()
};

#endif
