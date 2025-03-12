.section .text
.align 2
.globl	_start

_start:
    li   t0, 0x7FFFFFFF # rs1 = 0x7FFFFFFF
    addi t2, t0, 1    # rd = rs1 + 1
    li   t3, 0x80000000 # Expected result = 0x80000000
    beq  t2, t3, pass  # Check if rd == expected result
    li   t4, 0        # Fail: t4 = 0
    .word 0           # Stop the simulator
pass:
    li   t4, 1        # Pass: t4 = 1
    .word 0           # Stop the simulator
