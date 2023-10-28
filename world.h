#pragma once

#include <SDL.h>
#include <vector>

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
  World();
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

 private:
  void InitGrid(const int grid_width, const int grid_height);

  std::vector<std::vector<int>> grid_;
  int grid_width_, grid_height_;
  int window_h_, window_w_;
  int cell_size_;
};
