#include "raylib.h"


struct ball {
    float x, y;
    float radius;
};

struct platform {
    float x, y;
    float height, width;
};


int main(void) {
    // Initialization

    const int screenWidth = 800;
    const int screenHeight = 800;

    struct ball Ball;

    Ball.x = screenWidth / 2;
    Ball.y = 800;
    Ball.radius = 10;

    struct ball Fireball;
    Fireball.x = 400;
    Fireball.y = 10;

    int score = 0;
    bool losecondition = false;

    struct platform Ground[3];
    for (int i = 0; i < 4; i++) {
        Ground[i].x = GetScreenWidth() + (i * 5);
        Ground[i].y = 760;
        Ground[i].height = 40;
        Ground[i].width = GetRandomValue(50, 400);
    }


    InitWindow(screenWidth, screenHeight, "FIREBALL");
    SetTargetFPS(60);

    Texture2D fireball = LoadTexture("fireball.png");
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        BeginDrawing();
        DrawFPS(10, 10);
        ClearBackground(SKYBLUE);
        DrawText(TextFormat("SCORE %i", score), 320, 20, 40, RED);


        if (!losecondition) {
            DrawTexture(fireball, Fireball.x, Fireball.y, WHITE);
            DrawCircle((int) Ball.x, (int) Ball.y, (int) Ball.radius, BLACK);

            Ball.y += 100 * GetFrameTime(); // Gravity
            Fireball.y += (200 * GetFrameTime()) + (score * 0.2); // fireball speeds up as score increases

            // platform spawner
            for (int i = 0; i < 4; i++) {
                DrawRectangle(Ground[i].x, Ground[i].y, Ground[i].width, Ground[i].height, GRAY);
                Ground[i].x -= 100 * GetFrameTime();

                // once offscreen, move it to end of screen
                if (Ground[i].x + Ground[i].width < 0) {
                    Ground[i].width = (int) GetRandomValue(50, 400);
                    Ground[i].x = GetScreenWidth() - 10;
                }
            }
        }

        // increase score if fireball is dodged
        if (Fireball.y > GetScreenHeight()) {
            Fireball.x = GetRandomValue(0, GetScreenWidth());
            Fireball.y = 0;
            score++;
        }

        // Game ends once player and fireball collide
        if (CheckCollisionCircleRec((Vector2) {Ball.x, Ball.y}, Ball.radius,
                                    (Rectangle) {Fireball.x, Fireball.y, 42, 43})) {

            losecondition = true;

        }

        if (losecondition) {
            DrawText(TextFormat("GAME OVER. Press Q to reset."), 100, 400, 40, RED);

            // Game reset
            if (IsKeyPressed(KEY_Q)) {
                score = 0;
                losecondition = false;
                Fireball.y = 0;
            }

        }


        // Ball movement
        if (IsKeyDown(KEY_SPACE)) {
            Ball.y -= 300 * GetFrameTime();
        }
        if (IsKeyDown(KEY_A)) {
            Ball.x -= 200 * GetFrameTime();
        }
        if (IsKeyDown(KEY_D)) {
            Ball.x += 200 * GetFrameTime();
        }

        // Check for collision between ball and ground platforms
        for (int i = 0; i < 4; i++) {
            if (CheckCollisionCircleRec((Vector2) {Ball.x, Ball.y}, Ball.radius,
                                        (Rectangle) {Ground[i].x, Ground[i].y, Ground[i].width, Ground[i].height})) {

                Ball.y = Ground[i].y - Ball.radius;
            }
        }

        if (Ball.y > GetScreenHeight() - Ball.radius) {
            Ball.y = GetScreenHeight() - Ball.radius;
        }
        if (Ball.y < 650 + Ball.radius) {
            Ball.y = 650 + Ball.radius;
        }

        if (Ball.x > GetScreenWidth() - Ball.radius) {
            Ball.x = GetScreenWidth() - Ball.radius;
        }
        if (Ball.x < 0 + Ball.radius) {
            Ball.x = 0 + Ball.radius;
        }

        EndDrawing();

    }

    CloseWindow();
    return 0;
}