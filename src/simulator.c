#include "simulator.h"
#include "memory.h"
#include "decode.h"
#include "execute.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_REGISTERS 32

int run_simulator(int verbose_mode,
                  const char *memfile,
                  uint32_t start_address,
                  uint32_t stack_address)
{
    // Allocate memory
    uint32_t *memory = calloc(MEMORY_WORDS, sizeof(uint32_t));
    if (!memory) {
        fprintf(stderr, "Error: Unable to allocate memory\n");
        return 1;
    }

    // Load memory image
    if (load_memory_image(memfile, memory, MEMORY_WORDS) != 0) {
        fprintf(stderr, "Error loading memory image\n");
        free(memory);
        return 1;
    }

    // Initialize registers. x0 is always zero by convention
    uint32_t registers[NUM_REGISTERS] = {0};
    registers[2] = stack_address; // x2 is the stack pointer

    // PC
    uint32_t pc = start_address;

    printf("Memory image loaded.\n");
    printf("Starting simulation at PC=0x%08x, SP(x2)=0x%08x\n",
           pc, registers[2]);

    // Simulation loop. End when pc=0 or invalid instruction
    while (1) {
        // fetch
        uint32_t instruction = memory[pc / 4];

        // decode
        Instruction decoded = decode_instruction(instruction);

        if (verbose_mode) {
            printf("PC: 0x%08x, Instruction: 0x%08x\n", pc, instruction);
        }

        // execute
        int failure = execute_instruction(decoded, registers, &pc, memory);
        if (failure) {
            printf("Simulation halt -- zero or invalid instruction.\n");
            break;
        }

        if (verbose_mode) {
            printf("Registers After Execution:\n");
            for (int i = 0; i < NUM_REGISTERS; i++) {
                printf("x%d: 0x%08x ", i, registers[i]);
                if ((i + 1) % 4 == 0) {
                    printf("\n");
                }
            }
            printf("\n");
        }

        registers[0] = 0;  // enforce x0=0
        pc += 4;

        // if pc==0, that’s our condition to end
        if (pc == 0) {
            break;
        }
    }

    printf("Final PC: 0x%08x\n", pc);
    printf("Registers:\n");
    for (int i = 0; i < NUM_REGISTERS; i++) {
        printf("x%d: 0x%08x ", i, registers[i]);
        if ((i + 1) % 4 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    print_memory(memory, MEMORY_WORDS);

    free(memory);
    return 0; // success
}
