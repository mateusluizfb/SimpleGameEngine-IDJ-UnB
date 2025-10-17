#include <gtest/gtest.h>
#include <memory>
#include "Game.h"
#include "WaveSpawner.h"
#include "Zombie.h"
#include "GameObject.h"
#include "Camera.h"
#include "Log.h"
#include "State.h"
#include "SpriteRenderer.h"



TEST(TestWaveSpawner, SpawnsZombieAfterCooldown) {
	Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- TestWaveSpawner Logs ----");

  GameObject go;
	WaveSpawner spawner(go);
	float dt = 6.0f; // cooldown is 5.0f in default wave
	spawner.Update(dt);
	SUCCEED();
	delete game;
}


TEST(TestWaveSpawner, SpawnsCorrectZombieCount) {
	Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- TestWaveSpawner Logs ----");

  GameObject go;
	WaveSpawner spawner(go);
	for (int i = 0; i < 10; ++i) {
		spawner.Update(6.0f);
	}
	SUCCEED();
	delete game;
}


TEST(TestWaveSpawner, NextWaveTriggered) {
	Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- TestWaveSpawner Logs ----");

  GameObject go;
	WaveSpawner spawner(go);
	for (int i = 0; i < 5; ++i) {
		spawner.Update(6.0f);
	}
	SUCCEED();
	delete game;
}
