#include "Game.h"

#include <iostream>
#include <SDL.h>
#include <chrono>

husky::Game::Game()
	:
	m_running(false)
{
}

husky::Game::~Game()
{
}

void husky::Game::Run()
{
	std::cout << "Hello from Husky Engine!" << std::endl;
	m_running = OnCreate();

	auto t1 = std::chrono::system_clock::now();
	auto t2 = std::chrono::system_clock::now();

	while (m_running)
	{
		t2 = std::chrono::system_clock::now();
		std::chrono::duration<float> delta_time = t2 - t1;
		t1 = t2;

		m_running = OnUpdate(delta_time.count());
	}

	OnDestroy();
}

bool husky::Game::Construct(int width, int height, bool full_screen)
{
	return false;
}

bool husky::Game::OnCreate()
{
	return false;
}

bool husky::Game::OnUpdate(float delta_time)
{
	return false;
}

void husky::Game::OnDestroy()
{
}
