#ifndef __DEBUG_FUNCS_H__
#define __DEBUG_FUNCS_H__

    #define PRINT_STATS(ARR, SIZE)                                  \
        do {                                                        \
            printf("--- " #ARR " ---\n");                           \
            unsigned long _sum = 0;                                 \
            for (int _i = 0; _i < (SIZE); _i++) {                   \
                _sum += (ARR)[_i];                                  \
                printf("%lu\n", (unsigned long)(ARR)[_i]);          \
            }                                                       \
            printf("total: %lu | avg: %lu\n", _sum, _sum / (SIZE)); \
        } while (0)

#endif
