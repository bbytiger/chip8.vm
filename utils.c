#include <string.h>

#include "utils.h"

void print_reg() {
  printf("registers: ");
  for (int i = 0; i < 16; i++) {
    printf("%X ", reg[i]);
  }
  printf("\n");
}

// load rom into memory at 0x200
void load_rom(char* const filename) {
  FILE* fptr = fopen(filename, "rb");
  if (fptr != NULL) {
    fseek(fptr, 0L, SEEK_END);
    uint16_t sz = ftell(fptr);
    rewind(fptr);

    // load into buffer and close the file                                                          
    char* buf = (char*)malloc(sz + 1);
    fread(buf, sizeof(char), sz, fptr);
    fclose(fptr);

    memcpy(mem + START_ADDR, buf, sz);
    free(buf);
  }
}

void init_chip() {
  // set the program to the start address of the rom
  pc = START_ADDR;
  init_gen();
  // load fontset into memory
  for (int i = 0; i < FONTSET_SZ; i++) {
    mem[FONTSET_START_ADDR + i] = fontset[i];
  }
}

void init_gen() {
  // seed the generator
  srand(time(NULL));
}

uint8_t gen_rand() {
  return (uint8_t) rand();
}
