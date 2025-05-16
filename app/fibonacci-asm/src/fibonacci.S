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
    addi sp, sp, -4
    sw   ra, 0(sp)

    li  a0, 5
    jal fibonacci

    lw   ra, 0(sp)
    addi sp, sp, 4

    li  t0, 0x80002000
    sw  a0, 0(t0)

    ret

fibonacci:
    li  t1, 1 # (n - 1)
    ble a0, t1, finish # if (n <= 1) return

    mv  t0, zero # current
    mv  t2, zero # (n - 2)

    li  t3, 2    # iterator
loop:
    add  t0, t1, t2 # current  = fib(n-1) + fib(n-2)
    mv   t2, t1     # fib(n-2) = fib(n-1)
    mv   t1, t0     # fib(n-1) = current
    addi t3, t3, 1
    ble  t3, a0, loop  # for (i = 2; i <= n; i++)
    mv   a0, t0
finish:
    ret
