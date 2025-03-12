# Test Plan for SLTIU Instruction

## Instruction: SLTIU (Set Less Than Immediate Unsigned)

### Description
The SLTIU (set less than immediate unsigned) instruction compares the unsigned value in register rs1 against a signed 12-bit immediate, which is treated as unsigned. If rs1 is less than the immediate (unsigned comparison), register rd is set to 1; otherwise, rd is set to 0.

### Test Cases

1.  **rs1 < immediate - Set to 1 (Positive):**
    -   **Purpose:** Verify set to 1 when rs1 is less than positive immediate (unsigned).
    -   **Registers:** rs1 = 10, rd = any
    -   **Immediate:** imm = 20
    -   **Expected Result:** rd = 1 (10 < 20 unsigned)

2.  **rs1 < immediate - Set to 1 (Large rs1, small immediate):**
    -   **Purpose:** Verify set to 1 when large unsigned rs1 is less than small unsigned immediate (due to wrapping).
    -   **Registers:** rs1 = 0xFFFFFFFF (unsigned max), rd = any
    -   **Immediate:** imm = 1 (unsigned 1)
    -   **Expected Result:** rd = 0 (0xFFFFFFFF is not less than 1 unsigned)

3.  **rs1 == immediate - Set to 0:**
    -   **Purpose:** Verify set to 0 when rs1 is equal to immediate (unsigned).
    -   **Registers:** rs1 = 15, rd = any
    -   **Immediate:** imm = 15
    -   **Expected Result:** rd = 0 (15 is not less than 15 unsigned)

4.  **rs1 > immediate - Set to 0 (Positive):**
    -   **Purpose:** Verify set to 0 when rs1 is greater than positive immediate (unsigned).
    -   **Registers:** rs1 = 30, rd = any
    -   **Immediate:** imm = 20
    -   **Expected Result:** rd = 0 (30 is not less than 20 unsigned)

5.  **rs1 = 0, immediate = -1 (0xFFF unsigned):**
    -   **Purpose:** Verify comparison with a large unsigned immediate (signed -1 becomes unsigned 0xFFF).
    -   **Registers:** rs1 = 0, rd = any
    -   **Immediate:** imm = -1
    -   **Expected Result:** rd = 1 (0 < 0xFFF unsigned)

6.  **Boundary Condition - Maximum Positive Immediate (unsigned):**
    -   **Purpose:** Test upper boundary of positive immediate range (2047, treated as unsigned).
    -   **Registers:** rs1 = 2046, rd = any
    -   **Immediate:** imm = 2047
    -   **Expected Result:** rd = 1 (2046 < 2047 unsigned)

7.  **Boundary Condition - Maximum unsigned immediate (using signed -1 as 0xFFF unsigned):**
    -   **Purpose:** Test maximum unsigned immediate value (0xFFF, using signed -1).
    -   **Registers:** rs1 = 0x7FF, rd = any
    -   **Immediate:** imm = -1
    -   **Expected Result:** rd = 1 (0x7FF < 0xFFF unsigned)

8.  **Immediate = 0:**
    -   **Purpose:** Test comparison with zero immediate.
    -   **Registers:** rs1 = 1, rd = any
    -   **Immediate:** imm = 0
    -   **Expected Result:** rd = 0 (1 is not less than 0 unsigned)

11. **rs1 = 0:**
    -   **Purpose:** Test when rs1 is zero.
    -   **Registers:** rs1 = 0, rd = any
    -   **Immediate:** imm = 1
    -   **Expected Result:** rd = 1 (0 < 1 unsigned)

12. **rs1 = max unsigned, immediate = 0:**
    -   **Purpose:** Test when rs1 is maximum unsigned value and immediate is 0.
    -   **Registers:** rs1 = 0xFFFFFFFF, rd = any
    -   **Immediate:** imm = 0
    -   **Expected Result:** rd = 0 (0xFFFFFFFF is not less than 0 unsigned)

