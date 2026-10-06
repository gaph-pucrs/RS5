/* vector-stall-ops-test: multi-cycle vector operations (multiply, reductions,
 * slides, divide) while the data bus stalls the core (testbench
 * RAM_DELAY_CYCLES > 0).
 *
 * Every case loads its operands with vector loads, then does a scalar load
 * right before the operation, so the operation sits in execute while the core
 * is stalled. Results are checked against scalar C.
 *
 * Prints "Passed." or "Failed." at the end.
 */

#include <stdint.h>
#include <stdio.h>

#define ROUNDS 32

static int errors;

/* A scalar load from RAM: stalls the core while the next instruction (the
 * vector operation under test) is in execute */
static volatile uint32_t stall_word = 0xFEEDC0DEu;

static void check(const char *what, unsigned i, uint32_t got, uint32_t expected)
{
    if (got != expected) {
        if (errors < 12)
            printf("  %s elem %u: got 0x%08lx, expected 0x%08lx\n",
                   what, i, (unsigned long)got, (unsigned long)expected);
        errors++;
    }
}

/* e32, vl=4: v1 = a, v2 = b, v3 = c, scalar operand x, then lw, then insn,
 * then store vector register vres to out */
#define OP32(insn, vres, a, b, c, x, out) do {                     \
    uint32_t loaded;                                               \
    __asm__ volatile (                                             \
        "vsetivli zero, 4, e32, m1, ta, ma\n"                      \
        "vle32.v  v1, (%1)\n"                                      \
        "vle32.v  v2, (%2)\n"                                      \
        "vle32.v  v3, (%3)\n"                                      \
        "lw       %0, 0(%4)\n"                                     \
        insn "\n"                                                  \
        "vse32.v  " vres ", (%5)\n"                                \
        : "=&r"(loaded)                                            \
        : "r"(a), "r"(b), "r"(c), "r"(&stall_word), "r"(out),      \
          "r"(x)                                                   \
        : "memory", "v1", "v2", "v3");                             \
    check("lw", 0, loaded, 0xFEEDC0DEu);                           \
} while (0)

/* Same with e8, vl=4 */
#define OP8(insn, vres, a, b, out) do {                            \
    uint32_t loaded;                                               \
    __asm__ volatile (                                             \
        "vsetivli zero, 4, e8, m1, ta, ma\n"                       \
        "vle8.v   v1, (%1)\n"                                      \
        "vle8.v   v2, (%2)\n"                                      \
        "lw       %0, 0(%3)\n"                                     \
        insn "\n"                                                  \
        "vse8.v   " vres ", (%4)\n"                                \
        : "=&r"(loaded)                                            \
        : "r"(a), "r"(b), "r"(&stall_word), "r"(out)               \
        : "memory", "v1", "v2", "v3");                             \
    check("lw", 0, loaded, 0xFEEDC0DEu);                           \
} while (0)

static int32_t a32[4] = {7, -3, 100000, 0x40000001};
static int32_t b32[4] = {3, -5, -7, 9};
static int32_t c32[4] = {1000, -1000, 123456, -77};

static void t_mul(void)
{
    uint32_t out[4];

    /* vd is also a source: run twice -> multiplied twice */
    OP32("vmul.vv  v1, v1, v2", "v1", a32, b32, c32, 0, out);
    for (unsigned i = 0; i < 4; i++)
        check("vmul", i, out[i], (uint32_t)a32[i] * (uint32_t)b32[i]);

    OP32("vmulh.vv v3, v1, v2", "v3", a32, b32, c32, 0, out);
    for (unsigned i = 0; i < 4; i++)
        check("vmulh", i, out[i], (uint32_t)(((int64_t)a32[i] * b32[i]) >> 32));

    /* vd += vs1 * vs2: run twice -> accumulated twice */
    OP32("vmacc.vv v3, v1, v2", "v3", a32, b32, c32, 0, out);
    for (unsigned i = 0; i < 4; i++)
        check("vmacc", i, out[i], (uint32_t)c32[i] + (uint32_t)a32[i] * (uint32_t)b32[i]);
}

static void t_wmul(void)
{
    static int16_t a16[4] = {300, -2, 32767, -32768};
    static int16_t b16[4] = {-400, 7, 2, -3};
    int32_t out[4];
    uint32_t loaded;

    __asm__ volatile (
        "vsetivli zero, 4, e16, m1, ta, ma\n"
        "vle16.v  v1, (%1)\n"
        "vle16.v  v2, (%2)\n"
        "lw       %0, 0(%3)\n"
        "vwmul.vv v4, v1, v2\n"
        "vsetivli zero, 4, e32, m1, ta, ma\n"
        "vse32.v  v4, (%4)\n"
        : "=&r"(loaded)
        : "r"(a16), "r"(b16), "r"(&stall_word), "r"(out)
        : "memory", "v1", "v2", "v4", "v5");
    check("lw", 0, loaded, 0xFEEDC0DEu);
    for (unsigned i = 0; i < 4; i++)
        check("vwmul", i, (uint32_t)out[i], (uint32_t)((int32_t)a16[i] * b16[i]));
}

