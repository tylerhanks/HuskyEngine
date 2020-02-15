#pragma once
#include "LayerStack.h"
#include "Log.h"
#include "ImGuiLayer.h"

namespace husky {

	class Game
	{
	public:
		Game();
		virtual ~Game();

		bool Construct(int width, int height, bool full_screen);

		void SetAssetPath(const std::string& project_dir, const std::string& asset_dir);

		void PushLayer(Layer* layer);

		void Run();

		inline int Width() const { return m_width; }
		inline int Height() const { return m_height; }
		inline SDL_Window* GetSDLWindow() { return m_window; }

		inline static Game& Get() { return *s_instance; }

	protected:
		virtual bool OnCreate();
		virtual void OnDestroy();

		bool m_running;

	private:
		bool Update(float delta_time);
	
	private:
		LayerStack m_layer_stack;
		std::vector<Layer*> m_tbd_layers;
		ImGuiLayer* m_imgui_layer;
		SDL_Event e;
		SDL_Window* m_window;
		int m_width, m_height;

		static Game* s_instance;
	};

	// To be defined in CLIENT.
	Game* CreateGame();

}
