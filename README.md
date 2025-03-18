# RISC-V Simulator Project Overview
This project implements a simulator for the RISC-V RV32I base integer instruction set. As it currently stands, it implements all the basic functionality of the RV32I as defined in chapter 2 of the ISA. A GUI has also been created to simplify the execution process for the user.

## Usage
```
	make
	./riscv <single|verbose|silent> [memory file] [start address] [stack address]
```

Mode `silent` runs the entire file silently, then prints the ending registers and all non-zero memory locations.
Mode `verbose` prints the register contents after every instruction.
Mode `single` is used to execute a file one instruction at a time. `single` implies `verbose`.

## Extra Credit Attempted:
- Ability to single-step program execution
- GUI interface

## Future Work
- [ ] Implement instructions from the RV32M extension
- [ ] Implement instructions from the RV32F extension
- [ ] Implement syscalls for the `ecall` instruction


## Developer Information

### Running Tests
The automated test system is reliant on the `riscv64-elf-newlib` toolchain as packaged for Arch Linux. Some modifications to the test scripts may be required for other distributions.

To run the assembly testcases, perform
```python
	python assemblytomem.py
	python runassemblytests.py
```
If the tests are successful, you will see `All tests passed!` printed to the terminal.

To run C testcases, run
```python
	python ctomem.py
```
which will compile all C files into `.mem` files for the simulator. At the moment, the functional correctness of these mem files must be verified by hand.