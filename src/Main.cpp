#include "Game.h"

int main(int argc, char **argv)
{
  Game &game = Game::GetInstance("My Game", 1200, 900);  

  return 0;
}
