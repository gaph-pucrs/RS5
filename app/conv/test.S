	.section .text.init
	.global _entry
_entry:
    /* Globally disable interrupts */
    csrw mstatus, zero
	csrw mip, zero
	csrw mie, zero
	/* zero-initialize all registers */

	addi x1, zero, 0
	addi x2, zero, 0
	addi x3, zero, 0
	addi x4, zero, 0
	addi x5, zero, 0
	addi x6, zero, 0
	addi x7, zero, 0
	addi x8, zero, 0
	addi x9, zero, 0
	addi x10, zero, 0
	addi x11, zero, 0
	addi x12, zero, 0
	addi x13, zero, 0
	addi x14, zero, 0
	addi x15, zero, 0
	addi x16, zero, 0
	addi x17, zero, 0
	addi x18, zero, 0
	addi x19, zero, 0
	addi x20, zero, 0
	addi x21, zero, 0
	addi x22, zero, 0
	addi x23, zero, 0
	addi x24, zero, 0
	addi x25, zero, 0
	addi x26, zero, 0
	addi x27, zero, 0
	addi x28, zero, 0
	addi x29, zero, 0
	addi x30, zero, 0
	addi x31, zero, 0

	/* running tests from riscv-tests */
	la	sp, _stack

#define TEST(n) \
	.global n; \
	jal zero,n; \
	.global n ## _ret; \
	n ## _ret:

	jal main

#    li  	a0,0x56f
#    addi	a3,a3,-1768 # 56faa0 <INTconv0_featureMap.5>
#    #la a0, INTconv0_featureMap 
#    li a1, 580 
#
#print_words:
#    beqz a1, .end         # If a1 is 0, exit loop
#    lw a2, 0(a0)          # Load the word at address in a0
#    mv a0, a2             # Move the word to a0 for printing
#    li a7, 1              # syscall number for print integer
#    ecall                 # Make the system call
#
#    # Print newline
#    la a0, newline
#    li a7, 4              # syscall number for print string
#    ecall
#
#    addi a0, a0, 4        # Move to the next word (4 bytes)
#    addi a1, a1, -1       # Decrement the counter
#    j print_words         # Repeat the loop
#
#	li a0,0x80001000
#	addi a1,zero,'D'
#	addi a2,zero,'O'
#	addi a3,zero,'N'
#	addi a4,zero,'E'
#	addi a5,zero,'\n'
#	sw a1,0(a0)
#	sw a2,0(a0)
#	sw a3,0(a0)
#	sw a4,0(a0)
#	sw a5,0(a0)
.end:
	li	s10, 0x80000000		# this will interrupt the simulation (assertion)
	sw	zero, 0(s10)
	jal zero, .end

.section .data
buffer: .asciz "Value: %d\n"   # Format string for printing
newline: .asciz "\n"           # Newline string
