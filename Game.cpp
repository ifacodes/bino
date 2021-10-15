#include <SDL2/SDL.h>

#include "Game.hpp"

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    this->run();
}

Game::~Game()
{
}

void Game::run()
{
    Graphic_System g;
    SDL_Event e;
    while (true)
    {
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                return;
            }
        }
        this->draw(g);
    }
}

void Game::draw(Graphic_System &g)
{
    g.clear();
    g.render();
}

void Game::update(float dt)
{
}