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

    li t0, 8

    la t1, wordEls
    vlse32.v v1, (t1), t0

    nop
    nop
    nop

    li t0, 4

    la t2, halfEls
    vlse16.v v2, (t2), t0

    nop
    nop
    nop

    la t3, halfEls
    addi t3, t3, 2
    vlse16.v v3, (t3), t0

    nop
    nop
    nop

    li t0, 2

    la t4, byteEls
    vlse8.v v4, (t4), t0

    nop
    nop
    nop

    la t5, byteEls
    addi t5, t5, 1
    vlse8.v v5, (t5), t0

    nop
    nop
    nop

    addi t5, t5, 1
    vlse8.v v6, (t5), t0

    nop
    nop
    nop

    addi t5, t5, 1
    vlse8.v v7, (t5), t0

    nop
    nop
    nop
    #######################################
    # UNIT STRIDED LOAD - 2 Regs
    #######################################

    jal ra, clear_vreg_bank

    vsetvli t0, x0, e8, m2, ta, ma          # SEW=8, LMUL=2, VL=8

    li t0, 8

    la t1, wordEls
    vlse32.v v1, (t1), t0

    nop
    nop
    nop

    li t0, 4

    la t2, halfEls
    vlse16.v v3, (t2), t0

    nop
    nop
    nop

    la t3, halfEls
    addi t3, t3, 2
    vlse16.v v5, (t3), t0

    nop
    nop
    nop

    li t0, 2

    la t4, byteEls
    vlse8.v v7, (t4), t0

    nop
    nop
    nop

    la t5, byteEls
    addi t5, t5, 1
    vlse8.v v9, (t5), t0

    nop
    nop
    nop

    addi t5, t5, 1
    vlse8.v v11, (t5), t0

    nop
    nop
    nop

    addi t5, t5, 1
    vlse8.v v13, (t5), t0

    nop
    nop
    nop

    #######################################
    # UNIT STRIDED STORE
    #######################################

    vsetvli t0, x0, e8, m1, ta, ma          # SEW=8, LMUL=1, VL=8

    li t0, 8

    li t1, 4096         # 0x1000
    vsse32.v v1, (t1), t0

    li t0, 4

    li t2, 4104         # 0x1008
    vsse16.v v3, (t2), t0

    li t3, 4114         # 0x1012
    vsse16.v v4, (t3), t0

    li t0, 2

    li t4, 4128         # 0x1020
    vsse8.v v7, (t4), t0

    li t5, 4137         # 0x1029
    vsse8.v v7, (t5), t0

    li t6, 4150         # 0x1036
    vsse8.v v7, (t6), t0

    li a1, 4163         # 0x1043
    vsse8.v v7, (a1), t0

    #######################################
    # UNIT STRIDED STORE - 2 regs
    #######################################

    vsetvli t0, x0, e8, m2, ta, ma          # SEW=8, LMUL=2, VL=8

    li t0, 8

    li t1, 0x2000
    vsse32.v v1, (t1), t0

    li t0, 4

    li t2, 0x2010
    vsse16.v v3, (t2), t0

    li t3, 0x2022
    vsse16.v v3, (t3), t0

    li t0, 2

    li t4, 0x2030
    vsse8.v v7, (t4), t0

    li t5, 0x2041
    vsse8.v v7, (t5), t0

    li t6, 0x2052
    vsse8.v v7, (t6), t0

    li a1, 0x2053
    vsse8.v v7, (a1), t0

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
