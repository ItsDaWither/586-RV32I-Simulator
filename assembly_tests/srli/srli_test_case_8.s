.section .text
.align 2
.globl	_start

_start:
    li   t0, 0xFFFFFFFF  # rs1 = 0xFFFFFFFF
    srli t1, t0, 5     # rtemp = rs1 >> imm1
    srli t2, t1, 10    # rd = rtemp >> imm2
    li   t3, 0x0001FFFF  # Expected result
    beq  t2, t3, Pass    # Branch to Pass if t2 == t3
Fail:
    li   t4, 0        # Fail: t4 = 0 (if load incorrect)
    .word 0           # Stop the simulator
Pass:
    li   t4, 1        # Pass: t4 = 1 (if load correct)
    .word 0           # Stop the simulator
