#include "Game.h"

#include <iostream>
#include <SDL.h>
#include <chrono>

husky::Game::Game()
	:
	m_running(false),
	m_window(NULL)
{
}

husky::Game::~Game()
{
}

void husky::Game::Run()
{
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
	m_window = SDL_CreateWindow("HuskyEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	if (m_window == NULL)
	{
		HS_CORE_ERROR(std::cout, "Failed to create window");
		return false;
	}
	else
		return true;
}

bool husky::Game::OnUpdate(float delta_time)
{
	//handle events
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		else
		{
			for (auto it = m_layer_stack.rbegin(); it != m_layer_stack.rend(); it++)
			{
				if ((*it)->OnEvent(e))
					continue;
				else
					break;
			}
		}
	}

	//update layers
	for (auto it = m_layer_stack.begin(); it != m_layer_stack.end(); it++)
	{
		if ((*it)->OnUpdate(delta_time) == false)
		{
			m_tbd_layers.push_back(*it);
		}
	}

	for (auto tbd_layer : m_tbd_layers)
	{
		m_layer_stack.PopLayer(tbd_layer);
	}

	return m_layer_stack.size();
}

bool husky::Game::OnCreate()
{
	return false;
}

void husky::Game::OnDestroy()
{
}

void husky::Game::PushLayer(Layer* layer)
{
	m_layer_stack.PushLayer(layer);
}
