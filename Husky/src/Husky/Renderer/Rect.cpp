#include "Rect.h"

husky::Rect::Rect(int x, int y, int w, int h)
{
	rec.x = x; rec.y = y; rec.w = w; rec.h = h;
}

husky::Rect::Rect(const SDL_Rect& rect)
	: rec(rect) 
{
}

husky::Rect husky::Rect::Intersect(const Rect& rhs) const
{
	SDL_Rect result;
	if (SDL_IntersectRect(&rec, &rhs.rec, &result))
	{
		return Rect(result);
	}
	else
	{
		return Rect(0, 0, 0, 0);
	}
}

bool husky::Rect::IsEmpty()
{
	return !(rec.w && rec.h);
}
