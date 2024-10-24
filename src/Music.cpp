#include "Music.h"
#include <iostream>

Music::Music()
{
  this->music = nullptr;
}

Music::Music(std::string file)
{
  this->music = nullptr;
  this->Open(file);
}

void Music::Play(int times)
{
  if (this->IsOpen())
  {
    Mix_PlayMusic(this->music, times);
  }
}

void Music::Stop(int msToStop)
{
  Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file)
{
  this->music = Mix_LoadMUS(file.c_str());
  if (!this->IsOpen())
  {
    std::cout << "Mix_LoadMUS: " << Mix_GetError() << std::endl;
    exit(1);
  };
}

bool Music::IsOpen()
{
  return this->music != nullptr;
}

Music::~Music()
{
  this->Stop(0);
  Mix_FreeMusic(this->music);
}