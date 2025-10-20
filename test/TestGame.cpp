#include <gtest/gtest.h>
#include <thread>
#include "Log.h"
#include "Game.h"
#include "State.h"
#include "StageState.h"

TEST(TestGame, CalculateDeltaTime)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);
  StageState *stageState = new StageState();
  game->Push(stageState);

  Log::debug(" --- TestGame Logs ----");

  std::thread quitThread(
      [stageState]()
      {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        stageState->RequestQuit();
      });

  game->Run();

  EXPECT_NE(game->GetDeltaTime(), 0);

  if (quitThread.joinable()) quitThread.join();
}
