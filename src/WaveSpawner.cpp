#include "Log.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "WaveSpawner.h"
#include "GameObject.h"
#include "Zombie.h"
#include "State.h"
#include "Game.h"
#include "Wave.h"
#include "Camera.h"

float RandomFloat(float lower, float upper)
{
  return lower + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (upper - lower);
}

WaveSpawner::WaveSpawner(GameObject &associated)
  : Component(associated),
    zombieCounter(0),
    waves(),
    zombieCooldownTimer(),
    currentWave(0)
{
  int wavesCount = 1;

  for (int i = 0; i < wavesCount; i++) {
    Wave wave;
    wave.zombies = 2;
    wave.cooldown = 5.0f;
    waves.push_back(wave);
  }
}

void WaveSpawner::Update(float dt) {
  zombieCooldownTimer.Update(dt);

  Log::info("WAVE_SPAWNER - Time elapsed: " + std::to_string(zombieCooldownTimer.Get()));

  if (zombieCounter < waves[currentWave].zombies) {
    if (zombieCooldownTimer.Get() >= waves[currentWave].cooldown) {
      zombieCounter++;
      zombieCooldownTimer.Restart();

      Game &game = Game::GetInstance();
      State &currentState = game.GetState();
      Camera &camera = Camera::GetInstance();

      float distance = 500;
      Vec2 cameraCenter = camera.GetCenterPosition();
      Vec2 lowerBound = Vec2(cameraCenter.x - distance, cameraCenter.y - distance);
      Vec2 upperBound = Vec2(cameraCenter.x + distance, cameraCenter.y + distance);
      Vec2 zombieSpawnPos = Vec2(
        RandomFloat(lowerBound.x, upperBound.x),
        RandomFloat(lowerBound.y, upperBound.y)
      );

      Log::debug("WAVE_SPAWNER - Starting zombie game object");
      GameObject *zombieGameObject1 = new GameObject();
      Zombie *zombie1 = new Zombie(*zombieGameObject1);
      zombieGameObject1->AddComponent(zombie1);
      currentState.AddObject(zombieGameObject1);
      SpriteRenderer *spriteRenderer1 = zombieGameObject1->GetComponent<SpriteRenderer>();
      spriteRenderer1->SetPosition(zombieSpawnPos.x, zombieSpawnPos.y);
      Log::debug("WAVE_SPAWNER - Zombie game object loaded at: " + std::to_string(zombieSpawnPos.x) + "x" + std::to_string(zombieSpawnPos.y));
    }
  } else {
    Log::debug("WAVE_SPAWNER - Next wave!");

    if (currentWave + 1 < static_cast<int>(waves.size())) {
      currentWave++;
      zombieCounter = 0;
      zombieCooldownTimer.Restart();
    }
  }
}

void WaveSpawner::Render() {}
