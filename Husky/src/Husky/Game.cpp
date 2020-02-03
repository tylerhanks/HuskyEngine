#include "Game.h"

#include <iostream>
#include <SDL.h>

husky::Game::Game()
{
}

husky::Game::~Game()
{
}

void husky::Game::Run()
{
	std::cout << "Hello from Husky Engine!" << std::endl;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}

	std::cin.get();
}
