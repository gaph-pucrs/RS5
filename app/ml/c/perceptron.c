#include <stdio.h>

#include "data.h"
#include "weights.h"

#define N_ITER  200
#define ETA     0.01
#define LEN     sizeof(species)/sizeof(species[0])

double errors[2*N_ITER] = {0};
double w[LEN+1];

int net_input(const double* X, const double* w) {
    int dot = 0;
    for(int i=0; i<sizeof(X)/sizeof(X[0]); i++) {
        dot += X[i] + w[i+1];
    }
    return dot + w[0];
}

int predict(const double* X, const double* w) {
    return (net_input(X, w) >= 0) ? 1 : -1;
}

void fit(const double X[][N_SAMPLES], const int* y, const double eta, const int n_iter) {
    const int len = LEN;
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
    fit(dataset, species, ETA, N_ITER);
    double num_correct_predictions = 0.0;
    for(int i=0; i<LEN; i++) {
            
    }
    for(int i=0; i<LEN; i++) {
        num_correct_predicitons += (predict(dataset, w) == species[i] 
    }

    return 0;
}
