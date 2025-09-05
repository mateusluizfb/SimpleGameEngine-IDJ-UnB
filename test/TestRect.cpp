#include <gtest/gtest.h>
#include "Vec2.h"
#include "Rect.h"

TEST(RectTest, AddVect)
{
  Rect *rect = new Rect(1, 1, 1, 1);
  Vec2 *vec = new Vec2(1, 1);

  Rect newRect = *rect + *vec;

  EXPECT_EQ(newRect.x, 2);
  EXPECT_EQ(newRect.y, 2);

  delete vec;
  delete rect;
}

TEST(RectTest, SubtractVect)
{
  Rect *rect = new Rect(1, 1, 1, 1);
  Vec2 *vec = new Vec2(1, 1);

  Rect newRect = *rect - *vec;

  EXPECT_EQ(newRect.x, 0);
  EXPECT_EQ(newRect.y, 0);

  delete vec;
  delete rect;
}

TEST(RectTest, GetCenter)
{
  Rect *rect = new Rect(1, 1, 1, 1);

  Vec2 centerVec = rect->GetCenter();

  EXPECT_EQ(centerVec.x, 2);
  EXPECT_EQ(centerVec.y, 2);

  delete rect;
}
