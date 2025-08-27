#include "State.h"
#include "Sprite.h"
#include "SDL.h"
#include "Log.h"

State::State()
{
  quitRequested = false;
  bg = Sprite("assets/img/Background.png");
}

bool State::QuitRequested()
{
  return quitRequested;
}

void State::LoadAssets()
{
  // Load game assets here
}

void State::Update(float dt)
{
  if (SDL_QuitRequested() == SDL_TRUE)
  {
    Log::info("Quit requested via SDL event");
    quitRequested = true;
  }
}

void State::Render()
{
  bg.Render(0, 0);
}
