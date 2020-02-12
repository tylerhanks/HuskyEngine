#pragma once
#include <SDL.h>

namespace husky {

	struct Rect
	{
	public:
		Rect() = default;
		Rect(int x, int y, int w, int h);

		Rect Intersect(const Rect& rhs) const;

		bool IsEmpty();

	private:
		Rect(const SDL_Rect& rect);
		SDL_Rect rec;
	};

}
