#ifndef __CNN_COMMON_H__
#define __CNN_COMMON_H__
    
    #include <stdint.h>
    #include "debug.h"

    // N-bit weights and activations, 2N-bit accumulators (and biases, at the accumulator
    // scale): the headers must come from lmfrnet-utils/quantize.py --precision w8a8|w16a16
    #ifdef W16A16
        typedef int16_t act_t;
        typedef int16_t weight_t;
        typedef int32_t acc_t;
        #define ACT_MIN INT16_MIN
        #define ACT_MAX INT16_MAX
    #else
        typedef int8_t  act_t;
        typedef int8_t  weight_t;
        typedef int16_t acc_t;
        #define ACT_MIN INT8_MIN
        #define ACT_MAX INT8_MAX
    #endif

    // a value outside act_t would wrap when stored (int8: 130 -> -126, -130 -> 126),
    // so clamp it to the closest one act_t holds
    static inline act_t sat (const int v)
    {
        if (v > ACT_MAX) return ACT_MAX;
        if (v < ACT_MIN) return ACT_MIN;
        return v;
    }

    typedef struct {
        int H_in, W_in, C_in;
        int H_out, W_out, C_out;
    } TensorShape;

    typedef struct {
        const weight_t *w;
        const acc_t *b;
        int K;
        int s;
        int shift; // requantization: acc >> shift, rounded and saturated to act_t
    } ConvParams;

    typedef struct {
        ConvParams b11;
        ConvParams b33a;
        ConvParams b33b;
        ConvParams b33c;
    } MFBlockParams;

    typedef struct {
        TensorShape b11;
        TensorShape b33a;
        TensorShape b33b;
        TensorShape b33c;
    } MFBlockShapes;

    // keeps GCC from vectorizing (or turning into memset/memcpy) a function's
    // loops, so the vector build only has the hand-written RVV code
    #define KERNEL __attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns")))

    #ifndef VECTOR
        #include "cnn_common_scalar.h"
    #else
        #include "cnn_common_vector.h"
    #endif

#endif