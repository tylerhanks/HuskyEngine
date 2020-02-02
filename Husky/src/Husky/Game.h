#pragma once

namespace husky {

	class Game
	{
	public:
		Game();
		virtual ~Game();

		void Run();
	private:

	};

	// To be defined in CLIENT.
	Game* CreateGame();

}
