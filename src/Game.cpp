#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Game.h"
#include <string>
#include <stdexcept>

Game* Game::instance = nullptr;

Game::Game(const std::string &title, int width, int height)
{
  if (instance != nullptr)
  {
    throw std::runtime_error("Game instance already exists!");
  }
  instance = this;
}

Game::~Game()
{
  instance = nullptr;
}


Game& Game::GetInstance(const std::string &title, int width, int height)
{
  if (instance == nullptr) {
    instance = new Game(title, width, height);
  }
  return *instance;
}
