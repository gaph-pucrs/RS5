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
	# li		sp, MEM_SIZE
    li sp, 65536

    jal main
.end:
    li  t0, 0x80000000
    sw	zero, 0(t0)     # End simulation
	j   .end

.section .text
main:
    li t0, 0
    li t1, 9
    li t2, 8
    kybermul t0, t1, t2

    ret
    nop
    nop
    nop
    nop

.section .bss
.align 4
arr:
    .skip 40          # Array of 10 integers (4 bytes each)
