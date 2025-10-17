#ifndef WAVE_SPAWNER_H
#define WAVE_SPAWNER_H

#include <vector>
#include "Component.h"
#include "Wave.h"
#include "Timer.h"

class WaveSpawner : public Component {
private:
  int zombieCounter;
  std::vector<Wave> waves;
  Timer zombieCooldownTimer;
  Timer npcsCooldownTimer;
  int currentWave;

public:
  WaveSpawner(GameObject &associated);

  void Update(float dt) override;
  void Render() override;
};

#endif
