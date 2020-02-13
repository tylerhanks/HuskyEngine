#pragma once
#include <SDL.h>
#include <string>

#include "Vector2D.h"

namespace husky {

	class Renderer;

	struct Texture
	{
	public:
		Texture();
		Texture(SDL_Texture* tex, int width, int height);
		~Texture();

		friend class Renderer;

	private:
		SDL_Texture* m_tex;
		int m_width, m_height;
	};

	class Renderer
	{
	public:
		static void Init(SDL_Window* window);
		static void SetAssetPath(const std::string& path);

		static void Clear();
		static void Present();

		static Texture* LoadTextureFromBMP(const std::string& bmp_file_name, const std::string& sub_dir = "");
		static void DrawTexture(Texture* tex, int x_pos, int y_pos, int scale = 1);
		static void DrawTexture(Texture* tex, const Vec2i& pos, int scale = 1);

		static void Shutdown();

		// For internal use only.
		inline static SDL_Renderer* GetSDLRenderer() { return m_renderer; }

	private:
		static SDL_Renderer* m_renderer;
		static std::string m_asset_path;

		static constexpr char PATH_SEP = '\\';
	};

}