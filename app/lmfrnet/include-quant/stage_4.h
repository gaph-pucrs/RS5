#ifndef __LMFRNET_STAGE4_H__
#define __LMFRNET_STAGE4_H__

    #define STAGE_4_HEIGHT       4
    #define STAGE_4_WIDTH        4
    #define STAGE_4_CHANNELS   392

//--------------------------------------------------------
//                      Layer1
//--------------------------------------------------------
//{{{

    #define MMCBlock3_mmLayer1_branch11_CHANNELS    12
    #define MMCBlock3_mmLayer1_branch33a_CHANNELS   12
    #define MMCBlock3_mmLayer1_branch33b_CHANNELS    6
    #define MMCBlock3_mmLayer1_branch33c_CHANNELS    6
    #define MMCBlock3_mmLayer1_CHANNELS            224

    #include "../params-quant/MMCBlock3_mmLayer1_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer1_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer1_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer1_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer1_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer1_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer1_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer1_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer1_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer1_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer1_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer1_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer1_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer1_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer1_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer1_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer1_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer1_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer1_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer1_branch33c_bn_deviation.h"

//}}}
//--------------------------------------------------------
//                      Layer2
//--------------------------------------------------------
//{{{

    #define MMCBlock3_mmLayer2_branch11_CHANNELS    12
    #define MMCBlock3_mmLayer2_branch33a_CHANNELS   12
    #define MMCBlock3_mmLayer2_branch33b_CHANNELS    6
    #define MMCBlock3_mmLayer2_branch33c_CHANNELS    6
    #define MMCBlock3_mmLayer2_CHANNELS            248

    #include "../params-quant/MMCBlock3_mmLayer2_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer2_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer2_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer2_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer2_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer2_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer2_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer2_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer2_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer2_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer2_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer2_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer2_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer2_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer2_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer2_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer2_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer2_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer2_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer2_branch33c_bn_deviation.h"

//}}}

//--------------------------------------------------------
//                      Layer3
//--------------------------------------------------------
//{{{

    #define MMCBlock3_mmLayer3_branch11_CHANNELS    12
    #define MMCBlock3_mmLayer3_branch33a_CHANNELS   12
    #define MMCBlock3_mmLayer3_branch33b_CHANNELS    6
    #define MMCBlock3_mmLayer3_branch33c_CHANNELS    6
    #define MMCBlock3_mmLayer3_CHANNELS            272 

    #include "../params-quant/MMCBlock3_mmLayer3_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer3_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer3_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer3_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer3_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer3_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer3_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer3_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer3_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer3_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer3_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer3_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer3_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer3_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer3_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer3_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer3_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer3_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer3_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer3_branch33c_bn_deviation.h"

//}}}
//--------------------------------------------------------
//                      Layer4
//--------------------------------------------------------
//{{{

    #define MMCBlock3_mmLayer4_branch11_CHANNELS    12
    #define MMCBlock3_mmLayer4_branch33a_CHANNELS   12
    #define MMCBlock3_mmLayer4_branch33b_CHANNELS    6
    #define MMCBlock3_mmLayer4_branch33c_CHANNELS    6
    #define MMCBlock3_mmLayer4_CHANNELS            296

    #include "../params-quant/MMCBlock3_mmLayer4_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer4_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer4_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer4_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer4_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer4_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer4_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer4_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer4_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer4_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer4_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer4_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer4_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer4_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer4_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer4_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer4_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer4_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer4_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer4_branch33c_bn_deviation.h"

//}}}

//--------------------------------------------------------
//                      Layer5
//--------------------------------------------------------
//{{{

    #define MMCBlock3_mmLayer5_branch11_CHANNELS    12
    #define MMCBlock3_mmLayer5_branch33a_CHANNELS   12
    #define MMCBlock3_mmLayer5_branch33b_CHANNELS    6
    #define MMCBlock3_mmLayer5_branch33c_CHANNELS    6
    #define MMCBlock3_mmLayer5_CHANNELS            320

    #include "../params-quant/MMCBlock3_mmLayer5_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer5_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer5_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer5_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer5_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer5_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer5_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer5_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer5_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer5_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer5_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer5_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer5_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer5_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer5_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer5_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer5_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer5_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer5_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer5_branch33c_bn_deviation.h"

