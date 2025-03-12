#include "decode.h"
#include <stdio.h>

Instruction decode_instruction(uint32_t instruction) {
  Instruction decoded;

  // grab all fields (not necessarily used)
  decoded.opcode = instruction & 0x7F;
  decoded.rd = (instruction >> 7) & 0x1F;
  decoded.funct3 = (instruction >> 12) & 0x7;
  decoded.rs1 = (instruction >> 15) & 0x1F;
  decoded.rs2 = (instruction >> 20) & 0x1F;
  decoded.funct7 = (instruction >> 25) & 0x7F;

  switch (decoded.opcode) {
  // R-type
  case 0x33: // ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND opcodes
    decoded.imm = 0;
    break;

  // I-type
  case 0x03: // LB, LH, LW, LBU, LHU opcodes
  case 0x13: // ADDI, SLTI, SLTIU, XORI, ORI, ANDI opcodes
  case 0x67: // JALR opcode
    decoded.imm = (int32_t)instruction >> 20; // Sign-extend immediate
    break;

  // S-type
  case 0x23: // SB, SH, SW opcodes
    decoded.imm = ((int32_t)(instruction & 0xFE000000) >> 20) | // imm[11:5]
                  ((instruction >> 7) & 0x1F);                  // imm[4:0]
    break;

  // B-type
  case 0x63: // BEQ, BNE, BLT, BGE, BLTU, BGEU opcodes
    decoded.imm = ((int32_t)(instruction & 0x80000000) >> 19) | // imm[12]
                  ((instruction & 0x80) << 4) |                 // imm[11]
                  ((instruction >> 20) & 0x7E0) |               // imm[10:5]
                  ((instruction >> 7) & 0x1E);                  // imm[4:1]
    break;

  // U-type
  case 0x37: // LUI opcode
  case 0x17: // AUIPC opcode
    decoded.imm = (int32_t)(instruction & 0xFFFFF000);
    break;

  // J-type
  case 0x6F: // JAL opcode
    decoded.imm = ((int32_t)(instruction & 0x80000000) >> 11) | // imm[20]
                  (instruction & 0xFF000) |                     // imm[19:12]
                  ((instruction >> 9) & 0x800) |                // imm[11]
                  ((instruction >> 20) & 0x7FE);                // imm[10:1]
    break;

  // oops! bad opcode
  default:
    fprintf(stderr, "Error: Unsupported opcode 0x%02X\n", decoded.opcode);
  }

  return decoded;
}
