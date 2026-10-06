#ifndef PRINT_U64_H
#define PRINT_U64_H

#include <stdint.h>

/* Convert a uint64_t to a decimal string.
 * Uses a static buffer — call only once per printf invocation.
 * Replaces %llu (unsupported by newlib-nano) with %s + u64_str(). */
__attribute__((optimize("no-tree-vectorize")))
static inline const char *u64_str(uint64_t val)
{
    static char buf[21];
    if (val == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return buf;
    }
    int i = 20;
    buf[i] = '\0';
    while (val > 0) {
        buf[--i] = '0' + (int)(val % 10);
        val /= 10;
    }
    return buf + i;
}

#endif /* PRINT_U64_H */
