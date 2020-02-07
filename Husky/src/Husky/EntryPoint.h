#pragma once
#include "Log.h"
#include <iostream>

extern husky::Game* husky::CreateGame();

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		HS_CORE_ERROR(std::cout, "Failed to initialize");
		return -1;
	}

	auto game = husky::CreateGame();

	game->Run();

	delete game;

	return 0;
}
