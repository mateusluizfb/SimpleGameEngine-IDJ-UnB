#include "State.h"
#include "Sprite.h"
#include "Log.h"

/*
Notes:

- Can't assign `bg = Sprite("assets/img/Background.png")` inside the constructor. Because once the method ends, the Sprite is deleted and bg points to nothing
  the correct way should be in the initalized list like `bg("assets/img/Background.png")`
*/

State::State()
    : bg("assets/img/Background.png"),
      music("audio/BGM.wav")
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
}

void State::Render()
{ 
  for (size_t i = 0; i < objectArray.size(); i++)
  {
    objectArray[i]->Render();
  }
  
  bg.Render(0, 0);
}
