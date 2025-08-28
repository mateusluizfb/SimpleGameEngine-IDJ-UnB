#ifndef GAME_H
#define GAME_H

#include "SDL_render.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "State.h"
#include <string>

class Game
{
private:
  static Game* instance;
  static SDL_Renderer* renderer;
  static SDL_Window* window;
  static State* state;

  Game(const std::string &title, int width, int height);

public:
  ~Game();

  static Game& GetInstance(const std::string &title = "", int width = 0, int height = 0);
  static SDL_Renderer *GetRenderer();

  State& GetState();


  void Run();
};

#endif
