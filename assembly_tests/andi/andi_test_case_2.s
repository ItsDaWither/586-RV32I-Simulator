.section .text
.align 2
.globl	_start

_start:
    li   t0, 0xABCDEF01 # rs1 = 0xABCDEF01
    andi t2, t0, 0x00000000   # rd = rs1 & 0x00000000
    li   t3, 0x00000000 # Expected result = 0x00000000
    beq  t2, t3, pass  # Check if rd == expected result
    li   t4, 0        # Fail: t4 = 0
    .word 0           # Stop the simulator
pass:
    li   t4, 1        # Pass: t4 = 1
    .word 0           # Stop the simulator
