.section .data
.align 2
memory_location: .byte 0xC3  # Memory location 0x100

.section .text
.align 2
.globl	_start

_start:
    li   t1, 0           # rs1 = 0
    la   t2, memory_location # Load address of memory_location into t2
    lbu  t0, 0(t2)       # Load byte from memory_location + 0 into t0
    li   t2, 0x000000C3  # Expected result
    beq  t0, t2, pass    # Branch to pass if t0 == t2
    li   t4, 0           # Fail: t4 = 0 (if load incorrect)
    .word 0              # Stop the simulator
pass:
    li   t4, 1           # Pass: t4 = 1 (if load correct)
    .word 0              # Stop the simulator
