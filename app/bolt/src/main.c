#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include <model.h>
#include <test.h>

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
