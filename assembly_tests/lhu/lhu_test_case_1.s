.section .data
.align 2
memory_location: .half 0xCDEF  # Memory location 0x1010

.section .text
.align 2
.globl	_start

_start:
    la   t1, memory_location # rs1 = address of memory_location
    lhu  t0, 0(t1)       # Load halfword from memory_location + 0 into t0
    li   t2, 0x0000CDEF       # Load expected result into t2
    beq  t0, t2, pass    # Branch to pass if t0 is 0x0000CDEF
    li   t4, 0          # Fail: t4 = 0
    .word 0           # Stop the simulator
pass:
    li t4, 1        # Pass: t = 1
    .word 0           # Stop the simulator
