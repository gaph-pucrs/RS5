.section .text.init
.global _entry
_entry:

    # Configura o tratador de interrupções
    la t0, MEI_handler         # Grava o endereço do rótulo trap_handler
    csrw mtvec, t0              # no registrador mtvec

    li t3, 0xffffffff           # Habilita todas as interrupções externas
    la t4, 0x70000008           # endereço do registrador ie
    sw t3, 0(t4)

    # Habilita Interrupções Global
    li t1, 0x80                 # Seta o bit 7 (MPIE)
    csrs mstatus, t1            # do registrador mstatus


    # Habilita Interrupções Externas
    li t2, 0x800                # Seta os bits 11, 7 e 3 (MEIE, MTIE e MSIE)
    csrs mie, t2                # do registrador mie

    la t0, loop                 # Grava o endereço do rótulo main
    csrw mepc, t0               # no registrador mepc
    mret
loop:
    j loop

MEI_handler:

    li t1, 0x80005000 # uart_rx
    lw t2, 0(t1)      # byte recebido
   
    li a1,0x80001000 # uart_tx
    sw t2,0(a1)      # byte recebido

    j return
return:
    mret

.end:
	li	s10, 0x80000000		# this will interrupt the simulation (assertion)
	sw	zero, 0(s10)
	jal zero, .end