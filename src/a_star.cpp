#include "a_star.h"

#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>

std::vector<std::vector<World::Cell>> AStar::Search() {
  std::cout << std::fixed;
  std::cout << std::setprecision(3);

  int max_open_list_size = 0;
  int max_closed_list_size = 0;

  // get source and goal
  Node source{0, 0, 0, 0, 0, nullptr};
  Node goal{0, 0, 0, 0, 0, nullptr};

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
    Node q = *open_list_.begin();
    open_list_.erase(open_list_.begin());

    std::array<Node, kDirectionCount> successors = {{
        {q.x, q.y - 1, 0, 0, 0, &q},
        {q.x + 1, q.y - 1, 0, 0, 0, &q},
        {q.x + 1, q.y, 0, 0, 0, &q},
        {q.x + 1, q.y + 1, 0, 0, 0, &q},
        {q.x, q.y + 1, 0, 0, 0, &q},
        {q.x - 1, q.y + 1, 0, 0, 0, &q},
        {q.x - 1, q.y, 0, 0, 0, &q},
        {q.x - 1, q.y - 1, 0, 0, 0, &q},
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
          closed_list_.push_back(q);
          std::cout << "Max open list size: " << max_open_list_size << std::endl;
          std::cout << "Max closed list size: " << max_closed_list_size << std::endl;
          for (size_t j = 0; j < grid_[0].size(); j++) {
            for (size_t i = 0; i < grid_.size(); i++) {
              bool found = false;
              for (auto m : closed_list_) {
                if (n.x == static_cast<int>(i) && n.y == static_cast<int>(j)) {
                  found = true;
                  std::cout << "GOAL!" << " ";
                  break;
                } else if (m.x == static_cast<int>(i) &&
                        m.y == static_cast<int>(j)) {
                  found = true;
                  std::cout << m.f / 100 << " ";
                  grid_[i][j].f_ = static_cast<float>(m.f);
                  break;
                }
              }
              if (!found) {
                std::cout << "XXXXX" << " ";
              }
            }
            std::cout << std::endl;
          }
          std::cout << q.x << ", " << q.y << std::endl;
          std::cout << std::endl;
          return grid_;
          break;
        default:
          break;
      }
      n.g = q.g + sqrt(pow(n.x - q.x, 2) + pow(n.y - q.y, 2));
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
          max_open_list_size = std::max(max_open_list_size,
                                        static_cast<int>(open_list_.size()));
 
        }
      }
    }

    closed_list_.push_back(q);
    max_closed_list_size = std::max(max_closed_list_size,
                                    static_cast<int>(closed_list_.size()));

  }
  return grid_;
}
