#pragma once

#include "Graphic_System.hpp"

class Game
{
public:
    Game();
    ~Game();

private:
    void run();
    void draw(Graphic_System &g);
    void update(float dt);
};