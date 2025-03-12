# Test Plan for ANDI Instruction

## Instruction: ANDI (AND Immediate)

### Description
The ANDI (AND immediate) instruction performs a bitwise AND operation between the value in register rs1 and a signed 12-bit immediate, and writes the result to register rd.

### Test Cases

1.  **Basic AND - Positive Immediate:**
    -   **Purpose:** Verify basic AND operation with a positive immediate value.
    -   **Registers:** rs1 = 0x0000000F, rd = any
    -   **Immediate:** imm = 0x00000003
    -   **Expected Result:** rd = 0x00000003 (0xF & 0x3 = 0x3)

2.  **AND with Zero Immediate:**
    -   **Purpose:** Verify AND operation with a zero immediate value.
    -   **Registers:** rs1 = 0xABCDEF01, rd = any
    -   **Immediate:** imm = 0x00000000
    -   **Expected Result:** rd = 0x00000000 (x & 0 = 0)

3.  **AND with All Ones Immediate:**
    -   **Purpose:** Verify AND operation with an immediate value of all ones (0xFFF as signed 12-bit, sign-extended to 32-bits).
    -   **Registers:** rs1 = 0x0000FFFF, rd = any
    -   **Immediate:** imm = -1
    -   **Expected Result:** rd = 0x0000FFFF (0xFFFF & 0xFFFFFFFF = 0xFFFF)

4.  **AND with rs1 = 0:**
    -   **Purpose:** Verify AND operation when the source register rs1 is zero.
    -   **Registers:** rs1 = 0x00000000, rd = any
    -   **Immediate:** imm = 0xFFFFFFFF (-1 sign extended)
    -   **Expected Result:** rd = 0x00000000 (0 & x = 0)

5.  **AND with rs1 = immediate:**
    -   **Purpose:** Verify AND operation when rs1 and immediate are the same value.
    -   **Registers:** rs1 = 0x55555555, rd = any
    -   **Immediate:** imm = 0x7FF
    -   **Expected Result:** rd = 0x00000555 (0x55555555 & 0x7FF = 0x555)

6.  **AND with Maximum Positive Immediate (12-bit signed):**
    -   **Purpose:** Test upper boundary of positive immediate range.
    -   **Registers:** rs1 = 0x00001FFF, rd = any
    -   **Immediate:** imm = 2047
    -   **Expected Result:** rd = 0x000007FF (0x1FFF & 0x7FF = 0x7FF)

7.  **Boundary Condition - Maximum Negative Immediate (12-bit signed):**
    -   **Purpose:** Test lower boundary of negative immediate range.
    -   **Registers:** rs1 = 0xFFFFFFFF, rd = any
    -   **Immediate:** imm = -2048
    -   **Expected Result:** rd = 0xFFFFF800 (0xFFFFFFFF & 0xFFFFF800 = 0xFFFFF800)
