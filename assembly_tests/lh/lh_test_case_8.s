.section .data
.align 2
memory_location: .half 0xF0F0

.section .text
.align 2
.globl	_start

_start:
    la   t1, memory_location # rs1 = address of memory_location
    lh   t0, 0(t1)       # Load halfword from memory_location + 0 into t0
    li   t2, 0xFFFFF0F0       # Load expected result into t2
    beq  t0, t2, pass    # Branch to pass if t0 is 0xFFFFF0F0
    li   t4, 0          # Fail: t4 = 0
    .word 0           # Stop the simulator
pass:
    li t4, 1        # Pass: t = 1
    .word 0           # Stop the simulator
