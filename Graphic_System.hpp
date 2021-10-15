#pragma once
#include <SDL2/SDL.h>

class Graphic_System
{
public:
    Graphic_System()
    {
        if (SDL_CreateWindowAndRenderer(800, 600, 0, &this->_window, &this->_renderer) < 0)
        {
            printf("SDL error: %s\n", SDL_GetError());
        }
        SDL_SetWindowTitle(this->_window, "Test Window");
    }
    ~Graphic_System()
    {
        SDL_DestroyWindow(this->_window);
    }
    void render()
    {
        SDL_RenderPresent(this->_renderer);
    }
    void clear()
    {
        SDL_SetRenderDrawBlendMode(this->_renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(this->_renderer, 247, 83, 167, 255);
        SDL_RenderClear(this->_renderer);
    }

private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
};