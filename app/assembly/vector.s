.section .init
.align 4

.globl boot
    nop
    nop
    nop

    li a0, 8
    vsetvli t0, a0, e8, m1, ta, ma          # SEW= 8, LMUL=1
    nop
    vor.vi v1, v1, 15
    nop
    addi a7, a7, -9
    nop
    vor.vx v2, v2, a7
    nop
    vand.vv v1, v1, v2

    nop
    nop
    nop

    li a0, 16
    vsetvli t0, a0, e8, m2, ta, ma          # SEW= 8, LMUL=2
    nop
    vor.vi v4, v4, 15
    nop
    addi a7, a7, -9
    nop
    vor.vx v6, v6, a7
    nop
    vand.vv v1, v4, v6

    nop
    nop
    nop

    vsetvli t0, x0, e8, m4, ta, ma          # SEW= 8, LMUL=4, VL=32
    nop
    vor.vi v8, v8, 15
    nop
    addi a7, a7, -9
    nop
    vor.vx v12, v12, a7
    nop
    vand.vv v1, v8, v12

    nop
    nop
    nop

    vsetvli t0, x0, e8, m8, ta, ma          # SEW= 8, LMUL=8, VL=64
    nop
    vor.vi v16, v16, 15
    nop
    addi a7, a7, -9
    nop
    vor.vx v24, v24, a7
    nop
    vand.vv v1, v16, v24

    nop
    nop
    nop

    vsetvli t0, x0, e8, m4, ta, ma          # SEW= 8, LMUL=1
    
    nop
    nop
    nop

    vsetvli x0, x0, e16, m1, ta, ma          # SEW= 8, LMUL=1

    nop
    nop
    nop

    li a0, 1
    vsetvli t0, a0, e8, ta, ma          # SEW= 8, LMUL=1
    li a0, 2
    vsetvli t0, a0, e8, m2, ta, ma      # SEW= 8, LMUL=2
    li a0, 2
    vsetvli t0, a0, e32, mf2, ta, ma    # SEW=32, LMUL=1/2
    li a0, 3
    vsetvli t0, a0, e32, ta, ma         # Set vector length based on 32-bit vectors
    li a0, 4
    vsetvli a4, a0, e8, m1, ta, ma      # Byte vector for predicate calc
    li a0, 5
    vsetvli t0, a2, e8, m8, ta, ma      # Vectors of 8b
    li a0, 6
    vsetvli t0, a0, e8, m1, ta, ma      # Use 8b elements
    li a0, 7
    vsetvli t0, a0, e16, m2, ta, mu     # Use 16b elements
    li a0, 8
    vsetvli a4, a0, e32, m8, ta, ma
    li a0, 9
    vsetvli t0, x0, e8, m2, ta, ma      # Max length vectors of bytes

    nop
    nop
    nop

    li a1, 0x0c0
    vsetvl t0, a0, a1
    li a1, 0x0c1
    vsetvl t0, a0, a1
    li a1, 0x0d7
    vsetvl t0, a0, a1
    li a1, 0x0c3
    vsetvl t0, a0, a1
    li a1, 0x049
    vsetvl t0, a0, a1

    nop
    nop
    nop

    vsetivli t0, 10, e8, ta, ma          # SEW= 8, LMUL=1
    vsetivli t0, 20, e8, m2, ta, ma      # SEW= 8, LMUL=2
    vsetivli t0, 25, e32, mf2, ta, ma    # SEW=32, LMUL=1/2
    vsetivli t0, 31, e32, mf8, ta, ma    # Set vector length based on 32-bit vectors
.section .rodata		# Constants
.align 4
.globl _has_priv	# Set available for 'extern'
_has_priv: .4byte 1
reg_buffer: .4byte 0

