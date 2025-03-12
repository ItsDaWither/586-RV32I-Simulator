# Test Plan for SH Instruction

## Instruction: SH (Store Halfword)

### Description
The SH (store halfword) instruction stores the least significant halfword (2 bytes) of register rs2 into memory at an address calculated by adding a signed 12-bit offset to the value in register rs1. The memory address must be halfword-aligned.

### Test Cases

1.  **Basic Store - Positive Offset:**
    -   **Purpose:** Verify basic halfword store with a positive offset.
    -   **Registers:** rs1 = address (e.g., 0x1000), rs2 = 0xABCDEF01
    -   **Offset:** offset = 0x10
    -   **Expected Result:** Memory location 0x1010 contains halfword value 0xEF01 (least significant halfword of rs2)

2.  **Basic Store - Negative Offset:**
    -   **Purpose:** Verify basic halfword store with a negative offset.
    -   **Registers:** rs1 = address (e.g., 0x2000), rs2 = 0x12345678
    -   **Offset:** offset = -0x10 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Expected Result:** Memory location 0x1FF0 contains halfword value 0x5678 (least significant halfword of rs2)

3.  **Store with Zero Offset:**
    -   **Purpose:** Verify halfword store with a zero offset.
    -   **Registers:** rs1 = address (e.g., 0x3000), rs2 = 0x55AA55AA
    -   **Offset:** offset = 0x0
    -   **Expected Result:** Memory location 0x3000 contains halfword value 0x55AA (least significant halfword of rs2)

4.  **Boundary Condition - Maximum Positive Offset:**
    -   **Purpose:** Test upper boundary of positive offset range.
    -   **Registers:** rs1 = address (e.g., 0x4000), rs2 = 0x80000000
    -   **Offset:** offset = 2046 (max positive offset for halfword alignment)
    -   **Expected Result:** Memory location 0x47FE contains halfword value 0x0000 (least significant halfword of rs2)

5.  **Boundary Condition - Maximum Negative Offset:**
    -   **Purpose:** Test lower boundary of negative offset range.
    -   **Registers:** rs1 = address (e.g., 0x5000), rs2 = 0x7FFFFFFF
    -   **Offset:** offset = -2048 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Expected Result:** Memory location 0x4800 contains halfword value 0xFFFF (least significant halfword of rs2)

6.  **Store Halfword with rs1 = 0:**
    -   **Purpose:** Verify store halfword when the base address register rs1 is zero.
    -   **Registers:** rs1 = 0, rs2 = 0xC0C0C0C0
    -   **Offset:** offset = 0x100
    -   **Expected Result:** Memory location 0x100 contains halfword value 0xC0C0 (least significant halfword of rs2)

7.  **Store to address 0:**
    -   **Purpose:** Test storing halfword to memory address 0.
    -   **Registers:** rs1 = 0, rs2 = 0x0F0F0F0F
    -   **Offset:** offset = 0
    -   **Expected Result:** Memory location 0x0 contains halfword value 0x0F0F (least significant halfword of rs2)

8.  **Store halfword value 0x0000:**
    -   **Purpose:** Verify storing zero halfword value.
    -   **Registers:** rs1 = address (e.g., 0x6000), rs2 = 0x00000000
    -   **Offset:** offset = 0x20
    -   **Expected Result:** Memory location 0x6020 contains halfword value 0x0000

9.  **Store halfword value 0xFFFF:**
    -   **Purpose:** Verify storing maximum halfword value.
    -   **Registers:** rs1 = address (e.g., 0x7000), rs2 = 0xFFFFFFFF
    -   **Offset:** offset = 0x40
    -   **Expected Result:** Memory location 0x7040 contains halfword value 0xFFFF
