# Test Plan for SRA Instruction

## Instruction: SRA (Shift Right Arithmetic)

### Description
The SRA (shift right arithmetic) instruction shifts the value in register rs1 to the right arithmetically (sign bit shifted in from the left) by a number of bits specified by the lower 5 bits of register rs2, and writes the result to register rd.

### Test Cases

1.  **Basic Shift Right Arithmetic - Small Shift Amount (Positive):**
    -   **Purpose:** Verify basic arithmetic shift right operation with a small shift amount on a positive number.
    -   **Registers:** rs1 = 0x00000004, rs2 = 1, rd = any
    -   **Expected Result:** rd = 0x00000002 (shifted right by 1 bit)

2.  **Basic Shift Right Arithmetic - Small Shift Amount (Negative):**
    -   **Purpose:** Verify basic arithmetic shift right operation with a small shift amount on a negative number.
    -   **Registers:** rs1 = 0xFFFFFFFC (signed -4), rs2 = 1, rd = any
    -   **Expected Result:** rd = 0xFFFFFFFE (shifted right by 1 bit, sign bit shifted in)

3.  **Shift Right Arithmetic by Zero:**
    -   **Purpose:** Verify arithmetic shift right by zero bits.
    -   **Registers:** rs1 = 0x0000000F, rs2 = 0, rd = any
    -   **Expected Result:** rd = 0x0000000F (no shift)

4.  **Shift Right Arithmetic by Maximum Shift Amount (5 bits) - Positive:**
    -   **Purpose:** Test maximum shift amount (31, encoded in 5 bits) on a positive number.
    -   **Registers:** rs1 = 0x7FFFFFFF, rs2 = 31, rd = any
    -   **Expected Result:** rd = 0x00000000 (shifted right by 31 bits)

5.  **Shift Right Arithmetic by Maximum Shift Amount (5 bits) - Negative:**
    -   **Purpose:** Test maximum shift amount (31, encoded in 5 bits) on a negative number.
    -   **Registers:** rs1 = 0x80000000 (min negative), rs2 = 31, rd = any
    -   **Expected Result:** rd = 0xFFFFFFFF (shifted right by 31 bits, sign bit shifted in)

6.  **Shift Right Arithmetic with Zero Input:**
    -   **Purpose:** Verify arithmetic shift right operation with zero input.
    -   **Registers:** rs1 = 0x00000000, rs2 = 10, rd = any
    -   **Expected Result:** rd = 0x00000000 (shifting zero remains zero)

7.  **Shift Right Arithmetic with Positive Number:**
    -   **Purpose:** Verify arithmetic shift right operation with a positive number.
    -   **Registers:** rs1 = 0x7FFFFFFF, rs2 = 2, rd = any
    -   **Expected Result:** rd = 0x1FFFFFFF (shifted right by 2 bits)

8.  **Shift Right Arithmetic with Negative Number:**
    -   **Purpose:** Verify arithmetic shift right operation with a negative number, ensuring sign bit is shifted in.
    -   **Registers:** rs1 = 0x80000000 (min negative), rs2 = 2, rd = any
    -   **Expected Result:** rd = 0xE0000000 (shifted right by 2 bits, sign bit shifted in)

9.  **Shift by rs2 greater than 31 (only lower 5 bits are considered):**
    -   **Purpose:** Verify that only the lower 5 bits of rs2 are used for shift amount.
    -   **Registers:** rs1 = 0x00000004, rs2 = 32, rd = any
    -   **Expected Result:** rd = 0x00000004 (shifted right by 0 bits, no shift)

10. **Chaining shifts (Arithmetic):**
    -   **Purpose:** Verify that results of arithmetic shifts can be chained correctly.
    -   **Registers:** rs1 = 0x80000000 (negative), rs2 = 5, rd = any, rtemp = any, rshift = 10
    -   **Sequence:**
        1.  SRA rtemp, rs1, rs2  (rtemp = rs1 >> rs2)
        2.  SRA rd, rtemp, rshift   (rd = rtemp >> rshift)
    -   **Expected Result:** rtemp = 0xFC000000, rd = 0xFFFF0000

11. **Chaining shifts (Logical then Arithmetic):**
    -   **Purpose:** Verify chaining logical and arithmetic shifts.
    -   **Registers:** rs1 = 0xFFFFFFFF (negative), rs2 = 16, rd = any, rtemp = any, rshift = 16
    -   **Sequence:**
        1.  SRL rtemp, rs1, rs2  (rtemp = rs1 >>> rs2) ; Logical shift
        2.  SRA rd, rtemp, rshift   (rd = rtemp >> rshift)  ; Arithmetic shift
    -   **Expected Result:** rtemp = 0x0000FFFF (0xFFFFFFFF >>> 16), rd = 0x00000000 (0x0000FFFF >> 16)
