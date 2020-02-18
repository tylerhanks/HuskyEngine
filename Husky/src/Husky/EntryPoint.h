#pragma once
#include "Log.h"
#include <iostream>
#include <SDL_ttf.h>
#include <Windows.h>

extern husky::Game* husky::CreateGame();

int main(int argc, char** argv)
{
	HS_CORE_LOG("Initializing Husky Engine..");

	if ((SDL_Init(SDL_INIT_EVERYTHING) || TTF_Init()) != 0)
	{
		HS_CORE_ERROR("Failed to initialize");
		return -1;
	}

	auto game = husky::CreateGame();

	if (game != nullptr)
	{
		game->Run();

		delete game;

		SDL_Quit();

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);

		return 0;
	}
	else
	{
		HS_CORE_ERROR("Failed to create game");

		SDL_Quit();

		return -1;
	}
}
