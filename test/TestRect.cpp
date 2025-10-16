#include <gtest/gtest.h>
#include "Vec2.h"
#include "Rect.h"

TEST(TestRect, AddVect)
{
  Rect *rect = new Rect(1, 1, 1, 1);
  Vec2 *vec = new Vec2(1, 1);

  Rect newRect = *rect + *vec;

  EXPECT_EQ(newRect.x, 2);
  EXPECT_EQ(newRect.y, 2);

  delete vec;
  delete rect;
}

TEST(TestRect, SubtractVect)
{
  Rect *rect = new Rect(1, 1, 1, 1);
  Vec2 *vec = new Vec2(1, 1);

  Rect newRect = *rect - *vec;

  EXPECT_EQ(newRect.x, 0);
  EXPECT_EQ(newRect.y, 0);

  delete vec;
  delete rect;
}

TEST(TestRect, GetCenter)
{
  Rect *rect = new Rect(1, 1, 2, 2);

  Vec2 centerVec = rect->GetCenter();

  EXPECT_EQ(centerVec.x, 2);
  EXPECT_EQ(centerVec.y, 2);

  delete rect;
}

TEST(TestRect, IsVec2Inside)
{
  Rect *rect = new Rect(1, 1, 2, 2);
  Vec2 *vec1 = new Vec2(2, 2);
  Vec2 *vec2 = new Vec2(4, 4);

  bool isInside = rect->IsVec2Inside(*vec1);

  EXPECT_EQ(isInside, true);
  
  isInside = rect->IsVec2Inside(*vec2);
  
  EXPECT_EQ(isInside, false);

  delete vec2;
  delete vec1;
  delete rect;
}

TEST(TestRect, SetCenter)
{
  Rect rect(1, 2, 3, 4);
  Vec2 newCenter(10, 20);

  rect.SetCenter(newCenter);

  EXPECT_EQ(rect.x, 8.5);
  EXPECT_EQ(rect.y, 18);
  EXPECT_EQ(rect.w, 3);
  EXPECT_EQ(rect.h, 4);

  Vec2 center = rect.GetCenter();
  
  EXPECT_EQ(center.x, 10);
  EXPECT_EQ(center.y, 20);
}
