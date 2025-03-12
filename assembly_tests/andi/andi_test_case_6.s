.section .text
.align 2
.globl	_start

_start:
    li   t0, 0x00001FFF # rs1 = 0x00001FFF
    andi t2, t0, 2047   # rd = rs1 & 2047
    li   t3, 0x000007FF # Expected result = 0x000007FF
    beq  t2, t3, pass  # Check if rd == expected result
    li   t4, 0        # Fail: t4 = 0
    .word 0           # Stop the simulator
pass:
    li   t4, 1        # Pass: t4 = 1
    .word 0           # Stop the simulator
