#include <iostream>
#include <limits>
#include <ranges>
#include <algorithm>

#include "./world.h"
#include "./a_star.h"

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
      it2->type_ = CellType::kEmpty;
    }
  }
}

void World::Draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, COLOR_CELL);

  float f_min = std::numeric_limits<float>::max();
  float f_max = std::numeric_limits<float>::min();
  for (size_t i = 0; i < grid_.size(); i++) {
    for (size_t j = 0; j < grid_[0].size(); j++) {
      if (grid_[i][j].f_ > 0) {
        f_min = grid_[i][j].f_ < f_min ? grid_[i][j].f_ : f_min;
        f_max = grid_[i][j].f_ > f_max ? grid_[i][j].f_ : f_max;
      }
    }
  }

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
      SDL_Color c = {COLOR_CELL};
      switch (grid_[i][j].type_) {
        case CellType::kEmpty:
          SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
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
  for (int i = 0; i < GetGridWidth(); i++) {
    for (int j = 0; j < GetGridHeight(); j++) {
      int p = CELL_PADDING + 4;
      int x = 
          (GetWindowWidth() - GetCellSize() * GetGridWidth()) / 2 +
          i * GetCellSize() + p;
      int y = 
          (GetWindowHeight() - GetCellSize() * GetGridHeight()) / 2 +
          j * GetCellSize() + p;
      SDL_Rect rect = {x, y, GetCellSize() - p * 2,
                       GetCellSize() - p * 2};
      SDL_Color c = {COLOR_CELL};
      if (grid_[i][j].type_ == CellType::kEmpty && grid_[i][j].f_ > 0.0f) {
        c.r = c.r * (grid_[i][j].f_ - f_min) / (f_max - f_min) * 0.5;
        c.g = c.g * (grid_[i][j].f_ - f_min) / (f_max - f_min) * 0.5;
        c.b = c.b * (grid_[i][j].f_ - f_min) / (f_max - f_min) * 0.5;
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
        SDL_RenderFillRect(renderer, &rect);
      }
    }
  }
//
//  for (int i = 0; i < grid_.size(); i++) {
//    for (int j = 0; j < grid_[0].size(); j++) {
//      std::cout << grid_[i][j].f_ << " ";
//    }
//    std::cout << std::endl;
//  }
//  std::cout << std::endl;
}

int World::GetGridWidth() { return static_cast<int>(grid_.size()); }

int World::GetGridHeight() { return static_cast<int>(grid_[0].size()); }

int World::GetWindowWidth() { return window_w_; }

int World::GetWindowHeight() { return window_h_; }

void World::Reset() {
  for (auto it = grid_.begin(); it != grid_.end(); it++) {
    for (auto it2 = it->begin(); it2 != it->end(); it2++) {
      it2->type_ = CellType::kEmpty;
      it2->f_ = 0.0f;
    }
  }
}

void World::SetSource(const int x, const int y) {
  if (!SetCellType(x, y, CellType::kSource, false)) {
    return;
  }

  for (auto it = grid_.begin(); it != grid_.end(); it++) {
    for (auto it2 = it->begin(); it2 != it->end(); it2++) {
      if (it2->type_ == CellType::kSource &&
          it2 != (*(grid_.begin() + x)).begin() + y) {
        it2->type_ = CellType::kEmpty;
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
      if (it2->type_ == CellType::kGoal &&
          it2 != (*(grid_.begin() + x)).begin() + y) {
        it2->type_ = CellType::kEmpty;
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

  if (grid_[x][y].type_ == CellType::kEmpty) {
    grid_[x][y].type_ = cell_type;
    return true;
  } else if (toggle && grid_[x][y].type_ == CellType::kWall) {
    grid_[x][y].type_ = CellType::kEmpty;
    return true;
  }
  return false;
}

void World::Search() {
  bool source_exist = false;
  bool goal_exist = false;

  // Check Start and Goal are exist in grid
  for (auto it = grid_.begin(); it != grid_.end(); it++) {
    for (auto it2 = it->begin(); it2 != it->end(); it2++) {
      if (it2->type_ == CellType::kSource) {
        source_exist = true;
      }
      if (it2->type_ == CellType::kGoal) {
        goal_exist = true;
      }
    }
  }

  if (!source_exist || !goal_exist) {
    return;
  }

  // Clear f values
  for (auto it = grid_.begin(); it != grid_.end(); it++) {
    for (auto it2 = it->begin(); it2 != it->end(); it2++) {
      it2->f_ = 0.0f;
    }
  }
  
  AStar astar = AStar(grid_);
  grid_ = astar.Search();
}
