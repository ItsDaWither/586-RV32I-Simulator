.section .text
.align 2
.globl	_start

_start:
    li   t0, 10       # rs1 = 10
    addi t2, t0, 5    # rd = rs1 + 5
    li   t3, 15       # Expected result = 15
    beq  t2, t3, pass  # Check if rd == expected result
    li   t4, 0        # Fail: t4 = 0
    .word 0           # Stop the simulator
pass:
    li   t4, 1        # Pass: t4 = 1
    .word 0           # Stop the simulator
