.section .init
.align 4

.globl main

main:

    li      t0, 0x12345678

	csrrw	t2, misa, zero  # read misa

	csrrw	t2, mtvec, t0   # Write 12345678 to mtvec

	li		t1, 0xCC498180
	csrrs	t2, mtvec, t1   # Set some bits
	csrrc	t2, mtvec, t1   # Unset the bits previously set
	

	la		t0, except_handler		# Load the vector_entry address to t0
	csrw	mtvec,t0			# Write vector_entry address to mtvec

	jal		main



.section .rodata		# Constants
.align 4
.globl _has_priv	# Set available for 'extern'
_has_priv: .4byte 1
.globl except_handler	# MTVEC VALUE
except_handler: .4byte 1

