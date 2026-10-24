.text

.macro save_regs
  sw s0,  0*4(sp)
  sw s1,  1*4(sp)
  sw s2,  2*4(sp)
  sw s3,  3*4(sp)
  sw s4,  4*4(sp)
  sw s5,  5*4(sp)
  sw s6,  6*4(sp)
  sw s7,  7*4(sp)
  sw s8,  8*4(sp)
  sw s9,  9*4(sp)
  sw s10, 10*4(sp)
  sw s11, 11*4(sp)
  sw gp,  12*4(sp)
  sw tp,  13*4(sp)
  sw ra,  14*4(sp)
.endm

.macro restore_regs
  lw s0,  0*4(sp)
  lw s1,  1*4(sp)
  lw s2,  2*4(sp)
  lw s3,  3*4(sp)
  lw s4,  4*4(sp)
  lw s5,  5*4(sp)
  lw s6,  6*4(sp)
  lw s7,  7*4(sp)
  lw s8,  8*4(sp)
  lw s9,  9*4(sp)
  lw s10, 10*4(sp)
  lw s11, 11*4(sp)
  lw gp,  12*4(sp)
  lw tp,  13*4(sp)
  lw ra,  14*4(sp)
.endm

.macro load_coeffs len, poly
    lw t0, \len*4*0(\poly)
    lw t1, \len*4*1(\poly)
    lw t2, \len*4*2(\poly)
    lw t3, \len*4*3(\poly)
    lw t4, \len*4*4(\poly)
    lw t5, \len*4*5(\poly)
    lw t6, \len*4*6(\poly)
    lw tp, \len*4*7(\poly)
.endm

.macro store_coeffs len, poly
    sw t0, \len*4*0(\poly)
    sw t1, \len*4*1(\poly)
    sw t2, \len*4*2(\poly)
    sw t3, \len*4*3(\poly)
    sw t4, \len*4*4(\poly)
    sw t5, \len*4*5(\poly)
    sw t6, \len*4*6(\poly)
    sw tp, \len*4*7(\poly)
.endm

.macro load_6_zetas_zetasqinv
    lw s0, 0*4(a1);     lw s1, 1*4(a1)
    lw s2, 2*4(a1);     lw s3, 3*4(a1)
    lw s4, 4*4(a1);     lw s5, 5*4(a1)
    lw s6, 6*4(a1);     lw s7, 7*4(a1)
    lw s8, 8*4(a1);     lw s9, 9*4(a1)
    lw s10, 10*4(a1);   lw s11, 11*4(a1)
.endm

.macro load_zetas_zetasqinv
    lw s0, 0*4(a1);     lw s1, 1*4(a1)
    lw s2, 2*4(a1);     lw s3, 3*4(a1)
    lw s4, 4*4(a1);     lw s5, 5*4(a1)
    lw s6, 6*4(a1);     lw s7, 7*4(a1)
    lw s8, 8*4(a1);     lw s9, 9*4(a1)
    lw s10, 10*4(a1);   lw s11, 11*4(a1)
    lw gp,  12*4(a1);   lw ra,  13*4(a1)
.endm

# in: a, b
# out: a*b*(2^{-32}) mod q
# int64_t c=a*b
# int32_t t=c*qinv
# r=((int64_t)c-(int64_t)t*q)>>32=a*b*(2^{-32}) mod q
.macro montmul_ref r, a, b, q, qinv, t
    # cl <- low(a*b)
    mul \r, \a, \b
    # clqinv <- low(cl*qinv)
    mul \r, \r, \qinv
    # tq <- high(clqinv*q)
    mulh \r, \r, \q
    # ch <- high(a*b)
    mulh \t, \a, \b
    # r <- ch - tq
    sub \r, \t, \r
.endm

# in: a, b, bqinv <- low(b*qinv)
# out: a*b*(2^{-32}) mod q
.macro montmul r, a, b, bqinv, q, t
    mul  \r, \a, \bqinv
    mulh \t, \a, \b
    mulh \r, \r, \q
    sub  \r, \t, \r
.endm

.macro montmul_inplace a, b, bqinv, q, t
    mul  \t, \a, \bqinv
    mulh \a, \a, \b
    mulh \t, \t, \q
    sub  \a, \a, \t
.endm

.macro montmul_inplace_x2 \
    a_0, a_1, \
    zeta, zetaqinv, q, \
    t_0, t_1
    mul  \t_0, \a_0, \zetaqinv
    mul  \t_1, \a_1, \zetaqinv
    mulh \a_0, \a_0, \zeta
    mulh \a_1, \a_1, \zeta
    mulh \t_0, \t_0, \q
    mulh \t_1, \t_1, \q
    sub  \a_0, \a_0, \t_0
    sub  \a_1, \a_1, \t_1
