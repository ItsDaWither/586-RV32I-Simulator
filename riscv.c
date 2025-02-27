#include "memory.h"
#include "decode.h"
#include "execute.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_REGISTERS 32 // This should not change (ISA-defined)

int main(int argc, char *argv[]) {
  const char *memfile = "program.mem";
  uint32_t start_address = 0;
  uint32_t stack_address = MEMORY_SIZE_BYTES;

  if (argc > 1)
    memfile = argv[1];
  if (argc > 2)
    start_address = (uint32_t)strtoul(argv[2], NULL, 0);
  if (argc > 3)
    stack_address = (uint32_t)strtoul(argv[3], NULL, 0);

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
  // minus 4 to make sure first instruction is correct
  uint32_t pc = start_address - 4;

  printf("Memory image loaded.\nStarting simulation at PC = 0x%08x, SP (x2) = "
         "0x%08x\n",
         pc, registers[2]);

  // End at PC = 0 (jr ra with ra == 0)
  while (1) {
    // inc first so if halt sets to zero function actually stops

    // Fetch
    uint32_t instruction = memory[pc / 4];

    // Decode
    Instruction decoded = decode_instruction(instruction);

    // Execute
    execute_instruction(decoded, registers, &pc, memory);
  }

  free(memory);
  return 0;
}
