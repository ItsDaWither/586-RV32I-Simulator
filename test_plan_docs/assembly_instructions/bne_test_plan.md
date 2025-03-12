# Test Plan for BNE Instruction

## Instruction: BNE (Branch if Not Equal)

### Description
The BNE (branch if not equal) instruction branches to a target address if the values in registers rs1 and rs2 are not equal. The target address is calculated by adding a signed 12-bit offset to the PC.

### Test Cases

1.  **Registers Not Equal - Branch Taken (Positive Offset):**
    -   **Purpose:** Verify branch is taken when registers are not equal and offset is positive.
    -   **Registers:** rs1 = 10, rs2 = 11, PC = 0x1000
    -   **Offset:** offset = 0x20 (represented as 12-bit signed offset in assembly)
    -   **Expected Result:** PC = 0x1000 + 0x20 = 0x1020 (PC is updated to branch target)

2.  **Registers Not Equal - Branch Taken (Negative Offset):**
    -   **Purpose:** Verify branch is taken when registers are not equal and offset is negative.
    -   **Registers:** rs1 = 20, rs2 = 19, PC = 0x2000
    -   **Offset:** offset = -0x20 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Expected Result:** PC = 0x2000 - 0x20 = 0x1FE0 (PC is updated to branch target)

3.  **Registers Not Equal - Branch Taken (Zero Offset):**
    -   **Purpose:** Verify branch is taken when registers are not equal and offset is zero.
    -   **Registers:** rs1 = 30, rs2 = 31, PC = 0x3000
    -   **Offset:** offset = 0x0
    -   **Expected Result:** PC = 0x3000 (PC is updated to branch target, effectively staying at the same location)

4.  **Registers Equal - Branch Not Taken:**
    -   **Purpose:** Verify branch is not taken when registers are equal.
    -   **Registers:** rs1 = 10, rs2 = 10, PC = 0x4000
    -   **Offset:** offset = 0x100
    -   **Expected Result:** PC = 0x4000 + 4 = 0x4004 (PC increments to the next instruction)
