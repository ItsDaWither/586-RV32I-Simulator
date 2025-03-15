# Test Plan for AUIPC Instruction

## Instruction: AUIPC (Add Upper Immediate to PC)

### Description

The AUIPC (Add Upper Immediate to PC) instruction adds a 20-bit upper immediate to the program counter (PC) and places the result in the destination register. The immediate is left-shifted by 12 bits before being added to the PC.

## Test Cases

1.  **Add a positive immediate to the PC**
    *   Objective: Verify that AUIPC correctly adds a positive immediate to the PC.
    *   Registers: t2 = any
    *   Immediate: imm = 0x10000
    *   Description: The PC should be incremented by 0x10000000.
    *   Expected Result: t2 = PC + (0x10000 << 12)

2.  **Add a zero immediate to the PC**

    *   Objective: Verify that AUIPC correctly adds a zero immediate to the PC.
    *   Registers: t2 = any
    *   Immediate: imm = 0x0
    *   Description: The PC should remain unchanged.
    *   Expected Result: t2 = PC + (0x0 << 12)
