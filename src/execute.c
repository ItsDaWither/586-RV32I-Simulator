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

int execute_addi(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] + insn.imm;
  return 0;
}

int execute_lui(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = insn.imm;
  return 0;
}

int execute_auipc(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = *pc + insn.imm;
  return 0;
}

int execute_jal(Instruction insn, uint32_t *registers, uint32_t *pc) {
  int32_t offset = insn.imm;
  registers[insn.rd] = *pc + 4; // Store return address
  *pc = *pc + offset;
  return 0;
}

int execute_jalr(Instruction insn, uint32_t *registers, uint32_t *pc) {
  if ((registers[insn.rs1] & (~1)) == 0 && insn.rd == 0) {
    return 1; // Halt on jr ra with ra == 0
  }
  int32_t offset = insn.imm;
  uint32_t temp_pc = *pc;
  *pc = ((registers[insn.rs1] + offset) & (~1)); // clear the last bit
  registers[insn.rd] = temp_pc + 4;
  return 0;
}

int execute_beq(Instruction insn, uint32_t *registers, uint32_t *pc) {
  if (registers[insn.rs1] == registers[insn.rs2]) {
    *pc = *pc + insn.imm - 4;
  }
  return 0;
}

int execute_bne(Instruction insn, uint32_t *registers, uint32_t *pc) {
  if (registers[insn.rs1] != registers[insn.rs2]) {
    *pc = *pc + insn.imm - 4;
  }
  return 0;
}
int execute_blt(Instruction insn, uint32_t *registers, uint32_t *pc) {
  if ((int32_t)registers[insn.rs1] < (int32_t)registers[insn.rs2]) {
    *pc = *pc + insn.imm - 4;
  }
  return 0;
}

int execute_bge(Instruction insn, uint32_t *registers, uint32_t *pc) {
  if ((int32_t)registers[insn.rs1] >= (int32_t)registers[insn.rs2]) {
    *pc = *pc + insn.imm - 4;
  }
  return 0;
}

int execute_bltu(Instruction insn, uint32_t *registers, uint32_t *pc) {
  if (registers[insn.rs1] < registers[insn.rs2]) {
    *pc = *pc + insn.imm - 4;
  }
  return 0;
}

int execute_bgeu(Instruction insn, uint32_t *registers, uint32_t *pc) {
  if (registers[insn.rs1] >= registers[insn.rs2]) {
    *pc = *pc + insn.imm - 4;
  }
  return 0;
}

int execute_lb(Instruction insn, uint32_t *registers, uint32_t *pc,
                uint32_t *memory) {
  int32_t address = registers[insn.rs1] + insn.imm;
  uint8_t byte = read_memory_1(memory, address);
  registers[insn.rd] = sign_extend(byte, 8);
  return 0;
}

int execute_lh(Instruction insn, uint32_t *registers, uint32_t *pc,
                uint32_t *memory) {
  int32_t address = registers[insn.rs1] + insn.imm;
  uint16_t halfword = read_memory_2(memory, address);
  registers[insn.rd] = sign_extend(halfword, 16);
  return 0;
}

int execute_lw(Instruction insn, uint32_t *registers, uint32_t *pc,
                uint32_t *memory) {
  int32_t address = registers[insn.rs1] + insn.imm;
  registers[insn.rd] = read_memory_4(memory, address);
  return 0;
}

int execute_lbu(Instruction insn, uint32_t *registers, uint32_t *pc,
                 uint32_t *memory) {
  int32_t address = registers[insn.rs1] + insn.imm;
  uint8_t byte = read_memory_1(memory, address);
  registers[insn.rd] = (uint32_t)byte;
  return 0;
}

int execute_lhu(Instruction insn, uint32_t *registers, uint32_t *pc,
                 uint32_t *memory) {
  int32_t address = registers[insn.rs1] + insn.imm;
  uint16_t halfword = read_memory_2(memory, address);
  registers[insn.rd] = (uint32_t)halfword;
  return 0;
}

