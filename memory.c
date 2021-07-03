#include "memory.h"

void print_mem() { 
  for (int i = 0; i < MEM_SIZE; i++) {
    printf("%X ", mem[i]);
  }
  printf("\n"); 
};