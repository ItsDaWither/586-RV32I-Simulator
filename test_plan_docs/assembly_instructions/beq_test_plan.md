# Test Plan for BEQ Instruction

## Instruction: BEQ (Branch if Equal)

### Description
The BEQ (branch if equal) instruction branches to a target address if the values in registers rs1 and rs2 are equal. The target address is calculated by adding a signed 12-bit offset to the PC.

### Test Cases

1.  **Registers Equal - Branch Taken (Positive Offset):**
    -   **Purpose:** Verify branch is taken when registers are equal and offset is positive.
    -   **Registers:** rs1 = 10, rs2 = 10
    -   **Offset:** offset = 0x20 (represented as 12-bit signed offset in assembly)
    -   **Expected Result:** Branch Taken

2.  **Registers Equal - Branch Taken (Negative Offset):**
    -   **Purpose:** Verify branch is taken when registers are equal and offset is negative.
    -   **Registers:** rs1 = 20, rs2 = 20
    -   **Offset:** offset = -0x20 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Expected Result:** Branch Taken

3.  **Registers Equal - Branch Taken (Zero Offset):**
    -   **Purpose:** Verify branch is taken when registers are equal and offset is zero.
    -   **Registers:** rs1 = 30, rs2 = 30
    -   **Offset:** offset = 0x0
    -   **Expected Result:** Branch Taken

4.  **Registers Not Equal - Branch Not Taken:**
    -   **Purpose:** Verify branch is not taken when registers are not equal.
    -   **Registers:** rs1 = 10, rs2 = 11
    -   **Offset:** offset = 0x100
    -   **Expected Result:** Branch Not Taken
