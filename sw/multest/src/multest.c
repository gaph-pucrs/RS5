// Directed/random test of the M-extension multiply instructions (mul, mulh, mulhsu, mulhu).
// Reference = 32x32->64 shift-and-add in plain C (no hardware multiply involved).
// Output via the testbench integer port 0x80002000 (printed "%d\n"):
//   for each op: <op id> <errors> ; then the first mismatches as <op> <a> <b> <got> <exp>.
#include <stdint.h>
#define OUT(v) (*(volatile int32_t *)0x80002000 = (int32_t)(v))

static uint64_t __attribute__((noinline)) umul64(uint32_t a, uint32_t b) {
    uint64_t acc = 0, aa = a;
    for (int i = 0; i < 32; i++) { if ((b >> i) & 1u) acc += aa << i; }
    return acc;
}
static uint32_t ref(int op, uint32_t a, uint32_t b) {
    int an = (op == 1 || op == 2) && (a >> 31);           // mulh, mulhsu: a signed
    int bn = (op == 1) && (b >> 31);                        // mulh: b signed
    uint32_t ma = an ? (uint32_t)(-(int64_t)(int32_t)a) : a;
    uint32_t mb = bn ? (uint32_t)(-(int64_t)(int32_t)b) : b;
    uint64_t p = umul64(ma, mb);
    if (an ^ bn) p = ~p + 1u;
    return op == 0 ? (uint32_t)p : (uint32_t)(p >> 32);
}
static uint32_t hw(int op, uint32_t a, uint32_t b) {
    uint32_t r;
    switch (op) {
    case 0:  __asm__ volatile("mul    %0,%1,%2" : "=r"(r) : "r"(a), "r"(b)); break;
    case 1:  __asm__ volatile("mulh   %0,%1,%2" : "=r"(r) : "r"(a), "r"(b)); break;
    case 2:  __asm__ volatile("mulhsu %0,%1,%2" : "=r"(r) : "r"(a), "r"(b)); break;
    default: __asm__ volatile("mulhu  %0,%1,%2" : "=r"(r) : "r"(a), "r"(b)); break;
    }
    return r;
}
static uint32_t lfsr = 0xACE1u;
static uint32_t rnd(void) { // xorshift32
    lfsr ^= lfsr << 13; lfsr ^= lfsr >> 17; lfsr ^= lfsr << 5; return lfsr;
}
#define N_RAND 4000
int main(void) {
    static const uint32_t edge[] = {0, 1, 2, 3329, 0x7fff, 0x8000, 0xffff, 0x10000, 0x7fffffff,
                                    0x80000000, 0xffffffff, 0xfffffffe, 1290167, 3329u << 10, 3328u << 10};
    const int ne = sizeof(edge) / sizeof(edge[0]);
    int shown = 0;
    for (int op = 0; op < 4; op++) {
        int err = 0;
        for (int i = 0; i < ne * ne + N_RAND; i++) {
            uint32_t a, b;
            if (i < ne * ne) { a = edge[i / ne]; b = edge[i % ne]; }
            else { a = rnd(); b = rnd(); if (i & 1) { a &= 0x3fffff; b &= 0x1fffff; } }
            uint32_t g = hw(op, a, b), e = ref(op, a, b);
            if (g != e) { err++; if (shown < 12) { shown++; OUT(100 + op); OUT(a); OUT(b); OUT(g); OUT(e); } }
        }
        OUT(op); OUT(err);
    }
    OUT(-1);
    return 0;
}
