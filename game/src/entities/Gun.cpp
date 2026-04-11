#include "Gun.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Log.h"
#include "Character.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Game.h"
#include "State.h"

static void CreateBullet(
  GameObject &associated,
  State &currentState,
  Vec2 position,
  Vec2 projectileDirection,
  float rotation
) {
  Vec2 shootDirection = projectileDirection.Rotate(rotation);
  float shootAngle = std::atan2(shootDirection.y, shootDirection.x);

  GameObject *bulletGO = new GameObject();
  // TODO: Handle the case where the last param would be true (targeting player)
  Bullet *bullet = new Bullet(*bulletGO, shootAngle, 500, BULLET_DAMAGE, 400, true);
  bulletGO->AddComponent(bullet);
  bulletGO->box.SetCenter(associated.box.GetCenter() + shootDirection * 30);
  currentState.AddObject(bulletGO);
  bulletGO->angleDeg = associated.angleDeg + 90; // Rotate bullet in the direction it's shooting
}

Gun::Gun(GameObject &associated, std::weak_ptr<GameObject> character)
  : Component(associated),
    shootSound("game/audio/Range.wav"),
    reloadSound("game/audio/PumpAction.mp3"),
    cooldownState(0),
    cdTimer(Timer()),
    character(character),
    angle(0)
{
  SpriteRenderer *spriteRenderer = new SpriteRenderer(associated, "game/assets/img/Gun.png", 3, 2);
  Animator *animator = new Animator(associated);

  associated.AddComponent(spriteRenderer);
  associated.AddComponent(animator);

  animator->AddAnimation("idle", Animation(0, 0, 0));
  animator->AddAnimation("reloading", Animation(1, 5, 0.2));
}

void Gun::Shoot(Vec2 target) {
  Log::info("GUN - Shooting at target: (" + std::to_string(target.x) + ", " + std::to_string(target.y) + ")");

  shootSound.Play();
  cooldownState = 1;

  std::shared_ptr<GameObject> characterPtr = character.lock();

  Vec2 characterCenter = characterPtr->box.GetCenter();

  Vec2 projectileDirection = (target - characterCenter).Normalize();
  Game &game = Game::GetInstance();
  State &currentState = game.GetCurrentState();

  CreateBullet(associated, currentState, characterCenter, projectileDirection, 0.0);
  CreateBullet(associated, currentState, characterCenter, projectileDirection, 0.3);
  CreateBullet(associated, currentState, characterCenter, projectileDirection, -0.3);

  angle = std::atan2(projectileDirection.y, projectileDirection.x);;
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
  Character *characterComp = characterPtr->GetComponent<Character>();

  Vec2 characterCenter = characterPtr->box.GetCenter();

  Vec2 offset = Vec2(90, 0); // Default offset

  if (characterComp->player != nullptr) {
    // Always point gun toward mouse position
    int mouseWorldX = InputManager::GetInstance().GetMouseXWorld();
    int mouseWorldY = InputManager::GetInstance().GetMouseYWorld();
    angle = std::atan2(mouseWorldY - characterCenter.y, mouseWorldX - characterCenter.x);
  }

  offset = offset.Rotate(angle);
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
        cooldownState = 2;
        cdTimer.Restart();
        break;
    case 2:
        cooldownState = 3;
        reloadSound.Play();
        animator->SetAnimation("reloading");
        break;
    case 3:
        if (cdTimer.Get() > 1.2) {
          animator->SetAnimation("idle");
          cooldownState = 0;
        }
        break;
  }
}

void Gun::Render() {
}
