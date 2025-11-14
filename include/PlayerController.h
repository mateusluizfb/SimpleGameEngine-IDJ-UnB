#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Component.h"

#define X_UPPER_BOUND 1890.0f
#define X_LOWER_BOUND 613.0f
#define Y_UPPER_BOUND 2000.0f
#define Y_LOWER_BOUND 479.0f

class PlayerController : public Component {
public:
  PlayerController(GameObject &associated);
  
  void Start();

  void Update(float dt);
  void Render();
};

#endif
