#ifndef _CHIP8_MEMORY_
#define _CHIP8_MEMORY_

#define MEM_SIZE 4096

#include <stdint.h>
#include <stdio.h>

uint8_t mem[MEM_SIZE];

void print_mem(); 

#endif
