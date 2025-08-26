#ifndef GAME_H
#define GAME_H

#include "SDL_include.h"
#include <string>

class Game
{
private:
  static Game* instance;

  Game(const std::string &title, int width, int height);

public:
  ~Game();

  static Game& GetInstance(const std::string &title = "", int width = 0, int height = 0);
};

#endif
