#include "raylib.h"

const int screenWidth = 1152;
const int screenHeight = 648;

void drawCircle(float x, float y, float radius) {
    DrawCircleLines(x, y, radius, YELLOW);
    if (radius > 8) {
        radius /= 2;
        drawCircle(x + radius, y, radius);
        drawCircle(x - radius, y, radius);
        drawCircle(x, y + radius, radius);
        drawCircle(x, y - radius, radius);
    }
}

void cantor(float x, float y, float len) {
    float thick = 2;
    
    if (len < thick * 2) return;
    
    DrawLineEx((Vector2){x,y}, (Vector2){x+len, y}, thick, YELLOW);
    float len2 = len/2;
    DrawLineEx((Vector2){x + len2,y-len2}, (Vector2){x+len2, y+len2}, thick, YELLOW);
    /* DrawRectangleLines(x, y-len2, len, len, MAGENTA); */
    
    y += 32;
    len /= 3;
    cantor(x, y, len);
    cantor(x + 2 * len, y, len);
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(GRAY);

        /* drawCircle((float)screenWidth/2, (float)screenHeight/2, 256); */
        cantor(10, 20, screenWidth-20);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
