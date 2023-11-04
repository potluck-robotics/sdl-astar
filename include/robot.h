#pragma once
#include "./world.h"

/*! @brief The Robot class
 *
 *  This class represents the robot in the game.
 *  It is a simple object that can move around the world.
 */
class Robot {
 public:
  /*! @brief Constructor for the Robot class
   *
   *  @param world The world in which the robot exists
   */
  explicit Robot(World *world) : world_{world}, x_{0}, y_{0} {};

  /*! @brief Move the robot
   *
   *  This function moves the robot by the given amount.
   *
   *  @param dx The amount to move in the x direction
   *  @param dy The amount to move in the y direction
   */
  void Move(const int dx, const int dy);

  /*! @brief Draw the robot
   *
   *  This function draws the robot to the screen.
   *
   *  @param renderer The SDL_Renderer to draw to
   *  @param window_w The width of the window
   *  @param window_h The height of the window
   *  @param cell_size The size of each cell in the grid
   */
  void Draw(SDL_Renderer *renderer);

  const int GetX() { return x_; }
  const int GetY() { return y_; }

 private:
  World *world_;
  int x_;
  int y_;
};
