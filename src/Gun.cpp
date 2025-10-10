#include "Gun.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Log.h"
#include "Character.h"
#include "InputManager.h"

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
  shootSound.Play();

  Vec2 direction = (target - associated.box.GetCenter()).Normalize();
  angle = std::atan2(direction.y, direction.x);

  cooldownState = 1;
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

  // The angle rotates well, but the sprite is rendered on top of the 
  // character's. so when it goes to the right of the character, we need to
  // increase the offset, like an elipsis
  Vec2 offset = Vec2(30, 0).Rotate(angle); 
  Vec2 currentCenter = characterPtr->box.GetCenter();
  Vec2 newCenter = (currentCenter + offset);

  associated.box.SetCenter(newCenter);

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

  InputManager &inputManager = InputManager::GetInstance();

  if (inputManager.MousePress(LEFT_MOUSE_BUTTON))
  {
    Vec2 target = Vec2(inputManager.GetMouseXWorld(), inputManager.GetMouseYWorld());
    this->Shoot(target);
  }
}

void Gun::Render() {
}
