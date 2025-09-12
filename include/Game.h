#ifndef GAME_H
#define GAME_H

#include "SDL_render.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_timer.h"
#include "State.h"
#include <string>

class Game
{
private:
  static Game* instance;
  static SDL_Renderer* renderer;
  static SDL_Window* window;
  static State* state;

  int frameStart;
  float dt;
  
  Game(const std::string &title, int width, int height);
  void CalculateDeltaTime();

public:
  ~Game();

  static Game& GetInstance(const std::string &title = "", int width = 0, int height = 0);
  static SDL_Renderer *GetRenderer();

  State& GetState();
  float GetDeltaTime();

  void Run();
};

#endif
