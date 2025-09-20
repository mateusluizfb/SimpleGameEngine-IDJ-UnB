#include "Vec2.h"
#include <cmath>

Vec2::Vec2() : x(0.0), y(0.0) {}

Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2 &other) const
{
  return Vec2(this->x + other.x, this->y + other.y);
}

Vec2 Vec2::operator-(const Vec2 &other) const
{
  return Vec2(this->x - other.x, this->y - other.y);
}

Vec2 Vec2::operator*(float scalar) const
{
  return Vec2(this->x * scalar, this->y * scalar);
}

Vec2 Vec2::operator/(float scalar) const
{
  return Vec2(this->x / scalar, this->y / scalar);
}

// Reminder note: Is the Vector norm
float Vec2::Magnitude() const
{
  return std::sqrt(this->x * this->x + this->y * this->y);
}

// Reminder note: Normalized vector is when the norm is 1 (aka length of 1)
Vec2 Vec2::Normalize() const
{
  float norm = Magnitude();

  return Vec2((this->x / norm), (this->y / norm));
}

float Vec2::Distance(const Vec2 &other) const
{
  float x = this->x - other.x;
  float y = this->y - other.y;

  return std::sqrt(x * x + y * y);
}

float Vec2::Angle(const Vec2 &other) const
{
  float dx = this->x - other.x;
  float dy = this->y - other.y;

  return std::atan2(dy, dx);
}

Vec2 Vec2::Rotate(float angle) const
{
  float x = (this->x * std::cos(angle)) - (this->y * std::sin(angle));
  float y = (this->y * std::cos(angle)) + (this->x * std::sin(angle));

  return Vec2(x, y);
}
