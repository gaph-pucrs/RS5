.section .init
.align 4

.globl boot
    nop
    nop
    nop

    #######################################
    # UNIT STRIDED LOAD
    #######################################

    vsetvli t0, x0, e8, m1, ta, ma          # SEW=8, LMUL=1, VL=8

    la t1, wordEls
    vle32.v v1, (t1)

    nop
    nop
    nop

    la t2, halfEls
    vle16.v v2, (t2)

    nop
    nop
    nop

    la t3, halfEls
    addi t3, t3, 2
    vle16.v v3, (t3)

    nop
    nop
    nop

    la t4, byteEls
    vle8.v v4, (t4)

    nop
    nop
    nop

    la t5, byteEls
    addi t5, t5, 1
    vle8.v v5, (t5)

    nop
    nop
    nop

    addi t5, t5, 1
    vle8.v v6, (t5)

    nop
    nop
    nop

    addi t5, t5, 1
    vle8.v v7, (t5)

    nop
    nop
    nop
    #######################################
    # UNIT STRIDED LOAD - 2 Regs
    #######################################

    jal ra, clear_vreg_bank

    vsetvli t0, x0, e8, m2, ta, ma          # SEW=8, LMUL=2, VL=8

    la t1, wordEls
    vle32.v v1, (t1)

    nop
    nop
    nop

    la t2, halfEls
    vle16.v v3, (t2)

    nop
    nop
    nop

    la t3, halfEls
    addi t3, t3, 2
    vle16.v v5, (t3)

    nop
    nop
    nop

    la t4, byteEls
    vle8.v v7, (t4)

    nop
    nop
    nop

    la t5, byteEls
    addi t5, t5, 1
    vle8.v v9, (t5)

    nop
    nop
    nop

    addi t5, t5, 1
    vle8.v v11, (t5)

    nop
    nop
    nop

    addi t5, t5, 1
    vle8.v v13, (t5)

    nop
    nop
    nop

    #######################################
    # UNIT STRIDED STORE
    #######################################

    vsetvli t0, x0, e8, m1, ta, ma          # SEW=8, LMUL=1, VL=8

    li t1, 4096         # 0x1000
    vse32.v v1, (t1)

    li t2, 4104         # 0x1008
    vse16.v v3, (t2)

    li t3, 4114         # 0x1012
    vse16.v v4, (t3)

    li t4, 4128         # 0x1020
    vse8.v v7, (t4)

    li t5, 4137         # 0x1029
    vse8.v v7, (t5)

    li t6, 4150         # 0x1036
    vse8.v v7, (t6)

    li a1, 4163         # 0x1043
    vse8.v v7, (a1)

    #######################################
    # UNIT STRIDED STORE - 2 regs
    #######################################

    vsetvli t0, x0, e8, m2, ta, ma          # SEW=8, LMUL=2, VL=8

    li t1, 0x2000
    vse32.v v1, (t1)

    li t2, 0x2010
    vse16.v v3, (t2)

    li t3, 0x2022
    vse16.v v3, (t3)

    li t4, 0x2030
    vse8.v v7, (t4)

    li t5, 0x2041
    vse8.v v7, (t5)

    li t6, 0x2052
    vse8.v v7, (t6)

    li a1, 0x2053
    vse8.v v7, (a1)

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
wordEls: .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
halfEls: .half 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
byteEls: .byte 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
