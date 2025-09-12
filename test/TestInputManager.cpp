#include <gtest/gtest.h>
#include "Log.h"
#include "Game.h"
#include "InputManager.h"

TEST(TestInputManager, Instance)
{
  InputManager& im1 = InputManager::GetInstance();
  InputManager& im2 = InputManager::GetInstance();
  EXPECT_EQ(&im1, &im2);
}

TEST(TestInputManager, Update)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- TestInputManager Logs ----");

  InputManager& im = InputManager::GetInstance();

  EXPECT_NO_THROW(im.Update());

  delete game;
}
