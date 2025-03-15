.section .text
.align 2
.globl	_start

# auipc test assume start address is 0x0 (enforced by linker flags automation)
_start:
    auipc t2, 0x10000    # rd = pc + (imm << 12)
    li t3, 1             # t3 = 16
    slli t3, t3, 28      # t3 = 0x10000000
    beq  t2, t3, Pass    # Branch to Pass if t2 == t3
Fail:
    li   t4, 0        # Fail: t4 = 0 (if load incorrect)
    .word 0           # Stop the simulator
Pass:
    li   t4, 1        # Pass: t4 = 1 (if load correct)
    .word 0           # Stop the simulator
