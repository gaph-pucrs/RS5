#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "model.h"

typedef struct _dataset {
    int rel_time;
    int hops;
    int size;
    int prod;
    int cons;
    int latency;
} dataset_t;

dataset_t data[] = {
    {0,     2, 133, 5, 0, 668},
    {7109,  1, 133, 5, 1, 660},
    {17729, 3, 133, 5, 2, 673},
    {23788, 1, 133, 5, 3, 659},
    {30784, 2, 133, 5, 4, 668},
    {38507, 2, 133, 5, 0, 580},
    {45441, 1, 133, 5, 1, 574},
    {52381, 3, 133, 5, 2, 588},
    {59280, 1, 133, 5, 3, 572},
};

int model(int rel_timestamp, int hops, int size, int prod, int cons);

int main()
{
    const int n = (sizeof(data)/sizeof(dataset_t));
    int sqerr = 0;
    for (int i = 0; i < n; i++) {
        dataset_t *d = &data[i];
        int latency = model(d->rel_time, d->hops, d->size, d->prod, d->cons);
        int err = (d->latency - latency);
        sqerr += pow(err, 2);
    }
    float mse = sqerr / (float)n;
    int rmse = sqrt(mse) * 1000.0;
    int rmse_dec = rmse / 1000;
    int rmse_rl  = rmse - (rmse_dec*1000);
    printf("RMSE: %d.%d\n", rmse_dec, rmse_rl);
    return 0;
}
