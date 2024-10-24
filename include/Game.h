#pragma once
#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"
#include <string>

class Game
{
public:
  static Game &GetInstance();
  Game();
  ~Game();
  SDL_Renderer *GetRenderer();
  State &GetState();
  void Run();

private:
  Game(std::string title, int width, int height);
  static Game *instance;
  SDL_Window *window;
  SDL_Renderer *renderer;
  State *state;
};