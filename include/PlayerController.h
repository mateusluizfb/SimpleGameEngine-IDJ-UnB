#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Component.h"

class PlayerController : public Component {
public:
  PlayerController(GameObject &associated);
  
  void Start();

  void Update(float dt);
  void Render();
};

#endif
