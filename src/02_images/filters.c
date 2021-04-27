#include <stdint.h>
#include <stdlib.h>

#define MASK_R 0x000000FF
#define MASK_G 0x0000FF00
#define MASK_B 0x00FF0000
#define MASK_A 0xFF000000
#define MASK_RGB 0x00FFFFFF

uint8_t red(uint32_t color) {
    return color & MASK_R;
}

uint8_t green(uint32_t color) {
    return (color & MASK_G) >> 8;
}

uint8_t blue(uint32_t color) {
    return (color & MASK_B) >> 16;
}

uint8_t alpha(uint32_t color) {
    return (color & MASK_A) >> 24;
}

uint32_t rgb(uint32_t color) {
    return color & MASK_RGB;
}

uint32_t color1(uint8_t brightness) {
    return MASK_A | brightness << 16 | brightness << 8 | brightness;
}

uint32_t color4(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    return red | green << 8 | blue << 16 | alpha << 24;
}

int brightness(uint32_t col) {
    return 0.299*red(col) + 0.587*green(col) + 0.114*blue(col);
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
    if (brightness(col) > treshold) return 0xFFFFFFFF;
    else return 0xFF000000;
}

uint32_t detectEdgeR(uint32_t col, uint32_t colR, int strength) {
    int diff = abs(brightness(col) - brightness(colR)) * strength;
    return color1(diff);
}
