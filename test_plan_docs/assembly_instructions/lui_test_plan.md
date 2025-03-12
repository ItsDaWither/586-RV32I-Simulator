# Test Plan for LUI Instruction

## Instruction: LUI (Load Upper Immediate)

### Description
The LUI (load upper immediate) instruction loads a 20-bit immediate value into the upper 20 bits of the destination register rd, and clears the lower 12 bits.

### Test Cases

1.  **Basic Load - Positive Immediate:**
    -   **Purpose:** Verify basic loading of a positive immediate value into the upper bits.
    -   **Registers:** rd = any
    -   **Immediate:** imm = 0x12345 (represented as 20-bit immediate in assembly)
    -   **Expected Result:** rd = 0x12345000

2.  **Load with Zero Immediate:**
    -   **Purpose:** Verify loading with a zero immediate value.
    -   **Registers:** rd = any
    -   **Immediate:** imm = 0x0
    -   **Expected Result:** rd = 0x0

3.  **Boundary Condition - Maximum 20-bit Positive Immediate:**
    -   **Purpose:** Test the upper boundary of the positive immediate range (20-bit, max positive is 0xFFFFF).
    -   **Registers:** rd = any
    -   **Immediate:** imm = 0xFFFFF
    -   **Expected Result:** rd = 0xFFFFF000

4.  **Loading into x0 (zero register):**
    -   **Purpose:** Verify that LUI instruction when targeting x0 register has no effect, as x0 is always zero.
    -   **Registers:** rd = x0
    -   **Immediate:** imm = 0x12345
    -   **Expected Result:** x0 remains 0

5.  **Loading when rd is the same as rs1 (though LUI is I-type, so rs1 is not explicitly used, testing register overlap):**
    -   **Purpose:** While LUI doesn't use rs1, this test ensures no unintended side effects if rd and rs1 are the same register.
    -   **Registers:** rd = x1, rs1 = x1 (though rs1 is not used in LUI)
    -   **Immediate:** imm = 0xABCDE
    -   **Expected Result:** x1 = 0xABCDE000