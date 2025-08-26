#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Game.h"
#include <string>
#include <stdexcept>

Game* Game::instance = nullptr;
SDL_Renderer* Game::renderer = nullptr;

SDL_Renderer* init_window(const std::string &title, int width, int height)
{
  printf("INFO - Creating window: %s (%dx%d)\n", title.c_str(), width, height);

  SDL_Window *window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
  if (window == nullptr)
  {
    throw std::runtime_error("Failed to create SDL window: " + std::string(SDL_GetError()));
  }

  SDL_Renderer *initialized_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (initialized_renderer == nullptr)
  {
    throw std::runtime_error("Failed to create SDL renderer: " + std::string(SDL_GetError()));
  }

  printf("INFO - Window and renderer created successfully.\n");

  return initialized_renderer;
}

void init_sdl_deps()
{
  printf("INFO - Initializing SDL and its dependencies\n");

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
  renderer = init_window(title, width, height);
}

Game::~Game()
{
  printf("INFO - Cleaning up game resources\n");

  instance = nullptr;
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  printf("INFO - Game resources cleaned up successfully.\n");
}

Game& Game::GetInstance(const std::string &title, int width, int height)
{
  printf("INFO - Creating game instance\n");
  if (instance == nullptr) {
    instance = new Game(title, width, height);
  }
  return *instance;
}

State& Game::GetState()
{
  // Temp
  State* state = new State();
  return *state;
}

SDL_Renderer *Game::GetRenderer()
{
  return renderer;
}
