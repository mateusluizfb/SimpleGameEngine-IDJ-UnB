#ifndef VEC2_H
#define VEC2_H

class Vec2
{
public:
  float x, y;

  Vec2();
  Vec2(float x, float y);

  Vec2 operator+(const Vec2 &other) const;
  Vec2 operator-(const Vec2 &other) const;
  Vec2 operator*(float scalar) const;
  Vec2 operator/(float scalar) const;

  float Magnitude() const;
  Vec2 Normalize() const;
  float Distance(const Vec2 &other) const;
  float Angle(const Vec2 &other) const;
  float AngleDeg(const Vec2 &other) const;
  Vec2 Rotate(float angle) const;
};

#endif
