#include <libtcod/heightmap.h>
#include <libtcod/libtcod.h>
#include <libtcod/mersenne.h>
#include <stdint.h>

#include "raylib.h"

int main(void) {
  // Initialization
  //-------------------------------------------------------------------------------------

  int width = 96;
  int height = 96;
  int pixelSize = 8;

  const int screenWidth = width * pixelSize;
  const int screenHeight = width * pixelSize;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(30);  // Set our game to run at 60 frames-per-second

  TCOD_heightmap_t* heightmap = TCOD_heightmap_new(width, height);
  TCOD_random_t detRnd = TCOD_random_new_from_seed(TCOD_RNG_CMWC, 0xdeadbeef);
  TCOD_random_t prevDetRnd = TCOD_random_save(detRnd);

  /* TCOD_heightmap_add_hill(heightmap, width/4., height/4., 8, -8); */
  /* TCOD_heightmap_add_hill(heightmap, width/3., height/3., 12, 6); */

  Image image = GenImageColor(width, height, BLACK);
  uint32_t* data = image.data;

  int format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
  ImageFormat(&image, format);
  /* ImageFlipVertical(&image); */

  Texture2D texture = LoadTextureFromImage(image);
  RenderTexture2D target =
      LoadRenderTexture(width * pixelSize, height * pixelSize);
  //--------------------------------------------------------------------------------------

  float erosionCoef = .5;
  float sedimentationCoef = .5;

  // Main game loop

  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    // Update
    if (IsKeyPressed('Q')) erosionCoef += .1;
    if (IsKeyPressed('A')) erosionCoef -= .1;
    if (IsKeyPressed('W')) sedimentationCoef += .1;
    if (IsKeyPressed('S')) sedimentationCoef -= .1;

    /* TCOD_random_restore(detRnd, prevDetRnd); */
    TCOD_heightmap_clear(heightmap);
    TCOD_heightmap_add_hill(heightmap, width / 2., height / 2., width / 3., 8);
    TCOD_heightmap_rain_erosion(heightmap, width * height, erosionCoef,
                                sedimentationCoef, detRnd);
    TCOD_heightmap_normalize(heightmap, 0, 255);

    for (int x = 0; x < width; ++x) {
      for (int y = 0; y < height; ++y) {
        int val = TCOD_heightmap_get_value(heightmap, x, y);
        uint32_t* color = data + y * width + x;
        int rnd = TCOD_random_get_int(detRnd, 16, 32);
        SetPixelColor(color, (Color){val, val, val, 255}, format);
      }
    }

    UpdateTexture(
        texture,
        image
            .data);  //----------------------------------------------------------------------------------
    // TODO: Update your variables here

    if (IsKeyPressed('P')) {
      TakeScreenshot("img_0.png");
    }
    //----------------------------------------------------------------------------------

    // Draw

    //----------------------------------------------------------------------------------
    BeginTextureMode(target);
    DrawTextureEx(texture, (Vector2){0, 0}, 0, pixelSize, WHITE);
    EndTextureMode();

    BeginDrawing();
    /* ClearBackground(RAYWHITE); */
    DrawTexture(target.texture, 0, 0, WHITE);
    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();  // Close window and OpenGL context

  TCOD_heightmap_delete(
      heightmap);  //--------------------------------------------------------------------------------------

  return 0;
}
