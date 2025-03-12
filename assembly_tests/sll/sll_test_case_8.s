.section .text
.align 2
.globl	_start

_start:
    li   t0, 0x00000001  # rs1 = 0x00000001
    li   t1, 5           # rs2 = 5
    li   t3, 10          # rshift = 10
    sll  t5, t0, t1      # rtemp = rs1 << rs2
    sll  t2, t5, t3      # rd = rtemp << rshift
    li   t3, 0x00008000 # Expected result
    beq  t2, t3, Pass    # Branch to Pass if t2 == t3
Fail:
    li   t4, 0        # Fail: t4 = 0 (if load incorrect)
    .word 0           # Stop the simulator
Pass:
    li   t4, 1        # Pass: t4 = 1 (if load correct)
    .word 0           # Stop the simulator
