#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
public:
  Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance);

  void Update(float dt);
  void Render();
  int GetDamage();

private:
  Vec2 speed;
  float distanceLeft;
  int damage;
};

#endif
