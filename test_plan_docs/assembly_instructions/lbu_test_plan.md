# Test Plan for LBU Instruction

## Instruction: LBU (Load Byte Unsigned)

### Description
The LBU (load byte unsigned) instruction loads a byte from memory at an address calculated by adding a signed 12-bit offset to the value in register rs1. The loaded byte is zero-extended to 32 bits and written to register rd.

### Test Cases

1.  **Basic Load - Positive Offset:**
    -   **Purpose:** Verify basic unsigned byte load with a positive offset.
    -   **Registers:** rs1 = address of byte in memory, rd = any
    -   **Offset:** offset = 0x10
    -   **Memory:** Memory location contains byte value 0xAB
    -   **Expected Result:** rd = 0x000000AB (zero-extended byte 0xAB)

2.  **Basic Load - Negative Offset:**
    -   **Purpose:** Verify basic unsigned byte load with a negative offset.
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = -0x10 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Memory:** Memory location contains byte value 0x12
    -   **Expected Result:** rd = 0x00000012 (zero-extended byte 0x12)

3.  **Load with Zero Offset:**
    -   **Purpose:** Verify unsigned byte load with a zero offset.
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = 0x0
    -   **Memory:** Memory location contains byte value 0x55
    -   **Expected Result:** rd = 0x00000055 (zero-extended byte 0x55)

4.  **Boundary Condition - Maximum Positive Offset:**
    -   **Purpose:** Test upper boundary of positive offset range.
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = 2047
    -   **Memory:** Memory location contains byte value 0x80 (negative signed byte, positive unsigned byte)
    -   **Expected Result:** rd = 0x00000080 (zero-extended byte 0x80)

5.  **Boundary Condition - Maximum Negative Offset:**
    -   **Purpose:** Test lower boundary of negative offset range.
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = -2048 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Memory:** Memory location contains byte value 0xFF (maximum unsigned byte)
    -   **Expected Result:** rd = 0x000000FF (zero-extended byte 0xFF)

6.  **Load Byte with rs1 = 0:**
    -   **Purpose:** Verify load unsigned byte when the base address register rs1 is zero.
    -   **Registers:** rs1 = 0, rd = any
    -   **Offset:** offset = 0x100
    -   **Memory:** Memory location contains byte value 0xC3 (negative signed byte, positive unsigned byte)
    -   **Expected Result:** rd = 0x000000C3 (zero-extended byte 0xC3)

7.  **Load from address 0:**
    -   **Purpose:** Test loading unsigned byte from memory address 0.
    -   **Registers:** rs1 = 0, rd = any
    -   **Offset:** offset = 0
    -   **Memory:** Memory location contains byte value 0x0F (positive signed byte)
    -   **Expected Result:** rd = 0x0000000F (zero-extended byte 0x0F)

8.  **Load maximum unsigned byte:**
    -   **Purpose:** Verify correct zero extension for maximum unsigned byte value (0xFF).
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = 0x20
    -   **Memory:** Memory location contains byte value 0xFF (maximum unsigned byte)
    -   **Expected Result:** rd = 0x000000FF (zero-extended byte 0xFF)

9.  **Load zero byte:**
    -   **Purpose:** Verify correct zero extension for zero byte value (0x00).
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = 0x40
    -   **Memory:** Memory location contains byte value 0x00 (zero byte)
    -   **Expected Result:** rd = 0x00000000 (zero-extended byte 0x00)
