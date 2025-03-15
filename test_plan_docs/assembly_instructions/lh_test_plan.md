# Test Plan for LH Instruction

## Instruction: LH (Load Halfword)

### Description
The LH (load halfword) instruction loads a 2-byte halfword from memory at an address calculated by adding a signed 12-bit offset to the value in register rs1. The loaded halfword is sign-extended to 32 bits and written to register rd. The memory address must be halfword-aligned.

### Test Cases

1.  **Basic Load - Positive Offset:**
    -   **Purpose:** Verify basic halfword load with a positive offset.
    -   **Registers:** rs1 = address of halfword in memory, rd = any
    -   **Offset:** offset = 0x10
    -   **Memory:** Memory location contains halfword value 0xCDEF
    -   **Expected Result:** rd = 0xFFFFCDEF (sign-extended halfword 0xCDEF)

2.  **Basic Load - Negative Offset:**
    -   **Purpose:** Verify basic halfword load with a negative offset.
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = -0x10 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Memory:** Memory location contains halfword value 0x1234
    -   **Expected Result:** rd = 0x00001234 (sign-extended halfword 0x1234)

3.  **Load with Zero Offset:**
    -   **Purpose:** Verify halfword load with a zero offset.
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = 0x0
    -   **Memory:** Memory location contains halfword value 0x55AA
    -   **Expected Result:** rd = 0x000055AA (sign-extended halfword 0x55AA)

4.  **Boundary Condition - Maximum Positive Offset:**
    -   **Purpose:** Test upper boundary of positive offset range.
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = 2046 (max positive offset for halfword alignment)
    -   **Memory:** Memory location contains halfword value 0x8000 (negative signed halfword)
    -   **Expected Result:** rd = 0xFFFF8000 (sign-extended halfword 0x8000)

5.  **Boundary Condition - Maximum Negative Offset:**
    -   **Purpose:** Test lower boundary of negative offset range.
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = -2048 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Memory:** Memory location contains halfword value 0x7FFF (positive signed halfword)
    -   **Expected Result:** rd = 0x00007FFF (sign-extended halfword 0x7FFF)

6.  **Load Halfword with rs1 = 0:**
    -   **Purpose:** Verify load halfword when the base address register rs1 is zero.
    -   **Registers:** rs1 = 0, rd = any
    -   **Offset:** offset = 0x100
    -   **Memory:** Memory location contains halfword value 0xC0C0 (negative signed halfword)
    -   **Expected Result:** rd = 0xFFFFC0C0 (sign-extended halfword 0xC0C0)

7.  **Load from address 0:**
    -   **Purpose:** Test loading halfword from memory address 0.
    -   **Registers:** rs1 = 0, rd = any
    -   **Offset:** offset = 0
    -   **Memory:** Memory location contains halfword value 0x0F0F (positive signed halfword)
    -   **Expected Result:** rd = 0x00000F0F (sign-extended halfword 0x0F0F)

8.  **Load negative signed halfword:**
    -   **Purpose:** Verify correct sign extension for negative halfword values (MSB is 1).
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = 0x20
    -   **Memory:** Memory location contains halfword value 0xF0F0 (negative signed halfword)
    -   **Expected Result:** rd = 0xFFFFF0F0 (sign-extended halfword 0xF0F0)

9.  **Load positive signed halfword:**
    -   **Purpose:** Verify correct sign extension for positive halfword values (MSB is 0).
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = 0x40
    -   **Memory:** Memory location contains halfword value 0x0808 (positive signed halfword)
    -   **Expected Result:** rd = 0x00000808 (sign-extended halfword 0x0808)
