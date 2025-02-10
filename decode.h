#ifndef DECODE_H
#define DECODE_H

#include <stdint.h>

typedef struct {
  uint32_t opcode;
  uint32_t rd;
  uint32_t rs1;
  uint32_t rs2;
  uint32_t funct3;
  uint32_t funct7;
  int32_t  imm;     // decoder sign-extends
} Instruction;

Instruction decode_instruction(uint32_t instruction);

#endif