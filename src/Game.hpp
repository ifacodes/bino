#pragma once

#include "Graphic_System.hpp"

class Game {
 public:
  Game(int width = 1024, int height = 576);
  ~Game();

 private:
  int create_shader_from_files(const char* vertex_shader_file_path,
                               const char* fragment_shader_file_path);
  int create_shader_from_strings(const char* vertex_shader_source,
                                 const char* fragment_shader_source);
  void run();
  void draw(Graphic_System& g);
  void update(float dt);
  int _window_width;
  int _window_height;
};