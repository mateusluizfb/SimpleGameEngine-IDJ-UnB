#include "Log.h"
#include "Zombie.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"

Zombie::Zombie(GameObject &associated) : Component(associated), hitPoints(100), deathSound("audio/Dead.wav") {
  SpriteRenderer *spriteRenderer = new SpriteRenderer(associated, "assets/img/Enemy.png", 3, 2);
  Animator *animator = new Animator(associated);
  
  associated.AddComponent(spriteRenderer);
  associated.AddComponent(animator);

  spriteRenderer->SetPosition(600, 450);

  animator->AddAnimation("walk", Animation(0, 3, 10));
  animator->AddAnimation("dead", Animation(5, 5, 0));

  animator->SetAnimation("walk");
}

void Zombie::Damage(int damage) {
  if (hitPoints == 0) return;

  hitPoints -= damage;

  if (hitPoints == 0) {
    Animator *animator = associated.GetComponent<Animator>();

    if (animator == nullptr)
    {
      throw std::runtime_error("Zombie::Damage(): No Animator component found in associated GameObject.");
    }

    animator->SetAnimation("dead");
    deathSound.Play(1);
  }
}

int Zombie::GetHitPoints() {
  return hitPoints;
}

void Zombie::Update(float dt) {
  this->Damage(1);
}

void Zombie::Render() {
}
