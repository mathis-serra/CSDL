// Grid.h

#ifndef GRID_H
#define GRID_H

#include <SDL2/SDL.h>

class Grid {
public:
    Grid(int rows, int cols, int cellSize);
    void draw(SDL_Renderer* renderer);

private:
    int rows;
    int cols;
    int cellSize;
};

#endif // GRID_H
