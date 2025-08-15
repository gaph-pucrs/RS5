#ifndef __LMFRNET_STAGE3_H__
#define __LMFRNET_STAGE3_H__

    #define STAGE_3_HEIGHT       8
    #define STAGE_3_WIDTH        8
    #define STAGE_3_CHANNELS   200

//--------------------------------------------------------
//                      Layer1
//--------------------------------------------------------
//{{{

    #define MMCBlock2_mmLayer1_branch11_CHANNELS    12
    #define MMCBlock2_mmLayer1_branch33a_CHANNELS   12
    #define MMCBlock2_mmLayer1_branch33b_CHANNELS    6
    #define MMCBlock2_mmLayer1_branch33c_CHANNELS    6
    #define MMCBlock2_mmLayer1_CHANNELS            128

    #include "../params-quant/MMCBlock2_mmLayer1_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock2_mmLayer1_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock2_mmLayer1_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock2_mmLayer1_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock2_mmLayer1_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock2_mmLayer1_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock2_mmLayer1_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock2_mmLayer1_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock2_mmLayer1_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock2_mmLayer1_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock2_mmLayer1_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock2_mmLayer1_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock2_mmLayer1_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock2_mmLayer1_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock2_mmLayer1_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock2_mmLayer1_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock2_mmLayer1_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock2_mmLayer1_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock2_mmLayer1_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock2_mmLayer1_branch33c_bn_deviation.h"

//}}}
//--------------------------------------------------------
//                      Layer2
//--------------------------------------------------------
//{{{

    #define MMCBlock2_mmLayer2_branch11_CHANNELS    12
    #define MMCBlock2_mmLayer2_branch33a_CHANNELS   12
    #define MMCBlock2_mmLayer2_branch33b_CHANNELS    6
    #define MMCBlock2_mmLayer2_branch33c_CHANNELS    6
    #define MMCBlock2_mmLayer2_CHANNELS            152

    #include "../params-quant/MMCBlock2_mmLayer2_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock2_mmLayer2_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock2_mmLayer2_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock2_mmLayer2_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock2_mmLayer2_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock2_mmLayer2_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock2_mmLayer2_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock2_mmLayer2_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock2_mmLayer2_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock2_mmLayer2_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock2_mmLayer2_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock2_mmLayer2_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock2_mmLayer2_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock2_mmLayer2_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock2_mmLayer2_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock2_mmLayer2_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock2_mmLayer2_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock2_mmLayer2_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock2_mmLayer2_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock2_mmLayer2_branch33c_bn_deviation.h"

//}}}

//--------------------------------------------------------
//                      Layer3
//--------------------------------------------------------
//{{{

    #define MMCBlock2_mmLayer3_branch11_CHANNELS    12
    #define MMCBlock2_mmLayer3_branch33a_CHANNELS   12
    #define MMCBlock2_mmLayer3_branch33b_CHANNELS    6
    #define MMCBlock2_mmLayer3_branch33c_CHANNELS    6
    #define MMCBlock2_mmLayer3_CHANNELS            176

    #include "../params-quant/MMCBlock2_mmLayer3_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock2_mmLayer3_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock2_mmLayer3_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock2_mmLayer3_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock2_mmLayer3_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock2_mmLayer3_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock2_mmLayer3_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock2_mmLayer3_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock2_mmLayer3_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock2_mmLayer3_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock2_mmLayer3_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock2_mmLayer3_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock2_mmLayer3_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock2_mmLayer3_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock2_mmLayer3_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock2_mmLayer3_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock2_mmLayer3_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock2_mmLayer3_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock2_mmLayer3_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock2_mmLayer3_branch33c_bn_deviation.h"

//}}}
//--------------------------------------------------------
//                      Layer4
//--------------------------------------------------------
//{{{

    #define MMCBlock2_mmLayer4_branch11_CHANNELS    12
    #define MMCBlock2_mmLayer4_branch33a_CHANNELS   12
    #define MMCBlock2_mmLayer4_branch33b_CHANNELS    6
    #define MMCBlock2_mmLayer4_branch33c_CHANNELS    6
    #define MMCBlock2_mmLayer4_CHANNELS            200

    #include "../params-quant/MMCBlock2_mmLayer4_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock2_mmLayer4_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock2_mmLayer4_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock2_mmLayer4_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock2_mmLayer4_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock2_mmLayer4_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock2_mmLayer4_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock2_mmLayer4_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock2_mmLayer4_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock2_mmLayer4_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock2_mmLayer4_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock2_mmLayer4_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock2_mmLayer4_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock2_mmLayer4_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock2_mmLayer4_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock2_mmLayer4_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock2_mmLayer4_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock2_mmLayer4_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock2_mmLayer4_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock2_mmLayer4_branch33c_bn_deviation.h"

//}}}

//--------------------------------------------------------
//                      ConvNorm 2
//--------------------------------------------------------
//{{{

    #include "../params-quant/tran_ConvNormRelu2_conv_weight.h"
    #include "../params-quant/tran_ConvNormRelu2_bn_gamma.h"
    #include "../params-quant/tran_ConvNormRelu2_bn_beta.h"
    #include "../params-quant/tran_ConvNormRelu2_bn_running_mean.h"
    #include "../params-quant/tran_ConvNormRelu2_bn_deviation.h"

//}}}
#endif
