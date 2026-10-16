#ifndef __CNN_COMMON_H__
#define __CNN_COMMON_H__

    #include "cnn_std.h"

    typedef int type;

    typedef struct {
        int H_in, W_in, C_in;
        int H_out, W_out, C_out;
    } TensorShape;

    typedef struct {
        const type *w;  // conv: [C_out][C_in][K][K], fc: [C_out][C_in]
        const type *b;  // [C_out]
        int K;
        int s;
        int p;
    } ConvParams;

    // keeps GCC from vectorizing (or turning into memset/memcpy) the scalar loops,
    // so the scalar build has no vector code and the vector build only has ours
    #define KERNEL __attribute__((optimize("no-tree-vectorize","no-tree-slp-vectorize","no-tree-loop-distribute-patterns")))

    #ifndef VECTOR
        #include "cnn_common_scalar.h"
    #else
        #include "cnn_common_vector.h"
    #endif

#endif
