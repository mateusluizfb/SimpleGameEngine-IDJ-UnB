#include <gtest/gtest.h>
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
