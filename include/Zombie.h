#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"
#include "Sound.h"

#define ZOMBIE_DAMAGE 10

class Zombie : public Component {
private:
  bool hit;
  int hitPoints;
  Sound deathSound;
  Sound hitSound;
  int damage = ZOMBIE_DAMAGE;

public:
  Zombie(GameObject &associated);

  void Damage(int damage);
  int GetHitPoints();

  void Update(float dt) override;
  void Render() override;
  void NotifyCollision(GameObject &other) override;
  int GetDamage();
};

#endif
