#include "chunky/hooks.h"

#include "chunky/display.h"
#include "roamlib/player.h"

Entity* player;

void Init() {
  player = CreatePlayer();
  player->position.x = 32;
  player->position.y = 12;
};
void Update(){};
void PostUpdate(){};
void Draw() {
  SetPixel(32, 32, 0xff0000ff);

  DrawCircleGradient(32, 32, 32, GREEN, SKYBLUE);
};
void PostDraw(){};
void Close(){};
