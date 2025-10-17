#include <cmath>
#include "Log.h"
#include "GameObject.h"
#include "Bullet.h"
#include "SpriteRenderer.h"
#include "Collider.h"
#include "Character.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, bool targetsPlayer)
  : Component(associated),
  targetsPlayer(false),
  speed(Vec2(speed * std::cos(angle), speed * std::sin(angle))),
  distanceLeft(maxDistance),
  damage(damage)
{
  SpriteRenderer *spriteRenderer = new SpriteRenderer(associated, "assets/img/Bullet.png", 1, 1);
  Collider *collider = new Collider(associated, Vec2(1, 1), Vec2(0, 0));

  associated.AddComponent(spriteRenderer);
  associated.AddComponent(collider);
}

void Bullet::Update(float dt) {
  if (distanceLeft <= 0) {
    associated.RequestDelete();
    return;
  }

  Vec2 displacement = speed * dt;
  associated.box.x += displacement.x;
  associated.box.y += displacement.y;

  distanceLeft -= displacement.Magnitude();
}

void Bullet::Render() {
}

int Bullet::GetDamage() {
  return damage;
}
