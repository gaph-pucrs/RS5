	.section .text.init
	.global _entry
_entry:
    /* Globally disable interrupts. When misa.V is set, also set       */
    /* mstatus.VS = Initial, otherwise vector instructions would trap. */
    csrr t0, misa
    srli t0, t0, 21
    andi t0, t0, 1
    slli t0, t0, 9
    csrw mstatus, t0
    /* Install the trap handler used by the illegal-instruction tests */
    la   t0, trap_handler
    csrw mtvec, t0
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

	li a0,0x80001000
	addi a1,zero,'D'
	addi a2,zero,'O'
	addi a3,zero,'N'
	addi a4,zero,'E'
	addi a5,zero,'\n'
	sw a1,0(a0)
	sw a2,0(a0)
	sw a3,0(a0)
	sw a4,0(a0)
	sw a5,0(a0)
.end:
	li	s10, 0x80000000		# this will interrupt the simulation (assertion)
	sw	zero, 0(s10)
	jal zero, .end

/* Minimal trap handler: counts the trap, records mcause, mepc and mtval */
/* and resumes at the next instruction. Vector instructions are always  */
/* 32 bits wide, so mepc + 4 is the next instruction.                   */
	.align 2
	.global trap_handler
trap_handler:
	csrw mscratch, t0
	la   t0, trap_save
	sw   t1, 0(t0)
	lw   t1, 4(t0)
	addi t1, t1, 1
	sw   t1, 4(t0)
	csrr t1, mcause
	sw   t1, 8(t0)
	csrr t1, mepc
	sw   t1, 12(t0)
	csrr t1, mtval
	sw   t1, 16(t0)
	csrr t1, mepc
	addi t1, t1, 4
	csrw mepc, t1
	lw   t1, 0(t0)
	csrr t0, mscratch
	mret

/* trap_save layout: { t1 spill, count, mcause, mepc, mtval } */
	.data
	.align 2
	.global trap_save
trap_save:
	.word 0, 0, 0, 0, 0
