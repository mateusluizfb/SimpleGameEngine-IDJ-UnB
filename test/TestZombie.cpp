#include <gtest/gtest.h>
#include "Game.h"
#include "Zombie.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Log.h"
#include "Bullet.h"
#include "Character.h"
#include "StageState.h"

TEST(TestZombie, InitZombie)
{
  // Needed so it inits the renderer used by SpriteRenderer's Sprite
  Game *game = &Game::GetInstance("Test Game", 800, 600);
  game->StateStackPush(new StageState());

  Log::debug(" --- TestZombie Logs ----");

  GameObject* obj = new GameObject();
  Zombie *zombie = new Zombie(*obj);

  // Check initial hit points
  EXPECT_EQ(zombie->GetHitPoints(), 100);

  // Check if SpriteRenderer component was added
  SpriteRenderer *spriteRenderer = obj->GetComponent<SpriteRenderer>();
  EXPECT_NE(spriteRenderer, nullptr);

  // Check initial frame
  EXPECT_NO_THROW(spriteRenderer->SetFrame(0));

  delete obj;
  delete game;
}

TEST(TestZombie, DamageZombie)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);
  game->StateStackPush(new StageState());

  Log::debug(" --- TestZombie Logs ----");

  GameObject* obj = new GameObject();
  Zombie *zombie = new Zombie(*obj);

  zombie->Damage(30);
  EXPECT_EQ(zombie->GetHitPoints(), 70);

  zombie->Damage(50);
  EXPECT_EQ(zombie->GetHitPoints(), 20);

  EXPECT_NO_THROW(zombie->Damage(20));
  EXPECT_EQ(zombie->GetHitPoints(), 0);

  zombie->Damage(10);
  EXPECT_EQ(zombie->GetHitPoints(), 0);

  delete obj;
  delete game;
}

TEST(TestZombie, NotifyCollisionWithBullet)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);
  game->StateStackPush(new StageState());

  Log::debug(" --- TestZombie NotifyCollision Logs ----");

  GameObject* zombieObj = new GameObject();
  Zombie *zombie = new Zombie(*zombieObj);

  GameObject* bulletObj = new GameObject();
  // Create a Bullet with damage 42
  Bullet* bullet = new Bullet(*bulletObj, 0, 0, 42, 100, false);
  bulletObj->AddComponent(bullet);

  int initialHp = zombie->GetHitPoints();
  EXPECT_EQ(initialHp, 100);

  // Notify collision with bullet
  zombie->NotifyCollision(*bulletObj);

  // Should take damage
  EXPECT_EQ(zombie->GetHitPoints(), 58); // 100 - 42

  // Should not take damage again if already hit (hit flag)
  zombie->NotifyCollision(*bulletObj);
  EXPECT_EQ(zombie->GetHitPoints(), 58);

  delete bulletObj;
  delete zombieObj;
  delete game;
}

TEST(TestZombie, ZombieMovesTowardsPlayer)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);
  game->StateStackPush(new StageState());

  Log::debug(" --- TestZombie Movement Logs ----");

  Game::GetInstance().GetCurrentState().Start();
  std::weak_ptr<GameObject> playerPtr = Game::GetInstance().GetCurrentState().GetObjectByTag("player");
  ASSERT_FALSE(playerPtr.expired());
  GameObject* playerObj = playerPtr.lock().get();

  GameObject* zombieObj = new GameObject();
  zombieObj->box.x = 100;
  zombieObj->box.y = 100;
  zombieObj->box.w = 50;
  zombieObj->box.h = 50;
  Zombie *zombie = new Zombie(*zombieObj);

  float initialX = zombieObj->box.x;
  float initialY = zombieObj->box.y;

  // Run update for 1 second
  zombie->Update(1.0f);

  // After update, zombie should be closer to player
  float newX = zombieObj->box.x;
  float newY = zombieObj->box.y;

  float initialDist = std::hypot(initialX - playerObj->box.x, initialY - playerObj->box.y);
  float newDist = std::hypot(newX - playerObj->box.x, newY - playerObj->box.y);

  EXPECT_LT(newDist, initialDist);

  delete zombieObj;
  delete game;
}