.endm

.macro montmul_inplace_x4 \
        a_0, a_1, a_2, a_3, \
        zeta, zetaqinv, \
        q, t_0, t_1, t_2
    mul  \t_0, \a_0, \zetaqinv
    mul  \t_1, \a_1, \zetaqinv
    mul  \t_2, \a_2, \zetaqinv
    mul  \zetaqinv, \a_3, \zetaqinv
    mulh \a_0, \a_0, \zeta
    mulh \a_1, \a_1, \zeta
    mulh \a_2, \a_2, \zeta
    mulh \a_3, \a_3, \zeta
    mulh \t_0, \t_0, \q
    mulh \t_1, \t_1, \q
    mulh \t_2, \t_2, \q
    mulh \zetaqinv, \zetaqinv, \q
    sub  \a_0, \a_0, \t_0
    sub  \a_1, \a_1, \t_1
    sub  \a_2, \a_2, \t_2
    sub  \a_3, \a_3, \zetaqinv
.endm

.macro montrdc r, ch, cl, q, qinv
    mul  \r, \cl, \qinv
    mulh \r, \r, \q
    sub  \r, \ch, \r
.endm

.macro montrdc_x4 \
    r_0, r_1, r_2, r_3, \
    ch_0, cl_0, ch_1, cl_1, \
    ch_2, cl_2, ch_3, cl_3, \
    q, qinv
    mul  \r_0, \cl_0, \qinv
    mul  \r_1, \cl_1, \qinv
    mul  \r_2, \cl_2, \qinv
    mul  \r_3, \cl_3, \qinv
    mulh \r_0, \r_0, \q
    mulh \r_1, \r_1, \q
    mulh \r_2, \r_2, \q
    mulh \r_3, \r_3, \q
    sub  \r_0, \ch_0, \r_0
    sub  \r_1, \ch_1, \r_1
    sub  \r_2, \ch_2, \r_2
    sub  \r_3, \ch_3, \r_3
.endm

# .macro ct_bfu in0, in1, zeta, zetaqinv, q, tmp0, tmp1
#     montmul \tmp0, \in1, \zeta, \zetaqinv, \q, \tmp1
#     sub \in1, \in0, \tmp0
#     add \in0, \in0, \tmp0
# .endm

.macro ct_bfu a_0_0, a_0_1, zeta_0, zetaqinv_0, q, t_0_0, t_0_1
    mul  \t_0_0, \a_0_1, \zetaqinv_0
    mulh \t_0_1, \a_0_1, \zeta_0
    mulh \t_0_0, \t_0_0, \q
    sub  \t_0_0, \t_0_1, \t_0_0
    sub  \a_0_1, \a_0_0, \t_0_0
    add  \a_0_0, \a_0_0, \t_0_0
.endm

.macro ct_bfu_x2 \
    a_0_0, a_0_1, a_1_0, a_1_1, \
    zeta_0, zetaqinv_0, \
    zeta_1, zetaqinv_1, \
    q, \
    t_0_0, t_0_1, t_1_0, t_1_1
    mul  \t_0_0, \a_0_1, \zetaqinv_0
    mul  \t_1_0, \a_1_1, \zetaqinv_1
    mulh \t_0_1, \a_0_1, \zeta_0
    mulh \t_1_1, \a_1_1, \zeta_1
    mulh \t_0_0, \t_0_0, \q
    mulh \t_1_0, \t_1_0, \q
    sub  \t_0_0, \t_0_1, \t_0_0
    sub  \t_1_0, \t_1_1, \t_1_0
    sub  \a_0_1, \a_0_0, \t_0_0
    sub  \a_1_1, \a_1_0, \t_1_0
    add  \a_0_0, \a_0_0, \t_0_0
    add  \a_1_0, \a_1_0, \t_1_0
.endm

