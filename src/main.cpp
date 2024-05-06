#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Exemple Raylib");

    SetTargetFPS(60); 

    while (!WindowShouldClose()) { 
        

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Hello, Raylib!", 190, 200, 20, DARKGRAY); 

        EndDrawing();
    }
   
    CloseWindow();

    return 0;
}
