# Test Plan for SLT Instruction

## Instruction: SLT (Set Less Than)

### Description
The SLT (set less than) instruction compares the signed value in register rs1 against the signed value in register rs2. If rs1 is less than rs2, register rd is set to 1; otherwise, rd is set to 0.

### Test Cases

1.  **rs1 < rs2 - Set to 1 (Positive):**
    -   **Purpose:** Verify set to 1 when rs1 is less than rs2 (signed) and both are positive.
    -   **Registers:** rs1 = 10, rs2 = 20, rd = any
    -   **Expected Result:** rd = 1 (10 < 20)

2.  **rs1 < rs2 - Set to 1 (Negative rs1):**
    -   **Purpose:** Verify set to 1 when rs1 is negative and less than rs2 (signed).
    -   **Registers:** rs1 = -10, rs2 = 0, rd = any
    -   **Expected Result:** rd = 1 (-10 < 0)

3.  **rs1 == rs2 - Set to 0:**
    -   **Purpose:** Verify set to 0 when rs1 is equal to rs2 (signed).
    -   **Registers:** rs1 = 15, rs2 = 15, rd = any
    -   **Expected Result:** rd = 0 (15 is not less than 15)

4.  **rs1 > rs2 - Set to 0 (Positive):**
    -   **Purpose:** Verify set to 0 when rs1 is greater than rs2 (signed) and both are positive.
    -   **Registers:** rs1 = 30, rs2 = 20, rd = any
    -   **Expected Result:** rd = 0 (30 is not less than 20)

5.  **rs1 > rs2 - Set to 0 (Negative rs2):**
    -   **Purpose:** Verify set to 0 when rs1 is greater than rs2 (signed) and rs2 is negative.
    -   **Registers:** rs1 = 0, rs2 = -10, rd = any
    -   **Expected Result:** rd = 0 (0 is not less than -10)

6.  **Large positive and negative numbers (rs1 < rs2):**
    -   **Purpose:** Verify correct signed comparison with large numbers where rs1 < rs2.
    -   **Registers:** rs1 = 0x80000000 (INT_MIN), rs2 = 0x7FFFFFFF (INT_MAX), rd = any
    -   **Expected Result:** rd = 1 (INT_MIN < INT_MAX)

7.  **Large positive and negative numbers (rs1 > rs2):**
    -   **Purpose:** Verify correct signed comparison with large numbers where rs1 > rs2.
    -   **Registers:** rs1 = 0x7FFFFFFF (INT_MAX), rs2 = 0x80000000 (INT_MIN), rd = any
    -   **Expected Result:** rd = 0 (INT_MAX is not less than INT_MIN)

8.  **rs1 = 0:**
    -   **Purpose:** Test when rs1 is zero.
    -   **Registers:** rs1 = 0, rs2 = 1, rd = any
    -   **Expected Result:** rd = 1 (0 < 1)

9.  **rs2 = 0:**
    -   **Purpose:** Test when rs2 is zero.
    -   **Registers:** rs1 = -1, rs2 = 0, rd = any
    -   **Expected Result:** rd = 1 (-1 < 0)

10. **rs1 = rs2 = 0:**
    -   **Purpose:** Test when both rs1 and rs2 are zero.
    -   **Registers:** rs1 = 0, rs2 = 0, rd = any
    -   **Expected Result:** rd = 0 (0 is not less than 0)
