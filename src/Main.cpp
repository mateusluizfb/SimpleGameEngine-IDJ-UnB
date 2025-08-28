#include "Game.h"

int main(int argc, char **argv)
{
  Game &game = Game::GetInstance("Mateus Luiz - 150140801", 1200, 900);  

  game.Run();

  return 0;
}
