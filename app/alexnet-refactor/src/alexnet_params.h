#ifndef __ALEXNET_PARAMS_H__
#define __ALEXNET_PARAMS_H__

#include "cnn_common.h" // for `type`, used by ConvParams below
#include "alexnet_weights.h"

// TensorShape: { H_in, W_in, C_in, H_out, W_out, C_out }
// ConvParams:  { w, b, K, s, p }

// --- conv1 ---
const TensorShape conv1_shape = {
    IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_CHANNELS, CONV1_HEIGHT, CONV1_WIDTH, CONV1_CHANNELS
};

const ConvParams conv1_params = {
    features_0_weight, features_0_bias, CONV1_KERNEL, CONV1_STRIDE, CONV1_PAD
};

// --- pool1 (maxpool 3x3, stride 2) ---
const TensorShape pool1_shape = {
    CONV1_HEIGHT, CONV1_WIDTH, CONV1_CHANNELS, POOL1_HEIGHT, POOL1_WIDTH, CONV1_CHANNELS
};

// --- conv2 ---
const TensorShape conv2_shape = {
    POOL1_HEIGHT, POOL1_WIDTH, CONV1_CHANNELS, CONV2_HEIGHT, CONV2_WIDTH, CONV2_CHANNELS
};

const ConvParams conv2_params = {
    features_3_weight, features_3_bias, CONV2_KERNEL, CONV2_STRIDE, CONV2_PAD
};

// --- pool2 (maxpool 3x3, stride 2) ---
const TensorShape pool2_shape = {
    CONV2_HEIGHT, CONV2_WIDTH, CONV2_CHANNELS, POOL2_HEIGHT, POOL2_WIDTH, CONV2_CHANNELS
};

// --- conv3 ---
const TensorShape conv3_shape = {
    POOL2_HEIGHT, POOL2_WIDTH, CONV2_CHANNELS, CONV3_HEIGHT, CONV3_WIDTH, CONV3_CHANNELS
};

const ConvParams conv3_params = {
    features_6_weight, features_6_bias, CONV3_KERNEL, CONV3_STRIDE, CONV3_PAD
};

// --- conv4 ---
const TensorShape conv4_shape = {
    CONV3_HEIGHT, CONV3_WIDTH, CONV3_CHANNELS, CONV4_HEIGHT, CONV4_WIDTH, CONV4_CHANNELS
};

const ConvParams conv4_params = {
    features_8_weight, features_8_bias, CONV4_KERNEL, CONV4_STRIDE, CONV4_PAD
};

// --- conv5 ---
const TensorShape conv5_shape = {
    CONV4_HEIGHT, CONV4_WIDTH, CONV4_CHANNELS, CONV5_HEIGHT, CONV5_WIDTH, CONV5_CHANNELS
};

const ConvParams conv5_params = {
    features_10_weight, features_10_bias, CONV5_KERNEL, CONV5_STRIDE, CONV5_PAD
};

// --- pool5 (maxpool 3x3, stride 2) ---
const TensorShape pool5_shape = {
    CONV5_HEIGHT, CONV5_WIDTH, CONV5_CHANNELS, POOL5_HEIGHT, POOL5_WIDTH, CONV5_CHANNELS
};

// --- fc6 ---
const TensorShape fc6_shape = {
    1, 1, FC6_IN, 1, 1, FC6_OUT
};

const ConvParams fc6_params = {
    classifier_1_weight, classifier_1_bias, 0, 0, 0 // K, s, p unused by fc()
};

// --- fc7 ---
const TensorShape fc7_shape = {
    1, 1, FC6_OUT, 1, 1, FC7_OUT
};

const ConvParams fc7_params = {
    classifier_4_weight, classifier_4_bias, 0, 0, 0
};

// --- fc8 ---
const TensorShape fc8_shape = {
    1, 1, FC7_OUT, 1, 1, FC8_OUT
};

const ConvParams fc8_params = {
    classifier_6_weight, classifier_6_bias, 0, 0, 0
};

#endif
