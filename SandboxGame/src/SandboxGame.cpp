#include "Husky.h"

class SandboxGame : public husky::Game
{
public:
	SandboxGame()
	{

	}

	~SandboxGame()
	{

	}
private:

};

husky::Game* husky::CreateGame()
{
	return new SandboxGame();
}