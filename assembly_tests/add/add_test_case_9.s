.section .text
.align 2
.globl	_start

_start:
    li   t0, 0x7FFFFFFF # rs1 = 0x7FFFFFFF (INT_MAX)
    li   t1, 0x80000001 # rs2 = 0x80000001 (INT_MIN + 1)
    add  t2, t0, t1   # rd = rs1 + rs2
    li   t3, 0x00000000 # Expected result = 0x00000000 (INT_MAX + INT_MIN + 1 = 0)
    beq  t2, t3, pass  # Check if rd == expected result
    li   t4, 0        # Fail: t4 = 0
    .word 0           # Stop the simulator
pass:
    li   t4, 1        # Pass: t4 = 1
    .word 0           # Stop the simulator
