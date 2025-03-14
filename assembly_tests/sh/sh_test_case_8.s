.section .data
.align 2
memory_location: .half 0 # Memory location 0x6020

.section .text
.align 2
.globl	_start

_start:
    la   t1, memory_location # rs1 = address of memory_location
    li   t0, 0x00000000  # rs2 = 0x00000000
    sh   t0, 0(t1)       # Store halfword from rs2 into memory_location + 0
    lhu  t2, 0(t1)       # Load the halfword back from memory
    li   t3, 0x0000      # Expected result
    beq  t2, t3, pass    # Branch to pass if t2 == t3
    li   t4, 0          # Fail: t4 = 0
    .word 0           # Stop the simulator
pass:
    li t4, 1        # Pass: t = 1
    .word 0           # Stop the simulator
