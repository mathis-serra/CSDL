#include "raylib.h"
#include "Grid.h"

int main() {
    int screenWidth = 800;
    int screenHeight = 600;
    int cellSize = 32;
    Grid grid(screenWidth / cellSize, screenHeight / cellSize, cellSize);

    InitWindow(screenWidth, screenHeight, "Raylib - Tower Defense ");

    // Load tiles from assets folder
    grid.loadTiles("assets/free-fields-tileset-pixel-art-for-tower-defense/Tiles");

    // Load level from file if exists
    grid.loadFromFile("level.txt");

    SetTargetFPS(60);

    bool isDragging = false;
    Vector2 lastMousePos = {0, 0};

    // Define UI parameters
    const int paletteWidth = 160;
    const int tileSize = 64;
    const int numTilesPerRow = paletteWidth / tileSize;
    const int paletteOffsetX = screenWidth - paletteWidth;

    int selectedTileIndex = 0;

    while (!WindowShouldClose()) {
        grid.update();

        // Handle mouse input to set tile indices
        Vector2 mousePos = GetMousePosition();
        int x = static_cast<int>(mousePos.x) / cellSize;
        int y = static_cast<int>(mousePos.y) / cellSize;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (mousePos.x >= paletteOffsetX && mousePos.x < screenWidth) {
                // Clicked in the palette, calculate selected tile index
                int paletteX = static_cast<int>((mousePos.x - paletteOffsetX) / tileSize);
                int paletteY = static_cast<int>((mousePos.y) / tileSize);
                selectedTileIndex = paletteY * numTilesPerRow + paletteX;
            } else {
                // Clicked in the grid, set cell with selected tile index
                isDragging = true;
                grid.setCell(x, y, selectedTileIndex);
                lastMousePos = mousePos;
            }
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            isDragging = false;
        }

        if (isDragging && (mousePos.x != lastMousePos.x || mousePos.y != lastMousePos.y)) {
            grid.setCell(x, y, selectedTileIndex);
            lastMousePos = mousePos;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw tile palette
        for (int i = 0; i < grid.getNumTileTextures(); ++i) {
            int paletteX = (i % numTilesPerRow) * tileSize + paletteOffsetX;
            int paletteY = (i / numTilesPerRow) * tileSize;

            // Draw tile preview
            Rectangle tileRect = { paletteX, paletteY, tileSize, tileSize };
            DrawRectangleRec(tileRect, LIGHTGRAY);
            if (i == selectedTileIndex) DrawRectangleLinesEx(tileRect, 2, RED); // Highlight selected tile

            // Draw tile texture if available
            Texture2D texture = grid.getTileTexture(i);
            if (texture.id > 0) {
                DrawTexture(texture, paletteX, paletteY, WHITE);
            }
        }

        // Draw grid
        grid.draw();

        EndDrawing();
    }

    // Save level to file before exiting
    grid.saveToFile("level.txt");

    CloseWindow();

    return 0;
}
