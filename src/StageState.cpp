#include <memory>
#include <algorithm>

#include "StageState.h"
#include "Log.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#include "SpriteRenderer.h"
#include "Character.h"
#include "PlayerController.h"
#include "Collider.h"
#include "Collision.h"
#include "Camera.h"
#include "WaveSpawner.h"

#ifdef DEBUG
  #define PLAY_MUSIC false
#else
  #define PLAY_MUSIC true
#endif

StageState::StageState(): State(), music("audio/BGM.wav")
{
  Log::info("STATE - Initializing state");

  Camera::GetInstance().SetPosition(600, 450);
  Camera::GetInstance().SetSpeed(200, 200);

  if (PLAY_MUSIC) music.Play();
}

StageState::~StageState()
{
  Log::info("STATE - Destroying state");

  objectArray.clear();
}

void StageState::Start()
{
  Log::info("STATE - Starting state");

  LoadAssets();

  GameObject *waveSpawnerGameObject = new GameObject();
  waveSpawnerGameObject->AddComponent(new WaveSpawner(*waveSpawnerGameObject));
  this->AddObject(waveSpawnerGameObject);

  for (size_t i = 0; i < objectArray.size(); i++) {
    objectArray[i]->Start();
  }
  
  started = true;
}

void StageState::LoadAssets()
{
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

  Log::debug("STATE - Starting Character game object");
  GameObject *characterGameObject = new GameObject();
  Character *character = new Character(*characterGameObject, "assets/img/Player.png");
  character->player = character; // Is it correct to set itself as player?
  PlayerController *playerController = new PlayerController(*characterGameObject);
  characterGameObject->AddComponent(character);
  characterGameObject->AddComponent(playerController);
  this->AddObject(characterGameObject);
  SpriteRenderer *spriteRenderer1 = characterGameObject->GetComponent<SpriteRenderer>();
  spriteRenderer1->SetPosition(1253, 901);
  Log::debug("STATE - Character game object loaded");

  Camera::GetInstance().Follow(this->GetObjectPtr(characterGameObject).lock().get());
}

void StageState::Update(float dt)
{
  InputManager& inputManager = InputManager::GetInstance();

  if (inputManager.QuitRequested())
  {
    Log::warning("STATE - Quit requested via SDL event");
    music.Stop();
    this->RequestQuit();
  }

  if (inputManager.KeyPress(ESCAPE_KEY))
  {
    Log::info("STATE - Escape key pressed, popping state");
    music.Stop();
    this->RequestPop();
  }

  for (size_t i = 0; i < objectArray.size(); i++)
  {
    objectArray[i]->Update(dt);
  }

  std::vector<std::shared_ptr<GameObject>> colliderGameObjects;
  std::copy_if(objectArray.begin(), objectArray.end(), std::back_inserter(colliderGameObjects),
               [](const std::shared_ptr<GameObject>& go) { return go->GetComponent<Collider>() != nullptr; });

  for (size_t i = 0; i < colliderGameObjects.size(); i++)
  {
    Collider* colliderA = colliderGameObjects[i]->GetComponent<Collider>();
    if (colliderA == nullptr) continue;

    for (size_t j = i + 1; j < colliderGameObjects.size(); j++)
    {
      Collider* colliderB = colliderGameObjects[j]->GetComponent<Collider>();
      if (colliderB == nullptr) continue;

      if (Collision::IsColliding(
        colliderA->GetBox(),
        colliderB->GetBox(),
        colliderGameObjects[i]->GetAngleRad(),
        colliderGameObjects[j]->GetAngleRad()
      ))
      {
        colliderGameObjects[i]->NotifyCollision(*colliderGameObjects[j]);
        colliderGameObjects[j]->NotifyCollision(*colliderGameObjects[i]);
      }
    } 
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

void StageState::Render()
{ 
  RenderArray();
}

void StageState::Pause ()
{
  Log::info("STATE - Pausing state");
}

void StageState::Resume ()
{
  Log::info("STATE - Resuming state");
}
