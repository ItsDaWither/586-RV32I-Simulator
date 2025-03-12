# Test Plan for BLTU Instruction

## Instruction: BLTU (Branch if Less Than Unsigned)

### Description
The BLTU (branch if less than unsigned) instruction branches to a target address if the unsigned value in register rs1 is less than the unsigned value in register rs2. The target address is calculated by adding a signed 12-bit offset to the PC.

### Test Cases

1.  **rs1 < rs2 - Branch Taken (Positive Offset):**
    -   **Purpose:** Verify branch is taken when rs1 < rs2 (unsigned) and offset is positive.
    -   **Registers:** rs1 = 10, rs2 = 20, PC = 0x1000
    -   **Offset:** offset = 0x20 (represented as 12-bit signed offset in assembly)
    -   **Expected Result:** PC = 0x1000 + 0x20 = 0x1020 (PC is updated to branch target)

2.  **rs1 < rs2 - Branch Taken (Negative Offset):**
    -   **Purpose:** Verify branch is taken when rs1 < rs2 (unsigned) and offset is negative.
    -   **Registers:** rs1 = 0xFFFFFFF0 (unsigned representation of -16), rs2 = 0, PC = 0x2000
    -   **Offset:** offset = -0x20 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Expected Result:** PC = 0x2000 - 0x20 = 0x1FE0 (PC is updated to branch target)

3.  **rs1 < rs2 - Branch Taken (Zero Offset):**
    -   **Purpose:** Verify branch is taken when rs1 < rs2 (unsigned) and offset is zero.
    -   **Registers:** rs1 = 0x0, rs2 = 0x1, PC = 0x3000
    -   **Offset:** offset = 0x0
    -   **Expected Result:** PC = 0x3000 (PC is updated to branch target, effectively staying at the same location)

4.  **rs1 >= rs2 - Branch Not Taken:**
    -   **Purpose:** Verify branch is not taken when rs1 >= rs2 (unsigned).
    -   **Registers:** rs1 = 20, rs2 = 10, PC = 0x4000
    -   **Offset:** offset = 0x100
    -   **Expected Result:** PC = 0x4000 + 4 = 0x4004 (PC increments to the next instruction)

5.  **rs1 == rs2 - Branch Not Taken:**
    -   **Purpose:** Verify branch is not taken when rs1 == rs2 (unsigned).
    -   **Registers:** rs1 = 10, rs2 = 10, PC = 0x5000
    -   **Offset:** offset = 0x100
    -   **Expected Result:** PC = 0x5000 + 4 = 0x5004 (PC increments to the next instruction)

6. **Large unsigned numbers:**
    -   **Purpose:** Verify correct unsigned comparison with large unsigned numbers.
    -   **Registers:** rs1 = 0x7FFFFFFF, rs2 = 0x80000000, PC = 0x8000
    -   **Offset:** offset = 0x40
    -   **Expected Result:** PC = 0x8000 + 0x40 = 0x8040 (PC is updated to branch target because 0x7FFFFFFF < 0x80000000 in unsigned)

7. **Maximum unsigned value:**
    -   **Purpose:** Test with maximum unsigned values.
    -   **Registers:** rs1 = 0xFFFFFFFF, rs2 = 0x0, PC = 0x9000
    -   **Offset:** offset = 0x40
    -   **Expected Result:** PC = 0x9000 + 4 = 0x9004 (PC is NOT updated to branch target because 0xFFFFFFFF is not less than 0x0 in unsigned)
