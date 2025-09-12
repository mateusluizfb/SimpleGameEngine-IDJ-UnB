#include "Timer.h"


Timer::Timer() : time(0) {}

void Timer::Update(float dt) {
  this->time = this->time + dt;
}

void Timer::Restart() {
  this->time = 0;
}

float Timer::Get() {
  return this->time;
}
