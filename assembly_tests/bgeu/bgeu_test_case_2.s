.section .text
.align 2
.globl	_start

_start:
    j test_procedure
branch_taken:
    li   t4, 1        # Pass: t4 = 1 (if branch taken)
    .word 0           # Stop the simulator
test_procedure:
    li   t0, 0              # rs2 = 0
    li   t1, 0xFFFFFFF0     # rs1 = 0xFFFFFFF0
    bgeu  t1, t0, branch_taken # Branch to branch_taken if rs1 >= rs2
    li   t4, 0        # Fail: t4 = 0 (if branch not taken)
    .word 0           # Stop the simulator
