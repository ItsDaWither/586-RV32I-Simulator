# Test Plan for SB Instruction

## Instruction: SB (Store Byte)

### Description
The SB (store byte) instruction stores the least significant byte of register rs2 into memory at an address calculated by adding a signed 12-bit offset to the value in register rs1.

### Test Cases

1.  **Basic Store - Positive Offset:**
    -   **Purpose:** Verify basic byte store with a positive offset.
    -   **Registers:** rs1 = address (e.g., 0x1000), rs2 = 0xABCDEF01
    -   **Offset:** offset = 0x10
    -   **Expected Result:** Memory location 0x1010 contains byte value 0x01 (least significant byte of rs2)

2.  **Basic Store - Negative Offset:**
    -   **Purpose:** Verify basic byte store with a negative offset.
    -   **Registers:** rs1 = address (e.g., 0x2000), rs2 = 0x12345678
    -   **Offset:** offset = -0x10 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Expected Result:** Memory location 0x1FF0 contains byte value 0x78 (least significant byte of rs2)

3.  **Store with Zero Offset:**
    -   **Purpose:** Verify byte store with a zero offset.
    -   **Registers:** rs1 = address (e.g., 0x3000), rs2 = 0x55AA55AA
    -   **Offset:** offset = 0x0
    -   **Expected Result:** Memory location 0x3000 contains byte value 0xAA (least significant byte of rs2)

4.  **Boundary Condition - Maximum Positive Offset:**
    -   **Purpose:** Test upper boundary of positive offset range.
    -   **Registers:** rs1 = address (e.g., 0x4000), rs2 = 0x80000000
    -   **Offset:** offset = 2047
    -   **Expected Result:** Memory location 0x47FF contains byte value 0x00 (least significant byte of rs2)

5.  **Boundary Condition - Maximum Negative Offset:**
    -   **Purpose:** Test lower boundary of negative offset range.
    -   **Registers:** rs1 = address (e.g., 0x5000), rs2 = 0x7FFFFFFF
    -   **Offset:** offset = -2048 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Expected Result:** Memory location 0x4800 contains byte value 0xFF (least significant byte of rs2)

6.  **Store Byte with rs1 = 0:**
    -   **Purpose:** Verify store byte when the base address register rs1 is zero.
    -   **Registers:** rs1 = 0, rs2 = 0xC0C0C0C0
    -   **Offset:** offset = 0x100
    -   **Expected Result:** Memory location 0x100 contains byte value 0xC0 (least significant byte of rs2)

7.  **Store to address 0:**
    -   **Purpose:** Test storing byte to memory address 0.
    -   **Registers:** rs1 = 0, rs2 = 0x0F0F0F0F
    -   **Offset:** offset = 0
    -   **Expected Result:** Memory location 0x0 contains byte value 0x0F (least significant byte of rs2)

8.  **Store byte value 0x00:**
    -   **Purpose:** Verify storing zero byte value.
    -   **Registers:** rs1 = address (e.g., 0x6000), rs2 = 0x00000000
    -   **Offset:** offset = 0x20
    -   **Expected Result:** Memory location 0x6020 contains byte value 0x00

9.  **Store byte value 0xFF:**
    -   **Purpose:** Verify storing maximum byte value.
    -   **Registers:** rs1 = address (e.g., 0x7000), rs2 = 0xFFFFFFFF
    -   **Offset:** offset = 0x40
    -   **Expected Result:** Memory location 0x7040 contains byte value 0xFF
