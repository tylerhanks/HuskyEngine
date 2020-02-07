#include "Window.h"
#include "Log.h"
#include <iostream>

husky::Window::Window(const std::string& name, int width, int height, bool fullscreen)
	:
	m_name(name),
	m_width(width),
	m_height(height),
	m_fullscreen(fullscreen),
	m_window(NULL)
{
	init();
}

husky::Window::~Window()
{
	SDL_DestroyWindow(m_window);
}

std::string husky::Window::GetName() const
{
	return m_name;
}

int husky::Window::GetWidth() const
{
	return m_width;
}

int husky::Window::GetHeight() const
{
	return m_height;
}

bool husky::Window::IsFullscreen() const
{
	return m_fullscreen;
}

void husky::Window::init()
{
	if (m_fullscreen)
	{
		m_window = SDL_CreateWindow(m_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
		if (m_window == NULL)
		{
			logSDLError(std::cout, "Failed to create window");
		}
	}
	else
	{
		m_window = SDL_CreateWindow(m_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN);
		if (m_window == NULL)
		{
			logSDLError(std::cout, "Failed to create window");
		}
	}
}
