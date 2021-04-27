#include <stdint.h>
#include <stdlib.h>

#include "raylib.h"

#define MASK_R 0x000000FF
#define MASK_G 0x0000FF00
#define MASK_B 0x00FF0000
#define MASK_A 0xFF000000
#define MASK_RGB 0x00FFFFFF

uint8_t red(uint32_t color);

uint8_t green(uint32_t color);

uint8_t blue(uint32_t color);

uint8_t alpha(uint32_t color);

uint32_t rgb(uint32_t color);

uint32_t color1(uint8_t brightness);

uint32_t color4(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

int brightness(uint32_t col);

uint32_t invert(uint32_t col);

uint32_t grayscale(uint32_t col);

uint32_t treshold(uint32_t col, int treshold);

uint32_t edge(uint32_t col, uint32_t colR, int strength);

uint32_t convolution(uint32_t* data, int w, int h, int size, float mat[][size], int x, int y);
