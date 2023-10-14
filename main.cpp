#include <iostream>
#include <SDL.h>

int grid[10][10];
void init_grid();
void draw_grid(SDL_Renderer* renderer);

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("SDL2 Window",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        680, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    init_grid();

    SDL_Event e;
    bool quit = false;
    while (!quit){
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        draw_grid(renderer);
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
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++) {
            grid[i][j] = 0;
        }
    }
}

void draw_grid(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawLine(renderer, 100, 100, 200, 200); 

//    for(int i = 0; i < 10 ; i++) {
//        SDL_RenderDrawLine(renderer, i*48, 0, i*48, 680); 
//        SDL_RenderDrawLine(renderer, 0, i*68, 480, i*68); 
//    }
}
