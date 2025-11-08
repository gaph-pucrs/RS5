.section .init
.global _start
_start:
    # Configure system status MPP=0, MPIE=0, MIE=0
	csrw	mstatus, zero

	# Mask interrupts
	csrw	mie, zero

	# Clear pending interrupts
	csrw	mip, zero

    # Set stack to top of data memory
	li		sp, MEM_SIZE

    jal main
.end:
    li  t0, 0x80000000
    sw	zero, 0(t0)     # End simulation
	j   .end

my_label:
    # Apenas um retorno direto
    ret

label2:
    addi t2, t2, 3
    addi t1, t1, 3
    li t0, 1
    sw t0, 0(a0)
    li t0, 2
    sw t0, 4(a0)
    li t0, 3

.section .text
main:
    li t0, 5          # t0 = 5
    li t1, 10         # t1 = 10
    add t2, t0, t1    # t2 = t0 + t1

    sw t2, 0(sp)      # salva t2 no topo da pilha

    jal ra, my_label   # jump and link para my_label

    li a0, 0

    sub t2, t2, t0

    ret
    nop
    nop
    nop
    nop

.section .bss
.align 4
arr:
    .skip 40          # Array of 10 integers (4 bytes each)