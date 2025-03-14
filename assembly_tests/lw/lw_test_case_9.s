.section .data
.align 2
memory_location: .word 0x08080808  # Memory location 0x7040

.section .text
.align 2
.globl	_start

_start:
    la   t1, memory_location # rs1 = address of memory_location
    lw   t0, 0(t1)       # Load word from memory_location + 0 into t0
    li   t2, 0x08080808       # Load expected result into t2
    beq  t0, t2, pass    # Branch to pass if t0 is 0x08080808
    li   t4, 0          # Fail: t4 = 0
    .word 0           # Stop the simulator
pass:
    li t4, 1        # Pass: t = 1
    .word 0           # Stop the simulator
