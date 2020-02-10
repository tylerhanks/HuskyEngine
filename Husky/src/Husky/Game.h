#pragma once
#include "LayerStack.h"
#include "Log.h"

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

	protected:
		virtual bool OnCreate();
		virtual void OnDestroy();

		bool m_running;

	private:
		bool Update(float delta_time);

		LayerStack m_layer_stack;
		std::vector<Layer*> m_tbd_layers;
		SDL_Event e;
		SDL_Window* m_window;

		int m_width, m_height;
	};

	// To be defined in CLIENT.
	Game* CreateGame();

}
