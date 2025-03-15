.section .text
.align 2
.globl	_start

_start:
    li   t0, 30       # rs1 = 30
    li   t1, 31       # rs2 = 31
    bne  t0, t1, branch_taken # Branch to branch_taken if rs1 != rs2
    li   t4, 0        # Fail: t4 = 0 (if branch not taken)
    .word 0           # Stop the simulator
branch_taken:
    li   t4, 1        # Pass: t4 = 1 (if branch taken)
    .word 0           # Stop the simulator
