# Test Plan for BLT Instruction

## Instruction: BLT (Branch if Less Than)

### Description
The BLT (branch if less than) instruction branches to a target address if the signed value in register rs1 is less than the signed value in register rs2. The target address is calculated by adding a signed 12-bit offset to the PC.

### Test Cases

1.  **rs1 < rs2 - Branch Taken (Positive Offset):**
    -   **Purpose:** Verify branch is taken when rs1 < rs2 (signed) and offset is positive.
    -   **Registers:** rs1 = 10, rs2 = 20
    -   **Offset:** offset = 0x20 (represented as 12-bit signed offset in assembly)
    -   **Expected Result:** Branch Taken

2.  **rs1 < rs2 - Branch Taken (Negative Offset):**
    -   **Purpose:** Verify branch is taken when rs1 < rs2 (signed) and offset is negative.
    -   **Registers:** rs1 = -10, rs2 = 0
    -   **Offset:** offset = -0x20 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Expected Result:** Branch Taken

3.  **rs1 < rs2 - Branch Taken (Zero Offset):**
    -   **Purpose:** Verify branch is taken when rs1 < rs2 (signed) and offset is zero.
    -   **Registers:** rs1 = -20, rs2 = -10
    -   **Offset:** offset = 0x0
    -   **Expected Result:** Branch Taken

4.  **rs1 >= rs2 - Branch Not Taken:**
    -   **Purpose:** Verify branch is not taken when rs1 >= rs2 (signed).
    -   **Registers:** rs1 = 20, rs2 = 10
    -   **Offset:** offset = 0x100
    -   **Expected Result:** Branch Not Taken

5.  **rs1 == rs2 - Branch Not Taken:**
    -   **Purpose:** Verify branch is not taken when rs1 == rs2 (signed).
    -   **Registers:** rs1 = 10, rs2 = 10
    -   **Offset:** offset = 0x100
    -   **Expected Result:** Branch Not Taken

6. **Large negative and positive numbers:**
    -   **Purpose:** Verify correct signed comparison with large negative and positive numbers.
    -   **Registers:** rs1 = 0x80000000 (INT_MIN), rs2 = 0x7FFFFFFF (INT_MAX)
    -   **Offset:** offset = 0x40
    -   **Expected Result:** Branch Taken
