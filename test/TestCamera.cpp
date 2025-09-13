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