static void t_reductions(void)
{
    uint32_t out[4];
    int32_t expected;

    /* vd[0] = vs1[0] + sum(vs2), with vd = vs1: run twice -> summed twice */
    OP32("vredsum.vs v3, v1, v3\n vsetivli zero, 1, e32, m1, ta, ma", "v3", a32, b32, c32, 0, out);
    expected = c32[0];
    for (unsigned i = 0; i < 4; i++)
        expected += a32[i];
    check("vredsum", 0, out[0], (uint32_t)expected);

    OP32("vredmax.vs v3, v2, v3\n vsetivli zero, 1, e32, m1, ta, ma", "v3", a32, b32, c32, 0, out);
    expected = c32[0];
    for (unsigned i = 0; i < 4; i++)
        if (b32[i] > expected)
            expected = b32[i];
    check("vredmax", 0, out[0], (uint32_t)expected);
}

static void t_slides(void)
{
    uint32_t out[4];
    uint32_t x = 0x12345678u;

    OP32("vslide1up.vx   v3, v1, %6", "v3", a32, b32, c32, x, out);
    for (unsigned i = 0; i < 4; i++)
        check("vslide1up", i, out[i], i == 0 ? x : (uint32_t)a32[i - 1]);

    OP32("vslide1down.vx v3, v1, %6", "v3", a32, b32, c32, x, out);
    for (unsigned i = 0; i < 4; i++)
        check("vslide1down", i, out[i], i == 3 ? x : (uint32_t)a32[i + 1]);
}

static void t_div(void)
{
    static int32_t n32[4] = {100, -77, 12345678, -2000000000};
    static int32_t d32[4] = {7, 5, -1000, 3};
    static int8_t  n8[4]  = {100, -77, 120, -128};
    static int8_t  d8[4]  = {7, 5, -10, 3};
    uint32_t out[4];
    int8_t   out8[4];

    /* vdiv.vv vd, vs2, vs1: vd = vs2 / vs1 */
    OP32("vdiv.vv v3, v1, v2", "v3", n32, d32, c32, 0, out);
    for (unsigned i = 0; i < 4; i++)
        check("vdiv e32", i, out[i], (uint32_t)(n32[i] / d32[i]));

    OP32("vrem.vv v3, v1, v2", "v3", n32, d32, c32, 0, out);
    for (unsigned i = 0; i < 4; i++)
        check("vrem e32", i, out[i], (uint32_t)(n32[i] % d32[i]));

    OP8("vdiv.vv v3, v1, v2", "v3", n8, d8, out8);
    for (unsigned i = 0; i < 4; i++)
        check("vdiv e8", i, (uint8_t)out8[i], (uint8_t)(n8[i] / d8[i]));

    OP8("vrem.vv v3, v1, v2", "v3", n8, d8, out8);
    for (unsigned i = 0; i < 4; i++)
        check("vrem e8", i, (uint8_t)out8[i], (uint8_t)(n8[i] % d8[i]));
}

int main(void)
{
    /* enable the vector unit: mstatus.VS = initial */
    __asm__ volatile ("li t0, (1 << 9)\n csrs mstatus, t0" ::: "t0");

    printf("vector-stall-ops-test: %d rounds\n", ROUNDS);

    /* Several rounds: with injected stalls (testbench STALL_INJECT), each
     * round lands the stalls on different cycles of each operation */
    int e_mul = 0, e_wmul = 0, e_red = 0, e_slide = 0, e_div = 0;
    for (int round = 0; round < ROUNDS; round++) {
        int e = errors;
        t_mul();        e_mul   += errors - e; e = errors;
        t_wmul();       e_wmul  += errors - e; e = errors;
        t_reductions(); e_red   += errors - e; e = errors;
        t_slides();     e_slide += errors - e; e = errors;
        t_div();        e_div   += errors - e;
    }
    printf("mul: %d\n", e_mul);
    printf("wmul: %d\n", e_wmul);
    printf("reductions: %d\n", e_red);
    printf("slides: %d\n", e_slide);
    printf("div: %d\n", e_div);

    if (errors == 0) printf("Passed.\n\n");
    else             printf("Failed.\n\n");

    return 0;
}
