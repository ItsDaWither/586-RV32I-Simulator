#include "memory.h"
#include "decode.h"
#include "execute.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_REGISTERS 32 // This should not change (ISA-defined)

int main(int argc, char *argv[]) {
  const char *memfile = "program.mem";
  uint32_t start_address = 0;
  uint32_t stack_address = MEMORY_SIZE_BYTES;
  int verbose_mode = 0;

  if (argc > 1) {
    if (strcmp(argv[1], "verbose") == 0) {
      verbose_mode = 1;
    } else if (strcmp(argv[1], "silent") == 0) {
      verbose_mode = 0;
    } else {
      printf("Invalid verbosity, defaulting to silent");
    }
  }
  if (argc > 2) {
    memfile = argv[2];
  }
  if (argc > 3) {
    start_address = (uint32_t)strtoul(argv[3], NULL, 0);
  }
  if (argc > 4) {
    stack_address = (uint32_t)strtoul(argv[4], NULL, 0);
  }

  // Allocate memory as an array of 32-bit words.
  uint32_t *memory = calloc(MEMORY_WORDS, sizeof(uint32_t));
  if (!memory) {
    fprintf(stderr, "Error: Unable to allocate memory\n");
    return 1;
  }
  if (load_memory_image(memfile, memory, MEMORY_WORDS) != 0) {
    fprintf(stderr, "Error loading memory image\n");
    free(memory);
    return 1;
  }

  // Initialize registers. x0 is hardwired to 0.
  uint32_t registers[NUM_REGISTERS] = {0};
  registers[2] = stack_address; // x2 is the stack pointer.
  registers[1] = 0;

  // Set the program counter.
  uint32_t pc = start_address;

  printf("Memory image loaded.\nStarting simulation at PC = 0x%08x, SP (x2) = "
         "0x%08x\n",
         pc, registers[2]);

  // End at PC = 0 (jr ra with ra == 0)
  while (1) {
    // Fetch
    uint32_t instruction = memory[pc / 4];

    // Decode
    Instruction decoded = decode_instruction(instruction);

    if (verbose_mode) {
      printf("PC: 0x%08x, Instruction: 0x%08x\n", pc, instruction);
    }

    // Execute
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

    pc = pc + 4;
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
  return 0;
}
