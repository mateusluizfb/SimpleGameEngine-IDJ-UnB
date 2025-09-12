#include <gtest/gtest.h>
#include <thread>
#include "Log.h"
#include "Game.h"
#include "State.h"

TEST(TestGame, CalculateDeltaTime)
{
  Game *game = &Game::GetInstance("Test Game", 800, 600);
  State *state = &game->GetState();

  Log::debug(" --- TestGame Logs ----");

  std::thread quitThread(
      [state]()
      {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        state->RequestQuit();
      });

  game->Run();

  EXPECT_NE(game->GetDeltaTime(), 0);

  if (quitThread.joinable()) quitThread.join();
}
