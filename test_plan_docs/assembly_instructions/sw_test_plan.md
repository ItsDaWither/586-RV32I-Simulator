# Test Plan for SW Instruction

## Instruction: SW (Store Word)

### Description
The SW (store word) instruction stores the entire 32-bit value of register rs2 into memory at an address calculated by adding a signed 12-bit offset to the value in register rs1. The memory address must be word-aligned.

### Test Cases

1.  **Basic Store - Positive Offset:**
    -   **Purpose:** Verify basic word store with a positive offset.
    -   **Registers:** rs1 = address, rs2 = 0xABCDEF01
    -   **Offset:** offset = 0x10
    -   **Expected Result:** Memory location contains word value 0xABCDEF01

2.  **Basic Store - Negative Offset:**
    -   **Purpose:** Verify basic word store with a negative offset.
    -   **Registers:** rs1 = address, rs2 = 0x12345678
    -   **Offset:** offset = -0x10 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Expected Result:** Memory location contains word value 0x12345678

3.  **Store with Zero Offset:**
    -   **Purpose:** Verify word store with a zero offset.
    -   **Registers:** rs1 = address, rs2 = 0x55AA55AA
    -   **Offset:** offset = 0x0
    -   **Expected Result:** Memory location contains word value 0x55AA55AA

4.  **Boundary Condition - Maximum Positive Offset:**
    -   **Purpose:** Test upper boundary of positive offset range.
    -   **Registers:** rs1 = address, rs2 = 0x80000000
    -   **Offset:** offset = 2044 (max positive offset for word alignment)
    -   **Expected Result:** Memory location contains word value 0x80000000

5.  **Boundary Condition - Maximum Negative Offset:**
    -   **Purpose:** Test lower boundary of negative offset range.
    -   **Registers:** rs1 = address, rs2 = 0x7FFFFFFF
    -   **Offset:** offset = -2048 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Expected Result:** Memory location contains word value 0x7FFFFFFF

6.  **Store Word with rs1 = 0:**
    -   **Purpose:** Verify store word when the base address register rs1 is zero.
    -   **Registers:** rs1 = 0, rs2 = 0xC0C0C0C0
    -   **Offset:** offset = 0x100
    -   **Expected Result:** Memory location contains word value 0xC0C0C0C0

7.  **Store to address 0:**
    -   **Purpose:** Test storing word to memory address 0.
    -   **Registers:** rs1 = 0, rs2 = 0x0F0F0F0F
    -   **Offset:** offset = 0
    -   **Expected Result:** Memory location contains word value 0x0F0F0F0F

8.  **Store negative signed word:**
    -   **Purpose:** Verify storing negative signed word values (MSB is 1).
    -   **Registers:** rs1 = address, rs2 = 0xF0F0F0F0
    -   **Offset:** offset = 0x20
    -   **Expected Result:** Memory location contains word value 0xF0F0F0F0

9.  **Store positive signed word:**
    -   **Purpose:** Verify storing positive signed word values (MSB is 0).
    -   **Registers:** rs1 = address, rs2 = 0x08080808
    -   **Offset:** offset = 0x40
    -   **Expected Result:** Memory location contains word value 0x08080808

10. **Store maximum positive and negative word values:**
    -   **Purpose:** Verify storing maximum positive and negative word values.
    -   **Registers:** rs1 = address, rs2 = 0x7FFFFFFF (max positive), rs3 = 0x80000000 (max negative)
    -   **Offset:** offset = 0x0, offset2 = 0x4
    -   **Expected Result:** Memory location contains word value 0x7FFFFFFF, Memory location contains word value 0x80000000
