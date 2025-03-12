# Test Plan for SRAI Instruction

## Instruction: SRAI (Shift Right Arithmetic Immediate)

### Description
The SRAI (shift right arithmetic immediate) instruction shifts the value in register rs1 to the right arithmetically (sign bit shifted in from the left) by a specified number of bits given by the immediate field, and writes the result to register rd. The shift amount is encoded in the lower 5 bits of the immediate field.

### Test Cases

1.  **Basic Shift Right Arithmetic - Small Shift Amount (Positive):**
    -   **Purpose:** Verify basic arithmetic shift right operation with a small shift amount on a positive number.
    -   **Registers:** rs1 = 0x00000004, rd = any
    -   **Immediate:** imm = 1 (shift amount)
    -   **Expected Result:** rd = 0x00000002 (shifted right by 1 bit)

2.  **Basic Shift Right Arithmetic - Small Shift Amount (Negative):**
    -   **Purpose:** Verify basic arithmetic shift right operation with a small shift amount on a negative number.
    -   **Registers:** rs1 = 0xFFFFFFFC (signed -4), rd = any
    -   **Immediate:** imm = 1 (shift amount)
    -   **Expected Result:** rd = 0xFFFFFFFE (shifted right by 1 bit, sign bit shifted in)

3.  **Shift Right Arithmetic by Zero:**
    -   **Purpose:** Verify arithmetic shift right by zero bits.
    -   **Registers:** rs1 = 0x0000000F, rd = any
    -   **Immediate:** imm = 0 (shift amount)
    -   **Expected Result:** rd = 0x0000000F (no shift)

4.  **Shift Right Arithmetic by Maximum Shift Amount (5 bits) - Positive:**
    -   **Purpose:** Test maximum shift amount (31, encoded in 5 bits) on a positive number.
    -   **Registers:** rs1 = 0x7FFFFFFF, rd = any
    -   **Immediate:** imm = 31 (shift amount)
    -   **Expected Result:** rd = 0x00000000 (shifted right by 31 bits)

5.  **Shift Right Arithmetic by Maximum Shift Amount (5 bits) - Negative:**
    -   **Purpose:** Test maximum shift amount (31, encoded in 5 bits) on a negative number.
    -   **Registers:** rs1 = 0x80000000 (min negative), rd = any
    -   **Immediate:** imm = 31 (shift amount)
    -   **Expected Result:** rd = 0xFFFFFFFF (shifted right by 31 bits, sign bit shifted in)

6.  **Shift Right Arithmetic with Zero Input:**
    -   **Purpose:** Verify arithmetic shift right operation with zero input.
    -   **Registers:** rs1 = 0x00000000, rd = any
    -   **Immediate:** imm = 10 (shift amount)
    -   **Expected Result:** rd = 0x00000000 (shifting zero remains zero)

7.  **Shift Right Arithmetic with Positive Number:**
    -   **Purpose:** Verify arithmetic shift right operation with a positive number.
    -   **Registers:** rs1 = 0x7FFFFFFF, rd = any
    -   **Immediate:** imm = 2 (shift amount)
    -   **Expected Result:** rd = 0x1FFFFFFF (shifted right by 2 bits)

8.  **Shift Right Arithmetic with Negative Number:**
    -   **Purpose:** Verify arithmetic shift right operation with a negative number, ensuring sign bit is shifted in.
    -   **Registers:** rs1 = 0x80000000 (min negative), rd = any
    -   **Immediate:** imm = 2 (shift amount)
    -   **Expected Result:** rd = 0xE0000000 (shifted right by 2 bits, sign bit shifted in)

9.  **Shift by immediate greater than 31 (only lower 5 bits are considered):**
    -   **Purpose:** Verify that only the lower 5 bits of the immediate are used for shift amount.
    -   **Registers:** rs1 = 0x00000004, rd = any
    -   **Immediate:** imm = 0 (shift amount, should be treated as 0)
    -   **Expected Result:** rd = 0x00000004 (shifted right by 0 bits, no shift)

10. **Chaining shifts (Arithmetic):**
    -   **Purpose:** Verify that results of arithmetic shifts can be chained correctly.
    -   **Registers:** rs1 = 0x80000000 (negative), rd = any, rtemp = any
    -   **Immediate:** imm1 = 5 (first shift amount), imm2 = 10 (second shift amount)
    -   **Sequence:**
        1.  SRAI rtemp, rs1, imm1  (rtemp = rs1 >> imm1)
        2.  SRAI rd, rtemp, imm2   (rd = rtemp >> imm2)
    -   **Expected Result:** rtemp = 0xFC000000, rd = 0xFFFF0000

11. **Chaining shifts (Logical then Arithmetic):**
    -   **Purpose:** Verify chaining logical and arithmetic shifts.
    -   **Registers:** rs1 = 0xFFFFFFFF (negative), rd = any, rtemp = any
    -   **Immediate:** imm1 = 16 (logical shift amount), imm2 = 16 (arithmetic shift amount)
    -   **Sequence:**
        1.  SRLI rtemp, rs1, imm1  (rtemp = rs1 >>> imm1) ; Logical shift
        2.  SRAI rd, rtemp, imm2   (rd = rtemp >> imm2)  ; Arithmetic shift
    -   **Expected Result:** rtemp = 0x0000FFFF (0xFFFFFFFF >>> 16), rd = 0x00000000 (0x0000FFFF >> 16)
