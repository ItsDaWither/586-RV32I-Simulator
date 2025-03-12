# Test Plan for SLTU Instruction

## Instruction: SLTU (Set Less Than Unsigned)

### Description
The SLTU (set less than unsigned) instruction compares the unsigned value in register rs1 against the unsigned value in register rs2. If rs1 is less than rs2, register rd is set to 1; otherwise, rd is set to 0.

### Test Cases

1.  **rs1 < rs2 - Set to 1 (Positive):**
    -   **Purpose:** Verify set to 1 when rs1 is less than rs2 (unsigned) and both are positive.
    -   **Registers:** rs1 = 10, rs2 = 20, rd = any
    -   **Expected Result:** rd = 1 (10 < 20 unsigned)

2.  **rs1 < rs2 - Set to 1 (Large rs1, small rs2):**
    -   **Purpose:** Verify set to 1 when large unsigned rs1 is less than small unsigned rs2 (due to wrapping).
    -   **Registers:** rs1 = 0xFFFFFFFF, rs2 = 1, rd = any
    -   **Expected Result:** rd = 0 (0xFFFFFFFF is not less than 1 unsigned)

3.  **rs1 == rs2 - Set to 0:**
    -   **Purpose:** Verify set to 0 when rs1 is equal to rs2 (unsigned).
    -   **Registers:** rs1 = 15, rs2 = 15, rd = any
    -   **Expected Result:** rd = 0 (15 is not less than 15 unsigned)

4.  **rs1 > rs2 - Set to 0 (Positive):**
    -   **Purpose:** Verify set to 0 when rs1 is greater than rs2 (unsigned) and both are positive.
    -   **Registers:** rs1 = 30, rs2 = 20, rd = any
    -   **Expected Result:** rd = 0 (30 is not less than 20 unsigned)

5.  **Large unsigned numbers (rs1 < rs2):**
    -   **Purpose:** Verify correct unsigned comparison with large numbers where rs1 < rs2.
    -   **Registers:** rs1 = 0x7FFFFFFF, rs2 = 0x80000000, rd = any
    -   **Expected Result:** rd = 1 (0x7FFFFFFF < 0x80000000 unsigned)

6.  **Large unsigned numbers (rs1 > rs2):**
    -   **Purpose:** Verify correct unsigned comparison with large numbers where rs1 > rs2.
    -   **Registers:** rs1 = 0x80000000, rs2 = 0x7FFFFFFF, rd = any
    -   **Expected Result:** rd = 0 (0x80000000 is not less than 0x7FFFFFFF unsigned)

7.  **rs1 = 0:**
    -   **Purpose:** Test when rs1 is zero.
    -   **Registers:** rs1 = 0, rs2 = 1, rd = any
    -   **Expected Result:** rd = 1 (0 < 1 unsigned)

8.  **rs2 = 0:**
    -   **Purpose:** Test when rs2 is zero.
    -   **Registers:** rs1 = 1, rs2 = 0, rd = any
    -   **Expected Result:** rd = 0 (1 is not less than 0 unsigned)

9.  **rs1 = rs2 = 0:**
    -   **Purpose:** Test when both rs1 and rs2 are zero.
    -   **Registers:** rs1 = 0, rs2 = 0, rd = any
    -   **Expected Result:** rd = 0 (0 is not less than 0 unsigned)

10. **rs1 = max unsigned, rs2 = 0:**
    -   **Purpose:** Test when rs1 is maximum unsigned value and rs2 is 0.
    -   **Registers:** rs1 = 0xFFFFFFFF, rs2 = 0, rd = any
    -   **Expected Result:** rd = 0 (0xFFFFFFFF is not less than 0 unsigned)
