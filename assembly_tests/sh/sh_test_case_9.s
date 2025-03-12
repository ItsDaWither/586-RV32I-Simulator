.section .data
.align 2
memory_location: .half 0 # Memory location 0x7040

.section .text
.align 2
.globl	_start

_start:
    la   t1, memory_location # rs1 = address of memory_location
    li   t0, 0xFFFFFFFF  # rs2 = 0xFFFFFFFF
    sh   t0, 0(t1)       # Store halfword from rs2 into memory_location + 0
    li   t4, 0        # Fail: t4 = 0 (if store incorrect)
    .word 0           # Stop the simulator
    li   t4, 1        # Pass: t4 = 1 (if store correct)
    .word 0           # Stop the simulator
