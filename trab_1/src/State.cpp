#include "State.h"
#include "Sprite.h"
#include "SDL.h"

State::State()
{
  quitRequested = false;
  bg = Sprite("./assets/img/Background.png");
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
  // TODO
}

void State::Render()
{
  bg.Render(0, 0);
}
