# Test Plan for JAL Instruction

## Instruction: JAL (Jump and Link)

### Description
The JAL (jump and link) instruction jumps to a target address by adding a signed 20-bit offset to the PC. It also saves the address of the instruction following the jump (return address) into the destination register rd.

### Test Cases

1.  **Basic Jump - Positive Offset:**
    -   **Purpose:** Verify basic jump with a positive offset.
    -   **Registers:** rd = any, PC = current PC
    -   **Offset:** offset = 0x100 (represented as 20-bit signed offset in assembly)
    -   **Expected Result:** PC = current PC + 0x100, rd = current PC + 4 (return address)

2.  **Basic Jump - Negative Offset:**
    -   **Purpose:** Verify basic jump with a negative offset.
    -   **Registers:** rd = any, PC = current PC
    -   **Offset:** offset = -0x100 (represented as 2's complement 20-bit signed offset in assembly)
    -   **Expected Result:** PC = current PC - 0x100, rd = current PC + 4 (return address)

3.  **Jump with Zero Offset:**
    -   **Purpose:** Verify jump with a zero offset.
    -   **Registers:** rd = any, PC = current PC
    -   **Offset:** offset = 0x0
    -   **Expected Result:** PC = current PC, rd = current PC + 4 (return address)
