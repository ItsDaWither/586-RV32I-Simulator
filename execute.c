#include "execute.h"
#include "memory.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int32_t sign_extend(uint32_t value, uint32_t bits) {
  uint32_t sign_bit = 1 << (bits - 1);
  return (value & sign_bit) ? (int32_t)(value | ~((1 << bits) - 1))
                            : (int32_t)value;
}

void execute_addi(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] + insn.imm;
}

void execute_jalr(Instruction insn, uint32_t *registers, uint32_t *pc) {
  int32_t offset = insn.imm;
  uint32_t temp_pc = *pc;
  *pc = (registers[insn.rs1] + offset) & (~1); // clear the last bit
  registers[insn.rd] = temp_pc;
}

void execute_lui(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = insn.imm;
}

void execute_auipc(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = *pc - 4 + insn.imm; // pc was already incremented
}

void execute_jal(Instruction insn, uint32_t *registers, uint32_t *pc) {
  int32_t offset = insn.imm;
  registers[insn.rd] = *pc; // Store return address
  *pc = *pc + offset - 4;   // was already incremented
}

void execute_beq(Instruction insn, uint32_t *registers, uint32_t *pc) {
  if (registers[insn.rs1] == registers[insn.rs2]) {
    *pc = *pc + insn.imm - 4; // was already incremented
  }
}

void execute_bne(Instruction insn, uint32_t *registers, uint32_t *pc) {
  if (registers[insn.rs1] != registers[insn.rs2]) {
    *pc = *pc + insn.imm - 4; // was already incremented
  }
}
void execute_blt(Instruction insn, uint32_t *registers, uint32_t *pc) {
  if ((int32_t)registers[insn.rs1] < (int32_t)registers[insn.rs2]) {
    *pc = *pc + insn.imm - 4; // was already incremented
  }
}

void execute_bge(Instruction insn, uint32_t *registers, uint32_t *pc) {
  if ((int32_t)registers[insn.rs1] >= (int32_t)registers[insn.rs2]) {
    *pc = *pc + insn.imm - 4; // was already incremented
  }
}

void execute_bltu(Instruction insn, uint32_t *registers, uint32_t *pc) {
  if (registers[insn.rs1] < registers[insn.rs2]) {
    *pc = *pc + insn.imm - 4; // was already incremented
  }
}

void execute_bgeu(Instruction insn, uint32_t *registers, uint32_t *pc) {
  if (registers[insn.rs1] >= registers[insn.rs2]) {
    *pc = *pc + insn.imm - 4; // was already incremented
  }
}

void execute_lb(Instruction insn, uint32_t *registers, uint32_t *pc,
                uint32_t *memory) {
  int32_t address = registers[insn.rs1] + insn.imm;
  uint8_t byte = read_memory_1(memory, address);
  registers[insn.rd] = sign_extend(byte, 8);
}

void execute_lh(Instruction insn, uint32_t *registers, uint32_t *pc,
                uint32_t *memory) {
  int32_t address = registers[insn.rs1] + insn.imm;
  uint16_t halfword = read_memory_2(memory, address);
  registers[insn.rd] = sign_extend(halfword, 16);
}

void execute_lw(Instruction insn, uint32_t *registers, uint32_t *pc,
                uint32_t *memory) {
  int32_t address = registers[insn.rs1] + insn.imm;
  registers[insn.rd] = read_memory_4(memory, address);
}

void execute_lbu(Instruction insn, uint32_t *registers, uint32_t *pc,
                 uint32_t *memory) {
  int32_t address = registers[insn.rs1] + insn.imm;
  uint8_t byte = read_memory_1(memory, address);
  registers[insn.rd] = (uint32_t)byte;
}

void execute_lhu(Instruction insn, uint32_t *registers, uint32_t *pc,
                 uint32_t *memory) {
  int32_t address = registers[insn.rs1] + insn.imm;
  uint16_t halfword = read_memory_2(memory, address);
  registers[insn.rd] = (uint32_t)halfword;
}

void execute_sb(Instruction insn, uint32_t *registers, uint32_t *pc,
                uint32_t *memory) {
  int32_t address = registers[insn.rs1] + insn.imm;
  uint8_t byte_to_write = (uint8_t)registers[insn.rs2];
  write_memory_1(memory, address, byte_to_write);
}
void execute_sh(Instruction insn, uint32_t *registers, uint32_t *pc,
                uint32_t *memory) {
  int32_t address = registers[insn.rs1] + insn.imm;
  uint16_t halfword_to_write = (uint16_t)registers[insn.rs2];
  write_memory_2(memory, address, halfword_to_write);
}
void execute_sw(Instruction insn, uint32_t *registers, uint32_t *pc,
                uint32_t *memory) {
  int32_t address = registers[insn.rs1] + insn.imm;
  write_memory_4(memory, address, registers[insn.rs2]);
}
void execute_slli(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1]
                       << (insn.imm &
                           0x1F); // only first 5 bits are shift amount
}

void execute_srli(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] =
      registers[insn.rs1] >> (insn.imm & 0x1F); // only first 5 bits
}
void execute_srai(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] =
      (uint32_t)((int32_t)registers[insn.rs1] >> (insn.imm & 0x1F));
}

void execute_slti(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = (int32_t)registers[insn.rs1] < insn.imm ? 1 : 0;
}
void execute_sltiu(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] < (uint32_t)insn.imm ? 1 : 0;
}

void execute_xori(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] ^ insn.imm;
}
void execute_ori(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] | insn.imm;
}

void execute_andi(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] & insn.imm;
}
void execute_add(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] + registers[insn.rs2];
}

