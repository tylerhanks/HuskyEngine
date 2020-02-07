#pragma once
#include <SDL.h>
#include <string>

namespace husky {

	class Window
	{
	public:
		Window(const std::string& name, int width, int height, bool fullscreen);
		~Window();

		std::string GetName() const;
		int GetWidth() const;
		int GetHeight() const;
		bool IsFullscreen() const;

	private:
		void init();
		std::string m_name;
		int m_width;
		int m_height;
		bool m_fullscreen;
		SDL_Window* m_window;
	};

}
