#include "raylib.h"

void draw_grid(int screenWidth, int screenHeight, int size, Color color) {
    for (int i = 0; i < screenWidth; i += size) {
        DrawLine(i, 0, i, screenHeight, Fade(color, 0.3f));
    }
    for (int i = 0; i < screenHeight; i += size) {
        DrawLine(0, i, screenWidth, i, Fade(color, 0.3f));
    }
}

void add_cell(int x, int y, int size, Color color) {
    DrawRectangle(x, y, size, size, color);
    
}

