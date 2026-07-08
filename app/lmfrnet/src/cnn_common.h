#ifndef __CNN_COMMON_H__
#define __CNN_COMMON_H__
    
    #include "debug.h"

    typedef int type;

    typedef struct {
        int H_in, W_in, C_in;
        int H_out, W_out, C_out;
    } TensorShape;

    typedef struct {
        const type *w;
        const type *b;
        int K;
        int s;
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

    #ifndef VECTOR
        #include "cnn_common_scalar.h"
    #else
        #include "cnn_common_vector.h"
    #endif

#endif