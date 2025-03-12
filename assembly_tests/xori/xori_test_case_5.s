.section .text
.align 2
.globl	_start

_start:
    li   t0, 0x00000555  # rs1 = 0xAAAAAAAA
    xori t2, t0, 0x555   # rd = rs1 ^ imm
    xori t2, t2, 0x0     # rd = rs1 ^ imm
    li   t3, 0x0         # Expected result
    beq  t2, t3, Pass    # Branch to Pass if t2 == t3
Fail:
    li   t4, 0        # Fail: t4 = 0 (if load incorrect)
    .word 0           # Stop the simulator
Pass:
    li   t4, 1        # Pass: t4 = 1 (if load correct)
    .word 0           # Stop the simulator
