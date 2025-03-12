.section .text
.align 2
.globl	_start

_start:
    li   t0, 0xFFFFFFFF # rs1 = 0xFFFFFFFF
    andi t2, t0, -2048   # rd = rs1 & -2048
    li   t3, 0xFFFFF800 # Expected result = 0xFFFFF800
    beq  t2, t3, pass  # Check if rd == expected result
    li   t4, 0        # Fail: t4 = 0
    .word 0           # Stop the simulator
pass:
    li   t4, 1        # Pass: t4 = 1
    .word 0           # Stop the simulator
