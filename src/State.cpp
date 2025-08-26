#include "State.h"

State::State()
{
  quitRequested = false;
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
  // Update game state based on delta time
}

void State::Render()
{
  // Render the current state
}
