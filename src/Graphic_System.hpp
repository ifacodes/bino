#pragma once
// clang-format off
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
// clang-format on

#include <iostream>

class Graphic_System {
 public:
  Graphic_System(int width, int height) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Add High DPI at some point. This might require XCode.

    if (!(this->_window = SDL_CreateWindow(
              "Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
              width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI))) {
      printf("SDL error: %s\n", SDL_GetError());
    }

    this->_context = SDL_GL_CreateContext(this->_window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
      std::cerr << "Failed to initialise OpenGL context" << std::endl;
      exit(1);
    }
    std::cout << "OpenGL Version: " << GLVersion.major << "." << GLVersion.minor
              << std::endl;
  }
  ~Graphic_System() {
    SDL_GL_DeleteContext(this->_context);
    SDL_DestroyWindow(this->_window);
  }
  void render() {
    // Do stuff
    SDL_GL_SwapWindow(this->_window);
  }
  void clear() {
    glClearColor(147, 255, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
  }

 private:
  SDL_Window *_window;
  SDL_GLContext _context;
};