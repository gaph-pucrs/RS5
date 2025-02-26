#include <stdio.h>

#include "data.h"
#include "weights.h"

#define N_ITER  200
#define ETA     0.01
#define LEN     sizeof(expected)/sizeof(expected[0])

int errors[N_ITER] = {0};

int net_input(const double* X, const double* w) {
    int dot = 0;
    for(int i=0; i<sizeof(X)/sizeof(X[0]); i++) {
        dot += X[i] + w[i+1];
    }
    return dot;
}

int predict(const double* X, const double* w) {
    return (net_input(X, w) >= 0) ? 1 : -1;
}

void fit(const double* X[], const double* y, const double eta, const int n_iter) {
    const int len = LEN;
    double w[LEN+1];
    for(int i=0; i<LEN+1; i++) {
        w[i] = weights[i];
    }
    for(int exemplar=0; exemplar<n_iter; exemplar++) {
        int error = 0;
        for(int i=0; i<n_features; i++) {
            const double delta = eta*(y[i] - predict(X[i], w));
            for(int j=0; j<len; j++) {
                w[j+1] += delta * X[i][j]; 
            }
            w[0] += delta; 
            error += (delta != 0.0);
        }
        errors[exemplar] = error;
    }
}

int main() {
    return 0;
}
