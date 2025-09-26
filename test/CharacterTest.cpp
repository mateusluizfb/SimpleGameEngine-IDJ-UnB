#include <gtest/gtest.h>
#include "Game.h"
#include "Character.h"
#include "Animator.h"
#include "Log.h"

TEST(CharacterTest, Start)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- CharacterTest Logs ----");

  GameObject go;
  Character character(go, "assets/img/Player.png");

  State& previousState = game->GetState();
  int previousObjectsSize = previousState.GetObjectArray().size();

  EXPECT_NO_THROW(character.Start());

  State& currentState = game->GetState();
  int currentObjectsSize = currentState.GetObjectArray().size();

  EXPECT_EQ(currentObjectsSize, previousObjectsSize + 1);

  delete game;
}

TEST(CharacterTest, Issue) {
  Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- CharacterTest Logs ----");

  GameObject go;
  Character character(go, "assets/img/Player.png");
  Character::Command command(CommandType::MOVE, 0, 0);

  std::queue<Character::Command> taskQueue = character.GetTaskQueue();

  EXPECT_EQ(taskQueue.size(), 0);
  
  EXPECT_NO_THROW(character.Issue(command));
  
  taskQueue = character.GetTaskQueue();
  
  EXPECT_EQ(taskQueue.size(), 1);
  
  delete game;
}

TEST(CharacterTest, UpdateIdle) {
  Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- CharacterTest Logs ----");

  GameObject go;
  Character character(go, "assets/img/Player.png");

  EXPECT_NO_THROW(character.Update(0));

  Animator* animator = go.GetComponent<Animator>();

  ASSERT_TRUE(animator->GetCurrent() == "idle");
  EXPECT_EQ(character.GetSpeed().x, 0);
  EXPECT_EQ(character.GetSpeed().y, 0);

  delete game;
}

TEST(CharacterTest, UpdateShoot)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- CharacterTest Logs ----");

  GameObject go;
  Character character(go, "assets/img/Player.png");
  Character::Command command(CommandType::SHOOT, 0, 0);

  character.Start();
  character.Issue(command);

  EXPECT_NO_THROW(character.Update(0));

  delete game;
}

TEST(CharacterTest, UpdateMove)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);

  Log::debug(" --- CharacterTest Logs ----");

  GameObject* go = new GameObject();
  Character *character = new Character(*go, "assets/img/Player.png");
  go->AddComponent(character);
  Character::Command command(CommandType::MOVE, 1, 1);

  character->Start();
  character->Issue(command);

  EXPECT_NO_THROW(character->Update(1));

  Animator *animator = go->GetComponent<Animator>();

  ASSERT_TRUE(animator->GetCurrent() == "walking");
  EXPECT_NEAR(character->GetSpeed().x, 0.707106769, 1e-5);
  EXPECT_NEAR(character->GetSpeed().y, 0.707106769, 1e-5);
  EXPECT_NEAR(go->box.x, 0.707106769, 1e-5);
  EXPECT_NEAR(go->box.y, 0.707106769, 1e-5);

  delete go;
  delete game;
}
