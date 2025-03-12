# Test Plan for SUB Instruction

## Instruction: SUB (Subtract Registers)

### Description
The SUB (subtract registers) instruction subtracts the signed value in register rs2 from the signed value in register rs1, and writes the result to register rd.

### Test Cases

1.  **Basic Subtraction - Positive Operands (rs1 > rs2):**
    -   **Purpose:** Verify basic subtraction with two positive register values where rs1 > rs2.
    -   **Registers:** rs1 = 20, rs2 = 10, rd = any
    -   **Expected Result:** rd = 10 (20 - 10 = 10)

2.  **Basic Subtraction - Positive Operands (rs1 < rs2):**
    -   **Purpose:** Verify basic subtraction with two positive register values where rs1 < rs2, resulting in a negative result.
    -   **Registers:** rs1 = 10, rs2 = 20, rd = any
    -   **Expected Result:** rd = -10 (10 - 20 = -10)

3.  **Subtraction with One Negative Operand (rs2 negative):**
    -   **Purpose:** Verify subtraction where rs2 is negative (rs1 - (-rs2) which is rs1 + rs2).
    -   **Registers:** rs1 = 10, rs2 = -5, rd = any
    -   **Expected Result:** rd = 15 (10 - (-5) = 15)

4.  **Subtraction with Two Negative Operands:**
    -   **Purpose:** Verify subtraction with two negative register values.
    -   **Registers:** rs1 = -10, rs2 = -5, rd = any
    -   **Expected Result:** rd = -5 (-10 - (-5) = -5)

5.  **Subtraction with Zero Operands (rs2 = 0):**
    -   **Purpose:** Verify subtraction when rs2 is zero.
    -   **Registers:** rs1 = 10, rs2 = 0, rd = any
    -   **Expected Result:** rd = 10 (10 - 0 = 10)

6.  **Subtraction with Both Zero Operands:**
    -   **Purpose:** Verify subtraction when both source registers are zero.
    -   **Registers:** rs1 = 0, rs2 = 0, rd = any
    -   **Expected Result:** rd = 0 (0 - 0 = 0)

7.  **Boundary Condition - Maximum Positive Result (No Overflow):**
    -   **Purpose:** Test subtraction resulting in the maximum positive signed 32-bit integer.
    -   **Registers:** rs1 = 0x7FFFFFFF, rs2 = 0x00000000, rd = any
    -   **Expected Result:** rd = 0x7FFFFFFF (No overflow)

8.  **Underflow Condition - Negative Overflow:**
    -   **Purpose:** Test subtraction that results in negative overflow (result exceeds minimum negative signed 32-bit integer).
    -   **Registers:** rs1 = 0x80000000 (INT_MIN), rs2 = 0x00000001, rd = any
    -   **Expected Result:** rd = 0x7FFFFFFF (Underflow to maximum positive signed 32-bit integer due to wrap-around)

9.  **Overflow Condition - Positive Overflow (Wrap-around):**
    -   **Purpose:** Test subtraction that results in positive overflow (result exceeds maximum positive signed 32-bit integer).
    -   **Registers:** rs1 = 0x7FFFFFFF, rs2 = 0xFFFFFFFF (-1), rd = any
    -   **Expected Result:** rd = 0x80000000 (0x7FFFFFFF - (-1) = 0x80000000)

10. **Large Positive and Negative Numbers:**
    -   **Purpose:** Verify subtraction with large positive and negative numbers.
    -   **Registers:** rs1 = 0x7FFFFFFF (INT_MAX), rs2 = 0x80000001 (INT_MIN + 1), rd = any
    -   **Expected Result:** rd = 0xFFFFFFFE (INT_MAX - (INT_MIN + 1) = -2)
