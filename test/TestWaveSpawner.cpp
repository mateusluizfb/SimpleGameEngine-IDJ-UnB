#include <gtest/gtest.h>
#include <memory>
#include "Game.h"
#include "WaveSpawner.h"
#include "Zombie.h"
#include "GameObject.h"
#include "Camera.h"
#include "Character.h"
#include "Log.h"
#include "State.h"
#include "SpriteRenderer.h"

TEST(TestWaveSpawner, NextWaveTriggered) {
	Game *game = &Game::GetInstance("Test Game", 800, 600);
	Log::debug(" --- TestWaveSpawner Logs ----");

	State &state = game->GetState();
	state.Start();

	WaveSpawner *spawner = nullptr;
	for (auto &obj : state.GetObjectArray()) {
		spawner = obj->GetComponent<WaveSpawner>();
		if (spawner) break;
	}
	ASSERT_NE(spawner, nullptr) << "No WaveSpawner found in object array";

	// Initial object count
	size_t initialCount = game->GetState().GetObjectArray().size();

	// Run enough updates to trigger both zombie and npc spawns
	for (int i = 0; i < 5; ++i) {
		spawner->Update(6.0f);
	}

	size_t afterSpawnsCount = game->GetState().GetObjectArray().size();
	EXPECT_GT(afterSpawnsCount, initialCount) << "objectArray should have more objects after spawns";

	// Check if at least one NPC and one Zombie were spawned
	bool foundNPC = false;
	bool foundZombie = false;
	auto objects = game->GetState().GetObjectArray();
	for (auto &obj : objects) {
		if (obj->GetComponent<Character>() && obj->GetComponent<Character>()->player == nullptr) {
			foundNPC = true;
		}
		if (obj->GetComponent<Zombie>()) {
			foundZombie = true;
		}
	}
	EXPECT_TRUE(foundNPC) << "At least one NPC should have been spawned.";
	EXPECT_TRUE(foundZombie) << "At least one Zombie should have been spawned.";

	delete game;
}
