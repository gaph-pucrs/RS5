.section .init 
.align 4 

.globl boot 

la a1, vet
la a2, res 
vsetivli zero, 8, e32, m1, ta, ma 
vle32.v  v8, (a1) 
li t0, 10 
vadd.vx v8, v8, t0 
vse32.v  v8, (a2) 

la a1, 0x80001000 
la t0, res
li t1, 8


print: 
lw t2, 0(t0) 
sw t2, 0(a1)
addi t1, t1, -1
addi t0, t0,  4 
bnez t1, print 


exit:
li s10, 0x8000000
sw  zero,   0(s10)
jal zero, exit 


.section .rodata
.align 4

vet: .word 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8 
res: .word 
