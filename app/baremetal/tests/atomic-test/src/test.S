# Atomicity test, run with the simulated second hart: make HART1=1 (sim/AtomicHart.sv).
# Both harts increment one counter, alternating AMOADD and LR/SC retry loops.
# Printed (0x80002000), one per line:
#   counter (N + HART_N), SC retries on the counter, failed SCs on scratch (4),
#   SC on a private word (0), SC without reservation (1), and 1 if all is right.

.equ BASE,   0xE000          # shared words, see sim/AtomicHart.sv
.equ N,      200             # increments done by RS5
.equ HART_N, 200             # increments done by AtomicHart (its ITERATIONS)
.equ PRINT,  0x80002000

.section .init
.global _start
_start:
    csrw    mstatus, zero
    csrw    mie, zero
    csrw    mip, zero
    li      sp, MEM_SIZE
    jal     main
.end:
    li      t0, 0x80000000
    sw      zero, 0(t0)      # End simulation
    j       .end

.section .text
main:
    li      s0, BASE
    li      t6, PRINT
    li      t0, 1
    sw      t0, 0(s0)        # go

    li      s1, 0            # SC retries on the counter
    li      s2, 0            # iteration
    addi    t2, s0, 8        # &counter
inc:
    andi    t0, s2, 1
    bnez    t0, inc_lrsc
    li      t1, 1
    amoadd.w zero, t1, (t2)
    j       inc_next
inc_lrsc:
    lr.w    t3, (t2)
    addi    t3, t3, 1
    sc.w    t4, t3, (t2)
    beqz    t4, inc_next
    addi    s1, s1, 1
    j       inc_lrsc
inc_next:
    addi    s2, s2, 1
    li      t0, N
    blt     s2, t0, inc

wait_hart:
    lw      t0, 4(s0)
    beqz    t0, wait_hart

    lw      a0, 8(s0)
    sw      a0, 0(t6)        # counter
    sw      s1, 0(t6)        # SC retries

    # The hart now stores to scratch: every SC after a long wait must fail
    li      s3, 0
    li      s4, 4
    addi    t2, s0, 12       # &scratch
scratch:
    lr.w    t3, (t2)
    li      t5, 100
delay:
    addi    t5, t5, -1
    bnez    t5, delay
    sc.w    t4, t3, (t2)
    add     s3, s3, t4
    addi    s4, s4, -1
    bnez    s4, scratch
    li      t0, 1
    sw      t0, 16(s0)       # stop the hart
    sw      s3, 0(t6)        # failed SCs on scratch

    # A private word: LR then SC succeeds, a second SC has no reservation
    addi    t2, s0, 20
    lr.w    t3, (t2)
    sc.w    s5, t3, (t2)
    sw      s5, 0(t6)
    sc.w    s6, t3, (t2)
    sw      s6, 0(t6)

    li      t0, N + HART_N
    xor     a1, a0, t0       # 0 if the counter is right
    addi    t0, s3, -4
    or      a1, a1, t0       # 0 if all scratch SCs failed
    or      a1, a1, s5       # 0 if the private SC succeeded
    xori    t0, s6, 1
    or      a1, a1, t0       # 0 if the second SC failed
    seqz    a1, a1
    sw      a1, 0(t6)        # 1: pass
    ret
