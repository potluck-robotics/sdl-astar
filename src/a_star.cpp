#include "a_star.h"

#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <csignal>
#include <memory>

std::vector<std::vector<World::Cell>> AStar::Search() {
  std::cout << std::fixed;
  std::cout << std::setprecision(3);

  // get source and goal
  Node source{0, 0, 0, 0, 0, nullptr};
  Node goal{0, 0, 0, 0, 0, nullptr};
  std::vector<Node> path;

  for (size_t i = 0; i < grid_.size(); ++i) {
    for (size_t j = 0; j < grid_[i].size(); ++j) {
      if (grid_[i][j].type_ == World::CellType::kSource) {
        source.x = static_cast<int>(i);
        source.y = static_cast<int>(j);
      }
      if (grid_[i][j].type_ == World::CellType::kGoal) {
        goal.x = static_cast<int>(i);
        goal.y = static_cast<int>(j);
      }
    }
  }

  // push source to open list
  open_list_.push_back(source);

  while (open_list_.size() != 0) {
    std::sort(open_list_.begin(), open_list_.end(),
              [](const Node &a, const Node &b) { return a.f < b.f; });
    std::shared_ptr<Node> q = std::make_shared<Node>(*open_list_.begin());
    open_list_.erase(open_list_.begin());

  std::array<Node, kDirectionCount> successors = {{
      {q->x, q->y - 1, 0, 0, 0, q},
      {q->x + 1, q->y - 1, 0, 0, 0, q},
      {q->x + 1, q->y, 0, 0, 0, q},
      {q->x + 1, q->y + 1, 0, 0, 0, q},
      {q->x, q->y + 1, 0, 0, 0, q},
      {q->x - 1, q->y + 1, 0, 0, 0, q},
      {q->x - 1, q->y, 0, 0, 0, q},
      {q->x - 1, q->y - 1, 0, 0, 0, q},
  }};
    
    for (auto n : successors) {
      if (n.x < 0 || n.x > static_cast<int>(grid_.size()) - 1 || n.y < 0 ||
          n.y > static_cast<int>(grid_[0].size()) - 1) {
        continue;
      }
      switch (grid_[n.x][n.y].type_) {
        case World::CellType::kWall:
        case World::CellType::kSource:
          continue;
          break;
        case World::CellType::kGoal:
          // Reconstruct path
          path = ReconstructPath(n);
          closed_list_.push_back(*q);
          for (size_t j = 0; j < grid_[0].size(); j++) {
            for (size_t i = 0; i < grid_.size(); i++) {
              for (auto m : closed_list_) {
                if (n.x == static_cast<int>(i) && n.y == static_cast<int>(j)) {
                  break;
                } else if (m.x == static_cast<int>(i) &&
                        m.y == static_cast<int>(j)) {
                  grid_[i][j].f_ = static_cast<float>(m.f);
                  break;
                }
              }
            }
          }

          for (auto p : path)
          {
              grid_[p.x][p.y].on_path_ = true;
          }

          return grid_;
          break;
        default:
          break;
      }
      n.g = q->g + sqrt(pow(n.x - q->x, 2) + pow(n.y - q->y, 2));
      n.h = sqrt(pow(n.x - goal.x, 2) + pow(n.y - goal.y, 2));
      n.f = n.g + n.h;

      bool skip = false;
      for (auto m : open_list_) {
        if (m.x == n.x && m.y == n.y && m.f < n.f) {
          skip = true;
          break;
        }
      }

      for (auto m : closed_list_) {
        if (m.x == n.x && m.y == n.y && m.f < n.f) {
          skip = true;
          break;
        }
      }

      bool found = false;
      if (!skip) {
        for (auto m : open_list_) {
          if (m.x == n.x && m.y == n.y) {
            m = n;
            found = true;
            break;
          }
        }
        if (!found) {
         open_list_.push_back(n);
        }
      }
    }

    closed_list_.push_back(*q);

  }
  return grid_;
}

std::vector<AStar::Node> AStar::ReconstructPath(AStar::Node goal)
{
    std::vector<Node> path;

    Node n = goal;
    path.push_back(n);

    while(n.parent != nullptr)
    {
        n = *n.parent;
        path.push_back(n);
        std::cout << "x: " << n.x << "\ty: " << n.y << std::endl;
    }

    return path;
}

