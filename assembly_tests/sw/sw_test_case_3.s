.section .data
.align 2
memory_location: .word 0 # Memory location 0x3000

.section .text
.align 2
.globl	_start

_start:
    la   t1, memory_location # rs1 = address of memory_location
    li   t0, 0x55AA55AA  # rs2 = 0x55AA55AA
    sw   t0, 0(t1)       # Store word from rs2 into memory_location + 0
    lw   t2, 0(t1)       # Load the word back from memory
    li   t3, 0x55AA55AA  # Expected result
    beq  t2, t3, pass    # Branch to pass if t2 == t3
    li   t4, 0           # Fail: t4 = 0 (if store incorrect)
    .word 0              # Stop the simulator
pass:
    li   t4, 1           # Pass: t4 = 1 (if store correct)
    .word 0              # Stop the simulator
