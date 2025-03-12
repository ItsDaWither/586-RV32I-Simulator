.section .text
.align 2
.globl	_start

_start:
    li   t0, 1        # rs1 = 1
    addi t2, t0, 2047 # rd = rs1 + 2047
    li   t3, 2048     # Expected result = 2048
    beq  t2, t3, pass  # Check if rd == expected result
    li   t4, 0        # Fail: t4 = 0
    .word 0           # Stop the simulator
pass:
    li   t4, 1        # Pass: t4 = 1
    .word 0           # Stop the simulator
