.section .text
.align 2
.globl	_start

_start:
    li   t0, 0x0       # rs1 = 0x0
    li   t1, 0x1       # rs2 = 0x1
    bltu  t0, t1, branch_taken # Branch to branch_taken if rs1 < rs2
    li   t4, 0        # Fail: t4 = 0 (if branch not taken)
    .word 0           # Stop the simulator
branch_taken:
    li   t4, 1        # Pass: t4 = 1 (if branch taken)
    .word 0           # Stop the simulator
