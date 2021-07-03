#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "cpu.h"
#include "opcodes.h"
#include "utils.h"
#include "display.h"

int main(int argc, char** argv) {
  if (argc != 4) {
    printf("Usage: ");
    printf("%s", argv[0]);
    printf(" <Scale> <Delay> <ROM>\n");
    exit(1);
  }
  int video_scale = atoi(argv[1]);
  int cycle_delay = atoi(argv[2]);
  char* const rom_file = argv[3];

  init("CHIP-8 Emu", screen_W*video_scale, screen_H*video_scale, screen_W, screen_H);
  init_chip();
  load_rom(rom_file);
  int video_pitch = screen[0] * screen_H;
  time_t last_cycle_time = time(0);
  bool quit = false;

  while(!quit) {
    quit = process_input(keypad);
    time_t current_time = time(0);
    double dt = difftime(current_time, last_cycle_time) / 1000; // convert to millisecondsß
    if (dt > cycle_delay) {
      last_cycle_time = current_time;
      cycle();
      update(screen, video_pitch);
    }
  }

  return 0;
}
