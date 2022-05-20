#include <stdint.h>

#include "filters.h"
#include "raylib.h"

int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 960;
  const int screenHeight = 640;
  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
  SetTargetFPS(60);

  // Images & textures
  int format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;

  Image srcImg = LoadImage("assets/images/img_00.png");
  ImageFormat(&srcImg, format);

  Image dstImg = GenImageColor(srcImg.width, srcImg.height, BLACK);
  ImageFormat(&dstImg, format);

  float n = 9;
  float mat[][3] = {{-n / 9, -n / 9, -n / 9}, {-n / 9, n, -n / 9}, {-n / 9, -n / 9, -n / 9}};

  uint32_t* srcData = srcImg.data;
  uint32_t* dstData = dstImg.data;
  for (int y = 0; y < srcImg.height; y++) {
    int vOffset = y * srcImg.width;
    for (int x = 0; x < srcImg.width; x++) {
      uint32_t* srcCol = srcData + vOffset + x;
      uint32_t* dstCol = dstData + vOffset + x;
      *dstCol = *srcCol;
      /* *dstCol = invert(*dstCol); */
      /* *dstCol = grayscale(*dstCol); */
      /* *dstCol = treshold(*dstCol, 128); */
      *dstCol = convolution(srcData, srcImg.width, srcImg.height, mat, x, y);

      /* uint8_t* r = (uint8_t*)(data + vOffset + x); */
      /* uint8_t* g = r+1; */
      /* uint8_t* b = r+2; */
      /* uint8_t* a = r+3; */
    }
  }

  /* for (int y = 0; y < srcImg.height; y++) { */
  /*     int vOffset = y * srcImg.width; */
  /*     for (int x = 0; x < srcImg.width-1; x++) { */
  /*         uint32_t* srcCol = srcData + vOffset + x; */
  /*         uint32_t* dstCol = dstData + vOffset + x; */
  /*         *dstCol = *srcCol; */
  /*         *dstCol = edge(*dstCol, *(srcCol+1), 2); */
  /*     } */
  /* } */

  Texture srcTex = LoadTextureFromImage(srcImg);
  Texture dstTex = LoadTextureFromImage(dstImg);

  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawTexture(srcTex, 0, 0, WHITE);
    DrawTexture(dstTex, dstImg.width + 24, 0, WHITE);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();  // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
