# Test Plan for JALR Instruction

## Instruction: JALR (Jump and Link Register)

### Description
The JALR (jump and link register) instruction jumps to a target address calculated by adding a signed 12-bit offset to the value in register rs1. The least significant bit of the target address is forced to zero. It saves the address of the instruction following the jump (return address) into the destination register rd.  If rd is x0, no return address is saved. If rs1 is x0, the jump target is effectively just the offset.

### Test Cases

1.  **Basic Jump - Positive Offset:**
    -   **Purpose:** Verify basic jump with a positive offset and register value.
    -   **Registers:** rs1 = 0x1000, rd = any
    -   **Offset:** offset = 0x10 (represented as 12-bit signed offset in assembly)
    -   **Expected Result:** Jump Taken

2.  **Basic Jump - Negative Offset:**
    -   **Purpose:** Verify basic jump with a negative offset and register value.
    -   **Registers:** rs1 = 0x2000, rd = any
    -   **Offset:** offset = -0x10 (represented as 2's complement 12-bit signed offset in assembly)
    -   **Expected Result:** Jump Taken

3.  **Jump with Zero Offset:**
    -   **Purpose:** Verify jump with a zero offset.
    -   **Registers:** rs1 = 0x3000, rd = any
    -   **Offset:** offset = 0x0
    -   **Expected Result:** Jump Taken

4.  **JALR when rs1 is x0:**
    -   **Purpose:** Verify that JALR instruction works correctly when rs1 is x0, effectively jumping to the offset from zero.
    -   **Registers:** rs1 = x0, rd = any
    -   **Offset:** offset = 0x400
    -   **Expected Result:** Jump Taken

5. **Forced zero LSB of target address:**
    -   **Purpose:** Verify that the least significant bit of the calculated target address is always forced to zero.
    -   **Registers:** rs1 = 0x1235, rd = any
    -   **Offset:** offset = 0x0
    -   **Expected Result:** Jump Taken
