.equ MMR_BASE, 0x20000000

	.section .text.init
	.global _entry
_entry:

boot:
    # Configura o tratador de interrupções
    la t0, trap_handler         # Grava o endereço do rótulo trap_handler
    csrw mtvec, t0              # no registrador mtvec

    # Habilita Interrupções Global
    li t1, 0x80                 # Seta o bit 7 (MPIE)
    csrs mstatus, t1            # do registrador mstatus

    # Habilita Interrupções Externas
    li t2, 0x888                # Seta os bits 11, 7 e 3 (MEIE, MTIE e MSIE)
    csrs mie, t2                # do registrador mie

	# Configura timer
	li	t0, MMR_BASE
	li	t1, 50000	# 500 us (time / period)
	sw	zero,  0(t0)
	sw  zero,  4(t0)
	sw    t1,  8(t0)
	sw  zero, 12(t0)

    # Ajusta o mscratch
    li t1, 60000	            # Coloca o endereço do buffer para salvar
    csrw mscratch, t1           # registradores em mscratch

    # Seta o MPP com o priv Usuario
    # csrr t1, mstatus            # Seta os bits 11 e 12 (MPP)
    # li t2, ~0x1800              # do registrador mstatus
    # and t1, t1, t2              # com o valor 00
    # csrw mstatus, t1

	# Seta o MPP com privilegio Maquina
    csrr t1, mstatus            # Seta os bits 11 e 12 (MPP)
    li t2, 0x1800               # do registrador mstatus
    or t1, t1, t2               # com o valor 11
    csrw mstatus, t1

    la t0, main                 # Grava o endereço do rótulo main
    csrw mepc, t0               # no registrador mepc
    mret                        # PC <= MEPC; MIE <= MPIE; Muda modo para MPP

trap_handler:
    csrrw a0, mscratch, a0

	sw a1, 0(a0)
	sw a2, 4(a0) 
	sw a3, 8(a0) 
	sw a4, 12(a0)
	sw a5, 16(a0)

    csrr  a1, mcause

    bgez a1, exc_handler    # desvia se for uma exceção
    andi a1, a1, 0x3f       # isola a causa de interrupção
    li a2, 11               # a2 = interrupção externa
    beq a1, a2, MEI_handler # se for MEI salta pro handler
    li a2, 3                # a2 = software interrupt
    beq a1, a2, MSI_handler # se for MSI salta pro handler
    li a2, 7                # a2 = timer interrupt
    beq a1, a2, MTI_handler # se for MTI salta pro handler

    j return                # se nao retorna

MEI_handler:
    li a1,0x80001000
	addi a2,zero,'\n'
	sw a2,0(a1)
	addi a2,zero,'M'
	addi a3,zero,'E'
	addi a4,zero,'I'
	addi a5,zero,'\n'
	sw a2,0(a1)
	sw a3,0(a1)
	sw a4,0(a1)
	sw a5,0(a1)

	li a1,0x90001000
	addi a2,zero,'Z'
	sw a2,0(a1)

    j return

MSI_handler:
    li a1,0x80001000
	addi a2,zero,'\n'
	sw a2,0(a1)
	addi a2,zero,'M'
	addi a3,zero,'S'
	addi a4,zero,'I'
	addi a5,zero,'\n'
	sw a2,0(a1)
	sw a3,0(a1)
	sw a4,0(a1)
	sw a5,0(a1)

	li a1,0x90001000
	addi a2,zero,'Z'
	sw a2,0(a1)

    j return

MTI_handler:
    li a1,0x80001000
	addi a2,zero,'\n'
	sw a2,0(a1)
	addi a2,zero,'M'
	addi a3,zero,'T'
	addi a4,zero,'I'
	addi a5,zero,'\n'
	sw a2,0(a1)
	sw a3,0(a1)
	sw a4,0(a1)
	sw a5,0(a1)

	li	a1, MMR_BASE
	sw  zero, 0(a1)
	sw  zero, 4(a1)

	li a1,0x90001000
	addi a2,zero,'Z'
	sw a2,0(a1)

    j return

exc_handler:
    # TRATA A EXCECAO
    
    # Ajustando MEPC para retornar de uma chamada de sistema
    csrr a1, mepc # carrega endereço de retorno
    
    # (endereço da instrução que invocou a syscall)
    addi a1, a1, 4 # soma 4 no endereço de retorno
    
    # (para retornar após a ecall)
    csrw mepc, a1 # armazena endereço de retorno de volta no mepc

    j return

return:
	lw a1, 0(a0)
	lw a2, 4(a0)
	lw a3, 8(a0)
	lw a4, 12(a0)
	lw a5, 16(a0)

    csrrw a0, mscratch, a0
    mret

main:
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

	TEST(simple)

	TEST(lui)
	TEST(auipc)
	TEST(j)
	TEST(jal)
	TEST(jalr)

	TEST(beq)
	TEST(bne)
	TEST(blt)
	TEST(bge)
	TEST(bltu)
	TEST(bgeu)

	TEST(lb)
	TEST(lh)
	TEST(lw)
	TEST(lbu)
	TEST(lhu)

	TEST(sb)
	TEST(sh)
	TEST(sw)

	TEST(addi)
	TEST(slti)
	TEST(xori)
	TEST(ori)
	TEST(andi)
	TEST(slli)
	TEST(srli)
	TEST(srai)

	TEST(add)
	TEST(sub)
	TEST(sll)
	TEST(slt)
	TEST(xor)
	TEST(srl)
	TEST(sra)
	TEST(or)
	TEST(and)

	TEST(div)
	TEST(divu)
	TEST(mul)
	TEST(mulh)
	TEST(mulhsu)
	TEST(mulhu)
	TEST(rem)
	TEST(remu)

	TEST(csr)
	TEST(mcsr)
	TEST(ebreak)
	TEST(ecall)
	TEST(wfi)
	TEST(zicntr)

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
	# li	s10, 0x80000000		# this will interrupt the simulation (assertion)
	# sw	zero, 0(s10)
	jal zero, .end
