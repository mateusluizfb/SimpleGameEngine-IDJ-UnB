#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Game.h"
#include <string>
#include <stdexcept>

Game* Game::instance = nullptr;


void init_sdl_deps()
{
  int sdlInitResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
  if (sdlInitResult != 0)
  {
    throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
  }

  int imgInitResult = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
  if ((imgInitResult & (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)) == 0)
  {
    throw std::runtime_error("Failed to initialize SDL_image: " + std::string(IMG_GetError()));
  }

  int mixInitResult = Mix_Init(MIX_INIT_MP3);
  if ((mixInitResult & MIX_INIT_MP3) == 0)
  {
    throw std::runtime_error("Failed to initialize SDL_mixer: " + std::string(Mix_GetError()));
  }

  int mixOpenResult = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
  if (mixOpenResult != 0)
  {
    throw std::runtime_error("Failed to open audio: " + std::string(Mix_GetError()));
  }

  printf("INFO - SDL and its dependencies initialized successfully.\n");
}

Game::Game(const std::string &title, int width, int height)
{
  printf("INFO - Initializing game: %s (%dx%d)\n", title.c_str(), width, height);
  if (instance != nullptr)
  {
    throw std::runtime_error("Game instance already exists!");
  }
  
  instance = this;

  init_sdl_deps();
}

Game::~Game()
{
  instance = nullptr;
}


Game& Game::GetInstance(const std::string &title, int width, int height)
{
  printf("INFO - Creating game instance\n");
  if (instance == nullptr) {
    instance = new Game(title, width, height);
  }
  return *instance;
}
