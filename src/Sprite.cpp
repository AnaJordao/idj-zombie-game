#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Sprite.h"
#include "Game.h"
#include <iostream>

Sprite::Sprite()
{
  this->texture = nullptr;
}

Sprite::Sprite(std::string file)
{
  this->texture = nullptr;
  this->Open(file);
}

Sprite::~Sprite()
{
  SDL_DestroyTexture(this->texture);
}

void Sprite::Open(std::string file)
{
  if (this->IsOpen())
  {
    SDL_DestroyTexture(this->texture);
  }
  this->texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
  if (!this->IsOpen())
  {
    std::cout << "IMG_LoadTexture: " << IMG_GetError() << std::endl;
    exit(1);
  }

  SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
  this->SetClip(0, 0, this->width, this->height);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
  this->clipRect = {x, y, w, h};
}

void Sprite::Render(int x, int y)
{
  SDL_Rect dstRect = {x, y, this->clipRect.w, this->clipRect.h};
  SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, &this->clipRect, &dstRect);
}

int Sprite::GetWidth()
{
  return this->width;
}

int Sprite::GetHeight()
{
  return this->height;
}

bool Sprite::IsOpen()
{
  return this->texture != nullptr;
}