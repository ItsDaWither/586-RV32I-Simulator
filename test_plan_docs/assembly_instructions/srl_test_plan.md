# Test Plan for SRL Instruction

## Instruction: SRL (Shift Right Logical)

### Description
The SRL (shift right logical) instruction shifts the value in register rs1 to the right logically (zeros shifted in from the left) by a number of bits specified by the lower 5 bits of register rs2, and writes the result to register rd.

### Test Cases

1.  **Basic Shift Right Logical - Small Shift Amount:**
    -   **Purpose:** Verify basic logical shift right operation with a small shift amount.
    -   **Registers:** rs1 = 0x00000002, rs2 = 1, rd = any
    -   **Expected Result:** rd = 0x00000001 (shifted right by 1 bit)

2.  **Shift Right Logical by Zero:**
    -   **Purpose:** Verify shift right logical by zero bits.
    -   **Registers:** rs1 = 0x0000000F, rs2 = 0, rd = any
    -   **Expected Result:** rd = 0x0000000F (no shift)

3.  **Shift Right Logical by Maximum Shift Amount (5 bits):**
    -   **Purpose:** Test maximum shift amount (31, encoded in 5 bits).
    -   **Registers:** rs1 = 0x80000000, rs2 = 31, rd = any
    -   **Expected Result:** rd = 0x00000001 (shifted right by 31 bits)

4.  **Shift Right Logical with Zero Input:**
    -   **Purpose:** Verify shift right logical operation with zero input.
    -   **Registers:** rs1 = 0x00000000, rs2 = 10, rd = any
    -   **Expected Result:** rd = 0x00000000 (shifting zero remains zero)

5.  **Shift Right Logical with Negative Number (unsigned behavior):**
    -   **Purpose:** Verify shift right logical operation with a negative number, ensuring unsigned behavior (zeros shifted in from left).
    -   **Registers:** rs1 = 0xFFFFFFFF, rs2 = 1, rd = any
    -   **Expected Result:** rd = 0x7FFFFFFF (shifted right by 1 bit, zero shifted in from left)

6.  **Shift Right Logical with large value in rs1:**
    -   **Purpose:** Verify shift right logical operation with a large value in rs1.
    -   **Registers:** rs1 = 0xFFFFFFFF, rs2 = 30, rd = any
    -   **Expected Result:** rd = 0x00000003 (shifted right by 30 bits)

7.  **Shift by rs2 greater than 31 (only lower 5 bits are considered):**
    -   **Purpose:** Verify that only the lower 5 bits of rs2 are used for shift amount.
    -   **Registers:** rs1 = 0x00000002, rs2 = 32, rd = any
    -   **Expected Result:** rd = 0x00000002 (shifted right by 0 bits, no shift)

8.  **Chaining shifts:**
    -   **Purpose:** Verify that results of shifts can be chained correctly.
    -   **Registers:** rs1 = 0xFFFFFFFF, rs2 = 5, rd = any, rtemp = any, rshift = 10
    -   **Sequence:**
        1.  SRL rtemp, rs1, rs2  (rtemp = rs1 >> rs2)
        2.  SRL rd, rtemp, rshift   (rd = rtemp >> rshift)
    -   **Expected Result:** rd = 0x0001FFFF
