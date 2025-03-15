.section .text
.align 2
.globl	_start

_start:
    li   t0, 0xFFFFFFFF       # rs1 = 0xFFFFFFFF
    li   t1, 0x7FFFFFFF       # rs2 = 0x7FFFFFFF
    bgeu  t0, t1, branch_taken # Branch to branch_taken if rs1 >= rs2
    li   t4, 0        # Fail: t4 = 0 (if branch not taken)
    .word 0           # Stop the simulator
branch_taken:
    li   t4, 1        # Pass: t4 = 1 (if branch taken)
    .word 0           # Stop the simulator
