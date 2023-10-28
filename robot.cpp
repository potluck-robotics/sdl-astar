#include "./robot.h"

Robot::Robot(World *world) {
  world_ = world;
  x_ = 0;
  y_ = 0;
}

void Robot::Move(const int dx, const int dy) {
  x_ += dx;
  x_ = x_ > world_->GetWidth() ? world_->GetWidth() - 1 : x_;
  x_ = x_ < 0 ? 0 : x_;
  y_ += dy;
  y_ = y_ > world_->GetHeight() ? world_->GetHeight() - 1 : y_;
  y_ = y_ < 0 ? 0 : y_;
}

void Robot::Draw(SDL_Renderer *renderer, const int window_w, const int window_h,
                 const int cell_size) {
  SDL_SetRenderDrawColor(renderer, 127, 0, 127, 255);
  int x = (window_w - cell_size * GRID_WIDTH) / 2 + x_ * cell_size + 3;
  int y = (window_h - cell_size * GRID_HEIGHT) / 2 + y_ * cell_size + 3;
  SDL_Rect rect = {x, y, cell_size - 6, cell_size - 6};
  SDL_RenderFillRect(renderer, &rect);
}
