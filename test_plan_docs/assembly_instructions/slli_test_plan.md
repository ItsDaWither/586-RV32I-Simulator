# Test Plan for SLLI Instruction

## Instruction: SLLI (Shift Left Logical Immediate)

### Description
The SLLI (shift left logical immediate) instruction shifts the value in register rs1 to the left by a specified number of bits given by the immediate field, and writes the result to register rd. The shift amount is encoded in the lower 5 bits of the immediate field.

### Test Cases

1.  **Basic Shift Left - Small Shift Amount:**
    -   **Purpose:** Verify basic shift left operation with a small shift amount.
    -   **Registers:** rs1 = 0x00000001, rd = any
    -   **Immediate:** imm = 1 (shift amount)
    -   **Expected Result:** rd = 0x00000002 (shifted left by 1 bit)

2.  **Shift Left by Zero:**
    -   **Purpose:** Verify shift left by zero bits.
    -   **Registers:** rs1 = 0x0000000F, rd = any
    -   **Immediate:** imm = 0 (shift amount)
    -   **Expected Result:** rd = 0x0000000F (no shift)

3.  **Shift Left by Maximum Shift Amount (5 bits):**
    -   **Purpose:** Test maximum shift amount (31, encoded in 5 bits).
    -   **Registers:** rs1 = 0x00000001, rd = any
    -   **Immediate:** imm = 31 (shift amount)
    -   **Expected Result:** rd = 0x80000000 (shifted left by 31 bits)

4.  **Shift Left with Overflow:**
    -   **Purpose:** Verify shift left operation that results in overflow (bits shifted out).
    -   **Registers:** rs1 = 0x80000000, rd = any
    -   **Immediate:** imm = 1 (shift amount)
    -   **Expected Result:** rd = 0x00000000 (shifted left by 1 bit, MSB shifted out)

5.  **Shift Left with rs1 = 0:**
    -   **Purpose:** Verify shift left operation when the source register rs1 is zero.
    -   **Registers:** rs1 = 0x00000000, rd = any
    -   **Immediate:** imm = 10 (shift amount)
    -   **Expected Result:** rd = 0x00000000 (shifting zero remains zero)

6.  **Shift Left with large value in rs1:**
    -   **Purpose:** Verify shift left operation with a large value in rs1.
    -   **Registers:** rs1 = 0x7FFFFFFF, rd = any
    -   **Immediate:** imm = 2 (shift amount)
    -   **Expected Result:** rd = 0x1FFFFFFFC (shifted left by 2 bits)

7.  **Chaining shifts:**
    -   **Purpose:** Verify that results of shifts can be chained correctly.
    -   **Registers:** rs1 = 0x00000001, rd = any, rtemp = any
    -   **Immediate:** imm1 = 5 (first shift amount), imm2 = 10 (second shift amount)
    -   **Sequence:**
        1.  SLLI rtemp, rs1, imm1  (rtemp = rs1 << imm1)
        2.  SLLI rd, rtemp, imm2   (rd = rtemp << imm2)
    -   **Expected Result:** rtemp = 0x00000020 (0x1 << 5), rd = 0x00008000 ((0x1 << 5) << 10 = 0x1 << 15)
