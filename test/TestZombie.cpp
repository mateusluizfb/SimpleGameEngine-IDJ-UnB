#include <gtest/gtest.h>
#include "Game.h"
#include "Zombie.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Log.h"

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
