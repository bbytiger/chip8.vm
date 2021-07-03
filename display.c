#include "display.h"
#include <stdlib.h>
#include <stdio.h>

void print_screen() {
	for (int i = 0; i < screen_H; i++) {
		for (int j = 0; j < screen_W; j++) {
			printf("%X ", screen[i * screen_W + j]);
		}
		printf("\n");
	}
}

void init(char const* title, int window_W, int window_H) {
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_W * 8, screen_H*8, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void teardown() {
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void update(int pitch) {
	print_screen();
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (int y = 0; y < screen_H; y++) {
		for (int x = 0; x < screen_W; x++) {
			if (screen[x + (y * 64)]) {
					SDL_Rect rect;
					rect.x = x * 8;
					rect.y = y * 8;
					rect.w = 8;
					rect.h = 8;
					SDL_RenderFillRect(renderer, &rect);
			}
		}
	}
  SDL_RenderPresent(renderer);
}

bool process_input(uint8_t* keys) {
  bool quit = false;
  SDL_Event ev;
  while(SDL_PollEvent(&ev)) {
    switch(ev.type) {
      printf("%d\n", ev.type);
    case SDL_QUIT:
      quit = true;
      break;
    case SDL_KEYDOWN:
      switch(ev.key.keysym.sym) {
      case SDLK_ESCAPE:
	{
	  quit = true;
	} break;
	
      case SDLK_x:
	{
	  keys[0] = 1;
	} break;

      case SDLK_1:
	{
	  keys[1] = 1;
	} break;

      case SDLK_2:
	{
	  keys[2] = 1;
	} break;

      case SDLK_3:
	{
	  keys[3] = 1;
	} break;

      case SDLK_q:
	{
	  keys[4] = 1;
	} break;

      case SDLK_w:
	{
	  keys[5] = 1;
	} break;

      case SDLK_e:
	{
	  keys[6] = 1;
	} break;

      case SDLK_a:
	{
	  keys[7] = 1;
	} break;

      case SDLK_s:
	{
	  keys[8] = 1;
	} break;

      case SDLK_d:
	{
	  keys[9] = 1;
	} break;

      case SDLK_z:
	{
	  keys[0xA] = 1;
	} break;

      case SDLK_c:
	{
	  keys[0xB] = 1;
	} break;

      case SDLK_4:
	{
	  keys[0xC] = 1;
	} break;

      case SDLK_r:
	{
	  keys[0xD] = 1;
	} break;

      case SDLK_f:
	{
	  keys[0xE] = 1;
	} break;

      case SDLK_v:
	{
	  keys[0xF] = 1;
	} break;
      }
      break;
    case SDL_KEYUP:
      switch(ev.key.keysym.sym) {
      case SDLK_x:
	{
	  keys[0] = 0;
	} break;

      case SDLK_1:
	{
	  keys[1] = 0;
	} break;

      case SDLK_2:
	{
	  keys[2] = 0;
	} break;

      case SDLK_3:
	{
	  keys[3] = 0;
	} break;

      case SDLK_q:
	{
	  keys[4] = 0;
	} break;

      case SDLK_w:
	{
	  keys[5] = 0;
	} break;

      case SDLK_e:
	{
	  keys[6] = 0;
	} break;

      case SDLK_a:
	{
	  keys[7] = 0;
	} break;

      case SDLK_s:
	{
	  keys[8] = 0;
	} break;

      case SDLK_d:
	{
	  keys[9] = 0;
	} break;

      case SDLK_z:
	{
	  keys[0xA] = 0;
	} break;

      case SDLK_c:
	{
	  keys[0xB] = 0;
	} break;

      case SDLK_4:
	{
	  keys[0xC] = 0;
	} break;

      case SDLK_r:
	{
	  keys[0xD] = 0;
	} break;

      case SDLK_f:
	{
	  keys[0xE] = 0;
	} break;

      case SDLK_v:
	{
	  keys[0xF] = 0;
	} break;
      }
      break;
    }
  }
  return quit;
}
