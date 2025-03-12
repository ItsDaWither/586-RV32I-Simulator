.section .data
.align 2
memory_location: .half 0xFFFF  # Memory location 0x6020

.section .text
.align 2
.globl	_start

_start:
    la   t1, memory_location # rs1 = address of memory_location
    lhu  t0, 0(t1)       # Load halfword from memory_location + 0 into t0
    li   t4, 0        # Fail: t4 = 0 (if load incorrect)
    .word 0           # Stop the simulator
    li   t4, 1        # Pass: t4 = 1 (if load correct)
    .word 0           # Stop the simulator