//}}}

//--------------------------------------------------------
//                      Layer6
//--------------------------------------------------------
//{{{

    #define MMCBlock3_mmLayer6_branch11_CHANNELS    12
    #define MMCBlock3_mmLayer6_branch33a_CHANNELS   12
    #define MMCBlock3_mmLayer6_branch33b_CHANNELS    6
    #define MMCBlock3_mmLayer6_branch33c_CHANNELS    6
    #define MMCBlock3_mmLayer6_CHANNELS            344

    #include "../params-quant/MMCBlock3_mmLayer6_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer6_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer6_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer6_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer6_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer6_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer6_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer6_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer6_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer6_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer6_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer6_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer6_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer6_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer6_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer6_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer6_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer6_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer6_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer6_branch33c_bn_deviation.h"

//}}}

//--------------------------------------------------------
//                      Layer7
//--------------------------------------------------------
//{{{

    #define MMCBlock3_mmLayer7_branch11_CHANNELS    12
    #define MMCBlock3_mmLayer7_branch33a_CHANNELS   12
    #define MMCBlock3_mmLayer7_branch33b_CHANNELS    6
    #define MMCBlock3_mmLayer7_branch33c_CHANNELS    6
    #define MMCBlock3_mmLayer7_CHANNELS            368

    #include "../params-quant/MMCBlock3_mmLayer7_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer7_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer7_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer7_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer7_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer7_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer7_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer7_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer7_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer7_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer7_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer7_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer7_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer7_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer7_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer7_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer7_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer7_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer7_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer7_branch33c_bn_deviation.h"

//}}}

//--------------------------------------------------------
//                      Layer8
//--------------------------------------------------------
//{{{

    #define MMCBlock3_mmLayer8_branch11_CHANNELS    12
    #define MMCBlock3_mmLayer8_branch33a_CHANNELS   12
    #define MMCBlock3_mmLayer8_branch33b_CHANNELS    6
    #define MMCBlock3_mmLayer8_branch33c_CHANNELS    6
    #define MMCBlock3_mmLayer8_CHANNELS            392

    #include "../params-quant/MMCBlock3_mmLayer8_branch11_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer8_branch11_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer8_branch11_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer8_branch11_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer8_branch11_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer8_branch33a_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer8_branch33a_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer8_branch33a_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer8_branch33a_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer8_branch33a_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer8_branch33b_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer8_branch33b_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer8_branch33b_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer8_branch33b_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer8_branch33b_bn_deviation.h"

    #include "../params-quant/MMCBlock3_mmLayer8_branch33c_conv_weight.h"
    #include "../params-quant/MMCBlock3_mmLayer8_branch33c_bn_gamma.h"
    #include "../params-quant/MMCBlock3_mmLayer8_branch33c_bn_beta.h"
    #include "../params-quant/MMCBlock3_mmLayer8_branch33c_bn_running_mean.h"
    #include "../params-quant/MMCBlock3_mmLayer8_branch33c_bn_deviation.h"

//}}}

//--------------------------------------------------------
//                      ConvNorm 3
//--------------------------------------------------------
//{{{

    #include "../params-quant/tran_ConvNormRelu3_conv_weight.h"
    #include "../params-quant/tran_ConvNormRelu3_bn_gamma.h"
    #include "../params-quant/tran_ConvNormRelu3_bn_beta.h"
    #include "../params-quant/tran_ConvNormRelu3_bn_running_mean.h"
    #include "../params-quant/tran_ConvNormRelu3_bn_deviation.h"

//}}}

#endif
