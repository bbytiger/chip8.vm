#ifndef _CHIP8_REG_
#define _CHIP8_REG_
#include <stdint.h>

// specify the registers
enum {
  v0, v1, v2, v3,
  v4, v5, v6, v7,
  v8, v9, vA, vB,
  vC, vD, vE, vF,
  r_count,
};

uint8_t reg[r_count];
uint16_t ir;
uint16_t pc;
#endif
