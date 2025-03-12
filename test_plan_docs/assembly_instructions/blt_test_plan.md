# Test Plan for BLT Instruction

## Instruction: BLT (Branch if Less Than)

### Description
The BLT (branch if less than) instruction branches to a target address if the signed value in register rs1 is less than the signed value in register rs2. The target address is calculated by adding a signed 12-bit offset to the PC.

### Test Cases

1.  **rs1 < rs2 - Branch Taken (Positive Offset):**
    -   **Purpose:** Verify branch is taken when rs1 < rs2 (signed) and offset is positive.
    -   **Registers:** rs1 = 10, rs2 = 20, PC = 0x1000
    -   **Offset:** offset = 0x20 (represented as 12-bit signed offset in assembly)
    -   **Expected Result:** PC = 0x1000 + 0x20 = 0x1020 (PC is updated to branch target)

2.  **rs1 < rs2 - Branch Taken (Negative Offset):**
    -   **Purpose:** Verify branch is taken when rs1 < rs2 (signed) and offset is negative.
    -   **Registers:** rs1 = -10, rs2 = 0, PC = 0x2000
    -   **Offset:** offset = -0x20 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Expected Result:** PC = 0x2000 - 0x20 = 0x1FE0 (PC is updated to branch target)

3.  **rs1 < rs2 - Branch Taken (Zero Offset):**
    -   **Purpose:** Verify branch is taken when rs1 < rs2 (signed) and offset is zero.
    -   **Registers:** rs1 = -20, rs2 = -10, PC = 0x3000
    -   **Offset:** offset = 0x0
    -   **Expected Result:** PC = 0x3000 (PC is updated to branch target, effectively staying at the same location)

4.  **rs1 >= rs2 - Branch Not Taken:**
    -   **Purpose:** Verify branch is not taken when rs1 >= rs2 (signed).
    -   **Registers:** rs1 = 20, rs2 = 10, PC = 0x4000
    -   **Offset:** offset = 0x100
    -   **Expected Result:** PC = 0x4000 + 4 = 0x4004 (PC increments to the next instruction)

5.  **rs1 == rs2 - Branch Not Taken:**
    -   **Purpose:** Verify branch is not taken when rs1 == rs2 (signed).
    -   **Registers:** rs1 = 10, rs2 = 10, PC = 0x5000
    -   **Offset:** offset = 0x100
    -   **Expected Result:** PC = 0x5000 + 4 = 0x5004 (PC increments to the next instruction)

6. **Large negative and positive numbers:**
    -   **Purpose:** Verify correct signed comparison with large negative and positive numbers.
    -   **Registers:** rs1 = 0x80000000 (INT_MIN), rs2 = 0x7FFFFFFF (INT_MAX), PC = 0x8000
    -   **Offset:** offset = 0x40
    -   **Expected Result:** PC = 0x8000 + 0x40 = 0x8040 (PC is updated to branch target because INT_MIN < INT_MAX)
