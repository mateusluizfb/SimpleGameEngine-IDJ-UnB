#ifndef WAVE_SPAWNER_H
#define WAVE_SPAWNER_H

#include <vector>
#include "Component.h"
#include "Wave.h"
#include "Timer.h"

#define DEFAULT_DISTANCE 1000.0f

#define WAVES_COUNT 2
#define WAVE_ZOMBIES_COUNT 2
#define ZOMBIE_SPAWN_COOLDOWN 5.0f
#define NPC_SPAWN_COOLDOWN 10.0f

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
