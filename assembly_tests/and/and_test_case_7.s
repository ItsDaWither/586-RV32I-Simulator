.section .text
.align 2
.globl	_start

_start:
    li   t0, 0xF0F0F0F0 # rs1 = 0xF0F0F0F0
    li   t1, 0xABABABAB # rs2 = 0xABABABAB
    and  t2, t0, t1   # rd = rs1 & rs2
    li   t3, 0xA0A0A0A0 # Expected result = 0xA0A0A0A0
    beq  t2, t3, pass  # Check if rd == expected result
    li   t4, 0        # Fail: t4 = 0
    .word 0           # Stop the simulator
pass:
    li   t4, 1        # Pass: t4 = 1
    .word 0           # Stop the simulator