int execute_sb(Instruction insn, uint32_t *registers, uint32_t *pc,
                uint32_t *memory) {
  int32_t address = registers[insn.rs1] + insn.imm;
  uint8_t byte_to_write = (uint8_t)registers[insn.rs2];
  write_memory_1(memory, address, byte_to_write);
  return 0;
}
int execute_sh(Instruction insn, uint32_t *registers, uint32_t *pc,
                uint32_t *memory) {
  int32_t address = registers[insn.rs1] + insn.imm;
  uint16_t halfword_to_write = (uint16_t)registers[insn.rs2];
  write_memory_2(memory, address, halfword_to_write);
  return 0;
}
int execute_sw(Instruction insn, uint32_t *registers, uint32_t *pc,
                uint32_t *memory) {
  int32_t address = registers[insn.rs1] + insn.imm;
  write_memory_4(memory, address, registers[insn.rs2]);
  return 0;
}
int execute_slli(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1]
                       << (insn.imm &
                           0x1F); // only first 5 bits are shift amount
  return 0;
}

int execute_srli(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] =
      registers[insn.rs1] >> (insn.imm & 0x1F); // only first 5 bits
  return 0;
}
int execute_srai(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] =
      (uint32_t)((int32_t)registers[insn.rs1] >> (insn.imm & 0x1F));
  return 0;
}

int execute_slti(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = (int32_t)registers[insn.rs1] < insn.imm ? 1 : 0;
  return 0;
}
int execute_sltiu(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] < (uint32_t)insn.imm ? 1 : 0;
  return 0;
}

int execute_xori(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] ^ insn.imm;
  return 0;
}
int execute_ori(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] | insn.imm;
  return 0;
}

int execute_andi(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] & insn.imm;
  return 0;
}
int execute_add(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] + registers[insn.rs2];
  return 0;
}

int execute_sub(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] - registers[insn.rs2];
  return 0;
}

int execute_sll(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] << (registers[insn.rs2] & 0x1F);
  return 0;
}

int execute_slt(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] =
      (int32_t)registers[insn.rs1] < (int32_t)registers[insn.rs2] ? 1 : 0;
  return 0;
}

int execute_sltu(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] < registers[insn.rs2] ? 1 : 0;
  return 0;
}

int execute_xor(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] ^ registers[insn.rs2];
  return 0;
}

int execute_srl(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] >> (registers[insn.rs2] & 0x1F);
  return 0;
}

int execute_sra(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] =
      (uint32_t)((int32_t)registers[insn.rs1] >> (registers[insn.rs2] & 0x1F));
  return 0;
}

int execute_or(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] | registers[insn.rs2];
  return 0;
}
int execute_and(Instruction insn, uint32_t *registers, uint32_t *pc) {
  registers[insn.rd] = registers[insn.rs1] & registers[insn.rs2];
  return 0;
}

// TODO: implement other parts of ecall
int execute_ecall(Instruction insn, uint32_t *registers, uint32_t *pc) {
  if (registers[17] == 94) {
    *pc = 0;
  } else {
    fprintf(stderr, "ecall %d not implemented\n", registers[17]);
    *pc = 0;
  }
  return 0;
}

// default handler
int execute_unknown(Instruction insn, uint32_t *registers, uint32_t *pc) {
  fprintf(stderr, "Unknown instruction: opcode=0x%x\n", insn.opcode);
  *pc = 0; // set pc to zero to halt execution
  return 1;
}

