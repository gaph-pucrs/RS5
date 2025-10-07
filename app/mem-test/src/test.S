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

.section .text
main:
    la a0, arr
    li t0, 1
    sw t0, 0(a0)
    li t0, 2
    sw t0, 4(a0)
    li t0, 3
    sw t0, 8(a0)
    li t0, 4
    sw t0, 12(a0)
    li t0, 5
    sw t0, 16(a0)
    li t0, 6
    sw t0, 20(a0)
    li t0, 7
    sw t0, 24(a0)
    li t0, 8
    sw t0, 28(a0)
    li t0, 9
    sw t0, 32(a0)

    li t1, 0x80002000
    lw t0, 0(a0)
    sw t0, 0(t1)
    lw t0, 4(a0)
    sw t0, 0(t1)
    lw t0, 8(a0)
    sw t0, 0(t1)
    lw t0, 12(a0)
    sw t0, 0(t1)
    lw t0, 16(a0)
    sw t0, 0(t1)
    lw t0, 20(a0)
    sw t0, 0(t1)
    lw t0, 24(a0)
    sw t0, 0(t1)
    lw t0, 28(a0)
    sw t0, 0(t1)
    lw t0, 32(a0)
    sw t0, 0(t1)

    ret
    nop
    nop
    nop
    nop

.section .bss
.align 4
arr:
    .skip 40          # Array of 10 integers (4 bytes each)
