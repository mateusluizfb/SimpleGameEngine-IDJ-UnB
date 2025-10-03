#include <gtest/gtest.h>
#include "Log.h"
#include "Game.h"
#include "Character.h"
#include "Gun.h"

TEST(GunTest, GunCharacterWeakPtrExpiredAfterDelete)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- GunTest Logs ----");

  GameObject *go = new GameObject();
  auto characterPtr = std::make_shared<GameObject>();
  auto characterComponent = new Character(*characterPtr, "assets/img/Player.png");
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
