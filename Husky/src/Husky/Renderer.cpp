#include "Renderer.h"
#include "Log.h"

#include <iostream>

SDL_Renderer* husky::Renderer::m_renderer = NULL;
std::string husky::Renderer::m_asset_path = "";

void husky::Renderer::Init(SDL_Window* window)
{
	m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (m_renderer == NULL)
	{
		HS_CORE_ERROR(std::cout, "Failed to initialize renderer");
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
		HS_CORE_ERROR(std::cout, "Failed to get base path");
		return;
	}

	size_t pos = m_asset_path.rfind("bin");
	m_asset_path = m_asset_path.substr(0, pos) + path + PATH_SEP;

	HS_CORE_LOG(std::cout, "Initialized asset path to " + m_asset_path);
}

void husky::Renderer::Clear()
{
	SDL_RenderClear(m_renderer);
}

void husky::Renderer::Present()
{
	SDL_RenderPresent(m_renderer);
}

husky::Texture* husky::Renderer::LoadTextureFromBMP(const std::string& bmp_file_name, const std::string& sub_dir)
{
	std::string full_path = m_asset_path + sub_dir + PATH_SEP + bmp_file_name;

	SDL_Texture* tex = nullptr;
	SDL_Surface* surf = SDL_LoadBMP(full_path.c_str());

	if (surf)
	{
		tex = SDL_CreateTextureFromSurface(m_renderer, surf);
		SDL_FreeSurface(surf);

		if (tex == nullptr)
		{
			HS_CORE_ERROR(std::cout, "Failed to create texture");
			return new Texture();
		}
	}
	else
	{
		HS_CORE_ERROR(std::cout, "Failed to load BMP");
		return new Texture();
	}

	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	return new Texture(tex, w, h);
}

void husky::Renderer::DrawTexture(Texture* tex, int x_pos, int y_pos, int scale)
{
	SDL_Rect dst;
	dst.x = x_pos;
	dst.y = y_pos;
	dst.w = tex->m_width * scale;
	dst.h = tex->m_height * scale;

	SDL_RenderCopy(m_renderer, tex->m_tex, NULL, &dst);
}

void husky::Renderer::Shutdown()
{
	SDL_DestroyRenderer(m_renderer);
}

husky::Texture::Texture()
	:
	m_tex(nullptr),
	m_width(0),
	m_height(0)
{
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
