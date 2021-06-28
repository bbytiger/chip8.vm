#include <stdio.h>

#include "opcodes.h"
#include "utils.h"

int main(int argc, char** argv) {
  reg[14] = 254;
  reg[15] = 254;
  opcode = 0x8FE4;
  printf("%hu\n", opcode);
  op_8xy4();
  return 0;
}
