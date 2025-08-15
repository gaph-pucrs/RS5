#ifndef __LMFRNET_STAGE1_H__
#define __LMFRNET_STAGE1_H__

    #define STAGE_1_CHANNELS   32
    #define STAGE_1_HEIGHT     32
    #define STAGE_1_WIDTH      32
    #define STAGE_1_STRIDE      1

    #include "../params-quant/stemBlock_stemConv_conv_weight.h"
    #include "../params-quant/stemBlock_stemConv_conv_bias.h"
    #include "../params-quant/stemBlock_stemConv_bn_gamma.h"
    #include "../params-quant/stemBlock_stemConv_bn_beta.h"
    #include "../params-quant/stemBlock_stemConv_bn_running_mean.h"
    #include "../params-quant/stemBlock_stemConv_bn_deviation.h"

#endif
