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

    #include "../params/MMCBlock3_mmLayer1_branch11_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer1_branch11_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer1_branch11_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer1_branch11_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer1_branch11_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer1_branch33a_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer1_branch33a_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer1_branch33a_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer1_branch33a_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer1_branch33a_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer1_branch33b_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer1_branch33b_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer1_branch33b_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer1_branch33b_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer1_branch33b_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer1_branch33c_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer1_branch33c_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer1_branch33c_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer1_branch33c_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer1_branch33c_bn_running_var.h"

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

    #include "../params/MMCBlock3_mmLayer2_branch11_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer2_branch11_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer2_branch11_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer2_branch11_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer2_branch11_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer2_branch33a_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer2_branch33a_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer2_branch33a_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer2_branch33a_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer2_branch33a_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer2_branch33b_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer2_branch33b_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer2_branch33b_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer2_branch33b_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer2_branch33b_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer2_branch33c_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer2_branch33c_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer2_branch33c_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer2_branch33c_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer2_branch33c_bn_running_var.h"

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

    #include "../params/MMCBlock3_mmLayer3_branch11_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer3_branch11_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer3_branch11_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer3_branch11_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer3_branch11_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer3_branch33a_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer3_branch33a_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer3_branch33a_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer3_branch33a_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer3_branch33a_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer3_branch33b_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer3_branch33b_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer3_branch33b_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer3_branch33b_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer3_branch33b_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer3_branch33c_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer3_branch33c_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer3_branch33c_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer3_branch33c_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer3_branch33c_bn_running_var.h"

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

    #include "../params/MMCBlock3_mmLayer4_branch11_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer4_branch11_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer4_branch11_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer4_branch11_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer4_branch11_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer4_branch33a_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer4_branch33a_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer4_branch33a_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer4_branch33a_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer4_branch33a_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer4_branch33b_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer4_branch33b_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer4_branch33b_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer4_branch33b_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer4_branch33b_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer4_branch33c_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer4_branch33c_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer4_branch33c_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer4_branch33c_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer4_branch33c_bn_running_var.h"

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

    #include "../params/MMCBlock3_mmLayer5_branch11_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer5_branch11_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer5_branch11_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer5_branch11_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer5_branch11_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer5_branch33a_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer5_branch33a_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer5_branch33a_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer5_branch33a_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer5_branch33a_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer5_branch33b_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer5_branch33b_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer5_branch33b_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer5_branch33b_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer5_branch33b_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer5_branch33c_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer5_branch33c_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer5_branch33c_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer5_branch33c_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer5_branch33c_bn_running_var.h"

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

    #include "../params/MMCBlock3_mmLayer6_branch11_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer6_branch11_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer6_branch11_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer6_branch11_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer6_branch11_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer6_branch33a_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer6_branch33a_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer6_branch33a_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer6_branch33a_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer6_branch33a_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer6_branch33b_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer6_branch33b_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer6_branch33b_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer6_branch33b_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer6_branch33b_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer6_branch33c_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer6_branch33c_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer6_branch33c_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer6_branch33c_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer6_branch33c_bn_running_var.h"

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

    #include "../params/MMCBlock3_mmLayer7_branch11_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer7_branch11_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer7_branch11_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer7_branch11_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer7_branch11_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer7_branch33a_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer7_branch33a_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer7_branch33a_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer7_branch33a_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer7_branch33a_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer7_branch33b_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer7_branch33b_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer7_branch33b_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer7_branch33b_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer7_branch33b_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer7_branch33c_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer7_branch33c_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer7_branch33c_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer7_branch33c_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer7_branch33c_bn_running_var.h"

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

    #include "../params/MMCBlock3_mmLayer8_branch11_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer8_branch11_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer8_branch11_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer8_branch11_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer8_branch11_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer8_branch33a_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer8_branch33a_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer8_branch33a_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer8_branch33a_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer8_branch33a_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer8_branch33b_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer8_branch33b_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer8_branch33b_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer8_branch33b_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer8_branch33b_bn_running_var.h"

    #include "../params/MMCBlock3_mmLayer8_branch33c_conv_weight.h"
    #include "../params/MMCBlock3_mmLayer8_branch33c_bn_gamma.h"
    #include "../params/MMCBlock3_mmLayer8_branch33c_bn_beta.h"
    #include "../params/MMCBlock3_mmLayer8_branch33c_bn_running_mean.h"
    #include "../params/MMCBlock3_mmLayer8_branch33c_bn_running_var.h"

//}}}

//--------------------------------------------------------
//                      ConvNorm 3
//--------------------------------------------------------
//{{{

    #include "../params/tran_ConvNormRelu3_conv_weight.h"
    #include "../params/tran_ConvNormRelu3_bn_gamma.h"
    #include "../params/tran_ConvNormRelu3_bn_beta.h"
    #include "../params/tran_ConvNormRelu3_bn_running_mean.h"
    #include "../params/tran_ConvNormRelu3_bn_running_var.h"

//}}}

#endif
