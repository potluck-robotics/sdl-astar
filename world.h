#pragma once

#include <SDL.h>

#define GRID_WIDTH 12 
#define GRID_HEIGHT 9 

class World {
    public:
        World();
        void draw(SDL_Renderer* renderer, const int window_w, const int window_h, const int cell_size);

    private:
        int grid_[GRID_WIDTH][GRID_HEIGHT];
        void init_grid();
};
