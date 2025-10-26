#include <gtest/gtest.h>
#include "Game.h"
#include "GameObject.h"
#include "State.h"
#include "StageState.h"
#include "Log.h"
#include "WaveSpawner.h"
#include "Zombie.h"
#include "Character.h"
#include "GameData.h"

class MockWaveSpawner : public WaveSpawner {
public:
  MockWaveSpawner(GameObject& go, bool allWavesCompleted = true)
    : WaveSpawner(go), allWavesCompleted_(allWavesCompleted) {}
  bool AllWavesCompleted() { return allWavesCompleted_; }
  void SetAllWavesCompleted(bool value) { allWavesCompleted_ = value; }
private:
  bool allWavesCompleted_;
};

class MockZombie : public Zombie {
public:
  MockZombie(GameObject& go) : Zombie(go) {}
  int GetHitPoints() { return 1; }
};

class MockCharacter : public Character {
public:
  MockCharacter(GameObject& go) : Character(go, "") { player = nullptr; }
};

TEST(StageStateTest, Start)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- AddObjectAndComponent Logs ----");

  State *state = new StageState();
  game->StateStackPush(new StageState());
  std::vector<std::shared_ptr<GameObject>> objectArray = state->GetObjectArray();

  EXPECT_EQ(objectArray.size(), 0);

  state->Start();

  objectArray = state->GetObjectArray();

  EXPECT_NE(objectArray.size(), 0);

  delete state;
  delete game;
}

TEST(StageStateTest, GetObjectPtr)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- AddObjectAndComponent Logs ----");

  State *state = new StageState();
  game->StateStackPush(new StageState());
  std::vector<std::shared_ptr<GameObject>> objectArray = state->GetObjectArray();

  state->Start();
  objectArray = state->GetObjectArray();
  GameObject *gameObject = objectArray[0].get();

  std::weak_ptr<GameObject> foundGo = state->GetObjectPtr(gameObject);

  EXPECT_EQ(foundGo.lock().get(), gameObject);

  delete state;
  delete game;
}

TEST(StageStateTest, WavesNotEnded)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);

  State *state = new StageState();
  
  game->StateStackPush(state);

  GameData::playerVictory = false;

  state->Update(0.016f);

  EXPECT_FALSE(GameData::playerVictory);

  delete game;
}

TEST(StageStateTest, WavesEndedAndEnemiesDead) {
  // TODO
}

TEST(StageStateTest, PlayerDeath) {
  // TODO
}
