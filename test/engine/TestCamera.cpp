#include <gtest/gtest.h>
#include <Log.h>
#include <Game.h>
#include <Camera.h>

TEST(TestCamera, SingletonInstance) {
  Camera& camera = Camera::GetInstance();

  EXPECT_EQ(&camera, &Camera::GetInstance());
}

TEST(TestCamera, Update) {
  Camera& camera = Camera::GetInstance();
  GameObject obj;

  EXPECT_NO_THROW(camera.Follow(&obj));
  EXPECT_NO_THROW(camera.Unfollow());
}

TEST(TestCamera, PositionAndSpeed) {
  Camera& camera = Camera::GetInstance();

  camera.SetPosition(100, 100);
  EXPECT_FLOAT_EQ(100.0f, camera.GetPositionX());
  EXPECT_FLOAT_EQ(100.0f, camera.GetPositionY());

  camera.SetSpeedMultiplier(0.5f);

  EXPECT_FLOAT_EQ(50.0f, camera.GetPositionX());
  EXPECT_FLOAT_EQ(50.0f, camera.GetPositionY());

  camera.ResetSpeedMultiplier();
  EXPECT_FLOAT_EQ(100.0f, camera.GetPositionX());
  EXPECT_FLOAT_EQ(100.0f, camera.GetPositionY());
}

TEST(TestCamera, Following) {
  Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- TestCamera Logs ----");

  Camera& camera = Camera::GetInstance();
  GameObject obj;

  obj.box.x = 300;
  obj.box.y = 400;

  camera.Follow(&obj);
  EXPECT_NO_THROW(camera.Update(0.16f));

  EXPECT_FLOAT_EQ(300 - (Game::GetInstance().GetWindowWidth() / 2), camera.GetPositionX());
  EXPECT_FLOAT_EQ(400 - (Game::GetInstance().GetWindowHeight() / 2), camera.GetPositionY());

  camera.Unfollow();
  EXPECT_NO_THROW(camera.Update(0.16f));

  delete game;
}
