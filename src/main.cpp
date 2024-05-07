#include "raylib.h"
#include <vector>
#include <utility>

void DrawGrid(const std::vector<std::vector<int>>& cells, int cellSize) {
    for (size_t row = 0; row < cells.size(); row++) {
        for (size_t column = 0; column < cells[row].size(); column++) {
            Color color = cells[row][column] ? Color{0, 0, 0, 255} : Color{255, 255, 255, 255};
            DrawRectangle(column * cellSize, row * cellSize, cellSize - 1, cellSize - 1, color);
        }
    }
}

void SetCellValue(std::vector<std::vector<int>>& cells, int row, int column, int value) {
    if (row >= 0 && row < cells.size() && column >= 0 && column < cells[0].size()) {
        cells[row][column] = value;
    }
}

int CountLiveNeighbors(const std::vector<std::vector<int>>& cells, int row, int column) {
    int liveNeighbors = 0;
    std::vector<std::pair<int, int>> neighborOffsets = {
        {-1, 0}, {1, 0}, {0, -1}, {0 , 1},
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    for (const auto& offset : neighborOffsets) {
        int neighborRow = (row + offset.first + cells.size()) % cells.size();
        int neighborColumn = (column + offset.second + cells[0].size()) % cells[0].size(); 
        liveNeighbors += cells[neighborRow][neighborColumn];
    }

    return liveNeighbors;
}

void Update(std::vector<std::vector<int>>& cells, std::vector<std::vector<int>>& tempCells) {
    for (size_t row = 0; row < cells.size(); row++) {
        for (size_t column = 0; column < cells[row].size(); column++) {
            int liveNeighbors = CountLiveNeighbors(cells, row, column);
            int cellValue = cells[row][column];

            if (cellValue == 1) {
                if (liveNeighbors > 3 || liveNeighbors < 2) {
                    tempCells[row][column] = 0;
                } else {
                    tempCells[row][column] = 1;
                }
            } else {
                if (liveNeighbors == 3) {
                    tempCells[row][column] = 1;
                } else {
                    tempCells[row][column] = 0;
                }
            }
        }
    }

    // Mettre à jour la grille actuelle avec les nouveaux états de la grille temporaire
    for (size_t row = 0; row < cells.size(); row++) {
        for (size_t column = 0; column < cells[row].size(); column++) {
            cells[row][column] = tempCells[row][column];
        }
    }
}

void FillRandom(std::vector<std::vector<int>>& cells) {
    for (size_t row = 0; row < cells.size(); row++) {
        for (size_t column = 0; column < cells[row].size(); column++) {
            int randomValue = GetRandomValue(0, 4);
            cells[row][column] = (randomValue == 4) ? 1 : 0;
        }
    }
}

int main() {
    const int screenWidth = 750;
    const int screenHeight = 750;
    const int cellSize = 25;  

    InitWindow(screenWidth, screenHeight, "Game of Life");
    SetTargetFPS(12); 

    std::vector<std::vector<int>> cells(screenHeight / cellSize, std::vector<int>(screenWidth / cellSize, 0));
    std::vector<std::vector<int>> tempCells(screenHeight / cellSize, std::vector<int>(screenWidth / cellSize, 0));

    FillRandom(cells);

    bool drawGrid = false; 

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER)) { 
            drawGrid = true; 
        }

        Update(cells, tempCells);
        BeginDrawing();

        ClearBackground(BLACK);

        if (!drawGrid) {
            DrawText("Welcome to Game of Life", (screenWidth - MeasureText("Welcome to Game of Life", 50)) / 2, screenHeight / 2 - 80, 50, WHITE);
            DrawText("Press ENTER to play", (screenWidth - MeasureText("Press ENTER to play", 35)) / 2, screenHeight / 2 + 50, 35, WHITE);
        }

        if (drawGrid) { 
            DrawGrid(cells, cellSize);
        }
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
