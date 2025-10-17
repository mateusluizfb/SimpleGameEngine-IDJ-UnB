#include "Gun.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Log.h"
#include "Character.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Game.h"
#include "State.h"

Gun::Gun(GameObject &associated, std::weak_ptr<GameObject> character)
  : Component(associated),
    shootSound("audio/Range.wav"),
    reloadSound("audio/PumpAction.mp3"),
    cooldownState(0),
    cdTimer(Timer()),
    character(character),
    angle(0)
{
  SpriteRenderer *spriteRenderer = new SpriteRenderer(associated, "assets/img/Gun.png", 3, 2);
  Animator *animator = new Animator(associated);

  associated.AddComponent(spriteRenderer);
  associated.AddComponent(animator);

  animator->AddAnimation("idle", Animation(0, 0, 0));
  animator->AddAnimation("reloading", Animation(1, 5, 0.5));
}

void Gun::Shoot(Vec2 target) {
  Log::info("GUN - Shooting at target: (" + std::to_string(target.x) + ", " + std::to_string(target.y) + ")");

  shootSound.Play();
  cooldownState = 1;

  Vec2 direction = (target - associated.box.GetCenter()).Normalize();
  float shootAngle = std::atan2(direction.y, direction.x);

  Game &game = Game::GetInstance();
  State &currentState = game.GetState();

  GameObject *bulletGO = new GameObject();
  // TODO: Handle the case where the last param would be true (targeting player)
  Bullet *bullet = new Bullet(*bulletGO, shootAngle, 500, 10, 400, false); 
  bulletGO->AddComponent(bullet);
  bulletGO->box.SetCenter(associated.box.GetCenter() + direction * 30);
  currentState.AddObject(bulletGO);
  bulletGO->angleDeg = associated.angleDeg + 90; // Rotate bullet in the direction it's shooting
}

std::weak_ptr<GameObject> Gun::GetCharacter() {
  return character;
}

void Gun::Update(float dt)
{  
  if(character.expired()) {
    Log::warning("GUN - Character expired");
    associated.RequestDelete();
    return;
  }

  std::shared_ptr<GameObject> characterPtr = character.lock();

  // Always point gun toward mouse position
  Vec2 characterCenter = characterPtr->box.GetCenter();
  int mouseWorldX = InputManager::GetInstance().GetMouseXWorld();
  int mouseWorldY = InputManager::GetInstance().GetMouseYWorld();
  angle = std::atan2(mouseWorldY - characterCenter.y, mouseWorldX - characterCenter.x);
  
  Vec2 offset = Vec2(90, 0).Rotate(angle);
  associated.angleDeg = angle * (180.0 / M_PI); // Convert to degrees, it's used to rotate the sprite

  if (associated.angleDeg > 90 || associated.angleDeg < -90)
    associated.GetComponent<SpriteRenderer>()->SetFlip(SDL_FLIP_VERTICAL);
  else
    associated.GetComponent<SpriteRenderer>()->SetFlip(SDL_FLIP_NONE);

  associated.box.SetCenter(characterCenter + offset);

  Animator *animator = associated.GetComponent<Animator>();
  cdTimer.Update(dt);

  switch (cooldownState)
  {
    case 0:
        break;
    case 1:
        if (cdTimer.Get() > 0.5) {
          cooldownState = 2;
          cdTimer.Restart();
        }
        break;
    case 2:
        if (cdTimer.Get() > 0.5) {
          cooldownState = 3;
          cdTimer.Restart();
          reloadSound.Play();
          animator->SetAnimation("reloading");
        }
        break;
    case 3:
        if (cdTimer.Get() > 0.5) {
          animator->SetAnimation("idle");
          cooldownState = 0;
        }
        break;
  }
}

void Gun::Render() {
}
