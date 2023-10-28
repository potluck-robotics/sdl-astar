#pragma once

#include <SDL.h>
#define GRID_WIDTH 12 
#define GRID_HEIGHT 9 

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
  
        /*! @brief Draw the world
         *
         *  This function draws the world to the screen.
         *
         *  @param renderer The SDL_Renderer to draw to
         *  @param window_w The width of the window
         *  @param window_h The height of the window
         *  @param cell_size The size of each cell in the grid
         */
        void draw(SDL_Renderer* renderer, const int window_w, const int window_h, const int cell_size);
        /*! @brief Get the width of the world
         *
         *  @return The width of the world
         */
        int get_width();
 
        /*! @brief Get the height of the world
         *
         *  @return The height of the world
         */
        int get_height();

    private:
        int grid_[GRID_WIDTH][GRID_HEIGHT];
        void init_grid();
};
