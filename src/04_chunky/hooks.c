#include "Hooks.h"

#include "Display.h"

void Init(){};
void Update(){};
void PostUpdate(){};
void Draw() {
  SetPixel(32, 32, 0xff0000ff);

  DrawCircleGradient(32, 32, 32, GREEN, SKYBLUE);
};
void PostDraw(){};
void Close(){};
