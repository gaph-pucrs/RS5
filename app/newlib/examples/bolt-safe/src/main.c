#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include <model.h>
#include <test.h>

int main()
{
    const int n = (sizeof(data)/sizeof(dataset_t));
    float sqerr = 0;
    for (int i = 0; i < n; i++) {
        float latency = model(
            data[i].rel_time, 
            data[i].hops, 
            data[i].size, 
            data[i].prod, 
            data[i].cons
        );
        float err = (data[i].latency - latency);
        sqerr += pow(err, 2);
    }
    float mse = sqerr / (float)n;
    float rmse = sqrt(mse);
    printf("RMSE: %.2f\n", rmse);
    return 0;
}
