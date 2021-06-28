#ifndef _CHIP8_DISPLAY_
#define _CHIP8_DISPLAY_

// sprite might wrap around the edge of
// the screen if it gets drawn off-screen
static const uint8_t screen_H = 64;
static const uint8_t screen_W = 32;
static const uint16_t screen_SZ = screen_H * screen_W;
uint32_t screen[screen_SZ];

#endif
