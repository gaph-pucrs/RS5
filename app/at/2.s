#   res[] = vet[] + 10  (vector extension)

.section .init
.align 4

.globl boot
    nop
    nop
    nop
    
    lw          t1, tam
    vsetvli     t0, t1, e8, m1, ta, ma
    la          t2, vet
    la          t3, res
    vle8.v      v1, (t2) 
    vadd.vi     v2, v1, 10 
    vse8.v      v2, (t3) 

.end:
    li  s10,    0x80000000
    sw  zero,   0(s10)
    jal zero,   .end

.section .rodata
.align 4

vet:    .byte   0x1, 0x2, 0x3, 0x4
res:    .word   0x0
tam:    .byte   0x4


