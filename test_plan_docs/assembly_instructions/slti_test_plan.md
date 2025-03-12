# Test Plan for SLTI Instruction

## Instruction: SLTI (Set Less Than Immediate)

### Description
The SLTI (set less than immediate) instruction compares the signed value in register rs1 against a signed 12-bit immediate. If rs1 is less than the immediate, register rd is set to 1; otherwise, rd is set to 0.

### Test Cases

1.  **rs1 < immediate - Set to 1 (Positive):**
    -   **Purpose:** Verify set to 1 when rs1 is less than positive immediate.
    -   **Registers:** rs1 = 10, rd = any
    -   **Immediate:** imm = 20
    -   **Expected Result:** rd = 1 (10 < 20)

2.  **rs1 < immediate - Set to 1 (Negative rs1):**
    -   **Purpose:** Verify set to 1 when negative rs1 is less than immediate.
    -   **Registers:** rs1 = -10, rd = any
    -   **Immediate:** imm = 0
    -   **Expected Result:** rd = 1 (-10 < 0)

3.  **rs1 == immediate - Set to 0:**
    -   **Purpose:** Verify set to 0 when rs1 is equal to immediate.
    -   **Registers:** rs1 = 15, rd = any
    -   **Immediate:** imm = 15
    -   **Expected Result:** rd = 0 (15 is not less than 15)

4.  **rs1 > immediate - Set to 0 (Positive):**
    -   **Purpose:** Verify set to 0 when rs1 is greater than positive immediate.
    -   **Registers:** rs1 = 30, rd = any
    -   **Immediate:** imm = 20
    -   **Expected Result:** rd = 0 (30 is not less than 20)

5.  **rs1 > immediate - Set to 0 (Negative Immediate):**
    -   **Purpose:** Verify set to 0 when rs1 is greater than negative immediate.
    -   **Registers:** rs1 = 0, rd = any
    -   **Immediate:** imm = -10
    -   **Expected Result:** rd = 0 (0 is not less than -10)

6.  **Boundary Condition - Maximum Positive Immediate:**
    -   **Purpose:** Test upper boundary of positive immediate range.
    -   **Registers:** rs1 = 2046, rd = any
    -   **Immediate:** imm = 2047
    -   **Expected Result:** rd = 1 (2046 < 2047)

7.  **Boundary Condition - Maximum Negative Immediate:**
    -   **Purpose:** Test lower boundary of negative immediate range.
    -   **Registers:** rs1 = -2049, rd = any
    -   **Immediate:** imm = -2048
    -   **Expected Result:** rd = 1 (-2049 < -2048)

8.  **Immediate = 0:**
    -   **Purpose:** Test comparison with zero immediate.
    -   **Registers:** rs1 = -1, rd = any
    -   **Immediate:** imm = 0
    -   **Expected Result:** rd = 1 (-1 < 0)

10. **rs1 = 0:**
    -   **Purpose:** Test when rs1 is zero.
    -   **Registers:** rs1 = 0, rd = any
    -   **Immediate:** imm = 1
    -   **Expected Result:** rd = 1 (0 < 1)
