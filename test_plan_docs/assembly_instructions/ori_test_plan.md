# Test Plan for ORI Instruction

## Instruction: ORI (OR Immediate)

### Description
The ORI (OR immediate) instruction performs a bitwise OR operation between the value in register rs1 and a signed 12-bit immediate, and writes the result to register rd.

### Test Cases

1.  **Basic OR - Positive Immediate:**
    -   **Purpose:** Verify basic OR operation with a positive immediate value.
    -   **Registers:** rs1 = 0x0000000F, rd = any
    -   **Immediate:** imm = 0x00000003
    -   **Expected Result:** rd = 0x0000000F (0xF | 0x3 = 0xF)

2.  **OR with Zero Immediate:**
    -   **Purpose:** Verify OR operation with a zero immediate value.
    -   **Registers:** rs1 = 0xABCDEF01, rd = any
    -   **Immediate:** imm = 0x00000000
    -   **Expected Result:** rd = 0xABCDEF01 (x | 0 = x)

3.  **OR with All Ones Immediate:**
    -   **Purpose:** Verify OR operation with an immediate value of all ones (0xFFF as signed 12-bit, sign-extended to 32-bits).
    -   **Registers:** rs1 = 0x00000000, rd = any
    -   **Immediate:** imm = -1
    -   **Expected Result:** rd = 0xFFFFFFFF (0x0 | 0xFFFFFFFF = 0xFFFFFFFF)

4.  **OR with rs1 = 0:**
    -   **Purpose:** Verify OR operation when the source register rs1 is zero.
    -   **Registers:** rs1 = 0x00000000, rd = any
    -   **Immediate:** imm = 0x7FF
    -   **Expected Result:** rd = 0x000007FF (0 | x = x)

5.  **OR with rs1 = immediate:**
    -   **Purpose:** Verify OR operation when rs1 and immediate are the same value.
    -   **Registers:** rs1 = 0x555, rd = any
    -   **Immediate:** imm = 0x555
    -   **Expected Result:** rd = 0x555

6.  **OR with Maximum Positive Immediate (12-bit signed):**
    -   **Purpose:** Test upper boundary of positive immediate range.
    -   **Registers:** rs1 = 0x00001000, rd = any
    -   **Immediate:** imm = 2047
    -   **Expected Result:** rd = 0x000017FF (0x1000 | 0x7FF = 0x17FF)

7.  **Boundary Condition - Maximum Negative Immediate (12-bit signed):**
    -   **Purpose:** Test lower boundary of negative immediate range.
    -   **Registers:** rs1 = 0x00000001, rd = any
    -   **Immediate:** imm = -2048
    -   **Expected Result:** rd = 0xFFFF8001 (0x00000001 | 0xFFFFF800 = 0xFFFF8001)

8.  **Large register value and immediate:**
    -   **Purpose:** Verify OR operation with large register and immediate values.
    -   **Registers:** rs1 = 0xF0F0F0F0, rd = any
    -   **Immediate:** imm = 0x7FF
    -   **Expected Result:** rd = 0xF0F0F7FF (0xF0F0F0F0 | 0x000007FF = 0xF0F0F7FF)
