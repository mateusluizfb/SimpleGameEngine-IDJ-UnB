#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include "Component.h"
#include "Timer.h"
#include "Vec2.h"

class AIController : public Component {
private:
    enum AIState { MOVING, RESTING };
    AIState state;
    int npcCounter;
    Timer restTimer;
    Vec2 destination;

public:
  AIController(GameObject &associated);

  void Update(float dt) override;
  void Render() override;
};

#endif
