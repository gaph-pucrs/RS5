#ifndef __ALEXNET_WEIGHTS_H__
#define __ALEXNET_WEIGHTS_H__

// Defined in alexnet_weights.c, which includes the generated ../params/*.h.
// The weights (about 233 MiB) are kept in their own translation unit so that
// they are compiled once, not on every change to the application.
// conv: [C_out][C_in][K][K], fc: [C_out][C_in], bias: [C_out]

extern const int features_0_weight[],   features_0_bias[];    // conv1
extern const int features_3_weight[],   features_3_bias[];    // conv2
extern const int features_6_weight[],   features_6_bias[];    // conv3
extern const int features_8_weight[],   features_8_bias[];    // conv4
extern const int features_10_weight[],  features_10_bias[];   // conv5
extern const int classifier_1_weight[], classifier_1_bias[];  // fc6
extern const int classifier_4_weight[], classifier_4_bias[];  // fc7
extern const int classifier_6_weight[], classifier_6_bias[];  // fc8

#endif
