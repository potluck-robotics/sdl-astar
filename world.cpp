#include "./world.h"

/* World
 * init grid
 */
World::World() {}

World::World(const int window_w, const int window_h, const int grid_width,
             const int grid_height, const int cell_size) {
  window_w_ = window_w;
  window_h_ = window_h;
  cell_size_ = cell_size;
  InitGrid(grid_width, grid_height);
}

void World::InitGrid(const int grid_width, const int grid_height) {
  grid_.resize(grid_width);

  for (auto it = grid_.begin(); it != grid_.end(); it++) {
    it->resize(grid_height);
    for (auto it2 = it->begin(); it2 != it->end(); it2++) {
      *it2 = 0;
    }
  }
}

void World::Draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

  for (int i = 0; i < GetGridWidth(); i++) {
    for (int j = 0; j < GetGridHeight(); j++) {
      int x = (GetWindowWidth() - GetCellSize() * GetGridWidth()) / 2 +
              i * GetCellSize() + 1;
      int y = (GetWindowHeight() - GetCellSize() * GetGridHeight()) / 2 +
              j * GetCellSize() + 1;
      SDL_Rect rect = {x, y, GetCellSize() - 2, GetCellSize() - 2};
      SDL_RenderFillRect(renderer, &rect);
    }
  }
}

int World::GetGridWidth() { return grid_.size(); }

int World::GetGridHeight() { return grid_[0].size(); }

int World::GetWindowWidth() { return window_w_; }

int World::GetWindowHeight() { return window_h_; }