.macro ct_bfu_x4 \
        a_0_0, a_0_1, a_1_0, a_1_1, \
        a_2_0, a_2_1, a_3_0, a_3_1, \
        zeta0, zetaqinv0, zeta1, zetaqinv1, \
        zeta2, zetaqinv2, zeta3, zetaqinv3, \
        q, \
        t_0_0, t_0_1, t_1_0, t_1_1, \
        t_2_0, t_3_0
    mul  \t_0_0, \a_0_1, \zetaqinv0
    mul  \t_1_0, \a_1_1, \zetaqinv1
    mul  \t_2_0, \a_2_1, \zetaqinv2
    mul  \t_3_0, \a_3_1, \zetaqinv3
    mulh \t_0_1, \a_0_1, \zeta0
    mulh \t_0_0, \t_0_0, \q
    mulh \t_1_0, \t_1_0, \q
    mulh \t_2_0, \t_2_0, \q
    mulh \t_3_0, \t_3_0, \q
    sub  \t_0_0, \t_0_1, \t_0_0
    mulh \t_0_1, \a_1_1, \zeta1
    sub  \a_0_1, \a_0_0, \t_0_0
    add  \a_0_0, \a_0_0, \t_0_0
    mulh \t_1_1, \a_2_1, \zeta2
    sub  \t_1_0, \t_0_1, \t_1_0
    sub  \a_1_1, \a_1_0, \t_1_0
    add  \a_1_0, \a_1_0, \t_1_0
    mulh \t_0_1, \a_3_1, \zeta3
    sub  \t_2_0, \t_1_1, \t_2_0
    sub  \a_2_1, \a_2_0, \t_2_0
    add  \a_2_0, \a_2_0, \t_2_0
    sub  \t_3_0, \t_0_1, \t_3_0
    sub  \a_3_1, \a_3_0, \t_3_0
    add  \a_3_0, \a_3_0, \t_3_0
.endm

# .macro gs_bfu in0, in1, zeta, zetaqinv, q, tmp0, tmp1
#     sub \tmp0, \in0, \in1
#     add \in0, \in0, \in1
#     montmul \in1, \tmp0, \zeta, \zetaqinv, \q, \tmp1
# .endm

.macro gs_bfu a_0_0, a_0_1, zeta_0, zetaqinv_0, q, t_0_0, t_0_1
    sub  \t_0_0, \a_0_0, \a_0_1
    add  \a_0_0, \a_0_0, \a_0_1
    mul  \a_0_1, \t_0_0, \zetaqinv_0
    mulh \t_0_1, \t_0_0, \zeta_0
    mulh \a_0_1, \a_0_1, \q
    sub  \a_0_1, \t_0_1, \a_0_1
.endm

.macro gs_bfu_x2 \
    a_0_0, a_0_1, a_1_0, a_1_1, \
    zeta_0, zetaqinv_0, \
    zeta_1, zetaqinv_1, \
    q, \
    t_0_0, t_0_1, t_1_0, t_1_1
    sub  \t_0_0, \a_0_0, \a_0_1
    sub  \t_1_0, \a_1_0, \a_1_1
    add  \a_0_0, \a_0_0, \a_0_1
    add  \a_1_0, \a_1_0, \a_1_1
    mul  \a_0_1, \t_0_0, \zetaqinv_0
    mul  \a_1_1, \t_1_0, \zetaqinv_1
    mulh \t_0_1, \t_0_0, \zeta_0
    mulh \t_1_1, \t_1_0, \zeta_1
    mulh \a_0_1, \a_0_1, \q
    mulh \a_1_1, \a_1_1, \q
    sub  \a_0_1, \t_0_1, \a_0_1
    sub  \a_1_1, \t_1_1, \a_1_1
.endm

.macro gs_bfu_x4 \
        a_0_0, a_0_1, a_1_0, a_1_1, \
        a_2_0, a_2_1, a_3_0, a_3_1, \
        zeta0, zetaqinv0, zeta1, zetaqinv1, \
        zeta2, zetaqinv2, zeta3, zetaqinv3, \
        q, \
        t_0_0, t_1_0, t_2_0, t_3_0
    sub  \t_0_0, \a_0_0, \a_0_1
    sub  \t_1_0, \a_1_0, \a_1_1
    sub  \t_2_0, \a_2_0, \a_2_1
    add  \a_0_0, \a_0_0, \a_0_1
    add  \a_1_0, \a_1_0, \a_1_1
    sub  \t_3_0, \a_3_0, \a_3_1
    add  \a_2_0, \a_2_0, \a_2_1
    add  \a_3_0, \a_3_0, \a_3_1
    mul  \a_0_1, \t_0_0, \zetaqinv0
    mul  \a_1_1, \t_1_0, \zetaqinv1
    mul  \a_2_1, \t_2_0, \zetaqinv2
    mul  \a_3_1, \t_3_0, \zetaqinv3
    mulh \t_0_0, \t_0_0, \zeta0
    mulh \t_1_0, \t_1_0, \zeta1
    mulh \t_2_0, \t_2_0, \zeta2
    mulh \t_3_0, \t_3_0, \zeta3
    mulh \a_0_1, \a_0_1, \q
    mulh \a_1_1, \a_1_1, \q
    mulh \a_2_1, \a_2_1, \q
    mulh \a_3_1, \a_3_1, \q
    sub  \a_0_1, \t_0_0, \a_0_1
    sub  \a_1_1, \t_1_0, \a_1_1
    sub  \a_2_1, \t_2_0, \a_2_1
    sub  \a_3_1, \t_3_0, \a_3_1
