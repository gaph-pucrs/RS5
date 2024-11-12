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
    la      a2, dataset120 
#    li      a4, INPUT_SIZE 

DATASET_LOOP:
#    vsetvli a5, a4, e32, m8, ta, ma 
#    vle32.v v8, 0(a2) 
#    sub     a4, a5 
#    add     a2, a2, a5 
    la      a3, conv0_featureMap  
    la      a4, conv0_weights           # conv0_currentKernel  
    la      a5, conv0_bias 
    li      t1, MULTIP_conv1 
    li      t6, 64                      # was 8 
    li      s3, 0 
    li      s4, 64 

BEGIN_BIAS:
    lw      t2, 0(a5) 
    li      a0, 116 
    mul     t2, t2, t1 
#    li      t1, 64
#    vsetvli    zero, t1, e32, m8, ta, ma 
#    vmv.v.x v0, t2                      # bias_vreg 

#-------- OK -----------------
NEXT: 
    mv      a7, a0 
    bgeu    t6, a0, SKIP1 
    li      a7, 64                      # was 8  
SKIP1: 
    vmv.v.i v24, 0                      # sums_vreg  
    li      t1,  0 
    li      t5,  5 
    mv      s5,  a2 

LOOP:
    vsetvli zero, a7, e32, m8, ta, ma 
    vle32.v v8, (s5) 

    lw      t4, (a4) 
    vmv.v.x v16, t4                     # kernel[i]_vreg 

    addi    s5, s5, 4                   # input++ 
    addi    a4, a4, 4                   # kernel++ 
    addi    t1, t1, 1 

    li      s10, 0x80001000 
    vmv.x.s a0, v8
    sw      a0, (s10) 

    vmv.x.s a0, v16 
    sw      a0, (s10) 

    vmv.x.s a0, v24
    sw      a0, (s10) 

    vmacc.vv    v24, v8, v16            # vmacc.vx ??? 
#    vse32.v v24, (a3) 

    vmv.x.s a0, v24
    sw      a0, (s10) 
    #jal print_routine 
    bne     t1, t5, LOOP 
#    jal print_routine 
    j .end 
#-----------------------------
        
    vadd.vx v24, v24, t2  
    vsetvli zero, a7, e32, m8, ta, ma 
    addi    a2, a2, 256    
    vse32.v v24, (a3) 
    addi    a0, a0, -64 
#    addi    ?
#    addi    ?
    addi    a3, a3, 256                 # featureMap++ 
    bgt     a0, zero, SKIP2   
    addi    a4, a4, -20 
    j       NEXT 
SKIP2:
    addi    s3, s3, 1 
    bne     s3, s4, BEGIN_BIAS 
    
#    j .end     

print_routine:
    la a2, conv0_featureMap            # Load address of the words array
    la a5, 0x80001000 
    #li a1, 7424          # Load the number of words
    li a1, 1          # Load the number of words
    li t0, 0             # Initialize index to 0

print_loop:
    beq t0, a1, .end     # If index == count, exit the loop

    lw t1, 0(a2)         # Load current word into t1
    sw t1, 0(a5) 

    addi a2, a2, 4       # Move to the next word
    addi t0, t0, 1       # Increment index
    j print_loop         # Repeat the loop

.end:
    li      s10,    0x80000000
    sw      zero,   0(s10)
    jal     zero,   .end


.section .rodata
conv0_featureMap2: .word 
