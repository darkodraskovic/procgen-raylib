#include "filters.h"

#include <stdint.h>

#include "raymath.h"

uint8_t red(uint32_t color) { return color & MASK_R; }

uint8_t green(uint32_t color) { return (color & MASK_G) >> 8; }

uint8_t blue(uint32_t color) { return (color & MASK_B) >> 16; }

uint8_t alpha(uint32_t color) { return (color & MASK_A) >> 24; }

uint32_t rgb(uint32_t color) { return color & MASK_RGB; }

uint32_t color1(uint8_t brightness) {
  return MASK_A | brightness << 16 | brightness << 8 | brightness;
}

uint32_t color3(uint8_t red, uint8_t green, uint8_t blue) {
  return MASK_A | red | green << 8 | blue << 16;
}

uint32_t color4(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
  return red | green << 8 | blue << 16 | alpha << 24;
}

int brightness(uint32_t col) {
  return 0.299 * red(col) + 0.587 * green(col) + 0.114 * blue(col);
}

uint32_t invert(uint32_t col) {
  uint32_t c = ~rgb(col) & MASK_RGB;
  return c | col & MASK_A;
}

uint32_t grayscale(uint32_t col) {
  uint32_t avg = (red(col) + blue(col) + green(col)) / 3;
  return color4(avg, avg, avg, alpha(col));
}

uint32_t treshold(uint32_t col, int treshold) {
  if (brightness(col) > treshold)
    return 0xFFFFFFFF;
  else
    return 0xFF000000;
}

uint32_t edge(uint32_t col, uint32_t colR, int strength) {
  int diff = abs(brightness(col) - brightness(colR)) * strength;
  return color1(diff);
}

uint32_t convolution(uint32_t* data, int w, int h, float mat[CONV_SIZE][CONV_SIZE], int x,
                     int y) {
  int offset = CONV_SIZE / 2;
  int r = 0;
  int g = 0;
  int b = 0;

  for (int i = 0; i < CONV_SIZE; ++i) {
    int dstY = y - offset + i;
    dstY = Clamp(dstY, 0, h - 1);
    for (int j = 0; j < CONV_SIZE; ++j) {
      int dstX = x - offset + j;
      dstX = Clamp(dstX, 0, w - 1);
      uint32_t smplCol = *(data + dstY * w + dstX);
      r += red(smplCol) * mat[i][j];
      g += green(smplCol) * mat[i][j];
      b += blue(smplCol) * mat[i][j];
    }
  }
  r = Clamp(r, 0, 255);
  g = Clamp(g, 0, 255);
  b = Clamp(b, 0, 255);

  uint32_t* col = data + w * y + x;
  return color4(r, g, b, alpha(*col));
}
