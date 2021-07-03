#ifndef _CHIP8_DISPLAY_
#define _CHIP8_DISPLAY_

#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;

// sprite might wrap around the edge of
// the screen if it gets drawn off-screen
static const uint8_t screen_H = 32;
static const uint8_t screen_W = 64;
static const uint16_t screen_SZ = screen_H * screen_W;
uint32_t screen[screen_SZ];

void init(char const* title, int window_W, int window_H);
void teardown();
void update(int pitch);
bool process_input(uint8_t* keys);
void print_screen();

#endif
