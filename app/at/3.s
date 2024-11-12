#  res[] = vet[] + 10 
.section .init
.align 4

.globl boot

    lw  t1, tam
    la  t2, vet
    la  t3, res
    li  t4, 10

loop:
    lw      t5, 0(t2)
    add     t6, t5, t4
    sw      t6, 0(t3)

    addi    t3, t3, 4
    addi    t2, t2, 4
    addi    t1, t1, -1

    bne     t1, zero, loop

.end:
    li  s10,    0x80000000
    sw  zero,   0(s10)
    jal zero,   .end

.section .rodata
.align 4

vet:    .word   0x1, 0x2, 0x3, 0x4
res:    .word   0x0
tam:    .word   0x4
