# Test Plan for XOR Instruction

## Instruction: XOR (Exclusive OR)

### Description
The XOR (exclusive OR) instruction performs a bitwise exclusive OR operation between the value in register rs1 and the value in register rs2, and writes the result to register rd.

### Test Cases

1.  **Basic XOR - Positive Operands:**
    -   **Purpose:** Verify basic XOR operation with two positive register values.
    -   **Registers:** rs1 = 0x0000000F, rs2 = 0x00000003, rd = any
    -   **Expected Result:** rd = 0x0000000C (0xF ^ 0x3 = 0xC)

2.  **XOR with One Zero Operand:**
    -   **Purpose:** Verify XOR operation with one register value being zero.
    -   **Registers:** rs1 = 0xABCDEF01, rs2 = 0x00000000, rd = any
    -   **Expected Result:** rd = 0xABCDEF01 (x ^ 0 = x)

3.  **XOR with Both Operands Zero:**
    -   **Purpose:** Verify XOR operation when both source registers are zero.
    -   **Registers:** rs1 = 0x00000000, rs2 = 0x00000000, rd = any
    -   **Expected Result:** rd = 0x00000000 (0 ^ 0 = 0)

4.  **XOR with All Ones in Both Registers:**
    -   **Purpose:** Verify XOR operation with all bits set to 1 in both registers.
    -   **Registers:** rs1 = 0xFFFFFFFF, rs2 = 0xFFFFFFFF, rd = any
    -   **Expected Result:** rd = 0x00000000 (all bits cancel out)

5.  **XOR with Opposite Bits:**
    -   **Purpose:** Verify XOR operation with opposite bits in the registers.
    -   **Registers:** rs1 = 0x55555555, rs2 = 0xAAAAAAAA, rd = any
    -   **Expected Result:** rd = 0xFFFFFFFF (alternating bits are flipped)

6.  **XOR with rs1 = rs2:**
    -   **Purpose:** Verify XOR operation when rs1 and rs2 are the same value.
    -   **Registers:** rs1 = 0x12345678, rs2 = 0x12345678, rd = any
    -   **Expected Result:** rd = 0x00000000 (x ^ x = 0)

7.  **Large register values:**
    -   **Purpose:** Verify XOR operation with large register values.
    -   **Registers:** rs1 = 0xF0F0F0F0, rs2 = 0x0F0F0F0F, rd = any
    -   **Expected Result:** rd = 0xFFFFFFFF (0xF0F0F0F0 ^ 0x0F0F0F0F = 0xFFFFFFFF)
