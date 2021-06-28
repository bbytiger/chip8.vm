#ifndef _CHIP8_STACK_
#define  _CHIP8_STACK_

#include <stdint.h> // find some way so that the header is not repeated when compiled

static const uint16_t START_ADDR = 0x200; // memory for chip8 rom always gets loaded and starts here 

// stack with 16 levels
uint8_t stack[16];
// 8-bit stack pointer
uint8_t sp;

#endif
