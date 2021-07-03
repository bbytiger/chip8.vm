#include <stdio.h>

#include "cpu.h"
#include "opcodes.h"
#include "utils.h"
#include "display.h"

int main(int argc, char** argv) {
  reg[14] = 254;
  reg[15] = 254;
  opcode = 0x8FE4;
  printf("%hu\n", opcode);
  init("my init", 100, 100, 100, 100);
  return 0;
}
