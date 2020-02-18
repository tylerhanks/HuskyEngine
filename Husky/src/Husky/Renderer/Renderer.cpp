#include "Renderer.h"
#include "Husky/Core/Log.h"

#include <iostream>

SDL_Renderer* husky::Renderer::m_renderer = NULL;
std::string husky::Renderer::m_asset_path = "";

void husky::Renderer::Init(SDL_Window* window)
{
	m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (m_renderer == NULL)
	{
		HS_CORE_ERROR("Failed to initialize renderer");
	}
}

void husky::Renderer::SetAssetPath(const std::string& path)
{
	char* base_path = SDL_GetBasePath();

	if (base_path)
	{
		m_asset_path = base_path;
		SDL_free(base_path);
	}
	else
	{
		HS_CORE_ERROR("Failed to get base path");
		return;
	}

	size_t pos = m_asset_path.rfind("bin");
	m_asset_path = m_asset_path.substr(0, pos) + path + PATH_SEP;

	HS_CORE_LOG("Initialized asset path to " + m_asset_path);
}

void husky::Renderer::Clear()
{
	SDL_RenderClear(m_renderer);
}

void husky::Renderer::Present()
{
	SDL_RenderPresent(m_renderer);
}

husky::ref<husky::Font> husky::Renderer::LoadFontFromTTF(const std::string& font_file_name, int font_size, const std::string& sub_dir)
{
	std::string full_path = m_asset_path + sub_dir + PATH_SEP + font_file_name;

	TTF_Font* font = TTF_OpenFont(full_path.c_str(), font_size);
	if (font == nullptr)
	{
		HS_CORE_ERROR("Failed to open font");
		return nullptr;
	}
	else
	{
		return std::make_shared<Font>(font);
	}
}

husky::ref<husky::Texture> husky::Renderer::RenderTextSolid(const std::string& message, ref<Font> font, const Color& color)
{
	SDL_Surface* surf = TTF_RenderText_Solid(font->m_font, message.c_str(), color.m_color);
	if (surf == nullptr)
	{
		HS_CORE_ERROR("Failed to render text");
		return nullptr;
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(m_renderer, surf);
	if (tex == nullptr)
	{
		HS_CORE_ERROR("Failed to create texture");
		SDL_FreeSurface(surf);
		return nullptr;
	}
	SDL_FreeSurface(surf);
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	return std::make_shared<Texture>(tex, w, h);
}

husky::ref<husky::Texture> husky::Renderer::RenderTextShaded(const std::string& message, ref<Font> font, const Color& fg_color, const Color& bg_color)
{
	SDL_Surface* surf = TTF_RenderText_Shaded(font->m_font, message.c_str(), fg_color.m_color, bg_color.m_color);
	if (surf == nullptr)
	{
		HS_CORE_ERROR("Failed to render text");
		return nullptr;
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(m_renderer, surf);
	if (tex == nullptr)
	{
		HS_CORE_ERROR("Failed to create texture");
		SDL_FreeSurface(surf);
		return nullptr;
	}
	SDL_FreeSurface(surf);
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	return std::make_shared<Texture>(tex, w, h);
}

husky::ref<husky::Texture> husky::Renderer::RenderTextBlended(const std::string& message, ref<Font> font, const Color& color)
{
	SDL_Surface* surf = TTF_RenderText_Blended(font->m_font, message.c_str(), color.m_color);
	if (surf == nullptr)
	{
		HS_CORE_ERROR("Failed to render text");
		return nullptr;
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(m_renderer, surf);
	if (tex == nullptr)
	{
		HS_CORE_ERROR("Failed to create texture");
		SDL_FreeSurface(surf);
		return nullptr;
	}
	SDL_FreeSurface(surf);
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	return std::make_shared<Texture>(tex, w, h);
}

husky::ref<husky::Texture> husky::Renderer::LoadTextureFromBMP(const std::string& bmp_file_name, const std::string& sub_dir, const Color& chroma)
{
	std::string full_path = m_asset_path + sub_dir + PATH_SEP + bmp_file_name;

	SDL_Texture* tex = nullptr;
	SDL_Surface* surf = SDL_LoadBMP(full_path.c_str());

	if (surf)
	{
		SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, chroma.m_color.r, chroma.m_color.g, chroma.m_color.b));
		tex = SDL_CreateTextureFromSurface(m_renderer, surf);
		SDL_FreeSurface(surf);

		if (tex == nullptr)
		{
			HS_CORE_ERROR("Failed to create texture");
			return nullptr;
		}
	}
	else
	{
		HS_CORE_ERROR("Failed to load BMP");
		return nullptr;
	}

	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	return std::make_shared<Texture>(tex, w, h);
}

void husky::Renderer::DrawTexture(ref<Texture> tex, int x_pos, int y_pos, int scale)
{
	SDL_Rect dst;
	dst.x = x_pos;
	dst.y = y_pos;
	dst.w = tex->m_width * scale;
	dst.h = tex->m_height * scale;

	SDL_RenderCopy(m_renderer, tex->m_tex, NULL, &dst);
}

void husky::Renderer::DrawTexture(ref<Texture> tex, const Vec2i& pos, int scale)
{
	SDL_Rect dst;
	dst.x = pos.x;
	dst.y = pos.y;
	dst.w = tex->m_width * scale;
	dst.h = tex->m_height * scale;

	SDL_RenderCopy(m_renderer, tex->m_tex, NULL, &dst);
}

void husky::Renderer::DrawTexture(ref<Texture> tex, const Rect& src_rect, const Vec2i& pos, int scale)
{
	SDL_Rect dst;
	dst.x = pos.x;
	dst.y = pos.y;
	dst.w = tex->m_width * scale;
	dst.h = tex->m_height * scale;

	SDL_RenderCopy(m_renderer, tex->m_tex, &src_rect.rec, &dst);
}

void husky::Renderer::Shutdown()
{
	SDL_DestroyRenderer(m_renderer);
}

husky::Texture::Texture(SDL_Texture* tex, int width, int height)
	:
	m_tex(tex),
	m_width(width),
	m_height(height)
{
}

husky::Texture::~Texture()
{
	SDL_DestroyTexture(m_tex);
}

husky::Color::Color()
{
	m_color.r = 255;
	m_color.g = 255;
	m_color.b = 255;
	m_color.a = 255;
}

husky::Color::Color(int r, int g, int b, int a)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	m_color.a = a;
}

husky::Font::Font(TTF_Font* font)
	:
	m_font(font)
{
}

husky::Font::~Font()
{
	TTF_CloseFont(m_font);
}