.endm

.macro mul64 hi, lo, in1, in2
    mul  \lo, \in1, \in2
    mulh \hi, \in1, \in2
.endm

.macro add64 oh, ol, ih, il
    add  \ol, \ol, \il
    sltu \il, \ol, \il
    add  \oh, \oh, \ih
    add  \oh, \oh, \il
.endm

.macro lw64 oh, ol, off, poly
    lw \ol, \off(\poly)
    lw \oh, \off+4(\poly)
.endm

.macro sw64 ih, il, off, poly
    sw \il, \off(\poly)
    sw \ih, \off+4(\poly)
.endm

# q * qinv = 1 mod 2^32, used for Montgomery arithmetic
.equ q, 8380417
.equ qinv, 58728449
# inv256 = 2^64 * (1/256) mod q is used for reverting standard domain
.equ inv256, 41978
# inv256qinv <- low(inv256*qinv)
.equ inv256qinv, 4286571514

# void ntt_rv32im(int32_t in[256], const int32_t zetas[256*2]);
# register usage:
# a0-a1: in/out, zetas; a6: q; a1/a2/a3/a4/a5/a7: tmp
# 4*15(sp), 4*16(sp) for outer/inner loop control
# 4*17(sp) for saving a1
# t0-t6,tp: 8 coeffs; s0-s11, gp, ra: 7 zetas & zetas*qinv
# strategy: 3+3+2 layers merging
.globl ntt_rv32im
.align 2
ntt_rv32im:
    addi sp, sp, -4*18
    save_regs
    li a6, q
    load_zetas_zetasqinv
    sw   a1, 4*17(sp)
    # loop control, a0+32*4=a[32], 32: loop numbers, 4: wordLen
    addi a4, a0, 32*4
    sw   a4, 4*15(sp)
# 123 layers merging
ntt_rv32im_looper_123:
    load_coeffs 32, a0
    ct_bfu_x4   \
        t0, t4, t1, t5, t2, t6, t3, tp, \
        s0, s1, s0, s1, s0, s1, s0, s1, \
        a6, a1, a2, a3, a4, a5, a7
    ct_bfu_x4   \
        t0, t2, t1, t3, t4, t6, t5, tp, \
        s2, s3, s2, s3, s4, s5, s4, s5, \
        a6, a1, a2, a3, a4, a5, a7
    ct_bfu_x4   \
        t0, t1, t2, t3, t4, t5, t6, tp, \
        s6, s7, s8, s9, s10,s11,gp, ra, \
        a6, a1, a2, a3, a4, a5, a7
    store_coeffs 32, a0
    lw  a4, 4*15(sp)
    addi a0, a0, 4
    bne a4, a0, ntt_rv32im_looper_123
    lw   a1, 4*17(sp)
# reset a0 & update a1
addi a0, a0, -32*4
addi a1, a1, 4*7*2
# 456 layers merging
addi a5, a1, 8*4*7*2
sw   a1, 4*17(sp)
sw   a5, 4*15(sp)
ntt_rv32im_outer_456:
    load_zetas_zetasqinv
    addi a4, a0, 4*4
    sw   a4, 4*16(sp)
    ntt_rv32im_inner_456:
        load_coeffs 4, a0
        ct_bfu_x4   \
            t0, t4, t1, t5, t2, t6, t3, tp, \
            s0, s1, s0, s1, s0, s1, s0, s1, \
            a6, a1, a2, a3, a4, a5, a7
        ct_bfu_x4   \
            t0, t2, t1, t3, t4, t6, t5, tp, \
            s2, s3, s2, s3, s4, s5, s4, s5, \
            a6, a1, a2, a3, a4, a5, a7
        ct_bfu_x4   \
            t0, t1, t2, t3, t4, t5, t6, tp, \
            s6, s7, s8, s9, s10,s11,gp, ra, \
            a6, a1, a2, a3, a4, a5, a7
        store_coeffs 4, a0
        lw  a4, 4*16(sp)
        addi a0, a0, 4
        bne a4, a0, ntt_rv32im_inner_456
    addi a0, a0, 32*4-4*4
    lw   a1, 4*17(sp)
    lw   a5, 4*15(sp)
    addi a1, a1, 4*7*2
    sw   a1, 4*17(sp)
    bne  a5, a1, ntt_rv32im_outer_456
    # reset a0
    addi a0, a0, -8*32*4
    # 78 layers merging
    addi a4, a0, 32*8*4
    sw   a4, 4*15(sp)
