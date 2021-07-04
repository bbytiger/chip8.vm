#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/timeb.h>
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

  init("CHIP-8 Emu", screen_W*video_scale, screen_H*video_scale);
  init_chip();
  load_rom(rom_file);
  int video_pitch = screen[0] * screen_H;
  struct timeb last_cycle_time, current_time;
  ftime(&last_cycle_time);
  bool quit = false;

  while(!quit) {
    quit = process_input(keypad);
    ftime(&current_time);
    int dt = (int) (1000.0 * (current_time.time - last_cycle_time.time) + (current_time.millitm - last_cycle_time.millitm)); // convert to milliseconds
    if (dt > cycle_delay) {
      printf("ready to cycle\n");
      last_cycle_time = current_time;
      print_pointers();
      print_reg();
      print_stack();
      cycle();
      update(video_pitch);
    }
  }

  return 0;
}
