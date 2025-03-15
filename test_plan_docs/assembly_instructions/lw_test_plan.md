# Test Plan for LW Instruction

## Instruction: LW (Load Word)

### Description
The LW (load word) instruction loads a 4-byte word from memory at an address calculated by adding a signed 12-bit offset to the value in register rs1. The loaded word is written to register rd. The memory address must be word-aligned.

### Test Cases

1.  **Basic Load - Positive Offset:**
    -   **Purpose:** Verify basic word load with a positive offset.
    -   **Registers:** rs1 = address of word in memory, rd = any
    -   **Offset:** offset = 0x10
    -   **Memory:** Memory location contains word value 0xABCDEF01
    -   **Expected Result:** rd = 0xABCDEF01

2.  **Basic Load - Negative Offset:**
    -   **Purpose:** Verify basic word load with a negative offset.
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = -0x10 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Memory:** Memory location contains word value 0x12345678
    -   **Expected Result:** rd = 0x12345678

3.  **Load with Zero Offset:**
    -   **Purpose:** Verify word load with a zero offset.
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = 0x0
    -   **Memory:** Memory location contains word value 0x55AA55AA
    -   **Expected Result:** rd = 0x55AA55AA

4.  **Boundary Condition - Maximum Positive Offset:**
    -   **Purpose:** Test upper boundary of positive offset range.
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = 2044 (max positive offset for word alignment)
    -   **Memory:** Memory location contains word value 0x80000000 (negative signed word)
    -   **Expected Result:** rd = 0x80000000

5.  **Boundary Condition - Maximum Negative Offset:**
    -   **Purpose:** Test lower boundary of negative offset range.
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = -2048 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Memory:** Memory location contains word value 0x7FFFFFFF (positive signed word)
    -   **Expected Result:** rd = 0x7FFFFFFF

6.  **Load Word with rs1 = 0:**
    -   **Purpose:** Verify load word when the base address register rs1 is zero.
    -   **Registers:** rs1 = 0, rd = any
    -   **Offset:** offset = 0x100
    -   **Memory:** Memory location contains word value 0xC0C0C0C0 (negative signed word)
    -   **Expected Result:** rd = 0xC0C0C0C0

7.  **Load from address 0:**
    -   **Purpose:** Test loading word from memory address 0.
    -   **Registers:** rs1 = 0, rd = any
    -   **Offset:** offset = 0
    -   **Memory:** Memory location contains word value 0x0F0F0F0F (positive signed word)
    -   **Expected Result:** rd = 0x0F0F0F0F

8.  **Load negative signed word:**
    -   **Purpose:** Verify loading negative signed word values (MSB is 1).
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = 0x20
    -   **Memory:** Memory location contains word value 0xF0F0F0F0 (negative signed word)
    -   **Expected Result:** rd = 0xF0F0F0F0

9.  **Load positive signed word:**
    -   **Purpose:** Verify loading positive signed word values (MSB is 0).
    -   **Registers:** rs1 = address, rd = any
    -   **Offset:** offset = 0x40
    -   **Memory:** Memory location contains word value 0x08080808 (positive signed word)
    -   **Expected Result:** rd = 0x08080808
