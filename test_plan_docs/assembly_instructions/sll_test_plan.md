# Test Plan for SLL Instruction

## Instruction: SLL (Shift Left Logical)

### Description
The SLL (shift left logical) instruction shifts the value in register rs1 to the left by a number of bits specified by the lower 5 bits of register rs2, and writes the result to register rd.

### Test Cases

1.  **Basic Shift Left - Small Shift Amount:**
    -   **Purpose:** Verify basic shift left operation with a small shift amount.
    -   **Registers:** rs1 = 0x00000001, rs2 = 1, rd = any
    -   **Expected Result:** rd = 0x00000002 (shifted left by 1 bit)

2.  **Shift Left by Zero:**
    -   **Purpose:** Verify shift left by zero bits.
    -   **Registers:** rs1 = 0x0000000F, rs2 = 0, rd = any
    -   **Expected Result:** rd = 0x0000000F (no shift)

3.  **Shift Left by Maximum Shift Amount (5 bits):**
    -   **Purpose:** Test maximum shift amount (31, encoded in 5 bits).
    -   **Registers:** rs1 = 0x00000001, rs2 = 31, rd = any
    -   **Expected Result:** rd = 0x80000000 (shifted left by 31 bits)

4.  **Shift Left with Overflow:**
    -   **Purpose:** Verify shift left operation that results in overflow (bits shifted out).
    -   **Registers:** rs1 = 0x80000000, rs2 = 1, rd = any
    -   **Expected Result:** rd = 0x00000000 (shifted left by 1 bit, MSB shifted out)

5.  **Shift Left with rs1 = 0:**
    -   **Purpose:** Verify shift left operation when the source register rs1 is zero.
    -   **Registers:** rs1 = 0x00000000, rs2 = 10, rd = any
    -   **Expected Result:** rd = 0x00000000 (shifting zero remains zero)

6.  **Shift Left with large value in rs1:**
    -   **Purpose:** Verify shift left operation with a large value in rs1.
    -   **Registers:** rs1 = 0x7FFFFFFF, rs2 = 2, rd = any
    -   **Expected Result:** rd = 0x1FFFFFFFC (shifted left by 2 bits)

7.  **Shift by rs2 greater than 31 (only lower 5 bits are considered):**
    -   **Purpose:** Verify that only the lower 5 bits of rs2 are used for shift amount.
    -   **Registers:** rs1 = 0x00000001, rs2 = 32, rd = any
    -   **Expected Result:** rd = 0x00000001 (shifted left by 0 bits, no shift)

8.  **Chaining shifts:**
    -   **Purpose:** Verify that results of shifts can be chained correctly.
    -   **Registers:** rs1 = 0x00000001, rs2 = 5, rd = any, rtemp = any, rshift = 10
    -   **Sequence:**
        1.  SLL rtemp, rs1, rs2  (rtemp = rs1 << rs2)
        2.  SLL rd, rtemp, rshift   (rd = rtemp << rshift)
    -   **Expected Result:** rtemp = 0x00000020 (0x1 << 5), rd = 0x00008000 ((0x1 << 5) << 10 = 0x1 << 15)
