#pragma once
#include "world.h"

class Robot {
    public:
        Robot(World* world);
        void move(const int dx, const int dy);
        void draw(SDL_Renderer* renderer, const int window_w, const int window_h, const int cell_size);
    private:
        World* world_;
        int x_;
        int y_;
};
