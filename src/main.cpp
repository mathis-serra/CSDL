#include "raylib.h"

bool drawGrid = false;

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Game of Life");

    SetTargetFPS(60); 

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER)) { 
            drawGrid = true;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        if (!drawGrid) {
        DrawText("Welcome to Game of Life", (screenWidth - MeasureText("Welcome to Game of Life", 40)) / 2, screenHeight / 2 - 20, 40, WHITE);
        }

        if (drawGrid) { 
            for (int i = 0; i < screenWidth; i += 20) {
                DrawLine(i, 0, i, screenHeight, Fade(LIGHTGRAY, 0.3f));
            }
            for (int i = 0; i < screenHeight; i += 20) {
                DrawLine(0, i, screenWidth, i, Fade(LIGHTGRAY, 0.3f));
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
