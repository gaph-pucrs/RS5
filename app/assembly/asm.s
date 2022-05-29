.section .init
.align 4

.globl boot

    # Configura o tratador de interrupções
    la t0, trap_handler         # Grava o endereço do rótulo int_handler
    csrw mtvec, t0              # no registrador mtvec

    # Habilita Interrupções Global
    li t1, 0x80                 # Seta o bit 7 (MPIE)
    csrs mstatus, t1            # do registrador mstatus

    # Habilita Interrupções Externas
    li t2, 0x800                # Seta o bit 11 (MEIE)
    csrs mie, t2                # do registrador mie

    # Ajusta o mscratch
    la t1, reg_buffer           # Coloca o endereço do buffer para salvar
    csrw mscratch, t1           # registradores em mscratch

    # Muda para o Modo de usuário
    csrr t1, mstatus            # Seta os bits 11 e 12 (MPP)
    li t2, ~0x1800              # do registrador mstatus
    and t1, t1, t2              # com o valor 00
    csrw mstatus, t1

    la t0, main                 # Grava o endereço do rótulo main
    csrw mepc, t0               # no registrador mepc
    mret                        # PC <= MEPC; MIE <= MPIE; Muda modo para MPP

main:

    li      t0, 0x12345678
	li		t1, 0xEDCBA987
    li      a0, 0x98765432

	csrrw	t2, misa, zero      # read misa and write zero to it

	csrrw	t2, mscratch, t0    # Write 12345678 to mtvec
	csrrs	t2, mscratch, t1    # Set to '1
	csrrc	t2, mscratch, t1    # Unset the bits previously set

    ecall

	jal		main


trap_handler:
    csrrw a0, mscratch, a0
    csrr  a1, mcause
    
    # Ajustando MEPC para retornar de uma chamada de sistema
    csrr a1, mepc # carrega endereço de retorno
    
    # (endereço da instrução que invocou a syscall)
    addi a1, a1, 4 # soma 4 no endereço de retorno
    
    # (para retornar após a ecall)
    csrw mepc, a1 # armazena endereço de retorno de volta no mepc

    csrrw a0, mscratch, a0        
    mret


.section .rodata		# Constants
.align 4
.globl _has_priv	# Set available for 'extern'
_has_priv: .4byte 1
reg_buffer: .4byte 0

