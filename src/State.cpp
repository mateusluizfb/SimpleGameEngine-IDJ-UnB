#include "State.h"
#include "Log.h"

State::State() : zombie(*(new GameObject())) , music("audio/BGM.wav")
{
  Log::info("STATE - Initializing state");

  quitRequested = false;
  music.Play();
}

State::~State()
{
  Log::info("STATE - Destroying state");

  objectArray.clear();
}

void State::AddObject(GameObject *go)
{
  objectArray.emplace_back(std::unique_ptr<GameObject>(go));
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
    Log::debug("STATE - Quit requested via SDL event");
    music.Stop();
    quitRequested = true;
  }

  for (size_t i = 0; i < objectArray.size(); i++)
  {
    objectArray[i]->Update(0);
  }

  for (size_t i = 0; i < objectArray.size(); i++)
  {
    if (objectArray[i]->IsDead()) {
      objectArray.erase(objectArray.begin() + i);
    }
  }

  // TODO: Remove, for testing purposes only:
  zombie.Update(0);
}

void State::Render()
{ 
  for (size_t i = 0; i < objectArray.size(); i++)
  {
    objectArray[i]->Render();
  }

  // TODO: Remove, for testing purposes only:
  zombie.Render();
}
