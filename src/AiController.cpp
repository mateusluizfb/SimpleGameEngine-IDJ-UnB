#include <math.h>
#include <memory>
#include "AiController.h"
#include "GameObject.h"
#include "Game.h"
#include "Log.h"
#include "Character.h"

AIController::AIController(GameObject &associated)
  : Component(associated),
    state(MOVING),
    npcCounter(0),
    restTimer(),
    destination(0, 0)
{}

void AIController::Update(float dt) {
  switch (state) {
      case MOVING: {
        State &gameState = Game::GetInstance().GetState();
        std::weak_ptr<GameObject> player = gameState.GetPlayerPtr();
        Character *self = associated.GetComponent<Character>();

        if (player.expired()) return;

        Vec2 playerPos = player.lock()->box.GetCenter();
        Vec2 selfPos = associated.box.GetCenter();
        Vec2 direction = (playerPos - selfPos).Normalize();

        if (selfPos.Distance(playerPos) < DEFAULT_SHOOTING_DISTANCE)
        {
          self->Issue(Character::Command(
            CommandType::SHOOT,
            playerPos.x,
            playerPos.y
          ));

          state = RESTING;
          restTimer.Restart();
        }
        else
        {
          self->Issue(Character::Command(
            CommandType::MOVE,
            direction.x,
            direction.y
          ));
        }
      } break;

      case RESTING: {
        restTimer.Update(dt);
        if (restTimer.Get() >= 2.0f)
        {
          state = MOVING;
        }
      } break;
  }
}

void AIController::Render() {}
