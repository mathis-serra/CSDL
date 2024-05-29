// Grid.cpp

#include "Grid.h"

Grid::Grid(int rows, int cols, int cellSize) : rows(rows), cols(cols), cellSize(cellSize) {}

void Grid::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i <= rows; ++i) {
        SDL_RenderDrawLine(renderer, 0, i * cellSize, cols * cellSize, i * cellSize);
    }
    for (int i = 0; i <= cols; ++i) {
        SDL_RenderDrawLine(renderer, i * cellSize, 0, i * cellSize, rows * cellSize);
    }
}
