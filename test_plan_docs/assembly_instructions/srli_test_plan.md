# Test Plan for SRLI Instruction

## Instruction: SRLI (Shift Right Logical Immediate)

### Description
The SRLI (shift right logical immediate) instruction shifts the value in register rs1 to the right logically (zeros shifted in from the left) by a specified number of bits given by the immediate field, and writes the result to register rd. The shift amount is encoded in the lower 5 bits of the immediate field.

### Test Cases

1.  **Basic Shift Right Logical - Small Shift Amount:**
    -   **Purpose:** Verify basic logical shift right operation with a small shift amount.
    -   **Registers:** rs1 = 0x00000002, rd = any
    -   **Immediate:** imm = 1 (shift amount)
    -   **Expected Result:** rd = 0x00000001 (shifted right by 1 bit)

2.  **Shift Right Logical by Zero:**
    -   **Purpose:** Verify shift right logical by zero bits.
    -   **Registers:** rs1 = 0x0000000F, rd = any
    -   **Immediate:** imm = 0 (shift amount)
    -   **Expected Result:** rd = 0x0000000F (no shift)

3.  **Shift Right Logical by Maximum Shift Amount (5 bits):**
    -   **Purpose:** Test maximum shift amount (31, encoded in 5 bits).
    -   **Registers:** rs1 = 0x80000000, rd = any
    -   **Immediate:** imm = 31 (shift amount)
    -   **Expected Result:** rd = 0x00000001 (shifted right by 31 bits)

4.  **Shift Right Logical with Zero Input:**
    -   **Purpose:** Verify shift right logical operation with zero input.
    -   **Registers:** rs1 = 0x00000000, rd = any
    -   **Immediate:** imm = 10 (shift amount)
    -   **Expected Result:** rd = 0x00000000 (shifting zero remains zero)

5.  **Shift Right Logical with Negative Number (unsigned behavior):**
    -   **Purpose:** Verify shift right logical operation with a negative number, ensuring unsigned behavior (zeros shifted in from left).
    -   **Registers:** rs1 = 0xFFFFFFFF, rd = any
    -   **Immediate:** imm = 1 (shift amount)
    -   **Expected Result:** rd = 0x7FFFFFFF (shifted right by 1 bit, zero shifted in from left)

6.  **Shift Right Logical with large value in rs1:**
    -   **Purpose:** Verify shift right logical operation with a large value in rs1.
    -   **Registers:** rs1 = 0xFFFFFFFF, rd = any
    -   **Immediate:** imm = 30 (shift amount)
    -   **Expected Result:** rd = 0x00000003 (shifted right by 30 bits)

7.  **Shift by immediate greater than 31 (only lower 5 bits are considered):**
    -   **Purpose:** Verify that only the lower 5 bits of the immediate are used for shift amount.
    -   **Registers:** rs1 = 0x00000002, rd = any
    -   **Immediate:** imm = 0 (shift amount, should be treated as 0)
    -   **Expected Result:** rd = 0x00000002 (shifted right by 0 bits, no shift)

8.  **Chaining shifts:**
    -   **Purpose:** Verify that results of shifts can be chained correctly.
    -   **Registers:** rs1 = 0xFFFFFFFF, rd = any, rtemp = any
    -   **Immediate:** imm1 = 5 (first shift amount), imm2 = 10 (second shift amount)
    -   **Sequence:**
        1.  SRLI rtemp, rs1, imm1  (rtemp = rs1 >> imm1)
        2.  SRLI rd, rtemp, imm2   (rd = rtemp >> imm2)
    -   **Expected Result:** rd = 0x0001FFFF
