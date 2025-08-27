#include "State.h"
#include "Sprite.h"
#include "SDL.h"
#include "Log.h"

State::State() : bg("assets/img/Background.png") // CORRECT WAY: constructed in place and owns its texture for its entire lifetime, with no temporary or copy involved
{
  quitRequested = false;
  // bg = Sprite("assets/img/Background.png"); THIS IS WRONG: double free on bg.texture, it's temporarily created and destroyed in the ~Sprite()
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
    Log::debug("Quit requested via SDL event");
    quitRequested = true;
  }
}

void State::Render()
{
  bg.Render(0, 0);
}
