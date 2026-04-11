#include <gtest/gtest.h>
#include "Log.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"

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

TEST(TestInputManager, KeyPressRelease)
{
  InputManager& im = InputManager::GetInstance();

  int testKey = SDLK_LEFT;

  im.Update();

  EXPECT_FALSE(im.KeyPress(testKey));
  EXPECT_FALSE(im.KeyRelease(testKey));
  EXPECT_FALSE(im.IsKeyDown(testKey));

  EXPECT_NO_THROW(im.KeyPress(testKey));
  EXPECT_NO_THROW(im.KeyRelease(testKey));
  EXPECT_NO_THROW(im.IsKeyDown(testKey));
}

TEST(TestInputManager, KeyGetMouseWorld)
{
  Camera &camera = Camera::GetInstance();
  InputManager &im = InputManager::GetInstance();

  camera.SetPosition(0, 0);

  int mouseXWorld = im.GetMouseXWorld();
  int mouseYWorld = im.GetMouseYWorld();

  EXPECT_EQ(mouseXWorld, im.GetMouseX());
  EXPECT_EQ(mouseYWorld, im.GetMouseY());
}
