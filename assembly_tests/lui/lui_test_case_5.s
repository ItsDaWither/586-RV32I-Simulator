.section .text
.align 2
.globl	_start

_start:
    lui  x1, 0xABCDE     # rd = 0xABCDE000
    li   t1, 0xABCDE000
    beq  x1, t1, pass
fail:
    li   t4, 0        # Fail: t4 = 0 (if load incorrect)
    .word 0           # Stop the simulator
pass:
    li   t4, 1        # Pass: t4 = 1 (if load correct)
    .word 0           # Stop the simulator
