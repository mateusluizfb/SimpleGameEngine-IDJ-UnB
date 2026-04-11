
#include <cmath>
#include <gtest/gtest.h>
#include "Vec2.h"

TEST(Vec2Test, AddVector)
{
  Vec2* vec1 = new Vec2(1, 1);
  Vec2* vec2 = new Vec2(1, 1);

  Vec2 vecResult = *vec1 + *vec2;

  EXPECT_EQ(vecResult.x, 2);
  EXPECT_EQ(vecResult.y, 2);

  delete vec2;
  delete vec1;
}

TEST(Vec2Test, SubtractVector)
{
  Vec2 *vec1 = new Vec2(1, 1);
  Vec2 *vec2 = new Vec2(1, 1);

  Vec2 vecResult = *vec1 - *vec2;

  EXPECT_EQ(vecResult.x, 0);
  EXPECT_EQ(vecResult.y, 0);

  delete vec2;
  delete vec1;
}

TEST(Vec2Test, MultiplyScalar)
{
  Vec2 *vec1 = new Vec2(1, 1);

  Vec2 vecResult = *vec1 * 2.0;

  EXPECT_EQ(vecResult.x, 2);
  EXPECT_EQ(vecResult.y, 2);

  delete vec1;
}

TEST(Vec2Test, DivideScalar)
{
  Vec2 *vec1 = new Vec2(2, 2);

  Vec2 vecResult = *vec1 / 2.0;

  EXPECT_EQ(vecResult.x, 1.0);
  EXPECT_EQ(vecResult.y, 1.0);

  delete vec1;
}

TEST(Vec2Test, Magnitude)
{
  Vec2 *vec1 = new Vec2(2, 2);

  float result = vec1->Magnitude();

  EXPECT_NEAR(result, 2.82842708, 1e-5);

  delete vec1;
}

TEST(Vec2Test, Normalize)
{
  Vec2 *vec1 = new Vec2(2, 2);

  Vec2 normalizedVec = vec1->Normalize();

  float x = normalizedVec.x;
  float y = normalizedVec.y;

  float result = std::sqrt(x * x + y * y);

  EXPECT_NEAR(result, 1.0, 1e-5);

  delete vec1;
}

TEST(Vec2Test, Distance)
{
  Vec2 *vec1 = new Vec2(1, 5);
  Vec2 *vec2 = new Vec2(3, 2);

  float result = vec1->Distance(*vec2);

  EXPECT_NEAR(result, 3.60555124, 1e-5);

  delete vec2;
  delete vec1;
}

TEST(Vec2Test, Angle)
{
  Vec2 *vec1 = new Vec2(1, 3);
  Vec2 *vec2 = new Vec2(5, 7);

  float result = vec1->Angle(*vec2);

  EXPECT_NEAR(result, -2.3561945, 1e-5);

  delete vec2;
  delete vec1;
}

TEST(Vec2Test, AngleDeg)
{
  Vec2 *vec1 = new Vec2(1, 3);
  Vec2 *vec2 = new Vec2(5, 7);

  float result = vec1->AngleDeg(*vec2);

  EXPECT_NEAR(result, -135.0, 1e-5);

  delete vec2;
  delete vec1;
}

TEST(Vec2Test, Rotate)
{
  Vec2 *vec1 = new Vec2(1, 1);

  Vec2 rotadedVec = vec1->Rotate(1.57079632679); // 90 degrees

  EXPECT_NEAR(rotadedVec.x, -1.0, 1e-5);
  EXPECT_NEAR(rotadedVec.y, 1.0, 1e-5);

  delete vec1;
}
