
.section .init
.align 4
    
.globl boot

    lw          t1, tam
    vsetvli     t0, t1, e32, m4, ta, ma 
    la          t2, vet
    vle32.v     v2, (t2)
    vsll.vi     v15, v2, 1

.end:
    li      s10,    0x80000000
    sw      zero,   0(s10)
    jal     zero,   .end


.section .rodata
.align 4

vet:    .word   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
tam:    .word   8
