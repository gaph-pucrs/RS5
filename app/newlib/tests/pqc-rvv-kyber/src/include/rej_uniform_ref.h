#ifndef REJ_UNIFORM_REF_H
#define REJ_UNIFORM_REF_H

#include <stdint.h>

#include "params.h"

/*
 * Reference rejection sampling (static in the reference indcpa.c). Defined
 * here, not in a .c file, so ref_O2.c can build it again at -O2 under another
 * name; main.c has the -Os one.
 */
unsigned int rej_uniform_ref(int16_t *r, unsigned int len, const uint8_t *buf, unsigned int buflen)
{
    unsigned int ctr = 0, pos = 0;
    while (ctr < len && pos + 3 <= buflen) {
        uint16_t val0 = ((buf[pos + 0] >> 0) | ((uint16_t)buf[pos + 1] << 8)) & 0xFFF;
        uint16_t val1 = ((buf[pos + 1] >> 4) | ((uint16_t)buf[pos + 2] << 4)) & 0xFFF;
        pos += 3;
        if (val0 < KYBER_Q)
            r[ctr++] = val0;
        if (ctr < len && val1 < KYBER_Q)
            r[ctr++] = val1;
    }
    return ctr;
}

#endif
