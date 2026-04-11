#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
public:
  bool targetsPlayer;

  Bullet(
    GameObject &associated,
    float angle,
    float speed,
    int damage,
    float maxDistance,
    bool targetsPlayer
  );

  void Update(float dt);
  void Render();
  int GetDamage();
  void RequestDelete();

private:
  Vec2 speed;
  float distanceLeft;
  int damage;
};

#endif
