.section .text
.align 2
.globl	_start

_start:
    li   t0, 10       # rs1 = 10
    li   t1, -5       # rs2 = -5
    add  t2, t0, t1   # rd = rs1 + rs2
    li   t3, 5        # Expected result = 5
    beq  t2, t3, pass  # Check if rd == expected result
    li   t4, 0        # Fail: t4 = 0
    .word 0           # Stop the simulator
pass:
    li   t4, 1        # Pass: t4 = 1
    .word 0           # Stop the simulator
