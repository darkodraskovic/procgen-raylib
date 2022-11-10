#ifndef UTILS_H
#define UTILS_H

#include "raylib.h"

void SIG_Init();
void SIG_Close();

float SIG_GetNoise2D(float x, float y);

Color SIG_HexToRGB(int hexValue);
Color* SIG_HexArrayToColors(char* hex[], int arrayLen);

#endif /* UTILS_H */
