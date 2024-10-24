#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include <string>
#include <iostream>
#include "Game.h"
#include "State.h"

Game *Game::instance = nullptr;

Game &Game::GetInstance()
{
    // instance é static e por isso já tem um espaço de memória alocado desde sempre
    if (Game::instance == nullptr)
    {
        new Game("Ana Clara Jordão Perna - 190084006", 1200, 700);
    }
    return *Game::instance;
}

Game::Game(std::string title, int width, int height)
{

    if (instance != nullptr)
    {
        std::cout << "Game instance already exists" << std::endl;
        exit(1);
    }

    this->instance = this;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        std::cout << "SDL_Init: " << SDL_GetError() << std::endl;
        exit(1);
    };

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        std::cout << "IMG_Init: " << SDL_GetError() << std::endl;
        exit(1);
    };

    if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) == 0)
    {
        std::cout << "MIX_Init: " << SDL_GetError() << std::endl;
        exit(1);
    };

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
    {
        std::cout << "MIX_OpenAudio: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_Window *windowInstace = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (windowInstace == nullptr)
    {
        std::cout << "SDL_CreateWindow: " << SDL_GetError() << std::endl;
        exit(1);
    }
    else
    {
        this->window = windowInstace;
    }

    SDL_Renderer *rendererInstance = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if (rendererInstance == nullptr)
    {
        std::cout << "SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        exit(1);
    }
    else
    {
        this->renderer = rendererInstance;
    }

    this->state = new State();
}

Game::~Game()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

State &Game::GetState()
{
    return *this->state;
}

SDL_Renderer *Game::GetRenderer()
{
    return this->renderer;
}

void Game::Run()
{
    while (!this->state->QuitRequested())
    {
        this->state->Update(0);
        this->state->Render();
        SDL_RenderPresent(this->renderer);
        SDL_Delay(33); // aprox 30 fps
    }
}
