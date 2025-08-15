#ifndef __LMFRNET_STAGE5_H__
#define __LMFRNET_STAGE5_H__

    #define STAGE_5_HEIGHT       4
    #define STAGE_5_WIDTH        4
    #define STAGE_5_CHANNELS   464

//--------------------------------------------------------
//                      Layer1
//--------------------------------------------------------
//{{{

    #define MMCBlock4_mmLayer1_branch11_CHANNELS    12
    #define MMCBlock4_mmLayer1_branch33a_CHANNELS   12
    #define MMCBlock4_mmLayer1_branch33b_CHANNELS    6
    #define MMCBlock4_mmLayer1_branch33c_CHANNELS    6
    #define MMCBlock4_mmLayer1_CHANNELS            416

    #include "../params-quant/MMCBlock4_mmLayer1_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock4_mmLayer1_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock4_mmLayer1_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock4_mmLayer1_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock4_mmLayer1_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock4_mmLayer1_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock4_mmLayer1_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock4_mmLayer1_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock4_mmLayer1_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock4_mmLayer1_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock4_mmLayer1_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock4_mmLayer1_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock4_mmLayer1_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock4_mmLayer1_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock4_mmLayer1_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock4_mmLayer1_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock4_mmLayer1_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock4_mmLayer1_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock4_mmLayer1_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock4_mmLayer1_branch33c_bn_deviation.h"

//}}}
//--------------------------------------------------------
//                      Layer2
//--------------------------------------------------------
//{{{

    #define MMCBlock4_mmLayer2_branch11_CHANNELS    12
    #define MMCBlock4_mmLayer2_branch33a_CHANNELS   12
    #define MMCBlock4_mmLayer2_branch33b_CHANNELS    6
    #define MMCBlock4_mmLayer2_branch33c_CHANNELS    6
    #define MMCBlock4_mmLayer2_CHANNELS            440

    #include "../params-quant/MMCBlock4_mmLayer2_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock4_mmLayer2_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock4_mmLayer2_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock4_mmLayer2_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock4_mmLayer2_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock4_mmLayer2_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock4_mmLayer2_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock4_mmLayer2_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock4_mmLayer2_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock4_mmLayer2_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock4_mmLayer2_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock4_mmLayer2_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock4_mmLayer2_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock4_mmLayer2_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock4_mmLayer2_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock4_mmLayer2_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock4_mmLayer2_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock4_mmLayer2_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock4_mmLayer2_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock4_mmLayer2_branch33c_bn_deviation.h"

//}}}

//--------------------------------------------------------
//                      Layer3
//--------------------------------------------------------
//{{{

    #define MMCBlock4_mmLayer3_branch11_CHANNELS    12
    #define MMCBlock4_mmLayer3_branch33a_CHANNELS   12
    #define MMCBlock4_mmLayer3_branch33b_CHANNELS    6
    #define MMCBlock4_mmLayer3_branch33c_CHANNELS    6
    #define MMCBlock4_mmLayer3_CHANNELS            464

    #include "../params-quant/MMCBlock4_mmLayer3_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock4_mmLayer3_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock4_mmLayer3_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock4_mmLayer3_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock4_mmLayer3_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock4_mmLayer3_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock4_mmLayer3_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock4_mmLayer3_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock4_mmLayer3_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock4_mmLayer3_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock4_mmLayer3_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock4_mmLayer3_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock4_mmLayer3_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock4_mmLayer3_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock4_mmLayer3_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock4_mmLayer3_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock4_mmLayer3_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock4_mmLayer3_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock4_mmLayer3_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock4_mmLayer3_branch33c_bn_deviation.h"

//}}}
//--------------------------------------------------------
//                      ConvNorm 4
//--------------------------------------------------------
//{{{

    #include "../params-quant/tran_ConvNormRelu4_conv_weight.h"
    #include "../params-quant/tran_ConvNormRelu4_bn_gamma.h"
    #include "../params-quant/tran_ConvNormRelu4_bn_beta.h"
    #include "../params-quant/tran_ConvNormRelu4_bn_running_mean.h"
    #include "../params-quant/tran_ConvNormRelu4_bn_deviation.h"

//}}}

#endif