ntt_rv32im_looper_78:
    load_coeffs 1, a0
    load_6_zetas_zetasqinv
    ct_bfu_x4 \
        t0, t2, t1, t3, t4, t6, t5, tp, \
        s0, s1, s0, s1, s6, s7, s6, s7, \
        a6, a1, a2, a3, a4, a5, a7
    ct_bfu_x4 \
        t0, t1, t2, t3, t4, t5, t6, tp, \
        s2, s3, s4, s5, s8, s9, s10,s11,\
        a6, a1, a2, a3, a4, a5, a7
    store_coeffs 1, a0
    addi a0, a0, 8*4
    lw   a1, 4*17(sp)
    addi a1, a1, 4*3*2*2
    lw   a4, 4*15(sp)
    sw   a1, 4*17(sp)
    bne a4, a0, ntt_rv32im_looper_78
    restore_regs
    addi sp, sp, 4*18
    ret

# void intt_rv32im(int32_t in[256], const int32_t zetas[256*2]);
# register usage: 
# a0-a1: in/out, zetas; a6: q; a4: looper control; a2/a3/a5/a7: tmp
# 4*15(sp) for loop control
# t0-t6,tp: 8 coeffs; s0-s11, gp, ra: 7 zetas & zetas*qinv
# strategy: 2+3+3 layers merging
.globl intt_rv32im
.align 2
intt_rv32im:
    addi sp, sp, -4*16
    save_regs
li a6, q
# 12 layers merging
addi a4, a0, 32*8*4
intt_rv32im_looper_12:
    load_coeffs 1, a0
    load_6_zetas_zetasqinv
    gs_bfu_x4 \
        t0, t1, t2, t3, t4, t5, t6, tp, \
        s0, s1, s2, s3, s6, s7, s8, s9, \
        a6, a2, a3, a5, a7
    gs_bfu_x4 \
        t0, t2, t1, t3, t4, t6, t5, tp, \
        s4, s5, s4, s5, s10,s11, s10,s11,\
        a6, a2, a3, a5, a7
    store_coeffs 1, a0
    addi a0, a0, 8*4
    addi a1, a1, 4*3*2*2
    bne a4, a0, intt_rv32im_looper_12
    # reset a0
    addi a0, a0, -32*8*4
    # 345 layers merging
    addi a5, a1, 8*4*7*2
    sw   a5, 4*15(sp)
intt_rv32im_outer_345:
    load_zetas_zetasqinv
    addi a4, a0, 4*4
    intt_rv32im_inner_345:
        load_coeffs 4, a0
        gs_bfu_x4 \
            t0, t1, t2, t3, t4, t5, t6, tp, \
            s0, s1, s2, s3, s4, s5, s6, s7, \
            a6, a2, a3, a5, a7
        gs_bfu_x4 \
            t0, t2, t1, t3, t4, t6, t5, tp, \
            s8, s9, s8, s9, s10,s11, s10,s11, \
            a6, a2, a3, a5, a7
        gs_bfu_x4 \
            t0, t4, t1, t5, t2, t6, t3, tp, \
            gp, ra, gp, ra, gp, ra, gp, ra, \
            a6, a2, a3, a5, a7
        store_coeffs 4, a0
        addi a0, a0, 4
        bne a4, a0, intt_rv32im_inner_345
    lw   a5, 4*15(sp)
    addi a0, a0, 32*4-4*4
    addi a1, a1, 4*7*2
    bne a5, a1, intt_rv32im_outer_345
    # reset a0
    addi a0, a0, -8*32*4
    # 678 layers merging
    addi a4, a0, 32*4
    load_zetas_zetasqinv
