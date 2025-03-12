# Test Plan for ADD Instruction

## Instruction: ADD (Add Registers)

### Test Cases

1.  **Basic Addition - Positive Operands:**
    -   **Purpose:** Verify basic addition with two positive register values.
    -   **Registers:** rs1 = 10, rs2 = 5, rd = any
    -   **Expected Result:** rd = 15 (10 + 5 = 15)

2.  **Addition with One Negative Operand:**
    -   **Purpose:** Verify addition with one positive and one negative register value.
    -   **Registers:** rs1 = 10, rs2 = -5, rd = any
    -   **Expected Result:** rd = 5 (10 + (-5) = 5)

3.  **Addition with Two Negative Operands:**
    -   **Purpose:** Verify addition with two negative register values.
    -   **Registers:** rs1 = -10, rs2 = -5, rd = any
    -   **Expected Result:** rd = -15 (-10 + (-5) = -15)

4.  **Addition with Zero Operands:**
    -   **Purpose:** Verify addition when one of the source registers is zero.
    -   **Registers:** rs1 = 10, rs2 = 0, rd = any
    -   **Expected Result:** rd = 10 (10 + 0 = 10)

5.  **Addition with Both Zero Operands:**
    -   **Purpose:** Verify addition when both source registers are zero.
    -   **Registers:** rs1 = 0, rs2 = 0, rd = any
    -   **Expected Result:** rd = 0 (0 + 0 = 0)

6.  **Boundary Condition - Maximum Positive Result (No Overflow):**
    -   **Purpose:** Test addition resulting in the maximum positive signed 32-bit integer.
    -   **Registers:** rs1 = 0x7FFFFFFF, rs2 = 0x00000000, rd = any
    -   **Expected Result:** rd = 0x7FFFFFFF (No overflow)

7.  **Overflow Condition - Positive Overflow:**
    -   **Purpose:** Test addition that results in positive overflow (result exceeds maximum positive signed 32-bit integer).
    -   **Registers:** rs1 = 0x7FFFFFFF, rs2 = 0x00000001, rd = any
    -   **Expected Result:** rd = 0x80000000 (Overflow to minimum negative signed 32-bit integer due to wrap-around)

8.  **Underflow Condition - Negative Overflow (Wrap-around):**
    -   **Purpose:** Test addition that results in negative overflow (result exceeds minimum negative signed 32-bit integer).
    -   **Registers:** rs1 = 0x80000000, rs2 = 0xFFFFFFFF (-1 in signed) , rd = any
    -   **Expected Result:** rd = 0x7FFFFFFF (Underflow to maximum positive signed 32-bit integer due to wrap-around)

9.  **Large Positive and Negative Numbers:**
    -   **Purpose:** Verify addition with large positive and negative numbers.
    -   **Registers:** rs1 = 0x7FFFFFFF (INT_MAX), rs2 = 0x80000001 (INT_MIN + 1), rd = any
    -   **Expected Result:** rd = 0x00000000 (INT_MAX + INT_MIN + 1 = 0)
