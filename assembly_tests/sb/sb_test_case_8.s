.section .data
.align 2
memory_location: .byte 0 # Memory location 0x6020

.section .text
.align 2
.globl	_start

_start:
    la   t1, memory_location # rs1 = address of memory_location
    li   t0, 0x00000000  # rs2 = 0x00000000
    sb   t0, 0(t1)       # Store byte from rs2 into memory_location + 0
    lb   t2, 0(t1)       # Load the byte back from memory
    li   t3, 0x00        # Expected result
    beq  t2, t3, pass    # Branch to pass if t2 == t3
    li   t4, 0           # Fail: t4 = 0 (if store incorrect)
    .word 0              # Stop the simulator
pass:
    li   t4, 1           # Pass: t4 = 1 (if store correct)
    .word 0              # Stop the simulator
