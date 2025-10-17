#include <gtest/gtest.h>
#include "Game.h"
#include "Zombie.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Log.h"
#include "Bullet.h"

TEST(ZombieTest, InitZombie)
{
  // Needed so it inits the renderer used by SpriteRenderer's Sprite
  Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- ZombieTest Logs ----");

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

TEST(ZombieTest, DamageZombie)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- ZombieTest Logs ----");

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

TEST(ZombieTest, NotifyCollisionWithBullet)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- ZombieTest NotifyCollision Logs ----");

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

