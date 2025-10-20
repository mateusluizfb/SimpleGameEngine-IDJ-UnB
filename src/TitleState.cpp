#include "TitleState.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Log.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "Camera.h"

TitleState::TitleState() : State() {
  Log::info("TITLE_STATE - Initializing TitleState");

  GameObject *titleGameObject = new GameObject();
  titleGameObject->AddComponent(new SpriteRenderer(*titleGameObject, "assets/img/Title.png"));
  this->AddObject(titleGameObject);
}

TitleState::~TitleState() {
  Log::info("TITLE_STATE - Destroying TitleState");

  objectArray.clear();
}

void TitleState::LoadAssets() {
  Log::info("TITLE_STATE - Loading assets for TitleState");
}

void TitleState::Update(float dt) {
  InputManager &inputManager = InputManager::GetInstance();

  if (inputManager.QuitRequested()) {
    Log::warning("TITLE_STATE - Quit requested via SDL event");
    this->RequestQuit();
  }

  if (inputManager.KeyPress(SPACE_KEY))
  {
    Log::info("TITLE_STATE - Enter key pressed, popping TitleState");
    Game::GetInstance().Push(new StageState());
  }

  UpdateArray(dt);
}

void TitleState::Render()
{
  Log::info("TITLE_STATE - Rendering TitleState");

  RenderArray();
}

void TitleState::Resume() {
  Camera::GetInstance().SetPosition(0, 0);
}

void TitleState::Pause() {}
void TitleState::Start() {}
