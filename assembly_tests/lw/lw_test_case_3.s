.section .data
.align 2
memory_location: .word 0x55AA55AA  # Memory location 0x3000

.section .text
.align 2
.globl	_start

_start:
    la   t1, memory_location # rs1 = address of memory_location
    lw   t0, 0(t1)       # Load word from memory_location + 0 into t0
    li   t2, 0x55AA55AA  # Expected result
    beq  t0, t2, pass    # Branch to pass if t0 == t2
    li   t4, 0           # Fail: t4 = 0 (if load incorrect)
    .word 0              # Stop the simulator
pass:
    li   t4, 1           # Pass: t4 = 1 (if load correct)
    .word 0              # Stop the simulator
