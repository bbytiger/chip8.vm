
#include <string.h>

#include "opcodes.h"
#include "utils.h"

// note that the 0nnn opcode is deprecated

void op_00E0() {
  // clear the display
  memset(screen, 0, sizeof(screen));
}

void op_00EE() {
  // return from subroutine
  --sp; pc = stack[sp];
}

void op_1nnn() {
  // given opcode 1nnn --> jump to location nnn
  uint16_t addr = opcode & 0x0FFFu; pc = addr;
}

void op_2nnn() {
  // give opcode 2nnn --> call routine at location nnn
  uint16_t addr = opcode & 0x0FFFu;
  // save current pc on stack in new frame
  stack[sp] = pc; ++sp; pc = addr;
}

void op_3xkk() {
  // skip next instruction if vx = kk;
  // The interpreter compares register Vx to kk, and if they are equal, increments the program counter by 2.
  uint8_t kk = opcode & 0x00FFu;
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  if (reg[vx] == kk) pc += 2;
}

void op_4xkk() {
  // Skip next instruction if Vx != kk.
  // The interpreter compares register Vx to kk, and if they are not equal, increments the program counter by 2.
  uint8_t kk = opcode & 0x00FFu;
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  if (reg[vx] != kk) pc += 2;
}

void op_5xy0() {
  // Skip next instruction if Vx = Vy.
  // The interpreter compares register Vx to register Vy, and if they are equal, increments the program counter by 2.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  uint8_t vy = (opcode & 0x00F0u) >> 4u;
  if (reg[vx] == reg[vy]) pc += 2;
}

void op_6xkk() {
  // Set Vx = kk.
  // The interpreter puts the value kk into register Vx
  uint8_t kk = opcode & 0x00FFu;
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  reg[vx] = kk;
}

void op_7xkk() {
  // Set Vx = Vx + kk.
  // Adds the value kk to the value of register Vx, then stores the result in Vx.
  uint8_t kk = opcode & 0x00FFu;
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  reg[vx] += kk;
}

void op_8xy0() {
  // Set Vx = Vy.
  // Stores the value of register Vy in register Vx.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  uint8_t vy = (opcode & 0x00F0u) >> 4u;
  reg[vx] = reg[vy];
}

void op_8xy1() {
  // Set Vx = Vx OR Vy.
  // Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx. A bitwise OR compares the corrseponding bits from two values, and if either bit is 1, then the same bit in the result is also 1. Otherwise, it is 0.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  uint8_t vy = (opcode & 0x00F0u) >> 4u;
  reg[vx] |= reg[vy];
}

void op_8xy2() {
  // Set Vx = Vx AND Vy.
  // Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx. A bitwise AND compares the corrseponding bits from two values, and if both bits are 1, then the same bit in the result is also 1. Otherwise, it is 0.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  uint8_t vy = (opcode & 0x00F0u) >> 4u;
  reg[vx] &= reg[vy];
}

void op_8xy3() {
  // Set Vx = Vx XOR Vy.
  // Performs a bitwise exclusive OR on the values of Vx and Vy, then stores the result in Vx. An exclusive OR compares the corrseponding bits from two values, and if the bits are not both the same, then the corresponding bit in the result is set to 1. Otherwise, it is 0.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  uint8_t vy = (opcode & 0x00F0u) >> 4u;
  reg[vx] ^= reg[vy];
}

void op_8xy4() {
  // Set Vx = Vx + Vy, set VF = carry.
  // The values of Vx and Vy are added together. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0. Only the lowest 8 bits of the result are kept, and stored in Vx.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  uint8_t vy = (opcode & 0x00F0u) >> 4u;
  reg[vF] = (reg[vx] + reg[vy] > 255) ? 1 : 0;
  reg[vx] += reg[vy];
}

void op_8xy5() {
  // Set Vx = Vx - Vy, set VF = NOT borrow.
  // If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  uint8_t vy = (opcode & 0x00F0u) >> 4u;
  reg[vF] = (reg[vx] > reg[vy]) ? 1 : 0;
  reg[vx] -= reg[vy];  
}

void op_8xy6() {
  // Set Vx = Vx SHR 1.
  // If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  reg[vF] = (reg[vx] & 0x1u);
  reg[vx] >>= 1; // bitshift is much faster instead of divide
}

void op_8xy7() {
  // Set Vx = Vy - Vx, set VF = NOT borrow.
  // If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  uint8_t vy = (opcode & 0x00F0u) >> 4u;
  reg[vF] = (reg[vy] > reg[vx]) ? 1 : 0;
  reg[vx] = reg[vy] - reg[vx];
}

void op_8xyE() {
  // Set Vx = Vx SHL 1.
  // If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  reg[vF] = (reg[vx] & 0x80u) >> 7u;
  reg[vx] <<= 1; // bitshift is much faster than mult
}

void op_9xy0() {
  // Skip next instruction if Vx != Vy.
  // The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  uint8_t vy = (opcode & 0x00F0u) >> 4u;
  if (reg[vx] != reg[vy]) pc += 2;
}

void op_Annn() {
  // Set I = nnn.
  // The value of register I is set to nnn.
  ir = (opcode & 0x0FFFu);
}

void op_Bnnn() {
  // Jump to location nnn + V0.
  // The program counter is set to nnn plus the value of V0.
  pc = (opcode & 0x0FFFu) + reg[v0];
}

