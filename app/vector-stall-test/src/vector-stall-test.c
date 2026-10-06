/* vector-stall-test: vector loads and stores while the data bus stalls the
 * core (testbench RAM_DELAY_CYCLES > 0). Ported from the SoC ddr_vtest.
 * Every vector access is checked against scalar accesses.
 *
 * Prints "Passed." or "Failed." at the end.
 */

#include <stdint.h>
#include <stdio.h>

static int errors;

static void check(const char *what, unsigned i, uint32_t got, uint32_t expected)
{
    if (got != expected) {
        if (errors < 12)
            printf("  %s elem %u: got 0x%08lx, expected 0x%08lx\n",
                   what, i, (unsigned long)got, (unsigned long)expected);
        errors++;
    }
}

static uint32_t pattern(uint32_t i)
{
    return (i * 0x9E3779B9u) ^ 0x5A5A0F0Fu;
}

/* vle32 / vse32, LMUL=1 (4 elements at VLEN=128) */
static void t_unit32(volatile uint32_t *mem)
{
    uint32_t out[4];

    for (unsigned i = 0; i < 4; i++)
        mem[i] = pattern(i);

    /* load from mem, store to out */
    __asm__ volatile (
        "vsetivli zero, 4, e32, m1, ta, ma\n"
        "vle32.v  v1, (%0)\n"
        "vse32.v  v1, (%1)\n"
        :: "r"(mem), "r"(out) : "memory", "v1");
    for (unsigned i = 0; i < 4; i++)
        check("vle32", i, out[i], pattern(i));

    /* store to mem from out */
    for (unsigned i = 0; i < 4; i++)
        out[i] = pattern(i + 100);
    __asm__ volatile (
        "vsetivli zero, 4, e32, m1, ta, ma\n"
        "vle32.v  v2, (%0)\n"
        "vse32.v  v2, (%1)\n"
        :: "r"(out), "r"(mem + 8) : "memory", "v2");
    for (unsigned i = 0; i < 4; i++)
        check("vse32", i, mem[8 + i], pattern(i + 100));
}

/* vle8 / vse8 with vl=13: byte strobes and a partial last word */
static void t_unit8(volatile uint8_t *mem)
{
    uint8_t src[16], out[16];

    for (unsigned i = 0; i < 16; i++) {
        src[i] = (uint8_t)(0xA0 + i);
        mem[i] = 0x11;
    }
    __asm__ volatile (
        "vsetivli zero, 13, e8, m1, ta, ma\n"
        "vle8.v   v3, (%0)\n"
        "vse8.v   v3, (%1)\n"
        :: "r"(src), "r"(mem) : "memory", "v3");
    for (unsigned i = 0; i < 16; i++)
        check("vse8", i, mem[i], i < 13 ? (uint8_t)(0xA0 + i) : 0x11);

    for (unsigned i = 0; i < 16; i++)
        out[i] = 0;
    __asm__ volatile (
        "vsetivli zero, 13, e8, m1, ta, ma\n"
        "vle8.v   v4, (%0)\n"
        "vse8.v   v4, (%1)\n"
        :: "r"(mem), "r"(out) : "memory", "v4");
    for (unsigned i = 0; i < 13; i++)
        check("vle8", i, out[i], (uint8_t)(0xA0 + i));
}

/* vle32 / vse32 with LMUL=4: 16 elements over four registers */
static void t_lmul4(volatile uint32_t *mem)
{
    uint32_t out[16];

    for (unsigned i = 0; i < 16; i++) {
        mem[i] = pattern(i + 300);
        out[i] = 0;
    }
    __asm__ volatile (
        "vsetivli zero, 16, e32, m4, ta, ma\n"
        "vle32.v  v8, (%0)\n"
        "vse32.v  v8, (%1)\n"
        :: "r"(mem), "r"(out) : "memory", "v8", "v9", "v10", "v11");
    for (unsigned i = 0; i < 16; i++)
        check("vle32 m4", i, out[i], pattern(i + 300));
}

/* Scalar load right before a vector add that accumulates into its own
 * source (v6 += v7): if the add completes while the core is stalled on the
 * load, and is started again afterwards, v6 is added twice. */
static void t_scalar_then_valu(volatile uint32_t *mem)
{
    uint32_t ones[4] = {1, 1, 1, 1}, base[4] = {10, 20, 30, 40}, out[4];
    uint32_t loaded;

    mem[60] = 0xFEEDC0DEu;
    __asm__ volatile (
        "vsetivli zero, 4, e32, m1, ta, ma\n"
        "vle32.v  v6, (%1)\n"
        "vle32.v  v7, (%2)\n"
        "lw       %0, 0(%3)\n"
        "vadd.vv  v6, v6, v7\n"
        "vse32.v  v6, (%4)\n"
        : "=&r"(loaded)
        : "r"(base), "r"(ones), "r"(&mem[60]), "r"(out)
        : "memory", "v6", "v7");
    check("lw before vadd: lw", 0, loaded, 0xFEEDC0DEu);
    for (unsigned i = 0; i < 4; i++)
        check("lw before vadd: v6", i, out[i], base[i] + 1);
}

static uint32_t ram_area[64];

int main(void)
{
    /* enable the vector unit: mstatus.VS = initial */
    __asm__ volatile ("li t0, (1 << 9)\n csrs mstatus, t0" ::: "t0");

    printf("vector-stall-test: VLEN 128\n");

    int e = errors;
    t_unit32(ram_area);                          printf("unit32: %d\n", errors - e);  e = errors;
    t_unit8((volatile uint8_t *)(ram_area + 16)); printf("unit8: %d\n", errors - e);   e = errors;
    t_lmul4(ram_area + 40);                      printf("lmul4: %d\n", errors - e);   e = errors;
    t_scalar_then_valu(ram_area);                printf("lw+vadd: %d\n", errors - e);

    if (errors == 0) printf("Passed.\n\n");
    else             printf("Failed.\n\n");

    return 0;
}
