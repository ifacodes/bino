#include "Game.hpp"

#include <SDL2/SDL.h>

Game::Game(int width, int height)
    : _window_width(width), _window_height(height) {
  SDL_Init(SDL_INIT_EVERYTHING);
  this->run();
}

Game::~Game() {}

int Game::create_shader_from_files(const char* vertex_shader_file_path,
                                   const char* fragment_shader_file_path) {
  char vertex_shader_source[100000];
  char fragment_shader_source[100000];
  {
    FILE* vs_file = std::fopen(vertex_shader_file_path, "r+");
    if (!vs_file) {
      std::cerr << "Failed to open file: " << vertex_shader_file_path
                << std::endl;
      return 0;
    }
    size_t count = fread(vertex_shader_source, 1, 99999, vs_file);
    vertex_shader_source[count] = '\0';
    fclose(vs_file);
  }
  {
    FILE* fs_file = std::fopen(fragment_shader_file_path, "r+");
    if (!fs_file) {
      std::cerr << "Failed to open file: " << fragment_shader_file_path
                << std::endl;
      return 0;
    }
    size_t count = fread(fragment_shader_source, 1, 99999, fs_file);
    fragment_shader_source[count] = '\0';
    fclose(fs_file);
  }
  return this->create_shader_from_strings(vertex_shader_source,
                                          fragment_shader_source);
}

int Game::create_shader_from_strings(const char* vertex_shader_source,
                                     const char* fragment_shader_source) {
  GLuint program = glCreateProgram();
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

  {
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    int success = -1;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (GL_TRUE != success) {
      std::cerr << "Vertex Shader " << vertex_shader << "could not compile."
                << std::endl;
      char log[2048];
      glGetShaderInfoLog(vertex_shader, 2048, NULL, log);
      std::cerr << "Error Log for: " << vertex_shader << std::endl
                << log << std::endl;
      glDeleteShader(vertex_shader);
      glDeleteShader(fragment_shader);
      glDeleteProgram(program);
      return 0;
    }
  }

  {
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    int success = -1;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if (GL_TRUE != success) {
      std::cerr << "Fragment Shader " << fragment_shader << "could not compile."
                << std::endl;
      char log[2048];
      glGetShaderInfoLog(fragment_shader, 2048, NULL, log);
      std::cerr << "Error Log for: " << fragment_shader << log << std::endl;
      glDeleteShader(vertex_shader);
      glDeleteShader(fragment_shader);
      glDeleteProgram(program);
      return 0;
    }
  }
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);

  {
    glLinkProgram(program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    int success = -1;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (GL_TRUE != success) {
      std::cerr << "Unable to link shaders for program: " << program
                << std::endl;
      char log[2048];
      glGetProgramInfoLog(program, 2048, NULL, log);
      std::cerr << "Error Log for: " << program << std::endl
                << log << std::endl;
      glDeleteProgram(program);
      return 0;
    }
  }

  return program;
}

void Game::run() {
  Graphic_System g(this->_window_width, this->_window_height);
  GLuint shader_test =
      this->create_shader_from_files("shaders/test.vert", "shaders/test.frag");
  std::cout << shader_test << std::endl;
  SDL_Event e;
  while (true) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_QUIT: {
          return;
        }
        case SDL_WINDOWEVENT: {
          switch (e.window.event) {
            case SDL_WINDOWEVENT_RESIZED: {
              printf("Window Resized!");
            }
          }
        }
      }
    }
    this->draw(g);
  }
}

void Game::draw(Graphic_System& g) {
  g.clear();
  g.render();
}

void Game::update(float dt) {}