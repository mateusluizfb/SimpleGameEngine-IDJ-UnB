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
#include "Character.h"
#include "Game.h"
#include "SpriteRenderer.h"
#include "AiController.h"
#include "GameData.h"

static float RandomFloat(float lower, float upper)
{
  return lower + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (upper - lower);
}

static Vec2 GetRandomSpawnPosition(const Vec2& playerPos, float distance) {
  Vec2 lowerBound = Vec2(playerPos.x - distance, playerPos.y - distance);
  Vec2 upperBound = Vec2(playerPos.x + distance, playerPos.y + distance);
  return Vec2(
      RandomFloat(lowerBound.x, upperBound.x),
      RandomFloat(lowerBound.y, upperBound.y));
}

static void SpawnNpc(State& state, const Vec2& npcSpawnPos) {
  Log::debug("WAVE_SPAWNER - NPC enemy character object");
  GameObject *enemyCharacterObject = new GameObject();
  Character *enemyCharacter = new Character(*enemyCharacterObject, "assets/img/NPC.png");
  AIController *aiController = new AIController(*enemyCharacterObject);
  enemyCharacterObject->AddComponent(enemyCharacter);
  enemyCharacterObject->AddComponent(aiController);
  SpriteRenderer *spriteRenderer1 = enemyCharacterObject->GetComponent<SpriteRenderer>();
  spriteRenderer1->SetPosition(npcSpawnPos.x, npcSpawnPos.y);
  state.AddObject(enemyCharacterObject);
  Log::debug("WAVE_SPAWNER - NPC enemy character loaded");
}

static void SpawnZombie(State& state, const Vec2& zombieSpawnPos) {
  Log::debug("WAVE_SPAWNER - Starting zombie game object");
  GameObject *zombieGameObject1 = new GameObject();
  Zombie *zombie1 = new Zombie(*zombieGameObject1);
  zombieGameObject1->AddComponent(zombie1);
  state.AddObject(zombieGameObject1);
  SpriteRenderer *spriteRenderer1 = zombieGameObject1->GetComponent<SpriteRenderer>();
  spriteRenderer1->SetPosition(zombieSpawnPos.x, zombieSpawnPos.y);
  Log::debug("WAVE_SPAWNER - Zombie game object loaded at: " + std::to_string(zombieSpawnPos.x) + "x" + std::to_string(zombieSpawnPos.y));
}

WaveSpawner::WaveSpawner(GameObject &associated)
  : Component(associated),
    zombieCounter(0),
    waves(),
    zombieCooldownTimer(),
    npcsCooldownTimer(),
    currentWave(0)
{
  int wavesCount = WAVES_COUNT;

  for (int i = 0; i < wavesCount; i++) {
    Wave wave;
    wave.zombies = WAVE_ZOMBIES_COUNT;
    wave.npcs = WAVE_NPCS_COUNT;
    wave.cooldown = ZOMBIE_SPAWN_COOLDOWN;
    waves.push_back(wave);
  }
}

bool WaveSpawner::AllWavesCompleted()
{
  Log::debug("WAVE_SPAWNER - Current wave: " + std::to_string(currentWave) + " / " + std::to_string(waves.size()));

  return currentWave == static_cast<int>(waves.size());
}

void WaveSpawner::Update(float dt) {
  State &state = Game::GetInstance().GetCurrentState();
  std::weak_ptr<GameObject> player = state.GetPlayerPtr();

  if (player.expired()) return;

  zombieCooldownTimer.Update(dt);
  npcsCooldownTimer.Update(dt);

  Vec2 playerPos = player.lock()->box.GetCenter();

  if (npcCounter < waves[currentWave].npcs &&
      npcsCooldownTimer.Get() >= NPC_SPAWN_COOLDOWN)
  {
    Vec2 npcSpawnPos = GetRandomSpawnPosition(playerPos, DEFAULT_DISTANCE);
    SpawnNpc(state, npcSpawnPos);

    npcCounter++;
    npcsCooldownTimer.Restart();
  }

  if (zombieCounter < waves[currentWave].zombies &&
      zombieCooldownTimer.Get() >= waves[currentWave].cooldown)
  {
    Vec2 zombieSpawnPos = GetRandomSpawnPosition(playerPos, DEFAULT_DISTANCE);
    SpawnZombie(state, zombieSpawnPos);

    zombieCounter++;
    zombieCooldownTimer.Restart();
  }

  if (zombieCooldownTimer.Get() >= waves[currentWave].cooldown &&
      currentWave < static_cast<int>(waves.size()))
  {
    Log::info("WAVE_SPAWNER - Next wave!");
    currentWave++;
    zombieCounter = 0;
    npcCounter = 0;
    zombieCooldownTimer.Restart();
  }
}

void WaveSpawner::Render() {}
