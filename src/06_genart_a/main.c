// clang-format off
#include "raylib.h"
// clang-format on
#include <stdlib.h>

#include "Utils.h"

int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 800;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SIG_Init();

  SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  Color* colors =
      SIG_HexArrayToColors((char*[]){"8dab7f", "9c0d38", "ff6b6b", "404e4d", "32965d"}, 5);

  int lineMin = screenWidth / 16;
  int lineMax = screenWidth / 8;
  int lineThick = 3;

  // Main game loop
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(colors[4]);

    int stepY = 12;
    /* int stepX = 4; */

    for (int y = 0; y < screenHeight; y += stepY) {
      for (int x = 0; x < screenWidth; x += lineMax) {
        float value = SIG_GetNoise2D((float)x / screenWidth, (float)y / screenHeight) * lineMin;

        Vector2 lineStart = {x + value, y};
        Vector2 lineEnd = {x + lineMin, y};
        DrawLineEx(lineStart, lineEnd, lineThick, colors[2]);
      }
    }

    EndDrawing();
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  SIG_Close();
  CloseWindow();  // Close window and OpenGL context

  free(colors);
  //--------------------------------------------------------------------------------------

  return 0;
}
