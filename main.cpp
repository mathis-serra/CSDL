// main.cpp

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "game/vue/Grid.h"
#include "game/logic_game/cpp_files/Tower.h"
#include "game/logic_game/cpp_files/Enemy.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int GRID_ROWS = 10;
const int GRID_COLS = 10;
const int CELL_SIZE = 50;

bool init(SDL_Window*& window, SDL_Renderer*& renderer);
void close(SDL_Window* window, SDL_Renderer* renderer);

int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!init(window, renderer)) {
        std::cerr << "Failed to initialize!\n";
        return -1;
    }

    Grid grid(GRID_ROWS, GRID_COLS, CELL_SIZE);
    std::vector<Tower> towers;
    std::vector<Enemy> enemies;

    // Add some towers and enemies for demonstration
    towers.emplace_back(100, 100, CELL_SIZE);
    enemies.emplace_back(0, 150, CELL_SIZE, 1);

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                towers.emplace_back(x - CELL_SIZE / 2, y - CELL_SIZE / 2, CELL_SIZE);
            }
        }

        // Update enemies
        for (auto& enemy : enemies) {
            enemy.update();
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        grid.draw(renderer);

        // Draw towers
        for (const auto& tower : towers) {
            tower.draw(renderer);
        }

        // Draw enemies
        for (const auto& enemy : enemies) {
            enemy.draw(renderer);
        }

        SDL_RenderPresent(renderer);
    }

    close(window, renderer);
    return 0;
}

bool init(SDL_Window*& window, SDL_Renderer*& renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow("SDL Tower Defense", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    return true;
}

void close(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
