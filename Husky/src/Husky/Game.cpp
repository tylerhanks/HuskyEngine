#include <chrono>
#include <iostream>
#include <SDL.h>

#include "Game.h"
#include "Renderer.h"

husky::Game::Game()
	:
	m_running(false),
	m_window(NULL)
{
}

husky::Game::~Game()
{
	SDL_DestroyWindow(m_window);
	Renderer::Shutdown();
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

		m_running = Update(delta_time.count());
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
	{
		Renderer::Init(m_window);
		return true;
	}
}

void husky::Game::SetAssetPath(const std::string& project_dir, const std::string& asset_dir)
{
	Renderer::SetAssetPath(project_dir + '\\' + asset_dir);
}

bool husky::Game::Update(float delta_time)
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

	//delete layers that are finished
	for (auto tbd_layer : m_tbd_layers)
	{
		m_layer_stack.PopLayer(tbd_layer);
	}

	//render layers
	Renderer::Clear();

	for (auto it = m_layer_stack.begin(); it != m_layer_stack.end(); it++)
	{
		(*it)->OnRender();
	}

	Renderer::Present();

	//if no more layers, game is over
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
