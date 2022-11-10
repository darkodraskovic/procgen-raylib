#include "Utils.h"

#include <libtcod/libtcod.h>
#include <stdlib.h>

TCOD_noise_t noise2d;

void SIG_Init() {
  // A random number generator obtained with the Mersenne twister toolkit or NULL to use the
  // default random number generator.
  /* TCOD_random_t random = TCOD_random_new(TCOD_RNG_MT); */
  noise2d = TCOD_noise_new(2, TCOD_NOISE_DEFAULT_HURST, TCOD_NOISE_DEFAULT_LACUNARITY, NULL);
  /* TCOD_noise_set_type(noise2d, TCOD_NOISE_SIMPLEX); */
}

void SIG_Close() { TCOD_noise_delete(noise2d); }

float SIG_GetNoise2D(float x, float y) {
  // returns the noise function value between -1.0 and 1.0 at given coordinates
  return TCOD_noise_get_ex(noise2d, (float[2]){x, y}, TCOD_NOISE_SIMPLEX);
}

Color SIG_HexToRGB(int hexValue) {
  Color color;
  color.r = ((hexValue >> 16) & 0xFF);
  color.g = ((hexValue >> 8) & 0xFF);
  color.b = ((hexValue)&0xFF);
  color.a = 255.0;

  return color;
}

Color* SIG_HexArrayToColors(char* hex[], int arrayLen) {
  Color* colors = (Color*)malloc(sizeof(Color) * arrayLen);
  for (int i = 0; i < arrayLen; ++i) {
    int num = (int)strtol(hex[i], NULL, 16);
    colors[i] = SIG_HexToRGB(num);
  }

  return colors;
}
