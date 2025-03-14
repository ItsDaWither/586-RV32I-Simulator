.section .data
.align 2
memory_location: .word 0xC0C0C0C0  # Memory location 0x100

.section .text
.align 2
.globl	_start

_start:
    li   t1, 0           # rs1 = 0
    la   t2, memory_location # Load address of memory_location into t2
    lw   t0, 0(t2)       # Load word from memory_location + 0 into t0
    li   t2, 0xC0C0C0C0       # Load expected result into t2
    beq  t0, t2, pass    # Branch to pass if t0 is 0xC0C0C0C0
    li   t4, 0          # Fail: t4 = 0
    .word 0           # Stop the simulator
pass:
    li t4, 1        # Pass: t = 1
    .word 0           # Stop the simulator
