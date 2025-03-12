.section .data
.align 2
memory_location: .word 0x0F0F0F0F  # Memory location 0x0

.section .text
.align 2
.globl	_start

_start:
    li   t1, 0           # rs1 = 0
    la   t2, memory_location # Load address of memory_location into t2
    lw   t0, 0(t2)       # Load word from memory_location + 0 into t0
    li   t2, 0x0F0F0F0F  # Expected result
    beq  t0, t2, pass    # Branch to pass if t0 == t2
    li   t4, 0           # Fail: t4 = 0 (if load incorrect)
    .word 0              # Stop the simulator
pass:
    li   t4, 1           # Pass: t4 = 1 (if load correct)
    .word 0              # Stop the simulator
