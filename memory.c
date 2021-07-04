#include "memory.h"

void print_mem() { 
  printf("memory: ");
  for (int i = 0; i < MEM_SIZE; i++) {
    printf("%X ", mem[i]);
  }
  printf("\n"); 
};