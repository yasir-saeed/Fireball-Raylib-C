#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "game development");
    SetTargetFPS(FLAG_VSYNC_HINT);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        DrawFPS(10,10);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("WELCOME.", 190, 200, 20, LIGHTGRAY);

        EndDrawing();

    }

    CloseWindow();        // Close window and OpenGL context
    return 0;
}