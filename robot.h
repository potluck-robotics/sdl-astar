#pragma once
#include "world.h"

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
        Robot(World* world);

        /*! @brief Move the robot
         *
         *  This function moves the robot by the given amount.
         *
         *  @param dx The amount to move in the x direction
         *  @param dy The amount to move in the y direction
         */
        void move(const int dx, const int dy);

        /*! @brief Draw the robot
         *
         *  This function draws the robot to the screen.
         *
         *  @param renderer The SDL_Renderer to draw to
         *  @param window_w The width of the window
         *  @param window_h The height of the window
         *  @param cell_size The size of each cell in the grid
         */
        void draw(SDL_Renderer* renderer, const int window_w, const int window_h, const int cell_size);

    private:
        World* world_;
        int x_;
        int y_;
};
