#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE_BYTES (64 * 1024)        // 64KB total memory size.
#define MEMORY_WORDS (MEMORY_SIZE_BYTES / 4) // Number of 32-bit words.
#define NUM_REGISTERS 32 // This should not change (ISA-defined)
#define MAX_LINE_LENGTH 256

// Loads a memory image file with lines like "0: fd010113"
// into an array of 32-bit words. The address in the file is a byte address,
// which must be word aligned.
int load_memory_image(const char *filename, uint32_t *memory,
                      size_t num_words) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    fprintf(stderr, "Error: Cannot open file '%s'\n", filename);
    return 1;
  }
  char line[MAX_LINE_LENGTH];
  uint32_t address, word;
  while (fgets(line, sizeof(line), fp)) {
    if (line[0] == '\n' || line[0] == '#')
      continue;
    if (sscanf(line, "%x: %x", &address, &word) != 2) {
      fprintf(stderr, "Warning: Invalid line format: %s", line);
      continue;
    }
    if (address % 4 != 0) {
      fprintf(stderr, "Warning: Address 0x%x not word aligned, skipping.\n",
              address);
      continue;
    }
    size_t index = address / 4;
    if (index >= num_words) {
      fprintf(stderr, "Warning: Address 0x%x out of bounds, skipping.\n",
              address);
      continue;
    }
    memory[index] = word;
  }
  fclose(fp);
  return 0;
}

// Read 1 byte from memory.
uint8_t read_memory_1(uint32_t *memory, uint32_t address) {
  if (address >= MEMORY_SIZE_BYTES) {
    fprintf(stderr, "Error: read_memory_1: address 0x%x out of bounds\n",
            address);
    exit(1);
  }
  size_t index = address / 4;
  int offset = address % 4;
  return (memory[index] >> (offset * 8)) & 0xFF;
}

// Read 2 bytes (halfword) from memory.  Handles unaligned accesses.
uint16_t read_memory_2(uint32_t *memory, uint32_t address) {
  if (address >= MEMORY_SIZE_BYTES) {
    fprintf(stderr, "Error: read_memory_2: address 0x%x out of bounds\n",
            address);
    exit(1);
  }
  if ((address & 1) == 0) { // Aligned access
    size_t index = address / 4;
    int offset = address % 4;
    return (memory[index] >> (offset * 8)) & 0xFFFF;
  } else { // Unaligned
    uint16_t low = read_memory_1(memory, address);
    uint16_t high = read_memory_1(memory, address + 1);
    return low | (high << 8);
  }
}

// Read 4 bytes (word) from memory. Handles unaligned accesses.
uint32_t read_memory_4(uint32_t *memory, uint32_t address) {
  if (address >= MEMORY_SIZE_BYTES) {
    fprintf(stderr, "Error: read_memory_4: address 0x%x out of bounds\n",
            address);
    exit(1);
  }
  if ((address & 3) == 0) { // Aligned access
    return memory[address / 4];
  } else { // Unaligned
    uint32_t value = 0;
    for (int i = 0; i < 4; i++) {
      value |= ((uint32_t)read_memory_1(memory, address + i)) << (i * 8);
    }
    return value;
  }
}

// Write 1 byte to memory.
void write_memory_1(uint32_t *memory, uint32_t address, uint8_t value) {
  if (address >= MEMORY_SIZE_BYTES) {
    fprintf(stderr, "Error: write_memory_1: address 0x%x out of bounds\n",
            address);
    exit(1);
  }
  size_t index = address / 4;
  int offset = address % 4;
  memory[index] = (memory[index] & ~(0xFFu << (offset * 8))) |
                  ((uint32_t)value << (offset * 8));
}

// Write 2 bytes (halfword) to memory.  Handles unaligned accesses.
void write_memory_2(uint32_t *memory, uint32_t address, uint16_t value) {
  if (address >= MEMORY_SIZE_BYTES) {
    fprintf(stderr, "Error: write_memory_2: address 0x%x out of bounds\n",
            address);
    exit(1);
  }
  if ((address & 1) == 0) { // Aligned
    size_t index = address / 4;
    int offset = address % 4;
    memory[index] = (memory[index] & ~(0xFFFFu << (offset * 8))) |
                    ((uint32_t)value << (offset * 8));
  } else { // Unaligned
    write_memory_1(memory, address, (uint8_t)(value & 0xFF));
    write_memory_1(memory, address + 1, (uint8_t)((value >> 8) & 0xFF));
  }
}

// Write 4 bytes (word) to memory. Handles unaligned accesses.
void write_memory_4(uint32_t *memory, uint32_t address, uint32_t value) {
  if (address >= MEMORY_SIZE_BYTES) {
    fprintf(stderr, "Error: write_memory_4: address 0x%x out of bounds\n",
            address);
    exit(1);
  }
  if ((address & 3) == 0) { // Aligned access
    memory[address / 4] = value;
  } else { // Unaligned
    for (int i = 0; i < 4; i++) {
      write_memory_1(memory, address + i, (uint8_t)((value >> (i * 8)) & 0xFF));
    }
  }
}

int main(int argc, char *argv[]) {
  const char *memfile = "program.mem";
  uint32_t start_address = 0;
  uint32_t stack_address =
      MEMORY_SIZE_BYTES; // Default stack pointer at end of memory.

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
  registers[1] =
      0; // x1 (return address) is set to 0 to signal simulation termination.

  // Set the program counter.
  uint32_t pc = start_address;

  printf("Memory image loaded.\nStarting simulation at PC = 0x%08x, SP (x2) = "
         "0x%08x\n",
         pc, registers[2]);

  // Example usage of the memory read/write functions:
  uint32_t test_addr = 0x1001;
  write_memory_4(memory, test_addr, 0xDEADBEEF);
  printf("Wrote 0xDEADBEEF at 0x%08x, read back: 0x%08x\n", test_addr,
         read_memory_4(memory, test_addr));

  write_memory_2(memory, test_addr + 3, 0xBEEF);
  printf("Wrote 0xBEEF at 0x%08x, read back: 0x%04x\n", test_addr + 3,
         read_memory_2(memory, test_addr + 3));

  write_memory_1(memory, test_addr + 6, 0x7F);
  printf("Wrote 0x7F at 0x%08x, read back: 0x%02x\n", test_addr + 6,
         read_memory_1(memory, test_addr + 6));

  // (The simulator's fetch/decode/execute loop would go here.)

  free(memory);
  return 0;
}
