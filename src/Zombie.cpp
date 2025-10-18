#include "Log.h"
#include "Zombie.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collider.h"
#include "Bullet.h"
#include "Game.h"
#include "State.h"

Zombie::Zombie(GameObject &associated)
  : Component(associated),
    hit(false),
    hitPoints(100),
    deathSound("audio/Dead.wav"),
    hitSound("audio/Hit0.wav")
{
  SpriteRenderer *spriteRenderer = new SpriteRenderer(associated, "assets/img/Enemy.png", 3, 2);
  Animator *animator = new Animator(associated);
  Collider *collider = new Collider(associated, Vec2(1, 1), Vec2(1, 1));

  associated.AddComponent(spriteRenderer);
  associated.AddComponent(animator);
  associated.AddComponent(collider);

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
    animator->SetAnimation("hit");
  }
}

int Zombie::GetHitPoints()
{
  return hitPoints;
}

int Zombie::GetDamage()
{
  return damage;
}

void Zombie::Update(float dt) {
  Animator *animator = associated.GetComponent<Animator>();
  Timer *hitTimer = &animator->hitTimer;
  Timer *deathTimer = &animator->deathTimer;

  State &state = Game::GetInstance().GetState();

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

  if (hitPoints == 0) {
    deathTimer->Update(dt);
    return;
  }

  if (deathTimer->Get() >= 5)
  {
    Log::debug("ZOMBIE - Deleting game object");
    this->associated.RequestDelete();
  }

  std::weak_ptr<GameObject> player = state.GetPlayerPtr();

  if (player.expired()) { return; }

  Vec2 playerPos = player.lock()->box.GetCenter();
  Vec2 zombiePos = associated.box.GetCenter();
  float angleToPlayer = zombiePos.Angle(playerPos);
  Vec2 speed = Vec2(
    50 * std::cos(angleToPlayer),
    50 * std::sin(angleToPlayer)
  );
  Vec2 displacement = speed * dt;
  associated.box.x -= displacement.x;
  associated.box.y -= displacement.y;

  if (displacement.x > 0)
    associated.GetComponent<SpriteRenderer>()->SetFlip(SDL_FLIP_HORIZONTAL);
  else
    associated.GetComponent<SpriteRenderer>()->SetFlip(SDL_FLIP_NONE);
}

void Zombie::Render() {
}

void Zombie::NotifyCollision(GameObject &other) {
  Bullet *bullet = other.GetComponent<Bullet>();
  
  if (bullet == nullptr) return;
  if (hit) return;

  Animator *animator = associated.GetComponent<Animator>();
  Timer *hitTimer = &animator->hitTimer;

  this->Damage(bullet->GetDamage());
  hitSound.Play(1);
  hitTimer->Restart();
  bullet->RequestDelete();

  hit = true;
}