int execute_instruction(Instruction insn, uint32_t *registers, uint32_t *pc,
                         uint32_t *memory) {
  switch (insn.opcode) {
  case 0x37: // lui
    return execute_lui(insn, registers, pc);
    break;
  case 0x17: // auipc
    return execute_auipc(insn, registers, pc);
    break;
  case 0x6f: // jal
    return execute_jal(insn, registers, pc);
    break;
  case 0x67: // JALR opcode
    return execute_jalr(insn, registers, pc);
    break;
  case 0x63: // branch instructions
    switch (insn.funct3) {
    case 0x0: // beq
      return execute_beq(insn, registers, pc);
      break;
    case 0x1: // bne
      return execute_bne(insn, registers, pc);
      break;
    case 0x4: // blt
      return execute_blt(insn, registers, pc);
      break;
    case 0x5: // bge
      return execute_bge(insn, registers, pc);
      break;
    case 0x6: // bltu
      return execute_bltu(insn, registers, pc);
      break;
    case 0x7: // bgeu
      return execute_bgeu(insn, registers, pc);
      break;

    default:
      return execute_unknown(insn, registers, pc);
      break;
    }
    break;
  case 0x03: // load instructions
    switch (insn.funct3) {
    case 0x0: // lb
      return execute_lb(insn, registers, pc, memory);
      break;
    case 0x1: // lh
      return execute_lh(insn, registers, pc, memory);
      break;
    case 0x2: // lw
      return execute_lw(insn, registers, pc, memory);
      break;
    case 0x4: // lbu
      return execute_lbu(insn, registers, pc, memory);
      break;
    case 0x5: // lhu
      return execute_lhu(insn, registers, pc, memory);
      break;
    default:
      return execute_unknown(insn, registers, pc);
      break;
    }
    break;
  case 0x23: // store instructions
    switch (insn.funct3) {
    case 0x0: // sb
      return execute_sb(insn, registers, pc, memory);
      break;
    case 0x1: // sh
      return execute_sh(insn, registers, pc, memory);
      break;
    case 0x2: // sw
      return execute_sw(insn, registers, pc, memory);
      break;
    default:
      return execute_unknown(insn, registers, pc);
      break;
    }
    break;
  case 0x13: // immediate instructions
    switch (insn.funct3) {
    case 0x0: // addi
      return execute_addi(insn, registers, pc);
      break;
    case 0x1: // slli
      return execute_slli(insn, registers, pc);
      break;
    case 0x2: // slti
      return execute_slti(insn, registers, pc);
      break;
    case 0x3: // sltiu
      return execute_sltiu(insn, registers, pc);
      break;
    case 0x4: // xori
      return execute_xori(insn, registers, pc);
      break;
    case 0x5: // srli and srai
      if ((insn.imm >> 5) == 0) {
        return execute_srli(insn, registers, pc); // srli
      } else {
        return execute_srai(insn, registers, pc); // srai
      }
      break;
    case 0x6: // ori
      return execute_ori(insn, registers, pc);
      break;
    case 0x7: // andi
      return execute_andi(insn, registers, pc);
      break;
    default:
      return execute_unknown(insn, registers, pc);
      break;
    }
    break;
  case 0x33: // register-register instructions
    switch (insn.funct3) {
    case 0x0: // add and sub
      if (insn.funct7 == 0) {
        return execute_add(insn, registers, pc); // add
      } else {
        return execute_sub(insn, registers, pc); // sub
      }
      break;
    case 0x1: // sll
      return execute_sll(insn, registers, pc);
      break;
    case 0x2: // slt
      return execute_slt(insn, registers, pc);
      break;
    case 0x3: // sltu
      return execute_sltu(insn, registers, pc);
      break;
    case 0x4: // xor
      return execute_xor(insn, registers, pc);
      break;
    case 0x5: // srl and sra
      if (insn.funct7 == 0) {
        return execute_srl(insn, registers, pc); // srl
      } else {
        return execute_sra(insn, registers, pc); // sra
      }
      break;
    case 0x6: // or
      return execute_or(insn, registers, pc);
      break;
    case 0x7: // and
      return execute_and(insn, registers, pc);
      break;
    default:
      return execute_unknown(insn, registers, pc);
      break;
    }
    break;
  case 0x73: // ecall
    if (insn.funct3 == 0) {
      return execute_ecall(insn, registers, pc);
    } else {
      return execute_unknown(insn, registers, pc);
    }
    break;
  default:
    return execute_unknown(insn, registers, pc);
    break;
  }
}