intt_rv32im_looper_678:
    load_coeffs 32, a0
    gs_bfu_x4 \
        t0, t1, t2, t3, t4, t5, t6, tp, \
        s0, s1, s2, s3, s4, s5, s6, s7, \
        a6, a2, a3, a5, a7
    gs_bfu_x4 \
        t0, t2, t1, t3, t4, t6, t5, tp, \
        s8, s9, s8, s9, s10,s11, s10,s11, \
        a6, a2, a3, a5, a7
    gs_bfu_x4 \
        t0, t4, t1, t5, t2, t6, t3, tp, \
        gp, ra, gp, ra, gp, ra, gp, ra, \
        a6, a2, a3, a5, a7
    sw   a4, 4*15(sp)
    # revert to standard domain
    li a7, inv256
    li a5, inv256qinv
    montmul_inplace_x4 \
        t0, t1, t2, t3, \
        a7, a5, a6, a2, a3, a4
    store_coeffs 32, a0
    lw   a4, 4*15(sp)
    addi a0, a0, 4
    bne a4, a0, intt_rv32im_looper_678
    restore_regs
    addi sp, sp, 4*16
    ret

# void poly_basemul_8l_init_rv32im(int64_t r[256], const int32_t a[256], const int32_t b[256])
.globl poly_basemul_8l_init_rv32im
.align 2
poly_basemul_8l_init_rv32im:
    addi sp, sp, -4*15
    save_regs
    # loop control
    li gp, 32*8*8
    add gp, gp, a0
poly_basemul_8l_init_rv32im_looper:
    lw t0, 0*4(a1) # a0
    lw s0, 0*4(a2) # b0
    lw t1, 1*4(a1) # a1
    lw s1, 1*4(a2) # b1
    mul64 s9, s8, t0, s0
    lw t2, 2*4(a1) # a2
    lw s2, 2*4(a2) # b2
    mul64 s11,s10,t1, s1
    sw64 s9, s8, 0*8, a0
    lw t3, 3*4(a1) # a3
    lw s3, 3*4(a2) # b3
    mul64 a4, a3, t2, s2
    sw64 s11,s10,1*8, a0
    mul64 a6, a5, t3, s3
    sw64 a4, a3, 2*8, a0
    lw t4, 4*4(a1) # a4
    lw s4, 4*4(a2) # b4
    sw64 a6, a5, 3*8, a0
    mul64 s9, s8, t4, s4
    lw t5, 5*4(a1) # a5
    lw s5, 5*4(a2) # b5
    sw64 s9, s8, 4*8, a0
    mul64 s11,s10,t5, s5
    lw t6, 6*4(a1) # a6
    lw s6, 6*4(a2) # b6
    sw64 s11,s10,5*8, a0
    mul64 a4, a3, t6, s6
    lw tp, 7*4(a1) # a7
    lw s7, 7*4(a2) # b7
    sw64 a4, a3, 6*8, a0
    mul64 a6, a5, tp, s7
    sw64 a6, a5, 7*8, a0
    # loop control
    addi a0, a0, 8*8
    addi a1, a1, 4*8
    addi a2, a2, 4*8
    bne gp, a0, poly_basemul_8l_init_rv32im_looper
    restore_regs
    addi sp, sp, 4*15
    ret

# void poly_basemul_8l_acc_rv32im(int64_t r[256], const int32_t a[256], const int32_t b[256])
.globl poly_basemul_8l_acc_rv32im
.align 2
poly_basemul_8l_acc_rv32im:
    addi sp, sp, -4*15
    save_regs
    # loop control
    li gp, 32*8*8
    add gp, gp, a0
poly_basemul_8l_acc_rv32im_looper:
    lw t0, 0*4(a1) # a0
    lw s0, 0*4(a2) # b0
    lw64  s11,s10,0*8, a0
    mul64 s9, s8, t0, s0
    lw t1, 1*4(a1) # a1
    lw s1, 1*4(a2) # b1
    add64 s11,s10,s9,s8
    sw64  s11,s10,0*8, a0
    lw64  a6, a5, 1*8, a0
    mul64 a4, a3,t1, s1
    lw t2, 2*4(a1) # a2
    lw s2, 2*4(a2) # b2
    add64 a6, a5, a4, a3
    sw64  a6, a5, 1*8, a0
    lw64  s11,s10,2*8, a0
    mul64 s9, s8, t2, s2
    lw t3, 3*4(a1) # a3
    lw s3, 3*4(a2) # b3
    add64 s11,s10,s9,s8
    sw64  s11,s10,2*8, a0
    lw64  a6, a5, 3*8, a0
    mul64 a4, a3, t3, s3
    lw t4, 4*4(a1) # a4
    lw s4, 4*4(a2) # b4
    add64 a6, a5, a4, a3
    sw64  a6, a5, 3*8, a0
    lw64  s11,s10,4*8, a0
    mul64 s9, s8, t4, s4
    lw t5, 5*4(a1) # a5
    lw s5, 5*4(a2) # b5
    add64 s11,s10,s9,s8
    sw64  s11,s10,4*8, a0
    lw64  a6, a5, 5*8, a0
    mul64 a4, a3, t5, s5
    lw t6, 6*4(a1) # a6
    lw s6, 6*4(a2) # b6
    add64 a6, a5, a4, a3
    sw64  a6, a5, 5*8, a0
    lw64  s11,s10,6*8, a0
    mul64 s9, s8, t6, s6
    lw tp, 7*4(a1) # a7
    lw s7, 7*4(a2) # b7
    add64 s11,s10,s9, s8
    sw64  s11,s10,6*8, a0
    lw64  a6, a5, 7*8, a0
    mul64 a4, a3, tp, s7
    addi a1, a1, 4*8
    addi a2, a2, 4*8
    add64 a6, a5, a4, a3
    sw64  a6, a5, 7*8, a0
    # loop control
    addi a0, a0, 8*8
    bne gp, a0, poly_basemul_8l_acc_rv32im_looper
    restore_regs
    addi sp, sp, 4*15
    ret

