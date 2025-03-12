# Test Plan for LHU Instruction

## Instruction: LHU (Load Halfword Unsigned)

### Description
The LHU (load halfword unsigned) instruction loads a 2-byte halfword from memory at an address calculated by adding a signed 12-bit offset to the value in register rs1. The loaded halfword is zero-extended to 32 bits and written to register rd. The memory address must be halfword-aligned.

### Test Cases

1.  **Basic Load - Positive Offset:**
    -   **Purpose:** Verify basic unsigned halfword load with a positive offset.
    -   **Registers:** rs1 = address of halfword in memory (e.g., 0x1000), rd = any
    -   **Offset:** offset = 0x10
    -   **Memory:** Memory location 0x1010 contains halfword value 0xCDEF
    -   **Expected Result:** rd = 0x0000CDEF (zero-extended halfword 0xCDEF)

2.  **Basic Load - Negative Offset:**
    -   **Purpose:** Verify basic unsigned halfword load with a negative offset.
    -   **Registers:** rs1 = address (e.g., 0x2000), rd = any
    -   **Offset:** offset = -0x10 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Memory:** Memory location 0x1FF0 contains halfword value 0x1234
    -   **Expected Result:** rd = 0x00001234 (zero-extended halfword 0x1234)

3.  **Load with Zero Offset:**
    -   **Purpose:** Verify unsigned halfword load with a zero offset.
    -   **Registers:** rs1 = address (e.g., 0x3000), rd = any
    -   **Offset:** offset = 0x0
    -   **Memory:** Memory location 0x3000 contains halfword value 0x55AA
    -   **Expected Result:** rd = 0x000055AA (zero-extended halfword 0x55AA)

4.  **Boundary Condition - Maximum Positive Offset:**
    -   **Purpose:** Test upper boundary of positive offset range.
    -   **Registers:** rs1 = address (e.g., 0x4000), rd = any
    -   **Offset:** offset = 2046 (max positive offset for halfword alignment)
    -   **Memory:** Memory location 0x47FE contains halfword value 0x8000 (negative signed halfword, positive unsigned halfword)
    -   **Expected Result:** rd = 0x00008000 (zero-extended halfword 0x8000)

5.  **Boundary Condition - Maximum Negative Offset:**
    -   **Purpose:** Test lower boundary of negative offset range.
    -   **Registers:** rs1 = address (e.g., 0x5000), rd = any
    -   **Offset:** offset = -2048 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Memory:** Memory location 0x4800 contains halfword value 0xFFFF (maximum unsigned halfword)
    -   **Expected Result:** rd = 0x0000FFFF (zero-extended halfword 0xFFFF)

6.  **Load Halfword with rs1 = 0:**
    -   **Purpose:** Verify load unsigned halfword when the base address register rs1 is zero.
    -   **Registers:** rs1 = 0, rd = any
    -   **Offset:** offset = 0x100
    -   **Memory:** Memory location 0x100 contains halfword value 0xC0C0 (negative signed halfword, positive unsigned halfword)
    -   **Expected Result:** rd = 0x0000C0C0 (zero-extended halfword 0xC0C0)

7.  **Load from address 0:**
    -   **Purpose:** Test loading unsigned halfword from memory address 0.
    -   **Registers:** rs1 = 0, rd = any
    -   **Offset:** offset = 0
    -   **Memory:** Memory location 0x0 contains halfword value 0x0F0F (positive signed halfword)
    -   **Expected Result:** rd = 0x00000F0F (zero-extended halfword 0x0F0F)

8.  **Load maximum unsigned halfword:**
    -   **Purpose:** Verify correct zero extension for maximum unsigned halfword value (0xFFFF).
    -   **Registers:** rs1 = address (e.g., 0x6000), rd = any
    -   **Offset:** offset = 0x20
    -   **Memory:** Memory location 0x6020 contains halfword value 0xFFFF (maximum unsigned halfword)
    -   **Expected Result:** rd = 0x0000FFFF (zero-extended halfword 0xFFFF)

9.  **Load zero halfword:**
    -   **Purpose:** Verify correct zero extension for zero halfword value (0x0000).
    -   **Registers:** rs1 = address (e.g., 0x7000), rd = any
    -   **Offset:** offset = 0x40
    -   **Memory:** Memory location 0x7040 contains halfword value 0x0000 (zero halfword)
    -   **Expected Result:** rd = 0x00000000 (zero-extended halfword 0x0000)
