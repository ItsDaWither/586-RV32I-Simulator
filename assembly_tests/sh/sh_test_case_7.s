.section .data
.align 2
memory_location: .half 0 # Memory location 0x0

.section .text
.align 2
.globl	_start

_start:
    li   t1, 0           # rs1 = 0
    la   t2, memory_location # Load address of memory_location into t2
    li   t0, 0x0F0F0F0F  # rs2 = 0x0F0F0F0F
    sh   t0, 0(t2)       # Store halfword from rs2 into memory_location + 0
    lh   t3, 0(t2)       # Load the halfword back from memory
    li   t4, 0x0F0F      # Expected result
    beq  t3, t4, pass    # Branch to pass if t3 == t4
    li   t5, 0          # Fail: t5 = 0
    .word 0           # Stop the simulator
pass:
    li   t5, 1          # Pass: t5 = 1
    .word 0           # Stop the simulator
