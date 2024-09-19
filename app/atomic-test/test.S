
.global _entry

_entry:

	la t0, test
	li t1, 20

	amoadd.w t2, t1, 0(t0)

	lw t3, 0(t0)

.data

test: .word 30