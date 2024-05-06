#include "raylib.h"
#include <vector> 
#include"simulation.hpp"



int main() {
    const int screenWidth = 750;
    const int screenHeight = 750;
    const int cellSize = 25;  
    InitWindow(screenWidth, screenHeight, "Game of Life");
    SetTargetFPS(12); 
    Simulation Simulation(screenHeight, screenWidth, cellSize);
    Simulation.SetCellValue(3, 4, 1);



    
    

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER)) { 
            // drawGrid = true; 
            continue; 
        }



        Simulation.Update();
        BeginDrawing();

        ClearBackground(BLACK);

        // if (!drawGrid) {
        //     DrawText("Welcome to Game of Life", (screenWidth - MeasureText("Welcome to Game of Life", 50)) / 2, screenHeight / 2 - 80, 50, WHITE);
        //     DrawText("Press ENTER to play", (screenWidth - MeasureText("Press ENTER to play", 35)) / 2, screenHeight / 2 + 50, 35, WHITE);
        // }

        // if (drawGrid) { 
        //     draw_grid(screenWidth, screenHeight, cellSize, GRAY);
        //     for (const auto& pos : cellPositions) {
        //         add_cell((int)pos.x, (int)pos.y, cellSize, RED);
        //     }
        // }
        Simulation.Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
