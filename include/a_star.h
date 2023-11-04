#pragma once

#include <vector>
#include "world.h"

struct Node {
  int x;
  int y;
  int g;
  int h;
  int f;
  Node *parent;
};

class AStar {
 public:
  explicit AStar(const std::vector<std::vector<World::CellType>> &grid): grid_{grid} {} 

  void Search();

 private:
  std::vector<std::vector<World::CellType>> grid_;

  std::vector<Node> open_list_;
  std::vector<Node> closed_list_; 

};
