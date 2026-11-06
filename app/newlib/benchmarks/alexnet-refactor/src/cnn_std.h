#ifndef __CNN_STD_H__
#define __CNN_STD_H__

// must match QUANTIZATION_SCALE = 8192 (2^13) in alexnet-utils/gen_weights.py
#define QUANT_SHIFT  13

// torchvision AlexNet, CHW activations

#define IMAGE_HEIGHT    224
#define IMAGE_WIDTH     224
#define IMAGE_CHANNELS    3

#define CONV1_HEIGHT     55
#define CONV1_WIDTH      55
#define CONV1_CHANNELS   64
#define CONV1_KERNEL     11
#define CONV1_STRIDE      4
#define CONV1_PAD         2

#define POOL1_HEIGHT     27
#define POOL1_WIDTH      27

#define CONV2_HEIGHT     27
#define CONV2_WIDTH      27
#define CONV2_CHANNELS  192
#define CONV2_KERNEL      5
#define CONV2_STRIDE      1
#define CONV2_PAD         2

#define POOL2_HEIGHT     13
#define POOL2_WIDTH      13

#define CONV3_HEIGHT     13
#define CONV3_WIDTH      13
#define CONV3_CHANNELS  384
#define CONV3_KERNEL      3
#define CONV3_STRIDE      1
#define CONV3_PAD         1

#define CONV4_HEIGHT     13
#define CONV4_WIDTH      13
#define CONV4_CHANNELS  256
#define CONV4_KERNEL      3
#define CONV4_STRIDE      1
#define CONV4_PAD         1

#define CONV5_HEIGHT     13
#define CONV5_WIDTH      13
#define CONV5_CHANNELS  256
#define CONV5_KERNEL      3
#define CONV5_STRIDE      1
#define CONV5_PAD         1

#define POOL5_HEIGHT      6
#define POOL5_WIDTH       6

// avgpool (AdaptiveAvgPool2d(6, 6)) is the identity for a 224x224 input, and
// flattening the CHW pool5 output matches torch.flatten
#define FC6_IN         (CONV5_CHANNELS*POOL5_HEIGHT*POOL5_WIDTH)
#define FC6_OUT        4096
#define FC7_OUT        4096
#define FC8_OUT        1000

#endif
