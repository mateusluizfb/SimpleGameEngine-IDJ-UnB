#ifndef WAVE_SPAWNER_H
#define WAVE_SPAWNER_H

#include <vector>
#include "Component.h"
#include "Wave.h"
#include "Timer.h"

#define DEFAULT_DISTANCE 1000.0f

#ifdef DEBUG

#endif

#ifdef DEBUG
  #undef WAVES_COUNT
  #define WAVES_COUNT 1

  #undef WAVE_ZOMBIES_COUNT
  #define WAVE_ZOMBIES_COUNT 1

  #undef ZOMBIE_SPAWN_COOLDOWN
  #define ZOMBIE_SPAWN_COOLDOWN 1.0f

  #undef WAVE_NPCS_COUNT
  #define WAVE_NPCS_COUNT 1

  #undef NPC_SPAWN_COOLDOWN
  #define NPC_SPAWN_COOLDOWN 1.0f
#else
  #define WAVES_COUNT 2
  #define WAVE_ZOMBIES_COUNT 2
  #define WAVE_NPCS_COUNT 1
  #define ZOMBIE_SPAWN_COOLDOWN 5.0f
  #define NPC_SPAWN_COOLDOWN 10.0f
#endif

class WaveSpawner : public Component {
private:
  int zombieCounter;
  int npcCounter;
  std::vector<Wave> waves;
  Timer zombieCooldownTimer;
  Timer npcsCooldownTimer;
  int currentWave;

public:
  WaveSpawner(GameObject &associated);

  bool AllWavesCompleted();

  void Update(float dt) override;
  void Render() override;
};

#endif
