#include "Gun.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Log.h"
#include "Character.h"

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
  Log::debug("GUN - Shooting at target (" + std::to_string(target.x) + ", " + std::to_string(target.y) + ")");
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

  Vec2 offset = Vec2(30, 0);
  Vec2 newCenter = characterPtr->box.GetCenter() + offset;
  associated.box.SetCenter(newCenter.Rotate(angle));
}

void Gun::Render() {
}
