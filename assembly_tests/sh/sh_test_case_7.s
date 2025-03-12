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
    li   t4, 0        # Fail: t4 = 0 (if store incorrect)
    .word 0           # Stop the simulator
    li   t4, 1        # Pass: t4 = 1 (if store correct)
    .word 0           # Stop the simulator
