# Test Plan for BGEU Instruction

## Instruction: BGEU (Branch if Greater Than or Equal Unsigned)

### Description
The BGEU (branch if greater than or equal unsigned) instruction branches to a target address if the unsigned value in register rs1 is greater than or equal to the unsigned value in register rs2. The target address is calculated by adding a signed 12-bit offset to the PC.

### Test Cases

1.  **rs1 > rs2 - Branch Taken (Positive Offset):**
    -   **Purpose:** Verify branch is taken when rs1 > rs2 (unsigned) and offset is positive.
    -   **Registers:** rs1 = 20, rs2 = 10
    -   **Expected Result:** Branch Taken

2.  **rs1 > rs2 - Branch Taken (Negative Offset):**
    -   **Purpose:** Verify branch is taken when rs1 > rs2 (unsigned) and offset is negative.
    -   **Registers:** rs1 = 0, rs2 = 0xFFFFFFF0 (unsigned representation of -16)
    -   **Expected Result:** Branch Taken

3.  **rs1 > rs2 - Branch Taken (Zero Offset):**
    -   **Purpose:** Verify branch is taken when rs1 > rs2 (unsigned) and offset is zero.
    -   **Registers:** rs1 = 0x1, rs2 = 0x0
    -   **Offset:** offset = 0x0
    -   **Expected Result:** Branch Taken

4.  **rs1 < rs2 - Branch Not Taken:**
    -   **Purpose:** Verify branch is not taken when rs1 < rs2 (unsigned).
    -   **Registers:** rs1 = 10, rs2 = 20
    -   **Offset:** offset = 0x100
    -   **Expected Result:** Branch Not Taken

5.  **rs1 == rs2 - Branch Taken:**
    -   **Purpose:** Verify branch is taken when rs1 == rs2 (unsigned).
    -   **Registers:** rs1 = 10, rs2 = 10
    -   **Offset:** offset = 0x100
    -   **Expected Result:** Branch Taken

6. **Large unsigned numbers (rs1 == rs2):**
    -   **Purpose:** Verify correct unsigned comparison with large unsigned numbers when equal.
    -   **Registers:** rs1 = 0x80000000, rs2 = 0x80000000
    -   **Offset:** offset = 0x40
    -   **Expected Result:** Branch Taken

7. **Maximum unsigned value (rs1 > rs2):**
    -   **Purpose:** Test with maximum unsigned values when rs1 > rs2.
    -   **Registers:** rs1 = 0xFFFFFFFF, rs2 = 0x7FFFFFFF
    -   **Offset:** offset = 0x40
    -   **Expected Result:** Branch Taken

8. **Maximum unsigned value (rs1 >= rs2):**
    -   **Purpose:** Test with maximum unsigned values when rs1 >= rs2.
    -   **Registers:** rs1 = 0xFFFFFFFF, rs2 = 0xFFFFFFFF
    -   **Offset:** offset = 0x40
    -   **Expected Result:** Branch Taken
