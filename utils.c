#include <string.h>

#include "utils.h"

// load rom into memory at 0x200
void load_rom(char* const filename) {
  FILE* fptr = fopen(filename, "rb");
  if (fptr != NULL) {
    fseek(fptr, 0L, SEEK_END);
    uint16_t sz = ftell(fptr);

    // load into buffer and close the file                                                          
    char* buf = (char*)malloc(sz);
    fseek(fptr, 0L, SEEK_SET);
    fread(buf, sizeof(char), sz, fptr);
    fclose(fptr);

    memcpy(mem + START_ADDR, buf, sz);
    free(buf);
  }
}

void load_chip() {
  // set the program to the start address of the rom
  pc = START_ADDR;

  // load fontset into memory
  memcpy(mem + FONTSET_START_ADDR, fontset, FONTSET_SZ);
}

void init_gen() {
  // seed the generator
  srand(time(NULL));
}

uint8_t gen_rand() {
  return (uint8_t) rand();
}
