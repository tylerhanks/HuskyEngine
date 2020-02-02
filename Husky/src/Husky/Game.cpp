#include "Game.h"

#include <iostream>

husky::Game::Game()
{
}

husky::Game::~Game()
{
}

void husky::Game::Run()
{
	std::cout << "Hello from Husky Engine!" << std::endl;
	std::cin.get();
}
