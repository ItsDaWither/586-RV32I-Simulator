.section .text
.align 2
.globl	_start

_start:
    lui  t0, 0x12345     # rd = 0x12345000
    li   t1, 0x12345000
    beq  t0, t1, pass
fail:
    li   t4, 0        # Fail: t4 = 0 (if load incorrect)
    .word 0           # Stop the simulator
pass:
    li   t4, 1        # Pass: t4 = 1 (if load correct)
    .word 0           # Stop the simulator
