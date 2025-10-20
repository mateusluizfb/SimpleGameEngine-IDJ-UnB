#include <gtest/gtest.h>
#include "Game.h"
#include "GameObject.h"
#include "State.h"
#include "StageState.h"
#include "Log.h"

TEST(StateTest, Start)
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

TEST(StateTest, GetObjectPtr)
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
