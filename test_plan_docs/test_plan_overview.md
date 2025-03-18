# RISC-V Simulator Test Plan - Overview

The RISC-V Simulator simulates the RV32I instruction set, with the exclusion of some instructions. We perform functional testing of the simulator using two methods: unit tests via assembly files and snippets of C code.

## Test Documentation Structure
The test plan documentation includes:
- **Overview Document:** A high-level overview of the test plan.
- **Instruction-Specific Test Plans:** Detailed descriptions of the test cases for each instruction, located in the `test_plan_docs` directory.
- **Assembly Test Files:** Assembly examples for each test case, located in the `assembly_tests` directory under instruction-specific subdirectories. Assembly tests serve to unit-test the functionality of each instruction standalone.
- **C Test Cases:** There are a number of C code snippets in the `c_tests` directory designed to verify the behavior of standard C constructs in the simulator. These tests serve to ensure the simulator works on longer test files with significant functional output.

## Instructions Tested
The following RV32I instructions are included:
- ADD
- ADDI
- AND
- ANDI
- AUIPC
- BEQ
- BGE
- BGEU
- BLT
- BLTU
- BNE
- ECALL
- JAL
- JALR
- LB
- LBU
- LH
- LHU
- LUI
- LW
- OR
- ORI
- SB
- SH
- SLL
- SLLI
- SLT
- SLTI
- SLTIU
- SLTU
- SRA
- SRAI
- SRL
- SRLI
- SUB
- SW
- XOR
- XORI

TODO: Implement instructions from M and F extensions
