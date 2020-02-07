#pragma once
#include "Window.h"

namespace husky {

	class Game
	{
	public:
		Game();
		virtual ~Game();

		void Run();
		bool Construct(int width, int height, bool full_screen);

	protected:
		virtual bool OnCreate();
		virtual bool OnUpdate(float delta_time);
		virtual void OnDestroy();

		bool m_running;

	private:

	};

	// To be defined in CLIENT.
	Game* CreateGame();

}
