.section .data
.align 2
memory_location: .byte 0

.section .text
.align 2
.globl	_start

_start:
    li   t1, 0           # rs1 = 0
    la   t2, memory_location # Load address of memory_location into t2
    li   t0, 0xC0C0C0C0  # rs2 = 0xC0C0C0C0
    sb   t0, 0(t2)       # Store byte from rs2 into memory_location + 0
    lbu  t3, 0(t2)       # Load the byte back from memory
    li   t5, 0xC0        # Expected result
    beq  t3, t5, pass    # Branch to pass if t3 == t4
    li   t4, 0           # Fail: t5 = 0 (if store incorrect)
    .word 0              # Stop the simulator
pass:
    li   t4, 1           # Pass: t5 = 1 (if store correct)
    .word 0              # Stop the simulator
