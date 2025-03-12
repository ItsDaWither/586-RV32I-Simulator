# Test Plan for ADDI Instruction

## Instruction: ADDI (Add Immediate)

### Description
The ADDI (add immediate) instruction adds a signed 12-bit immediate to a register and writes the result to another register.

### Test Cases

1.  **Basic Addition - Positive Immediate:**
    -   **Purpose:** Verify basic addition with a positive immediate value.
    -   **Registers:** rs1 = 10, rd = any
    -   **Immediate:** imm = 5
    -   **Expected Result:** rd = 15

2.  **Basic Addition - Negative Immediate:**
    -   **Purpose:** Verify basic addition with a negative immediate value.
    -   **Registers:** rs1 = 10, rd = any
    -   **Immediate:** imm = -5 (represented as 2's complement in assembly)
    -   **Expected Result:** rd = 5

3.  **Addition with Zero Immediate:**
    -   **Purpose:** Verify addition with a zero immediate value.
    -   **Registers:** rs1 = 10, rd = any
    -   **Immediate:** imm = 0
    -   **Expected Result:** rd = 10

4.  **Boundary Condition - Maximum Positive Immediate:**
    -   **Purpose:** Test the upper boundary of the positive immediate range (12-bit signed, max positive is 2047).
    -   **Registers:** rs1 = 1, rd = any
    -   **Immediate:** imm = 2047
    -   **Expected Result:** rd = 2048

5.  **Boundary Condition - Maximum Negative Immediate:**
    -   **Purpose:** Test the lower boundary of the negative immediate range (12-bit signed, max negative is -2048).
    -   **Registers:** rs1 = 1, rd = any
    -   **Immediate:** imm = -2048 (represented as 2's complement in assembly)
    -   **Expected Result:** rd = -2047 (or 0xFFFF8001 in unsigned representation, depending on register interpretation)

6.  **Register rs1 = 0:**
    -   **Purpose:** Verify addition when the source register rs1 is zero.
    -   **Registers:** rs1 = 0, rd = any
    -   **Immediate:** imm = 10
    -   **Expected Result:** rd = 10

7.  **Immediate = 0 and Register rs1 = 0:**
    -   **Purpose:** Verify addition when both the source register rs1 and the immediate are zero.
    -   **Registers:** rs1 = 0, rd = any
    -   **Immediate:** imm = 0
    -   **Expected Result:** rd = 0

8.  **Large Positive Register and Positive Immediate:**
    -   **Purpose:** Test addition with a large positive register value and a positive immediate to check for potential overflow behavior (though overflow behavior is not explicitly defined in the test scope, it's good to test).
    -   **Registers:** rs1 = 0x7FFFFFFF (max positive 32-bit signed integer), rd = any
    -   **Immediate:** imm = 1
    -   **Expected Result:** rd = 0x80000000 (min negative 32-bit signed integer, due to wrap-around in 2's complement)

9.  **Large Negative Register and Negative Immediate:**
    -   **Purpose:** Test addition with a large negative register value and a negative immediate to check for potential underflow behavior.
    -   **Registers:** rs1 = 0x80000000 (min negative 32-bit signed integer), rd = any
    -   **Immediate:** imm = -1 (represented as 2's complement)
    -   **Expected Result:** rd = 0x7FFFFFFF (max positive 32-bit signed integer, due to wrap-around in 2's complement)
