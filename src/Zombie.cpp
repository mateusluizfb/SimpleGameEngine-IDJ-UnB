#include "Zombie.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Log.h"

Zombie::Zombie(GameObject &associated) : Component(associated), hitPoints(100) {
  SpriteRenderer *spriteRenderer = new SpriteRenderer(associated, "assets/img/Enemy.png", 3, 2);
  associated.AddComponent(spriteRenderer);
  spriteRenderer->SetPosition(600, 450);
  spriteRenderer->SetFrame(0);

  Log::debug("ZOMBIE - Zombie created with 100 HP");
}

void Zombie::Damage(int damage) {
  if (damage == 0) return;

  hitPoints -= damage;

  if (hitPoints <= 0) {
    SpriteRenderer *spriteRenderer = associated.GetComponent<SpriteRenderer>();
    spriteRenderer->SetFrame(5);
  }
}

void Zombie::Update(float dt) {
  this->Damage(1);
}

void Zombie::Render() {
  SpriteRenderer *spriteRenderer = associated.GetComponent<SpriteRenderer>();
  spriteRenderer->Render();
}
