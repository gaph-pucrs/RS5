#   Add 10 to a vector reg

.section .init
.align 4

.globl boot
    nop
    nop
    nop

    lw          t1, tam
    vsetvli     t0, t1, e8, m1, ta, ma
    la          t2, vet
    vle8.v      v1, (t2)
    li          t3, 10 
    vadd.vx     v2, v1, t3   

.end:
    li  s10,    0x80000000
    sw  zero,   0(s10)
    jal zero,   .end

.section .rodata
.align 4

vet:    .word   0x1, 0x2, 0x3, 0x4
tam:    .word   0x00000004
