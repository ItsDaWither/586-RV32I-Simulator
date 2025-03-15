.section .data
.align 2
memory_location: .half 0

.section .text
.align 2
.globl	_start

_start:
    la   t1, memory_location # rs1 = address of memory_location
    li   t0, 0xABCDEF01  # rs2 = 0xABCDEF01
    sh   t0, 0(t1)       # Store halfword from rs2 into memory_location + 0
    lhu  t2, 0(t1)       # Load the halfword back from memory
    li   t3, 0xEF01      # Expected result
    beq  t2, t3, pass    # Branch to pass if t2 == t3
    li   t4, 0           # Fail: t4 = 0 (if store incorrect)
    .word 0              # Stop the simulator
pass:
    li   t4, 1           # Pass: t4 = 1 (if store correct)
    .word 0              # Stop the simulator
