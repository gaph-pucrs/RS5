#define MMR_BASE  0x20000000
#define PLIC_BASE 0x30000000

	.global _entry
_entry:

boot:
    # Configura o tratador de interrupções
    la t0, trap_handler         # Grava o endereço do rótulo trap_handler
    csrw mtvec, t0              # no registrador mtvec

    # Habilita Interrupções Global
    li t1, 0x80                 # Seta o bit 7 (MPIE)
    csrs mstatus, t1            # do registrador mstatus

	# Habilita Interrupções no PLIC
	li	t0, PLIC_BASE
	li	t1, -1
	sw  t1, 8(t0)

	# Configura timer
	li	t0, MMR_BASE
	li	t1, 100000000	# 0.5 to 1 seconds (time / period)
	sw	zero,  0(t0)
	sw  zero,  4(t0)
	sw    t1,  8(t0)
	sw  zero, 12(t0)

	# Habilita Interrupções Externas
    li t2, 0x880                # Seta os bits 11 e 7 (MEIE e MTIE)
    csrs mie, t2                # do registrador mie

    # Ajusta o mscratch
    li t1, 60000	            # Coloca o endereço do buffer para salvar
    csrw mscratch, t1           # registradores em mscratch

    # Seta o MPP com o priv Usuario
    li   t2, 0x1800             # Limpa os bits 11 e 12 (MPP)
    csrc mstatus, t2            # do registrador mstatus

    la t0, idle                 # Grava o endereço do rótulo idle
    csrw mepc, t0               # no registrador mepc
    mret                        # PC <= MEPC; MIE <= MPIE; Muda modo para MPP

idle:
    wfi
    j idle

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
    li a2, 7                # a2 = timer interrupt
    beq a1, a2, MTI_handler # se for MTI salta pro handler

    j return                # se nao retorna

MEI_handler:
    li a1,0x80001000
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

MTI_handler:
    li a1,0x80001000
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
