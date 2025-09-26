#include "Character.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Gun.h"
#include "Game.h"
#include "Log.h"

Character::Command::Command(CommandType type, float x, float y)
  : type(type), pos(x, y) {}

Character::Character(GameObject &associated, std::string sprite)
  : Component(associated),
    // player(nullptr),
    // gun(),
    taskQueue(),
    speed(Vec2(0, 0)),
    linearSpeed(1),
    hp(100),
    deathTimer(Timer())
{
  SpriteRenderer *spriteRenderer = new SpriteRenderer(associated, sprite, 3, 2);
  Animator *animator = new Animator(associated);

  associated.AddComponent(spriteRenderer);
  associated.AddComponent(animator);

  animator->AddAnimation("idle", Animation(6, 9, 0.5));
  animator->AddAnimation("walking", Animation(0, 5, 0));
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

  Gun* gunComponent = new Gun(*gunGO, currentState.GetObjectPtr(&this->associated));
  gunGO->AddComponent(gunComponent);

  std::weak_ptr<GameObject> gunPtr = currentState.AddObject(gunGO);
  gun = gunPtr;
}

void Character::Update(float dt) {
  Animator* animator = associated.GetComponent<Animator>();

  if (animator->GetCurrent() == "dead" && deathTimer.Get() > 1)
  {
    Log::debug("CHARACTER - Character removal after death animation.");
    associated.RequestDelete();
    return;
  }

  if (hp <= 0)
  {
    Log::debug("CHARACTER - Character is dead.");
    animator->SetAnimation("dead");
    deathTimer.Update(dt);
    return;
  }

  while (!taskQueue.empty()) {
      Command item = taskQueue.front();
      
      switch (item.type)
      {
        case CommandType::MOVE:
        {
          Log::debug("CHARACTER - Character moving");
          
          animator->SetAnimation("walking");

          // TODO test without normalize
          speed = item.pos.Normalize() * linearSpeed;

          // TODO: SpriteRenderer has a SetPosition that could be used here:
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

        default: {
          speed = Vec2(0, 0);
          animator->SetAnimation("idle");
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
