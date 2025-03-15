.section .data
.align 2
memory_location: .byte 0x12

.section .text
.align 2
.globl	_start

_start:
    la   t1, memory_location # rs1 = address of memory_location
    lbu  t0, 0(t1)       # Load byte from memory_location + 0 into t0
    li   t2, 0x00000012  # Expected result
    beq  t0, t2, pass    # Branch to pass if t0 == t2
    li   t4, 0           # Fail: t4 = 0 (if load incorrect)
    .word 0              # Stop the simulator
pass:
    li   t4, 1           # Pass: t4 = 1 (if load correct)
    .word 0              # Stop the simulator
