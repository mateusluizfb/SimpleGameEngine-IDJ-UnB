#include <string>
#include <stdexcept>
#include "Log.h"
#include "Game.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

Game* Game::instance = nullptr;
SDL_Renderer* Game::renderer = nullptr;
SDL_Window* Game::window = nullptr;
State* Game::state = nullptr;

SDL_Window* init_window(const std::string &title, int width, int height)
{
  Log::info("GAME - Creating window: " + title + " (" + std::to_string(width) + "x" + std::to_string(height) + ")");

  SDL_Window *window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
  if (window == nullptr)
  {
    throw std::runtime_error("GAME - Failed to create SDL window: " + std::string(SDL_GetError()));
  }

  return window;
}

SDL_Renderer* init_renderer(SDL_Window* window)
{
  Log::info("GAME - Creating renderer");

  SDL_Renderer *initialized_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (initialized_renderer == nullptr)
  {
    throw std::runtime_error("GAME - Failed to create SDL renderer: " + std::string(SDL_GetError()));
  }

  return initialized_renderer;
}

void init_sdl_libs()
{
  Log::info("GAME - Initializing SDL and its dependencies");

  int sdlInitResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
  if (sdlInitResult != 0)
  {
    throw std::runtime_error("GAME - Failed to initialize SDL: " + std::string(SDL_GetError()));
  }

  int imgInitResult = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
  if ((imgInitResult & (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)) == 0)
  {
    throw std::runtime_error("GAME - Failed to initialize SDL_image: " + std::string(IMG_GetError()));
  }

  int mixInitResult = Mix_Init(MIX_INIT_MP3);
  if ((mixInitResult & MIX_INIT_MP3) == 0)
  {
    throw std::runtime_error("GAME - Failed to initialize SDL_mixer: " + std::string(Mix_GetError()));
  }

  int mixOpenResult = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
  
  if (mixOpenResult != 0)
  {
    throw std::runtime_error("GAME - Failed to open audio: " + std::string(Mix_GetError()));
  }

  int allocateChannelsResult = Mix_AllocateChannels(32);
  if (allocateChannelsResult != 32)
  {
    throw std::runtime_error("GAME - Failed to allocate mixing channels: " + std::string(Mix_GetError()));
  }

  Log::info("GAME - SDL and its dependencies initialized successfully.");
}

Game::Game(const std::string &title, int width, int height)
{
  Log::info("GAME - Initializing game: " + title + " (" + std::to_string(width) + "x" + std::to_string(height) + ")");
  if (instance != nullptr)
  {
    throw std::runtime_error("Game instance already exists!");
  } else {
    instance = this;
  }
  
  init_sdl_libs();
  window = init_window(title, width, height);
  renderer = init_renderer(window);

  // Temporary State Initializing for now:
  Log::debug("GAME - Starting temporary state.");
  state = new State();
  
  Log::debug("GAME - Starting background game object");
  GameObject* bgGameObject = new GameObject();
  bgGameObject->AddComponent(new SpriteRenderer(*bgGameObject, "assets/img/Background.png"));
  state->AddObject(bgGameObject);
  Log::debug("GAME - Background game object loaded");

  Log::debug("GAME - Starting TileMap game object");
  GameObject *tileMapGameObject = new GameObject();
  TileSet *tileSet = new TileSet(64, 64, "assets/img/Tileset.png");
  TileMap *tileMap = new TileMap(*tileMapGameObject, "assets/map/map.txt", tileSet);
  tileMapGameObject->AddComponent(tileMap);
  state->AddObject(tileMapGameObject);
  Log::debug("GAME - TileMap game object loaded");

  Log::debug("GAME - Starting zombie game object");
  GameObject *zombieGameObject = new GameObject();
  Zombie *zombie = new Zombie(*zombieGameObject);
  zombieGameObject->AddComponent(zombie);
  state->AddObject(zombieGameObject);
  Log::debug("GAME - Zombie game object loaded");
}

Game::~Game()
{
  Log::info("GAME - Cleaning up game resources");

  instance = nullptr;
  delete state;
  state = nullptr;
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  Log::info("GAME - Game resources cleaned up successfully.");
}

Game& Game::GetInstance(const std::string &title, int width, int height)
{
  Log::info("Creating game instance");
  if (instance == nullptr) {
    instance = new Game(title, width, height);
  }

  return *instance;
}

State& Game::GetState()
{
  return *state;
}

SDL_Renderer *Game::GetRenderer()
{
  return renderer;
}

void Game::Run()
{
  Log::info("GAME - Starting game loop");
  State& state = GetState();
  
  while (!state.QuitRequested())
  {
    state.Update(0);
    state.Render();
    SDL_RenderPresent(renderer);
    SDL_Delay(33); // Force ~30 FPS
  }

  Log::info("GAME - Exiting game loop");
  Game::~Game();
}
