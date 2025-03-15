# Test Plan for ECALL Instruction

## Instruction: ECALL (Environment Call)

### Description
The ECALL (environment call) instruction makes a request to the execution environment. The behavior of ECALL is determined by the specific environment and the value in register a7 (x17). In this simulator, ECALL with a7 = 94 will halt the simulator.

### Test Cases

1.  **ECALL with a7 = 94 (Halt):**
    -   **Purpose:** Verify that ECALL with a7 = 94 halts the simulator.
    -   **Registers:** a7 = 94, rd = any, rs1 = any, rs2 = any
    -   **Expected Result:** The simulator should halt execution.

2.  **ECALL with a7 != 94 (Unknown ECALL):**
    -   **Purpose:** Verify that ECALL with a7 != 94 prints an error message and halts the simulator.
    -   **Registers:** a7 = 1, rd = any, rs1 = any, rs2 = any
    -   **Expected Result:** The simulator should print an error message to stderr and halt execution.
