#include <getopt.h>

#include <iostream>
#include <regex>
#include <string>

#include "Game.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  // TODO: Add a command line option parser for debugging things
  int width{0}, height{0}, opt;
  while ((opt = getopt(argc, argv, "w:h:")) != -1) {
    switch (opt) {
      case 'w': {
        width = atoi(optarg);
        break;
      }
      case 'h': {
        height = atoi(optarg);
        break;
      }
    }
  }
  if (width > 0 && height > 0) {
    Game game(width, height);
  } else {
    Game game;
  }
  return 0;
}
