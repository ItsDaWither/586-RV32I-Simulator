# Test Plan for XORI Instruction

## Instruction: XORI (Exclusive OR Immediate)

### Description
The XORI (exclusive OR immediate) instruction performs a bitwise exclusive OR operation between the value in register rs1 and a signed 12-bit immediate, and writes the result to register rd.

### Test Cases

1.  **Basic XOR - Positive Immediate:**
    -   **Purpose:** Verify basic XOR operation with a positive immediate value.
    -   **Registers:** rs1 = 0x0000000F, rd = any
    -   **Immediate:** imm = 0x00000003
    -   **Expected Result:** rd = 0x0000000C (0xF ^ 0x3 = 0xC)

2.  **XOR with Zero Immediate:**
    -   **Purpose:** Verify XOR operation with a zero immediate value.
    -   **Registers:** rs1 = 0xABCDEF01, rd = any
    -   **Immediate:** imm = 0x00000000
    -   **Expected Result:** rd = 0xABCDEF01 (x ^ 0 = x)

3.  **XOR with All Ones Immediate:**
    -   **Purpose:** Verify XOR operation with an immediate value of all ones (0xFFF as signed 12-bit, but will be 0xFFF in lower 12 bits).
    -   **Registers:** rs1 = 0x0000FFFF, rd = any
    -   **Immediate:** imm = -1
    -   **Expected Result:** rd = 0xFFFF0000 (0x0000FFFF ^ 0xFFFFFFFF = 0xFFFF0000)

4.  **XOR with rs1 = 0:**
    -   **Purpose:** Verify XOR operation when the source register rs1 is zero.
    -   **Registers:** rs1 = 0x00000000, rd = any
    -   **Immediate:** imm = 2047
    -   **Expected Result:** rd = 2047 (0 ^ x = x)

5.  **XOR with rs1 = immediate:**
    -   **Purpose:** Verify XOR operation when rs1 and immediate are the same value.
    -   **Registers:** rs1 = 0x00000555, rd = any
    -   **Immediate:** imm = 0x555
    -   **Expected Result:** rd = 0x0 (x ^ x = 0)

6.  **XOR with Maximum Positive Immediate (12-bit signed):**
    -   **Purpose:** Test upper boundary of positive immediate range.
    -   **Registers:** rs1 = 0x00000001, rd = any
    -   **Immediate:** imm = 2047
    -   **Expected Result:** rd = 0x000007FE (0x00000001 ^ 0x000007FF = 0x000007FE)

7.  **Boundary Condition - Maximum Negative Immediate (12-bit signed):**
    -   **Purpose:** Test lower boundary of negative immediate range.
    -   **Registers:** rs1 = 0xFFFFFFFF, rd = any
    -   **Immediate:** imm = -2048
    -   **Expected Result:** rd = 0x000007FF(0xFFFFFFFF ^ 0xFFFFF800 = 0x000007FF)

8.  **Large register value and immediate:**
    -   **Purpose:** Verify XOR operation with large register and immediate values.
    -   **Registers:** rs1 = 0xF0F0F0F0, rd = any
    -   **Immediate:** imm = 2047
    -   **Expected Result:** rd = 0xF0F00F0F (0xF0F0F0F0 ^ 0xABABABAB = 0x5A5A5A5B)
