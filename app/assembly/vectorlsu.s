.section .init
.align 4

.globl boot
    nop
    nop
    nop

    #######################################
    # Indexed LOAD
    #######################################

    vsetvli t0, x0, e8, m1, ta, ma          # SEW=8, LMUL=1, VL=8

    la t1, byteoffsets
    vle8.v v1, (t1)

    la t2, byteEls
    vluxei8.v v2, (t2), v1
    nop
    vloxei8.v v3, (t2), v1

    # 2 regs
    vsetvli t0, x0, e8, m2, ta, ma          # SEW=8, LMUL=2, VL=16

    vle8.v v6, (t1)
    nop
    vluxei8.v v8, (t2), v6
    nop
    vloxei8.v v10, (t2), v6


    #######################################
    # Indexed STORES
    #######################################

    jal clear_vreg_bank

    vsetvli t0, x0, e8, m1, ta, ma          # SEW=8, LMUL=1, VL=8

    la t1, byteoffsets
    vle8.v v1, (t1)

    la t2, byteEls
    vle8.v v2, (t2)

    la t3, storeSec
    vsuxei8.v v2, (t3), v1

    la t4, storeSec
    addi t4, t4, 24
    vsuxei8.v v2, (t4), v1

    # 2 regs
    vsetvli t0, x0, e8, m2, ta, ma          # SEW=8, LMUL=2, VL=16

    la t1, byteoffsets
    vle8.v v1, (t1)

    la t2, byteEls
    vle8.v v4, (t2)

    la t3, storeSec
    vsuxei8.v v4, (t3), v1

    la t4, storeSec
    addi t4, t4, 24
    vsuxei8.v v4, (t4), v1








clear_vreg_bank:
    # CLEARS VREG BANK
    vsetvli t0, x0, e32, m8, ta, ma          # SEW= 32, LMUL=8, VL=VLMAX
    vand.vi v0,  v0,  0
    vand.vi v8,  v8,  0
    vand.vi v16, v16, 0
    vand.vi v24, v24, 0
    jr ra


.section .rodata		# Constants
.align 4
wordEls: .word 0x11111111, 0x22222222, 0x33333333, 0x44444444, 0x55555555, 0x66666666, 0x77777777, 0x88888888, 0x99999999, 0x10101010, 0x111111, 0x12121212, 0x13131313, 0x14141414, 0x15151515, 0x16161616
halfEls: .half 0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888, 0x9999, 0x1010, 0x1111, 0x1212, 0x1313, 0x1414, 0x1515, 0x1616
byteEls: .byte 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29

byteoffsets: .byte 2, 4, 8, 16, 8, 2, 1, 9, 3, 7, 5, 12, 0, 8, 17, 25

storeSec: .byte 0x00