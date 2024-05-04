.section .init
.align 4

.globl boot
    nop
    nop
    nop

    #######################################
    # 8 bits multiplications
    #######################################
    li a0, 8
    vsetvli t0, a0, e8, m1, ta, ma          # SEW= 8, LMUL=1
    nop
    vor.vi v1, v1, 5    # 0x05
    nop
    vor.vi v2, v2, 2    # 0x02
    nop
    vmul.vv v3, v1, v2  # 0x0A

    nop
    vor.vi v4, v4, 5    # 0x05
    nop
    addi a2, a2, 4      # 0x04
    nop
    vmul.vx v5, v4, a2  # 0x14

    nop
    li a1, 100
    vor.vx v6, v6, a1     # 0x64
    nop
    li a2, 11             # 0x0B
    nop
    vmul.vx v7, v6, a2    # 0x044C (4C)
    nop
    vmulhu.vx v8, v6, a2  # 0x044C (04)

    #signed-unsigned
    nop
    li a1, -9
    vor.vx v9, v9, a1      # 0xF7
    nop
    li a2, 33              # 0x21
    nop
    vmul.vx v10, v9, a2    # 0xFED7 (D7)
    nop
    vmulhsu.vx v11, v9, a2 # 0xFED7 (FE)

    #signed
    nop
    li a1, -9
    vor.vx v12, v12, a1    # 0xF7
    nop
    li a2, -33             # 0xDF
    nop
    vmul.vx v13, v12, a2   # 0x0129 (29)
    nop
    vmulh.vx v14, v12, a2  # 0x0129 (01)

    vsetvli t0, x0, e8, m2, ta, ma          # SEW=8, LMUL=2, VL=16
    nop
    vor.vi v15, v15, 8     # 0x08
    nop
    li a2, 255             # 0xFF
    vor.vx v17, v17, a2    # 0xFF
    nop
    vmul.vv v19, v15, v17  # 0x07F8
    nop
    vmulhu.vv v21, v15, v17 # 0x07F8

    jal ra, clear_vreg_bank

    #######################################
    # 16 bits multiplications
    #######################################
    # Positive 16-bit multiplication
    vsetvli t0, a0, e16, m1, ta, ma          # SEW= 16, LMUL=1
    nop
    li a1, 100          # 0x0064
    vor.vx v6, v6, a1
    nop
    li a2, 11           # 0x000B
    nop
    vmul.vx v7, v6, a2  # 0x044C

    # Signed-Unsigned 16-bit multiplication
    nop
    li a1, -9           # 0xFFF7
    vor.vx v9, v9, a1
    nop
    li a2, 33           # 0x0021
    nop
    vmul.vx v10, v9, a2  # 0xFED7
    nop
    vmulhsu.vx v11, v9, a2  # 0xFFFFED7

    # Zero-extended 16-bit multiplication
    nop
    li a1, 0                # Load 16-bit value 0x0000
    vor.vx v12, v12, a1
    nop
    li a2, -1               # Load 16-bit signed value 0xFFFF
    nop
    vmul.vx v13, v12, a2    # 0x00
    nop
    vmulhu.vx v14, v12, a2  # 0x00

    # High 16-bit multiplication
    nop
    li a1, -100         # Load 16-bit signed value 0xFF9C
    vor.vx v15, v15, a1
    nop
    li a2, 100          # 0x0064
    nop
    vmul.vx v16, v15, a2 # D8f0
    nop
    vmulh.vx v17, v15, a2 # FFFF

    #######################################
    # Widening Multiplication 8 bits
    #######################################
    jal ra, clear_vreg_bank

    li a0, 8
    vsetvli t0, a0, e8, m1, ta, ma          # SEW= 8, LMUL=1
    nop
    li a1, 100
    vor.vx v1, v1, a1     # 0x64
    nop
    li a2, 11             # 0x0B
    nop
    vwmulu.vx v2, v1, a2  # 0x044C

    li a0, 16
    vsetvli t0, a0, e8, m2, ta, ma          # SEW= 8, LMUL=2
    nop
    li a1, 100
    vor.vx v4, v4, a1     # 0x64
    nop
    li a2, 11             # 0x0B
    nop
    vwmul.vx v6, v4, a2   # 0x044C

    #######################################
    # MACCs
    #######################################
    jal ra, clear_vreg_bank

    li a0, 8
    vsetvli t0, a0, e8, m1, ta, ma          # SEW= 8, LMUL=1
    nop
    li a1, 02
    vor.vx v1, v1, a1    # 0x02
    nop
    vmacc.vx v2, a1, v1  # 0x04 + 0x00 = 0x04

    nop
    vmacc.vx v2, a1, v1  # 0x04 + 0x04 = 0x8

    nop
    vmacc.vv v2, v1, v1  # 0x04 + 0x08 = 0x0C

    nop
    vmacc.vv v2, v1, v1  # 0x04 + 0x0C = 0x10

    #vnmsac
    nop
    vnmsac.vv v2, v1, v1  # 0x10 - 0x04 = 0x0C

    nop
    vnmsac.vv v2, v1, v1  # 0x0C - 0x04 = 0x08

    #vmadd
    nop
    li a2, 04
    vor.vx v3, v3, a2    # 0x04
    nop
    vmadd.vx v1, a2, v1  # 0x02 * 0x04 + 0x2 = 0x0A

    nop
    vmadd.vx v1, a2, v1  # 0x0A * 0x04 + 0xA = 0x32

    nop
    li a3, 208            # 0xD0
    vor.vx v4, v4, a3
    nop
    vnmsub.vx v1, a2, v4  # 0xD0 - (0x32 * 0x04) = 0x08
    nop
    vnmsub.vx v1, a2, v4  # 0xC8 - (0x08 * 0x04) = 0xB0

    jal ra, clear_vreg_bank

    vsetvli t0, x0, e8, m1, ta, ma          # SEW= 8, LMUL=1, VL=VLMAX
    nop
    li a1, 02
    vor.vx v1, v1, a1    # 0x02
    li a1, 04
    vor.vx v2, v2, a2    # 0x04

    vsetvli t0, x0, e8, m2, ta, ma          # SEW= 8, LMUL=2
    nop
    vmacc.vx v3, a1, v1  # (0x04*0x02)0x08 + 0x00 = 0x04 and (0x04*0x04)0x10 + 0x00 = 0x10

    nop
    vmacc.vx v3, a1, v1  # (0x04*0x02)0x08 + 0x08 = 0x10 and (0x04*0x04)0x10 + 0x10 = 0x20

    nop
    vmacc.vv v3, v1, v1  # (0x02*0x02)0x04 + 0x10 = 0x14 and (0x04*0x04)0x10 + 0x20 = 0x30

    nop
    vmacc.vv v3, v1, v1  # (0x02*0x02)0x04 + 0x14 = 0x18 and (0x04*0x04)0x10 + 0x30 = 0x40

    #vnmsac
    nop
    vnmsac.vv v3, v1, v1  # 0x18 - (0x02*0x02)0x04 = 0x14 and 0x40 -(0x04*0x04)0x10 = 0x30

    nop
    vnmsac.vv v3, v1, v1  # 0x0C - 0x04 = 0x08


    #######################################
    # Divisions
    #######################################
    jal ra, clear_vreg_bank

    vsetvli t0, x0, e8, m1, ta, ma          # SEW=8, LMUL=1, VL=8

    nop
    vor.vi v1, v1, 13   # 0x0D
    li a4, 5            # 0x05
    vdiv.vx v2, v1, a4  # 0x02
    nop
    vrem.vx v3, v1, a4  # 0x03

    nop
    vor.vi v5, v5, -13  # 0xF3
    nop
    vdiv.vx v6, v5, a4  # 0xFE
    nop
    vrem.vx v7, v5, a4  # 0xFD

    nop
    vor.vi v9, v9, 13    # 0x0D
    li a4, -5            # 0xFB
    vdiv.vx v10, v9, a4  # 0xFE
    nop
    vrem.vx v11, v9, a4  # 0x03

    nop
    vor.vi v13, v13, -13  # 0xF3
    nop
    vdiv.vx v14, v13, a4  # 0x02
    nop
    vrem.vx v15, v13, a4  # 0xFD

    # overflow
    nop
    li a3, 128
    vor.vx v17, v17, a3   # 0x80
    li a4, 1              # 0x01
    vdiv.vx v18, v17, a4  # 0x80
    nop
    vrem.vx v19, v17, a4  # 0x00

    li a5, -1             # 0xFF
    vdiv.vx v20, v17, a5  # 0x80
    nop
    vrem.vx v21, v17, a5  # 0x00

    # divide by zero
    vdiv.vx v23, v17, x0  # 0xFF
    nop
    vrem.vx v24, v17, x0  # 0x80

    vor.vi v22, v22, 1    # 0x01
    nop
    vdiv.vx v25, v22, x0  # 0xFF
    nop
    vrem.vx v26, v22, x0  # 0x01

    nop
    vdiv.vx v27, v31, x0  # 0xFF
    nop
    vrem.vx v28, v31, x0  # 0x00

    # LMUL > 1
    jal ra, clear_vreg_bank

    vsetvli t0, x0, e8, m1, ta, ma          # SEW=8, LMUL=1, VL=8
    nop
    vor.vi v1, v1, 13   # 0x0D
    nop
    vor.vi v2, v2, -13  # 0xF3
    li a4, 5            # 0x05

    vsetvli t0, x0, e8, m2, ta, ma          # SEW=8, LMUL=2, VL=16
    vdiv.vx v4, v1, a4  # 0x02 and 0xFE
    nop
    vrem.vx v7, v1, a4  # 0x03 and 0xFD

    #######################################
    # Logicals
    #######################################
    jal ra, clear_vreg_bank

    li a0, 8
    vsetvli t0, a0, e8, m1, ta, ma          # SEW= 8, LMUL=1
    nop
    vor.vi v1, v1, 15   # 0x0F
    nop
    addi a7, a7, -9     # 0xF7
    nop
    vor.vx v2, v2, a7
    nop
    vand.vv v1, v1, v2  # 0x07

    nop
    nop
    nop

    li a0, 16
    vsetvli t0, a0, e8, m2, ta, ma          # SEW= 8, LMUL=2
    nop
    vor.vi v4, v4, 15     # 0x0F
    nop
    addi a7, a7, -9       # 0xEE
    nop
    vor.vx v6, v6, a7
    nop
    vand.vv v1, v4, v6    # 0x0E

    nop
    nop
    nop

    vsetvli t0, x0, e8, m4, ta, ma          # SEW= 8, LMUL=4, VL=32
    nop
    vor.vi v8, v8, 15       # 0x0F
    nop
    addi a7, a7, -9         # 0xE5
    nop
    vor.vx v12, v12, a7
    nop
    vand.vv v1, v8, v12     # 0x05

    nop
    nop
    nop

    vsetvli t0, x0, e8, m8, ta, ma          # SEW= 8, LMUL=8, VL=64
    nop
    vor.vi v16, v16, 15     # 0x0F
    nop
    addi a7, a7, -9         # 0xDC
    nop
    vor.vx v24, v24, a7
    nop
    vand.vv v1, v16, v24    # 0x0C

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
    vor.vx  v1, v1, a0                      # 0xFF
    vor.vx  v2, v2, a0                      # 0xFF
    vadd.vv v3, v1, v2                      # 0xFE

    nop
    li a0, 154                              # Loads 0x9A to a0
    vadd.vx v4, v4, a0
    li a0, 91                               # Loads 0x5B to a0
    vadd.vx v5, v4, a0                      # Results in 0xF5

    nop
    vadd.vi v6, v6, 15                      # Results in 0x0F (0x00 + 0x0F)
    vadd.vi v7, v6, 12                      # Results in 0x1B (0x0F + 0x0C)

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

    # REVERSE SUB INSTRUCTION
    vsetvli t0, x0, e8, m1, ta, ma          # SEW= 8, LMUL=1, VL=VLMAX
    li a0, 7                                # Loads 0x07 to a0
    vadd.vx v15, v15, a0
    li a0, 16                               # Loads 0x10 to a0
    vrsub.vx v16, v15, a0                   # Makes 16 - 8
    nop
    vrsub.vi v17, v16, 10                   # Makes 10 - 8

    # Test 16 Bits Reverse Subs
    vsetvli t0, x0, e16, m1, ta, ma         # SEW= 8, LMUL=1, VL=VLMAX
    li a0, 2200                             # Loads 0x0898 to a0
    vadd.vx v18, v18, a0
    li a0, 4000                             # Loads 0x0FA0 to a0
    vrsub.vx v19, v18, a0                   # Makes 4000 - 2200 = 1800(708)
    nop
    vrsub.vi v20, v19, 8                    # Makes 8 - 1800 = -700 (F900)

    # Test LMUL_2 Reverse Subs
    vsetvli t0, x0, e8, m2, ta, ma          # SEW= 8, LMUL=1, VL=VLMAX
    li a0, 7                                # Loads 0x07 to a0
    vadd.vx v21, v21, a0
    li a0, 16                               # Loads 0x10 to a0
    vrsub.vx v23, v21, a0                   # Makes 16 - 8
    nop
    vrsub.vi v25, v23, 10                   # Makes 10 - 8

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

