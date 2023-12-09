#pragma once

#include <vector>

#include "world.h"

class AStar {
 public:
  explicit AStar(const std::vector<std::vector<World::Cell>> &grid)
      : grid_{grid} {}

  std::vector<std::vector<World::Cell>> Search();

 private:
  struct Node {
    int x;
    int y;
    double g;
    double h;
    double f;
    Node *parent;
  };

  enum Direction {
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

  std::vector<std::vector<World::Cell>> grid_;

  std::vector<Node> open_list_;
  std::vector<Node> closed_list_;
};
