#pragma once

#include <SDL.h>

#include <vector>

#include "./config.h"

/*! @brief The World class
 *
 *  This class represents the world in which the game takes place.
 *  It is a grid of cells, each of which can be either empty or
 *  contain a wall.
 */
class World {
 public:
  /*! @brief Constructor for the World class
   */
  World(const int window_w, const int window_h, const int grid_width,
        const int grid_height, const int cell_size);

  /*! @brief Draw the world
   *
   *  This function draws the world to the screen.
   *
   *  @param renderer The SDL_Renderer to draw to
   *  @param window_w The width of the window
   *  @param window_h The height of the window
   *  @param cell_size The size of each cell in the grid
   */
  void Draw(SDL_Renderer *renderer);
  /*! @brief Get the width of the world
   *
   *  @return The width of the world
   */
  int GetGridWidth();

  /*! @brief Get the height of the world
   *
   *  @return The height of the world
   */
  int GetGridHeight();

  int GetWindowWidth();

  int GetWindowHeight();

  int GetCellSize() { return cell_size_; }

  void SetSource(const int x, const int y);
  void SetGoal(const int x, const int y);
  void ToggleWall(const int x, const int y);

  void Search();

 private:
  enum class CellType {
    kEmpty = 0,
    kSource,
    kGoal,
    kWall,
  };

  void InitGrid(const int grid_width, const int grid_height);

  std::vector<std::vector<CellType>> grid_;
  int window_w_, window_h_;
  int cell_size_;

  bool SetCellType(const int x, const int y, const CellType cell_type,
                   bool toggle);
};
