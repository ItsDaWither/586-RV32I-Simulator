// execute.h
#ifndef EXECUTE_H
#define EXECUTE_H

#include "decode.h"
#include <stdint.h>

int execute_instruction(Instruction insn, uint32_t *registers, uint32_t *pc,
                         uint32_t *memory);

#endif