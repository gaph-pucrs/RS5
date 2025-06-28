#ifndef __LMFRNET_STAGE2_H__
#define __LMFRNET_STAGE2_H__

    #define STAGE_2_HEIGHT       16
    #define STAGE_2_WIDTH        16
    #define STAGE_2_CHANNELS    104

//--------------------------------------------------------
//                      Layer 1
//--------------------------------------------------------
    #define MMCBlock1_mmLayer1_branch11_CHANNELS     12
    #define MMCBlock1_mmLayer1_branch33a_CHANNELS    12
    #define MMCBlock1_mmLayer1_branch33b_CHANNELS     6
    #define MMCBlock1_mmLayer1_branch33c_CHANNELS     6
    #define MMCBlock1_mmLayer1_CHANNELS              56

    #include "../params/MMCBlock1_mmLayer1_branch11_conv_weight.h"
    #include "../params/MMCBlock1_mmLayer1_branch11_bn_gamma.h"
    #include "../params/MMCBlock1_mmLayer1_branch11_bn_beta.h"
    #include "../params/MMCBlock1_mmLayer1_branch11_bn_running_mean.h"
    #include "../params/MMCBlock1_mmLayer1_branch11_bn_running_var.h"

    #include "../params/MMCBlock1_mmLayer1_branch33a_conv_weight.h"
    #include "../params/MMCBlock1_mmLayer1_branch33a_bn_gamma.h"
    #include "../params/MMCBlock1_mmLayer1_branch33a_bn_beta.h"
    #include "../params/MMCBlock1_mmLayer1_branch33a_bn_running_mean.h"
    #include "../params/MMCBlock1_mmLayer1_branch33a_bn_running_var.h"

    #include "../params/MMCBlock1_mmLayer1_branch33b_conv_weight.h"
    #include "../params/MMCBlock1_mmLayer1_branch33b_bn_gamma.h"
    #include "../params/MMCBlock1_mmLayer1_branch33b_bn_beta.h"
    #include "../params/MMCBlock1_mmLayer1_branch33b_bn_running_mean.h"
    #include "../params/MMCBlock1_mmLayer1_branch33b_bn_running_var.h"

    #include "../params/MMCBlock1_mmLayer1_branch33c_conv_weight.h"
    #include "../params/MMCBlock1_mmLayer1_branch33c_bn_gamma.h"
    #include "../params/MMCBlock1_mmLayer1_branch33c_bn_beta.h"
    #include "../params/MMCBlock1_mmLayer1_branch33c_bn_running_mean.h"
    #include "../params/MMCBlock1_mmLayer1_branch33c_bn_running_var.h"

//--------------------------------------------------------
//                      Layer 2
//--------------------------------------------------------
    #define MMCBlock1_mmLayer2_branch11_CHANNELS     12
    #define MMCBlock1_mmLayer2_branch33a_CHANNELS    12
    #define MMCBlock1_mmLayer2_branch33b_CHANNELS     6
    #define MMCBlock1_mmLayer2_branch33c_CHANNELS     6
    #define MMCBlock1_mmLayer2_CHANNELS              80

    #include "../params/MMCBlock1_mmLayer2_branch11_conv_weight.h"
    #include "../params/MMCBlock1_mmLayer2_branch11_bn_gamma.h"
    #include "../params/MMCBlock1_mmLayer2_branch11_bn_beta.h"
    #include "../params/MMCBlock1_mmLayer2_branch11_bn_running_mean.h"
    #include "../params/MMCBlock1_mmLayer2_branch11_bn_running_var.h"

    #include "../params/MMCBlock1_mmLayer2_branch33a_conv_weight.h"
    #include "../params/MMCBlock1_mmLayer2_branch33a_bn_gamma.h"
    #include "../params/MMCBlock1_mmLayer2_branch33a_bn_beta.h"
    #include "../params/MMCBlock1_mmLayer2_branch33a_bn_running_mean.h"
    #include "../params/MMCBlock1_mmLayer2_branch33a_bn_running_var.h"

    #include "../params/MMCBlock1_mmLayer2_branch33b_conv_weight.h"
    #include "../params/MMCBlock1_mmLayer2_branch33b_bn_gamma.h"
    #include "../params/MMCBlock1_mmLayer2_branch33b_bn_beta.h"
    #include "../params/MMCBlock1_mmLayer2_branch33b_bn_running_mean.h"
    #include "../params/MMCBlock1_mmLayer2_branch33b_bn_running_var.h"

    #include "../params/MMCBlock1_mmLayer2_branch33c_conv_weight.h"
    #include "../params/MMCBlock1_mmLayer2_branch33c_bn_gamma.h"
    #include "../params/MMCBlock1_mmLayer2_branch33c_bn_beta.h"
    #include "../params/MMCBlock1_mmLayer2_branch33c_bn_running_mean.h"
    #include "../params/MMCBlock1_mmLayer2_branch33c_bn_running_var.h"

//--------------------------------------------------------
//                      Layer 3
//--------------------------------------------------------
    #define MMCBlock1_mmLayer3_branch11_CHANNELS     12
    #define MMCBlock1_mmLayer3_branch33a_CHANNELS    12
    #define MMCBlock1_mmLayer3_branch33b_CHANNELS     6
    #define MMCBlock1_mmLayer3_branch33c_CHANNELS     6
    #define MMCBlock1_mmLayer3_CHANNELS             104

    #include "../params/MMCBlock1_mmLayer3_branch11_conv_weight.h"
    #include "../params/MMCBlock1_mmLayer3_branch11_bn_gamma.h"
    #include "../params/MMCBlock1_mmLayer3_branch11_bn_beta.h"
    #include "../params/MMCBlock1_mmLayer3_branch11_bn_running_mean.h"
    #include "../params/MMCBlock1_mmLayer3_branch11_bn_running_var.h"

    #include "../params/MMCBlock1_mmLayer3_branch33a_conv_weight.h"
    #include "../params/MMCBlock1_mmLayer3_branch33a_bn_gamma.h"
    #include "../params/MMCBlock1_mmLayer3_branch33a_bn_beta.h"
    #include "../params/MMCBlock1_mmLayer3_branch33a_bn_running_mean.h"
    #include "../params/MMCBlock1_mmLayer3_branch33a_bn_running_var.h"

    #include "../params/MMCBlock1_mmLayer3_branch33b_conv_weight.h"
    #include "../params/MMCBlock1_mmLayer3_branch33b_bn_gamma.h"
    #include "../params/MMCBlock1_mmLayer3_branch33b_bn_beta.h"
    #include "../params/MMCBlock1_mmLayer3_branch33b_bn_running_mean.h"
    #include "../params/MMCBlock1_mmLayer3_branch33b_bn_running_var.h"

    #include "../params/MMCBlock1_mmLayer3_branch33c_conv_weight.h"
    #include "../params/MMCBlock1_mmLayer3_branch33c_bn_gamma.h"
    #include "../params/MMCBlock1_mmLayer3_branch33c_bn_beta.h"
    #include "../params/MMCBlock1_mmLayer3_branch33c_bn_running_mean.h"
    #include "../params/MMCBlock1_mmLayer3_branch33c_bn_running_var.h"

//--------------------------------------------------------
//                      ConvNorm 1
//--------------------------------------------------------
    #include "../params/tran_ConvNormRelu1_conv_weight.h"
    #include "../params/tran_ConvNormRelu1_bn_gamma.h"
    #include "../params/tran_ConvNormRelu1_bn_beta.h"
    #include "../params/tran_ConvNormRelu1_bn_running_mean.h"
    #include "../params/tran_ConvNormRelu1_bn_running_var.h"

#endif
