.section .text
.align 2
.globl	_start

_start:
    li   t0, 0x0000000F # rs1 = 0x0000000F
    andi t2, t0, 0x00000003   # rd = rs1 & 0x00000003
    li   t3, 0x00000003 # Expected result = 0x00000003
    beq  t2, t3, pass  # Check if rd == expected result
    li   t4, 0        # Fail: t4 = 0
    .word 0           # Stop the simulator
pass:
    li   t4, 1        # Pass: t4 = 1
    .word 0           # Stop the simulator
