#include "raylib.h"
#include "raymath.h"
#include "stdio.h"


struct ball{
    float x,y;
    float radius;
};

int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 800;
    struct ball Ball;
    Ball.x = screenWidth / 2;
    Ball.y = screenHeight / 2;
    Ball.radius = 10;

    InitWindow(screenWidth, screenHeight, "game development");
    SetTargetFPS(FLAG_VSYNC_HINT);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        DrawFPS(10,10);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircle((int)Ball.x, (int)Ball.y, (int)Ball.radius, BLACK);

        if(IsKeyDown(KEY_W)){
              Ball.y -= 200 * GetFrameTime();
        }
        if(IsKeyDown(KEY_S)){
            Ball.y += 200 * GetFrameTime();
        }

        if(IsKeyDown(KEY_A)){
            Ball.x -= 200 * GetFrameTime();
        }
        if(IsKeyDown(KEY_D)){
            Ball.x += 200 * GetFrameTime();
        }


        if(Ball.y > GetScreenHeight()){
            Ball.y = GetScreenHeight();
        }
        if(Ball.y < 0){
            Ball.y = 0;
        }

        if(Ball.x > GetScreenWidth()){
            Ball.x = GetScreenWidth();
        }
        if(Ball.x < 0){
            Ball.x = 0;
        }


        EndDrawing();

    }

    CloseWindow();
    return 0;
}