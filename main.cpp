#include <iostream>
#include <SDL.h>


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define GRID_WIDTH 12 
#define GRID_HEIGHT 9 

int grid[GRID_WIDTH][GRID_HEIGHT];
void init_grid();
void draw_grid(SDL_Renderer* renderer, const int cell_size);

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("SDL2 Window",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    init_grid();

    SDL_Event e;
    bool quit = false;
    while (!quit){
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        unsigned int cell_size = 30;
        draw_grid(renderer, cell_size);
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (e.type == SDL_KEYDOWN){
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
        }

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void init_grid()
{
    for (int i = 0; i < GRID_WIDTH; i++){
        for (int j = 0; j < GRID_HEIGHT; j++) {
            grid[i][j] = 0;
        }
    }
}

void draw_grid(SDL_Renderer* renderer, const int cell_size)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

    for(int i = 0; i < GRID_WIDTH ; i++) 
    {
        for(int j = 0; j < GRID_HEIGHT ; j++) 
        {
            int x = (WINDOW_WIDTH - cell_size * GRID_WIDTH) / 2 + i * cell_size + 1;
            int y = (WINDOW_HEIGHT - cell_size * GRID_HEIGHT) / 2 + j * cell_size + 1;
            SDL_Rect rect = {x, y, cell_size - 2, cell_size - 2};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
