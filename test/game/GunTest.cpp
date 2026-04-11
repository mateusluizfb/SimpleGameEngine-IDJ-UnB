#include <gtest/gtest.h>
#include "Log.h"
#include "Game.h"
#include "Character.h"
#include "Gun.h"
#include "Bullet.h"
#include "StageState.h"

TEST(GunTest, GunCharacterWeakPtrExpiredAfterDelete)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);
  game->StateStackPush(new StageState());

  Log::debug(" --- GunTest Logs ----");

  GameObject *go = new GameObject();
  auto characterPtr = std::make_shared<GameObject>();
  auto characterComponent = new Character(*characterPtr, "game/assets/img/Player.png");
  characterPtr->AddComponent(characterComponent);

  auto gunPtr = std::make_shared<GameObject>();
  auto gunComponent = new Gun(*gunPtr, characterPtr);
  gunPtr->AddComponent(gunComponent);

  characterPtr.reset();

  EXPECT_TRUE(gunComponent->GetCharacter().expired());

  EXPECT_NO_THROW(gunComponent->Update(0));

  delete go;
  delete game;
}

TEST(GunTest, GunShootCreatesBullet)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);
  game->StateStackPush(new StageState());
  State &state = game->GetCurrentState();

  auto characterPtr = std::make_shared<GameObject>();
  auto characterComponent = new Character(*characterPtr, "game/assets/img/Player.png");
  characterPtr->AddComponent(characterComponent);

  auto gunPtr = std::make_shared<GameObject>();
  auto gunComponent = new Gun(*gunPtr, characterPtr);
  gunPtr->AddComponent(gunComponent);

  // Initial object count
  size_t initialCount = state.GetObjectArray().size();

  // Call Shoot
  Vec2 target(500, 500);
  gunComponent->Shoot(target);

  // After shooting, there should be three more objects (the bullets)
  auto objectArray = state.GetObjectArray();
  EXPECT_EQ(objectArray.size(), initialCount + 3);

  // The last object should be a Bullet
  auto lastObj = objectArray.back();
  auto bullet = lastObj->GetComponent<Bullet>();
  EXPECT_NE(bullet, nullptr);

  delete game;
}