# void poly_basemul_8l_acc_end_rv32im(int32_t r[256], const int32_t a[256], const int32_t b[256], int64_t r_double[256])
.globl poly_basemul_8l_acc_end_rv32im
.align 2
poly_basemul_8l_acc_end_rv32im:
    addi sp, sp, -4*16
    save_regs
    li a4, q
    li a5, qinv
    # loop control
    li gp, 64*4*4
    add gp, gp, a0
    sw gp, 4*15(sp)
poly_basemul_8l_acc_end_rv32im_looper:
    # a0-a3
    lw s0, 0*4(a1)
    lw s1, 1*4(a1)
    lw s2, 2*4(a1)
    lw s3, 3*4(a1)
    # b0-b4
    lw t0, 0*4(a2)
    lw t1, 1*4(a2)
    lw t2, 2*4(a2)
    lw t3, 3*4(a2)
    # r_double[0-3]
    lw64 s5, s4, 0*8, a3
    lw64 s7, s6, 1*8, a3
    lw64 s9, s8, 2*8, a3
    lw64 s11,s10,3*8, a3
    # a0b0-a3b3
    mul64 t5, t4, s0, t0
    mul64 a7, a6, s1, t1
    mul64 tp, t6, s2, t2
    mul64 ra, gp, s3, t3
    # accumulate
    add64 s5, s4, t5, t4
    add64 s7, s6, a7, a6
    add64 s9, s8, tp, t6
    add64 s11,s10,ra, gp
    # rdc
    montrdc_x4 \
        s0, s1, s2, s3, \
        s5, s4, s7, s6, \
        s9, s8, s11,s10,\
        a4, a5
    # store results
    sw s0, 0*4(a0)
    sw s1, 1*4(a0)
    sw s2, 2*4(a0)
    sw s3, 3*4(a0)
    # loop control
    addi a0, a0, 4*4
    addi a1, a1, 4*4
    addi a2, a2, 4*4
    addi a3, a3, 8*4
    lw gp, 4*15(sp)
    bne gp, a0, poly_basemul_8l_acc_end_rv32im_looper
    restore_regs
    addi sp, sp, 4*16
    ret

# void poly_basemul_8l_rv32im(int32_t r[256], const int32_t a[256], const int32_t b[256])
.globl poly_basemul_8l_rv32im
.align 2
poly_basemul_8l_rv32im:
    addi sp, sp, -4*15
    save_regs
    li a4, q
    li a5, qinv
    # loop control
    li gp, 64*4*4
    add gp, gp, a0
poly_basemul_8l_rv32im_looper:
    # a0-a3
    lw s0, 0*4(a1)
    lw s1, 1*4(a1)
    lw s2, 2*4(a1)
    lw s3, 3*4(a1)
    # b0-b4
    lw t0, 0*4(a2)
    lw t1, 1*4(a2)
    lw t2, 2*4(a2)
    lw t3, 3*4(a2)
    # a0b0-a3b3
    mul64 s5, s4, s0, t0
    mul64 s7, s6, s1, t1
    mul64 s9, s8, s2, t2
    mul64 s11,s10,s3, t3
    montrdc_x4 \
        t4, t5, a6, a7, \
        s5, s4, s7, s6, \
        s9, s8, s11,s10,\
        a4, a5
    # store results
    sw t4, 0*4(a0)
    sw t5, 1*4(a0)
    sw a6, 2*4(a0)
    sw a7, 3*4(a0)
    # loop control
    addi a0, a0, 4*4
    addi a1, a1, 4*4
    addi a2, a2, 4*4
    bne gp, a0, poly_basemul_8l_rv32im_looper
    restore_regs
    addi sp, sp, 4*15
    ret

