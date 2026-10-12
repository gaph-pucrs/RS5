.section .init
.align 4

.globl _start
_start:
	# Configure system status MPP=0, MPIE=0, MIE=0
	csrw	mstatus, zero

	# Mask interrupts
	csrw	mie, zero

	# Clear pending interrupts
	csrw	mip, zero

	.option	push
	.option	norelax
	la		gp, __global_pointer$
	.option	pop

	# Set stack to top of data memory
	li		sp, MEM_SIZE
	
	# Clear the BSS
	la		a0, _edata
	la		a2, _end
	sub		a2, a2, a0
	li		a1, 0
	call	memset

	# Initialize newlib
	la 		a0, __libc_fini_array
	call	atexit
	call	__libc_init_array

	# Clear argc, argv, envp
	li		a0, 0
	li		a1, 0
	li		a2, 0

	call	main

	call	exit
