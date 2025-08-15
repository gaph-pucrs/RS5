#ifndef __LMFRNET_STAGE2_H__
#define __LMFRNET_STAGE2_H__

    #define STAGE_2_HEIGHT       16
    #define STAGE_2_WIDTH        16
    #define STAGE_2_CHANNELS    104

//--------------------------------------------------------
//                      Layer 1
//--------------------------------------------------------
//{{{

    #define MMCBlock1_mmLayer1_branch11_CHANNELS     12
    #define MMCBlock1_mmLayer1_branch33a_CHANNELS    12
    #define MMCBlock1_mmLayer1_branch33b_CHANNELS     6
    #define MMCBlock1_mmLayer1_branch33c_CHANNELS     6
    #define MMCBlock1_mmLayer1_CHANNELS              56

    #include "../params-quant/MMCBlock1_mmLayer1_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock1_mmLayer1_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock1_mmLayer1_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock1_mmLayer1_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock1_mmLayer1_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock1_mmLayer1_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock1_mmLayer1_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock1_mmLayer1_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock1_mmLayer1_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock1_mmLayer1_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock1_mmLayer1_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock1_mmLayer1_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock1_mmLayer1_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock1_mmLayer1_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock1_mmLayer1_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock1_mmLayer1_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock1_mmLayer1_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock1_mmLayer1_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock1_mmLayer1_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock1_mmLayer1_branch33c_bn_deviation.h"

//}}}
//--------------------------------------------------------
//                      Layer 2
//--------------------------------------------------------
//{{{

    #define MMCBlock1_mmLayer2_branch11_CHANNELS     12
    #define MMCBlock1_mmLayer2_branch33a_CHANNELS    12
    #define MMCBlock1_mmLayer2_branch33b_CHANNELS     6
    #define MMCBlock1_mmLayer2_branch33c_CHANNELS     6
    #define MMCBlock1_mmLayer2_CHANNELS              80

    #include "../params-quant/MMCBlock1_mmLayer2_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock1_mmLayer2_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock1_mmLayer2_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock1_mmLayer2_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock1_mmLayer2_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock1_mmLayer2_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock1_mmLayer2_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock1_mmLayer2_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock1_mmLayer2_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock1_mmLayer2_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock1_mmLayer2_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock1_mmLayer2_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock1_mmLayer2_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock1_mmLayer2_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock1_mmLayer2_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock1_mmLayer2_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock1_mmLayer2_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock1_mmLayer2_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock1_mmLayer2_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock1_mmLayer2_branch33c_bn_deviation.h"

//}}}
//--------------------------------------------------------
//                      Layer 3
//--------------------------------------------------------
//{{{

    #define MMCBlock1_mmLayer3_branch11_CHANNELS     12
    #define MMCBlock1_mmLayer3_branch33a_CHANNELS    12
    #define MMCBlock1_mmLayer3_branch33b_CHANNELS     6
    #define MMCBlock1_mmLayer3_branch33c_CHANNELS     6
    #define MMCBlock1_mmLayer3_CHANNELS             104

    #include "../params-quant/MMCBlock1_mmLayer3_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock1_mmLayer3_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock1_mmLayer3_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock1_mmLayer3_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock1_mmLayer3_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock1_mmLayer3_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock1_mmLayer3_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock1_mmLayer3_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock1_mmLayer3_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock1_mmLayer3_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock1_mmLayer3_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock1_mmLayer3_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock1_mmLayer3_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock1_mmLayer3_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock1_mmLayer3_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock1_mmLayer3_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock1_mmLayer3_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock1_mmLayer3_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock1_mmLayer3_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock1_mmLayer3_branch33c_bn_deviation.h"

//}}}
//--------------------------------------------------------
//                      ConvNorm 1
//--------------------------------------------------------
//{{{

    #include "../params-quant/tran_ConvNormRelu1_conv_weight.h"
    #include "../params-quant/tran_ConvNormRelu1_bn_gamma.h"
    #include "../params-quant/tran_ConvNormRelu1_bn_beta.h"
    #include "../params-quant/tran_ConvNormRelu1_bn_running_mean.h"
    #include "../params-quant/tran_ConvNormRelu1_bn_deviation.h"

///}}}
#endif
