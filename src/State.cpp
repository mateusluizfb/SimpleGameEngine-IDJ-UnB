#include "State.h"
#include "Log.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#include "SpriteRenderer.h"

#include <memory>
#include "Camera.h"

State::State() : music("audio/BGM.wav")
{
  Log::info("STATE - Initializing state");

  Camera::GetInstance().SetPosition(600, 450);
  Camera::GetInstance().SetSpeed(200, 200);

  quitRequested = false;
  music.Play();

  // Init state objects:
  Log::debug("STATE - Starting background game object");
  GameObject *bgGameObject = new GameObject();
  bgGameObject->AddComponent(new SpriteRenderer(*bgGameObject, "assets/img/Background.png"));
  SpriteRenderer *bgSprite = bgGameObject->GetComponent<SpriteRenderer>();
  bgSprite->SetCameraFollower(true);
  this->AddObject(bgGameObject);
  Log::debug("STATE - Background game object loaded");

  Log::debug("STATE - Starting TileMap game object");
  GameObject *tileMapGameObject = new GameObject();
  TileSet *tileSet = new TileSet(64, 64, "assets/img/Tileset.png");
  TileMap *tileMap = new TileMap(*tileMapGameObject, "assets/map/map.txt", tileSet);
  tileMapGameObject->AddComponent(tileMap);
  this->AddObject(tileMapGameObject);
  Log::debug("STATE - TileMap game object loaded");
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
  InputManager& inputManager = InputManager::GetInstance();

  if (inputManager.QuitRequested())
  {
    Log::warning("STATE - Quit requested via SDL event");
    music.Stop();
    this->RequestQuit();
  }

  if (inputManager.KeyPress(SPACE_KEY))
  {
    Log::debug("STATE - Starting zombie game object");
    GameObject *zombieGameObject1 = new GameObject();
    Zombie *zombie1 = new Zombie(*zombieGameObject1);
    zombieGameObject1->AddComponent(zombie1);
    this->AddObject(zombieGameObject1);
    SpriteRenderer *spriteRenderer1 = zombieGameObject1->GetComponent<SpriteRenderer>();
    spriteRenderer1->SetPosition(inputManager.GetMouseXWorld(), inputManager.GetMouseYWorld());
    Log::debug("STATE - Zombie game object loaded");
  }

  for (size_t i = 0; i < objectArray.size(); i++)
  {
    objectArray[i]->Update(dt);
  }

  for (size_t i = 0; i < objectArray.size(); i++)
  {
    if (objectArray[i]->IsDead()) {
      Log::info("STATE - Removing dead game object");
      objectArray.erase(objectArray.begin() + i);
    }
  }

  Camera::GetInstance().Update(dt);
}

void State::Render()
{ 
  for (size_t i = 0; i < objectArray.size(); i++)
  {
    objectArray[i]->Render();
  }
}

void State::RequestQuit() {
  this->quitRequested = true;
}
