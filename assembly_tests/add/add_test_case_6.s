.section .text
.align 2
.globl	_start

_start:
    li   t0, 0x7FFFFFFF # rs1 = 0x7FFFFFFF
    li   t1, 0x00000000 # rs2 = 0x00000000
    add  t2, t0, t1   # rd = rs1 + rs2
    li   t3, 0x7FFFFFFF # Expected result = 0x7FFFFFFF
    beq  t2, t3, pass  # Check if rd == expected result
    li   t4, 0        # Fail: t4 = 0
    .word 0           # Stop the simulator
pass:
    li   t4, 1        # Pass: t4 = 1
    .word 0           # Stop the simulator
