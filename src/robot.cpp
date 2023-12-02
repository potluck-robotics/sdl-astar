#include "robot.h"

void Robot::Move(const int dx, const int dy) {
  x_ += dx;
  x_ = x_ >= world_->GetGridWidth() ? world_->GetGridWidth() - 1 : x_;
  x_ = x_ < 0 ? 0 : x_;
  y_ += dy;
  y_ = y_ >= world_->GetGridHeight() ? world_->GetGridHeight() - 1 : y_;
  y_ = y_ < 0 ? 0 : y_;
}

void Robot::Draw(SDL_Renderer *renderer) {
  int window_w = world_->GetWindowWidth();
  int window_h = world_->GetWindowHeight();
  int grid_width = world_->GetGridWidth();
  int grid_height = world_->GetGridHeight();
  int cell_size = world_->GetCellSize();

  SDL_SetRenderDrawColor(renderer, COLOR_CURSOR);
  int x =
      (window_w - cell_size * grid_width) / 2 + x_ * cell_size + CURSOR_PADDING;
  int y = (window_h - cell_size * grid_height) / 2 + y_ * cell_size +
          CURSOR_PADDING;
  SDL_Rect rect = {x, y, cell_size - CURSOR_PADDING * 2,
                   cell_size - CURSOR_PADDING * 2};
  SDL_RenderFillRect(renderer, &rect);
}
