#include "raylib.h"
#include <vector> 

bool drawGrid = false;
std::vector<Vector2> cellPositions; // Vecteur pour stocker les positions des cellules

void draw_grid(int screenWidth, int screenHeight, int size, Color color);
void add_cell(int x, int y, int size, Color color);

int main() {
    const int screenWidth = 1100;
    const int screenHeight = 700;
    const int cellSize = 16; // Taille de chaque cellule
    const int numCells = 5; // Nombre de cellules à ajouter
    InitWindow(screenWidth, screenHeight, "Game of Life");

    SetTargetFPS(60); 

    for (int i = 0; i < numCells; ++i) {
        // Génère des positions aléatoires multiples de la taille de la cellule
        int randX = GetRandomValue(0, (screenWidth / cellSize) - 1) * cellSize; 
        int randY = GetRandomValue(0, (screenHeight / cellSize) - 1) * cellSize; 
        cellPositions.push_back({(float)randX, (float)randY});
    }

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
            draw_grid(screenWidth, screenHeight, cellSize, GRAY);
            for (const auto& pos : cellPositions) {
                add_cell((int)pos.x, (int)pos.y, cellSize, RED);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}