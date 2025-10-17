#include "Log.h"
#include "Game.h"
#include "Gun.h"
#include "Character.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Collider.h"
#include "Camera.h"
#include "Bullet.h"

Character::Command::Command(CommandType type, float x, float y)
  : type(type), pos(x, y) {}

Character::Character(GameObject &associated, std::string sprite)
  : Component(associated),
    // player(nullptr),
    hitSound("audio/Hit1.wav"),
    deathSound("audio/Dead.wav"),
    hit(false),
    taskQueue(),
    speed(Vec2(0, 0)),
    linearSpeed(100),
    hp(100),
    deathTimer(Timer())
{
  SpriteRenderer *spriteRenderer = new SpriteRenderer(associated, sprite, 3, 4);
  Animator *animator = new Animator(associated);
  Collider *collider = new Collider(associated, Vec2(1, 1), Vec2(1, 1));

  associated.AddComponent(spriteRenderer);
  associated.AddComponent(animator);
  associated.AddComponent(collider);

  animator->AddAnimation("walking", Animation(0, 5, 0.2));
  animator->AddAnimation("idle", Animation(6, 9, 0.5));
  animator->AddAnimation("dead", Animation(10, 11, 0.5));

  animator->SetAnimation("idle");
}

Character::~Character() {
  if (player) {
    player = nullptr;
  }
}

void Character::Start() {
  Log::info("CHARACTER - Starting character component");

  Game& game = Game::GetInstance();
  State& currentState= game.GetState();
  
  GameObject *gunGO = new GameObject();
  gun = currentState.AddObject(gunGO);

  Gun* gunComponent = new Gun(*gunGO, currentState.GetObjectPtr(&this->associated));
  gunGO->AddComponent(gunComponent);
}

void Character::Update(float dt) {
  Animator* animator = associated.GetComponent<Animator>();

  if (hit) {
    Timer* hitTimer = &animator->hitTimer;
    hitTimer->Update(dt);

    Log::debug("CHARACTER - Character is hit, time since last hit: " + std::to_string(hitTimer->Get()));

    if (hitTimer->Get() > 0.2) {
      hit = false;
    }
  }

  if (animator->GetCurrent() == "dead") {
    deathTimer.Update(dt);
  }

  if (animator->GetCurrent() == "dead" && deathTimer.Get() > 1)
  {
    Log::info("CHARACTER - Character removal after death animation.");
    associated.RequestDelete();
    return;
  }

  if (hp <= 0 && animator->GetCurrent() != "dead")
  {
    Log::info("CHARACTER - Character is dead.");
    Camera::GetInstance().Unfollow();
    animator->SetAnimation("dead");
    deathSound.Play(1);
    gun.lock()->RequestDelete();
    return;
  }

  if (taskQueue.empty() && animator->GetCurrent() != "dead")
  {
    speed = Vec2(0, 0);
    animator->SetAnimation("idle");
    return;
  }

  while (!taskQueue.empty()) {
      Command item = taskQueue.front();
      
      switch (item.type)
      {
        case CommandType::MOVE:
        {          
          animator->SetAnimation("walking");

          // TODO test without normalize
          speed = item.pos.Normalize() * linearSpeed;

          SpriteRenderer* spriteRenderer = associated.GetComponent<SpriteRenderer>();

          if (speed.x <= 0) {
            spriteRenderer->SetFlip(SDL_FLIP_HORIZONTAL);
          } else {
            spriteRenderer->SetFlip(SDL_FLIP_NONE);
          }

          associated.box.x += speed.x * dt;
          associated.box.y += speed.y * dt;

          break;
        }

        case CommandType::SHOOT:
        {
          if (gun.expired()) {
            throw std::runtime_error("Character::Update(): Character's gun is null");
          }

          Log::debug("CHARACTER - Character shooting");
          gun.lock()->GetComponent<Gun>()->Shoot(item.pos);
          break;
        }
      }

      taskQueue.pop();
  }
}

void Character::Render() {
}

void Character::Issue(Command command) {
  taskQueue.push(command);
}

std::queue<Character::Command> Character::GetTaskQueue()
{
  return taskQueue;
}

Vec2 Character::GetSpeed()
{
  return speed;
}

int Character::GetHp() {
  return hp;
}

void Character::NotifyCollision(GameObject &other) {
  if (other.IsDead() || this->associated.IsDead()) return;

  Bullet *bullet = other.GetComponent<Bullet>();
  Animator *animator = associated.GetComponent<Animator>();
  Timer *hitTimer = &animator->hitTimer;

  if (bullet != nullptr && bullet->targetsPlayer && hitTimer->Get() > 2.0)
  {
    hp -= bullet->GetDamage();
    Log::info("CHARACTER - Character hit by bullet! HP: " + std::to_string(hp));
    hitSound.Play(1);
    hitTimer->Restart();
    return;
  }

  if (hp <= 0) return;

  if (hitTimer->Get() > 2.0) {
    hp -= 50;
    Log::info("CHARACTER - Character hit! HP: " + std::to_string(hp));
    hitSound.Play(1);
    hitTimer->Restart();
    return;
  }

  hit = true;
}

Vec2 Character::GetCenterPosition() {
  return associated.box.GetCenter();
}
