#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"

State::State()
{
  this->quitRequested = false;
  this->bg = new Sprite();
  this->music = new Music();
  this->LoadAssets();
  music->Play();
}

void State::LoadAssets()
{
  this->bg->Open("assets/img/Background.png");
  this->music->Open("assets/audio/BGM.wav");
}

void State::Update(float dt)
{
  if (SDL_QuitRequested())
  {
    this->quitRequested = true;
  };
}

void State::Render()
{
  this->bg->Render(0, 0);
}

bool State::QuitRequested()
{
  return this->quitRequested;
}