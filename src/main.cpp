#include <SDL.h>

#include <iostream>

#include "robot.h"
#include "world.h"
#include "config.h"

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *window =
      SDL_CreateWindow("SDL A*", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_SetRenderDrawColor(renderer, COLOR_BACKGROUND);
  SDL_RenderClear(renderer);

  World world(WINDOW_WIDTH, WINDOW_HEIGHT, GRID_WIDTH, GRID_HEIGHT, CELL_SIZE);
  Robot cursor(&world);

  SDL_Event e;
  bool quit = false;

  while (!quit) {
    SDL_SetRenderDrawColor(renderer, COLOR_BACKGROUND);
    SDL_RenderClear(renderer);

    world.Draw(renderer);
    cursor.Draw(renderer);

    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_UP:
            cursor.Move(0, -1);
            break;
          case SDLK_DOWN:
            cursor.Move(0, 1);
            break;
          case SDLK_LEFT:
            cursor.Move(-1, 0);
            break;
          case SDLK_RIGHT:
            cursor.Move(1, 0);
            break;
          case SDLK_ESCAPE:
            quit = true;
            break;
          case SDLK_s:
            world.SetSource(cursor.GetX(), cursor.GetY());
            break;
          case SDLK_g:
            world.SetGoal(cursor.GetX(), cursor.GetY());
            break;
          case SDLK_SPACE:
            world.ToggleWall(cursor.GetX(), cursor.GetY());
            break;
          case SDLK_RETURN:
            world.Search();
            break;
          default:
            break;
        }
      }
    }

    SDL_RenderPresent(renderer);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
