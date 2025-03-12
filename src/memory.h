#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdlib.h>

#define MEMORY_SIZE_BYTES (64 * 1024)
#define MEMORY_WORDS (MEMORY_SIZE_BYTES / 4) // Number of 32-bit words.
#define MAX_LINE_LENGTH 256

uint8_t read_memory_1(uint32_t *memory, uint32_t address);
uint16_t read_memory_2(uint32_t *memory, uint32_t address);
uint32_t read_memory_4(uint32_t *memory, uint32_t address);
void write_memory_1(uint32_t *memory, uint32_t address, uint8_t value);
void write_memory_2(uint32_t *memory, uint32_t address, uint16_t value);
void write_memory_4(uint32_t *memory, uint32_t address, uint32_t value);
int load_memory_image(const char *filename, uint32_t *memory, size_t num_words);
void print_memory(uint32_t *memory, size_t num_words);

#endif
