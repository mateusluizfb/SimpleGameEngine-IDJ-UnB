#include <gtest/gtest.h>
#include "Bullet.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Game.h"
#include "Log.h"

TEST(BulletTest, BulletUpdateMovesAndDeletesAfterMaxDistance)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- GunTest Logs ----");

  GameObject *go = new GameObject();
  Bullet *bullet = new Bullet(*go, 0.0f, 100.0f, 10, 150.0f); // angle 0 (right), speed 100, max distance 150
  go->AddComponent(bullet);

  // Initial position
  float initialX = go->box.x;
  float initialY = go->box.y;

  // Update with dt = 1 second
  bullet->Update(1.0f);

  // After 1 second, it should have moved right by speed * dt = 100 * 1 = 100
  EXPECT_FLOAT_EQ(go->box.x, initialX + 100.0f);
  EXPECT_FLOAT_EQ(go->box.y, initialY);

  // Update with dt = 0.5 seconds (total distance now should be 150)
  bullet->Update(0.5f);

  // After another 0.5 seconds, it should have moved right by another speed * dt = 100 * 0.5 = 50
  EXPECT_FLOAT_EQ(go->box.x, initialX + 150.0f);
  EXPECT_FLOAT_EQ(go->box.y, initialY);

  // Update with dt = 1 second (this should exceed max distance and request deletion)
  bullet->Update(1.0f);

  // Now the bullet should request deletion since it has reached max distance
  EXPECT_TRUE(go->IsDead());

  delete go;
  delete game;
}
