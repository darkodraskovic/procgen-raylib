
#include "chunky/hooks.h"

#include <stdlib.h>

#include "chunky/display.h"
#include "config.h"
#include "roamlib/draw.h"
#include "roamlib/map.h"
#include "roamlib/player.h"

void DrawChar(const char ch, int x, int y) {
  DrawText(&ch, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, GREEN);
}

/* void drawEverything(void) { */
/*   clear(); */
/*   drawMap(); */
/*   drawEntity(player); */
/* } */

Entity* player;
Map* map;

void Init() {
  map = CreateMap(MAP_WIDTH, MAP_HEIGHT);

  player = CreatePlayer(MAP_WIDTH / 2, MAP_HEIGHT / 2);
};

void Update() { HandleInput(map, GetCharPressed()); };
void PostUpdate(){};
void Draw() {
  /* SetPixel(32, 32, 0xff0000ff); */

  /* DrawCircleGradient(32, 32, 32, GREEN, SKYBLUE); */
  DrawMap(map);
  DrawEntity(player);
};
void PostDraw(){};
void Close(){};
