#include "Log.h"
#include "Zombie.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "InputManager.h"
#include "Camera.h"

Zombie::Zombie(GameObject &associated)
  : Component(associated),
    hit(false),
    hitPoints(100),
    deathSound("audio/Dead.wav"),
    hitSound("audio/Hit0.wav")
{
  SpriteRenderer *spriteRenderer = new SpriteRenderer(associated, "assets/img/Enemy.png", 3, 2);
  Animator *animator = new Animator(associated);

  associated.AddComponent(spriteRenderer);
  associated.AddComponent(animator);

  animator->AddAnimation("walk", Animation(0, 3, 0.5));
  animator->AddAnimation("dead", Animation(5, 5, 0));
  animator->AddAnimation("hit", Animation(4, 4, 0));

  animator->SetAnimation("walk");
}

void Zombie::Damage(int damage) {
  if (hitPoints == 0) return;
  
  Animator *animator = associated.GetComponent<Animator>();
  hitPoints -= damage;

  if (hitPoints == 0) {

    if (animator == nullptr)
    {
      throw std::runtime_error("Zombie::Damage(): No Animator component found in associated GameObject.");
    }

    animator->SetAnimation("dead");
    deathSound.Play(1);
  } else {
    hit = true;
    animator->SetAnimation("hit");
  }
}

int Zombie::GetHitPoints() {
  return hitPoints;
}

void Zombie::Update(float dt) {
  InputManager &inputManager = InputManager::GetInstance();

  Animator *animator = associated.GetComponent<Animator>();
  Timer *hitTimer = &animator->hitTimer;
  Timer *deathTimer = &animator->deathTimer;

  // Hit Update
  if (hit && hitPoints != 0 && hitTimer->Get() >= 0.5)
  {
    animator->SetAnimation("walk");
    hit = false;
    hitTimer->Restart();
  }
  
  if (hit)
  {
    hitTimer->Update(dt);
  }

  // Death Update
  if (hitPoints == 0) {
    deathTimer->Update(dt);
  }

  if (deathTimer->Get() >= 5)
  {
    Log::debug("ZOMBIE - Deleting game object");
    this->associated.RequestDelete();
  }

  // Buttons Update
  if (inputManager.MousePress(LEFT_MOUSE_BUTTON))
  {
    Log::debug("ZOMBIE - Left mouse button click received");

    Vec2 mousePosition = Vec2(inputManager.GetMouseXWorld(), inputManager.GetMouseYWorld());
    Rect zombieBox = associated.box;

    if (zombieBox.IsVec2Inside(mousePosition))
    {
      Log::debug("ZOMBIE - Zombie clicked!");
      hitSound.Play(1);
      this->Damage(10);
    }
  }
}

void Zombie::Render() {
}
