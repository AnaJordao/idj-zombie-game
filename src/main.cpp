#include "Game.h"

int main(int argc, char **argv)
{
  Game &gameRef = Game::GetInstance();
  gameRef.Run();
  return 0;
}