void execute_sub(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] - registers[insn.rs2];
}

void execute_sll(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] << (registers[insn.rs2] & 0x1F);
}

void execute_slt(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] =
      (int32_t)registers[insn.rs1] < (int32_t)registers[insn.rs2] ? 1 : 0;
}

void execute_sltu(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] < registers[insn.rs2] ? 1 : 0;
}

void execute_xor(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] ^ registers[insn.rs2];
}

void execute_srl(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] >> (registers[insn.rs2] & 0x1F);
}

void execute_sra(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] =
      (uint32_t)((int32_t)registers[insn.rs1] >> (registers[insn.rs2] & 0x1F));
}

void execute_or(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] | registers[insn.rs2];
}
void execute_and(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] & registers[insn.rs2];
}

// TODO: implement other parts of ecall
void execute_ecall(Instruction insn, uint32_t *registers, uint32_t *pc) {
  if (registers[17] == 94) {
    *pc = 0;
  } else {
    fprintf(stderr, "ecall %d not implemented\n", registers[17]);
    *pc = 0;
  }
}

// default handler
void execute_unknown(Instruction insn, uint32_t *registers, uint32_t *pc) {
  fprintf(stderr, "Unknown instruction: opcode=%x\n", insn.opcode);
  *pc = 0; // set pc to zero to halt execution
}

void execute_instruction(Instruction insn, uint32_t *registers, uint32_t *pc,
                         uint32_t *memory) {
  switch (insn.opcode) {
  case 0x37: // lui
    execute_lui(insn, registers, pc);
    break;
  case 0x17: // auipc
    execute_auipc(insn, registers, pc);
    break;
  case 0x6f: // jal
    execute_jal(insn, registers, pc);
    break;
  case 0x63: // branch instructions
    switch (insn.funct3) {
    case 0x0: // beq
      execute_beq(insn, registers, pc);
      break;
    case 0x1: // bne
      execute_bne(insn, registers, pc);
      break;
    case 0x4: // blt
      execute_blt(insn, registers, pc);
      break;
    case 0x5: // bge
      execute_bge(insn, registers, pc);
      break;
    case 0x6: // bltu
      execute_bltu(insn, registers, pc);
      break;
    case 0x7: // bgeu
      execute_bgeu(insn, registers, pc);
      break;
    default:
      execute_unknown(insn, registers, pc);
      break;
    }
    break;
  case 0x03: // load instructions
    switch (insn.funct3) {
    case 0x0: // lb
      execute_lb(insn, registers, pc, memory);
      break;
    case 0x1: // lh
      execute_lh(insn, registers, pc, memory);
      break;
    case 0x2: // lw
      execute_lw(insn, registers, pc, memory);
      break;
    case 0x4: // lbu
      execute_lbu(insn, registers, pc, memory);
      break;
    case 0x5: // lhu
      execute_lhu(insn, registers, pc, memory);
      break;
    default:
      execute_unknown(insn, registers, pc);
      break;
    }
    break;
  case 0x23: // store instructions
    switch (insn.funct3) {
    case 0x0: // sb
      execute_sb(insn, registers, pc, memory);
      break;
    case 0x1: // sh
      execute_sh(insn, registers, pc, memory);
      break;
    case 0x2: // sw
      execute_sw(insn, registers, pc, memory);
      break;
    default:
      execute_unknown(insn, registers, pc);
      break;
    }
    break;
  case 0x13: // immediate instructions
    switch (insn.funct3) {
    case 0x0: // addi
      execute_addi(insn, registers, pc);
      break;
    case 0x1: // slli
      execute_slli(insn, registers, pc);
      break;
    case 0x2: // slti
      execute_slti(insn, registers, pc);
      break;
    case 0x3: // sltiu
      execute_sltiu(insn, registers, pc);
      break;
    case 0x4: // xori
      execute_xori(insn, registers, pc);
      break;
    case 0x5: // srli and srai
      if ((insn.imm >> 5) == 0) {
        execute_srli(insn, registers, pc); // srli
      } else {
        execute_srai(insn, registers, pc); // srai
      }
      break;
    case 0x6: // ori
      execute_ori(insn, registers, pc);
      break;
    case 0x7: // andi
      execute_andi(insn, registers, pc);
      break;
    default:
      execute_unknown(insn, registers, pc);
      break;
    }
    break;
  case 0x33: // register-register instructions
    switch (insn.funct3) {
    case 0x0: // add and sub
      if (insn.funct7 == 0) {
        execute_add(insn, registers, pc); // add
      } else {
        execute_sub(insn, registers, pc); // sub
      }
      break;
    case 0x1: // sll
      execute_sll(insn, registers, pc);
      break;
    case 0x2: // slt
      execute_slt(insn, registers, pc);
      break;
    case 0x3: // sltu
      execute_sltu(insn, registers, pc);
      break;
    case 0x4: // xor
      execute_xor(insn, registers, pc);
      break;
    case 0x5: // srl and sra
      if (insn.funct7 == 0) {
        execute_srl(insn, registers, pc); // srl
      } else {
        execute_sra(insn, registers, pc); // sra
      }
      break;
    case 0x6: // or
      execute_or(insn, registers, pc);
      break;
    case 0x7: // and
      execute_and(insn, registers, pc);
      break;
    default:
      execute_unknown(insn, registers, pc);
      break;
    }
    break;
  case 0x73: // ecall
    if (insn.funct3 == 0) {
      execute_ecall(insn, registers, pc);
    } else {
      execute_unknown(insn, registers, pc);
    }
    break;
  default:
    execute_unknown(insn, registers, pc);
    break;
  }
}
