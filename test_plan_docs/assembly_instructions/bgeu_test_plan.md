# Test Plan for BGEU Instruction

## Instruction: BGEU (Branch if Greater Than or Equal Unsigned)

### Description
The BGEU (branch if greater than or equal unsigned) instruction branches to a target address if the unsigned value in register rs1 is greater than or equal to the unsigned value in register rs2. The target address is calculated by adding a signed 12-bit offset to the PC.

### Test Cases

1.  **rs1 > rs2 - Branch Taken (Positive Offset):**
    -   **Purpose:** Verify branch is taken when rs1 > rs2 (unsigned) and offset is positive.
    -   **Registers:** rs1 = 20, rs2 = 10, PC = 0x1000
    -   **Offset:** offset = 0x20 (represented as 12-bit signed offset in assembly)
    -   **Expected Result:** PC = 0x1000 + 0x20 = 0x1020 (PC is updated to branch target)

2.  **rs1 > rs2 - Branch Taken (Negative Offset):**
    -   **Purpose:** Verify branch is taken when rs1 > rs2 (unsigned) and offset is negative.
    -   **Registers:** rs1 = 0, rs2 = 0xFFFFFFF0 (unsigned representation of -16), PC = 0x2000
    -   **Offset:** offset = -0x20 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Expected Result:** PC = 0x2000 - 0x20 = 0x1FE0 (PC is updated to branch target)

3.  **rs1 > rs2 - Branch Taken (Zero Offset):**
    -   **Purpose:** Verify branch is taken when rs1 > rs2 (unsigned) and offset is zero.
    -   **Registers:** rs1 = 0x1, rs2 = 0x0, PC = 0x3000
    -   **Offset:** offset = 0x0
    -   **Expected Result:** PC = 0x3000 (PC is updated to branch target, effectively staying at the same location)

4.  **rs1 < rs2 - Branch Not Taken:**
    -   **Purpose:** Verify branch is not taken when rs1 < rs2 (unsigned).
    -   **Registers:** rs1 = 10, rs2 = 20, PC = 0x4000
    -   **Offset:** offset = 0x100
    -   **Expected Result:** PC = 0x4000 + 4 = 0x4004 (PC increments to the next instruction)

5.  **rs1 == rs2 - Branch Taken:**
    -   **Purpose:** Verify branch is taken when rs1 == rs2 (unsigned).
    -   **Registers:** rs1 = 10, rs2 = 10, PC = 0x5000
    -   **Offset:** offset = 0x100
    -   **Expected Result:** PC = 0x5000 + 0x100 = 0x5100 (PC is updated to branch target)

6. **Large unsigned numbers (rs1 == rs2):**
    -   **Purpose:** Verify correct unsigned comparison with large unsigned numbers when equal.
    -   **Registers:** rs1 = 0x80000000, rs2 = 0x80000000, PC = 0x8000
    -   **Offset:** offset = 0x40
    -   **Expected Result:** PC = 0x8000 + 0x40 = 0x8040 (PC is updated to branch target because 0x80000000 >= 0x80000000 in unsigned)

7. **Maximum unsigned value (rs1 > rs2):**
    -   **Purpose:** Test with maximum unsigned values when rs1 > rs2.
    -   **Registers:** rs1 = 0xFFFFFFFF, rs2 = 0x7FFFFFFF, PC = 0x9000
    -   **Offset:** offset = 0x40
    -   **Expected Result:** PC = 0x9000 + 0x40 = 0x9040 (PC is updated to branch target because 0xFFFFFFFF > 0x7FFFFFFF in unsigned)

8. **Maximum unsigned value (rs1 >= rs2):**
    -   **Purpose:** Test with maximum unsigned values when rs1 >= rs2.
    -   **Registers:** rs1 = 0xFFFFFFFF, rs2 = 0xFFFFFFFF, PC = 0xA000
    -   **Offset:** offset = 0x40
    -   **Expected Result:** PC = 0xA000 + 0x40 = 0xA040 (PC is updated to branch target because 0xFFFFFFFF >= 0xFFFFFFFF in unsigned)
