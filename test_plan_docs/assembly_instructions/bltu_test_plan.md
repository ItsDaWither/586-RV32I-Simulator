# Test Plan for BLTU Instruction

## Instruction: BLTU (Branch if Less Than Unsigned)

### Description
The BLTU (branch if less than unsigned) instruction branches to a target address if the unsigned value in register rs1 is less than the unsigned value in register rs2. The target address is calculated by adding a signed 12-bit offset to the PC.

### Test Cases

1.  **rs1 < rs2 - Branch Taken (Positive Offset):**
    -   **Purpose:** Verify branch is taken when rs1 < rs2 (unsigned) and offset is positive.
    -   **Registers:** rs1 = 10, rs2 = 20
    -   **Offset:** offset = 0x20 (represented as 12-bit signed offset in assembly)
    -   **Expected Result:** Branch Taken

2.  **rs1 < rs2 - Branch Taken (Negative Offset):**
    -   **Purpose:** Verify branch is taken when rs1 < rs2 (unsigned) and offset is negative.
    -   **Registers:** rs1 = 0xFFFFFFF0 (unsigned representation of -16), rs2 = 0
    -   **Offset:** offset = -0x20 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Expected Result:** Branch Taken

3.  **rs1 < rs2 - Branch Taken (Zero Offset):**
    -   **Purpose:** Verify branch is taken when rs1 < rs2 (unsigned) and offset is zero.
    -   **Registers:** rs1 = 0x0, rs2 = 0x1
    -   **Offset:** offset = 0x0
    -   **Expected Result:** Branch Taken

4.  **rs1 >= rs2 - Branch Not Taken:**
    -   **Purpose:** Verify branch is not taken when rs1 >= rs2 (unsigned).
    -   **Registers:** rs1 = 20, rs2 = 10
    -   **Offset:** offset = 0x100
    -   **Expected Result:** Branch Not Taken

5.  **rs1 == rs2 - Branch Not Taken:**
    -   **Purpose:** Verify branch is not taken when rs1 == rs2 (unsigned).
    -   **Registers:** rs1 = 10, rs2 = 10
    -   **Offset:** offset = 0x100
    -   **Expected Result:** Branch Not Taken

6. **Large unsigned numbers:**
    -   **Purpose:** Verify correct unsigned comparison with large unsigned numbers.
    -   **Registers:** rs1 = 0x7FFFFFFF, rs2 = 0x80000000
    -   **Offset:** offset = 0x40
    -   **Expected Result:** Branch Taken

7. **Maximum unsigned value:**
    -   **Purpose:** Test with maximum unsigned values.
    -   **Registers:** rs1 = 0xFFFFFFFF, rs2 = 0x0
    -   **Offset:** offset = 0x40
    -   **Expected Result:** Branch Not Taken
