#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>

#include "Vector2D.h"
#include "Rect.h"

namespace husky {

	template<typename T>
	using ref = std::shared_ptr<T>;

	class Renderer;

	struct Color
	{
	public:
		Color();
		Color(int r, int g, int b, int a = 255);

		friend class Renderer;

	private:
		SDL_Color m_color;
	};

	namespace colors {

		static const Color Black(0, 0, 0);
		static const Color White(255, 255, 255);
		static const Color Red(255, 0, 0);
		static const Color Lime(0, 255, 0);
		static const Color Blue(0, 0, 255);
		static const Color Yellow(255, 255, 0);
		static const Color Cyan(0, 255, 255);
		static const Color Magenta(255, 0, 255);
		static const Color Silver(192, 192, 192);
		static const Color Gray(128, 128, 128);
		static const Color Maroon(128, 0, 0);
		static const Color Olive(128, 128, 0);
		static const Color Green(0, 128, 0);
		static const Color Purple(128, 0, 128);
		static const Color Teal(0, 128, 128);
		static const Color Navy(0, 0, 128);

	}

	struct Texture
	{
	public:
		Texture(SDL_Texture* tex, int width, int height);
		~Texture();

		friend class Renderer;

	private:
		SDL_Texture* m_tex;
		int m_width, m_height;
	};

	struct Font
	{
	public:
		Font(TTF_Font* font);
		~Font();

		friend class Renderer;

	private:
		TTF_Font* m_font;
	};

	class Renderer
	{
	public:
		static void Init(SDL_Window* window);
		static void SetAssetPath(const std::string& path);

		static void Clear();
		static void Present();

		static ref<Font> LoadFontFromTTF(const std::string& font_file_name, int font_size, const std::string& sub_dir = "");
		static ref<Texture> RenderTextSolid(const std::string& message, ref<Font> font, const Color& color);
		static ref<Texture> RenderTextShaded(const std::string& message, ref<Font> font, const Color& fg_color, const Color& bg_color);
		static ref<Texture> RenderTextBlended(const std::string& message, ref<Font> font, const Color& color);

		static ref<Texture> LoadTextureFromBMP(const std::string& bmp_file_name, const std::string& sub_dir = "", const Color& chroma = colors::Magenta);
		static void DrawTexture(ref<Texture> tex, int x_pos, int y_pos, int scale = 1);
		static void DrawTexture(ref<Texture> tex, const Vec2i& pos, int scale = 1);

		static void Shutdown();

		// For internal use only.
		inline static SDL_Renderer* GetSDLRenderer() { return m_renderer; }

	private:
		static SDL_Renderer* m_renderer;
		static std::string m_asset_path;

		static constexpr char PATH_SEP = '\\';
	};

}