# void polyvec_basemul_poly_8l(int32_t *r_vec, const int32_t *a_poly, const int32_t *b_vec, int32_t veclen);
.globl polyvec_basemul_poly_8l_rv32im
.align 2
polyvec_basemul_poly_8l_rv32im:
    addi sp, sp, -4*15
    save_regs
    li a7, q
    li ra, qinv
    # outer loop control
    addi a6, a1, 32*8*4
polyvec_basemul_poly_8l_rv32im_outer_loop:
    lw t0, 0*4(a1) # a0
    lw t1, 1*4(a1) # a1
    lw t2, 2*4(a1) # a2
    lw t3, 3*4(a1) # a3
    lw t4, 4*4(a1) # a4
    lw t5, 5*4(a1) # a5
    lw t6, 6*4(a1) # a6
    lw tp, 7*4(a1) # a7
    # inner loop control
    li gp, 0
    polyvec_basemul_poly_8l_rv32im_inner_loop:
        lw s0, 0*4(a2) # b0
        lw s1, 1*4(a2) # b1
        lw s2, 2*4(a2) # b2
        lw s3, 3*4(a2) # b3
        mul64 s9, s8, t0, s0
        mul64 s11, s10, t1, s1
        montrdc a4, s9, s8, a7, ra
        montrdc a5, s11, s10, a7, ra
        sw    a4, 0*4(a0)
        sw    a5, 1*4(a0)
        mul64 s9, s8, t2, s2
        mul64 s11, s10, t3, s3
        montrdc a4, s9, s8, a7, ra
        montrdc a5, s11, s10, a7, ra
        lw s4, 4*4(a2) # b4
        lw s5, 5*4(a2) # b5
        lw s6, 6*4(a2) # b6
        lw s7, 7*4(a2) # b7
        mul64 s9, s8, t4, s4
        sw    a4, 2*4(a0)
        mul64 s11, s10, t5, s5
        sw    a5, 3*4(a0)
        montrdc a4, s9, s8, a7, ra
        montrdc a5, s11, s10, a7, ra
        sw    a4, 4*4(a0)
        sw    a5, 5*4(a0)
        mul64 s9, s8, t6, s6
        mul64 s11, s10, tp, s7
        montrdc a4, s9, s8, a7, ra
        montrdc a5, s11, s10, a7, ra
        sw    a4, 6*4(a0)
        sw    a5, 7*4(a0)
        # inner loop control & update index
        addi gp, gp, 1
        addi a0, a0, 256*4
        addi a2, a2, 256*4
        bne a3, gp, polyvec_basemul_poly_8l_rv32im_inner_loop
    # reset a0 & a2
    slli a4, a3, 10
    sub a0, a0, a4
    sub a2, a2, a4
    # outer loop control & update index
    addi a0, a0, 8*4
    addi a1, a1, 8*4
    addi a2, a2, 8*4
    bne a6, a1, polyvec_basemul_poly_8l_rv32im_outer_loop
    restore_regs
    addi sp, sp, 4*15
    ret

# void poly_reduce_rv32im(int32_t in[256]);
.globl poly_reduce_rv32im
.align 2
poly_reduce_rv32im:
    li a1, 4194304  # 1<<22
    li a2, q
    addi a3, a0, 64*4*4
poly_reduce_rv32im_loop:
    lw a4, 0*4(a0)
    lw a5, 1*4(a0)
    lw a6, 2*4(a0)
    lw a7, 3*4(a0)
    add  t0, a4, a1
    add  t1, a5, a1
    add  t2, a6, a1
    add  t3, a7, a1
    srai t0, t0, 23
    srai t1, t1, 23
    srai t2, t2, 23
    srai t3, t3, 23
    mul  t0, t0, a2
    mul  t1, t1, a2
    mul  t2, t2, a2
    mul  t3, t3, a2
    sub  a4, a4, t0
    sub  a5, a5, t1
    sub  a6, a6, t2
    sub  a7, a7, t3
    sw a4, 0*4(a0)
    sw a5, 1*4(a0)
    sw a6, 2*4(a0)
    sw a7, 3*4(a0)
    addi a0, a0, 4*4
    bne a3, a0, poly_reduce_rv32im_loop
    ret