void op_Cxkk() {
  // Set Vx = random byte AND kk.
  // The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx. See instruction 8xy2 for more information on AND.
  uint8_t kk = opcode & 0x00FFu;
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  init_gen(); uint8_t rand = gen_rand();
  reg[vx] = kk & rand;
}

/* not done yet */
void op_Dxyn() {
  // Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
  // The interpreter reads n bytes from memory, starting at the address stored in I. These bytes are then displayed as sprites on screen at coordinates (Vx, Vy). Sprites are XORed onto the existing screen. If this causes any pixels to be erased, VF is set to 1, otherwise it is set to 0. If the sprite is positioned so part of it is outside the coordinates of the display, it wraps around to the opposite side of the screen. See instruction 8xy3 for more information on XOR, and section 2.4, Display, for more information on the Chip-8 screen and sprites.
  uint8_t n = (opcode & 0x000Fu);
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  uint8_t vy = (opcode & 0x00F0u) >> 4u;
  uint8_t px_data;

  reg[vF] = 0;
  for (int i = 0; i < n; i++) {
    px_data = mem[ir+i];
    for (int j = 0; j < 8; j++) {
      if ((px_data & (0x80 >> j))) { // for each of the bits, check against pixel to see if it should be filled in for the sprite
        // if exceed either side of the screen, wrap around
        uint32_t* px_ptr = &screen[(vx + i + (vy + j) * screen_W) % screen_SZ];
        // if any pixels erased, set the vf flag
        if (*(px_ptr) == 0xFFFFFFF) reg[vF] = 1;
        *(px_ptr) ^= 0xFFFFFFFF;
      }
    }
  }
}

void op_Ex9E() {
  // Skip next instruction if key with the value of Vx is pressed.
  // Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, PC is increased by 2.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  if (keypad[reg[vx]]) pc += 2; 
}

void op_ExA1() {
  // Skip next instruction if key with the value of Vx is not pressed.
  // Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, PC is increased by 2.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  if (!keypad[reg[vx]]) pc += 2; 
}

void op_Fx07() {
  // Set Vx = delay timer value.
  // The value of DT is placed into Vx.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  reg[vx] = delay_timer;
}

void op_Fx0A() {
  // Wait for a key press, store the value of the key in Vx.
  // All execution stops until a key is pressed, then the value of that key is stored in Vx.

  // the trick to waiting for a key press is decrementing the pc by 2 instructions (because each execution loop will increment by 2)
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  if (keypad[0x0]) {
    reg[vx] = 0x0;
  } else if (keypad[0x1]) {
    reg[vx] = 0x1;
  } else if (keypad[0x2]) {
    reg[vx] = 0x2;
  } else if (keypad[0x3]) {
    reg[vx] = 0x3;
  } else if (keypad[0x4]) {
    reg[vx] = 0x4;
  } else if (keypad[0x5]) {
    reg[vx] = 0x5;
  } else if (keypad[0x6]) {
    reg[vx] = 0x6;
  } else if (keypad[0x7]) {
    reg[vx] = 0x7;
  } else if (keypad[0x8]) {
    reg[vx] = 0x8;
  } else if (keypad[0x9]) {
    reg[vx] = 0x9;
  } else if (keypad[0xA]) {
    reg[vx] = 0xA;
  } else if (keypad[0xB]) {
    reg[vx] = 0xB;
  } else if (keypad[0xC]) {
    reg[vx] = 0xC;
  } else if (keypad[0xD]) {
    reg[vx] = 0xD;
  } else if (keypad[0xE]) {
    reg[vx] = 0xE;
  } else if (keypad[0xF]) {
    reg[vx] = 0xF;
  } else {
    pc -= 2; // don't let the cpu execution move on from this instruction
  }
}

void op_Fx15() {
  // Set delay timer = Vx.
  // DT is set equal to the value of Vx.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  delay_timer = reg[vx];
}

void op_Fx18() {
  // Set sound timer = Vx.
  // ST is set equal to the value of Vx.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  sound_timer = reg[vx];
}

void op_Fx1E() {
  // Set I = I + Vx.
  // The values of I and Vx are added, and the results are stored in I.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  ir += reg[vx];
}

void op_Fx29() {
  // Set I = location of sprite for digit Vx.
  // The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx. See section 2.4, Display, for more information on the Chip-8 hexadecimal font.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  ir = (5 * reg[vx]) + FONTSET_START_ADDR;
}

void op_Fx33() {
  // Store BCD representation of Vx in memory locations I, I+1, and I+2.
  // The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.
   uint8_t vx = (opcode & 0x0F00u) >> 8u;
   mem[ir] = reg[vx] / 100;
   mem[ir+1] = (reg[vx] / 10) % 10;
   mem[ir] = reg[vx] % 10;
}

void op_Fx55() {
  // Store registers V0 through Vx in memory starting at location I.
  // The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  memcpy(mem + ir, reg, vx);
}

void op_Fx65() {
  // Read registers V0 through Vx from memory starting at location I.
  // The interpreter reads values from memory starting at location I into registers V0 through Vx.
  uint8_t vx = (opcode & 0x0F00u) >> 8u;
  memcpy(reg, mem + ir, vx);
}

void op_unknown() {
  exit(42);
}
