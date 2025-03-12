#include "memory.h"
#include <stdio.h>
#include <string.h>

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
  char address_str[MAX_LINE_LENGTH], value_str[MAX_LINE_LENGTH];
  uint32_t address;

  while (fgets(line, sizeof(line), fp)) {
    if (line[0] == '\n' || line[0] == '#')
      continue;
    if (sscanf(line, "%[^:]: %s", address_str, value_str) != 2) {
      fprintf(stderr, "Warning: Invalid line format: %s", line);
      continue;
    }

    address = (uint32_t)strtoul(address_str, NULL, 16);
    if (address >= MEMORY_SIZE_BYTES) {
      fprintf(stderr, "Warning: Address 0x%x out of bounds, skipping.\n",
              address);
      continue;
    }

    size_t value_len = strlen(value_str);
    uint32_t value = (uint32_t)strtoul(value_str, NULL, 16);

    if (value_len <= 2) {
      write_memory_1(memory, address, (uint8_t)value);
    } else if (value_len <= 4) {
      write_memory_2(memory, address, (uint16_t)value);
    } else if (value_len <= 8) {
      write_memory_4(memory, address, value);
    } else {
      fprintf(stderr, "Warning: Invalid value length: %s", line);
    }
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