.section .init
.align 4

# Main defines
.equ    BATCH_SIZE,         32
.equ    DATASET_UNITS,      1
.equ    INPUT_SIZE,         120
.equ    NUM_FILTERS,        64
.equ    KERNEL_SIZE,        5
.equ    CONV0_INPUT_SIZE,   120
.equ    CONV3_INPUT_SIZE,   116
.equ    CONV6_INPUT_SIZE,   112
.equ    FC1_OUTPUT_SIZE,    128
.equ    FC2_OUTPUT_SIZE,    5

# INT CNN defines

.equ    MULTIP_conv1,       1000
.equ    MULTIP_conv3,       1000
.equ    MULTIP_conv6,       1000
.equ    MULTIP_fc1,         1000
.equ    MULTIP_fc2,         1000

.globl boot 
# la      a2, dataset120 
#    li      a4, INPUT_SIZE 

DATASET_LOOP:
#    vsetvli a5, a4, e32, m8, ta, ma 
#    vle32.v v8, 0(a2) 
#    sub     a4, a5 
#    add     a2, a2, a5 
    la      a3, conv0_featureMap2  
    la      a4, conv0_weights           # conv0_currentKernel  
    la      a5, conv0_bias 
    li      t6, 64                      # was 8 
    li      s3, 0 
    li      s4, 64 

BEGIN_BIAS:
    lw      t2, 0(a5) 
    la      a2, dataset120 
    addi    a5, a5, 4 
    li      t1, MULTIP_conv1
    li      a0, 116 
    mul     t2, t2, t1 

    # li      s10, 0x80001000 
    # lw      t1, (a2)
    # sw      t1, (s10)  
    # li      s10, 0x80001000 
    #lw      s9, (a4) 
    # sw      t2, (s10) 

NEXT: 
    mv      a7, a0 
    # bgeu    t6, a0, SKIP1 
    # li      a7, 64                      # was 8  
SKIP1: 
    vmv.v.i v24, 0                      # sums_vreg  
    li      t1,  0 
    li      t5,  5 
    mv      s5,  a2 

#----------------------------------------------------------------
    vsetvli a1, a7, e32, m8, ta, ma 
LOOP:
    # vsetvli a1, a7, e32, m8, ta, ma 
    vle32.v v8, (s5) 

    lw      t4, (a4)

    addi    s5, s5, 4                   # input++ 
    addi    a4, a4, 4                   # kernel++ 
    addi    t1, t1, 1 

    vmacc.vx    v24, t4, v8                # vmacc.vx ??? 
    bne     t1, t5, LOOP 
#----------------------------------------------------------------

    vadd.vx v24, v24, t2  
    vsetvli zero, a7, e32, m8, ta, ma 
    addi    a2, a2, 256    

    vmsgt.vi v0, v24, 0                    # RELU 

    vse32.v v24, (a3), v0.t
    # vse32.v v24, (a3)
    slli     t1, a1, 2

    # li      s10, 0x80001000 
    # sw      a0, (s10) 

    addi    a0, a0, -64 
#    addi    ?
#    addi    ?
    # addi    a3, a3, 256                 # featureMap++ 
    add     a3, a3, t1                    # featureMap++ 
    # bgt     a0, zero, SKIP2   
    bgt     zero, a0, SKIP2   
    addi    a4, a4, -20 
    j       NEXT 
SKIP2:
    addi    s3, s3, 1 
    bne     s3, s4, BEGIN_BIAS 
    
    # j .end     

# INT HANDLER 

    li  a5, 0x10624dd3                  # magic number 

    #li  a5, 0x10625000 
    #addi a5, a5, -557 

    la  a4, conv0_featureMap2 
    li  a1, 7424                        # NUM_FILTERS * (CONV0_INPUT_SIZE-4) 
    
INT_HANDLER:
    vsetvli a0, a1, e32, m8, ta, ma 
    vle32.v v8, (a4)                    # featureMap.vreg 
    sub     a1, a1, a0 
    
#------------------------------------------------------------------------------------
    vmulh.vx  v16, v8, a5   
    vsra.vi   v8,  v8, 31               # sign bit 
    vsra.vi   v16, v16, 6               # /= 64 
    vsub.vv   v16, v16, v8              # -= sign_bit 
#------------------------------------------------------------------------------------ ok 

    slli      t1,  a0,  2 
    vse32.v   v16, (a4)                 # featureMap[i] = featureMap[i]/1000 
    add       a4, a4, t1 
    bnez      a1, INT_HANDLER 

    #j .end  

# RELU

#     la  a4, conv0_featureMap2 
#     li a1, 7424
#     li t0, 0 

# RELU:
#     lw a2, (a4)
#     bgtz a2, SKIP3
#     li a2, 0 
# SKIP3:
#     sw a2, 0(a4)
#     addi a4, a4, 4 
#     addi t0, t0, 1
#     bne t0, a1, RELU

# RELU:
#     vsetvli a0, a1, e32, m8, ta, ma 
#     sub a1, a1, a0 
    
#     vle32.v v8, (a4) 
#     vmsgt.vi v0, v8, 0
#     vse32.v v8, (a4), v0.t 

#     slli t1, a0, 2
#     add a4, a4, t1
#     bnez a1, RELU 

print_routine:
    la a2, conv0_featureMap2            # Load address of the words array
    la a5, 0x80001000 
    li a1, 7424                         # Load the number of words
    #li a1, 1                           # Load the number of words
    li t0, 0                            # Initialize index to 0

print_loop:
    beq t0, a1, .end                    # If index == count, exit the loop

    lw t1, 0(a2)                        # Load current word into t1
    sw t1, 0(a5) 

    addi a2, a2, 4                      # Move to the next word
    addi t0, t0, 1                      # Increment index
    j print_loop                        # Repeat the loop

.end:
    li      s10,    0x80000000
    sw      zero,   0(s10)
    jal     zero,   .end


.section .rodata
conv0_featureMap2: .space 29696
