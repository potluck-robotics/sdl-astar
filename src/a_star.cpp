#include "a_star.h"
#include <algorithm>
#include <array>

enum Direction{
  kNorth = 0,
  kNorthEast,
  kEast,
  kSouthEast,
  kSouth,
  kSouthWest,
  kWest,
  kNorthWest,
  kDirectionCount
};

void AStar::Search() {
  // get source and goal
  Node source{0, 0, 0, 0, 0, nullptr};
  Node goal{0, 0, 0, 0, 0, nullptr};

  for (size_t i = 0; i < grid_.size(); ++i) {
    for (size_t j = 0; j < grid_[i].size(); ++j) {
      if (grid_[i][j] == World::CellType::kSource) {
        source.x = static_cast<int>(i); 
        source.y = static_cast<int>(j);
      }
      if (grid_[i][j] == World::CellType::kGoal) {
        goal.x = static_cast<int>(i);
        goal.y = static_cast<int>(j);
      }
    }
  }

  // push source to open list
  open_list_.push_back(source);
  // TODO: delete this
  open_list_.push_back(goal);

  while (open_list_.size() != 0) {
    std::sort(open_list_.begin(), open_list_.end(), [](const Node &a, const Node &b) { return a.f < b.f; });
    Node q = *open_list_.begin();
    open_list_.erase(open_list_.begin());

    std::array<Node, kDirectionCount> successors;

    // generate successors
    successors[kNorth].x = q.x;
    successors[kNorth].y = q.y - 1;
    successors[kNorthEast].x = q.x + 1;
    successors[kNorthEast].y = q.y - 1;
    // E
    successors[kEast].x = q.x + 1;
    successors[kEast].y = q.y;
    // SE
    successors[kSouthEast].x = q.x + 1;
    successors[kSouthEast].y = q.y + 1;
    // S
    successors[kSouth].x = q.x;
    successors[kSouth].y = q.y + 1;
    // SW
    successors[kSouthWest].x = q.x - 1;
    successors[kSouthWest].y = q.y + 1;
    // W
    successors[kWest].x = q.x - 1; 
    successors[kWest].y = q.y;
    // NW
    successors[kNorthWest].x = q.x - 1;
    successors[kNorthWest].y = q.y - 1;
  }
}
