#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stdint.h>

int run_simulator(int verbose_mode,
                  const char *memfile,
                  uint32_t start_address,
                  uint32_t stack_address);

#endif
