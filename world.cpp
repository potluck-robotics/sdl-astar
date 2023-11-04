#include "./world.h"

/* World
 * init grid
 */
World::World(const int window_w, const int window_h,
             const int grid_width, const int grid_height,
             const int cell_size)
    : window_w_{window_w}, window_h_{window_h}, cell_size_{cell_size} {
  InitGrid(grid_width, grid_height);
}

void World::InitGrid(const int grid_width, const int grid_height) {
  grid_.resize(grid_width);

  for (auto it = grid_.begin(); it != grid_.end(); it++) {
    it->resize(grid_height);
    for (auto it2 = it->begin(); it2 != it->end(); it2++) {
      *it2 = CellType::kEmpty;
    }
  }
}

void World::Draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, COLOR_CELL);

  for (int i = 0; i < GetGridWidth(); i++) {
    for (int j = 0; j < GetGridHeight(); j++) {
      int x = 
          (GetWindowWidth() - GetCellSize() * GetGridWidth()) / 2 +
          i * GetCellSize() + CELL_PADDING;
      int y = 
          (GetWindowHeight() - GetCellSize() * GetGridHeight()) / 2 +
          j * GetCellSize() + CELL_PADDING;
      SDL_Rect rect = {x, y, GetCellSize() - CELL_PADDING * 2,
                       GetCellSize() - CELL_PADDING * 2};
      switch (grid_[i][j]) {
        case CellType::kEmpty:
          SDL_SetRenderDrawColor(renderer, COLOR_CELL);
          break;
        case CellType::kSource:
          SDL_SetRenderDrawColor(renderer, COLOR_SOURCE);
          break;
        case CellType::kGoal:
          SDL_SetRenderDrawColor(renderer, COLOR_GOAL);
          break;
        case CellType::kWall:
          SDL_SetRenderDrawColor(renderer, COLOR_WALL);
          break;
        default:
          SDL_SetRenderDrawColor(renderer, COLOR_BACKGROUND);
          break;
      }
      SDL_RenderFillRect(renderer, &rect);
    }
  }
}

int World::GetGridWidth() { return static_cast<int>(grid_.size()); }

int World::GetGridHeight() { return static_cast<int>(grid_[0].size()); }

int World::GetWindowWidth() { return window_w_; }

int World::GetWindowHeight() { return window_h_; }

void World::SetStart(const int x, const int y) {
  if (!SetCellType(x, y, CellType::kSource, false)) {
    return;
  }

  for (auto it = grid_.begin(); it != grid_.end(); it++) {
    for (auto it2 = it->begin(); it2 != it->end(); it2++) {
      if (*it2 == CellType::kSource &&
          it2 != (*(grid_.begin() + x)).begin() + y) {
        *it2 = CellType::kEmpty;
      }
    }
  }
}

void World::SetGoal(const int x, const int y) {
  if (!SetCellType(x, y, CellType::kGoal, false)) {
    return;
  }

  for (auto it = grid_.begin(); it != grid_.end(); it++) {
    for (auto it2 = it->begin(); it2 != it->end(); it2++) {
      if (*it2 == CellType::kGoal &&
          it2 != (*(grid_.begin() + x)).begin() + y) {
        *it2 = CellType::kEmpty;
      }
    }
  }
}

void World::ToggleWall(const int x, const int y) {
  SetCellType(x, y, CellType::kWall, true);
}

bool World::SetCellType(const int x, const int y, const CellType cell_type,
                        bool toggle) {
  if (x < 0 || x > GetGridWidth() - 1 || y < 0 || y > GetGridHeight() - 1) {
    return false;
  }

  if (grid_[x][y] == CellType::kEmpty) {
    grid_[x][y] = cell_type;
    return true;
  } else if (toggle && grid_[x][y] == CellType::kWall) {
    grid_[x][y] = CellType::kEmpty;
    return true;
  }
  return false;
}
