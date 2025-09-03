#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"

class Zombie : public Component {
private:
  int hitPoints;

public:
  Zombie(GameObject &associated);

  void Damage(int damage);
  int GetHitPoints();

  void Update(float dt) override;
  void Render() override;
};

#endif
