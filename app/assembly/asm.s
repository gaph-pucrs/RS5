.section .init
.align 4

.globl main
main:

	# Configure system status MPP=0, MPIE=0, MIE=0
	csrw	mstatus, zero

	# Clear pending interrupts
	csrw	mip, zero

	# Enable MEI when unmasked (if MIE=1)
	li		t0, 0x800
	csrw	mie, t0

	# Disable S-Mode int/exc handling
	# Handle them in M-Mode
	csrw	mideleg, zero
	csrw	medeleg, zero

	# Configure Syscall
	la		t0, except_handler		# Load the vector_entry address to t0
	csrw	mtvec,t0			# Write vector_entry address to mtvec
								# Last bit is 0, means DIRECT mode

	jal		main

	csrw	mscratch, sp	# Save sp to mscratch

	j		except_handler


.section .rodata		# Constants
.align 4
.globl _has_priv	# Set available for 'extern'
_has_priv: .4byte 1
.globl except_handler	# MTVEC VALUE
except_handler: .4byte 1

