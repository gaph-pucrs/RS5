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

	/* RV32UI */
	TEST(add)
	TEST(addi)
	TEST(and)
	TEST(andi)
	TEST(auipc)
	TEST(beq)
	TEST(bge)
	TEST(bgeu)
	TEST(blt)
	TEST(bltu)
	TEST(bne)
	# TEST(fence_i)
	TEST(jal)
	TEST(jalr)
	TEST(lb)
	TEST(lbu)
	TEST(lh)
	TEST(lhu)
	TEST(lui)
	TEST(lw)
	# TEST(ma_data)
	TEST(or)
	TEST(ori)
	TEST(sb)
	TEST(sh)
	TEST(simple)
	TEST(sll)
	TEST(slli)
	TEST(slt)
	TEST(slti)
	TEST(sltiu)
	TEST(sltu)
	TEST(sra)
	TEST(srai)
	TEST(srl)
	TEST(srli)
	TEST(sub)
	TEST(sw)
	TEST(xor)
	TEST(xori)

	/* RV32UM */
	TEST(div)
	TEST(divu)
	TEST(mul)
	TEST(mulh)
	TEST(mulhsu)
	TEST(mulhu)
	TEST(rem)
	TEST(remu)

	/* RV32UC */
	TEST(rvc)

	/* RV32UA */
	TEST(amoadd_w)
	TEST(amoand_w)
	TEST(amomax_w)
	TEST(amomaxu_w)
	TEST(amomin_w)
	TEST(amominu_w)
	TEST(amoor_w)
	TEST(amoswap_w)
	TEST(amoxor_w)
	TEST(lrsc)

	/* I don't know where this one came from */
	TEST(j)

	/* RV32MI */
	TEST(mcsr)
	TEST(ebreak)
	TEST(ecall)
	TEST(zicntr)

	/* RV32SI */
	TEST(wfi)

	/* RV32MI csr test changes privilege level without coming back so it needs to be the last */
	TEST(csr)

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
