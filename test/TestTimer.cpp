#include <gtest/gtest.h>
#include <thread>
#include "Log.h"
#include "Timer.h"

TEST(TestTimer, UpdateTimer)
{
  Timer *timer = new Timer();

  EXPECT_EQ(timer->Get(), 0);
  
  timer->Update(1);
  
  EXPECT_EQ(timer->Get(), 1);
  
  timer->Restart();
  
  EXPECT_EQ(timer->Get(), 0);

  delete timer;
}
