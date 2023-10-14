#include "world.h"

/* World
 * init grid 
 */
World::World()
{
    init_grid();
}

void World::init_grid()
{
    for (int i = 0; i < GRID_WIDTH; i++){
        for (int j = 0; j < GRID_HEIGHT; j++) {
            grid_[i][j] = 0;
        }
    }
}

void World::draw(SDL_Renderer* renderer, const int window_w, const int window_h, const int cell_size)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

    for(int i = 0; i < GRID_WIDTH ; i++) 
    {
        for(int j = 0; j < GRID_HEIGHT ; j++) 
        {
            int x = (window_w - cell_size * GRID_WIDTH) / 2 + i * cell_size + 1;
            int y = (window_h - cell_size * GRID_HEIGHT) / 2 + j * cell_size + 1;
            SDL_Rect rect = {x, y, cell_size - 2, cell_size - 2};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

int World::get_width()
{
    return GRID_WIDTH;
}

int World::get_height()
{
    return GRID_HEIGHT;
}
