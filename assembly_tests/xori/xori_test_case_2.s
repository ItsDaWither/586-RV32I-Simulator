.section .text
.align 2
.globl	_start

_start:
    li   t0, 0xABCDEF01  # rs1 = 0xABCDEF01
    xori t2, t0, 0x00000000 # rd = rs1 ^ imm
    li   t3, 0xABCDEF01  # Expected result
    beq  t2, t3, Pass    # Branch to Pass if t2 == t3
Fail:
    li   t4, 0        # Fail: t4 = 0 (if load incorrect)
    .word 0           # Stop the simulator
Pass:
    li   t4, 1        # Pass: t4 = 1 (if load correct)
    .word 0           # Stop the simulator
