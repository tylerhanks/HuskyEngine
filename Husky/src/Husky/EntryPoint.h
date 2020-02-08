#pragma once
#include "Log.h"
#include <iostream>

extern husky::Game* husky::CreateGame();

int main(int argc, char** argv)
{
	HS_CORE_LOG(std::cout, "Initializing Husky Engine..");

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		HS_CORE_ERROR(std::cout, "Failed to initialize");
		return -1;
	}

	auto game = husky::CreateGame();

	if (game != nullptr)
	{
		game->Run();

		delete game;

		SDL_Quit();

		return 0;
	}
	else
	{
		HS_CORE_ERROR(std::cout, "Failed to create game");

		SDL_Quit();

		return -1;
	}
}
