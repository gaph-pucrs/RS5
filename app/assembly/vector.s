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

    jal ra, clear_vreg_bank

    nop
    nop
    nop
    
    # ARITHMETICH INSTRUCTIONS
    # Test 8 Bits Adds
    vsetvli t0, x0, e8, m1, ta, ma          # SEW= 8, LMUL=1, VL=VLMAX
    li a0, 255                              # Loads 0xFF to a0
    vor.vx  v1, v1, a0
    vor.vx  v2, v2, a0
    vadd.vv v3, v1, v2

    nop
    li a0, 154                              # Loads 0x9A to a0
    vadd.vx v4, v4, a0
    li a0, 91                               # Loads 0x5B to a0
    vadd.vx v5, v4, a0

    nop
    vadd.vi v6, v6, 15
    vadd.vi v7, v6, 12

    # Test VADD For LMUL > 1
    nop
    vsetvli t0, x0, e8, m2, ta, ma          # SEW= 8, LMUL=2, VL=VLMAX
    li a0, 58                               # Loads 0x3A to a0
    vadd.vx v8, v6, a0
    nop
    vadd.vi v10, v4, 10

    jal ra, clear_vreg_bank

    # Test 16 Bits Adds
    vsetvli t0, x0, e16, m1, ta, ma          # SEW= 16, LMUL=1, VL=VLMAX
    li a0, 8144                              # Loads 0x1FD0 to a0
    vor.vx  v1, v1, a0
    vor.vx  v2, v2, a0
    vadd.vv v3, v1, v2

    nop
    li a0, 39578                            # Loads 0x9A9A to a0
    vadd.vx v4, v4, a0
    li a0, 26214                            # Loads 0x6666 to a0
    vadd.vx v5, v4, a0

    nop
    li a0, 39578                            # Loads 0x9A9A to a0
    vadd.vx v6, v6, a0
    li a0, 25957                            # Loads 0x6565 to a0
    vadd.vx v7, v6, a0

    jal ra, clear_vreg_bank
    nop
    nop
    nop

    # SUB INSTRUCTION
    vsetvli t0, x0, e8, m1, ta, ma          # SEW= 8, LMUL=1, VL=VLMAX
    li a0, 2                                # Loads 0x02 to a0
    vadd.vx v1, v1, a0
    li a0, 1                                # Loads 0x01 to a0
    vsub.vx v2, v1, a0

    li a0, 10                               # Loads 0x0A to a0
    vadd.vx v3, v3, a0
    li a0, 6                                # Loads 0x06 to a0
    vsub.vx v4, v3, a0

    li a0, 30                               # Loads 0x1E to a0
    vadd.vx v5, v5, a0
    li a0, -15                              # Loads 0xF1 to a0
    vsub.vx v6, v5, a0

    # Test 16 Bits Subs
    vsetvli t0, x0, e16, m1, ta, ma         # SEW= 16, LMUL=1, VL=VLMAX
    li a0, 2472                             # Loads 0x09A8 to a0
    vadd.vx v7, v7, a0
    li a0, 1634                             # Loads 0x0662 to a0
    vsub.vx v8, v7, a0

    # VSETVL INSTRUCTIONS
    nop
    nop
    nop

    vsetvli t0, x0, e8, m4, ta, ma          # SEW= 8, LMUL=4
    
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
.globl _has_priv	# Set available for 'extern'
_has_priv: .4byte 1
reg_buffer: .4byte 0

