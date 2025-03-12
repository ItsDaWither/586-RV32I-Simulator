# Test Plan for LB Instruction

## Instruction: LB (Load Byte)

### Description
The LB (load byte) instruction loads a byte from memory at an address calculated by adding a signed 12-bit offset to the value in register rs1. The loaded byte is sign-extended to 32 bits and written to register rd.

### Test Cases

1.  **Basic Load - Positive Offset:**
    -   **Purpose:** Verify basic byte load with a positive offset.
    -   **Registers:** rs1 = address of byte in memory (e.g., 0x1000), rd = any
    -   **Offset:** offset = 0x10
    -   **Memory:** Memory location 0x1010 contains byte value 0xAB
    -   **Expected Result:** rd = 0xFFFFFFAB (sign-extended byte 0xAB)

2.  **Basic Load - Negative Offset:**
    -   **Purpose:** Verify basic byte load with a negative offset.
    -   **Registers:** rs1 = address (e.g., 0x2000), rd = any
    -   **Offset:** offset = -0x10 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Memory:** Memory location 0x1FF0 contains byte value 0x12
    -   **Expected Result:** rd = 0x00000012 (sign-extended byte 0x12)

3.  **Load with Zero Offset:**
    -   **Purpose:** Verify byte load with a zero offset.
    -   **Registers:** rs1 = address (e.g., 0x3000), rd = any
    -   **Offset:** offset = 0x0
    -   **Memory:** Memory location 0x3000 contains byte value 0x55
    -   **Expected Result:** rd = 0x00000055 (sign-extended byte 0x55)

4.  **Boundary Condition - Maximum Positive Offset:**
    -   **Purpose:** Test upper boundary of positive offset range.
    -   **Registers:** rs1 = address (e.g., 0x4000), rd = any
    -   **Offset:** offset = 2047
    -   **Memory:** Memory location 0x47FF contains byte value 0x80 (negative signed byte)
    -   **Expected Result:** rd = 0xFFFFFF80 (sign-extended byte 0x80)

5.  **Boundary Condition - Maximum Negative Offset:**
    -   **Purpose:** Test lower boundary of negative offset range.
    -   **Registers:** rs1 = address (e.g., 0x5000), rd = any
    -   **Offset:** offset = -2048 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Memory:** Memory location 0x4800 contains byte value 0x7F (positive signed byte)
    -   **Expected Result:** rd = 0x0000007F (sign-extended byte 0x7F)

6.  **Load Byte with rs1 = 0:**
    -   **Purpose:** Verify load byte when the base address register rs1 is zero.
    -   **Registers:** rs1 = 0, rd = any
    -   **Offset:** offset = 0x100
    -   **Memory:** Memory location 0x100 contains byte value 0xC3 (negative signed byte)
    -   **Expected Result:** rd = 0xFFFFFFC3 (sign-extended byte 0xC3)

7.  **Load from address 0:**
    -   **Purpose:** Test loading byte from memory address 0.
    -   **Registers:** rs1 = 0, rd = any
    -   **Offset:** offset = 0
    -   **Memory:** Memory location 0x0 contains byte value 0x0F (positive signed byte)
    -   **Expected Result:** rd = 0x0000000F (sign-extended byte 0x0F)

8.  **Load negative signed byte:**
    -   **Purpose:** Verify correct sign extension for negative byte values (MSB is 1).
    -   **Registers:** rs1 = address (e.g., 0x6000), rd = any
    -   **Offset:** offset = 0x20
    -   **Memory:** Memory location 0x6020 contains byte value 0xF0 (negative signed byte)
    -   **Expected Result:** rd = 0xFFFFFFF0 (sign-extended byte 0xF0)

9.  **Load positive signed byte:**
    -   **Purpose:** Verify correct sign extension for positive byte values (MSB is 0).
    -   **Registers:** rs1 = address (e.g., 0x7000), rd = any
    -   **Offset:** offset = 0x40
    -   **Memory:** Memory location 0x7040 contains byte value 0x08 (positive signed byte)
    -   **Expected Result:** rd = 0x00000008 (sign-extended byte 0x08)
