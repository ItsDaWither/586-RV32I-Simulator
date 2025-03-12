.section .text
.align 2
.globl	_start

_start:
    li   t0, 0x80000000 # rs1 = 0x80000000
    li   t1, 0xFFFFFFFF # rs2 = 0xFFFFFFFF (-1 in signed)
    add  t2, t0, t1   # rd = rs1 + rs2
    li   t3, 0x7FFFFFFF # Expected result = 0x7FFFFFFF
    beq  t2, t3, pass  # Check if rd == expected result
    li   t4, 0        # Fail: t4 = 0
    .word 0           # Stop the simulator
pass:
    li   t4, 1        # Pass: t4 = 1
    .word 0           # Stop the simulator
