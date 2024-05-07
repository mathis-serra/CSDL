#include "raylib.h"
#include <vector>
#include <utility>
#include <iostream> 

// Function to draw the grid based on the state of cells
void DrawGrid(const std::vector<std::vector<int>>& cells, int cellSize) {
    for (int row = 0; row < cells.size(); row++) {
        for (int column = 0; column < cells[row].size(); column++) {
            Color color = cells[row][column] ? Color{0, 0, 0, 255} : Color{255, 255, 255, 255};
            DrawRectangle(column * cellSize, row * cellSize, cellSize - 1, cellSize - 1, color);
        }
    }
}

// Function to set the value of a cell in the grid
void SetCellValue(std::vector<std::vector<int>>& cells, int row, int column, int value) {
    if (row >= 0 && row < cells.size() && column >= 0 && column < cells[0].size()) {
        cells[row][column] = value;
    }
}

// Function to count the number of live neighbors around a cell
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

// Function to update the state of the cells based on the Game of Life rules
void Update(std::vector<std::vector<int>>& cells, std::vector<std::vector<int>>& tempCells) {
    for (int row = 0; row < cells.size(); row++) {
        for (int column = 0; column < cells[row].size(); column++) {
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

    // Update the current grid with the new states from the temporary grid
    for (int row = 0; row < cells.size(); row++) {
        for (int column = 0; column < cells[row].size(); column++) {
            cells[row][column] = tempCells[row][column];
        }
    }
}

// Function to randomly populate the grid with live and dead cells
void FillRandom(std::vector<std::vector<int>>& cells) {
    for (int row = 0; row < cells.size(); row++) {
        for (int column = 0; column < cells[row].size(); column++) {
            int randomValue = GetRandomValue(0, 4);
            cells[row][column] = (randomValue == 4) ? 1 : 0;
        }
    }
}

// Function to save the current population to a text file
void SavePopulation(const std::vector<std::vector<int>>& cells, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file != NULL) {
        for (int row = 0; row < cells.size(); row++) {
            for (int column = 0; column < cells[row].size(); column++) {
                fprintf(file, "%d ", cells[row][column]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
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

        if (IsKeyPressed(KEY_S)) { // Press "S" key to save the population
            SavePopulation(cells, "population.txt");
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
