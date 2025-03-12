.section .text
.align 2
.globl	_start

_start:
    li   t0, 0x7FFFFFFF  # rs1 = 0x7FFFFFFF (INT_MAX)
    li   t1, 0x80000001  # rs2 = 0x80000001 (INT_MIN + 1)
    sub  t2, t0, t1     # rd = rs1 - rs2
    li   t3, 0xFFFFFFFE  # Expected result
    beq  t2, t3, Pass    # Branch to Pass if t2 == t3
Fail:
    li   t4, 0        # Fail: t4 = 0 (if load incorrect)
    .word 0           # Stop the simulator
Pass:
    li   t4, 1        # Pass: t4 = 1 (if load correct)
    .word 0           # Stop the simulator
